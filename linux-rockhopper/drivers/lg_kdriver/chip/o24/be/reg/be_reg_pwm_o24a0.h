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

#ifndef _BE_O24A0_PE_O24A0_H_
#define _BE_O24A0_PE_O24A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20100 RW 0x0000_0000
	UINT32 pwm0_tx_intr                     :1;	//(0,RW,0x00) //pwm0 tx interrupt
	UINT32 pwm1_tx_intr                     :1;	//(1,RW,0x00) //pwm1 tx interrupt
	UINT32 pwm2_tx_intr                     :1;	//(2,RW,0x00) //pwm2 tx interrupt
	UINT32 pwm3_rx_intr0                    :1;	//(3,RW,0x00) //pwm3 rx0 interrupt
	UINT32 pwm3_rx_intr1                    :1;	//(4,RW,0x00) //pwm3 rx1 interrupt
	UINT32 resvd                            :27;
	};
}O24A0_PE_PWM_INTR_STATUS_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20104 RW 0x0000_0000
	UINT32 pwm0_tx_intr                     :1;	//(0,RW,0x00) //pwm0 tx interrupt
	UINT32 pwm1_tx_intr                     :1;	//(1,RW,0x00) //pwm1 tx interrupt
	UINT32 pwm2_tx_intr                     :1;	//(2,RW,0x00) //pwm2 tx interrupt
	UINT32 pwm3_rx_intr0                    :1;	//(3,RW,0x00) //pwm3 rx0 interrupt
	UINT32 pwm3_rx_intr1                    :1;	//(4,RW,0x00) //pwm3 rx1 interrupt
	UINT32 resvd                            :27;
	};
}O24A0_PE_PWM_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20108 RO 0x0000_0000
	UINT32 pwm0_tx_intr                     :1;	//(0,RO,0x00) //pwm0 tx interrupt
	UINT32 pwm1_tx_intr                     :1;	//(1,RO,0x00) //pwm1 tx interrupt
	UINT32 pwm2_tx_intr                     :1;	//(2,RO,0x00) //pwm2 tx interrupt
	UINT32 pwm3_rx_intr0                    :1;	//(3,RO,0x00) //pwm3 rx0 interrupt
	UINT32 pwm3_rx_intr1                    :1;	//(4,RO,0x00) //pwm3 rx1 interrupt
	UINT32 resvd                            :27;
	};
}O24A0_PE_PWM_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2010C RW 0x0000_001F
	UINT32 pwm0_tx_intr                     :1;	//(0,RW,0x01) //pwm0 tx interrupt
	UINT32 pwm1_tx_intr                     :1;	//(1,RW,0x01) //pwm1 tx interrupt
	UINT32 pwm2_tx_intr                     :1;	//(2,RW,0x01) //pwm2 tx interrupt
	UINT32 pwm3_rx_intr0                    :1;	//(3,RW,0x01) //pwm3 rx0 interrupt
	UINT32 pwm3_rx_intr1                    :1;	//(4,RW,0x01) //pwm3 rx1 interrupt
	UINT32 resvd                            :27;
	};
}O24A0_PE_PWM_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20110 RW 0x0000_0000
	UINT32 pwm0_en                          :1;	//(0,RW,0x00) //PWM0 enable	0 := diable	1  = enable
	UINT32 pwm0_freq_mode                   :3;	//(3:1,RW,0x00) //PWM0 frequency selection	000 := 30, 60 or 120 Hz for native display frame rate. (1주기당 1번)	001  = 60, 120 or 240 Hz (1주기당 2번)	010  = 120, 240 or 480 Hz (1주기당 4번)	011  = 240, 480 or 960 Hz (1주기당 8번)
	UINT32 pwm0_resolution                  :2;	//(5:4,RW,0x00) //when Duty control method, unit step of duty.	"00" := 256 pixel is one unit	"01" = 512 pixel	"10" = 1024 pixel	"11" = reserved
	UINT32 pwm0_inv                         :1;	//(6,RW,0x00) //pwm inverse	0 := PWM	1  = inversed PWM
	UINT32 pwm0_sel                         :1;	//(7,RW,0x00) //selection of PWM0 gen method	0 := Duty control	1  = Width control
	UINT32 pwm0_width_falling_pos           :24;	//(31:8,RW,0x0000_0000) //Pixel clock counts for falling position above VSYNC full clock counts for width control	pwm_resolution과 무관하며,	pwm_freq_mode에 따른 falling_pos는 사용자가 계산하여 입력해야 한다.
	};
}O24A0_PE_PWM0_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20114 RW 0x0000_0000
	UINT32 pwm0_free_width                  :24;	//(23:0,RW,0x0000_0000) //when free run mode, size of one Vsync's width by pixel. (24bits)
	UINT32 resvd0                           :4;
	UINT32 pwm0_end_ctrl0                   :1;	//(28,RW,0x00) //falling end control
	UINT32 pwm0_end_ctrl1                   :1;	//(29,RW,0x00) //rising end control
	UINT32 resvd1                           :2;
	};
}O24A0_PE_PWM0_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20118 RW 0x0000_0000
	UINT32 pwm0_intr_mask                   :16;	//(15:0,RW,0x0) //interrupt mask of PWM0 frequency  ( if mask bit = '1', the specified interrupt is actived.)	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	UINT32 pwm0_method                      :1;	//(16,RW,0x00) //PWM0 generation select from V sync locking and free run mode	0 := V sync locking mode	1  = Free run mode
	UINT32 pwm0_mon                         :3;	//(19:17,RW,0x00) //"000" := CCO	"001"  = IMX	"010"  = VCP	"011"  = SHP	"100"  = REC
	UINT32 pwm0_mux                         :4;	//(23:20,RW,0x00) //pwm output mux register	"000" := pwm0	"001" = pwm0	"010" = dvo VSYNC	"011" = dvo HSYNC	"100" = dvo DE	"101" = (pwm0 or pwm1)	"110" = (pwm0 or pwm2)	"111" = (pwm0 or pwm1 or pwm2)	"1000" = pwm_trigger_out
	UINT32 pwm0_phase_mode                  :2;	//(25:24,RW,0x00) //"00" := 0 offset	"01" = period 의 1/2 offset	"10" = period 의 1/4 offset	"11" = period 의 1/8 offset
	UINT32 pwm0_phase_index                 :3;	//(28:26,RW,0x00) //예를 들어, phase_shift를 1/2 offset mode로 선택하면, "000" 과 "001"의 값으로 offset을 반영할 수 있다.	"000" := 0 offset start	"001" = 1/n offset start	"010" = 2/n offset start	"011" = 3/n offset start	"100" = 4/n offset start	"101" = 5/n offset start	"110" = 6/n offset start	"111" = 7/n offset start
	UINT32 resvd                            :1;
	UINT32 pwm0_fc_h_disp                   :1;	//(30,RW,0x00) //force to low PWM0 signal	0 := PWM signal	1  = fixed high signal
	UINT32 pwm0_fc_l_disp                   :1;	//(31,RW,0x00) //force to low PWM0 signal	0 := PWM signal	1  = fixed low signal
	};
}O24A0_PE_PWM0_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2011C RW 0x0000_0000
	UINT32 pwm1_en                          :1;	//(0,RW,0x00) //PWM1 enable	0 := diable	1  = enable
	UINT32 pwm1_freq_mode                   :3;	//(3:1,RW,0x00) //PWM1 frequency selection	000 := 30, 60 or 120 Hz for native display frame rate. (1주기당 1번)	001  = 60, 120 or 240 Hz (1주기당 2번)	010  = 120, 240 or 480 Hz (1주기당 4번)	011  = 240, 480 or 960 Hz (1주기당 8번)
	UINT32 pwm1_resolution                  :2;	//(5:4,RW,0x00) //when Duty control method, unit step of duty.	"00" := 256 pixel is one unit	"01" = 512 pixel	"10" = 1024 pixel	"11" = reserved
	UINT32 pwm1_inv                         :1;	//(6,RW,0x00) //pwm inverse	0 := PWM	1  = inversed PWM
	UINT32 pwm1_sel                         :1;	//(7,RW,0x00) //selection of PWM1 gen method	0 := Duty control	1  = Width control
	UINT32 pwm1_width_falling_pos           :24;	//(31:8,RW,0x0000_0000) //Pixel clock counts for falling position above VSYNC full clock counts for width control	pwm_resolution과 무관하며,	pwm_freq_mode에 따른 falling_pos는 사용자가 계산하여 입력해야 한다.
	};
}O24A0_PE_PWM1_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20120 RW 0x0000_0000
	UINT32 pwm1_free_width                  :24;	//(23:0,RW,0x0000_0000) //when free run mode, size of one Vsync's width by pixel. (24bits)
	UINT32 resvd0                           :4;
	UINT32 pwm1_end_ctrl0                   :1;	//(28,RW,0x00) //falling end control
	UINT32 pwm1_end_ctrl1                   :1;	//(29,RW,0x00) //rising end control
	UINT32 resvd1                           :2;
	};
}O24A0_PE_PWM1_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20124 RW 0x0000_0000
	UINT32 pwm1_intr_mask                   :16;	//(15:0,RW,0x0) //interrupt mask of PWM1 frequency  ( if mask bit = '1', the specified interrupt is actived.)	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	UINT32 pwm1_method                      :1;	//(16,RW,0x00) //PWM1 generation select from V sync locking and free run mode	0 := V sync locking mode	1  = Free run mode
	UINT32 pwm1_mon                         :3;	//(19:17,RW,0x00) //"000" := CCO	"001"  = IMX	"010"  = VCP	"011"  = SHP	"100"  = REC
	UINT32 pwm1_mux                         :4;	//(23:20,RW,0x00) //pwm output mux register	"000" := pwm1	"001" = pwm1	"010" = dvo VSYNC	"011" = dvo HSYNC	"100" = dvo DE	"101" = (pwm1 or pwm0)	"110" = (pwm1 or pwm2)	"111" = (pwm1 or pwm1 or pwm2)	"1000" = pwm_trigger_out
	UINT32 pwm1_phase_mode                  :2;	//(25:24,RW,0x00) //"00" := 0 offset	"01" = period 의 1/2 offset	"10" = period 의 1/4 offset	"11" = period 의 1/8 offset
	UINT32 pwm1_phase_index                 :3;	//(28:26,RW,0x00) //"000" := 1/n offset	"001" = 2/n offset	"010" = 3/n offset	"011" = 4/n offset	"100" = 5/n offset	"101" = 6/n offset	"110" = 7/n offset	"111" = 8/n offset
	UINT32 resvd                            :1;
	UINT32 pwm1_fc_h_disp                   :1;	//(30,RW,0x00) //force to low PWM1 signal	0 := PWM signal	1  = fixed high signal
	UINT32 pwm1_fc_l_disp                   :1;	//(31,RW,0x00) //force to low PWM1 signal	0 := PWM signal	1  = fixed low signal
	};
}O24A0_PE_PWM1_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20128 RW 0x0000_0000
	UINT32 pwm2_en                          :1;	//(0,RW,0x00) //PWM2 enable	0 := diable	1  = enable
	UINT32 pwm2_freq_mode                   :3;	//(3:1,RW,0x00) //PWM2 frequency selection	000 := 30, 60 or 120 Hz for native display frame rate. (1주기당 1번)	001  = 60, 120 or 240 Hz (1주기당 2번)	010  = 120, 240 or 480 Hz (1주기당 4번)	011  = 240, 480 or 960 Hz (1주기당 8번)
	UINT32 pwm2_resolution                  :2;	//(5:4,RW,0x00) //when Duty control method, unit step of duty.	"00" := 256 pixel is one unit	"01" = 512 pixel	"10" = 1024 pixel	"11" = reserved
	UINT32 pwm2_inv                         :1;	//(6,RW,0x00) //pwm inverse	0 := PWM	1  = inversed PWM
	UINT32 pwm2_sel                         :1;	//(7,RW,0x00) //selection of PWM2 gen method	0 := Duty control	1  = Width control
	UINT32 pwm2_width_falling_pos           :24;	//(31:8,RW,0x0000_0000) //Pixel clock counts for falling position above VSYNC full clock counts for width control	pwm_resolution과 무관하며,	pwm_freq_mode에 따른 falling_pos는 사용자가 계산하여 입력해야 한다.
	};
}O24A0_PE_PWM2_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2012C RW 0x0000_0000
	UINT32 pwm2_free_width                  :24;	//(23:0,RW,0x0000_0000) //when free run mode, size of one Vsync's width by pixel. (24bits)
	UINT32 resvd0                           :4;
	UINT32 pwm2_end_ctrl0                   :1;	//(28,RW,0x00) //falling end control
	UINT32 pwm2_end_ctrl1                   :1;	//(29,RW,0x00) //rising end control
	UINT32 resvd1                           :2;
	};
}O24A0_PE_PWM2_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20130 RW 0x0000_0000
	UINT32 pwm2_intr_mask                   :16;	//(15:0,RW,0x0) //interrupt mask of PWM2 frequency  ( if mask bit = '1', the specified interrupt is actived.)	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	UINT32 pwm2_method                      :1;	//(16,RW,0x00) //PWM2 generation select from V sync locking and free run mode	0 := V sync locking mode	1  = Free run mode
	UINT32 pwm2_mon                         :3;	//(19:17,RW,0x00) //"000" := CCO	"001"  = IMX	"010"  = VCP	"011"  = SHP	"100"  = REC
	UINT32 pwm2_mux                         :4;	//(23:20,RW,0x00) //pwm output mux register	"000" := pwm2	"001" = pwm2	"010" = dvo VSYNC	"011" = dvo HSYNC	"100" = dvo DE	"101" = (pwm2 or pwm0)	"110" = (pwm2 or pwm1)	"111" = (pwm2 or pwm1 or pwm2)	"1000" = pwm_trigger_out
	UINT32 pwm2_phase_mode                  :2;	//(25:24,RW,0x00) //"00" := 0 offset	"01" = period 의 1/2 offset	"10" = period 의 1/4 offset	"11" = period 의 1/8 offset
	UINT32 pwm2_phase_index                 :3;	//(28:26,RW,0x00) //"000" := 1/n offset	"001" = 2/n offset	"010" = 3/n offset	"011" = 4/n offset	"100" = 5/n offset	"101" = 6/n offset	"110" = 7/n offset	"111" = 8/n offset
	UINT32 resvd                            :1;
	UINT32 pwm2_fc_h_disp                   :1;	//(30,RW,0x00) //force to low PWM2 signal	0 := PWM signal	1  = fixed high signal
	UINT32 pwm2_fc_l_disp                   :1;	//(31,RW,0x00) //force to low PWM2 signal	0 := PWM signal	1  = fixed low signal
	};
}O24A0_PE_PWM2_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20134 RW 0x0000_0000
	UINT32 pwm3_en                          :1;	//(0,RW,0x00) //PWM3 enable	0 := diable	1  = enable
	UINT32 pwm3_freq_mode                   :3;	//(3:1,RW,0x00) //PWM3 frequency selection	000 := 30, 60 or 120 Hz for native display frame rate.	001  = 60, 120 or 240 Hz	010  = 120, 240 or 480 Hz	011  = 240, 480 or 960 Hz
	UINT32 resvd                            :4;
	UINT32 pwm3_threshold                   :24;	//(31:8,RW,0x0000_0000) //diffrence of previous PWM and current PWM threshold	if difference is over this threshold, interrupt is occurred. (24bits)
	};
}O24A0_PE_PWM3_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20138 RW 0x0000_0000
	UINT32 pwm3_intr_mask1                  :8;	//(7:0,RW,0x0) //interrupt mask of PWM3 frequency (PWM_RX0)  ( if mask bit = '1', the specified interrupt is actived.)	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	UINT32 resvd0                           :8;
	UINT32 pwm3_intr_mask0                  :1;	//(16,RW,0x00) //interrupt mask of PWM3 (PWM_RX1) ( if mask bit = '1', the specified interrupt is actived.)	bit selection control.	16 = difference notification of PWM
	UINT32 resvd1                           :3;
	UINT32 pwm3_in_mux                      :2;	//(21:20,RW,0x00) //0 := pwm_in	1 = pwm0_tx (for self-test)	2 = pwm1_tx (for self-test)	3 = pwm2_tx (for self-test)
	UINT32 resvd2                           :10;
	};
}O24A0_PE_PWM3_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2013C RO 0x0000_0000
	UINT32 pwm3_0_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_0_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20140 RO 0x0000_0000
	UINT32 pwm3_0_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_0_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20144 RO 0x0000_0000
	UINT32 pwm3_1_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_1_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20148 RO 0x0000_0000
	UINT32 pwm3_1_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_1_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2014C RO 0x0000_0000
	UINT32 pwm3_2_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_2_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20150 RO 0x0000_0000
	UINT32 pwm3_2_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_2_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20154 RO 0x0000_0000
	UINT32 pwm3_3_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_3_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20158 RO 0x0000_0000
	UINT32 pwm3_3_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_3_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2015C RO 0x0000_0000
	UINT32 pwm3_4_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_4_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20160 RO 0x0000_0000
	UINT32 pwm3_4_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_4_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20164 RO 0x0000_0000
	UINT32 pwm3_5_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_5_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20168 RO 0x0000_0000
	UINT32 pwm3_5_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_5_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2016C RO 0x0000_0000
	UINT32 pwm3_6_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_6_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20170 RO 0x0000_0000
	UINT32 pwm3_6_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_6_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20174 RO 0x0000_0000
	UINT32 pwm3_7_low                       :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_7_LOW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20178 RO 0x0000_0000
	UINT32 pwm3_7_high                      :24;	//(23:0,RO,0x0000_0000) //
	UINT32 resvd                            :8;
	};
}O24A0_PE_PWM3_7_HIGH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2017C RW 0x0000_0000
	UINT32 pwm0_v_we                        :1;	//(0,RW,0x00) //
	UINT32 pwm1_v_we                        :1;	//(1,RW,0x00) //
	UINT32 pwm2_v_we                        :1;	//(2,RW,0x00) //
	UINT32 pwm0_v_sub_we                    :1;	//(3,RW,0x00) //
	UINT32 pwm1_v_sub_we                    :1;	//(4,RW,0x00) //
	UINT32 pwm2_v_sub_we                    :1;	//(5,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pwm0_v_sub_f_we                  :1;	//(8,RW,0x00) //
	UINT32 pwm1_v_sub_f_we                  :1;	//(9,RW,0x00) //
	UINT32 pwm2_v_sub_f_we                  :1;	//(10,RW,0x00) //
	UINT32 resvd1                           :21;
	};
}O24A0_PE_PWM_V_LOAD_WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20180 RW 0x0000_0000
	UINT32 pwm0_v_r                         :16;	//(15:0,RW,0x0) //PWM0 rising count	pwm0_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm0_v_r_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM0 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM0_V_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20184 RW 0x0000_0000
	UINT32 pwm0_v_f                         :16;	//(15:0,RW,0x0) //PWM0 falling count	pwm0_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm0_v_f_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM0 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM0_V_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20188 RW 0x0000_0000
	UINT32 pwm1_v_r                         :16;	//(15:0,RW,0x0) //PWM1 rising count	pwm1_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm1_v_r_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM1	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM1_V_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2018C RW 0x0000_0000
	UINT32 pwm1_v_f                         :16;	//(15:0,RW,0x0) //PWM1 rising count	pwm1_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm1_v_f_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM1 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM1_V_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20190 RW 0x0000_0000
	UINT32 pwm2_v_r                         :16;	//(15:0,RW,0x0) //PWM2 rising count	pwm2_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm2_v_r_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM2	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM2_V_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20194 RW 0x0000_0000
	UINT32 pwm2_v_f                         :16;	//(15:0,RW,0x0) //PWM2 falling count	pwm2_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm2_v_f_id                      :4;	//(31:28,RW,0x00) //Duty range ID of PWM2	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM2_V_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA20198 RW 0x0000_0000
	UINT32 pwm0_v_sub                       :16;	//(15:0,RW,0x0) //PWM0 sub rising count	pwm0_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm0_v_sub_id                    :4;	//(31:28,RW,0x00) //This register can be used for duty control and width control.	For duty control, you can use pwm#_v_r/f register and pwm#_v_sub register for controlling pwm rising and falling count.	For width control, you can use pwm#_v_r register and pwm#_v_sub register for pwm width pixel count. For example,	pwm#_0_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 0.	pwm#_1_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 1.	pwm#_2_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 2.	pwm#_3_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 3.	pwm#_4_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 4.	pwm#_5_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 5.	pwm#_6_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 6.	pwm#_7_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 7.	pwm#_8_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 8.
	};
}O24A0_PE_PWM0_V_SUB_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2019C RW 0x0000_0000
	UINT32 pwm1_v_sub                       :16;	//(15:0,RW,0x0) //PWM1 sub rising count	pwm1_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm1_v_sub_id                    :4;	//(31:28,RW,0x00) //This register can be used for duty control and width control.	For duty control, you can use pwm#_v_r/f register and pwm#_v_sub register for controlling pwm rising and falling count.	For width control, you can use pwm#_v_r register and pwm#_v_sub register for pwm width pixel count. For example,	pwm#_0_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 0.	pwm#_1_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 1.	pwm#_2_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 2.	pwm#_3_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 3.	pwm#_4_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 4.	pwm#_5_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 5.	pwm#_6_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 6.	pwm#_7_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 7.	pwm#_8_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 8.
	};
}O24A0_PE_PWM1_V_SUB_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201A0 RW 0x0000_0000
	UINT32 pwm2_v_sub                       :16;
	UINT32 resvd                            :12;
	UINT32 pwm2_v_sub_id                    :4;	//(31:28,RW,0x00) //This register can be used for duty control and width control.	For duty control, you can use pwm#_v_r/f register and pwm#_v_sub register for controlling pwm rising and falling count.	For width control, you can use pwm#_v_r register and pwm#_v_sub register for pwm width pixel count. For example,	pwm#_0_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 0.	pwm#_1_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 1.	pwm#_2_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 2.	pwm#_3_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 3.	pwm#_4_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 4.	pwm#_5_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 5.	pwm#_6_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 6.	pwm#_7_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 7.	pwm#_8_width[23:0] = {pwm#_v_sub[7:0], pwm#_v_r[15:0]} for index 8.
	};
}O24A0_PE_PWM2_V_SUB_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201A4 RW 0x0005_0000
	UINT32 pwm0_lock_pulse_x                :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 pwm0_lock_pulse_y                :13;	//(28:16,RW,0x5) //
	UINT32 resvd1                           :2;
	UINT32 pwm0_lock_pulse_half_en          :1;	//(31,RW,0x00) //
	};
}O24A0_PE_PWM0_LOCK_PULSE_XY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201A8 RW 0x0005_0000
	UINT32 pwm1_lock_pulse_x                :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 pwm1_lock_pulse_y                :13;	//(28:16,RW,0x5) //
	UINT32 resvd1                           :2;
	UINT32 pwm1_lock_pulse_half_en          :1;	//(31,RW,0x00) //
	};
}O24A0_PE_PWM1_LOCK_PULSE_XY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201AC RW 0x0005_0000
	UINT32 pwm2_lock_pulse_x                :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 pwm2_lock_pulse_y                :13;	//(28:16,RW,0x5) //
	UINT32 resvd1                           :2;
	UINT32 pwm2_lock_pulse_half_en          :1;	//(31,RW,0x00) //
	};
}O24A0_PE_PWM2_LOCK_PULSE_XY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201B0 RW 0x0005_0000
	UINT32 pwm3_lock_pulse_x                :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 pwm3_lock_pulse_y                :13;	//(28:16,RW,0x5) //
	UINT32 resvd1                           :2;
	UINT32 pwm3_lock_pulse_half_en          :1;	//(31,RW,0x00) //
	};
}O24A0_PE_PWM3_LOCK_PULSE_XY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201B4 RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM0_WIDTH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201B8 RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM0_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201BC RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM0_OFFSET_SUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201C0 RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM1_WIDTH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201C4 RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM1_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201C8 RO 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,RO,0x0000_0000) //
	};
}O24A0_PE_PWM1_OFFSET_SUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201CC RW 0x0000_0000
	UINT32 pwm0_vwidth_man                  :24;	//(23:0,RW,0x0000_0000) //
	UINT32 pwm0_freq_offset_mode            :3;	//(26:24,RW,0x00) //0' := for debugging only.
	UINT32 resvd                            :4;
	UINT32 pwm0_vwidth_man_en               :1;	//(31,RW,0x00) //0' := disable	'1' = enable
	};
}O24A0_PE_PWM0_VWIDTH_MAN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201D0 RW 0x0000_0000
	UINT32 pwm1_vwidth_man                  :24;	//(23:0,RW,0x0000_0000) //
	UINT32 pwm1_freq_offset_mode            :3;	//(26:24,RW,0x00) //0' := for debugging only.
	UINT32 resvd                            :4;
	UINT32 pwm1_vwidth_man_en               :1;	//(31,RW,0x00) //0' := disable	'1' = enable
	};
}O24A0_PE_PWM1_VWIDTH_MAN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201D4 RW 0x0000_0000
	UINT32 pwm2_vwidth_man                  :24;	//(23:0,RW,0x0000_0000) //
	UINT32 pwm2_freq_offset_mode            :3;	//(26:24,RW,0x00) //0' := for debugging only.
	UINT32 resvd                            :4;
	UINT32 pwm2_vwidth_man_en               :1;	//(31,RW,0x00) //0' := disable	'1' = enable
	};
}O24A0_PE_PWM2_VWIDTH_MAN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201D8 RW 0x0000_0000
	UINT32 tdata00                          :16;	//(31:0,RW,0x0000_0000) //
	UINT32 pwm_master_mode                  :3;	//(18:16,RW,0x00) //"000" := master mode off.	"001" = pwm_tx0 is master.	"010" = pwm_tx1 is master.	"011" = pwm_tx2 is master.	"100" = master mode off.
	UINT32 tdata01                          :1;	//(31:0,RW,0x0000_0000) //
	UINT32 pwm2_ld_pwm                      :1;	//(20,RW,0x00) //1' 쓰고 '0'을 써야 함.
	UINT32 tdata02                          :2;	//(31:0,RW,0x0000_0000) //
	UINT32 pwm2_ld_pwm_tx_mode              :1;	//(23,RW,0x00) //0' := load mode off	'1' = load mode on
	UINT32 pwm1_ld_pwm                      :1;	//(24,RW,0x00) //1' 쓰고 '0'을 써야 함.
	UINT32 tdata03                          :2;	//(31:0,RW,0x0000_0000) //
	UINT32 pwm1_ld_pwm_tx_mode              :1;	//(27,RW,0x00) //0' := load mode off	'1' = load mode on
	UINT32 pwm0_ld_pwm                      :1;	//(28,RW,0x00) //1' 쓰고,  '0'을 써야 함.
	UINT32 tdata04                          :2;	//(31:0,RW,0x0000_0000) //
	UINT32 pwm0_ld_pwm_tx_mode              :1;	//(31,RW,0x00) //0' := load mode off	'1' = load mode on
	};
}O24A0_PE_PWM_MASTER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201DC RW 0x0000_0000
	UINT32 pwm0_v_sub_f                     :16;	//(15:0,RW,0x0) //PWM0 falling count	pwm0_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm0_v_sub_f_id                  :4;	//(31:28,RW,0x00) //Duty range ID of PWM0 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM0_V_SUB_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201E0 RW 0x0000_0000
	UINT32 pwm1_v_sub_f                     :16;	//(15:0,RW,0x0) //PWM1 falling count	pwm1_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm1_v_sub_f_id                  :4;	//(31:28,RW,0x00) //Duty range ID of PWM0 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM1_V_SUB_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201E4 RW 0x0000_0000
	UINT32 pwm2_v_sub_f                     :16;	//(15:0,RW,0x0) //PWM2 falling count	pwm2_resoultion 에 따라 full pixel count/256, /512, /1024를 처리한 값.
	UINT32 resvd                            :12;
	UINT32 pwm2_v_sub_f_id                  :4;	//(31:28,RW,0x00) //Duty range ID of PWM0 	bit selection control. (N would be 30, 60 or 120)	0 for N [Hz] : 30, 60 or 120	0, 1 for (N*2) [Hz] : 60, 120 or 240	0, 1, 2, 3 for (N*4) [Hz] : 120, 240 or 480	0, 1, 2, 3, 4, 5, 6, 7 for (N*8) [Hz] : 240, 480 or 960
	};
}O24A0_PE_PWM2_V_SUB_F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201EC RW 0x0000_0000
	UINT32 sw_reset_lock                    :1;	//(0,RW,0x00) //WR VALUE '0', '1' Don't Case
	UINT32 resvd0                           :2;
	UINT32 end_mode                         :1;	//(3,RW,0x00) //when divide_mode and frame rate chagning, close the end of line.
	UINT32 vsync_sel                        :1;	//(4,RW,0x00) //Source of PWM	0 : display Vsync	1 : external Vsync (dpe_vsync)
	UINT32 resvd1                           :3;
	UINT32 vcount_sel                       :1;	//(8,RW,0x00) //Source of PWM Vcount	0 : display sync gen's vcount	1 : internal vcount gen's vcount
	UINT32 resvd2                           :3;
	UINT32 ext_gain_apply                   :1;	//(12,RW,0x00) //External Gain apply mode, only use duty_mode	0 : disable	1 : enable
	UINT32 resvd3                           :3;
	UINT32 hcount_num                       :16;	//(31:16,RW,0x0) //Internal Vcount's one line number	0x897 (2,199, UD
	};
}O24A0_PE_SW_RESET_LOCK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201F0 RW 0x0000_C000
	UINT32 trigger_low_num                  :28;	//(27:0,RW,0x00_C000) //trigger_out low signal's position from trigger point
	UINT32 resvd                            :2;
	UINT32 trigger_pt_sel                   :1;	//(30,RW,0x0) //trigger start position	0 : rising	1 : falling
	UINT32 pwm_trigger_en                   :1;	//(31,RW,0x00) //PWM trigger process enable
	};
}O24A0_PE_PWM_TRG_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201F4 RW 0x0003_0000
	UINT32 trigger_high_num                 :28;	//(27:0,RW,0x03_0000) //trigger_out high signal's position from trigger point
	UINT32 resvd                            :4;
	};
}O24A0_PE_PWM_TRG_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201F8 RW 0x0000_0000
	UINT32 pwm_gain                         :13;	//(12:0,RW,0x0000_0000) //PWM gain
	UINT32 resvd                            :19;
	};
}O24A0_PE_PWM_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA201FC RW 0x0000_0000
	UINT32 pwm0_out_sel                     :7;	//(6:0,RW,0x0000_0000) //60: double_vactive	61: double_vsync	62: def_vactv	63: def_vsync	64: trk_t_vs	65: trk_t_va	66: disp_t_vsync	67: dispt_t_vactive	68: p_vrr_double_en	69: vrr_double_en	70: hrr_line_win	71: togg_state	72: vsync_trk	73: vactive_trk	74: short_sel	75: reg_vfp_win	76: vfp_flag	77: cvi_abnormal_dn	78: cvi_abnormal_up 	79: de_hactv	80: de_vactv	81: de_hsync	82: de_vsync	83: de_3d_lr	84: de_3d_en	85: genlock_o	86: gen_vsync_o	87: DCO_VSYNC	88: genlock_m	89: genlock_i	90: mpip_vs	91: mpip_hs	92: mpip_va	93: mpip_ha,	94: sync_disable
	UINT32 resvd0                           :1;
	UINT32 pwm1_out_sel                     :7;	//(14:8,RW,0x0000_0000) //30 : cco_vs	31 : cco_hs	32: osd_ha	33: osd_hs	34: cco_de	35: pip_vs	36: pip_hs	37: pip_va	38: pip_ha	39: pip_de	40: sb_vs	41: sb_hs	42: sb_va	43: sb_ha	44: sb_de	45: cv_toggle	46: cvi_vs	47: cvi_va	48: vcp_hfp_i	49: disp_vs	50: tracking_en	51: reg_trk_en_o	52: d_status	53: double_va	54: double_vs	55: disp_p_vactive	56: disp_p_vsync	57: reg_vrr_double_vs	58: cvi_vsync_abnormal	59: trk_actv_period
	UINT32 resvd1                           :1;
	UINT32 pwm2_out_sel                     :7;	//(22:16,RW,0x0000_0000) //0: 8k_vs	1: 8k_hs	2: 8k_va	3: 8k_ha	4: vsd_cco_osd_va	5: disp_vsync	6: disp_hsync	7: disp_vactive	8: disp_hactive	9: vsd_cco_osd_vs	10: vsd_cco_vid_vs	11: vsd_cco_vid_hs	12: vsd_cco_vid_va	13: vsd_cco_vid_ha	14: vsd_cco_vid_de	15: shp_vs_o	16: shp_hs_o	17: shp_va_o	18: shp_ha_o	19: shp_de_o	20: vcp_mv_vs	21: vcp_mv_hs	22: vcp_mv_va	23: vcp_mv_ha	24: vcp_mv_de	25: vs_toggle(dco)	26: hs_toggle(dco)	27: cvi_vs	28: cvi_hs	29: vsd_intr
	UINT32 resvd2                           :9;
	};
}O24A0_PE_PWM_OUT_SEL_T;

