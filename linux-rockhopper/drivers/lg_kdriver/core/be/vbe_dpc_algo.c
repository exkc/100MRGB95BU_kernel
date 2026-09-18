/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

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
*  dpc algo file for VBE device
*
*  author
*  version		1.0
*  date		2025.03.12
*  note
*
*  @addtogroup BE
*	@{
*/

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "os_util.h"
#include "debug_util.h"
#include "be_dbg.h"
#include "be_proc.h"
#include "be_top_hal.h"
#include "vbe_dpc_algo.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
//get divide value with protection of divide zero case to specify (z) value
#define GET_DIV(_x,_y,_z)	(((_y)==0)?(_z):((_x)/(_y)))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static uint _g_vbe_dpc_hdr_mode = 0;//0:sdr,1:hdr
module_param_named(dpc_hdr_mode, _g_vbe_dpc_hdr_mode, uint, 0644);
static uint _g_vbe_dpc_iir_gain = 0;//0~256
module_param_named(dpc_iir_gain, _g_vbe_dpc_iir_gain, uint, 0644);
// BE_PRINT_DPC on  : dmesg -C ; echo +b15 > /proc/logm/be ; dmesg -w | grep '] be ';
// BE_PRINT_DPC off : echo -b15 > /proc/logm/be ;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
//use under 16b data for each table_x/table_y
static UINT32 N_interpolation(UINT32 *table_x, UINT32 *table_y, UINT32 din_xdata, UINT32 point_num)
{
	int interp_y_l = 1;
	int interp_y_r = 1;
	int interp_dist_l = 1;
	int interp_dist_r = 1;
	int i;
	UINT32 interp_mult_l;
	UINT32 interp_mult_r;
	UINT32 interp_dist_t;
	UINT32 div_in_up;
	UINT32 div_in_dn;
	UINT32 dout_ydata;

	int max_i = point_num;

	//p_calc_LUT_ind : process(clk)
	//Special period : Left side of X(0) point
	if (din_xdata < table_x[0])
	{
		interp_y_l = table_y[0];
		interp_y_r = table_y[0];
		interp_dist_l = 0;
		interp_dist_r = 1;
	}
	// Special period : Right side of X(n-1) point
	else if (din_xdata >= table_x[max_i-1])
	{
		interp_y_l = table_y[max_i-1];
		interp_y_r = table_y[max_i-1];
		interp_dist_l = 1;
		interp_dist_r = 0;
	}
	// Working period
	else
	{
		for ( i = 0; i < max_i - 1; i++)
		{
			if (din_xdata >= table_x[i] && din_xdata < table_x[i+1])
			{
				interp_y_l = table_y[i];
				interp_y_r = table_y[i+1];

				interp_dist_l = din_xdata - table_x[i];
				interp_dist_r = table_x[i+1] - din_xdata;
			}
		}
	}

	interp_mult_l = interp_y_l * interp_dist_r;
	interp_mult_r = interp_y_r * interp_dist_l;
	interp_dist_t = interp_dist_l + interp_dist_r;

	div_in_up = interp_mult_l + interp_mult_r;
	div_in_dn = interp_dist_t;

	dout_ydata = GET_DIV(div_in_up, div_in_dn, div_in_up);

	return dout_ydata;
}

static UINT32 adaptive_dpc_core(struct vbe_dpc_algo_param *p)
{
	////// OLED APL IIR

	// UINT32 curr_apl = 0;
	// read APL
	// curr_apl = (gpREG_OLED->addr_oapl_ctrl_70.naive_apl_tcon_mux) >> 1;

	UINT32 final_apl = 0;
	UINT32 prev_apl = 0;
	UINT32 interval = 0;
	UINT32 prev_duty = 0;
	const UINT32 apl_iir_interval_cnt = 2;
	UINT32 curr_duty;
	UINT32 final_duty;
	UINT32 apl_duty_lut_out; // 9bit(0 ~ 511)
	UINT32 *apl_duty_lut_x;//10b
	UINT32 *apl_duty_lut_y;//9b
	UINT32 curr_apl;
	// UINT32 param_hdr_mode;
	UINT32 param_apl_iir_gain;
	UINT32 log_en;

	if (!p) {
		return 0;
	}

	curr_apl = (p->fixapl >= 0 && p->fixapl <= 1023)? (UINT32)p->fixapl:p->readapl;
	param_apl_iir_gain = p->iirgain;
	apl_duty_lut_x = p->lutx;
	apl_duty_lut_y = p->luty;
	log_en = p->dbgprint;
	prev_apl = (!p->cur2pre)? p->finalapl:p->curapl;
	prev_duty = p->curduty;
	interval = p->interval;

	//if(param_hdr_mode == 0)// SDR input
	//{
	//	param_apl_iir_gain = 253;
	//}
	//else             // HDR input
	//{
	//	param_apl_iir_gain = 192;
	//}

	// use param_apl_iir_gain(256 = 1.0) input
	final_apl = (curr_apl * ((UINT32)256 - param_apl_iir_gain) + prev_apl * param_apl_iir_gain) >> 8 ;

	if(log_en == 1) {
		printk("%d)DPC apl.prev %4d curr %4d final %4d\n",log_en,prev_apl,curr_apl,final_apl);
	}

	if(interval % apl_iir_interval_cnt == 0)
	{
		if     (final_apl < curr_apl)	final_apl++;
		else if(final_apl > curr_apl)	final_apl--;
	}

	if(interval < apl_iir_interval_cnt - 1)	interval++;
	else									interval = 0;

	if(log_en == 2) {
		printk("%d)DPC apl.prev %4d curr %4d final %4d\n",log_en,prev_apl,curr_apl,final_apl);
	}

////// APL-DUTY LUT
#if 0
	apl_duty_lut_x[0]  = 0   ;
	apl_duty_lut_x[1]  = 30  ;
	apl_duty_lut_x[2]  = 50  ;
	apl_duty_lut_x[3]  = 71  ;
	apl_duty_lut_x[4]  = 101 ;
	apl_duty_lut_x[5]  = 153 ;
	apl_duty_lut_x[6]  = 204 ;
	apl_duty_lut_x[7]  = 255 ;
	apl_duty_lut_x[8]  = 306 ;
	apl_duty_lut_x[9]  = 409 ;
	apl_duty_lut_x[10] = 511 ;
	apl_duty_lut_x[11] = 613 ;
	apl_duty_lut_x[12] = 716 ;
	apl_duty_lut_x[13] = 818 ;
	apl_duty_lut_x[14] = 921 ;
	apl_duty_lut_x[15] = 1023;

	if(param_hdr_mode == 0)// SDR input
	{
		apl_duty_lut_y[0]  =   90;
		apl_duty_lut_y[1]  =    0;
		apl_duty_lut_y[2]  =    0;
		apl_duty_lut_y[3]  =    3;
		apl_duty_lut_y[4]  =   20;
		apl_duty_lut_y[5]  =   20;
		apl_duty_lut_y[6]  =   20;
		apl_duty_lut_y[7]  =   20;
		apl_duty_lut_y[8]  =   20;
		apl_duty_lut_y[9]  =   20;
		apl_duty_lut_y[10] =   20;
		apl_duty_lut_y[11] =   20;
		apl_duty_lut_y[12] =   20;
		apl_duty_lut_y[13] =   20;
		apl_duty_lut_y[14] =   20;
		apl_duty_lut_y[15] =   13;
	}
	else if(param_hdr_mode == 1)// SDR input
	{
		apl_duty_lut_y[0]  =   90;
		apl_duty_lut_y[1]  =    0;
		apl_duty_lut_y[2]  =    0;
		apl_duty_lut_y[3]  =    7;
		apl_duty_lut_y[4]  =   53;
		apl_duty_lut_y[5]  =   53;
		apl_duty_lut_y[6]  =   53;
		apl_duty_lut_y[7]  =   53;
		apl_duty_lut_y[8]  =   53;
		apl_duty_lut_y[9]  =   53;
		apl_duty_lut_y[10] =   53;
		apl_duty_lut_y[11] =   53;
		apl_duty_lut_y[12] =   53;
		apl_duty_lut_y[13] =   53;
		apl_duty_lut_y[14] =   34;
		apl_duty_lut_y[15] =   13;
	}
	else if(param_hdr_mode == 2)// // HDR input
	{
		apl_duty_lut_y[0]  =  90;
		apl_duty_lut_y[1]  = 255;
		apl_duty_lut_y[2]  = 232;
		apl_duty_lut_y[3]  = 212;
		apl_duty_lut_y[4]  = 180;
		apl_duty_lut_y[5]  = 198;
		apl_duty_lut_y[6]  = 219;
		apl_duty_lut_y[7]  = 240;
		apl_duty_lut_y[8]  = 219;
		apl_duty_lut_y[9]  = 175;
		apl_duty_lut_y[10] = 136;
		apl_duty_lut_y[11] = 104;
		apl_duty_lut_y[12] =  77;
		apl_duty_lut_y[13] =  56;
		apl_duty_lut_y[14] =  34;
		apl_duty_lut_y[15] =  13;
	}
	else //if(param_hdr_mode == 3)// max duty
	{
		apl_duty_lut_y[0]  = 255;
		apl_duty_lut_y[1]  = 255;
		apl_duty_lut_y[2]  = 255;
		apl_duty_lut_y[3]  = 255;
		apl_duty_lut_y[4]  = 255;
		apl_duty_lut_y[5]  = 255;
		apl_duty_lut_y[6]  = 255;
		apl_duty_lut_y[7]  = 255;
		apl_duty_lut_y[8]  = 255;
		apl_duty_lut_y[9]  = 255;
		apl_duty_lut_y[10] = 255;
		apl_duty_lut_y[11] = 255;
		apl_duty_lut_y[12] = 255;
		apl_duty_lut_y[13] = 255;
		apl_duty_lut_y[14] = 255;
		apl_duty_lut_y[15] = 255;
	}
#endif
	apl_duty_lut_out = N_interpolation(apl_duty_lut_x, apl_duty_lut_y, final_apl, 16);

////// duty delay filter
	curr_duty = apl_duty_lut_out;
	// delay : duty change from high to low, use previously calcualted duty(not previously applied duty).
	// follow: duty change from low to high, use current duty.
	if( prev_duty > curr_duty )
	{
		final_duty = prev_duty;
	}
	else
	{
		final_duty = curr_duty;
	}

	if(log_en == 3) {
		printk("DPC APL[pre %4d cur %4d final %4d] duty[pre %3d cur %3d final %3d] %s\n", prev_apl, curr_apl, final_apl, prev_duty, curr_duty, final_duty, (prev_duty>curr_duty)? "delay":"follow");
	}

	p->preapl = prev_apl;
	p->curapl = curr_apl;
	p->finalapl = final_apl;
	p->preduty = prev_duty;
	p->curduty = curr_duty;
	p->interval = interval;

	return final_duty;
}

int vbe_dpc_algo_update(struct vbe_dpc_algo_param *p)
{
	if (lx_chip() != LX_CHIP_O24 || !p) {
		return 0;
	}

	if (p->prerun != p->run) {
		if (!p->run) {
			p->preapl = 0;
			p->preduty = 0;
			p->interval = 0;
		}
		p->prerun = p->run;
	}

	if (p->run) {
		BE_TOP_HAL_GetDispApl(&p->readapl);
		if(p->dbgprint == 10) {printk("DPC get_oled_apl:%d\n",p->readapl);}
		p->finalduty = adaptive_dpc_core(p);
	}

	return 0;
}
