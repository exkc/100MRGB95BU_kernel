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



/** @file 
 *
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		wonsik.do
 *  @version	1.0 
 *  @date		2012-04-30
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>	/** interrupt */
#include <linux/platform_device.h>
#include <linux/wait.h>		/** wait_event_interrupt_timeout	*/

#include "afe_kapi.h"

#include "sys_regs.h"
//#include "ctop_regs.h"

#include "resolution.h"
#include "adc_module.h"
#include "cvd_module.h"
#include "afe_drv.h"
#include "os_util.h"

#include "adc_hw_m19a0.h"

#ifdef COMP_COPY_PROTECTION
#include "../de/de_cfg_m19.h"
#include "../de/de_vbi_reg_m19.h"
#include "../de/de_ctr_reg_m19.h"
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define INTERLACE_CHECK_COUNT 7

//#define ADC_DETECTION_INTERRUPT_MASK	0x0000068A
//#define ADC_DETECTION_INTERRUPT_MASK	0x00000E8A
#define ADC_AOGC_INTERRUPT_MASK			0x0000C000
//#define ADC_BOUNDARY_COMPENSATION

//#define BEFORE_REVISION
#define VPORT_REG_DIRECT_ACCESS 0
#define L9_RGB_WA_FOR_CLOCK_ADJUST

#ifdef ENHANCED_IFM_SPEED_MODE		// defined in adc_module.h
#define APA_LOOP_COUNT	1	//10
#else
#define APA_LOOP_COUNT	5	//10
#endif

#define M19A_ADC_HW_VERSION 0x18100100
//#define SCART_RGB_13_5MHz_CLK_
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int SYS_IO_WriteRegArray(UINT32 addr, UINT32 size, const void *data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_AFE_PCMODE_MODETABLE_T *gPCTable;
extern int gResolution;
extern LX_AFE_ADC_INPUT_SOURCE_TYPE_T gADC_type;
extern int gPrevious_index;

extern OS_SEM_T	g_ADC_Sema;
extern ADC_SYNC_MODE g_ADC_Sync_Mode ;

extern LX_AFE_ADC_GAIN_VALUE_T user_gain_value;

extern int	g_SCART_RGB_13_5MHz_CLK;

#ifdef M16P_BRINGUP_TODO
//extern DE_DEE_REG_H13_T gDE_DEE_H13;
extern DE_VBI_REG_M16_T gDE_VBI_M16;	// M16 Component CP registers
#endif

extern int _g_ADC_Enable_Htotal_Diff_Check;
#ifdef M16P_BRINGUP_TODO
extern DE_CVC_REG_M16_T gDE_CVC_M16;
#endif

extern int g_adc_hw_revision;
extern int g_comp_vsout_sel;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static UINT32	gADC_APA_Enable = 1;

static int	g_M16_Comp_Double_Sampling = 0;

#ifdef	KDRV_CONFIG_PM
typedef	struct{
	unsigned int gstPmSelPortValue;
	S_EXTAU_VALUE gstPmExtauValue;
	S_RGB_POSITION gstPmPositionValue;
	unsigned int guiPmPhaseValue;
	LX_AFE_ADC_GAIN_VALUE_T gstPmGainValue;
	LX_AFE_ADC_OFFSET_VALUE_T gstPmOffsetValue;
	int giPmIndexValue;
	SINT16 giPmClockValue;
	unsigned int guiPmInterruptStatus;
}S_ADC_PM_DATA;

static S_ADC_PM_DATA *gAdcPMData;

static int gAdcPmInitial = -1;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DECLARE_WAIT_QUEUE_HEAD(agoc_done);
static int giAgocIntDone = 0;

//static int giSelMuxBackup = 0;

//static UINT32	gADC_APA_Delay = 50;
static UINT32	gADC_APA_Delay = 200;	//100;	//200;	//151006 : MSPG-1025P 1-line on/off pattern
static UINT32 	gADC_APA_Same_Count = 1;
static UINT32 	gADC_APA_Enable_Print = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/

int ADC_M19Ax_PowerOn(void)
{
	BMC_REG_M19Ax_RdFL(videoafe_05);
	BMC_REG_M19Ax_Wr01(videoafe_05, llpll_icpcon, 0x7);	// 20uA => 30uA
	BMC_REG_M19Ax_WrFL(videoafe_05);

	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, 1);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, 1);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, 1);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 1);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	//OS_MsecSleep(5);
	OS_UsecDelay(10);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 0);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	return 0;
}
#if 0	// not used
int ADC_M19Ax_PowerOff(void)
{
	// reg_exta_sel , reg_extb_sel
	//gVportRegBx->reg_exta_sel.reg_exta_sel = 0x0;
	//gVportRegBx->reg_exta_sel.reg_extb_sel = 0x0;

	//FIXME juhee - check if removed is ok not to set.
#if 0
	VPORT_RdFL(cvbsafe_pdb_001);
	VPORT_Wr01(cvbsafe_pdb_001, afe3ch_vref_pdb, 0);
	VPORT_WrFL(cvbsafe_pdb_001);
#endif
	BMC_REG_M19Ax_RdFL(videoafe_02);
	BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_biaspdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_02);
	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	//FIXME juhee - what will be the right value??
#if 0
	VPORT_RdFL(top_003);
	VPORT_Wr01(top_003, reg_ch3pll_pdb, 0);
	VPORT_WrFL(top_003);
#endif

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 0);
	BMC_REG_M19Ax_WrFL(videoafe_11);
	BMC_REG_M19Ax_RdFL(videoafe_05);
	BMC_REG_M19Ax_Wr01(videoafe_05, refpll_pdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_05);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 1);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	return 0;

}
#endif

int ADC_M19Ax_RegInit(void)
{
	S_OFFSET_INFORM offset;
	//ADC_PowerOn();

	//H13_BRINGUP 120607 : set initial selmux to ypbpr0
	BMC_REG_M19Ax_RdFL(videoafe_03);
	BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_selmux, 0);
	BMC_REG_M19Ax_WrFL(videoafe_03);

	// Release resets of HS-LVDS block
	ADC_M19Ax_LVDS_Reset_Control(0);

	//gVportRegBx->ch3_cst_002.cst_postcoast = 0x1f;	//Crunky pseudo Sync
	/* release swrst_f24m is move to i2c_coreinit
	ACE_REG_M17C0_RdFL(soft_reset_0);
	//gsoft_reset_0.swrst_pix = 0;
	ACE_REG_M17C0_Wr01(soft_reset_0, swrst_f24m, 0);
	ACE_REG_M17C0_WrFL(soft_reset_0);
	*/

	//powerory 111012 : MSPG_925FS
	ACE_REG_M19Ax_RdFL(adc_dig_22);
	ACE_REG_M19Ax_RdFL(adc_dig_23);
	ACE_REG_M19Ax_Wr01(adc_dig_22, precoast, 0x0D);	//Default Value : 0x0B
	ACE_REG_M19Ax_Wr01(adc_dig_23, postcoast, 0x1D);
	ACE_REG_M19Ax_WrFL(adc_dig_22);
	ACE_REG_M19Ax_WrFL(adc_dig_23);

	//FIXME : Juhee 3DCD is not possible
	ACE_REG_M19Ax_RdFL(adc_dig_113);
	ACE_REG_M19Ax_Wr01(adc_dig_113, size_detect_ctrl, 0x3DCD);
	ACE_REG_M19Ax_WrFL(adc_dig_113);

	// Modified by min 110922 // for L9B0 Bring-Up 110830 by dws
	BMC_REG_M19Ax_RdFL(videoafe_03);
	//BMC_REG_M19Ax_Wr01(afe_3ch_12, afe3ch_icon_buf, 0x2);
	BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_buf, 0x4);		//150421 : M16
	BMC_REG_M19Ax_WrFL(videoafe_03);

	// AFE3CH_CTL_ADD option moved to ADC_M19Ax_SetType
	/*
	ACE_REG_M17C0_RdFL(afe_3ch_7);
	ACE_REG_M17C0_Wr01(afe_3ch_7, afe3ch_ctl_add, 0x93);
	ACE_REG_M17C0_WrFL(afe_3ch_7);
	*/

	//gVportRegBx->ch3_cst_003.cst_hspolover = 0x1; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_vspolover = 0x1; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_hspoluser = 0x0; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_vspoluser = 0x0; // 0825 new value from powerory

	//For no interrupt occurrence when resolution change between master 210(576i) to 209(480i)
	//gVportRegBx->ch3_llpll_010.llpll_lpf_clk_sel = 0x1;
	//110214

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, llpll_lpf_clk_sel, 0);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	ADC_M19Ax_PowerOn();

	// initial rgb, bias pdb down
	ADC_M19Ax_Channel_Power_Control(0,0,0,0);

	//20110125
//	_iow(&gVportRegBx->ch3_digital_003 , 8 , 0 , 0x80);	// ch3reg_hspdeq_thr
	ACE_REG_M19Ax_Wr01(adc_dig_54, hsprdeq_thr, 0xC4);
	ACE_REG_M19Ax_WrFL(adc_dig_54);

	//20110425
	//L9A0 Initial Resettings by powerory

	offset.offset_R = ADC_R_PRE_OFFSET_VALUE;
	offset.offset_G = ADC_G_PRE_OFFSET_VALUE;
	offset.offset_B = ADC_B_PRE_OFFSET_VALUE;

	ADC_M19Ax_SetOffsetRGB( &offset);

	ACE_REG_M19Ax_Wr01(adc_dig_53, hsdiff_thr, 0x0);
	ACE_REG_M19Ax_WrFL(adc_dig_53);

	//110426 by powerory
	ACE_REG_M19Ax_Wr01(adc_dig_222, clamp_init, 0x0F);
	ACE_REG_M19Ax_WrFL(adc_dig_222);

	//110426 by powerory	(Clamp position adjust)
	//gadc_dig_203.blank_sp_0 = 0x80;	// default 0x04;

	//110513 by min
	ACE_REG_M19Ax_Wr01(adc_dig_203, blank_sp, 0x60);	// default 0x04);
	ACE_REG_M19Ax_WrFL(adc_dig_203);

	ACE_REG_M19Ax_RdFL(adc_dig_204);
	ACE_REG_M19Ax_RdFL(adc_dig_209);
	ACE_REG_M19Ax_RdFL(adc_dig_215);
	ACE_REG_M19Ax_Wr01(adc_dig_204, r_blank_mode, 0x1);
	ACE_REG_M19Ax_Wr01(adc_dig_209, g_blank_mode, 0x1);
	ACE_REG_M19Ax_Wr01(adc_dig_215, b_blank_mode, 0x1);
	ACE_REG_M19Ax_WrFL(adc_dig_204);
	ACE_REG_M19Ax_WrFL(adc_dig_209);
	ACE_REG_M19Ax_WrFL(adc_dig_215);

	ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
	ACE_REG_M19Ax_WrFL(adc_dig_220);

	//110720 : changed cst_diff_thr value to 1 for valid coast on 1080i component input of BH-200.
	//Default value '3' is for abnormal vsync pulse of Divico component signal.
	ACE_REG_M19Ax_Wr01(adc_dig_27, cst_diff_thr, 0x1);
	ACE_REG_M19Ax_WrFL(adc_dig_27);

	//110901 : powerory
	ACE_REG_M19Ax_Wr01(adc_dig_255, apa_sampling_counter_max, 0x3);
	ACE_REG_M19Ax_WrFL(adc_dig_255);

	//110901 : powerory
	ACE_REG_M19Ax_Wr01(adc_dig_243, apa_wait_counter_max, 0x10000);
	ACE_REG_M19Ax_WrFL(adc_dig_243);

	//111006 by wonsik : enable ADC auto mute (when LLPLL status is '0'), and disable TPG mute
	ACE_REG_M19Ax_RdFL(adc_dig_230);
	ACE_REG_M19Ax_Wr01(adc_dig_230, mute_ctrl, 0x2);	// Auto Mute
	//gadc_dig_230.mute_ctrl = 0x1;	// Manual Mute
	//gadc_dig_230.mute_ctr; = 0x0;	// Normal Mode
	ACE_REG_M19Ax_WrFL(adc_dig_230);

	// Component  no sync (LLPLL unlock) by bh.min: 131112
	BMC_REG_M19Ax_RdFL(videoafe_01);
//	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
	BMC_REG_M19Ax_WrFL(videoafe_01);

	//For AV&Comp Jack(AV Smearing) M16 Shield On all ports
	ADC_M19Ax_Shield_Control(1);

#ifdef	KDRV_CONFIG_PM
	if(gAdcPmInitial < 0)
	{
		gAdcPMData = (S_ADC_PM_DATA *)kmalloc(sizeof(S_ADC_PM_DATA) , GFP_KERNEL);
		gAdcPMData->giPmIndexValue = -1;
		gAdcPmInitial = 0;
	}
#endif
//	OS_MsecSleep(100);

	AFE_PRINT("ADC REG initialize : version [%x]\n", M19A_ADC_HW_VERSION);

	g_adc_hw_revision = M19A_ADC_HW_VERSION;

	return 0;
}


int ADC_M19Ax_GetBoundaryInform(ST_EXTAU *inform)
{
	ACE_REG_M19Ax_RdFL(adc_dig_183);
	ACE_REG_M19Ax_RdFL(adc_dig_185);
	ACE_REG_M19Ax_RdFL(adc_dig_187);
	ACE_REG_M19Ax_RdFL(adc_dig_189);

	// get extau_up
	ACE_REG_M19Ax_Rd01(adc_dig_183, extau_up_result, inform->extau_up);

	// get extau_down
	ACE_REG_M19Ax_Rd01(adc_dig_185, extau_down_result, inform->extau_down);

	// get extau_left
	ACE_REG_M19Ax_Rd01(adc_dig_187, extau_left_result, inform->extau_left);
#ifdef ADC_BOUNDARY_COMPENSATION
	if(inform->extau_left >= 1)
	{
		inform->extau_left -= 1;
	}
#endif

	// get extau_lest
	ACE_REG_M19Ax_Rd01(adc_dig_189, extau_right_result, inform->extau_right);
#ifdef ADC_BOUNDARY_COMPENSATION
	if(inform->extau_right >= 1)
	{
		inform->extau_right -= 1;
	}
#endif

	return 0;
}

int ADC_M19Ax_SetTAUInform(S_EXTAU_VALUE *value)
{
	UINT32 hsout_tmp;

	// Height
	ACE_REG_M19Ax_RdFL(adc_dig_177);
	ACE_REG_M19Ax_Wr01(adc_dig_177, extau_down_offset, value->height_offset);
	ACE_REG_M19Ax_WrFL(adc_dig_177);

	// WIDTH
	ACE_REG_M19Ax_RdFL(adc_dig_181);
	ACE_REG_M19Ax_Wr01(adc_dig_181, extau_right_offset, value->width_offset);
	ACE_REG_M19Ax_WrFL(adc_dig_181);

	ACE_REG_M19Ax_RdFL(adc_dig_171);
	ACE_REG_M19Ax_Wr01(adc_dig_171, extau_ctrl, value->control);
	ACE_REG_M19Ax_WrFL(adc_dig_171);

	ACE_REG_M19Ax_RdFL(adc_dig_173);
	ACE_REG_M19Ax_Wr01(adc_dig_173, extau_level, value->level);
	ACE_REG_M19Ax_WrFL(adc_dig_173);

	// For Proper Boundary Detection in case of PC RGB Horizontal Sync Crosstalk on RGB Signal, Adjusted left_offset.
	// Enlarge Value to 10 1019 for PC geforce 8400GS
	ACE_REG_M19Ax_RdFL(adc_dig_76);
	//hsout_tmp = ((gadc_dig_75.ro_hsout_width_1 << 8) & 0xF00) + gadc_dig_76.ro_hsout_width_0;
	ACE_REG_M19Ax_Rd01(adc_dig_76, ro_hsout_width, hsout_tmp);
	hsout_tmp += 10;
	ACE_REG_M19Ax_Wr01(adc_dig_179, extau_left_offset, hsout_tmp );
	ACE_REG_M19Ax_WrFL(adc_dig_179);

	return 0;
}

int ADC_M19Ax_SetRGBPosition(S_RGB_POSITION *pos)
{
	ACE_REG_M19Ax_RdFL(adc_dig_131);
	ACE_REG_M19Ax_Wr01(adc_dig_131, ap_xpos_b, pos->width_b);
	ACE_REG_M19Ax_WrFL(adc_dig_131);

	ACE_REG_M19Ax_RdFL(adc_dig_123);
	ACE_REG_M19Ax_Wr01(adc_dig_123, ap_xpos_g, pos->width_g);
	ACE_REG_M19Ax_WrFL(adc_dig_123);

	ACE_REG_M19Ax_RdFL(adc_dig_139);
	ACE_REG_M19Ax_Wr01(adc_dig_139, ap_xpos_r, pos->width_r);
	ACE_REG_M19Ax_WrFL(adc_dig_139);

	ACE_REG_M19Ax_RdFL(adc_dig_135);
	ACE_REG_M19Ax_Wr01(adc_dig_135, ap_ypos_b, pos->height_b);
	ACE_REG_M19Ax_WrFL(adc_dig_135);

	ACE_REG_M19Ax_RdFL(adc_dig_127);
	ACE_REG_M19Ax_Wr01(adc_dig_127, ap_ypos_g, pos->height_g);
	ACE_REG_M19Ax_WrFL(adc_dig_127);

	ACE_REG_M19Ax_RdFL(adc_dig_143);
	ACE_REG_M19Ax_Wr01(adc_dig_143, ap_ypos_r, pos->height_r);
	ACE_REG_M19Ax_WrFL(adc_dig_143);

	return 0;
}

int ADC_M19Ax_GetRGBResult(S_RGB_OUT *result)
{
	ACE_REG_M19Ax_RdFL(adc_dig_149);
	ACE_REG_M19Ax_Rd01(adc_dig_149, ap_out_b, result->out_b);

	ACE_REG_M19Ax_RdFL(adc_dig_153);
	ACE_REG_M19Ax_Rd01(adc_dig_153, ap_out_g, result->out_g);

	ACE_REG_M19Ax_RdFL(adc_dig_157);
	ACE_REG_M19Ax_Rd01(adc_dig_157, ap_out_r, result->out_r);

	return 0;
}

int ADC_M19Ax_GetRGBPosition(S_RGB_POSITION *pos)
{
	ACE_REG_M19Ax_RdFL(adc_dig_131);
	ACE_REG_M19Ax_Rd01(adc_dig_131, ap_xpos_b, pos->width_b);

	ACE_REG_M19Ax_RdFL(adc_dig_123);
	ACE_REG_M19Ax_Rd01(adc_dig_123, ap_xpos_g, pos->width_g);

	ACE_REG_M19Ax_RdFL(adc_dig_139);
	ACE_REG_M19Ax_Rd01(adc_dig_139, ap_xpos_r, pos->width_r);

	ACE_REG_M19Ax_RdFL(adc_dig_135);
	ACE_REG_M19Ax_Rd01(adc_dig_135, ap_ypos_b, pos->height_b);

	ACE_REG_M19Ax_RdFL(adc_dig_127);
	ACE_REG_M19Ax_Rd01(adc_dig_127, ap_ypos_g, pos->height_g);

	ACE_REG_M19Ax_RdFL(adc_dig_143);
	ACE_REG_M19Ax_Rd01(adc_dig_143, ap_ypos_r, pos->height_r);

	return 0;
}

