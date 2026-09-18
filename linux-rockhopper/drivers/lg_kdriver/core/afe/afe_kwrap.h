 /******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file afe_kadp.h
 *
 *  application interface header for afe device
 *
 *  @author		wonsik.do (wonsik.do@lge.com)
 *  @version		1.0
 *  @date		2010-01-03
 *
 *  @addtogroup lg1150_afe
 *	@{
 */

#ifndef	_AFE_KWRAP_H_
#define	_AFE_KWRAP_H_

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include "afe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef struct
{
	UINT16	u16_Width;
	UINT16	u16_Height;
} kwrap_afe_resolution_t;
typedef struct
{
	UINT16 u16_HStart;
	UINT16 u16_VStart;
	UINT16 u16_HTotal;
	UINT16 u16_Width;
	UINT16 u16_Height;
} kwrap_afe_pcmode_info_t;
/*------------------------------------------------------------------------------
	Extern Function Prototype Declaration
------------------------------------------------------------------------------*/
int afe_kwrap_open(void);
int afe_kwrap_adc_init(void);
int afe_kwrap_cvd_init(LX_AFE_CVD_SELECT_T select_main_sub);
int afe_kwrap_cvd_set_source_type(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_SOURCE_TYPE_T select_cvbs_svideo, LX_AFE_CVD_INPUT_PORT_T select_cvbs_input_port, LX_AFE_CVD_INPUT_PORT_T select_chroma_input_port, LX_AFE_CVD_SOURCE_ATTRIBUTE_T select_source_attribute);
int afe_kwrap_adc_set_source_type(LX_AFE_ADC_INPUT_SOURCE_TYPE_T select_rgb_ypbpr, LX_AFE_ADC_INPUT_PORT_T select_adc_input_port);
int afe_kwrap_set_analog_color_system(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T 	color_system);
int afe_kwrap_cvd_setsyncdetectionfortuning(BOOLEAN bEnable);
int afe_kwrap_cvd_sync_exist(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN *cvd_sync);
int	afe_kwrap_cvd_read_vfreq(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 *is_line625);
int afe_kwrap_ttx_set_video_standard(LX_AFE_VIDEO_SYSTEM_T cvd_standard);
int afe_kwrap_cvd_get_timing_info(LX_AFE_CVD_SELECT_T select_main_sub, LX_AFE_CVD_TIMING_INFO_T *cvd_timing_info);
int afe_kwrap_get_fb_status(LX_AFE_SCART_MODE_T *mode);
int afe_kwrap_get_scart_ar(LX_AFE_SCART_ID_T Scart_Id, LX_AFE_SCART_AR_T *Scart_AR);
int afe_kwrap_set_adc_gain(UINT16 adc_red_value, UINT16 adc_green_value, UINT16 adc_blue_value);
int afe_kwrap_set_adc_offset(UINT16 adc_red_value, UINT16 adc_green_value, UINT16 adc_blue_value);
int afe_kwrap_get_adc_gain(LX_AFE_ADC_GAIN_VALUE_T *gain_param);
int afe_kwrap_get_adc_offset(LX_AFE_ADC_OFFSET_VALUE_T *offset_param);
int afe_kwrap_adc_get_timing_info(LX_AFE_ADC_TIMING_INFO_T *adc_timing_info);
int afe_kwrap_get_pc_mode_info(LX_AFE_PCMODE_INFO_T *pPcmode_info);
int afe_kwrap_pc_adjust(LX_AFE_ADJ_PCMODE_T pc_adjust_mode, SINT16 pc_adjust_value);
int afe_kwrap_pc_auto_adjust(LX_AFE_ADJ_PC_T *pPc_adjust);
int afe_kwrap_set_scart_overlay(BOOLEAN bOnOff);
int afe_kwrap_get_default_pc_mode(UINT8 index, kwrap_afe_pcmode_info_t *pPCmode_table_info);
int afe_kwrap_adc_calibration(BOOLEAN bInternal, BOOLEAN bRGB, UINT16 TargetForRGain, UINT16 TargetForGGain, UINT16 TargetForBGain, BOOLEAN bEnableCompParams);
int afe_kwrap_adc_set_default_modetable(void);
int afe_kwrap_set_user_pcmode_resolution(UINT32 user_resolution);
int afe_kwrap_adc_set_scart_mode(BOOLEAN scart_enable);
int afe_kwrap_close(void);
int afe_kwrap_select_vport_output(LX_AFE_VPORT_OUT_SRC_T out_src, LX_AFE_VPORT_OUT_CH_T out_ch);
int afe_kwrap_vport_reg_read(UINT32 addr, UINT32 *data);
int afe_kwrap_vport_reg_write(UINT32 addr, UINT32 data);
int afe_kwrap_cvd_start_timer(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 timeout);
int afe_kwrap_cvd_stop_timer(LX_AFE_CVD_SELECT_T select_main_sub);
int afe_kwrap_cvd_program_color_system(LX_AFE_CVD_SELECT_T select_main_sub, UINT8 color_system);
int afe_kwrap_adc_set_llpll(UINT32 index);
int afe_kwrap_adc_get_sync_status(BOOLEAN *sync_status);
int afe_kwrap_adc_test(LX_AFE_ADC_TEST_PARAM_T *pADC_Test_Param_t);
int afe_kwrap_cvd_test(LX_AFE_CVD_TEST_PARAM_T *pCVD_Test_Param_t);
int afe_kwrap_adc_reset_digital(void);
int afe_kwrap_adc_reset_digital_24mhz(void);
int afe_kwrap_adc_reset_llpll(void);
int afe_kwrap_cvd_set_sw_3dcomb_control(UINT8 enable, UINT32 hf_thr, UINT32 lf_thr, UINT32 diff_thr, UINT32 region_30_mode);
int afe_kwrap_adc_power_control(UINT32 enable);
int afe_kwrap_cvd_power_control(UINT32 enable);
int afe_kwrap_adc_read_pixel_value(UINT32 x_pos, UINT32 y_pos, UINT32 x_size, UINT32 y_size, UINT32 *sum_r_value, UINT32 *sum_g_value, UINT32 *sum_b_value);