typedef struct {
	O24A0_PE_PWM_INTR_STATUS_EN_T                     pwm_intr_status_en;	//0xCCA20100
	O24A0_PE_PWM_INTR_CLEAR_T                             pwm_intr_clear;	//0xCCA20104
	O24A0_PE_PWM_INTR_STATUS_T                           pwm_intr_status;	//0xCCA20108
	O24A0_PE_PWM_INTR_MASK_T                               pwm_intr_mask;	//0xCCA2010C
	O24A0_PE_PWM0_CTRL0_T                                     pwm0_ctrl0;	//0xCCA20110
	O24A0_PE_PWM0_CTRL1_T                                     pwm0_ctrl1;	//0xCCA20114
	O24A0_PE_PWM0_CTRL2_T                                     pwm0_ctrl2;	//0xCCA20118
	O24A0_PE_PWM1_CTRL0_T                                     pwm1_ctrl0;	//0xCCA2011C
	O24A0_PE_PWM1_CTRL1_T                                     pwm1_ctrl1;	//0xCCA20120
	O24A0_PE_PWM1_CTRL2_T                                     pwm1_ctrl2;	//0xCCA20124
	O24A0_PE_PWM2_CTRL0_T                                     pwm2_ctrl0;	//0xCCA20128
	O24A0_PE_PWM2_CTRL1_T                                     pwm2_ctrl1;	//0xCCA2012C
	O24A0_PE_PWM2_CTRL2_T                                     pwm2_ctrl2;	//0xCCA20130
	O24A0_PE_PWM3_CTRL0_T                                     pwm3_ctrl0;	//0xCCA20134
	O24A0_PE_PWM3_CTRL1_T                                     pwm3_ctrl1;	//0xCCA20138
	O24A0_PE_PWM3_0_LOW_T                                     pwm3_0_low;	//0xCCA2013C
	O24A0_PE_PWM3_0_HIGH_T                                   pwm3_0_high;	//0xCCA20140
	O24A0_PE_PWM3_1_LOW_T                                     pwm3_1_low;	//0xCCA20144
	O24A0_PE_PWM3_1_HIGH_T                                   pwm3_1_high;	//0xCCA20148
	O24A0_PE_PWM3_2_LOW_T                                     pwm3_2_low;	//0xCCA2014C
	O24A0_PE_PWM3_2_HIGH_T                                   pwm3_2_high;	//0xCCA20150
	O24A0_PE_PWM3_3_LOW_T                                     pwm3_3_low;	//0xCCA20154
	O24A0_PE_PWM3_3_HIGH_T                                   pwm3_3_high;	//0xCCA20158
	O24A0_PE_PWM3_4_LOW_T                                     pwm3_4_low;	//0xCCA2015C
	O24A0_PE_PWM3_4_HIGH_T                                   pwm3_4_high;	//0xCCA20160
	O24A0_PE_PWM3_5_LOW_T                                     pwm3_5_low;	//0xCCA20164
	O24A0_PE_PWM3_5_HIGH_T                                   pwm3_5_high;	//0xCCA20168
	O24A0_PE_PWM3_6_LOW_T                                     pwm3_6_low;	//0xCCA2016C
	O24A0_PE_PWM3_6_HIGH_T                                   pwm3_6_high;	//0xCCA20170
	O24A0_PE_PWM3_7_LOW_T                                     pwm3_7_low;	//0xCCA20174
	O24A0_PE_PWM3_7_HIGH_T                                   pwm3_7_high;	//0xCCA20178
	O24A0_PE_PWM_V_LOAD_WRITE_T                         pwm_v_load_write;	//0xCCA2017C
	O24A0_PE_PWM0_V_R_T                                         pwm0_v_r;	//0xCCA20180
	O24A0_PE_PWM0_V_F_T                                         pwm0_v_f;	//0xCCA20184
	O24A0_PE_PWM1_V_R_T                                         pwm1_v_r;	//0xCCA20188
	O24A0_PE_PWM1_V_F_T                                         pwm1_v_f;	//0xCCA2018C
	O24A0_PE_PWM2_V_R_T                                         pwm2_v_r;	//0xCCA20190
	O24A0_PE_PWM2_V_F_T                                         pwm2_v_f;	//0xCCA20194
	O24A0_PE_PWM0_V_SUB_R_T                                 pwm0_v_sub_r;	//0xCCA20198
	O24A0_PE_PWM1_V_SUB_R_T                                 pwm1_v_sub_r;	//0xCCA2019C
	O24A0_PE_PWM2_V_SUB_R_T                                 pwm2_v_sub_r;	//0xCCA201A0
	O24A0_PE_PWM0_LOCK_PULSE_XY_T                     pwm0_lock_pulse_xy;	//0xCCA201A4
	O24A0_PE_PWM1_LOCK_PULSE_XY_T                     pwm1_lock_pulse_xy;	//0xCCA201A8
	O24A0_PE_PWM2_LOCK_PULSE_XY_T                     pwm2_lock_pulse_xy;	//0xCCA201AC
	O24A0_PE_PWM3_LOCK_PULSE_XY_T                     pwm3_lock_pulse_xy;	//0xCCA201B0
	O24A0_PE_PWM0_WIDTH_T                                     pwm0_width;	//0xCCA201B4
	O24A0_PE_PWM0_OFFSET_T                                   pwm0_offset;	//0xCCA201B8
	O24A0_PE_PWM0_OFFSET_SUM_T                           pwm0_offset_sum;	//0xCCA201BC
	O24A0_PE_PWM1_WIDTH_T                                     pwm1_width;	//0xCCA201C0
	O24A0_PE_PWM1_OFFSET_T                                   pwm1_offset;	//0xCCA201C4
	O24A0_PE_PWM1_OFFSET_SUM_T                           pwm1_offset_sum;	//0xCCA201C8
	O24A0_PE_PWM0_VWIDTH_MAN_T                           pwm0_vwidth_man;	//0xCCA201CC
	O24A0_PE_PWM1_VWIDTH_MAN_T                           pwm1_vwidth_man;	//0xCCA201D0
	O24A0_PE_PWM2_VWIDTH_MAN_T                           pwm2_vwidth_man;	//0xCCA201D4
	O24A0_PE_PWM_MASTER_T                                     pwm_master;	//0xCCA201D8
	O24A0_PE_PWM0_V_SUB_F_T                                 pwm0_v_sub_f;	//0xCCA201DC
	O24A0_PE_PWM1_V_SUB_F_T                                 pwm1_v_sub_f;	//0xCCA201E0
	O24A0_PE_PWM2_V_SUB_F_T                                 pwm2_v_sub_f;	//0xCCA201E4
	UINT32                                                    reserved0;	//0xCCA201E8
	O24A0_PE_SW_RESET_LOCK_T                               sw_reset_lock;	//0xCCA201EC
	O24A0_PE_PWM_TRG_CTRL0_T                               pwm_trg_ctrl0;	//0xCCA201F0
	O24A0_PE_PWM_TRG_CTRL1_T                               pwm_trg_ctrl1;	//0xCCA201F4
	O24A0_PE_PWM_GAIN_T                                         pwm_gain;	//0xCCA201F8
	O24A0_PE_PWM_OUT_SEL_T                                   pwm_out_sel;	//0xCCA201FC
}PE_PWM_REG_O24A0_T;

#endif