int ADC_M19Ax_SetRGBSize(S_RGB_SIZE *size)
{
	ACE_REG_M19Ax_RdFL(adc_dig_133);
	ACE_REG_M19Ax_Wr01(adc_dig_133, ap_xsize_b, size->width_b);
	ACE_REG_M19Ax_WrFL(adc_dig_133);

	ACE_REG_M19Ax_RdFL(adc_dig_125);
	ACE_REG_M19Ax_Wr01(adc_dig_125, ap_xsize_g, size->width_g);
	ACE_REG_M19Ax_WrFL(adc_dig_125);

	ACE_REG_M19Ax_RdFL(adc_dig_141);
	ACE_REG_M19Ax_Wr01(adc_dig_141, ap_xsize_r, size->width_r);
	ACE_REG_M19Ax_WrFL(adc_dig_141);

	ACE_REG_M19Ax_RdFL(adc_dig_137);
	ACE_REG_M19Ax_Wr01(adc_dig_137, ap_ysize_b, size->height_b);
	ACE_REG_M19Ax_WrFL(adc_dig_137);

	ACE_REG_M19Ax_RdFL(adc_dig_129);
	ACE_REG_M19Ax_Wr01(adc_dig_129, ap_ysize_g, size->height_g);
	ACE_REG_M19Ax_WrFL(adc_dig_129);

	ACE_REG_M19Ax_RdFL(adc_dig_145);
	ACE_REG_M19Ax_Wr01(adc_dig_145, ap_ysize_r, size->height_r);
	ACE_REG_M19Ax_WrFL(adc_dig_145);

	return 0;
}

int ADC_M19Ax_GetSizeValue(S_VIDEO_SIZE_INFORM *size)
{
	UINT32 vspol = 0;
	UINT32 hspol = 0;

	ACE_REG_M19Ax_RdFL(adc_dig_115);
	ACE_REG_M19Ax_Rd01(adc_dig_115, sd_ext_vsize, size->ext_vsize);

	ACE_REG_M19Ax_RdFL(adc_dig_118);
	ACE_REG_M19Ax_Rd01(adc_dig_118, sd_vd_vsize, size->vd_vsize);

	ACE_REG_M19Ax_RdFL(adc_dig_120);
	ACE_REG_M19Ax_Rd01(adc_dig_120, sd_vd_hsize, size->vd_hsize);

	ACE_REG_M19Ax_RdFL(adc_dig_29);

	ACE_REG_M19Ax_Rd02(adc_dig_29, ro_hspol, hspol, ro_vspol, vspol);
	//size->polarity = (gadc_dig_29.ro_hspol<<1) | (gadc_dig_29.ro_vspol);
	size->polarity = (hspol<<1) | (vspol);

	//111020 for composite sync support
#if 0
	if( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_34);
		ACE_REG_M19Ax_RdFL(adc_dig_35);
		out16 =  (gadc_dig_34.ro_vsprdref_1)&0x1F;
		out32 = out16 << 8;
		ACE_REG_M19Ax_Rd01(adc_dig_35, ro_vsprdref_0, out16);
		out32 |= out16;

		if(out32 < 100)
		{
			AFE_PRINT("VTotal [%d]\n", out32);
			ACE_REG_M19Ax_RdFL(adc_dig_22);
			ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
			ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x1);
			ACE_REG_M19Ax_WrFL(adc_dig_22);
		}
		else
		{
			ACE_REG_M19Ax_RdFL(adc_dig_22);
			ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
			ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x0);
			ACE_REG_M19Ax_WrFL(adc_dig_22);
		}
		//if(gadc_dig_29.ro_interlaced)
		//{
		//	AFE_PRINT("RGB Interlaced mode\n");
		//	ACE_REG_M19Ax_RdFL(adc_dig_22);
		//	gadc_dig_22.compover = 0x1;
		//	gadc_dig_22.compuser = 0x1;
		//	ACE_REG_M19Ax_WrFL(adc_dig_22);
		//}
		//else
		//{
		//	ACE_REG_M19Ax_RdFL(adc_dig_22);
		//	gadc_dig_22.compover = 0x1;
		//	gadc_dig_22.compuser = 0x0;
		//	ACE_REG_M19Ax_WrFL(adc_dig_22);
		//}
	}
#endif

	return 0;
}

int ADC_M19Ax_SetPort(unsigned int sel_port)
{

#ifdef	KDRV_CONFIG_PM
	memcpy((void *)&gAdcPMData->gstPmSelPortValue , (void *)&sel_port , sizeof(unsigned int));
#endif
	//AFE_PRINT("ADC_SetPort \n");

	AFE_PRINT("ADC_SetPort : sel_port = [%d] \n", sel_port);

	BMC_REG_M19Ax_RdFL(videoafe_03);
	BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_selmux, sel_port);
	BMC_REG_M19Ax_WrFL(videoafe_03);

	if(sel_port == 0)
		ADC_M19Ax_Shield_Control(0);
	else
		ADC_M19Ax_Shield_Control(1);

	/*
	ACE_REG_M19Ax_RdFL(adc_dig_22);
	ACE_REG_M19Ax_Wr01(adc_dig_22, compover, sel_port->compover);
	ACE_REG_M19Ax_Wr01(adc_dig_22, compover, sel_port->compuser);
	ACE_REG_M19Ax_WrFL(adc_dig_22);
	*/

	return 0;
}

int ADC_M19Ax_GetSelectedPort(void)
{
	int ret;
	BMC_REG_M19Ax_RdFL(videoafe_03);
	BMC_REG_M19Ax_Rd01(videoafe_03, videoafe_selmux, ret);

	return	ret;
}

unsigned int ADC_M19Ax_GetPhaseValue(void)
{
	UINT32 ret = 0;

	ACE_REG_M19Ax_RdFL(m19_llpll_shift);
	ACE_REG_M19Ax_Rd01(m19_llpll_shift, llpll_shift, ret);

	return ret;
}

int ADC_M19Ax_SetPhaseValue(unsigned int phase)
{
//	AFE_PRINT("######### Set ADC Phase Register to [%d][0x%x]\n", phase,phase );
	ADC_DEBUG("%s entered with value [0x%x]\n", __func__, phase);

	ACE_REG_M19Ax_Wr01(m19_llpll_shift, llpll_shift, phase);
	ACE_REG_M19Ax_WrFL(m19_llpll_shift);

	return 0;
}

unsigned int ADC_M19Ax_GetScanType(void)
{
	unsigned int ret = 0, tmp = 0;
	UINT8	count=0;

	for(;count<INTERLACE_CHECK_COUNT;count++)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_29);

		ACE_REG_M19Ax_Rd01(adc_dig_29, ro_interlaced, tmp);
		ret += tmp^1;
	}

//	AFE_PRINT("* Interlace check count value = [%d]\n", ret);

	if(ret > (INTERLACE_CHECK_COUNT/2))
		return 1;
	else
		return 0;

}


int ADC_M19Ax_SetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain)
{
	int ret = 0;
	int call_from_hal = 0;
	LX_AFE_ADC_GAIN_VALUE_T modGain;

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, stGain->R_Gain_Value, stGain->G_Gain_Value, stGain->B_Gain_Value);

	if ( ( stGain->G_Gain_Value & 0x8000) == 0x8000 )
	{
		ADC_DEBUG("%s call from HAL_VFE_ADC_SetCALData\n", __func__);
		call_from_hal = 1;
		stGain->G_Gain_Value &= 0x7FFF;
		//111123 wonsik.do
		user_gain_value.R_Gain_Value = stGain->R_Gain_Value;
		user_gain_value.G_Gain_Value = stGain->G_Gain_Value;
		user_gain_value.B_Gain_Value = stGain->B_Gain_Value;

		ADC_M19Ax_AdcGainCompensator(stGain, &modGain);
	}
	else
	{
		modGain.R_Gain_Value = stGain->R_Gain_Value;
		modGain.G_Gain_Value = stGain->G_Gain_Value;
		modGain.B_Gain_Value = stGain->B_Gain_Value;
	}

	if ( (modGain.R_Gain_Value > 0x3FFF) || (modGain.G_Gain_Value > 0x3FFF) || (modGain.B_Gain_Value > 0x3FFF) )
		return -1;

	ACE_REG_M19Ax_Wr01(adc_dig_01, r_pre_gain, modGain.R_Gain_Value );
	ACE_REG_M19Ax_Wr01(adc_dig_03, g_pre_gain, modGain.G_Gain_Value );
	ACE_REG_M19Ax_Wr01(adc_dig_05, b_pre_gain, modGain.B_Gain_Value );

	ACE_REG_M19Ax_WrFL(adc_dig_01);
	ACE_REG_M19Ax_WrFL(adc_dig_03);
	ACE_REG_M19Ax_WrFL(adc_dig_05);

	return ret;
}

int ADC_M19Ax_GetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain)
{
	int ret = 0;

	ACE_REG_M19Ax_RdFL(adc_dig_01);
	ACE_REG_M19Ax_RdFL(adc_dig_03);
	ACE_REG_M19Ax_RdFL(adc_dig_05);
	ACE_REG_M19Ax_Rd01(adc_dig_01, r_pre_gain, stGain->R_Gain_Value);
	ACE_REG_M19Ax_Rd01(adc_dig_03, g_pre_gain, stGain->G_Gain_Value);
	ACE_REG_M19Ax_Rd01(adc_dig_05, b_pre_gain, stGain->B_Gain_Value);
	/*
	stGain->R_Gain_Value = gadc_dig_0.r_pre_gain_1 << 8 | gadc_dig_1.r_pre_gain_0;
	stGain->G_Gain_Value = gadc_dig_2.g_pre_gain_1 << 8 | gadc_dig_3.g_pre_gain_0;
	stGain->B_Gain_Value = gadc_dig_4.b_pre_gain_1 << 8 | gadc_dig_5.b_pre_gain_0;
	*/

	return ret;
}


int ADC_M19Ax_SetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset)
{
	int ret = 0;

	if ( (stOffset->R_Offset_Value > 0x1FFF) || (stOffset->G_Offset_Value > 0x1FFF) || (stOffset->B_Offset_Value > 0x1FFF) )
		return -1;

	ACE_REG_M19Ax_Wr01(adc_dig_225, r_pre_offset, stOffset->R_Offset_Value );
	ACE_REG_M19Ax_WrFL(adc_dig_225);

	ACE_REG_M19Ax_Wr01(adc_dig_227, g_pre_offset, stOffset->G_Offset_Value );
	ACE_REG_M19Ax_WrFL(adc_dig_227);

	ACE_REG_M19Ax_Wr01(adc_dig_229, b_pre_offset, stOffset->B_Offset_Value );
	ACE_REG_M19Ax_WrFL(adc_dig_229);


	return ret;
}

int ADC_M19Ax_GetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset)
{
	int ret = 0;

	ACE_REG_M19Ax_RdFL(adc_dig_225);
	ACE_REG_M19Ax_RdFL(adc_dig_227);
	ACE_REG_M19Ax_RdFL(adc_dig_229);
	ACE_REG_M19Ax_Rd01(adc_dig_225, r_pre_offset, stOffset->R_Offset_Value);
	ACE_REG_M19Ax_Rd01(adc_dig_227, g_pre_offset, stOffset->G_Offset_Value);
	ACE_REG_M19Ax_Rd01(adc_dig_229, b_pre_offset, stOffset->B_Offset_Value);
	/*
	stOffset->R_Offset_Value = gadc_dig_224.r_pre_offset_1 << 8 | gadc_dig_225.r_pre_offset_0;
	stOffset->G_Offset_Value = gadc_dig_226.g_pre_offset_1 << 8 | gadc_dig_227.g_pre_offset_0;
	stOffset->B_Offset_Value = gadc_dig_228.b_pre_offset_1 << 8 | gadc_dig_229.b_pre_offset_0;
	*/

	return ret;
}


/**
 *
 * setting the LLPLL by index value which came from ADC_IFM_SearchTable
 *
 * @param	S_VIDEO_SIZE_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_M19Ax_SetInputVideo(int iIndex)
{

//	int i;
	UINT32 hsout_width =0;
	//UINT8	llpll_filter_status;

	int ret = 0;

#ifdef	KDRV_CONFIG_PM
	gAdcPMData->giPmIndexValue = iIndex;
#endif
	ADC_DEBUG("%s entered with value [%d]\n", __func__, iIndex);

	ACE_REG_M19Ax_RdFL(adc_dig_74);

	//For SCART RGB, Do not inverted field.
//	if((iIndex == 306)&& (gADC_type == LX_ADC_INPUT_SOURCE_YPBPR))// for Component 576i 50Hz field indication should be inverted
	// in case of input source change from scart RGB to component with same resolution fld_inv bit can't not be set.
	// inv_inv bit has no effect on SCART RGB input.
	if((iIndex == 306))
	{
		ACE_REG_M19Ax_Wr01(adc_dig_74, fld_inv, 0x1);
	}
	else
	{
		ACE_REG_M19Ax_Wr01(adc_dig_74, fld_inv, 0x0);
	}

	ACE_REG_M19Ax_WrFL(adc_dig_74);

	hsout_width = HS_Out_Width[iIndex];

	//From L9B0 revisioin minimum hsync width is reduced to '4'
	if(hsout_width < 4)
		hsout_width = 4;

	ADC_DEBUG("Hsout_width = [%d]\n", hsout_width);

	ACE_REG_M19Ax_RdFL(adc_dig_60);

	if(g_M16_Comp_Double_Sampling > 0)
	{
		if( ( (iIndex == 303) || (iIndex == 306)) &&(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR) && ( g_SCART_RGB_13_5MHz_CLK ))// component 480i / 576i
			hsout_width *= 2;
		else if( ( (iIndex == 303) || (iIndex == 306))  && ( g_SCART_RGB_13_5MHz_CLK == 0 ))// component 480i / 576i
			hsout_width *= 2;
	}

	ACE_REG_M19Ax_Wr01(adc_dig_60, hsout_width, hsout_width );

	ACE_REG_M19Ax_WrFL(adc_dig_60);

	if(g_M16_Comp_Double_Sampling > 0)
	{
		if( ( (iIndex == 303) &&(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR) &&( g_SCART_RGB_13_5MHz_CLK) ) ||	// component 480i
				( (iIndex == 303) &&( g_SCART_RGB_13_5MHz_CLK == 0) ) )
		{
			iIndex = 304;	// Use 480P timing
			ADC_DEBUG("for Component 480i, enable subsampling\n");

			ACE_REG_M19Ax_RdFL(adc_dig_223);
			ACE_REG_M19Ax_Wr01(adc_dig_223, sub_sampling_en, 0x1);
			ACE_REG_M19Ax_WrFL(adc_dig_223);
		}
		else if( ( (iIndex == 306) &&(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR) &&( g_SCART_RGB_13_5MHz_CLK) ) ||	// component 576i
				( (iIndex == 306) &&( g_SCART_RGB_13_5MHz_CLK == 0) ) )
		{
			iIndex = 307;	// Use 576P timing
			ADC_DEBUG("for Component 576i, enable subsampling\n");

			ACE_REG_M19Ax_RdFL(adc_dig_223);
			ACE_REG_M19Ax_Wr01(adc_dig_223, sub_sampling_en, 0x1);
			ACE_REG_M19Ax_WrFL(adc_dig_223);
		}
		else
		{
			ACE_REG_M19Ax_RdFL(adc_dig_223);
			ACE_REG_M19Ax_Wr01(adc_dig_223, sub_sampling_en, 0x0);
			ACE_REG_M19Ax_WrFL(adc_dig_223);
		}
	}

	//CH3_LLPLL_003
	BMC_REG_M19Ax_RdFL(videoafe_05);
	BMC_REG_M19Ax_Wr01(videoafe_05, llpll_div_max, (LLPLL_div_max[iIndex])&0x1F);
	BMC_REG_M19Ax_WrFL(videoafe_05);

	//LLPLL_counter_max
	BMC_REG_M19Ax_RdFL(videoafe_10);
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_counter_max, LLPLL_counter_max[iIndex] & 0xFFF );
	BMC_REG_M19Ax_WrFL(videoafe_10);

	//LLPLL_shift 일단 0으로 초기화

	ACE_REG_M19Ax_Wr01(m19_llpll_shift, llpll_shift, 0);
	ACE_REG_M19Ax_WrFL(m19_llpll_shift);

	//LLPLL_dco_max
	BMC_REG_M19Ax_RdFL(videoafe_10);
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_dco_max, (LLPLL_dco_max[iIndex])&0x1F);
	//LLPLL_dco_min
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_dco_min, (LLPLL_dco_min_M16[iIndex])&0x1F);
	//LLPLL_coarse_scale
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_coarse_scale, (LLPLL_coarse_scale[iIndex])&0xF);
	BMC_REG_M19Ax_WrFL(videoafe_10);

	//LLPLL_g1_nom
	BMC_REG_M19Ax_RdFL(videoafe_09);
	BMC_REG_M19Ax_Wr01(videoafe_09, llpll_g1_nom, (LLPLL_g1_nom[iIndex])&0x1F);
	//LLPLL_g2_nom
	BMC_REG_M19Ax_Wr01(videoafe_09, llpll_g2_nom, (LLPLL_g2_nom[iIndex])&0x1F);
	//LLPLL_g3_p_nom
	BMC_REG_M19Ax_Wr01(videoafe_09, llpll_g3_p_nom, (LLPLL_g3_p_nom[iIndex])&0x1F);
	//LLPLL_g3_n_nom
	BMC_REG_M19Ax_Wr01(videoafe_09, llpll_g3_n_nom, (LLPLL_g3_n_nom[iIndex])&0x1F);
	BMC_REG_M19Ax_WrFL(videoafe_09);

	//LLPLL_g1_fine
	BMC_REG_M19Ax_RdFL(videoafe_08);
	BMC_REG_M19Ax_Wr01(videoafe_08, llpll_g1_fine, (LLPLL_g1_fine[iIndex])&0x1F);
	//LLPLL_g2_fine
	BMC_REG_M19Ax_Wr01(videoafe_08, llpll_g2_fine, (LLPLL_g2_fine[iIndex])&0x1F);
	//LLPLL_g3_p_fine
	BMC_REG_M19Ax_Wr01(videoafe_08, llpll_g3_p_fine, (LLPLL_g3_p_fine[iIndex])&0x1F);
	//LLPLL_g3_n_fine
	BMC_REG_M19Ax_Wr01(videoafe_08, llpll_g3_n_fine, (LLPLL_g3_n_fine[iIndex])&0x1F);
	BMC_REG_M19Ax_WrFL(videoafe_08);

	/*
	for( i = 0 ; i < 30 ; i++)
	{
		BMC_REG_M19Ax_RdFL(videoafe_07);
		BMC_REG_M19Ax_Rd01(videoafe_07, llpll_filter_status, llpll_filter_status);
		if(llpll_filter_status == 3) break;
		OS_MsecSleep(5);
	}
	if(i==30)
	{
		AFE_PRINT("!!!!!!!!!!!! LLPLL UNLOCK !!!!!!!!!!!!!!!!!\n");
		ADC_Reset_LLPLL();
		ret = -1;
	}
	*/



	ACE_REG_M19Ax_RdFL(adc_dig_204);
	ACE_REG_M19Ax_RdFL(adc_dig_209);
	ACE_REG_M19Ax_RdFL(adc_dig_214);

	ACE_REG_M19Ax_Wr01(adc_dig_204, r_blank_num_clear, 1);
	ACE_REG_M19Ax_Wr01(adc_dig_209, g_blank_num_clear, 1);
	ACE_REG_M19Ax_Wr01(adc_dig_214, b_blank_num_clear, 1);

	ACE_REG_M19Ax_WrFL(adc_dig_204);
	ACE_REG_M19Ax_WrFL(adc_dig_209);
	ACE_REG_M19Ax_WrFL(adc_dig_214);

	ACE_REG_M19Ax_Wr01(adc_dig_204, r_blank_num_clear, 0);
	ACE_REG_M19Ax_Wr01(adc_dig_209, g_blank_num_clear, 0);
	ACE_REG_M19Ax_Wr01(adc_dig_214, b_blank_num_clear, 0);

	ACE_REG_M19Ax_WrFL(adc_dig_204);
	ACE_REG_M19Ax_WrFL(adc_dig_209);
	ACE_REG_M19Ax_WrFL(adc_dig_214);

	/*
	if(i<100)
		return 0;
	else
		return -1;
		*/

	return ret;
}