int afe_kwrap_adc_enable_periodic_signal_info_read(UINT32 enable);
int afe_kwrap_adc_execute_format_detection(void);
int afe_kwrap_adc_enable_component_auto_phase(UINT32 enable);
int afe_kwrap_cvd_enable_detection_interrupt(UINT32 enable);
int afe_kwrap_cvd_get_states_detail(LX_AFE_CVD_STATES_DETAIL_T *pcvd_states_detail_t);
int afe_kwrap_cvd_get_lock_states(LX_AFE_CVD_SELECT_T select_main_sub, UINT32 *Cvd_Lock_States);
int afe_kwrap_cvd_set_pq_value(LX_AFE_CVD_PQ_MODE_T	cvd_pq_mode);
int afe_kwrap_adc_test(LX_AFE_ADC_TEST_PARAM_T *pADC_Test_Param_t);
int afe_kwrap_cvd_bypass_control(LX_AFE_CVD_BYPASS_SOURCE_T buf_out_1_sel,  LX_AFE_CVD_BYPASS_SOURCE_T buf_out_2_sel,  LX_AFE_CVD_BYPASS_CVBS_SOURCE_T	cvbs_source_sel);
int afe_kwrap_cvd_vdac_power_control(BOOLEAN bOnOff);
int afe_kwrap_lvds_src_control(LX_AFE_LVDS_SELECT_T lvds_sel, LX_AFE_LVDS_PDB_T lvds_power, LX_AFE_LVDS_DATA_TYPE_T lvds_type, LX_AFE_LVDS_SOURCE_T lvds_source, LX_AFE_LVDS_MODE_T lvds_mode);
int afe_kwrap_adc_set_sog_slicer_level(UINT32 sog_lvl);
int afe_kwrap_cvd_set_hstate_max(UINT32 hstate_max_value);
int afe_kwrap_cvd_get_mem_cfg(UINT32* mem_base_comb_buffer, UINT32* mem_size_comb_buffer, UINT32* mem_base_cvd_reg, UINT32* mem_size_cvd_reg);
int afe_kwrap_read_ace_reg(UINT32 addr, UINT32 *data);
int afe_kwrap_write_ace_reg(UINT32 addr, UINT32 data);
int afe_kwrap_cvd_get_crunky_status(UINT32 *ck_vbi_detected, UINT32 *number_of_cs);
int afe_kwrap_set_adc_calibration_mode(BOOLEAN mode);
int afe_kwrap_debugprintctrl(unsigned int printType, unsigned int printColor, unsigned int printEnable);
int afe_kwrap_adc_get_comp_psp_status(UINT32 *pPSP_Detected, UINT32 *pVline_Normal, UINT32 *pVline_Measured, UINT32 *pValid_Signal );
int afe_kwrap_cvd_set_blacklevel(UINT32 black_level);