int ADC_M19Ax_Check_LLPLL_status(void)
{
	int i;
	int ret = 0;
	UINT32 filter_status;

	//ADC_DEBUG("%s entered \n", __func__);

	for( i = 0 ; i < 30 ; i++)
	{
		BMC_REG_M19Ax_RdFL(videoafe_07);
		BMC_REG_M19Ax_Rd01(videoafe_07, llpll_filter_status, filter_status);
		if(filter_status == 3) break;
		OS_MsecSleep(5);
	}
	if(i==30)
	{
		AFE_ERROR("!!!!!!!!!!!! LLPLL UNLOCK !!!!!!!!!!!!!!!!!\n");
		ADC_Reset_LLPLL();
		ret = -1;
	}

	return ret;
}

int ADC_M19Ax_AGOCInit(void)
{
	ST_GAIN_INFORM *gain_temp;

	ADC_CALIB_DEBUG("%s entered \n", __func__);

	gain_temp = (ST_GAIN_INFORM *)kmalloc(sizeof(ST_GAIN_INFORM),GFP_KERNEL);

	//111123 wonsik.do
	ACE_REG_M19Ax_RdFL(adc_dig_89);
	ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_src_sel, 0x0);
	ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_enable_sel, 0x0);
	ACE_REG_M19Ax_WrFL(adc_dig_89);

	// aogc conter set as max
	ACE_REG_M19Ax_RdFL(adc_dig_100);
	ACE_REG_M19Ax_Wr01(adc_dig_100, aogc_counter_max, 0xFFFE);
	ACE_REG_M19Ax_WrFL(adc_dig_100);

	ACE_REG_M19Ax_RdFL(adc_dig_98);
	ACE_REG_M19Ax_Wr01(adc_dig_98, aogc_sample_count, 0x6);
	ACE_REG_M19Ax_WrFL(adc_dig_98);

	//110504 by powerory
	ACE_REG_M19Ax_RdFL(adc_dig_97);
	ACE_REG_M19Ax_Wr01(adc_dig_97, aogc_th, 0x03FF);
	ACE_REG_M19Ax_WrFL(adc_dig_97);

	//Add From B0 Revision(Auto Calibration)
	ACE_REG_M19Ax_RdFL(adc_dig_98);
	ACE_REG_M19Ax_Wr01(adc_dig_98, aogc_sample_accum, 0);
	ACE_REG_M19Ax_WrFL(adc_dig_98);

#if 0
	// removed from B0
	// aoc, agc sel register
	gVportRegBx->ch3reg_agc_ire.ch3reg_agc_ire = 3;
	gVportRegBx->ch3reg_agc_ire.ch3reg_aoc_ire = 4;
#endif
//	gVportRegBx->ch3_adc_007.afe3ch_ire_sel = 4;

	//TODO :dws
	// First set gain value to default
	gain_temp->gain_R = 0x1000;
	gain_temp->gain_G = 0x1000;
	gain_temp->gain_B = 0x1000;

	ADC_SetGainRGB(gain_temp);

	return 0;
}

/**
 *
 * setting ADC IRE test enable/disable
 *
 * @param	0 : inactive , 1 : active
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_M19Ax_SetIRETestMode(int sel , E_AGC_IRE mode)
{
	int ret = 0;


	if(sel)	// IRE Test mode inactive
	{
		BMC_REG_M19Ax_RdFL(videoafe_02);
		BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_ire_test, 1);
		BMC_REG_M19Ax_WrFL(videoafe_02);
		//by dws 110520 : ADC_AGOCInit is already executed before.
		//ADC_AGOCInit();

		//ACE_REG_M17C0_RdFL(afe_3ch_0);
		//ACE_REG_M17C0_Rd01(afe_3ch_0, videoafe_selmux, giSelMuxBackup);

		// aogc test start
		ACE_REG_M19Ax_RdFL(adc_dig_89);
		ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_enable, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_89);

		// 110503 by powerory
		// 111103 by wonsik.do : digital reset still needed on L9B0 ???
		// H13_BRINGUP : for accurate adc result , digital reset still needed
		ADC_M19Ax_Reset_Digital();

		// H13_BRINGUP : Removed 20mse delay : 20120612
//			OS_MsecSleep(20);
	}
	else	// IRE Test mode active
	{
		//ACE_REG_M17C0_RdFL(afe_3ch_0);
		//gafe_3ch_0.videoafe_selmux = giSelMuxBackup;
		//ACE_REG_M17C0_WrFL(afe_3ch_0);

		// aogc test stop
		ACE_REG_M19Ax_RdFL(adc_dig_89);
		ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_enable, 0);
		ACE_REG_M19Ax_WrFL(adc_dig_89);

		BMC_REG_M19Ax_RdFL(videoafe_02);
		BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_ire_test, 0);
		BMC_REG_M19Ax_WrFL(videoafe_02);
	}
	return ret;
}

/**
 *
 * get RGB average value from register
 *
 * @param	ST_GAIN_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/

int ADC_M19Ax_GetIRELevel( S_GAIN_TARGET *gain)
{
	int ret = 0;
	unsigned int temp_r, temp_g,temp_b;

	ACE_REG_M19Ax_RdFL(adc_dig_104);
	ACE_REG_M19Ax_Rd01(adc_dig_104, ro_avg_r, temp_r);

	ACE_REG_M19Ax_RdFL(adc_dig_107);
	ACE_REG_M19Ax_Rd01(adc_dig_107, ro_avg_g, temp_g);

	ACE_REG_M19Ax_RdFL(adc_dig_110);
	ACE_REG_M19Ax_Rd01(adc_dig_110, ro_avg_b, temp_b);


// powerory 2010-12-10
	//gain->gain_R = (float)( (temp_r&0xffff00) >> 8) + (float)(temp_r&0xff)/256.0;
	//gain->gain_G = (float)( (temp_g&0xffff00) >> 8) + (float)(temp_g&0xff)/256.0;
	//gain->gain_B = (float)( (temp_b&0xffff00) >> 8) + (float)(temp_b&0xff)/256.0;
//~powerory

	//120103 wonsik.do : removed floating point in kernel driver
//	gain->gain_R = (float)( (temp_r&0xffc000) >> 14) + (float)(temp_r&0x3fff)/16384.0;
//	gain->gain_G = (float)( (temp_g&0xffc000) >> 14) + (float)(temp_g&0x3fff)/16384.0;
//	gain->gain_B = (float)( (temp_b&0xffc000) >> 14) + (float)(temp_b&0x3fff)/16384.0;
	gain->gain_R = temp_r;
	gain->gain_G = temp_g;
	gain->gain_B = temp_b;
	//by dws
	//gain->gain_R = (float)( (temp_r&0xffe000) >> 13) + (float)(temp_r&0x1fff)/8192.0;
	//gain->gain_G = (float)( (temp_g&0xffe000) >> 13) + (float)(temp_g&0x1fff)/8192.0;
	//gain->gain_B = (float)( (temp_b&0xffe000) >> 13) + (float)(temp_b&0x1fff)/8192.0;


	ADC_DEBUG("IRE level 1 : R[%d] , G[%d] , B[%d] \n",(int)gain->gain_R, (int)gain->gain_G , (int)gain->gain_B );

	return ret;

}


/**
 *
 * set IRE value for R,G,B
 *
 * @param	S_VIDEO_SIZE_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_M19Ax_SetIRELevel(E_AGC_IRE ire , S_GAIN_TARGET *gain)
{
	int ret = 0;
	unsigned short target_ire;
	int wait_count = 0;


	switch(ire)
	{
		case 	IRE0:
		case	IRE0_RGB:
		case	IRE0_COMP:
			target_ire = 0;
		break;
		case 	IRE73:		//1
			target_ire = 73;
			ire = IRE73_L9;		//0
		break;
		case 	IRE950:		//2
			target_ire = 950;
			ire = IRE950_L9;	//3
		break;
		case 	IRE1023:
			target_ire = 1023;
		break;

		default:
			target_ire = 0;
			AFE_ERROR("WARNING : Invalid E_AGC_IRE type\n");
		break;
	}

	// set IRE
	//gVportRegBx->ch3_adc_007.ch3reg_adc_ire_sel_man = ire;
	BMC_REG_M19Ax_RdFL(videoafe_02);
	BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_ire_sel, ire);
	BMC_REG_M19Ax_WrFL(videoafe_02);

//	ADC_DEBUG("IRE level set %d\n",ire);

	// set target value
	if(ire == IRE0_COMP){
		ACE_REG_M19Ax_Wr01(adc_dig_91, r_compare, (512));
		ACE_REG_M19Ax_WrFL(adc_dig_91);

		ACE_REG_M19Ax_Wr01(adc_dig_93, g_compare, (target_ire));
		ACE_REG_M19Ax_WrFL(adc_dig_93);

		ACE_REG_M19Ax_Wr01(adc_dig_95, b_compare, (512));
		ACE_REG_M19Ax_WrFL(adc_dig_95);
	}
	else
	{
		ACE_REG_M19Ax_Wr01(adc_dig_91, r_compare, ((target_ire)&0x3FF));
		ACE_REG_M19Ax_WrFL(adc_dig_91);

		ACE_REG_M19Ax_Wr01(adc_dig_93, g_compare, ((target_ire)&0x3FF));
		ACE_REG_M19Ax_WrFL(adc_dig_93);

		ACE_REG_M19Ax_Wr01(adc_dig_95, b_compare, ((target_ire)&0x3FF));
		ACE_REG_M19Ax_WrFL(adc_dig_95);
	}

	giAgocIntDone = 0;		// prevent invoking the interrupt before on time
	ADC_SetIRETestMode(1 , ire);
//	OS_MsecSleep(500);

#if 0
	wait_event_interruptible_timeout(agoc_done , giAgocIntDone != 0 , msecs_to_jiffies(300) );

	giAgocIntDone = 0;
#else
	for(;wait_count < 50; wait_count++)
	{
		OS_MsecSleep(10);
		if(ADC_M19Ax_Read_AGOC_State() == 0)
			break;
		ADC_CALIB_DEBUG("AGOC State Check loop [%d]\n", wait_count);
	}
	if(wait_count == 50)
		AFE_ERROR("@@@@@ AGOC NOT COMPLETED !!! @@@@@\n");

#endif

	ADC_M19Ax_GetIRELevel(gain);
	ADC_SetIRETestMode(0 , ire);
	return ret;
}

int ADC_M19Ax_SetAgocWakeup(void)
{

	giAgocIntDone = 1;
	wake_up_interruptible(&agoc_done);

	return 0;
}

int ADC_M19Ax_GetGainRGB( ST_GAIN_INFORM *gain)
{

	ACE_REG_M19Ax_RdFL(adc_dig_01);
	ACE_REG_M19Ax_RdFL(adc_dig_03);
	ACE_REG_M19Ax_RdFL(adc_dig_05);
	ACE_REG_M19Ax_Rd01(adc_dig_01, r_pre_gain, gain->gain_R);
	ACE_REG_M19Ax_Rd01(adc_dig_03, g_pre_gain, gain->gain_G);
	ACE_REG_M19Ax_Rd01(adc_dig_05, b_pre_gain, gain->gain_B);
	/*
	gain->gain_R = gadc_dig_0.r_pre_gain_1 << 8 | gadc_dig_1.r_pre_gain_0;
	gain->gain_G = gadc_dig_2.g_pre_gain_1 << 8 | gadc_dig_3.g_pre_gain_0;
	gain->gain_B = gadc_dig_4.b_pre_gain_1 << 8 | gadc_dig_5.b_pre_gain_0;
	*/

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, gain->gain_R, gain->gain_G, gain->gain_B);

	return 0;
}

int ADC_M19Ax_SetGainRGB( ST_GAIN_INFORM *gain)
{
	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, gain->gain_R, gain->gain_G, gain->gain_B);

	ACE_REG_M19Ax_Wr01(adc_dig_01, r_pre_gain, (gain->gain_R ) & 0x3FFF);
	ACE_REG_M19Ax_Wr01(adc_dig_03, g_pre_gain, (gain->gain_G ) & 0x3FFF);
	ACE_REG_M19Ax_Wr01(adc_dig_05, b_pre_gain, (gain->gain_B ) & 0x3FFF);

	ACE_REG_M19Ax_WrFL(adc_dig_01);
	ACE_REG_M19Ax_WrFL(adc_dig_03);
	ACE_REG_M19Ax_WrFL(adc_dig_05);

	return 0;
}


int ADC_M19Ax_GetOffsetRGB( S_OFFSET_INFORM *offset)
{

	ACE_REG_M19Ax_RdFL(adc_dig_225);
	ACE_REG_M19Ax_RdFL(adc_dig_227);
	ACE_REG_M19Ax_RdFL(adc_dig_229);
	ACE_REG_M19Ax_Rd01(adc_dig_225, r_pre_offset, offset->offset_R);
	ACE_REG_M19Ax_Rd01(adc_dig_227, g_pre_offset, offset->offset_G);
	ACE_REG_M19Ax_Rd01(adc_dig_229, b_pre_offset, offset->offset_B);
	/*
	offset->offset_R = gadc_dig_224.r_pre_offset_1 << 8 | gadc_dig_225.r_pre_offset_0;
	offset->offset_G = gadc_dig_226.g_pre_offset_1 << 8 | gadc_dig_227.g_pre_offset_0;
	offset->offset_B = gadc_dig_228.b_pre_offset_1 << 8 | gadc_dig_229.b_pre_offset_0;
	*/

	return 0;
}

int ADC_M19Ax_SetOffsetRGB( S_OFFSET_INFORM *offset)
{

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, offset->offset_R, offset->offset_G, offset->offset_B);

	ACE_REG_M19Ax_Wr01(adc_dig_225, r_pre_offset, offset->offset_R & 0x1FFF);
	ACE_REG_M19Ax_WrFL(adc_dig_225);

	ACE_REG_M19Ax_Wr01(adc_dig_227, g_pre_offset, offset->offset_G & 0x1FFF);
	ACE_REG_M19Ax_WrFL(adc_dig_227);

	ACE_REG_M19Ax_Wr01(adc_dig_229, b_pre_offset, offset->offset_B & 0x1FFF);
	ACE_REG_M19Ax_WrFL(adc_dig_229);


	return 0;
}


int ADC_M19Ax_GetSumRGB(S_RGB_SUM *sum)
{
	ACE_REG_M19Ax_RdFL(adc_dig_169);
	ACE_REG_M19Ax_Rd01(adc_dig_169, ap_sum_r, sum->sum_R);

	ACE_REG_M19Ax_RdFL(adc_dig_165);
	ACE_REG_M19Ax_Rd01(adc_dig_165, ap_sum_g, sum->sum_G);

	ACE_REG_M19Ax_RdFL(adc_dig_161);
	ACE_REG_M19Ax_Rd01(adc_dig_161, ap_sum_b, sum->sum_B);

	return 0;
}

/**
 *
 * Enable SCART RGB input on component 2(from B0 revision board) port for EU model
 *
 * @param	BOOLEAN scart_enable(TRUE:Enable SCART RGB, FALSE:component mode)
 *
*/
int ADC_M19Ax_Enable_Scart_Mode(BOOLEAN scart_enable)
{
//	UINT32	VP2_Intr_Enable_Mask = 0xFFFFFBFC; // Disable Resolution change & SOY1 detection interrupt.
//	static UINT32 	VP2_Intr_Enable_Save = 0;

	ADC_DEBUG("%s entered with value [%d]\n", __func__, scart_enable);

	if (scart_enable == TRUE)
	{
		//Interrupt Disable for component1
#if 0
		VP2_Intr_Enable_Save = gVportRegBx->intr_vp2_enable.intr_vp2_enable;
		gVportRegBx->intr_vp2_enable.intr_vp2_enable = VP2_Intr_Enable_Save & VP2_Intr_Enable_Mask;
#endif
		BMC_REG_M19Ax_RdFL(videoafe_03);
		//gafe_3ch_0.videoafe_selmux = 0x1;
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_selmux, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_03);

	//	gVportRegBx->ch3_adc_003.afe3ch_sel_ck = 0x1; // select clock from CVD

		//120128 wonsik.do : ADC_SetType is also called in KADP_AFE_Set_Source_Type(ADC_SetInputFormat)
//		ADC_SetType(LX_ADC_INPUT_SOURCE_RGB_SCART); // for SCART RGB set port type to RGB
	}
	else
	{
		// No need to set interrupt enable for the scart input.
#if 0
		if(VP2_Intr_Enable_Save)
			gVportRegBx->intr_vp2_enable.intr_vp2_enable = VP2_Intr_Enable_Save;
#endif

		// Port selection should be called from DDI
		//gVportRegBx->ch3_adc_004.videoafe_selmux = 0x0; // select component 1 port for ADC
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sel_ck, 0);
		BMC_REG_M19Ax_WrFL(videoafe_04);
	}
	return 0;
}

void ADC_M19Ax_Vport_ALL_Power_Down(void)	// not used
{
	/* AFE3CH Power Down Setting */
	//gVportRegBx->cvbsafe_pdb_001.afe3ch_biaspdb = 0x0;
//	gVportRegBx->cvbsafe_pdb_001.afe3ch_biaspdb = 0;

	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	/* LLPLL PDB */
	BMC_REG_M19Ax_RdFL(videoafe_05);
	BMC_REG_M19Ax_Wr01(videoafe_05, refpll_pdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_05);

	/* LLPLL/CST SWRST & 3CH_DIG SWRST */
	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 0);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 1);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);
}

int ADC_M19Ax_Channel_Power_Control(int vref_pdb, int bpdb, int gpdb, int rpdb)
{
	int ret = 0;
	UINT8	bpdb_status, gpdb_status, rpdb_status;

	ADC_DEBUG("ADC Channel Power Control vfref_pdb[%d], bpdb[%d], gpdb[%d], rpdb[%d]\n", vref_pdb, bpdb, gpdb, rpdb);

	ret = OS_LockMutex(&g_ADC_Sema);

	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Rd03(videoafe_00, videoafe_bpdb, bpdb_status, videoafe_gpdb, gpdb_status, videoafe_rpdb, rpdb_status);

	if( (bpdb_status == bpdb) && (gpdb_status == gpdb) && (rpdb_status == rpdb))
	{
		OS_UnlockMutex(&g_ADC_Sema);
		return 0;
	}

	// When Input Change from SCART RGB to AV/ATV, prevent CVD black screen 
	// Before turn off gpdb, disabling FB_EN to prevent CVD RGB-mixer latchup
	if(gpdb == 0)
		CVD_Set_Scart_FB_En(0);	// Disable FB_EN on no signal

	if(bpdb || gpdb || rpdb)	// 160725 : Added to reduce boot time
		OS_MsecSleep(5);

	if(bpdb >= 0)
	{
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, bpdb);
	}
	if(gpdb >= 0)
	{
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, gpdb);
	}
	if(rpdb >= 0)
	{
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, rpdb);
	}
	BMC_REG_M19Ax_WrFL(videoafe_00);

	if(bpdb || gpdb || rpdb)
	{
		/* to prevent htotal one */
		ADC_M19Ax_Reset_LLPLL();
		ADC_M19Ax_Reset_Digital();
	}
	else if( (bpdb == 0) && (gpdb == 0) && (rpdb == 0))
	{
		ADC_DEBUG("ADC Disconnect : Shield On \n");
		ADC_M19Ax_Shield_Control(1);
	}

	OS_UnlockMutex(&g_ADC_Sema);

	return ret;
}

int ADC_M19Ax_SetType(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type)
{
	S_BLANK_INFORM blank_value;
	//AFE_PRINT("ADC_SetType \n");
#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
	S_OFFSET_INFORM offset;
#endif
	gADC_type = sel_type;

	if(sel_type == LX_ADC_INPUT_SOURCE_YPBPR)
	{
		ADC_DEBUG("Component Input Mode\n");

		//ADC_M19Ax_SetCurrent(sel_type);

		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_outmux, 0);
		BMC_REG_M19Ax_WrFL(videoafe_04);

		BMC_REG_M19Ax_RdFL(videoafe_00);
		// afe3ch_clpcur moved to comp_params
		//BMC_REG_M19Ax_Wr01(afe_3ch_3, afe3ch_clpcur, 0x4);	//150421 : M16
		//BMC_REG_M19Ax_Wr01(afe_3ch_3, afe3ch_clpcur, 0x4);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rvclpsel, 1);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bvclpsel, 1);
		BMC_REG_M19Ax_WrFL(videoafe_00);

		ADC_M19Ax_Set_Sync_Mode(ADC_COMPOSITE_SYNC_MODE);
		/*
		   ACE_REG_M19Ax_RdFL(adc_dig_22);
		   ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
		   ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x1);
		   ACE_REG_M19Ax_WrFL(adc_dig_22);
		 */

		blank_value.r_blank_target_value = 0x400;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.g_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x240;
		blank_value.b_blank_target_value = 0x400;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;

		ADC_M19Ax_Set_Blank_Value(&blank_value);

		//added 0716
		ACE_REG_M19Ax_RdFL(adc_dig_58);
		ACE_REG_M19Ax_Wr01(adc_dig_58, hsout_width_sel, 0x1);		// Set to Manual mode '1'  ( For L8 '0' is manual mode )
		ACE_REG_M19Ax_WrFL(adc_dig_58);

		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		//110928 by dws: if set to '0' with vsprdeq_thr value '0x2', 1080P 60Hz screen sometimes roll-down slowly.
		ACE_REG_M19Ax_RdFL(adc_dig_61);
		//gadc_dig_61.vsout_sel = 0x0;
		//111101 by wonsik.do : use vsync bypass mode to fix picture rolling up/down problem.
		ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_61);

		//If vsout_sel is 0(vs_gen), sometimes vertical sync is not lock to video. Need more debuggint.
		//1214 powerory
		ACE_REG_M19Ax_Wr01(adc_dig_64, vsdiff_thr, 0x80);
		ACE_REG_M19Ax_WrFL(adc_dig_64);

		//gadc_dig_65.vsprdeq_thr = 0x0E;
		// reduced vsprdeq_thr value for fast locking on 24/25/30Hz signals.(110712)
		//gadc_dig_65.vsprdeq_thr = 0x02;
		//110928 by dws : better increase vsprdeq_thr value to '5', to use vsync locked mode (vsout_sel '0')
		//111101 by dws : increased vsprdeq_thr value to '7' from '5' (720P 50Hz sometimes roll-down )
		ACE_REG_M19Ax_Wr01(adc_dig_65, vsprdeq_thr, 0x07);
		ACE_REG_M19Ax_WrFL(adc_dig_65);

		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
		//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 0;

		/*
		//20110124 powerory (480i 입력에서 문제점해결위해 수정)
		ACE_REG_M19Ax_Wr01(adc_dig_52, hsdiff_thr_1, 0x0);
		ACE_REG_M19Ax_Wr01(adc_dig_53, hsdiff_thr_0, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_52);
		ACE_REG_M19Ax_WrFL(adc_dig_53);
		 */

		//20110125
		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block
		ACE_REG_M19Ax_RdFL(adc_dig_88);
		ACE_REG_M19Ax_Wr01(adc_dig_88, hsync_sel, 0);
		ACE_REG_M19Ax_WrFL(adc_dig_88);

		//Modified Component Initial SOG Settings : 121126
		/*
		ACE_REG_M17C0_RdFL(afe_3ch_7);
		//gafe_3ch_7.afe3ch_ctl_add	= 0x93;
		//ACE_REG_M17C0_Wr01(afe_3ch_7, afe3ch_ctl_add, 0x13);	 //by gogosing 111026 : shibasoku sync unstable problem.
		ACE_REG_M17C0_Wr01(afe_3ch_7, sog_deglitch, 0x0);	 
		ACE_REG_M17C0_Wr01(afe_3ch_7, en_win, 0x0);
		ACE_REG_M17C0_Wr01(afe_3ch_7, adc_input_filter_sel, 0x0);
		ACE_REG_M17C0_WrFL(afe_3ch_7);

		ACE_REG_M17C0_RdFL(afe_3ch_6);
		ACE_REG_M17C0_Wr01(afe_3ch_6, afe3ch_sog_bw, 0x3);
		//gafe_3ch_6.afe3ch_sog_inbw = 0x3;			// select data clock
		// 111109 fix component shaking on shibasoku.
		// H13_BRINGUP : 0512
		//ACE_REG_M17C0_Wr01(afe_3ch_6, afe3ch_sog_inbw, 0x1);	//0x3	// select llpll clock
		ACE_REG_M17C0_Wr01(afe_3ch_6, afe3ch_sog_inbw, 0x4);

		ACE_REG_M17C0_WrFL(afe_3ch_6);

		//H13_BRINGUP : 0512
		ACE_REG_M17C0_RdFL(afe_3ch_8);
		ACE_REG_M17C0_Wr01(afe_3ch_8, afe3ch_sel_fs, 0x0);
		//ACE_REG_M17C0_Wr01(afe_3ch_8, afe3ch_sel_datack, 0x1);
		ACE_REG_M17C0_Wr01(afe_3ch_8, afe3ch_sel_invdatack, 0x1);
		//ACE_REG_M17C0_Wr01(afe_3ch_8, afe3ch_sel_bg, 0x0);
		ACE_REG_M17C0_Wr01(afe_3ch_8, afe3ch_sel_fil, 0x0);
		ACE_REG_M17C0_WrFL(afe_3ch_8);
		*/

		BMC_REG_M19Ax_RdFL(videoafe_01);
		//New Value for L9B0 by Min 110915
		// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_hys, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_01);

		//Modified Component Initial SOG Settings : 121126
		//Following is component 1080P 50/60Hz settings
		// #######################################################################
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
		BMC_REG_M19Ax_WrFL(videoafe_01);
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x4);	//Modified for Master Distributer (from 0x0)
		BMC_REG_M19Ax_WrFL(videoafe_01);

		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x3);	 
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_04);
		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_03);

		BMC_REG_M19Ax_RdFL(videoafe_00);
		//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video

		//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_datack, 0x0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);	//130215 : use data clock
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_00);

		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x2);	//0x3 for 1-line on/off pattern
		BMC_REG_M19Ax_WrFL(videoafe_01);
		// #######################################################################

		ACE_REG_M19Ax_RdFL(adc_dig_111);
		// to enable en_win
		ACE_REG_M19Ax_Wr01(adc_dig_111, intr_ctrl, 0x8);
		ACE_REG_M19Ax_WrFL(adc_dig_111);
		
		ACE_REG_M19Ax_RdFL(adc_dig_296);
		ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_296);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//modified for FT low voltage test (from 0x4)
		BMC_REG_M19Ax_WrFL(videoafe_03);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_R_PRE_OFFSET_VALUE;
		offset.offset_G	= ADC_G_PRE_OFFSET_VALUE;
		offset.offset_B	= ADC_B_PRE_OFFSET_VALUE;

		ADC_M19Ax_SetOffsetRGB(&offset);
#endif

	}
	else if(sel_type == LX_ADC_INPUT_SOURCE_RGB_SCART)
	{
		ADC_DEBUG("SCART RGB Input Mode\n");
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_outmux, 0);
		BMC_REG_M19Ax_WrFL(videoafe_04);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150421 : M16
		BMC_REG_M19Ax_WrFL(videoafe_03);
		//BMC_REG_M19Ax_Wr01(afe_3ch_3, videoafe_clpcur, 0x3);
		BMC_REG_M19Ax_RdFL(videoafe_00);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bvclpsel, 0);
		BMC_REG_M19Ax_WrFL(videoafe_00);

		ADC_M19Ax_Set_Sync_Mode(ADC_COMPOSITE_SYNC_MODE);
		/*
		ACE_REG_M19Ax_RdFL(adc_dig_22);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_22);
		*/

		blank_value.r_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x200;
		blank_value.b_blank_target_value = 0x200;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;
		ADC_M19Ax_Set_Blank_Value(&blank_value);

		//added 0716
		ACE_REG_M19Ax_RdFL(adc_dig_58);
		ACE_REG_M19Ax_Wr01(adc_dig_58, hsout_width_sel, 0x1);		// Set to Manual mode '1'  ( For L8 '0' is manual mode )
		ACE_REG_M19Ax_WrFL(adc_dig_58);

		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		ACE_REG_M19Ax_RdFL(adc_dig_61);
		ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_61);

		//If vsout_sel is 0(vs_gen), sometimes vertical sync is not lock to video. Need more debuggint.
		//1214 powerory
		ACE_REG_M19Ax_Wr01(adc_dig_64, vsdiff_thr, 0x80);
		ACE_REG_M19Ax_WrFL(adc_dig_64);

		//gadc_dig_65.vsprdeq_thr = 0x0E;
		// reduced vsprdeq_thr value for fast locking on 24/25/30Hz signals.(110712)
		/*
		ACE_REG_M19Ax_Wr01(adc_dig_65, vsprdeq_thr, 0x0F);
		ACE_REG_M19Ax_WrFL(adc_dig_65);
		*/

		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 0;

		/*
		//20110124 powerory (480i 입력에서 문제점해결위해 수정)
		ACE_REG_M19Ax_Wr01(adc_dig_52, hsdiff_thr_1, 0x0);
		ACE_REG_M19Ax_Wr01(adc_dig_53, hsdiff_thr_0, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_52);
		ACE_REG_M19Ax_WrFL(adc_dig_53);
		*/

		//20110125
		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block
		ACE_REG_M19Ax_RdFL(adc_dig_88);
		ACE_REG_M19Ax_Wr01(adc_dig_88, hsync_sel, 0);
		ACE_REG_M19Ax_WrFL(adc_dig_88);

		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x8);		//LOEWE SCART RGB Noise
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_hys, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_01);

		//###########################################
		//0x1a/0x26
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
		BMC_REG_M19Ax_WrFL(videoafe_01);
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x5);	// MSPG blue color sync unstable
		BMC_REG_M19Ax_WrFL(videoafe_01);

		//0x1a/0x27
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x3);	 
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_04);
		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x7);
		BMC_REG_M19Ax_WrFL(videoafe_03);

		//0x1b/0x50
		BMC_REG_M19Ax_RdFL(videoafe_00);
	//	BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);

		/* for H13B0 Bring-up hsoutprd '0' when RF snow noise. */
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video

		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_00);

		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x3);
		BMC_REG_M19Ax_WrFL(videoafe_01);
		//###########################################

		ACE_REG_M19Ax_RdFL(adc_dig_111);
		// to enable en_win
		ACE_REG_M19Ax_Wr01(adc_dig_111, intr_ctrl, 0x8);
		ACE_REG_M19Ax_WrFL(adc_dig_111);
		
		ACE_REG_M19Ax_RdFL(adc_dig_296);
		ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_296);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//modified for FT low voltage test (from 0x4)
		BMC_REG_M19Ax_WrFL(videoafe_03);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_R_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;
		offset.offset_G	= ADC_G_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;
		offset.offset_B	= ADC_B_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;

		ADC_M19Ax_SetOffsetRGB(&offset);
#endif
	}
	else
	{
		ADC_DEBUG("RGB Input Mode\n");
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_outmux, 1);
		BMC_REG_M19Ax_WrFL(videoafe_04);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_03);
		BMC_REG_M19Ax_RdFL(videoafe_00);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bvclpsel, 0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
		BMC_REG_M19Ax_WrFL(videoafe_00);

		ADC_M19Ax_Set_Sync_Mode(ADC_SEPERATED_SYNC_MODE);
		/*
		ACE_REG_M19Ax_RdFL(adc_dig_22);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_22);
		*/

		blank_value.r_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x200;
		blank_value.b_blank_target_value = 0x200;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;
		ADC_M19Ax_Set_Blank_Value(&blank_value);

		//added 0716
		//gVportRegBx->ch3_digital_004.ch3reg_hsout_width_sel = 0x1; // Select Auto Hsync output sync width

		// for horizontal sync re-shape in ADC

		//TEMP for L9B0 Bring-UP	: 110832 by dws
		// if hsout width is set to '2', output image collapses.
		ACE_REG_M19Ax_RdFL(adc_dig_58);
		ACE_REG_M19Ax_Wr01(adc_dig_58, hsout_width_sel, 0x1);
		//gadc_dig_58.hsout_width_sel = 0x0;
		ACE_REG_M19Ax_WrFL(adc_dig_58);

//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x0; // Select internal Hsync for digital block
//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // powerory  <== CAN NOT CHANGE HSIZE BY 1 STEP
//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // B0 Revision Fixed bug(HSIZE 1 STEP)

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;
		ACE_REG_M19Ax_RdFL(adc_dig_61);
		ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_61);

		/*
		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
		ACE_REG_M19Ax_Wr01(adc_dig_52, hsdiff_thr_1, 0x0);
		ACE_REG_M19Ax_Wr01(adc_dig_53, hsdiff_thr_0, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_52);
		ACE_REG_M19Ax_WrFL(adc_dig_53);
		*/

//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 1;
//		gVportRegBx->ch3_digital_003.ch3reg_hsoutcnt = gVportRegBx->ch3_llpll_003.llpll_counter_max - 1;
		//20110125
		ACE_REG_M19Ax_RdFL(adc_dig_88);
		ACE_REG_M19Ax_Wr01(adc_dig_88, hsync_sel, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_88);

		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x0);	 
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_04);
		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_03);

		//110921 : Is sog_inbw setting needed on RGB mode ???
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x3);
		BMC_REG_M19Ax_WrFL(videoafe_01);

		ACE_REG_M19Ax_RdFL(adc_dig_296);
		ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_296);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//180717 : modified for FT low voltage test (from 0x4)
		BMC_REG_M19Ax_WrFL(videoafe_03);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_R_PRE_OFFSET_VALUE;
		offset.offset_G	= ADC_G_PRE_OFFSET_VALUE;
		offset.offset_B	= ADC_B_PRE_OFFSET_VALUE;

		ADC_M19Ax_SetOffsetRGB(&offset);
#endif

		ADC_M19Ax_SetCurrent(2);
	}

	return 0;
}

int ADC_M19Ax_Set_LLPLL(UINT32 arg)
{

	if(arg >= PARAM_NUM)
		return -1;

		AFE_PRINT("Setting LLPLL to Index Number [%d]\n", arg);

	//ADC_SetInputVideo(arg);

	if(ADC_SetInputVideo(arg) == 0)
		gPrevious_index = 0xffff;

	return 0;

}

int ADC_M19Ax_SetClock(int iIndex, SINT16 value)
{
	UINT16 clock_value;
#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	UINT8 dco_max_value, dco_min_value;
#endif
	//	AFE_PRINT("%s entered\n", __func__);
	//LLPLL_counter_max
	clock_value = LLPLL_counter_max[iIndex];

	//	AFE_PRINT("Clock Value =[%d +(%d)], \n", clock_value, value);

	// No Need to Write Same Value
	/*
	   if(gVportRegBx->ch3_llpll_003.llpll_counter_max == (clock_value + value))
	   return 0;
	 */

#ifdef	KDRV_CONFIG_PM
	gAdcPMData->giPmClockValue = value;
#endif
	clock_value += value;
	//ADC_Ext_Clamp(1);

	BMC_REG_M19Ax_RdFL(videoafe_10);
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_counter_max, clock_value&0xFFF);
	BMC_REG_M19Ax_WrFL(videoafe_10);

	//by dws : remove mdelay
	//mdelay(10);
	OS_MsecSleep(5);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	ADC_M19Ax_Get_DCO_MinMax_Value(&dco_min_value, &dco_max_value);
	ADC_M19Ax_Set_DCO_MinMax_Value(0, 0);
#endif

	//by dws : remove mdelay
	//mdelay(10);
	OS_MsecSleep(5);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	ADC_M19Ax_Set_DCO_MinMax_Value(dco_min_value, dco_max_value);
#endif
	OS_MsecSleep(30);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	// for MSPG 68 timing (1152*720) : sometimes LLPLL unlock occur durring size adjust
	ADC_M19Ax_Check_LLPLL_status();
#endif

	return 0;
}

int ADC_M19Ax_Reset_Digital(void)
{
	ADC_DEBUG("reset_digital\n");

#ifdef L8_RGB_FEEDBACK_HSYNC_WORKAROUND
	ADC_Channel_Power_Control(-1, 0, -1, 0);
#endif

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 1);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	//by dws : remove mdelay
//	mdelay(5);
	OS_MsecSleep(5);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 0);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

#ifdef L8_RGB_FEEDBACK_HSYNC_WORKAROUND
	ADC_Channel_Power_Control(-1, 1, -1, 1);
#endif

	return 0;
}


int ADC_M19Ax_Reset_Digital_24MHZ(void)
{
	ADC_DEBUG("%s entered\n", __func__);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_f24m, 1);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	OS_MsecSleep(5);

	MIP_REG_M19Ax_RdFL(bmc_ctr01);
	MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_f24m, 0);
	MIP_REG_M19Ax_WrFL(bmc_ctr01);

	return 0;
}


int ADC_M19Ax_Reset_Digital_Control(int enable_reset)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable_reset);

	if(enable_reset)
	{
		MIP_REG_M19Ax_RdFL(bmc_ctr01);
		MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 1);
		MIP_REG_M19Ax_WrFL(bmc_ctr01);
	}
	else
	{
		MIP_REG_M19Ax_RdFL(bmc_ctr01);
		MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_pix, 0);
		MIP_REG_M19Ax_WrFL(bmc_ctr01);
	}

	return 0;
}

int ADC_M19Ax_Reset_LLPLL(void)
{
	ADC_DEBUG("%s entered\n", __func__);

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 0);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 1);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	return 0;
}

int ADC_M19Ax_Reset_LLPLL_Control(int enable_reset)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable_reset);

	if(enable_reset)
	{
		BMC_REG_M19Ax_RdFL(videoafe_11);
		BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 0);
		BMC_REG_M19Ax_WrFL(videoafe_11);
	}
	else
	{
		BMC_REG_M19Ax_RdFL(videoafe_11);
		BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 1);
		BMC_REG_M19Ax_WrFL(videoafe_11);
	}

	return 0;
}

int ADC_M19Ax_Sync_Polarity_Override(int set)
{
	ADC_DEBUG("%s entered\n", __func__);
	if(set)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_21);
		ACE_REG_M19Ax_Wr01(adc_dig_21, hspolover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_21, vspolover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_21, hspoluser, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_21, vspoluser, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_21);
	}
	else
	{
		ACE_REG_M19Ax_RdFL(adc_dig_21);
		ACE_REG_M19Ax_Wr01(adc_dig_21, hspolover, 0);
		ACE_REG_M19Ax_Wr01(adc_dig_21, vspolover, 0);
//		gadc_dig_21.hspoluser = 0;
//		gadc_dig_21.vspoluser = 0;
		ACE_REG_M19Ax_WrFL(adc_dig_21);
	}

	return 0;
}