/* For KADP Debugger */
UINT32 afe_kwrap_adc_testmenu(void);
void	afe_kwrap_adc_debug_test (void);
UINT32 afe_kwrap_cvd_testmenu(void);
void	afe_kwrap_cvd_debug_test (void);
int afe_kwrap_get_ace_fb_status(LX_AFE_SCART_MODE_T *mode);
int afe_kwrap_set_scart_rgb_operation_mode(LX_AFE_SCART_BYPASS_MODE_T scart_rgb_mode);
int afe_kwrap_cvd_atv_channel_change(BOOLEAN bChannel_Change);
int afe_kwrap_cvd_get_noise_status(UINT32 *pCVD_Noise_Status);
int afe_kwrap_cvd_vdac_mute_control(int Enable);
int afe_kwrap_adc_initializemodule(void);
int afe_kwrap_cvd_initializemodule(void);
int afe_kwrap_adc_uninitializemodule(void);
int afe_kwrap_cvd_uninitializemodule(void);
int afe_kwrap_adc_enablemodule(void);
int afe_kwrap_cvd_enablemodule(void);
int afe_kwrap_adc_disablemodule(void);
int afe_kwrap_cvd_disablemodule(void);
int afe_kwrap_cvd_connectmodule(LX_AFE_CVD_SOURCE_ATTRIBUTE_T select_source_attribute, LX_AFE_CVD_INPUT_PORT_T select_cvbs_input_port);
int afe_kwrap_adc_connectmodule(LX_AFE_ADC_INPUT_SOURCE_TYPE_T select_rgb_ypbpr, LX_AFE_ADC_INPUT_PORT_T select_adc_input_port);
int afe_kwrap_cvd_disconnectmodule(void);
int afe_kwrap_adc_disconnectmodule(void);
int afe_kwrap_isopen(void);
int afe_kwrap_adc_get_comp_cp_data(LX_AFE_ADC_COMP_VBI_CP_T *stComp_VBI_CP_Data);
int afe_kwrap_adc_flush_comp_cp_data(void);
int afe_kwrap_get_otp_adc_gain(int index, LX_AFE_ADC_GAIN_VALUE_T *gain_param);
int afe_kwrap_get_otp_adc_offset(int index, LX_AFE_ADC_OFFSET_VALUE_T *offset_param);
int afe_kwrap_set_otp_adc_gainoffset(int index, int write_enable, LX_AFE_ADC_GAIN_VALUE_T *gain_param, LX_AFE_ADC_OFFSET_VALUE_T *offset_param);
int afe_kwrap_set_internal_demod_mode(BOOLEAN internal_mode);
int afe_kwrap_reset_adc_gainoffset(void);
int afe_kwrap_get_otp_adc_gain_offset(LX_AFE_ADC_GAIN_VALUE_T *p_gain_comp, LX_AFE_ADC_OFFSET_VALUE_T *p_offset_comp, LX_AFE_ADC_GAIN_VALUE_T *p_gain_rgb, LX_AFE_ADC_OFFSET_VALUE_T *p_offset_rgb);
int afe_kwrap_set_otp_adc_gain_offset(int write_enable, LX_AFE_ADC_OTP_CAL_VALUE_T *p_adc_otp_gain_offset);
/*------------------------------------------------------------------------------
	Extern Variables
------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