int ADC_M19Ax_Check_Sync_Exist(void)
{

#if 1
	UINT8	vsdet_value, hsdet_value;

	ACE_REG_M19Ax_RdFL(adc_dig_28);

	ACE_REG_M19Ax_Rd01(adc_dig_28, ro_hsdet, hsdet_value);
	ACE_REG_M19Ax_Rd01(adc_dig_28, ro_vsdet, vsdet_value);

	if ( ( ( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC) && (hsdet_value == 1) /*&& (vsdet_value == 1)*/ ) || ( ( gADC_type != LX_ADC_INPUT_SOURCE_RGB_PC) && (hsdet_value == 1) ) )
		return 1;
#else
	UINT8	no_signal;

	ACE_REG_M19Ax_RdFL(adc_dig_121);

	ACE_REG_M19Ax_Rd01(adc_dig_121, no_signal, no_signal);

	if(no_signal < 1) // signal exist
		return 1;
#endif

	return 0;

}

int ADC_M19Ax_Enable_Detection_Interrupt(int enable)
{
	ADC_DEBUG("%s entered\n", __func__);

	return 0;
}

int ADC_M19Ax_Enable_AOGC_Interrupt(int enable)
{
	ADC_DEBUG("%s entered\n", __func__);

	if(enable)
	{
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sel_ck, 2);	//set ADC clock from ref clock
		BMC_REG_M19Ax_WrFL(videoafe_04);
	}
	else
	{
		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sel_ck, 0);
		BMC_REG_M19Ax_WrFL(videoafe_04);
	}

	return 0;
}

int ADC_M19Ax_Mute_Enable(int enable)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable);
	if(enable)
	{
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
			ACE_REG_M19Ax_RdFL(adc_dig_89);
			ACE_REG_M19Ax_Wr01(adc_dig_89, red_signedout, 1);
			ACE_REG_M19Ax_Wr01(adc_dig_89, green_signedout, 0);
			ACE_REG_M19Ax_Wr01(adc_dig_89, blue_signedout, 1);
			ACE_REG_M19Ax_WrFL(adc_dig_89);
		}
		BMC_REG_M19Ax_RdFL(videoafe_02);
		BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_ire_test, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_02);
	}
	else
	{
		ACE_REG_M19Ax_RdFL(adc_dig_89);
		ACE_REG_M19Ax_Wr01(adc_dig_89, red_signedout, 0);
		ACE_REG_M19Ax_Wr01(adc_dig_89, green_signedout, 0);
		ACE_REG_M19Ax_Wr01(adc_dig_89, blue_signedout, 0);
		ACE_REG_M19Ax_WrFL(adc_dig_89);
		BMC_REG_M19Ax_RdFL(videoafe_02);
		BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_ire_test, 0);
		BMC_REG_M19Ax_WrFL(videoafe_02);
	}

	return 0;
}

int ADC_M19Ax_Power_OnOff(void)	// not used
{
	ADC_DEBUG("%s entered\n", __func__);

	BMC_REG_M19Ax_RdFL(videoafe_02);
	BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_biaspdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_02);

	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, 0);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, 0);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 1;
	//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 1;
	//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 1;


	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	BMC_REG_M19Ax_RdFL(videoafe_02);
	BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_biaspdb, 1);
	BMC_REG_M19Ax_WrFL(videoafe_02);

	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_bpdb, 1);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gpdb, 1);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_rpdb, 1);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 0);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	BMC_REG_M19Ax_RdFL(videoafe_11);
	BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 1);
	BMC_REG_M19Ax_WrFL(videoafe_11);

	return 0;
}

int ADC_M19Ax_Ext_Clamp(int sel_ext)
{
//	static int g_ph_value = 4;

	ADC_DEBUG("%s entered [%d]\n", __func__, sel_ext);
	if(sel_ext)
	{
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			ADC_Channel_Power_Control(0);
	//		gVportRegBx->top_008.reg_swrst_llpll = 0x1;
//			gVportRegBx->top_008.reg_swrst_ch3pix = 0x1;
			/*
			VPORT_RdFL(ch3_adc_005);
			VPORT_Wr01(ch3_adc_005, afe3ch_g_ph, 1);
			VPORT_WrFL(ch3_adc_005);
			AFE_PRINT("Set g_ph value to 0 \n");
			*/
		}

//		mdelay(10);

		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			mdelay(5);
//			ADC_Channel_Power_Control(1);
//			mdelay(5);
		}
		// powerory
		//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 1;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 1;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 1;
		//~powerory
#if 0
		if(gADC_type != LX_ADC_INPUT_SOURCE_YPBPR)	// 1019 Workaround for CVI Vsync Unstable on component input(VENICE 1080i)
			gVportRegBx->top_008.reg_swrst_ch3pix = 0x1;
		//mdelay(1000);
#endif
	}
	else
	{
		// powerory
		//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 0;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 0;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 0;
		//~powerory
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			mdelay(5);
	//		gVportRegBx->top_008.reg_swrst_llpll = 0x0;
//			mdelay(300);
//			gVportRegBx->top_008.reg_swrst_ch3pix = 0x0;
			/*
			VPORT_RdFL(ch3_adc_005);
			VPORT_Wr01(ch3_adc_005, afe3ch_g_ph, g_ph_value);
			VPORT_WrFL(ch3_adc_005);
			AFE_PRINT("Restore g_ph value to [%d]\n",g_ph_value);
			*/
		}
		//mdelay(30);
	}

	return 0;
}

int ADC_M19Ax_Set_Clamp(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width)
{
	if(clamp_base)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_50);
		ACE_REG_M19Ax_Wr01(adc_dig_50, clamp_base, clamp_base & 0x3);
		ACE_REG_M19Ax_WrFL(adc_dig_50);
	}

	if(clamp_place)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_51);
		ACE_REG_M19Ax_Wr01(adc_dig_51, clamp_place, clamp_place);
		ACE_REG_M19Ax_WrFL(adc_dig_51);
	}

	if(clamp_width)
	{
		ACE_REG_M19Ax_RdFL(adc_dig_220);
		ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, clamp_width);
		ACE_REG_M19Ax_WrFL(adc_dig_220);
	}

	return 0;
}

#ifdef	KDRV_CONFIG_PM
int ADC_M19Ax_RunSuspend(void)
{
	/*
	// confirm initialization done
	if(gVportRegBx == NULL)
		return -1;

	// TAU inform
	gAdcPMData->gstPmExtauValue.height_offset = gVportRegBx->ch3_digital_026.ch3reg_extau_down_offset;
	gAdcPMData->gstPmExtauValue.width_offset = gVportRegBx->ch3_digital_028.ch3reg_extau_right_offset;
	gAdcPMData->gstPmExtauValue.width_offset = gVportRegBx->ch3_digital_023.ch3reg_extau_ctrl;

	//
	ADC_GetRGBPosition(&gAdcPMData->gstPmPositionValue);
	// phase
	gAdcPMData->guiPmPhaseValue = ADC_GetPhaseValue();

	ADC_GetGainValue(&gAdcPMData->gstPmGainValue);

	ADC_GetOffsetValue(&gAdcPMData->gstPmOffsetValue);


	gAdcPMData->guiPmInterruptStatus = gVportRegBx->intr_vp2_enable.intr_vp2_enable;

	ADC_Vport_ALL_Power_Down();
	*/

	return 0;
}

int ADC_M19Ax_RunResume(void)
{

	ADC_M19Ax_RegInit();

	/*
	if(gAdcPMData->gstPmSelPortValue.port == 0xfffffff)
		return 0;

	VPORT_RdFL(ch3_digital_026);
	VPORT_Wr01(ch3_digital_026, ch3reg_extau_down_offset, gAdcPMData->gstPmExtauValue.height_offset);
	VPORT_WrFL(ch3_digital_026);

	gVportRegBx->ch3_digital_028.ch3reg_extau_right_offset = gAdcPMData->gstPmExtauValue.width_offset;
	gVportRegBx->ch3_digital_023.ch3reg_extau_ctrl = gAdcPMData->gstPmExtauValue.width_offset;

	gVportRegBx->intr_vp2_enable.intr_vp2_enable = gAdcPMData->guiPmInterruptStatus;

	if(gAdcPMData->giPmIndexValue < 0)
		return 0;

	ADC_SetRGBPosition(&gAdcPMData->gstPmPositionValue);

	ADC_SetPhaseValue(gAdcPMData->guiPmPhaseValue);

	ADC_SetGainValue(&gAdcPMData->gstPmGainValue);

	ADC_SetOffsetValue(&gAdcPMData->gstPmOffsetValue);

	if(gAdcPMData->giPmIndexValue >= 0)
	{
		ADC_SetInputVideo(gAdcPMData->giPmIndexValue);
		ADC_SetClock(gAdcPMData->giPmIndexValue ,gAdcPMData->giPmClockValue);
	}

	*/
	return 0;
}
#endif


/**
 *
 * ADC_GetPCmodeInfo : Return current mode index
 *
 * @param	struct work_struct
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_M19Ax_GetPCModeInfo(LX_AFE_PCMODE_INFO_T *stPCModeInfo)
{
	UINT16	Vline, Vlowline;

	if(gResolution >= 0)
	{
		memset((void *)stPCModeInfo, 0, sizeof(LX_AFE_PCMODE_INFO_T));
		stPCModeInfo->u8_Mode_Idx = gResolution;

		ACE_REG_M19Ax_RdFL(adc_dig_76);
		ACE_REG_M19Ax_Rd01(adc_dig_76, ro_hsout_width, stPCModeInfo->u16_HSyncWidth);

		ACE_REG_M19Ax_RdFL(adc_dig_35);
		ACE_REG_M19Ax_Rd01(adc_dig_35, ro_vsprdref, Vline);

		ACE_REG_M19Ax_RdFL(adc_dig_36);
		ACE_REG_M19Ax_Rd01(adc_dig_36, ro_vslowref, Vlowline);

		stPCModeInfo->u8_UI_Phase = ADC_Phase_Convert_to_UI_Value(ADC_GetPhaseValue(), gResolution);
		if(Vlowline > (Vline>>1))
		{
			// Active High VSync Pulse
			stPCModeInfo->u16_VSyncWidth = Vline - Vlowline;
		}
		else
		{
			stPCModeInfo->u16_VSyncWidth = Vlowline;
		}

		return 0;
	}
	else
	{
		memset((void *)stPCModeInfo, 0, sizeof(LX_AFE_PCMODE_INFO_T));
		stPCModeInfo->u8_Mode_Idx = 0xff;
		return 0;
	}
}

int ADC_M19Ax_Get_LLPLL_Filter_Status(void)
{
	UINT32 filter_status;
	BMC_REG_M19Ax_RdFL(videoafe_07);
	BMC_REG_M19Ax_Rd01(videoafe_07, llpll_filter_status, filter_status);

	return filter_status;
}

int ADC_M19Ax_Set_Coast(UINT8 precoast, UINT8 postcoast)
{
	ACE_REG_M19Ax_RdFL(adc_dig_22);
	ACE_REG_M19Ax_RdFL(adc_dig_23);
	ACE_REG_M19Ax_Wr01(adc_dig_22, precoast, precoast&0x1F);
	ACE_REG_M19Ax_Wr01(adc_dig_23, postcoast, postcoast&0x1F);
	ACE_REG_M19Ax_WrFL(adc_dig_22);
	ACE_REG_M19Ax_WrFL(adc_dig_23);

	return 0;
}

int ADC_M19Ax_Set_Hsync_Sel(UINT8 select)
{
	ACE_REG_M19Ax_RdFL(adc_dig_88);

	if(select > 0)
	{
		// Select feedback LLPLL Hsync for digital block
		ACE_REG_M19Ax_Wr01(adc_dig_88, hsync_sel, 0x1);
	}
	else
	{
		ACE_REG_M19Ax_Wr01(adc_dig_88, hsync_sel, 0);
	}

	ACE_REG_M19Ax_WrFL(adc_dig_88);

	return 0;
}

int ADC_M19Ax_CVI_Sync_Exist(void)
{
	//FIXME L8B0 bug, Check if L9 has the same problem.
#if 0
	UINT32 hsync_exist, vsync_exist, src_valid;
	CHA_CVI_RdFL(cha_size_status0);
	CHA_CVI_Rd03(cha_size_status0, hsync_signal_detect, hsync_exist, vsync_signal_detect, vsync_exist, source_valid, src_valid);

	AFE_PRINT("hsync = [%d], vsync = [%d], valid = [%d]\n", hsync_exist, vsync_exist, src_valid);

	if(hsync_exist && vsync_exist/* && src_valid*/)
		return 1;
	else
#endif
	return 0;
}

int ADC_M19Ax_Set_SOG_Level(UINT32 level)
{
	if(level > 0x1F)
		return -1;

	BMC_REG_M19Ax_RdFL(videoafe_01);
	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, level&0x1F);
	BMC_REG_M19Ax_WrFL(videoafe_01);

	ADC_DEBUG("Set SOG Level = [0x%x]\n", level);

	return 0;
}

int ADC_M19Ax_Get_SOG_Level(UINT32 *level)
{
	BMC_REG_M19Ax_RdFL(videoafe_01);
	BMC_REG_M19Ax_Rd01(videoafe_01, videoafe_soglvl, *level);

	ADC_DEBUG("Get SOG Level = [0x%x]\n", *level);

	return 0;
}

int ADC_M19Ax_Check_Htotal_Diff(UINT8 count, int Kadp_Index)
{
	UINT8 i;
	UINT16 maxCnt16 = 0;
	UINT16 hsoutprd16 = 0;
	int	filter_status;

	static int hsprd_wrong_count = 0;
	static int hsprd_one_count = 0;
	static int hsprd_one_error_count = 0;
	static int llpll_unlock_count = 0;

	UINT32	phase_value;

	for(i = 0; i < count;i++)
	{
		maxCnt16 = 0;
		hsoutprd16 = 0;

		BMC_REG_M19Ax_RdFL(videoafe_07);
		BMC_REG_M19Ax_Rd01(videoafe_07, llpll_filter_status, filter_status);

		BMC_REG_M19Ax_RdFL(videoafe_10);
		BMC_REG_M19Ax_Rd01(videoafe_10, llpll_counter_max, maxCnt16);

		ACE_REG_M19Ax_RdFL(adc_dig_82);
		ACE_REG_M19Ax_Rd01(adc_dig_82, ro_hsoutprd, hsoutprd16);

		if(	g_M16_Comp_Double_Sampling > 0)
		{
			if( (gADC_type == LX_ADC_INPUT_SOURCE_YPBPR) && ( (Kadp_Index == 59) || (Kadp_Index == 61) ) )
			{
				//ADC_DEBUG("##### 480i/576i [%d]!!!\n", hsoutprd16);
				hsoutprd16 = hsoutprd16 >> 1;
			}
		}

		if(filter_status == 0)
		{
			ADC_DEBUG("LLPLL Unlock [%d]\n", llpll_unlock_count);
			if( (gADC_type == LX_ADC_INPUT_SOURCE_YPBPR) && ( (Kadp_Index == 59) || (Kadp_Index == 61) ) )
			{
//				ADC_Reset_Digital();
			}
			llpll_unlock_count++;
		}
		else
			llpll_unlock_count = 0;
			
		if(llpll_unlock_count > 100)
		{
			AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			AFE_PRINT("!!!!! LLPLL UNLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			AFE_PRINT("!!!!! RESET LLPLL                        !!!!!!!!!!\n");
			AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			ADC_Reset_LLPLL();
			llpll_unlock_count = 0;
			_g_ADC_Enable_Htotal_Diff_Check = 0;

			return 0;
		}

		if(abs(maxCnt16 - hsoutprd16) > 0)
		{
			ADC_DEBUG("htotal_in[%d],htotal_out[%d],llpll_status[%d]\n", maxCnt16, hsoutprd16, filter_status);
			
			if(hsoutprd16 == 1)
				hsprd_one_count++;
			else
				hsprd_wrong_count++;

			if(hsprd_wrong_count > 20) {
				// add for M14B0 reset_digital cannot recover from htotal zero condition
				ADC_Reset_LLPLL();
				ADC_Reset_Digital();

				AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				AFE_PRINT("!!!!! Htotal diff [%d] [0x%x][0x%x]		!!!!!!!!!!\n", i, maxCnt16 , hsoutprd16);
				AFE_PRINT("!!!!! RESET LLPLL                        !!!!!!!!!!\n");
				AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				hsprd_wrong_count = 0;
				_g_ADC_Enable_Htotal_Diff_Check = 0;

				return 0;
			}

			if(hsprd_one_error_count > 1) {
				AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				AFE_PRINT("!!!!! Htotal one for long time [%d] [0x%x][0x%x]!!!\n", i, maxCnt16 , hsoutprd16);
				AFE_PRINT("!!!!! RESET LLPLL                        !!!!!!!!!!\n");
				AFE_PRINT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				ADC_Reset_LLPLL();
				hsprd_one_count = 0;
				hsprd_one_error_count = 0;
				_g_ADC_Enable_Htotal_Diff_Check = 0;

				return 0;
			}
			else if(hsprd_one_count >= 5) {
				phase_value = ADC_M19Ax_GetPhaseValue();
				AFE_PRINT("##### Htotal one [%d] [0x%x][0x%x]!!!\n", i, maxCnt16 , hsoutprd16);
				AFE_PRINT("##### Prev Phase Value [0x%x]\n",  phase_value);

				if(phase_value >= 5)
					phase_value -= 5;
				else
					phase_value += 5;

				AFE_PRINT("##### Modified Phase Value [0x%x]\n",  phase_value);
				ADC_M19Ax_SetPhaseValue(phase_value);

				hsprd_one_error_count++;
				hsprd_one_count = 0;
			}

			OS_MsecSleep(10);
		}
		else {
			hsprd_wrong_count = 0;
			hsprd_one_count = 0;
			hsprd_one_error_count = 0;

			return 0;
		}

	}
	return -1;
}

int ADC_M19Ax_Read_Pixel_Value(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t)
{
	int ret = 0;
	S_RGB_SUM sum;

	ACE_REG_M19Ax_Wr01(adc_dig_139, ap_xpos_r, (pixel_value_t->X_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_139);

	ACE_REG_M19Ax_Wr01(adc_dig_141, ap_xsize_r, (pixel_value_t->X_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_141);

	ACE_REG_M19Ax_Wr01(adc_dig_143, ap_ypos_r, (pixel_value_t->Y_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_143);

	ACE_REG_M19Ax_Wr01(adc_dig_145, ap_ysize_r, (pixel_value_t->Y_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_145);

	ACE_REG_M19Ax_Wr01(adc_dig_123, ap_xpos_g, (pixel_value_t->X_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_123);

	ACE_REG_M19Ax_Wr01(adc_dig_125, ap_xsize_g, (pixel_value_t->X_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_125);

	ACE_REG_M19Ax_Wr01(adc_dig_127, ap_ypos_g, (pixel_value_t->Y_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_127);

	ACE_REG_M19Ax_Wr01(adc_dig_129, ap_ysize_g, (pixel_value_t->Y_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_129);

	ACE_REG_M19Ax_Wr01(adc_dig_131, ap_xpos_b, (pixel_value_t->X_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_131);

	ACE_REG_M19Ax_Wr01(adc_dig_133, ap_xsize_b, (pixel_value_t->X_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_133);

	ACE_REG_M19Ax_Wr01(adc_dig_135, ap_ypos_b, (pixel_value_t->Y_Pos&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_135);

	ACE_REG_M19Ax_Wr01(adc_dig_137, ap_ysize_b, (pixel_value_t->Y_Size&0xFFF));
	ACE_REG_M19Ax_WrFL(adc_dig_137);

	if( (pixel_value_t->X_Size * pixel_value_t->Y_Size) > 5)
		OS_MsecSleep(100);
	else
		OS_UsecDelay(10);

	ADC_M19Ax_GetSumRGB(&sum);

	pixel_value_t->Sum_R_Value = sum.sum_R;
	pixel_value_t->Sum_G_Value = sum.sum_G;
	pixel_value_t->Sum_B_Value = sum.sum_B;

	return ret;
}

int ADC_M19Ax_Green_Mid_Level_Select(UINT8 value)
{
	BMC_REG_M19Ax_RdFL(videoafe_00);
	BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_gvclpsel, value & 0x1);
	BMC_REG_M19Ax_WrFL(videoafe_00);

	return 0;
}

int ADC_M19Ax_Read_VSync_Width(UINT32 *pvs_width)
{
	UINT32 v_line_count, v_low_line_count;
	UINT16 out16 = 0;

	if( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC)
	{
		out16 = 0;
		v_line_count = 0;
		ACE_REG_M19Ax_RdFL(adc_dig_35);
		ACE_REG_M19Ax_Rd01(adc_dig_35, ro_vsprdref, v_line_count);

		ACE_REG_M19Ax_RdFL(adc_dig_36);
		ACE_REG_M19Ax_Rd01(adc_dig_36, ro_vslowref, v_low_line_count);

		if((v_line_count /2) > v_low_line_count)	// Active Low VSync
			*pvs_width = v_low_line_count;
		else										// Active High VSync
			*pvs_width = v_line_count - v_low_line_count;
	}
	else		//for component & SCART-RGB
	{
		ACE_REG_M19Ax_RdFL(adc_dig_79);

		ACE_REG_M19Ax_Rd01(adc_dig_79, ro_vsout_width, *pvs_width);
	}

	return 0;
}

int ADC_M19Ax_Read_HSync_Width(UINT32 *phs_width)
{
	UINT32 h_line_count, h_low_line_count;

	ACE_REG_M19Ax_RdFL(adc_dig_31);
	ACE_REG_M19Ax_Rd01(adc_dig_31, ro_hsprdref, h_line_count);

	ACE_REG_M19Ax_RdFL(adc_dig_33);
	ACE_REG_M19Ax_Rd01(adc_dig_33, ro_hslowref, h_low_line_count);

	if((h_line_count /2) > h_low_line_count)	// Active Low VSync
		*phs_width = h_low_line_count;
	else										// Active High VSync
		*phs_width = h_line_count - h_low_line_count;

	return 0;
}


void ADC_M19Ax_LVDS_Control(int enable)
{
/*
	if(enable > 0)
	{
		ACE_REG_M17C0_RdFL(hslvdstx2_0);
		ACE_REG_M17C0_RdFL(hslvdstx2_1);
		ACE_REG_M17C0_Wr01(hslvdstx2_0, pdb3, 0x1);
		ACE_REG_M17C0_Wr01(hslvdstx2_1, ch_en3, 0x3f);
		ACE_REG_M17C0_WrFL(hslvdstx2_0);
		ACE_REG_M17C0_WrFL(hslvdstx2_1);
	}
	else
	{
		ACE_REG_M17C0_RdFL(hslvdstx2_0);
		ACE_REG_M17C0_RdFL(hslvdstx2_1);
		ACE_REG_M17C0_Wr01(hslvdstx2_0, pdb3, 0x0);
		ACE_REG_M17C0_Wr01(hslvdstx2_1, ch_en3, 0x0);
		ACE_REG_M17C0_WrFL(hslvdstx2_0);
		ACE_REG_M17C0_WrFL(hslvdstx2_1);
	}
*/
	return;
}


void ADC_M19Ax_Set_Blank(int blank_sp)
{
	if(blank_sp > 0)
	{
		ACE_REG_M19Ax_Wr01(adc_dig_203, blank_sp, blank_sp);
		ACE_REG_M19Ax_WrFL(adc_dig_203);
	}
	return;
}


int ADC_M19Ax_Set_Blank_Value(S_BLANK_INFORM *blank_value_t)
{
	int r_blank_high_value, r_blank_low_value;
	int g_blank_high_value, g_blank_low_value;
	int b_blank_high_value, b_blank_low_value;

	r_blank_high_value = blank_value_t->r_blank_target_value + blank_value_t->width + blank_value_t->r_shift_value;
	r_blank_low_value = blank_value_t->r_blank_target_value - blank_value_t->width + blank_value_t->r_shift_value;

	g_blank_high_value = blank_value_t->g_blank_target_value + blank_value_t->width + blank_value_t->g_shift_value;
	g_blank_low_value = blank_value_t->g_blank_target_value - blank_value_t->width + blank_value_t->g_shift_value;

	b_blank_high_value = blank_value_t->b_blank_target_value + blank_value_t->width + blank_value_t->b_shift_value;
	b_blank_low_value = blank_value_t->b_blank_target_value - blank_value_t->width + blank_value_t->b_shift_value;

	ACE_REG_M19Ax_Wr01(adc_dig_206, r_blank_high, r_blank_high_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_206);

	ACE_REG_M19Ax_Wr01(adc_dig_211, g_blank_high, g_blank_high_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_211);

	ACE_REG_M19Ax_Wr01(adc_dig_217, b_blank_high, b_blank_high_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_217);

	ACE_REG_M19Ax_Wr01(adc_dig_208, r_blank_low, r_blank_low_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_208);

	ACE_REG_M19Ax_Wr01(adc_dig_213, g_blank_low, g_blank_low_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_213);

	ACE_REG_M19Ax_Wr01(adc_dig_219, b_blank_low, b_blank_low_value & 0x7FF);
	ACE_REG_M19Ax_WrFL(adc_dig_219);


	return 0;
}

int ADC_M19Ax_Set_DCO_MinMax_Value(UINT8 dco_min, UINT8 dco_max)
{
	//LLPLL_dco_max
	BMC_REG_M19Ax_RdFL(videoafe_10);

	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_dco_max, dco_max);
	BMC_REG_M19Ax_Wr01(videoafe_10, llpll_dco_min, dco_min);

	BMC_REG_M19Ax_WrFL(videoafe_10);

	return 0;
}

int ADC_M19Ax_Get_DCO_MinMax_Value(UINT8 *pdco_min, UINT8 *pdco_max)
{
	//LLPLL_dco_max
	BMC_REG_M19Ax_RdFL(videoafe_10);

	BMC_REG_M19Ax_Rd01(videoafe_10, llpll_dco_max, *pdco_max);
	BMC_REG_M19Ax_Rd01(videoafe_10, llpll_dco_min, *pdco_min);

	return 0;
}

/***
  	Release/Enable Reset of HS-LVDS 0/1
	set reset_enable to '0' to release reset
 ***/
int ADC_M19Ax_LVDS_Reset_Control(int reset_enable)
{
	ADC_DEBUG("%s [%d]\n", __func__, reset_enable);

#ifdef M19_BRINGUP_TMP
	ACE_REG_M17C0_RdFL(soft_reset_04);

	if(reset_enable)
	{
		ACE_REG_M17C0_Wr01(soft_reset_04, swrst_lvds, 0x1);
	}
	else
	{
		ACE_REG_M17C0_Wr01(soft_reset_04, swrst_lvds, 0);
	}

	ACE_REG_M17C0_WrFL(soft_reset_04);
#endif

	return 0;
}

/***
	A-Die HS-LVDS Source Control Function
 ***/
int ADC_M19Ax_LVDS_Src_Control(LX_AFE_LVDS_SRC_CONTROL_T *pLVDS_Control_t)
{
	ADC_DEBUG("%s lvds[%d],power[%d],type[%d],source[%d],mix mode[%d]\n", __func__, pLVDS_Control_t->lvds_sel, pLVDS_Control_t->lvds_power, pLVDS_Control_t->lvds_type, pLVDS_Control_t->lvds_source, pLVDS_Control_t->lvds_mode);

	if(pLVDS_Control_t->lvds_sel != LX_AFE_LVDS0_SEL)
	{
		AFE_ERROR("No LVDS1 channel on H13 A-Die!!!!! [%s][%d]\n", __func__, __LINE__);
		return -1;
	}

	if(pLVDS_Control_t->lvds_mode != LX_AFE_LVDS_MODE_NO_CHANGE)
	{

	}

	if(pLVDS_Control_t->lvds_power != LX_AFE_LVDS_POWER_NO_CHANGE)
	{
		if(pLVDS_Control_t->lvds_sel == LX_AFE_LVDS0_SEL)
		{
		}
		else
		{
			AFE_ERROR("No LVDS1 channel on H13 A-Die!!!!! [%s][%d]\n", __func__, __LINE__);
			/*
			   ACE_REG_M17C0_RdFL(hslvdstx1_0);
			   ACE_REG_M17C0_Wr01(hslvdstx1_0, pdb2, pLVDS_Control_t->lvds_power);
			   ACE_REG_M17C0_WrFL(hslvdstx1_0);
			 */
		}
	}


	if(pLVDS_Control_t->lvds_source == LX_AFE_LVDS_SOURCE_3CH)
	{
	}
	else if(pLVDS_Control_t->lvds_source == LX_AFE_LVDS_SOURCE_CVD) {
	}
	else if(pLVDS_Control_t->lvds_source != LX_AFE_LVDS_SOURCE_NO_CHANGE)
		AFE_ERROR("Invalid LVDS Source Selection [%d] H13 A-Die!!!!! [%s][%d]\n", pLVDS_Control_t->lvds_source, __func__, __LINE__);

	/*
	if(pLVDS_Control_t->lvds_mode == LX_AFE_LVDS_MODE_NORMAL)
		ACE_REG_M17C0_Wr01(data_bridge_2, lvds_selection2, 0);
	else
		ACE_REG_M17C0_Wr01(data_bridge_2, lvds_selection2, 1);
		*/

	return 0;
}

int ADC_M19Ax_Read_APA_Intr(void)
{
	int ret;

	ACE_REG_M19Ax_RdFL(m19_3ch_intr_02);
	ACE_REG_M19Ax_Rd01(m19_3ch_intr_02, intr_adc3ch_apa_complete_cro, ret);

	return ret;
}

int ADC_M19Ax_Clear_APA_Intr(void)
{
	ACE_REG_M19Ax_RdFL(m19_3ch_intr_02);
	ACE_REG_M19Ax_Wr01(m19_3ch_intr_02, intr_adc3ch_apa_complete_cro, 1);
	ACE_REG_M19Ax_WrFL(m19_3ch_intr_02);

	return 0;
}

int ADC_M19Ax_Enable_APA_Intr(void)
{
	ACE_REG_M19Ax_RdFL(m19_3ch_intr_en_02);
	ACE_REG_M19Ax_Wr01(m19_3ch_intr_en_02, enable_intr_adc3ch_apa_complete, 1);
	ACE_REG_M19Ax_WrFL(m19_3ch_intr_en_02);

	return 0;
}

int ADC_M19Ax_Disable_APA_Intr(void)
{
	ACE_REG_M19Ax_RdFL(m19_3ch_intr_en_02);
	ACE_REG_M19Ax_Wr01(m19_3ch_intr_en_02, enable_intr_adc3ch_apa_complete, 0);
	ACE_REG_M19Ax_WrFL(m19_3ch_intr_en_02);

	return 0;
}

int ADC_M19Ax_Component_APA(int iIndex)
{

	int iPhaseMax, Phase_Result, Phase_Compare;
	int Prev_Phase_Result = 0xffffffff;
	int repeat = 0;
	int check_count = 0;
	int same_count = 0;
	int apa_array[APA_LOOP_COUNT];

	ADC_APA_DEBUG("%s entered \n", __func__);

	if( (iIndex < 0) || (iIndex >= PARAM_NUM) )
		return -1;

	if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
	{
									// Do not execute APA on 480i/480p inputs
		if( (gADC_APA_Enable == 1) && (TB_WIDTH[iIndex] > 720) )
		{
			OS_MsecSleep(gADC_APA_Delay);

			ADC_APA_DEBUG("%s msec sleep[%d] \n", __func__, gADC_APA_Delay);

			for(;repeat < APA_LOOP_COUNT;repeat++)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_240);
				ACE_REG_M19Ax_Wr01(adc_dig_240, apa_enable, 0);
				ACE_REG_M19Ax_WrFL(adc_dig_240);

				//120103 wonsik.do : removed floating point in kernel driver
				iPhaseMax = (1000000000 / (TB_FS[iIndex] * 130) +2); //0918 by powerory
				ADC_M19Ax_Reset_Digital();
//				ADC_DEBUG("%s PhaseMax [0x%x] \n",__func__, iPhaseMax);

				//111123 wonsik.do
				ACE_REG_M19Ax_RdFL(adc_dig_255);
				ACE_REG_M19Ax_Wr01(adc_dig_255, apa_sampling_counter_max, 0x3);
				ACE_REG_M19Ax_WrFL(adc_dig_255);

				ACE_REG_M19Ax_RdFL(adc_dig_253);
				ACE_REG_M19Ax_Wr01(adc_dig_253, apa_hsfal_offset, 0x81);
				ACE_REG_M19Ax_WrFL(adc_dig_253);

				ACE_REG_M19Ax_RdFL(adc_dig_254);
				ACE_REG_M19Ax_Wr01(adc_dig_254, apa_pos_offset, 0xC);	// restore default value
				ACE_REG_M19Ax_WrFL(adc_dig_254);

				ACE_REG_M19Ax_Wr01(adc_dig_250, apa_hsfal_thr, 0x80);	//default value
				ACE_REG_M19Ax_WrFL(adc_dig_250);

				ACE_REG_M19Ax_RdFL(adc_dig_257);
				ACE_REG_M19Ax_Wr01(adc_dig_257, apa_phase_max, iPhaseMax & 0x3FF);
				ACE_REG_M19Ax_WrFL(adc_dig_257);

				ACE_REG_M19Ax_RdFL(adc_dig_294);
				ACE_REG_M19Ax_Wr01(adc_dig_294, llpll_shift_sel, 0);
				ACE_REG_M19Ax_WrFL(adc_dig_294);

				ADC_M19Ax_Disable_APA_Intr();
				ADC_M19Ax_Clear_APA_Intr();

				OS_MsecSleep(30);

				ACE_REG_M19Ax_RdFL(adc_dig_240);
				ACE_REG_M19Ax_Wr01(adc_dig_240, apa_enable, 1);
				ACE_REG_M19Ax_WrFL(adc_dig_240);

				OS_MsecSleep(5);

				ADC_M19Ax_Enable_APA_Intr();

				//				OS_MsecSleep(100);
				for(check_count = 0;check_count < 50;check_count++) {
					if(ADC_M19Ax_Read_APA_Intr() > 0)
					{
						if(check_count == 0)
						{
							AFE_PRINT("APA done too fast ???\n");
							OS_MsecSleep(50);
						}
						break;
					}

					OS_MsecSleep(5);

				}

				ADC_M19Ax_Disable_APA_Intr();
				ADC_M19Ax_Clear_APA_Intr();

				ADC_APA_DEBUG("APA Done in [%d]msec\n", check_count*5);

				ACE_REG_M19Ax_RdFL(adc_dig_266);

				ACE_REG_M19Ax_Rd01(adc_dig_266, apa_phase1_ro, Phase_Result);

				ADC_APA_DEBUG("repeat[%d] Phase Result[0x%x], Phase Max[0x%x]\n", repeat, Phase_Result, iPhaseMax);

				if(abs(Phase_Result - Prev_Phase_Result) <= 1)
				{
					ADC_APA_DEBUG("Same with Prev Phase value \n");
					same_count++;
				}
				else
					same_count = 0;

				apa_array[repeat] = Phase_Result;

				Prev_Phase_Result = Phase_Result;

				if(gADC_APA_Enable_Print)
				{
					UINT32 debug_value;

					ACE_REG_M19Ax_RdFL(adc_dig_249);
					ACE_REG_M19Ax_Rd01(adc_dig_249, apa_blank_avg_ro, debug_value);
					ADC_APA_DEBUG("apa_blank_avg_ro = 	[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_266);
					ACE_REG_M19Ax_Rd01(adc_dig_266, apa_phase1_ro, debug_value);
					ADC_APA_DEBUG("apa_phase1_ro =		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_264);
					ACE_REG_M19Ax_Rd01(adc_dig_264, apa_data1_ro, debug_value);
					ADC_APA_DEBUG("apa_data1_ro = 		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_267);
					ACE_REG_M19Ax_Rd01(adc_dig_267, apa_pos1_ro, debug_value);
					ADC_APA_DEBUG("apa_pos1_ro = 		[0x%x]\n", debug_value);

					ACE_REG_M19Ax_RdFL(adc_dig_271);
					ACE_REG_M19Ax_Rd01(adc_dig_271, apa_phase2_ro, debug_value);
					ADC_APA_DEBUG("apa_phase2_ro =		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_269);
					ACE_REG_M19Ax_Rd01(adc_dig_269, apa_data2_ro, debug_value);
					ADC_APA_DEBUG("apa_data2_ro = 		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_272);
					ACE_REG_M19Ax_Rd01(adc_dig_272, apa_pos2_ro, debug_value);
					ADC_APA_DEBUG("apa_pos2_ro = 		[0x%x]\n", debug_value);

					ACE_REG_M19Ax_RdFL(adc_dig_276);
					ACE_REG_M19Ax_Rd01(adc_dig_276, apa_phase3_ro, debug_value);
					ADC_APA_DEBUG("apa_phase3_ro =		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_274);
					ACE_REG_M19Ax_Rd01(adc_dig_274, apa_data3_ro, debug_value);
					ADC_APA_DEBUG("apa_data3_ro = 		[0x%x]\n", debug_value);
					ACE_REG_M19Ax_RdFL(adc_dig_277);
					ACE_REG_M19Ax_Rd01(adc_dig_277, apa_pos3_ro, debug_value);
					ADC_APA_DEBUG("apa_pos3_ro = 		[0x%x]\n", debug_value);

				}
				if(same_count >= gADC_APA_Same_Count)
					break;
			}

#ifndef ENHANCED_IFM_SPEED_MODE
			if(repeat == APA_LOOP_COUNT)
			{
				Phase_Result = ( apa_array[APA_LOOP_COUNT-1] + apa_array[APA_LOOP_COUNT-2] + apa_array[APA_LOOP_COUNT-3] + apa_array[APA_LOOP_COUNT-4] ) >> 2;
				ADC_APA_DEBUG("Apa value not conversed, use average value [0x%x] <= [0x%x],[0x%x],[0x%x],[0x%x]", Phase_Result, apa_array[APA_LOOP_COUNT-1] , apa_array[APA_LOOP_COUNT-2] , apa_array[APA_LOOP_COUNT-3] , apa_array[APA_LOOP_COUNT-4] );
			}
#endif

			ACE_REG_M19Ax_RdFL(adc_dig_264);
			ACE_REG_M19Ax_Rd01(adc_dig_264, apa_data1_ro, Phase_Compare);

			if(Phase_Result != Phase_Compare)
				ADC_APA_DEBUG("\n ###### Phase Result DIFF [0x%x]!=[0x%x] ######\n", Phase_Compare, Phase_Result);

			ACE_REG_M19Ax_RdFL(adc_dig_264);
			ACE_REG_M19Ax_Wr01(adc_dig_294, llpll_shift_sel, 1);
			ACE_REG_M19Ax_WrFL(adc_dig_294);

			// for 1080P 50/60Hz
			//120103 wonsik.do : removed floating point in kernel driver
			if( TB_FS[iIndex] > 100000)
			{
				/*
				if(0) {
					if(Phase_Result >= 2)
						Phase_Result -= 2;
				}
				else {
					if(Phase_Result >= 4)
						Phase_Result -= 4;
				}
				*/

				if(g_comp_vsout_sel == 1)
				{
					if(gResolution == 69) {	// for 1080P 50Hz : to avoid blinking picture when APA phase "0x1d" 
						if( (Phase_Result > 0x13) && (Phase_Result < 0x20) )
							Phase_Result = 0x13;
						ADC_APA_DEBUG("1080P 50Hz set Phase_Result[0x%x]\n", Phase_Result);
					}
				}
			}
#if 1	//180717
			else if(gResolution == 63) {	// for 720P 50Hz : to avoid blinking picture when APA phase "0x48~0x4b" 
				if(Phase_Result >= 0x34)	// half of phase max
					Phase_Result = 0x0;
				ADC_APA_DEBUG("720P 50Hz set Phase_Result[0x%x]\n", Phase_Result);
			}
#endif
			else
			{
				if(Phase_Result >= iPhaseMax/6)
				{
					Phase_Result -= iPhaseMax/6;

				}
				else
				{
					if(gResolution == 67)
					{
						ADC_APA_DEBUG("1080P 24Hz for HVP-3060 Phase adjust : Phase_Result[0x%x]\n", Phase_Result);
					}
					else
						Phase_Result = iPhaseMax + Phase_Result - iPhaseMax/6;
				}

				if(g_comp_vsout_sel == 1)
				{
					if(gResolution == 67)	// for 1080P 24Hz : to avoid blinking picture when APA phase around "0x4a"
					{
						if(Phase_Result >= 0x34)	// half of phase max
							Phase_Result = 0x0;
						ADC_APA_DEBUG("1080P 24Hz for MSPG Phase adjust  : Phase_Result[0x%x]\n", Phase_Result);
					}
					else if(gResolution == 68)
					{
						if(Phase_Result >= 0x34)	// half of phase max
							Phase_Result = 0x0;
						ADC_APA_DEBUG("1080P 30Hz for MSPG Phase adjust  : Phase_Result[0x%x]\n", Phase_Result);
					}
					else if(gResolution == 84) // for 1080P 25Hz : to avoid blinking picture when APA phase around "0x4a"
					{
						if(Phase_Result >= 0x34)	// half of phase max
							Phase_Result = 0x0;
						ADC_APA_DEBUG("1080P 25Hz for MSPG Phase adjust  : Phase_Result[0x%x]\n", Phase_Result);
					}
				}
			}
			AFE_PRINT("APA : Calculated Phase Result =[0x%x] \n", Phase_Result);

			ADC_SetPhaseValue(Phase_Result); // by dws

			ACE_REG_M19Ax_Wr01(adc_dig_240, apa_enable, 0);
			ACE_REG_M19Ax_WrFL(adc_dig_240);

		}
		else
		{
			ADC_APA_DEBUG("%s Do not execute APA \n", __func__);
			ACE_REG_M19Ax_RdFL(adc_dig_264);
			ACE_REG_M19Ax_Wr01(adc_dig_294, llpll_shift_sel, 1);
			ACE_REG_M19Ax_WrFL(adc_dig_294);

			ADC_M19Ax_Reset_Digital();

			if(gResolution >= 0)
				ADC_SetPhaseValue((gPCTable+gResolution)->u16_ADC_Phase); // by dws
		}

	}
	else
	{
		ACE_REG_M19Ax_RdFL(adc_dig_264);
		ACE_REG_M19Ax_Wr01(adc_dig_294, llpll_shift_sel, 1);
		ACE_REG_M19Ax_WrFL(adc_dig_294);
	}

	return 0;
}

int ADC_M19Ax_Component_APA_Test(UINT32 ADC_APA_Delay, UINT32 ADC_APA_Enable, UINT32 ADC_APA_Same_Count, UINT32 ADC_APA_Execute, UINT32 ADC_APA_Enable_Print)
{
	if(ADC_APA_Execute)
	{
		ADC_APA_Enable = 1;

		if(gResolution >= 0)
			ADC_M19Ax_Component_APA(ConvertTable[gResolution]);
	}
	else
	{
		gADC_APA_Delay = ADC_APA_Delay;
		gADC_APA_Enable = ADC_APA_Enable;
		gADC_APA_Same_Count = ADC_APA_Same_Count;
		gADC_APA_Enable_Print = ADC_APA_Enable_Print;
	}
	return 0;
}

int ADC_M19Ax_Get_Vtotal_Value(void)
{
	int Vline = 0;
	ACE_REG_M19Ax_RdFL(adc_dig_35);
	ACE_REG_M19Ax_Rd01(adc_dig_35, ro_vsprdref, Vline);
	return Vline;
}

int ADC_M19Ax_Set_Sync_Mode(ADC_SYNC_MODE sync_mode)
{
	int ret = 0;

	ret = OS_LockMutex(&g_ADC_Sema);

	if(sync_mode == ADC_COMPOSITE_SYNC_MODE)
	{
		ADC_DEBUG("ADC Composite Sync Mode\n");
		ACE_REG_M19Ax_RdFL(adc_dig_22);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_22);

		g_ADC_Sync_Mode = ADC_COMPOSITE_SYNC_MODE;
	}
	else if (sync_mode == ADC_SEPERATED_SYNC_MODE)
	{
		ADC_DEBUG("ADC Seperated Sync Mode\n");
		ACE_REG_M19Ax_RdFL(adc_dig_22);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compover, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_22, compuser, 0x0);
		ACE_REG_M19Ax_WrFL(adc_dig_22);

		g_ADC_Sync_Mode = ADC_SEPERATED_SYNC_MODE;
	}
	else
		ret = -1;

	OS_UnlockMutex(&g_ADC_Sema);

	return ret;
}

int ADC_M19Ax_Mute_Control(ADC_MUTE_CTRL adc_mute_control)
{
	int ret = 0;

	ACE_REG_M19Ax_RdFL(adc_dig_230);

	switch(adc_mute_control)
	{
		case ADC_MUTE_CTRL_NORMAL:
			ACE_REG_M19Ax_Wr01(adc_dig_230, mute_ctrl, 0x0);
			break;

		case ADC_MUTE_CTRL_MUTE:
			ACE_REG_M19Ax_Wr01(adc_dig_230, mute_ctrl, 0x1);
			break;

		case ADC_MUTE_CTRL_AUTO:
			ACE_REG_M19Ax_Wr01(adc_dig_230, mute_ctrl, 0x2);
			break;

		default:
				ret = -1;
			break;
	}

	ACE_REG_M19Ax_WrFL(adc_dig_230);

	ADC_DEBUG("%s entered with value [%d]\n", __func__, adc_mute_control);

	return ret;
}

int ADC_M19Ax_Read_AGOC_State(void)
{
	UINT32 aogc_state;

	ACE_REG_M19Ax_RdFL(adc_dig_101);
	ACE_REG_M19Ax_Rd01(adc_dig_101, ro_aogc_state, aogc_state);
	return aogc_state;

}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_M19Ax_Enable_Sync_Low_Level_Read(int enable)
{
	if(enable)
	{
		ACE_REG_M19Ax_Wr01(adc_dig_255, apa_sampling_counter_max, 0x2);
		ACE_REG_M19Ax_WrFL(adc_dig_255);

		ACE_REG_M19Ax_Wr01(adc_dig_253, apa_hsfal_offset, 0x8);
		ACE_REG_M19Ax_WrFL(adc_dig_253);

		ACE_REG_M19Ax_RdFL(adc_dig_254);
		ACE_REG_M19Ax_Wr01(adc_dig_254, apa_pos_offset, 0x0);	//default 0x0C : bug fix sync low level read 0x0 
		ACE_REG_M19Ax_WrFL(adc_dig_254);

		ACE_REG_M19Ax_Wr01(adc_dig_250, apa_hsfal_thr, 0x00);	//default 0x80 : shibasoku low sync level test
		ACE_REG_M19Ax_WrFL(adc_dig_250);

		ACE_REG_M19Ax_Wr01(adc_dig_257, apa_phase_max, 0x1);
		ACE_REG_M19Ax_WrFL(adc_dig_257);

		//apa_phase_step : 0x1 : default

#if 0
		ACE_REG_M19Ax_RdFL(adc_dig_89);
		ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_src_sel, 0x1);
		ACE_REG_M19Ax_Wr01(adc_dig_89, aogc_enable_sel, 0x2);
		ACE_REG_M19Ax_WrFL(adc_dig_89);

		ACE_REG_M19Ax_RdFL(adc_dig_99);
		ACE_REG_M19Ax_RdFL(adc_dig_100);
		ACE_REG_M19Ax_Wr01(adc_dig_99, aogc_counter_max_1, 0x00);
		ACE_REG_M19Ax_Wr01(adc_dig_100, aogc_counter_max_0, 0x02);
		ACE_REG_M19Ax_WrFL(adc_dig_99);
		ACE_REG_M19Ax_WrFL(adc_dig_100);

		ACE_REG_M19Ax_RdFL(adc_dig_98);
		ACE_REG_M19Ax_Wr01(adc_dig_98, aogc_sample_count, 0x3);
		ACE_REG_M19Ax_WrFL(adc_dig_98);

		ACE_REG_M19Ax_RdFL(adc_dig_98);
		ACE_REG_M19Ax_Wr01(adc_dig_98, aogc_sample_accum, 0);
		ACE_REG_M19Ax_WrFL(adc_dig_98);
#endif
		OS_MsecSleep(5);

		//added 130104 : apa reset needed???
		ADC_M19Ax_Reset_Digital();
	}
	return 0;
}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_M19Ax_Read_Sync_Low_Level(void)
{
	int level;

	ACE_REG_M19Ax_Wr01(adc_dig_240, apa_enable, 1);
	ACE_REG_M19Ax_WrFL(adc_dig_240);
	OS_MsecSleep(5);

	ACE_REG_M19Ax_RdFL(adc_dig_264);
	ACE_REG_M19Ax_Rd01(adc_dig_264, apa_data1_ro, level);

//	ADC_DEBUG("apa_data1_ro = 		[0x%x]\n", level);

	ACE_REG_M19Ax_Wr01(adc_dig_240, apa_enable, 0);
	ACE_REG_M19Ax_WrFL(adc_dig_240);

	return level;
}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_M19Ax_Post_Gain_Control(int percent)
{
	int G_Gain;

//	ACE_REG_M19Ax_RdFL(adc_dig_8);
//	ACE_REG_M19Ax_RdFL(adc_dig_9);
//	G_Gain = gadc_dig_8.g_gain_1 << 8 | gadc_dig_9.g_gain_0;

	//120103 wonsik.do : removed floating point in kernel driver
	//G_Gain = 0x1000 * (percent / 100.0);
	G_Gain = (0x1000 * percent) / 100;

	ADC_DEBUG("%s entered with value [0x%x]\n", __func__, G_Gain);

	ACE_REG_M19Ax_Wr01(adc_dig_09, g_gain, (G_Gain) & 0x3FFF);
	ACE_REG_M19Ax_WrFL(adc_dig_09);

	return 0;
}

int ADC_M19Ax_Get_Post_Gain_Value(void)
{
	int G_Gain;

	ACE_REG_M19Ax_RdFL(adc_dig_09);
	ACE_REG_M19Ax_Rd01(adc_dig_09, g_gain, G_Gain);

	return G_Gain;
}

int ADC_M19Ax_LVDS_Channel_Enable_Control(int enable)
{
	return 0;
}

/**
 * @brief set component SOG parameter settings
 *
 * @param width			: picture width
 * @param progressive	: interlace(0) or progressive(1)
 *
 * @return 
 */
int ADC_M19Ax_Set_Comp_Params(int width, int progressive, int v_freq)
{
	int ret = 0;
	S_RGB_POSITION rgb_pos;
	S_RGB_SIZE rgb_size;

	ADC_DEBUG("%s entered with width value [%d], adc_type[%d]\n", __func__, width, gADC_type);

	if( gADC_type == LX_ADC_INPUT_SOURCE_RGB_SCART) {

		//480i, 576i
		ADC_M19Ax_Set_Blank(0x20);

		//150405 : use feedback sync for SCART
		//120207 : use internal hsync for 480/576 I/P Component
		ADC_M19Ax_Set_Hsync_Sel(1);

		BMC_REG_M19Ax_RdFL(videoafe_01);
		//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
		BMC_REG_M19Ax_WrFL(videoafe_01);

		ADC_M19Ax_SetCurrent(2);

		//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
		ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
		ACE_REG_M19Ax_WrFL(adc_dig_220);
	}
	else if(width < 1024) {
		if(progressive < 1) {

			//480i, 576i

			//0x1a/0x26
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
			BMC_REG_M19Ax_WrFL(videoafe_01);
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x5); //227 timing bending 0x7=>0x5	//shibasoku unstable sync	//nintendo Wii stable sync
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//0x1a/0x27
			BMC_REG_M19Ax_RdFL(videoafe_04);
			//BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x3);	 
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x1);		// 150713 : sync level 33% 
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
			BMC_REG_M19Ax_WrFL(videoafe_04);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x7);
			BMC_REG_M19Ax_WrFL(videoafe_03);

			//0x1b/0x50
			BMC_REG_M19Ax_RdFL(videoafe_00);
	//		BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
	//		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_00);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x2);		// 151002 : sync level 33% test
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//150405 : use feedback sync for 480/576i
			//120207 : use internal hsync for 480/576 I/P Component
			ADC_M19Ax_Set_Hsync_Sel(1);

			// 111123 wonsik.do : for post gain control for 110% white saturation test.
			//ADC_M19Ax_Enable_Sync_Low_Level_Read(1);

			/* 141007 : Add Pixel Value Read Workaround for sync_level zero condition */
			rgb_pos.width_r = 730;
			rgb_pos.width_g = 730;
			rgb_pos.width_b = 730;
			rgb_pos.height_r = 20;
			rgb_pos.height_g = 20;
			rgb_pos.height_b = 20;
			// blank area setting

			rgb_size.width_r = 45;
			rgb_size.width_g = 45;
			rgb_size.width_b = 45;
			rgb_size.height_r = 200;
			rgb_size.height_g = 200;
			rgb_size.height_b = 200;

			ADC_M19Ax_SetRGBSize(&rgb_size);
			ADC_M19Ax_SetRGBPosition(&rgb_pos);

			// 131122 wonsik.do : soglvl to 0x5 for sync level 33% test (H13 UD)
			// 180502 wonsik.do : M19 soglvl 0x8 meets sync level 28% test
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x8);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//ADC_M19Ax_Set_Blank(0x30);	//For MSPG 1025D 480i
			//ADC_M19Ax_Set_Blank(0x2B);	//For MSPG-6000 , M16
			ADC_M19Ax_Set_Blank(0x10);	// vertical var noise left side

			BMC_REG_M19Ax_RdFL(videoafe_01);
		//	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);	//227 timing bending 0x2=>0x1
		//	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);	//150713 : sync level 33%
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_03);
			//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150825 : M16 Comp Noise
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x1);	//151030 : M16 Comp Noise
			BMC_REG_M19Ax_WrFL(videoafe_03);

			//ADC_M19Ax_SetCurrent(0);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_03);

			ACE_REG_M19Ax_RdFL(adc_dig_296);
			ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
			ACE_REG_M19Ax_WrFL(adc_dig_296);
			
			if(g_comp_vsout_sel == 0)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_61);
				ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
				ACE_REG_M19Ax_WrFL(adc_dig_61);
			}
		}
		else {
			//480p, 576p
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
			BMC_REG_M19Ax_WrFL(videoafe_01);
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x4);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_04);
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x3);	 
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
			BMC_REG_M19Ax_WrFL(videoafe_04);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x7);
			BMC_REG_M19Ax_WrFL(videoafe_03);

			BMC_REG_M19Ax_RdFL(videoafe_00);
			//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
	//		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);		//160610 : M17 1080P black video //141017 : TViX S1 sync unstable
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_00);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x2);		// 161005 : 480P->1080i invalid format fix
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//150405 : use feedback sync for 480/576P
			//120207 : use internal hsync for 480/576 I/P Component
			ADC_M19Ax_Set_Hsync_Sel(1);

			// 131122 wonsik.do : soglvl to 0x5 for sync level 33% test (H13 UD)
			// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			ADC_M19Ax_Set_Blank(0x10);	// vertical var noise left side

			BMC_REG_M19Ax_RdFL(videoafe_01);
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x2);	//150825 : M16 Comp Noise
			BMC_REG_M19Ax_WrFL(videoafe_03);

			//ADC_M19Ax_SetCurrent(0);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_03);

			ACE_REG_M19Ax_RdFL(adc_dig_296);
			ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
			ACE_REG_M19Ax_WrFL(adc_dig_296);

			if(g_comp_vsout_sel == 0)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_61);
				ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
				ACE_REG_M19Ax_WrFL(adc_dig_61);
			}
		}

		//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
		ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
		ACE_REG_M19Ax_WrFL(adc_dig_220);
	}
	else if (width < 1500) {
		//720P
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
		BMC_REG_M19Ax_WrFL(videoafe_01);
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x4);
		BMC_REG_M19Ax_WrFL(videoafe_01);

		BMC_REG_M19Ax_RdFL(videoafe_04);
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x3);	 
		BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
		BMC_REG_M19Ax_WrFL(videoafe_04);
		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x4);
		BMC_REG_M19Ax_WrFL(videoafe_03);

		BMC_REG_M19Ax_RdFL(videoafe_00);
		//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_fil, 0x2);		//bending top screen
		//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
//		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
		//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_datack, 0x0);
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);	//modified 130130 : MSPG-7100 720P (215 timing)
		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_00);

		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x2);		//150429 : 1line on/off
		BMC_REG_M19Ax_WrFL(videoafe_01);

		//120207 : use feedback hsync for 720P/1080IP Component Video
		ADC_M19Ax_Set_Hsync_Sel(1);

		// 131122 wonsik.do : soglvl to 0x5 for sync level 33% test (H13 UD)
		// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
		BMC_REG_M19Ax_RdFL(videoafe_01);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
		BMC_REG_M19Ax_WrFL(videoafe_01);

		ADC_M19Ax_Set_Blank(0x40);

		BMC_REG_M19Ax_RdFL(videoafe_01);
	//	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
		BMC_REG_M19Ax_WrFL(videoafe_01);

		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150825 : M16 Comp Noise
		BMC_REG_M19Ax_WrFL(videoafe_03);

		//ADC_M19Ax_SetCurrent(2);
		BMC_REG_M19Ax_RdFL(videoafe_03);
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//180717 : modified for FT low voltage test (from 0x3)
		BMC_REG_M19Ax_WrFL(videoafe_03);

		ACE_REG_M19Ax_RdFL(adc_dig_296);
		ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x1ff);	//181001 : fix unstable sync (0x10)
		ACE_REG_M19Ax_WrFL(adc_dig_296);
		
		if(g_comp_vsout_sel == 0)
		{
			//170810 : 720P 60Hz/50Hz vertical shift using vsout_sel '0'
			ACE_REG_M19Ax_RdFL(adc_dig_61);
			ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
			ACE_REG_M19Ax_WrFL(adc_dig_61);
		}

		//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
		ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
		ACE_REG_M19Ax_WrFL(adc_dig_220);
	}
	else {
		if(progressive < 1) {

			//1080i

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
			BMC_REG_M19Ax_WrFL(videoafe_01);
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x3);	//M16P
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_04);
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x1);	//150506 
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
			BMC_REG_M19Ax_WrFL(videoafe_04);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x4); //M16P	//150825 from '0' //150506
			BMC_REG_M19Ax_WrFL(videoafe_03);

			BMC_REG_M19Ax_RdFL(videoafe_00);
			//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
//			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);	//130215 : use data clock
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_00);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x1); //M16P	// for APA //0x3 for 1-line on/off pattern
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//120207 : use feedback hsync for 720P/1080IP Component Video
			ADC_M19Ax_Set_Hsync_Sel(1);

			// 131122 wonsik.do : soglvl to 0x5 for sync level 33% test (H13 UD)
			// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			ADC_M19Ax_Set_Blank(0x40);

			BMC_REG_M19Ax_RdFL(videoafe_01);
		//	BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
	//		BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x3);	//150429 : for 1line on/off pattern
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150825 : M16 Comp Noise
			BMC_REG_M19Ax_WrFL(videoafe_03);

		//	ADC_M19Ax_SetCurrent(2);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//180717 : modified for FT low voltage test (from 0x3)
			BMC_REG_M19Ax_WrFL(videoafe_03);

			ACE_REG_M19Ax_RdFL(adc_dig_296);
			ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x0);
			ACE_REG_M19Ax_WrFL(adc_dig_296);
			
			if(g_comp_vsout_sel == 0)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_61);
				ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x1);
				ACE_REG_M19Ax_WrFL(adc_dig_61);
			}

			//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
			ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
			ACE_REG_M19Ax_WrFL(adc_dig_220);
		}
		else if(v_freq < 40000) {

			//1080P 24/25/30Hz
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
			BMC_REG_M19Ax_WrFL(videoafe_01);
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x4);	//Modified for Master Distributer (from 0x0)
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_04);
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x1);	 // 1-line on/off pattern 150511
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
			BMC_REG_M19Ax_WrFL(videoafe_04);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x4); //M16P	// Noise issue 151125 // 1-line on/off pattern 150511
			BMC_REG_M19Ax_WrFL(videoafe_03);

			BMC_REG_M19Ax_RdFL(videoafe_00);
			//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
	//		BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);	//130215 : use data clock
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_00);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x1);	// for APA //0x3 for 1-line on/off pattern
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//120207 : use feedback hsync for 720P/1080IP Component Video
			ADC_M19Ax_Set_Hsync_Sel(1);

			// 131122 wonsik.do : soglvl to 0x5 for sync level 33% test (H13 UD)
			// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			ADC_M19Ax_Set_Blank(0x40);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x1);
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x3); //M16P	//150511 : 1-line on/off pattern
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150825 : M16 Comp Noise
			BMC_REG_M19Ax_WrFL(videoafe_03);

			//ADC_M19Ax_SetCurrent(2);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//180717 : modified for FT low voltage test (from 0x3)
			BMC_REG_M19Ax_WrFL(videoafe_03);

			ACE_REG_M19Ax_RdFL(adc_dig_296);
			ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x1ff);	//181001 : fix unstable sync (0x10)
			ACE_REG_M19Ax_WrFL(adc_dig_296);

			if(g_comp_vsout_sel == 0)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_61);
				ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x0);
				ACE_REG_M19Ax_WrFL(adc_dig_61);
			}

			//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
			ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x14);
			ACE_REG_M19Ax_WrFL(adc_dig_220);
		}

		else {

			//1080P 50/60Hz
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_bw, 0x3);
			BMC_REG_M19Ax_WrFL(videoafe_01);
			BMC_REG_M19Ax_RdFL(videoafe_01);
//			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x4);	//Modified for Master Distributer (from 0x0)
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x0);	// for APA	//1-line on/off pattern 150511
//			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_fil, 0x2);	// for 1080P 50Hz phase(0x22) sync unstable 160615
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_04);
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_deglitch, 0x1);	// 150506 for 1080P
			BMC_REG_M19Ax_Wr01(videoafe_04, videoafe_sog_enwin, 0x1);
			BMC_REG_M19Ax_WrFL(videoafe_04);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, 0x2);	//M16++ better phase noise (0x3=>0x2)
			BMC_REG_M19Ax_WrFL(videoafe_03);

			BMC_REG_M19Ax_RdFL(videoafe_00);
			//BMC_REG_M19Ax_Wr01(afe_3ch_8, videoafe_sel_bg, 0x0);
			//BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_invdatack, 0x0);	//160610 : M17 1080P black video
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_datack, 0x1);	//130215 : MSPG-6100 1080P 50Hz(time:224) sync unstable at phase 0xe
			BMC_REG_M19Ax_Wr01(videoafe_00, videoafe_sel_fs, 0x0);
			BMC_REG_M19Ax_WrFL(videoafe_00);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_ssfil, 0x0);// for APA	//0x3 for 1-line on/off pattern
			BMC_REG_M19Ax_WrFL(videoafe_01);

			//120207 : use feedback hsync for 720P/1080IP Component Video
			ADC_M19Ax_Set_Hsync_Sel(1);

			// 180502 wonsik.do : soglvl to 0x7 to prevent hsoutprd '1' error
			BMC_REG_M19Ax_RdFL(videoafe_01);
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_soglvl, 0x9);
			BMC_REG_M19Ax_WrFL(videoafe_01);

			ADC_M19Ax_Set_Blank(0x40);

			BMC_REG_M19Ax_RdFL(videoafe_01);
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x2);	// QE 1080P htotal one issue : 130221
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//150421 : M16
			//BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x2);	//150511 : 1-line on/off pattern
			BMC_REG_M19Ax_Wr01(videoafe_01, videoafe_sog_sinki, 0x4);	//160616 : unstable phase
			BMC_REG_M19Ax_WrFL(videoafe_01);

			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_clpcur, 0x4);	//150825 : M16 Comp Noise
			BMC_REG_M19Ax_WrFL(videoafe_03);

			//ADC_M19Ax_SetCurrent(2);
			BMC_REG_M19Ax_RdFL(videoafe_03);
			BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x2);	//180717 : modified for FT low voltage test (from 0x4)
			BMC_REG_M19Ax_WrFL(videoafe_03);

			ACE_REG_M19Ax_RdFL(adc_dig_296);
			ACE_REG_M19Ax_Wr01(adc_dig_296, hslowdelta_in, 0x1ff);	//181001 : fix unstable sync (0x10)
			ACE_REG_M19Ax_WrFL(adc_dig_296);
			
			if(g_comp_vsout_sel == 0)
			{
				ACE_REG_M19Ax_RdFL(adc_dig_61);
				ACE_REG_M19Ax_Wr01(adc_dig_61, vsout_sel, 0x0);
				ACE_REG_M19Ax_WrFL(adc_dig_61);
			}

			//180618 : 1080P 50/60Hz, prevent low voltage blue turn off
			ACE_REG_M19Ax_Wr01(adc_dig_220, clamp_width, 0x24);
			ACE_REG_M19Ax_WrFL(adc_dig_220);
		}
	}

	return ret;
}


/**
 * @brief Read A-Die Register Value
 *
 * @param addr
 * @param value
 *
 * @return 
 */
int ADC_M19Ax_Read_ACE_Reg(UINT32 addr , UINT32 *value)
{
	int ret = RET_OK;

	void * recvAddr;
	void * currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;

	do {
		recvAddr = (void *)(uintptr_t)addr;

		recvAddr += (uintptr_t)gMIP_DIG_CTRL_M19.phys.addr;

		currAddr = recvAddr;
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);
		*value = REG_RD(currAddr);
		if (currAddr == recvAddr) break;
		nextValue = REG_RD(currAddr+4);
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		*value  = GET_BITS(*value, dBit, wBit);
		*value += GET_PVAL(nextValue, wBit, dBit);

	} while (0);

	return ret;
}

/**
 * @brief Write data to A-Die Register
 *
 * @param addr
 * @param value
 *
 * @return 
 */
int ADC_M19Ax_Write_ACE_Reg(UINT32 addr , UINT32 value)
{
	void * recvAddr;
	void * currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;

	do {

		recvAddr = (void *)(uintptr_t)addr;
		recvAddr += (uintptr_t)gMIP_DIG_CTRL_M19.phys.addr;

		currAddr = recvAddr;
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);
		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);
		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(currAddr		,currValue);
		REG_WD((currAddr+4) ,nextValue);
	} while (0);
	return 0;
}

int ADC_M19Ax_Get_Line_Count(UINT32 *pLineCount)
{

	ACE_REG_M19Ax_RdFL(adc_dig_35);
	ACE_REG_M19Ax_Rd01(adc_dig_35, ro_vsprdref, *pLineCount);

	return 0;
}

int ADC_M19Ax_Read_ACE_GPIO(UINT32 *pGPIO_Status)
{

	return 0;
}

int ADC_M19Ax_Component_Set_CP_Params(int kadp_index)
{
	LX_AFE_ADC_GAIN_VALUE_T mod_gain_value;

	ADC_DEBUG("%s entered with kadp index[%d]\n", __func__, kadp_index);

#ifdef M16P_BRINGUP_TODO
	switch(kadp_index)
	{
		case 59:	// 480i 60Hz : CGSM line 20,283
			DE_VBI_M16_RdFL(ctrl_cgms0);
			DE_VBI_M16_RdFL(ctrl_cgms1);
	//		DE_VBI_M16_Wr(ctrl_cgms0, 0x00340901);		// 27Mhz 480i
			DE_VBI_M16_Wr(ctrl_cgms0, 0x001E0901);	// 13.5Mhz 480i
			DE_VBI_M16_Wr(ctrl_cgms1, 0x03161027);
			DE_VBI_M16_WrFL(ctrl_cgms0);
			DE_VBI_M16_WrFL(ctrl_cgms1);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		case 60:	// 480p 60Hz : CGMS line 41
			DE_VBI_M16_RdFL(ctrl_cgms0);
			DE_VBI_M16_RdFL(ctrl_cgms1);
			DE_VBI_M16_Wr(ctrl_cgms0, 0x001a0f11);
			DE_VBI_M16_Wr(ctrl_cgms1, 0x02161027);
			DE_VBI_M16_WrFL(ctrl_cgms0);
			DE_VBI_M16_WrFL(ctrl_cgms1);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		case 61:	// 576i 50Hz : WSS
			DE_VBI_M16_RdFL(ctrl_wss0);
			DE_VBI_M16_RdFL(ctrl_wss1);
			DE_VBI_M16_RdFL(ctrl_wss2);
//			DE_VBI_M16_Wr(ctrl_wss0, 0x10100201);	//27MHz 576i
			DE_VBI_M16_Wr(ctrl_wss0, 0x15080201);	//13.5Mhz 576i
			DE_VBI_M16_Wr(ctrl_wss1, 0x031d1027);
//			DE_VBI_M16_Wr(ctrl_wss2, 0x001c3555);	//27Mhz 576i
			DE_VBI_M16_Wr(ctrl_wss2, 0x000E2555);	//13.5Mhz 576i
			DE_VBI_M16_WrFL(ctrl_wss0);
			DE_VBI_M16_WrFL(ctrl_wss1);
			DE_VBI_M16_WrFL(ctrl_wss2);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		case 62:	// 576p 50Hz : WSS
			DE_VBI_M16_RdFL(ctrl_wss0);
			DE_VBI_M16_RdFL(ctrl_wss1);
			DE_VBI_M16_RdFL(ctrl_wss2);
			DE_VBI_M16_Wr(ctrl_wss0, 0x00080811);
			DE_VBI_M16_Wr(ctrl_wss1, 0x021d1027);
			DE_VBI_M16_Wr(ctrl_wss2, 0x000e2555);
			DE_VBI_M16_WrFL(ctrl_wss0);
			DE_VBI_M16_WrFL(ctrl_wss1);
			DE_VBI_M16_WrFL(ctrl_wss2);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		case 64:	// 720p 60Hz : CGMS line 24
			DE_VBI_M16_RdFL(ctrl_cgms0);
			DE_VBI_M16_RdFL(ctrl_cgms1);
			DE_VBI_M16_Wr(ctrl_cgms0, 0x003a0821);
			DE_VBI_M16_Wr(ctrl_cgms1, 0x04161027);
			DE_VBI_M16_WrFL(ctrl_cgms0);
			DE_VBI_M16_WrFL(ctrl_cgms1);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		case 66:	// 1080i 60Hz : CGMS line 19
			DE_VBI_M16_RdFL(ctrl_cgms0);
			DE_VBI_M16_RdFL(ctrl_cgms1);
			DE_VBI_M16_Wr(ctrl_cgms0, 0x004d0831);	// fixed for 1080i 60Hz
			DE_VBI_M16_Wr(ctrl_cgms1, 0x04161027);
			DE_VBI_M16_WrFL(ctrl_cgms0);
			DE_VBI_M16_WrFL(ctrl_cgms1);

			ADC_M19Ax_Flush_Component_CP_Data();
			break;
		default :
			break;
	}
#endif

	if( (user_gain_value.R_Gain_Value != 0) && (user_gain_value.G_Gain_Value != 0) && (user_gain_value.B_Gain_Value != 0) )
	{
		ADC_M19Ax_AdcGainCompensator(&user_gain_value, &mod_gain_value);
		ADC_M19Ax_SetGainValue(&mod_gain_value);
	}

	return 0;
}

int ADC_M19Ax_Component_Get_CP_Data(LX_AFE_ADC_COMP_VBI_CP_T *stComp_VBI_CP_Data)
{
#ifdef COMP_COPY_PROTECTION
	DE_VBI_M16_RdFL(data_cgms0);
	DE_VBI_M16_RdFL(data_cgms1);
	DE_VBI_M16_RdFL(data_wss0);
	DE_VBI_M16_RdFL(data_wss1);
	stComp_VBI_CP_Data->cgms_data0 = DE_VBI_M16_Rd(data_cgms0);
	stComp_VBI_CP_Data->cgms_data1 = DE_VBI_M16_Rd(data_cgms1);
	stComp_VBI_CP_Data->wss_data0 = DE_VBI_M16_Rd(data_wss0);
	stComp_VBI_CP_Data->wss_data1 = DE_VBI_M16_Rd(data_wss1);

	stComp_VBI_CP_Data->cgms_cp_data = ( stComp_VBI_CP_Data->cgms_data1 >> 20) & 0xf;
	stComp_VBI_CP_Data->wss_cp_data = ( stComp_VBI_CP_Data->wss_data1 >> 0) & 0x3;

	ADC_M19Ax_Flush_Component_CP_Data();
#endif

	return 0;
}

int ADC_M19Ax_Flush_Component_CP_Data(void)
{
#ifdef COMP_COPY_PROTECTION
	DE_VBI_M16_RdFL(ctrl_cgms0);
	DE_VBI_M16_Wr01(ctrl_cgms0, cgms_enable, 0);
	DE_VBI_M16_WrFL(ctrl_cgms0);

	DE_VBI_M16_RdFL(ctrl_wss0);
	DE_VBI_M16_Wr01(ctrl_wss0, wss_enable, 0);
	DE_VBI_M16_WrFL(ctrl_wss0);

	DE_VBI_M16_RdFL(ctrl_cgms0);
	DE_VBI_M16_Wr01(ctrl_cgms0,cgms_enable, 1);
	DE_VBI_M16_WrFL(ctrl_cgms0);

	DE_VBI_M16_RdFL(ctrl_wss0);
	DE_VBI_M16_Wr01(ctrl_wss0, wss_enable, 1);
	DE_VBI_M16_WrFL(ctrl_wss0);

#endif
	return 0;
}

int ADC_M19Ax_Set_ADC_Input_Filter_Sel(int value)
{
	BMC_REG_M19Ax_RdFL(videoafe_03);
	BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adc_fil, value);
	BMC_REG_M19Ax_WrFL(videoafe_03);

	return 0;
}


int ADC_M19Ax_SetCurrent(int current_value)
{
	if(current_value == 0)
	{
		//480ip noise issue
		BMC_REG_M19Ax_RdFL(videoafe_03);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x0);	// 150820 : M16 // default 0x4
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_f12, 0x0);	// 150820 : M16 // default 0x02
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_f34, 0x0);	// 150820 : M16 // default 0x02
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_m, 0x0);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_ref, 0x0);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_ps, 0x0);
		BMC_REG_M19Ax_WrFL(videoafe_03);
	}
	else
	{
		BMC_REG_M19Ax_RdFL(videoafe_03);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_icon_adc, 0x4);	// 150421 : M16 // default 0x4
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_f12, 0x2);	// 150421 : M16 // default 0x02
		BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_f34, 0x2);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_m, 0x2);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_ref, 0x2);
		//BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_adcisel_ps, 0x2);
		BMC_REG_M19Ax_WrFL(videoafe_03);
	}
	return 0;
}

/* To prevent AV Smearing, Shield on the disconnected ADC Ports */
int ADC_M19Ax_Shield_Control(int comp1)
{
	UINT32 shield_on;

	shield_on = (comp1 & 0x1) << 1;

	ADC_DEBUG("%s entered with value[0x%x]\n", __func__, shield_on);

	BMC_REG_M19Ax_RdFL(videoafe_03);
	BMC_REG_M19Ax_Wr01(videoafe_03, videoafe_shield_on, shield_on);
	BMC_REG_M19Ax_WrFL(videoafe_03);

	return 0;
}

int ADC_M19Ax_AdcGainCompensator(LX_AFE_ADC_GAIN_VALUE_T *orgGain, LX_AFE_ADC_GAIN_VALUE_T *modGain)
{
#if 1
	if( (gADC_type != LX_ADC_INPUT_SOURCE_YPBPR ) || \
			( (gADC_type == LX_ADC_INPUT_SOURCE_YPBPR ) && ( (gResolution == 69) || (gResolution == 70) ) ) )
	{
		modGain->R_Gain_Value = orgGain->R_Gain_Value;
		modGain->G_Gain_Value = orgGain->G_Gain_Value;
		modGain->B_Gain_Value = orgGain->B_Gain_Value;

		ADC_DEBUG("%s entered use orginal gain [0x%x][0x%x][0x%x]\n", __func__, modGain->R_Gain_Value, modGain->G_Gain_Value, modGain->B_Gain_Value);
	}
	else
	{
		//180717 : ADC Gain Compensator value change (+0x10)
		if(orgGain->R_Gain_Value >= 0x48)
			modGain->R_Gain_Value = orgGain->R_Gain_Value - 0x48;
		else
			modGain->R_Gain_Value = orgGain->R_Gain_Value;
		if(orgGain->G_Gain_Value >= 0x50)
			modGain->G_Gain_Value = orgGain->G_Gain_Value - 0x50;
		else 
			modGain->G_Gain_Value = orgGain->G_Gain_Value;
		if(orgGain->B_Gain_Value >= 0x48)
			modGain->B_Gain_Value = orgGain->B_Gain_Value - 0x48;
		else 
			modGain->B_Gain_Value = orgGain->B_Gain_Value;

		ADC_DEBUG("%s entered use Modified gain [0x%x][0x%x][0x%x]\n", __func__, modGain->R_Gain_Value, modGain->G_Gain_Value, modGain->B_Gain_Value);
	}
#else
	modGain->R_Gain_Value = orgGain->R_Gain_Value;
	modGain->G_Gain_Value = orgGain->G_Gain_Value;
	modGain->B_Gain_Value = orgGain->B_Gain_Value;
#endif

	return 0;
}
