/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_chpi_dnr_hw_o20.c
 *
 *  driver for picture enhance sharpness functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj,S(kanthiraj.s@lge.com) - for SWMD code restrcuturing
 *	@version	0.1
 *	@note
 *	@date		2011.04.12
  *	@modified date	2015.05.25
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/delay.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
#include "pe_hw_o20.h"
#include "pe_reg_o20.h"
#include "pe_fwi_o20.h"
#include "pe_inf_o20.h"
#include "pe_dnr_hw_param_o20.h"
#include "pe_dnr_psp_hw_param_o20.h"
#include "pe_chpi_dnr_hw_f20.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_DNR_HW_F20_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_DNR_HW_F20_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_F20_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_PSP_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_PSP_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_PSP_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_PSP_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_DNR_PSP_HW_PARAM_DATA_F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_F20_T *data;
	} reg_data;
} PE_DNR_LED_HW_PARAM_DATA_F20_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern const PE_REG_PARAM_T dnr_l_hd_i_default_o20[];
extern const PE_REG_PARAM_T dnr_l_hd_p_default_o20[];
extern const PE_REG_PARAM_T dnr_l_sd_default_o20[];
extern const PE_REG_PARAM_T dnr_l_ud_default_o20[];
extern const PE_REG_PARAM_T led_dnr_l_ud_default_o20[];
extern const PE_REG_PARAM_T led_dnr_l_hd_default_o20[];
extern const PE_REG_PARAM_T led_dnr_l_sd_default_o20[];
extern const PE_REG_PARAM_T dnrpsp_l_hd_default_o20[];
extern const PE_REG_PARAM_T dnrpsp_l_sd_default_o20[];
extern const PE_REG_PARAM_T dnrpsp_l_ud_default_o20[];
extern const UINT32 sqm_dnr_init_o20[];
extern const UINT32 sqm_dct_init_o20[];
extern const PE_REG_PARAM_T dnr_l_hd_i_default_f20[];
extern const PE_REG_PARAM_T dnr_l_hd_p_default_f20[];
extern const PE_REG_PARAM_T dnr_l_sd_default_f20[];
extern const PE_REG_PARAM_T dnr_l_ud_default_f20[];
extern const PE_REG_PARAM_T led_dnr_l_ud_default_f20[];
extern const PE_REG_PARAM_T led_dnr_l_hd_default_f20[];
extern const PE_REG_PARAM_T led_dnr_l_sd_default_f20[];
extern const PE_REG_PARAM_T dnrpsp_l_hd_default_f20[];
extern const PE_REG_PARAM_T dnrpsp_l_sd_default_f20[];
extern const PE_REG_PARAM_T dnrpsp_l_ud_default_f20[];


/*----------------------------------------------------------------------------------------
	global Functions
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
static PE_DNR_HW_PARAM_DATA_F20_T _g_pe_dnr_hw_param_data_f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_DNR_PSP_HW_PARAM_DATA_F20_T _g_pe_dnr_psp_hw_param_data_f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_DNR_LED_HW_PARAM_DATA_F20_T _g_pe_dnr_led_hw_param_data_f20 = {{NULL}, {NULL}, {NULL}, {NULL}};

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
static int PE_CHPI_DNR_HW_F20_CreateDataTable(void)
{
	int ret = RET_OK;
	PE_DNR_HW_PARAM_DATA_F20_T *p_dnr = &_g_pe_dnr_hw_param_data_f20;
	PE_DNR_PSP_HW_PARAM_DATA_F20_T *p_dnr_psp = &_g_pe_dnr_psp_hw_param_data_f20;
	PE_DNR_LED_HW_PARAM_DATA_F20_T *p_dnr_led = &_g_pe_dnr_led_hw_param_data_f20;

	/* create dflt table */
	if (p_dnr->reg_dflt.addr == NULL)
	{
		p_dnr->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O20_T));
	}
	/* create user table */
	if (p_dnr->reg_user.addr == NULL)
	{
		p_dnr->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O20_T));
		memset((p_dnr->reg_user.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O20_T));	// 0x0
	}
	/* create mask table */
	if (p_dnr->reg_mask.addr == NULL)
	{
		p_dnr->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O20_T));
		memset((p_dnr->reg_mask.addr), -1, sizeof(PE_DNR_HW_PARAM_REG_O20_T));// 0xffffffff
	}
	/* create data table */
	if (p_dnr->reg_data.addr == NULL)
	{
		p_dnr->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O20_T));
		memset((p_dnr->reg_data.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O20_T));	// 0x0
	}
	/* report srsult */
	if (p_dnr->reg_dflt.addr != NULL && p_dnr->reg_user.addr != NULL && \
		p_dnr->reg_mask.addr != NULL && p_dnr->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_dnr]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_dnr]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_dnr->reg_dflt.addr == NULL)? "x":"o", \
			(p_dnr->reg_user.addr == NULL)? "x":"o", \
			(p_dnr->reg_mask.addr == NULL)? "x":"o", \
			(p_dnr->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_dnr_psp->reg_dflt.addr == NULL)
	{
		p_dnr_psp->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));
	}
	/* create user table */
	if (p_dnr_psp->reg_user.addr == NULL)
	{
		p_dnr_psp->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));
		memset((p_dnr_psp->reg_user.addr), 0, sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));	// 0x0
	}
	/* create mask table */
	if (p_dnr_psp->reg_mask.addr == NULL)
	{
		p_dnr_psp->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));
		memset((p_dnr_psp->reg_mask.addr), -1, sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));// 0xffffffff
	}
	/* create data table */
	if (p_dnr_psp->reg_data.addr == NULL)
	{
		p_dnr_psp->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));
		memset((p_dnr_psp->reg_data.addr), 0, sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T));	// 0x0
	}
	/* report srsult */
	if (p_dnr_psp->reg_dflt.addr != NULL && p_dnr_psp->reg_user.addr != NULL && \
		p_dnr_psp->reg_mask.addr != NULL && p_dnr_psp->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_dnr_psp]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_dnr_psp]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_dnr_psp->reg_dflt.addr == NULL)? "x":"o", \
			(p_dnr_psp->reg_user.addr == NULL)? "x":"o", \
			(p_dnr_psp->reg_mask.addr == NULL)? "x":"o", \
			(p_dnr_psp->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_dnr_led->reg_dflt.addr == NULL)
	{
		p_dnr_led->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));
	}
	/* create user table */
	if (p_dnr_led->reg_user.addr == NULL)
	{
		p_dnr_led->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));
		memset((p_dnr_led->reg_user.addr), 0, sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));	// 0x0
	}
	/* create mask table */
	if (p_dnr_led->reg_mask.addr == NULL)
	{
		p_dnr_led->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));
		memset((p_dnr_led->reg_mask.addr), -1, sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_dnr_led->reg_data.addr == NULL)
	{
		p_dnr_led->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));
		memset((p_dnr_led->reg_data.addr), 0, sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T));	// 0x0
	}
	/* report srsult */
	if (p_dnr_led->reg_dflt.addr != NULL && p_dnr_led->reg_user.addr != NULL && \
		p_dnr_led->reg_mask.addr != NULL && p_dnr_led->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_dnr_led]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_dnr_led]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_dnr_led->reg_dflt.addr == NULL)? "x":"o", \
			(p_dnr_led->reg_user.addr == NULL)? "x":"o", \
			(p_dnr_led->reg_mask.addr == NULL)? "x":"o", \
			(p_dnr_led->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	return ret;
}

static PE_CHPI_DNR_HW_F20_DNR_FMT PE_CHPI_DNR_HW_F20_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_DNR_HW_F20_DNR_FMT dnr_fmt = PE_CHPI_DNR_F20_DNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				dnr_fmt = PE_CHPI_DNR_F20_DNR_SD;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				dnr_fmt = PE_CHPI_DNR_F20_DNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					dnr_fmt = PE_CHPI_DNR_F20_DNR_HD_I;
				else
					dnr_fmt = PE_CHPI_DNR_F20_DNR_HD_P;
			}
			else
			{
				
				dnr_fmt = PE_CHPI_DNR_F20_DNR_UD;
			}
			break;
	}
	return dnr_fmt;
}

static PE_CHPI_DNR_HW_F20_PSP_FMT PE_CHPI_DNR_HW_F20_ConvDispInfoToPspFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_DNR_HW_F20_PSP_FMT psp_fmt = PE_CHPI_DNR_F20_PSP_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				psp_fmt = PE_CHPI_DNR_F20_PSP_SD;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				psp_fmt = PE_CHPI_DNR_F20_PSP_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				psp_fmt = PE_CHPI_DNR_F20_PSP_HD;
			}
			else
			{
				psp_fmt = PE_CHPI_DNR_F20_PSP_UD;
			}
			break;
	}
	return psp_fmt;
}

static PE_CHPI_DNR_HW_F20_LED_FMT PE_CHPI_DNR_HW_F20_ConvDispInfoToLedFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_DNR_HW_F20_LED_FMT led_fmt = PE_CHPI_DNR_F20_LED_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				led_fmt = PE_CHPI_DNR_F20_LED_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				led_fmt = PE_CHPI_DNR_F20_LED_HD;
			}
			else
			{
				led_fmt = PE_CHPI_DNR_F20_LED_UD;
			}
			break;
	}
	return led_fmt;
}

static int PE_CHPI_DNR_HW_F20_SetDnrDefault(PE_CHPI_DNR_HW_F20_DNR_FMT cur0_dnr_fmt)
{
	int ret = RET_OK;
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_dnr_hw_param_data_f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_dnr_hw_param_data_f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_dnr_hw_param_data_f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_dnr_hw_param_data_f20.reg_data.addr;

	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_dnr_fmt)
	{
		case PE_CHPI_DNR_F20_DNR_SD:
			p_dflt_param = dnr_l_sd_default_f20;
			break;
		case PE_CHPI_DNR_F20_DNR_HD_I:
			p_dflt_param = dnr_l_hd_i_default_f20;
			break;
		case PE_CHPI_DNR_F20_DNR_HD_P:
			p_dflt_param = dnr_l_hd_p_default_f20;
			break;
		case PE_CHPI_DNR_F20_DNR_UD:
		default:
			p_dflt_param = dnr_l_ud_default_f20;
			break;
	}

	size = sizeof(PE_DNR_HW_PARAM_REG_F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_F20_QWr(dnr.dnr_max_ctrl.udata32,p_data[0]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_0.udata32,p_data[1]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_1.udata32,p_data[2]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_2.udata32,p_data[3]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_3.udata32,p_data[4]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_4.udata32,p_data[5]);
	PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_5.udata32,p_data[6]);
	PE_CHPI_TBL0_F20_QWr(dnr.detail_ctrl.udata32,p_data[7]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_0.udata32,p_data[8]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_1.udata32,p_data[9]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_2.udata32,p_data[10]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_3.udata32,p_data[11]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_4.udata32,p_data[12]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_5.udata32,p_data[13]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_0.udata32,p_data[14]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_1.udata32,p_data[15]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_2.udata32,p_data[16]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_3.udata32,p_data[17]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_4.udata32,p_data[18]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_5.udata32,p_data[19]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_6.udata32,p_data[20]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_7.udata32,p_data[21]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_8.udata32,p_data[22]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_9.udata32,p_data[23]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_10.udata32,p_data[24]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_11.udata32,p_data[25]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_12.udata32,p_data[26]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_0.udata32,p_data[27]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_1.udata32,p_data[28]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_2.udata32,p_data[29]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_3.udata32,p_data[30]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_4.udata32,p_data[31]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_5.udata32,p_data[32]);
	PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_6.udata32,p_data[33]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_13.udata32,p_data[34]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_14.udata32,p_data[35]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_6.udata32,p_data[36]);
	PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_7.udata32,p_data[37]);
	PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_0.udata32,p_data[38]);
	PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_1.udata32,p_data[39]);
	PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_2.udata32,p_data[40]);
	PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_3.udata32,p_data[41]);
	PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_4.udata32,p_data[42]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_15.udata32,p_data[43]);
	PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_16.udata32,p_data[44]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_0.udata32,p_data[45]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_1.udata32,p_data[46]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_2.udata32,p_data[47]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_3.udata32,p_data[48]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_4.udata32,p_data[49]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_5.udata32,p_data[50]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_6.udata32,p_data[51]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_7.udata32,p_data[52]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_8.udata32,p_data[53]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_9.udata32,p_data[54]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_10.udata32,p_data[55]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_8.udata32,p_data[56]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_9.udata32,p_data[57]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_10.udata32,p_data[58]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_11.udata32,p_data[59]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_6.udata32,p_data[60]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_7.udata32,p_data[61]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_8.udata32,p_data[62]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_9.udata32,p_data[63]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_10.udata32,p_data[64]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_11.udata32,p_data[65]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_12.udata32,p_data[66]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_11.udata32,p_data[67]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_12.udata32,p_data[68]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_13.udata32,p_data[69]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_14.udata32,p_data[70]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_15.udata32,p_data[71]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_16.udata32,p_data[72]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_17.udata32,p_data[73]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_18.udata32,p_data[74]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_19.udata32,p_data[75]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_20.udata32,p_data[76]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_21.udata32,p_data[77]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_22.udata32,p_data[78]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_23.udata32,p_data[79]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_24.udata32,p_data[80]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_25.udata32,p_data[81]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_26.udata32,p_data[82]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_27.udata32,p_data[83]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_28.udata32,p_data[84]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_29.udata32,p_data[85]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_30.udata32,p_data[86]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_31.udata32,p_data[87]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_32.udata32,p_data[88]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_33.udata32,p_data[89]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_34.udata32,p_data[90]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_35.udata32,p_data[91]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_36.udata32,p_data[92]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_37.udata32,p_data[93]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_38.udata32,p_data[94]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_39.udata32,p_data[95]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_40.udata32,p_data[96]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_41.udata32,p_data[97]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_42.udata32,p_data[98]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_43.udata32,p_data[99]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_44.udata32,p_data[100]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_45.udata32,p_data[101]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_46.udata32,p_data[102]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_47.udata32,p_data[103]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_48.udata32,p_data[104]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_49.udata32,p_data[105]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_50.udata32,p_data[106]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_51.udata32,p_data[107]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_52.udata32,p_data[108]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_53.udata32,p_data[109]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_54.udata32,p_data[110]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_55.udata32,p_data[111]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_56.udata32,p_data[112]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_57.udata32,p_data[113]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_58.udata32,p_data[114]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_59.udata32,p_data[115]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_60.udata32,p_data[116]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_61.udata32,p_data[117]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_62.udata32,p_data[118]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_63.udata32,p_data[119]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_12.udata32,p_data[120]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_13.udata32,p_data[121]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_14.udata32,p_data[122]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_15.udata32,p_data[123]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_64.udata32,p_data[124]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_65.udata32,p_data[125]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_66.udata32,p_data[126]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_67.udata32,p_data[127]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_68.udata32,p_data[128]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_69.udata32,p_data[129]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_70.udata32,p_data[130]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_71.udata32,p_data[131]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_72.udata32,p_data[132]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_73.udata32,p_data[133]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_74.udata32,p_data[134]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_75.udata32,p_data[135]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_76.udata32,p_data[136]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_77.udata32,p_data[137]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_78.udata32,p_data[138]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_79.udata32,p_data[139]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_80.udata32,p_data[140]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_81.udata32,p_data[141]);
	PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_82.udata32,p_data[142]);
	//PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_83.udata32,p_data[143]);

	/* count */
	PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_DNR);

	return ret;
}

static int PE_CHPI_DNR_HW_F20_SetPspDefault(PE_CHPI_DNR_HW_F20_PSP_FMT cur0_psp_fmt)
{
	int ret = RET_OK;
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_dnr_psp_hw_param_data_f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_dnr_psp_hw_param_data_f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_dnr_psp_hw_param_data_f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_dnr_psp_hw_param_data_f20.reg_data.addr;

	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_psp_fmt)
	{
		case PE_CHPI_DNR_F20_PSP_SD:
			p_dflt_param = dnrpsp_l_sd_default_f20;
			break;
		case PE_CHPI_DNR_F20_PSP_HD:
			p_dflt_param = dnrpsp_l_hd_default_f20;
			break;
		case PE_CHPI_DNR_F20_PSP_UD:
		default:
			p_dflt_param = dnrpsp_l_ud_default_f20;
			break;
	}

	size = sizeof(PE_DNR_PSP_HW_PARAM_REG_O20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl00_o.udata32,p_data[0]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl01_o.udata32,p_data[1]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl02_o.udata32,p_data[2]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_th_o.udata32,p_data[3]);
	PE_CHPI_TBL0_F20_QWr(psp.fg_position_o.udata32,p_data[4]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x0_o.udata32,p_data[5]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x1_o.udata32,p_data[6]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x2_o.udata32,p_data[7]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x3_o.udata32,p_data[8]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y0_o.udata32,p_data[9]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y1_o.udata32,p_data[10]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y2_o.udata32,p_data[11]);
	PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y3_o.udata32,p_data[12]);
	PE_CHPI_TBL0_F20_QWr(psp.prob_map_o.udata32,p_data[13]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips_map_o.udata32,p_data[14]);
	PE_CHPI_TBL0_F20_QWr(psp.prob_diff_map_o.udata32,p_data[15]);
	PE_CHPI_TBL0_F20_QWr(psp.object_map_o.udata32,p_data[16]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_map_o.udata32,p_data[17]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_iir_o.udata32,p_data[18]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_gain_o.udata32,p_data[19]);
	PE_CHPI_TBL0_F20_QWr(psp.vrtx_cpc_ctrl_o.udata32,p_data[20]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef01_o.udata32,p_data[21]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef23_o.udata32,p_data[22]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef45_o.udata32,p_data[23]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef67_o.udata32,p_data[24]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef8_o.udata32,p_data[25]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef01_o.udata32,p_data[26]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef23_o.udata32,p_data[27]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef4_o.udata32,p_data[28]);
	PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut1_o.udata32,p_data[29]);
	PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut2_o.udata32,p_data[30]);
	PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut1_o.udata32,p_data[31]);
	PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut2_o.udata32,p_data[32]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_win_h_o.udata32,p_data[33]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_win_v_o.udata32,p_data[34]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_iir1_o.udata32,p_data[35]);
	PE_CHPI_TBL0_F20_QWr(psp.bg_measure_ctrl_o.udata32,p_data[36]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl00_f.udata32,p_data[37]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl01_f.udata32,p_data[38]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl02_f.udata32,p_data[39]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_th_f.udata32,p_data[40]);
	PE_CHPI_TBL0_F20_QWr(psp.fg_position_f.udata32,p_data[41]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved0_f.udata32,p_data[42]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved1_f.udata32,p_data[43]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved2_f.udata32,p_data[44]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved3_f.udata32,p_data[45]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved4_f.udata32,p_data[46]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved5_f.udata32,p_data[47]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved6_f.udata32,p_data[48]);
	PE_CHPI_TBL0_F20_QWr(psp.reserved7_f.udata32,p_data[49]);
	PE_CHPI_TBL0_F20_QWr(psp.prob_map_f.udata32,p_data[50]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips_map_f.udata32,p_data[51]);
	PE_CHPI_TBL0_F20_QWr(psp.prob_diff_map_f.udata32,p_data[52]);
	PE_CHPI_TBL0_F20_QWr(psp.object_map_f.udata32,p_data[53]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_map_f.udata32,p_data[54]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_iir_f.udata32,p_data[55]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_gain_f.udata32,p_data[56]);
	PE_CHPI_TBL0_F20_QWr(psp.vrtx_cpc_ctrl_f.udata32,p_data[57]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef01_f.udata32,p_data[58]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef23_f.udata32,p_data[59]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef45_f.udata32,p_data[60]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef67_f.udata32,p_data[61]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef8_f.udata32,p_data[62]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef01_f.udata32,p_data[63]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef23_f.udata32,p_data[64]);
	PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef4_f.udata32,p_data[65]);
	PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut1_f.udata32,p_data[66]);
	PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut2_f.udata32,p_data[67]);
	PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut1_f.udata32,p_data[68]);
	PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut2_f.udata32,p_data[69]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_win_h_f.udata32,p_data[70]);
	PE_CHPI_TBL0_F20_QWr(psp.edge_win_v_f.udata32,p_data[71]);
	PE_CHPI_TBL0_F20_QWr(psp.psp_iir1_f.udata32,p_data[72]);
	PE_CHPI_TBL0_F20_QWr(psp.bg_measure_ctrl_f.udata32,p_data[73]);
	PE_CHPI_TBL0_F20_QWr(psp.face0_set_f.udata32,p_data[74]);
	PE_CHPI_TBL0_F20_QWr(psp.face1_set_f.udata32,p_data[75]);
	PE_CHPI_TBL0_F20_QWr(psp.face2_set_f.udata32,p_data[76]);
	PE_CHPI_TBL0_F20_QWr(psp.face3_set_f.udata32,p_data[77]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips0_set_f.udata32,p_data[78]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips1_set_f.udata32,p_data[79]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips2_set_f.udata32,p_data[80]);
	PE_CHPI_TBL0_F20_QWr(psp.ellips3_set_f.udata32,p_data[81]);

	/* count */
	PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_PSP);

	return ret;
}

static int PE_CHPI_DNR_HW_F20_SetLedDefault(PE_CHPI_DNR_HW_F20_LED_FMT cur0_led_fmt)
{
	int ret = RET_OK;
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_dnr_led_hw_param_data_f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_dnr_led_hw_param_data_f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_dnr_led_hw_param_data_f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_dnr_led_hw_param_data_f20.reg_data.addr;

	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_DNR_HW_F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_led_fmt)
	{
		case PE_CHPI_DNR_F20_LED_SD:
			p_dflt_param = led_dnr_l_sd_default_f20;
			break;
		case PE_CHPI_DNR_F20_LED_HD:
			p_dflt_param = led_dnr_l_hd_default_f20;
			break;
		case PE_CHPI_DNR_F20_LED_UD:
		default:
			p_dflt_param = led_dnr_l_ud_default_f20;
			break;
	}

	size = sizeof(PE_LED_DNR_HW_PARAM_REG_F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_0.udata32,p_data[0]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_1.udata32,p_data[1]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_2.udata32,p_data[2]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_3.udata32,p_data[3]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_4.udata32,p_data[4]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_5.udata32,p_data[5]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_6.udata32,p_data[6]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_7.udata32,p_data[7]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_8.udata32,p_data[8]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_9.udata32,p_data[9]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_10.udata32,p_data[10]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_11.udata32,p_data[11]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_12.udata32,p_data[12]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_13.udata32,p_data[13]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_14.udata32,p_data[14]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_15.udata32,p_data[15]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_16.udata32,p_data[16]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_17.udata32,p_data[17]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_18.udata32,p_data[18]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_19.udata32,p_data[19]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_20.udata32,p_data[20]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_21.udata32,p_data[21]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_22.udata32,p_data[22]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_23.udata32,p_data[23]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_24.udata32,p_data[24]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_25.udata32,p_data[25]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_26.udata32,p_data[26]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_27.udata32,p_data[27]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_28.udata32,p_data[28]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_29.udata32,p_data[29]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_30.udata32,p_data[30]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_31.udata32,p_data[31]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_32.udata32,p_data[32]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_33.udata32,p_data[33]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_34.udata32,p_data[34]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_35.udata32,p_data[35]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_36.udata32,p_data[36]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_37.udata32,p_data[37]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_38.udata32,p_data[38]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_39.udata32,p_data[39]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_40.udata32,p_data[40]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_41.udata32,p_data[41]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_42.udata32,p_data[42]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_43.udata32,p_data[43]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_44.udata32,p_data[44]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_45.udata32,p_data[45]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_46.udata32,p_data[46]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_47.udata32,p_data[47]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_48.udata32,p_data[48]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_49.udata32,p_data[49]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_50.udata32,p_data[50]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_51.udata32,p_data[51]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_52.udata32,p_data[52]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_53.udata32,p_data[53]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_54.udata32,p_data[54]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_55.udata32,p_data[55]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_56.udata32,p_data[56]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_57.udata32,p_data[57]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_58.udata32,p_data[58]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_59.udata32,p_data[59]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_60.udata32,p_data[60]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_61.udata32,p_data[61]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_62.udata32,p_data[62]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_63.udata32,p_data[63]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_64.udata32,p_data[64]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_65.udata32,p_data[65]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_66.udata32,p_data[66]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_67.udata32,p_data[67]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_68.udata32,p_data[68]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_69.udata32,p_data[69]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_70.udata32,p_data[70]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_71.udata32,p_data[71]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_72.udata32,p_data[72]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_73.udata32,p_data[73]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_74.udata32,p_data[74]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_75.udata32,p_data[75]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_76.udata32,p_data[76]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_77.udata32,p_data[77]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_78.udata32,p_data[78]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_79.udata32,p_data[79]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_80.udata32,p_data[80]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_81.udata32,p_data[81]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_82.udata32,p_data[82]);
	//PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_83.udata32,p_data[83]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_84.udata32,p_data[83]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_85.udata32,p_data[84]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_86.udata32,p_data[85]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_87.udata32,p_data[86]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_88.udata32,p_data[87]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_89.udata32,p_data[88]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_90.udata32,p_data[89]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_91.udata32,p_data[90]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_92.udata32,p_data[91]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_93.udata32,p_data[92]);
	PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_94.udata32,p_data[93]);
	/* count */
	PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_LED);

	return ret;
}

int PE_CHPI_DNR_HW_F20_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_O20_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_DNR_HW_F20_DNR_FMT pre0_dnr_fmt = PE_CHPI_DNR_F20_DNR_NUM;
	static PE_CHPI_DNR_HW_F20_PSP_FMT pre0_psp_fmt = PE_CHPI_DNR_F20_PSP_NUM;
	static PE_CHPI_DNR_HW_F20_LED_FMT pre0_led_fmt = PE_CHPI_DNR_F20_LED_NUM;
	PE_CHPI_DNR_HW_F20_DNR_FMT cur0_dnr_fmt;
	PE_CHPI_DNR_HW_F20_PSP_FMT cur0_psp_fmt;
	PE_CHPI_DNR_HW_F20_LED_FMT cur0_led_fmt;
	do{
		ret = PE_INF_O20_GetCurInfSettings(&inf_set);
		PE_CHPI_DNR_HW_F20_CHECK_CODE(ret,break,"PE_INF_O20_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_dnr_fmt = PE_CHPI_DNR_HW_F20_ConvDispInfoToDnrFmt(disp0_inf);
		if(pre0_dnr_fmt!=cur0_dnr_fmt)
		{
			ret = PE_CHPI_DNR_HW_F20_SetDnrDefault(cur0_dnr_fmt);
			PE_CHPI_DNR_HW_F20_CHECK_CODE(ret,break,"PE_CHPI_DNR_HW_F20_SetDnrDefault() error\n");
			pre0_dnr_fmt=cur0_dnr_fmt;
		}
		cur0_psp_fmt = PE_CHPI_DNR_HW_F20_ConvDispInfoToPspFmt(disp0_inf);
		if(pre0_psp_fmt!=cur0_psp_fmt)
		{
			ret = PE_CHPI_DNR_HW_F20_SetPspDefault(cur0_psp_fmt);
			PE_CHPI_DNR_HW_F20_CHECK_CODE(ret,break,"PE_CHPI_DNR_HW_F20_SetPspDefault() error\n");
			pre0_psp_fmt=cur0_psp_fmt;
		}
		cur0_led_fmt = PE_CHPI_DNR_HW_F20_ConvDispInfoToLedFmt(disp0_inf);
		if(pre0_led_fmt!=cur0_led_fmt)
		{
			ret = PE_CHPI_DNR_HW_F20_SetLedDefault(cur0_led_fmt);
			PE_CHPI_DNR_HW_F20_CHECK_CODE(ret,break,"PE_CHPI_DNR_HW_F20_SetLedDefault() error\n");
			pre0_led_fmt=cur0_led_fmt;
		}
	}while(0);
	return ret;
}

int PE_CHPI_DNR_HW_F20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_DNR_HW_F20_CreateDataTable();
		if (ret)	break;

		if (pstParams->resume_mode == 1)	break;//if qsm,skip

		/* addr */
		PE_CHPI_TBL0_F20_QWr(dnr.dnr_max_ctrl.uaddr32,0xF0221594);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_0.uaddr32,0xF02215A0);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_1.uaddr32,0xF02215A4);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_2.uaddr32,0xF02215A8);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_3.uaddr32,0xF02215AC);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_4.uaddr32,0xF02215B0);
		PE_CHPI_TBL0_F20_QWr(dnr.mnr_ctrl_5.uaddr32,0xF02215B4);
		PE_CHPI_TBL0_F20_QWr(dnr.detail_ctrl.uaddr32,0xF02215B8);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_0.uaddr32,0xF02215BC);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_1.uaddr32,0xF02215C0);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_2.uaddr32,0xF02215C4);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_3.uaddr32,0xF02215C8);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_4.uaddr32,0xF02215CC);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_5.uaddr32,0xF02215D0);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_0.uaddr32,0xF02215D4);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_1.uaddr32,0xF02215D8);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_2.uaddr32,0xF02215DC);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_3.uaddr32,0xF02215E4);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_4.uaddr32,0xF02215E8);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_5.uaddr32,0xF02215F0);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_6.uaddr32,0xF02215F4);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_7.uaddr32,0xF02215F8);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_8.uaddr32,0xF0221600);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_9.uaddr32,0xF0221604);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_10.uaddr32,0xF0221608);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_11.uaddr32,0xF022160C);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_12.uaddr32,0xF0221610);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_0.uaddr32,0xF022166C);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_1.uaddr32,0xF0221670);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_2.uaddr32,0xF0221674);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_3.uaddr32,0xF0221678);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_4.uaddr32,0xF022167C);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_5.uaddr32,0xF0221680);
		PE_CHPI_TBL0_F20_QWr(dnr.sc_bnr_ctrl_6.uaddr32,0xF0221684);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_13.uaddr32,0xF022169C);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_ctrl_14.uaddr32,0xF02216A0);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_6.uaddr32,0xF02216A4);
		PE_CHPI_TBL0_F20_QWr(dnr.dc_bnr_ctrl_7.uaddr32,0xF02216A8);
		PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_0.uaddr32,0xF02216AC);
		PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_1.uaddr32,0xF02216B0);
		PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_2.uaddr32,0xF02216B4);
		PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_3.uaddr32,0xF02216B8);
		PE_CHPI_TBL0_F20_QWr(dnr.sqm_ctrl_4.uaddr32,0xF02216BC);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_15.uaddr32,0xF0221730);
		PE_CHPI_TBL0_F20_QWr(dnr.ac_bnr_16.uaddr32,0xF0221734);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_0.uaddr32,0xF0221764);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_1.uaddr32,0xF0221768);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_2.uaddr32,0xF022176C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_3.uaddr32,0xF0221770);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_4.uaddr32,0xF0221774);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_5.uaddr32,0xF0221778);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_6.uaddr32,0xF022177C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_7.uaddr32,0xF0221780);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_8.uaddr32,0xF0221784);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_9.uaddr32,0xF0221788);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_10.uaddr32,0xF022178C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_8.uaddr32,0xF0221790);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_9.uaddr32,0xF0221794);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_10.uaddr32,0xF0221798);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_11.uaddr32,0xF022179C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_6.uaddr32,0xF02217A8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_7.uaddr32,0xF02217AC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_8.uaddr32,0xF02217B0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_9.uaddr32,0xF02217B4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_10.uaddr32,0xF02217B8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_11.uaddr32,0xF02217BC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_mnr_ctrl_12.uaddr32,0xF02217C0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_11.uaddr32,0xF02217C4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_12.uaddr32,0xF02217C8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_13.uaddr32,0xF02217CC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_14.uaddr32,0xF02217D0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_15.uaddr32,0xF02217D4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_16.uaddr32,0xF02217D8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_17.uaddr32,0xF02217DC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_18.uaddr32,0xF02217E0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_19.uaddr32,0xF02217E4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_20.uaddr32,0xF02217E8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_21.uaddr32,0xF02217EC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_22.uaddr32,0xF02217F0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_23.uaddr32,0xF02217F4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_24.uaddr32,0xF02217F8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_25.uaddr32,0xF02217FC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_26.uaddr32,0xF0221800);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_27.uaddr32,0xF0221804);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_28.uaddr32,0xF0221808);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_29.uaddr32,0xF022180C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_30.uaddr32,0xF0221810);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_31.uaddr32,0xF0221814);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_32.uaddr32,0xF0221818);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_33.uaddr32,0xF022181C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_34.uaddr32,0xF0221820);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_35.uaddr32,0xF0221824);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_36.uaddr32,0xF0221828);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_37.uaddr32,0xF022182C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_38.uaddr32,0xF0221830);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_39.uaddr32,0xF0221834);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_40.uaddr32,0xF0221838);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_41.uaddr32,0xF022183C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_42.uaddr32,0xF0221840);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_43.uaddr32,0xF0221844);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_44.uaddr32,0xF0221848);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_45.uaddr32,0xF022184C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_46.uaddr32,0xF0221850);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_47.uaddr32,0xF0221854);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_48.uaddr32,0xF0221858);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_49.uaddr32,0xF022185C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_50.uaddr32,0xF0221860);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_51.uaddr32,0xF0221864);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_52.uaddr32,0xF0221868);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_53.uaddr32,0xF022186C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_54.uaddr32,0xF0221870);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_55.uaddr32,0xF0221874);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_56.uaddr32,0xF0221878);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_57.uaddr32,0xF022187C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_58.uaddr32,0xF0221880);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_59.uaddr32,0xF0221884);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_60.uaddr32,0xF0221888);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_61.uaddr32,0xF022188C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_62.uaddr32,0xF0221890);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_63.uaddr32,0xF0221894);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_12.uaddr32,0xF0221898);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_13.uaddr32,0xF022189C);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_14.uaddr32,0xF02218A0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_dc_bnr_ctrl_15.uaddr32,0xF02218A4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_64.uaddr32,0xF02218A8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_65.uaddr32,0xF02218AC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_66.uaddr32,0xF02218B0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_67.uaddr32,0xF02218B4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_68.uaddr32,0xF02218B8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_69.uaddr32,0xF02218BC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_70.uaddr32,0xF02218C0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_71.uaddr32,0xF02218C4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_72.uaddr32,0xF02218C8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_73.uaddr32,0xF02218CC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_74.uaddr32,0xF02218D0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_75.uaddr32,0xF02218D4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_76.uaddr32,0xF02218D8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_77.uaddr32,0xF02218DC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_78.uaddr32,0xF02218E0);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_79.uaddr32,0xF02218E4);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_80.uaddr32,0xF02218E8);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_81.uaddr32,0xF02218EC);
		PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_82.uaddr32,0xF02218F0);
		//PE_CHPI_TBL0_F20_QWr(dnr.reg_decon_ctrl_83.uaddr32,0xF02218F4);

		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl00_o.uaddr32,0xF0221F00);
		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl01_o.uaddr32,0xF0221F04);
		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl02_o.uaddr32,0xF0221F08);
		PE_CHPI_TBL0_F20_QWr(psp.edge_th_o.uaddr32,0xF0221F0C);
		PE_CHPI_TBL0_F20_QWr(psp.fg_position_o.uaddr32,0xF0221F10);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x0_o.uaddr32,0xF0221F14);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x1_o.uaddr32,0xF0221F18);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x2_o.uaddr32,0xF0221F1C);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_x3_o.uaddr32,0xF0221F20);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y0_o.uaddr32,0xF0221F24);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y1_o.uaddr32,0xF0221F28);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y2_o.uaddr32,0xF0221F2C);
		PE_CHPI_TBL0_F20_QWr(psp.perspect_lut_y3_o.uaddr32,0xF0221F30);
		PE_CHPI_TBL0_F20_QWr(psp.prob_map_o.uaddr32,0xF0221F34);
		PE_CHPI_TBL0_F20_QWr(psp.ellips_map_o.uaddr32,0xF0221F38);
		PE_CHPI_TBL0_F20_QWr(psp.prob_diff_map_o.uaddr32,0xF0221F3C);
		PE_CHPI_TBL0_F20_QWr(psp.object_map_o.uaddr32,0xF0221F40);
		PE_CHPI_TBL0_F20_QWr(psp.blur_map_o.uaddr32,0xF0221F44);
		PE_CHPI_TBL0_F20_QWr(psp.psp_iir_o.uaddr32,0xF0221F4C);
		PE_CHPI_TBL0_F20_QWr(psp.psp_gain_o.uaddr32,0xF0221F50);
		PE_CHPI_TBL0_F20_QWr(psp.vrtx_cpc_ctrl_o.uaddr32,0xF0221F5C);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef01_o.uaddr32,0xF0221F60);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef23_o.uaddr32,0xF0221F64);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef45_o.uaddr32,0xF0221F68);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef67_o.uaddr32,0xF0221F6C);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef8_o.uaddr32,0xF0221F70);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef01_o.uaddr32,0xF0221F74);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef23_o.uaddr32,0xF0221F78);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef4_o.uaddr32,0xF0221F7C);
		PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut1_o.uaddr32,0xF0222000);
		PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut2_o.uaddr32,0xF0222004);
		PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut1_o.uaddr32,0xF0222008);
		PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut2_o.uaddr32,0xF022200C);
		PE_CHPI_TBL0_F20_QWr(psp.edge_win_h_o.uaddr32,0xF0222010);
		PE_CHPI_TBL0_F20_QWr(psp.edge_win_v_o.uaddr32,0xF0222014);
		PE_CHPI_TBL0_F20_QWr(psp.psp_iir1_o.uaddr32,0xF0222028);
		PE_CHPI_TBL0_F20_QWr(psp.bg_measure_ctrl_o.uaddr32,0xF022202C);
		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl00_f.uaddr32,0xF0222100);
		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl01_f.uaddr32,0xF0222104);
		PE_CHPI_TBL0_F20_QWr(psp.psp_ctrl02_f.uaddr32,0xF0222108);
		PE_CHPI_TBL0_F20_QWr(psp.edge_th_f.uaddr32,0xF022210C);
		PE_CHPI_TBL0_F20_QWr(psp.fg_position_f.uaddr32,0xF0222110);
		PE_CHPI_TBL0_F20_QWr(psp.reserved0_f.uaddr32,0xF0222114);
		PE_CHPI_TBL0_F20_QWr(psp.reserved1_f.uaddr32,0xF0222118);
		PE_CHPI_TBL0_F20_QWr(psp.reserved2_f.uaddr32,0xF022211C);
		PE_CHPI_TBL0_F20_QWr(psp.reserved3_f.uaddr32,0xF0222120);
		PE_CHPI_TBL0_F20_QWr(psp.reserved4_f.uaddr32,0xF0222124);
		PE_CHPI_TBL0_F20_QWr(psp.reserved5_f.uaddr32,0xF0222128);
		PE_CHPI_TBL0_F20_QWr(psp.reserved6_f.uaddr32,0xF022212C);
		PE_CHPI_TBL0_F20_QWr(psp.reserved7_f.uaddr32,0xF0222130);
		PE_CHPI_TBL0_F20_QWr(psp.prob_map_f.uaddr32,0xF0222134);
		PE_CHPI_TBL0_F20_QWr(psp.ellips_map_f.uaddr32,0xF0222138);
		PE_CHPI_TBL0_F20_QWr(psp.prob_diff_map_f.uaddr32,0xF022213C);
		PE_CHPI_TBL0_F20_QWr(psp.object_map_f.uaddr32,0xF0222140);
		PE_CHPI_TBL0_F20_QWr(psp.blur_map_f.uaddr32,0xF0222144);
		PE_CHPI_TBL0_F20_QWr(psp.psp_iir_f.uaddr32,0xF022214C);
		PE_CHPI_TBL0_F20_QWr(psp.psp_gain_f.uaddr32,0xF0222150);
		PE_CHPI_TBL0_F20_QWr(psp.vrtx_cpc_ctrl_f.uaddr32,0xF022215C);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef01_f.uaddr32,0xF0222160);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef23_f.uaddr32,0xF0222164);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef45_f.uaddr32,0xF0222168);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef67_f.uaddr32,0xF022216C);
		PE_CHPI_TBL0_F20_QWr(psp.blur_hcoef8_f.uaddr32,0xF0222170);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef01_f.uaddr32,0xF0222174);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef23_f.uaddr32,0xF0222178);
		PE_CHPI_TBL0_F20_QWr(psp.blur_vcoef4_f.uaddr32,0xF022217C);
		PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut1_f.uaddr32,0xF0222200);
		PE_CHPI_TBL0_F20_QWr(psp.l5_gain_lut2_f.uaddr32,0xF0222204);
		PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut1_f.uaddr32,0xF0222208);
		PE_CHPI_TBL0_F20_QWr(psp.l0_gain_lut2_f.uaddr32,0xF022220C);
		PE_CHPI_TBL0_F20_QWr(psp.edge_win_h_f.uaddr32,0xF0222210);
		PE_CHPI_TBL0_F20_QWr(psp.edge_win_v_f.uaddr32,0xF0222214);
		PE_CHPI_TBL0_F20_QWr(psp.psp_iir1_f.uaddr32,0xF0222228);
		PE_CHPI_TBL0_F20_QWr(psp.bg_measure_ctrl_f.uaddr32,0xF022222C);
		PE_CHPI_TBL0_F20_QWr(psp.face0_set_f.uaddr32,0xF0222244);
		PE_CHPI_TBL0_F20_QWr(psp.face1_set_f.uaddr32,0xF0222248);
		PE_CHPI_TBL0_F20_QWr(psp.face2_set_f.uaddr32,0xF022224C);
		PE_CHPI_TBL0_F20_QWr(psp.face3_set_f.uaddr32,0xF0222250);
		PE_CHPI_TBL0_F20_QWr(psp.ellips0_set_f.uaddr32,0xF0222254);
		PE_CHPI_TBL0_F20_QWr(psp.ellips1_set_f.uaddr32,0xF0222258);
		PE_CHPI_TBL0_F20_QWr(psp.ellips2_set_f.uaddr32,0xF022225C);
		PE_CHPI_TBL0_F20_QWr(psp.ellips3_set_f.uaddr32,0xF0222260);

		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_0.uaddr32,0xF036CD04);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_1.uaddr32,0xF036CD08);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_2.uaddr32,0xF036CD0C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_3.uaddr32,0xF036CD10);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_4.uaddr32,0xF036CD14);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_5.uaddr32,0xF036CD18);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_6.uaddr32,0xF036CD1C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_7.uaddr32,0xF036CD20);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_8.uaddr32,0xF036CD24);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_9.uaddr32,0xF036CD28);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_10.uaddr32,0xF036CD2C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_11.uaddr32,0xF036CD30);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_12.uaddr32,0xF036CD34);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_13.uaddr32,0xF036CD38);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_14.uaddr32,0xF036CD3C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_15.uaddr32,0xF036CD40);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_16.uaddr32,0xF036CD44);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_17.uaddr32,0xF036CD48);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_18.uaddr32,0xF036CD4C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_19.uaddr32,0xF036CD50);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_20.uaddr32,0xF036CD54);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_21.uaddr32,0xF036CD58);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_22.uaddr32,0xF036CD5C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_23.uaddr32,0xF036CD60);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_24.uaddr32,0xF036CDBC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_25.uaddr32,0xF036CDC0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_26.uaddr32,0xF036CDC4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_27.uaddr32,0xF036CDC8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_28.uaddr32,0xF036CDCC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_29.uaddr32,0xF036CDD0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_30.uaddr32,0xF036CDD4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_31.uaddr32,0xF036CDD8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_32.uaddr32,0xF036CDDC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_33.uaddr32,0xF036CDE0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_34.uaddr32,0xF036CDE4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_35.uaddr32,0xF036CDE8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_36.uaddr32,0xF036CDEC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_37.uaddr32,0xF036CDF0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_38.uaddr32,0xF036CDF4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_39.uaddr32,0xF036CDF8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_40.uaddr32,0xF036CDFC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_41.uaddr32,0xF036CE00);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_42.uaddr32,0xF036CE04);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_43.uaddr32,0xF036CE08);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_44.uaddr32,0xF036CE0C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_45.uaddr32,0xF036CE10);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_46.uaddr32,0xF036CE14);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_47.uaddr32,0xF036CE18);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_48.uaddr32,0xF036CE1C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_49.uaddr32,0xF036CE20);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_50.uaddr32,0xF036CE24);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_51.uaddr32,0xF036CE28);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_52.uaddr32,0xF036CE2C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_53.uaddr32,0xF036CE30);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_54.uaddr32,0xF036CE34);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_55.uaddr32,0xF036CE38);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_56.uaddr32,0xF036CE3C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_57.uaddr32,0xF036CE40);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_58.uaddr32,0xF036CE44);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_59.uaddr32,0xF036CE48);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_60.uaddr32,0xF036CE4C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_61.uaddr32,0xF036CE50);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_62.uaddr32,0xF036CE54);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_63.uaddr32,0xF036CE58);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_64.uaddr32,0xF036CE5C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_65.uaddr32,0xF036CE60);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_66.uaddr32,0xF036CE64);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_67.uaddr32,0xF036CE68);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_68.uaddr32,0xF036CE6C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_69.uaddr32,0xF036CE70);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_70.uaddr32,0xF036CE74);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_71.uaddr32,0xF036CE78);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_72.uaddr32,0xF036CE7C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_73.uaddr32,0xF036CE80);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_74.uaddr32,0xF036CE84);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_75.uaddr32,0xF036CE88);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_76.uaddr32,0xF036CE8C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_77.uaddr32,0xF036CE90);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_78.uaddr32,0xF036CE94);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_79.uaddr32,0xF036CE98);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_80.uaddr32,0xF036CE9C);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_81.uaddr32,0xF036CEA0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_82.uaddr32,0xF036CEA4);
		//PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_83.uaddr32,0xF036CEA8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_84.uaddr32,0xF036CEAC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_85.uaddr32,0xF036CEB0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_86.uaddr32,0xF036CEB4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_87.uaddr32,0xF036CEB8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_88.uaddr32,0xF036CEBC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_89.uaddr32,0xF036CEC0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_90.uaddr32,0xF036CEC4);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_91.uaddr32,0xF036CEC8);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_92.uaddr32,0xF036CECC);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_93.uaddr32,0xF036CED0);
		PE_CHPI_TBL0_F20_QWr(led.reg_decon_ctrl_94.uaddr32,0xF036CED4);

		/* init */
		PE_CHPI_DNR_HW_F20_SetDnrDefault(PE_CHPI_DNR_F20_DNR_HD_P);
		PE_CHPI_DNR_HW_F20_SetPspDefault(PE_CHPI_DNR_F20_PSP_HD);
		PE_CHPI_DNR_HW_F20_SetLedDefault(PE_CHPI_DNR_F20_LED_HD);

		/* download dnr sqm db */
		/* see PE_NRD_HW_O20_DownloadDnrSqmCmnInitDb */
		/* PE_CHPI_DNR_SQM_F20_T                 sqm3;//14 */
		PE_CHPI_TBL0_F20_QWr(sqm3.ui32,0);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm3.data32[i],sqm_dnr_init_o20[i]);
		}
		PE_CHPI_TBL0_F20_QWr(sqm3.cnt32,0);

		/* download dnr user db */
		/* see PE_NRD_HW_O20_DownloadDnrInitDb */
		/* PE_CHPI_DNR_USER_F20_T                usr1;//18 */
		PE_CHPI_TBL0_F20_QWr(usr1.ui32,0);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr1.data32[i],0);
		}
		PE_CHPI_TBL0_F20_QWr(usr1.cnt32,0);

		/* count */
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM3);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR1);

		/* download dct sqm db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntSqmCmnInitDb */
		/* PE_CHPI_DNR_DCNT_SQM_F20_T            sqm4;//15 */
		PE_CHPI_TBL0_F20_QWr(sqm4.ui32,0);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm4.data32[i],sqm_dct_init_o20[i]);
		}
		PE_CHPI_TBL0_F20_QWr(sqm4.cnt32,0);

		/* download dct user db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntInitDb */
		/* PE_CHPI_DNR_DCNT_USER_F20_T           usr2;//19 */
		PE_CHPI_TBL0_F20_QWr(usr2.ui32,0);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr2.data32[i],0);
		}
		PE_CHPI_TBL0_F20_QWr(usr2.cnt32,0);

		/* download dct led sqm db */
		/* see PE_NRD_HW_O20_DownloadLedDcntSqmCmnInitDb */
		/* PE_CHPI_LED_DCNT_SQM_F20_T            sqm5;//16 */
		PE_CHPI_TBL0_F20_QWr(sqm5.ui32,0);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm5.data32[i],0);
		}
		PE_CHPI_TBL0_F20_QWr(sqm5.cnt32,0);

		/* download dct led user db */
		/* see PE_NRD_HW_O20_DownloadLedDcntInitDb */
		/* PE_CHPI_LED_DCNT_USER_F20_T           usr3;//20 */
		PE_CHPI_TBL0_F20_QWr(usr3.ui32,0);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr3.data32[i],0);
		}
		PE_CHPI_TBL0_F20_QWr(usr3.cnt32,0);

		/* count */
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM4);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR2);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM5);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR3);

		PE_PRINT_NOTI("[TBL][DNR]done(resume:%d)\n",pstParams->resume_mode);
		PE_INF_HW_O20_BACKUP_CHPI1("[TBL][DNR]done(resume:%d)",pstParams->resume_mode);
	}while(0);
	return ret;
}

int PE_CHPI_DNR_HW_F20_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	LX_PE_NRD_DNR_CMN_T *p_param;
	LX_PE_NRD_DNR_ALL_CMN_T *pp;
	PE_DNR_HW_PARAM_DATA_F20_T *p_dnr = &_g_pe_dnr_hw_param_data_f20;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		p_param = (LX_PE_NRD_DNR_CMN_T *)pstParams;
		pp = (LX_PE_NRD_DNR_ALL_CMN_T *)p_param->data;

		/* set tbl */
		PE_CHPI_TBL0_F20_Wr(dnr.dnr_max_ctrl.reg_dnr_max_enable,GET_BITS(pp->dnr______ui[0],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_0.reg_mnr_chroma_en,GET_BITS(pp->dnr______ui[1],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_0.reg_mnr_enable,GET_BITS(pp->dnr______ui[2],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_dc_bnr_enable,GET_BITS(pp->dnr______ui[3],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_obj_gain_mul,GET_BITS(pp->dnr______ui[4],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en,GET_BITS(pp->dnr______ui[5],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en,GET_BITS(pp->dnr______ui[6],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_en,GET_BITS(pp->dnr______ui[7],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_en,GET_BITS(pp->dnr______ui[8],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_min,GET_BITS(pp->dnr______ui[9],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_max,GET_BITS(pp->dnr______ui[10],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_min,GET_BITS(pp->dnr______ui[11],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_max,GET_BITS(pp->dnr______ui[12],0,8));
		/*dnr_____mnr*/
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_1.reg_mmd_x_min,GET_BITS(pp->dnr_____mnr[0],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_1.reg_mmd_x_max,GET_BITS(pp->dnr_____mnr[1],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_1.reg_mmd_y_min,GET_BITS(pp->dnr_____mnr[2],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_1.reg_mmd_y_max,GET_BITS(pp->dnr_____mnr[3],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_3.reg_mmd_scale,GET_BITS(pp->dnr_____mnr[4],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.mnr_ctrl_3.reg_blur_sel,GET_BITS(pp->dnr_____mnr[5],0,1));
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_F20_Wr(dnr.detail_ctrl.reg_bnr_diff_p,GET_BITS(pp->dnr___dcbnr[0],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.detail_ctrl.reg_bnr_diff_l,GET_BITS(pp->dnr___dcbnr[1],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_dc_motion_min,GET_BITS(pp->dnr___dcbnr[2],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_dc_motion_max,GET_BITS(pp->dnr___dcbnr[3],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_dc_blur_sel,GET_BITS(pp->dnr___dcbnr[4],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_1.reg_var_cut_resolution,GET_BITS(pp->dnr___dcbnr[5],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_1.reg_var_h_gain,GET_BITS(pp->dnr___dcbnr[6],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_1.reg_var_v_gain,GET_BITS(pp->dnr___dcbnr[7],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_1.reg_luma_gain_en,GET_BITS(pp->dnr___dcbnr[8],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_2.reg_dc_protection_th,GET_BITS(pp->dnr___dcbnr[9],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_2.reg_dc_protection_en,GET_BITS(pp->dnr___dcbnr[10],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_2.reg_dc_motion_en,GET_BITS(pp->dnr___dcbnr[11],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_2.reg_dc_var_en,GET_BITS(pp->dnr___dcbnr[12],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th0,GET_BITS(pp->dnr___dcbnr[13],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th1,GET_BITS(pp->dnr___dcbnr[14],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th2,GET_BITS(pp->dnr___dcbnr[15],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th3,GET_BITS(pp->dnr___dcbnr[16],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.sc_bnr_ctrl_0.reg_sc_bnr_en,GET_BITS(pp->dnr___dcbnr[17],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x0,GET_BITS(pp->dnr___dcbnr[18],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x1,GET_BITS(pp->dnr___dcbnr[19],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x2,GET_BITS(pp->dnr___dcbnr[20],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x3,GET_BITS(pp->dnr___dcbnr[21],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x4,GET_BITS(pp->dnr___dcbnr[22],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x5,GET_BITS(pp->dnr___dcbnr[23],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x6,GET_BITS(pp->dnr___dcbnr[24],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x7,GET_BITS(pp->dnr___dcbnr[25],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y0,GET_BITS(pp->dnr___dcbnr[26],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y1,GET_BITS(pp->dnr___dcbnr[27],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y2,GET_BITS(pp->dnr___dcbnr[28],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y3,GET_BITS(pp->dnr___dcbnr[29],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y4,GET_BITS(pp->dnr___dcbnr[30],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y5,GET_BITS(pp->dnr___dcbnr[31],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y6,GET_BITS(pp->dnr___dcbnr[32],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y7,GET_BITS(pp->dnr___dcbnr[33],0,8));
		/*dnr___acbnr*/
		PE_CHPI_TBL0_F20_Wr(dnr.detail_ctrl.reg_bnr_ac_detail_min,GET_BITS(pp->dnr___acbnr[0],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.detail_ctrl.reg_bnr_ac_detail_max,GET_BITS(pp->dnr___acbnr[1],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th,GET_BITS(pp->dnr___acbnr[2],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th,GET_BITS(pp->dnr___acbnr[3],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h,GET_BITS(pp->dnr___acbnr[4],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min,GET_BITS(pp->dnr___acbnr[5],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max,GET_BITS(pp->dnr___acbnr[6],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th,GET_BITS(pp->dnr___acbnr[7],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_0,GET_BITS(pp->dnr___acbnr[8],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_1,GET_BITS(pp->dnr___acbnr[9],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_2,GET_BITS(pp->dnr___acbnr[10],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_3,GET_BITS(pp->dnr___acbnr[11],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0,GET_BITS(pp->dnr___acbnr[12],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1,GET_BITS(pp->dnr___acbnr[13],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2,GET_BITS(pp->dnr___acbnr[14],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3,GET_BITS(pp->dnr___acbnr[15],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min,GET_BITS(pp->dnr___acbnr[16],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max,GET_BITS(pp->dnr___acbnr[17],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v,GET_BITS(pp->dnr___acbnr[18],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th1,GET_BITS(pp->dnr___acbnr[19],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th2,GET_BITS(pp->dnr___acbnr[20],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th3,GET_BITS(pp->dnr___acbnr[21],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th4,GET_BITS(pp->dnr___acbnr[22],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th,GET_BITS(pp->dnr___acbnr[23],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0,GET_BITS(pp->dnr___acbnr[24],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1,GET_BITS(pp->dnr___acbnr[25],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2,GET_BITS(pp->dnr___acbnr[26],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3,GET_BITS(pp->dnr___acbnr[27],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0,GET_BITS(pp->dnr___acbnr[28],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1,GET_BITS(pp->dnr___acbnr[29],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2,GET_BITS(pp->dnr___acbnr[30],0,8));

		PE_CHPI_TBL0_F20_WrFL(dnr.dnr_max_ctrl.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.mnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_dc_bnr_ctrl_12.udata32);
		/*dnr_____mnr*/
		PE_CHPI_TBL0_F20_WrFL(dnr.mnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.mnr_ctrl_3.udata32);
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_F20_WrFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.sc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_dc_bnr_ctrl_8.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_dc_bnr_ctrl_9.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_dc_bnr_ctrl_10.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_dc_bnr_ctrl_11.udata32);
		/*dnr___acbnr*/
		PE_CHPI_TBL0_F20_WrFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_4.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_5.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_6.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.ac_bnr_ctrl_7.udata32);

		/* download dnr sqm db */
		/* see PE_NRD_HW_O20_DownloadDnrSqmCmnUserDb */
		/* PE_CHPI_DNR_SQM_F20_T                 sqm3;//14 */
		PE_CHPI_TBL0_F20_QWr(sqm3.ui32,pp->dnr__ui_val);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm3.data32[i],pp->dnr___sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm3.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(sqm3.cnt32,i);

		/* download dnr user db */
		/* see PE_NRD_HW_O20_DownloadDnrUserDb */
		/* PE_CHPI_DNR_USER_F20_T                usr1;//18 */
		PE_CHPI_TBL0_F20_QWr(usr1.ui32,pp->dnr__ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr1.data32[i],pp->dnr____buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr1.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(usr1.cnt32,i);

		/* count */
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_DNR);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM3);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR1);

		/* set user */
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dnr_max_ctrl.reg_dnr_max_enable,GET_BITS(pp->dnr______ui[0],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_0.reg_mnr_chroma_en,GET_BITS(pp->dnr______ui[1],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_0.reg_mnr_enable,GET_BITS(pp->dnr______ui[2],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_bnr_enable,GET_BITS(pp->dnr______ui[3],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_obj_gain_mul,GET_BITS(pp->dnr______ui[4],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en,GET_BITS(pp->dnr______ui[5],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en,GET_BITS(pp->dnr______ui[6],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_v_en,GET_BITS(pp->dnr______ui[7],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_h_en,GET_BITS(pp->dnr______ui[8],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_x_min,GET_BITS(pp->dnr______ui[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_x_max,GET_BITS(pp->dnr______ui[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_y_min,GET_BITS(pp->dnr______ui[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_y_max,GET_BITS(pp->dnr______ui[12],0,8));
		/*dnr_____mnr*/
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_1.reg_mmd_x_min,GET_BITS(pp->dnr_____mnr[0],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_1.reg_mmd_x_max,GET_BITS(pp->dnr_____mnr[1],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_1.reg_mmd_y_min,GET_BITS(pp->dnr_____mnr[2],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_1.reg_mmd_y_max,GET_BITS(pp->dnr_____mnr[3],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_3.reg_mmd_scale,GET_BITS(pp->dnr_____mnr[4],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,mnr_ctrl_3.reg_blur_sel,GET_BITS(pp->dnr_____mnr[5],0,1));
		/*dnr___dcbnr*/
		PE_CHPI_DNR_HW_F20_USER(p_dnr,detail_ctrl.reg_bnr_diff_p,GET_BITS(pp->dnr___dcbnr[0],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,detail_ctrl.reg_bnr_diff_l,GET_BITS(pp->dnr___dcbnr[1],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_motion_min,GET_BITS(pp->dnr___dcbnr[2],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_motion_max,GET_BITS(pp->dnr___dcbnr[3],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_blur_sel,GET_BITS(pp->dnr___dcbnr[4],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_1.reg_var_cut_resolution,GET_BITS(pp->dnr___dcbnr[5],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_1.reg_var_h_gain,GET_BITS(pp->dnr___dcbnr[6],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_1.reg_var_v_gain,GET_BITS(pp->dnr___dcbnr[7],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_1.reg_luma_gain_en,GET_BITS(pp->dnr___dcbnr[8],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_protection_th,GET_BITS(pp->dnr___dcbnr[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_protection_en,GET_BITS(pp->dnr___dcbnr[10],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_motion_en,GET_BITS(pp->dnr___dcbnr[11],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_var_en,GET_BITS(pp->dnr___dcbnr[12],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th0,GET_BITS(pp->dnr___dcbnr[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th1,GET_BITS(pp->dnr___dcbnr[14],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th2,GET_BITS(pp->dnr___dcbnr[15],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th3,GET_BITS(pp->dnr___dcbnr[16],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,sc_bnr_ctrl_0.reg_sc_bnr_en,GET_BITS(pp->dnr___dcbnr[17],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x0,GET_BITS(pp->dnr___dcbnr[18],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x1,GET_BITS(pp->dnr___dcbnr[19],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x2,GET_BITS(pp->dnr___dcbnr[20],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x3,GET_BITS(pp->dnr___dcbnr[21],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x4,GET_BITS(pp->dnr___dcbnr[22],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x5,GET_BITS(pp->dnr___dcbnr[23],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x6,GET_BITS(pp->dnr___dcbnr[24],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x7,GET_BITS(pp->dnr___dcbnr[25],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y0,GET_BITS(pp->dnr___dcbnr[26],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y1,GET_BITS(pp->dnr___dcbnr[27],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y2,GET_BITS(pp->dnr___dcbnr[28],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y3,GET_BITS(pp->dnr___dcbnr[29],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y4,GET_BITS(pp->dnr___dcbnr[30],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y5,GET_BITS(pp->dnr___dcbnr[31],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y6,GET_BITS(pp->dnr___dcbnr[32],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y7,GET_BITS(pp->dnr___dcbnr[33],0,8));
		/*dnr___acbnr*/
		PE_CHPI_DNR_HW_F20_USER(p_dnr,detail_ctrl.reg_bnr_ac_detail_min,GET_BITS(pp->dnr___acbnr[0],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,detail_ctrl.reg_bnr_ac_detail_max,GET_BITS(pp->dnr___acbnr[1],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th,GET_BITS(pp->dnr___acbnr[2],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th,GET_BITS(pp->dnr___acbnr[3],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h,GET_BITS(pp->dnr___acbnr[4],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min,GET_BITS(pp->dnr___acbnr[5],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max,GET_BITS(pp->dnr___acbnr[6],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th,GET_BITS(pp->dnr___acbnr[7],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_0,GET_BITS(pp->dnr___acbnr[8],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_1,GET_BITS(pp->dnr___acbnr[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_2,GET_BITS(pp->dnr___acbnr[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_3,GET_BITS(pp->dnr___acbnr[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0,GET_BITS(pp->dnr___acbnr[12],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1,GET_BITS(pp->dnr___acbnr[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2,GET_BITS(pp->dnr___acbnr[14],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3,GET_BITS(pp->dnr___acbnr[15],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min,GET_BITS(pp->dnr___acbnr[16],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max,GET_BITS(pp->dnr___acbnr[17],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v,GET_BITS(pp->dnr___acbnr[18],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th1,GET_BITS(pp->dnr___acbnr[19],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th2,GET_BITS(pp->dnr___acbnr[20],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th3,GET_BITS(pp->dnr___acbnr[21],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th4,GET_BITS(pp->dnr___acbnr[22],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th,GET_BITS(pp->dnr___acbnr[23],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0,GET_BITS(pp->dnr___acbnr[24],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1,GET_BITS(pp->dnr___acbnr[25],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2,GET_BITS(pp->dnr___acbnr[26],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3,GET_BITS(pp->dnr___acbnr[27],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0,GET_BITS(pp->dnr___acbnr[28],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1,GET_BITS(pp->dnr___acbnr[29],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2,GET_BITS(pp->dnr___acbnr[30],0,8));
	}while(0);
	return ret;
}

int PE_CHPI_DNR_HW_F20_GetCtrl(void)
{
	int ret = RET_OK;
	UINT32 i;
	LX_PE_NRD_DNR_ALL_CMN_T stParams;
	LX_PE_NRD_DNR_ALL_CMN_T *pp;
	UINT8 *pd;
	UINT32 *pd32;
	do{
		pp = &stParams;
		memset(pp,0,sizeof(LX_PE_NRD_DNR_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized
		PE_CHPI_TBL0_F20_RdFL(dnr.dnr_max_ctrl.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.mnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_dc_bnr_ctrl_12.udata32);
		/*dnr_____mnr*/
		PE_CHPI_TBL0_F20_RdFL(dnr.mnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.mnr_ctrl_3.udata32);
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_F20_RdFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.dc_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.dc_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.dc_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.sc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_dc_bnr_ctrl_8.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_dc_bnr_ctrl_9.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_dc_bnr_ctrl_10.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_dc_bnr_ctrl_11.udata32);
		/*dnr___acbnr*/
		PE_CHPI_TBL0_F20_RdFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_4.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_5.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_6.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.ac_bnr_ctrl_7.udata32);


		/* set tbl */
		pp->dnr______ui[0] =PE_CHPI_TBL0_F20_Rd(dnr.dnr_max_ctrl.reg_dnr_max_enable);
		pp->dnr______ui[1] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_0.reg_mnr_chroma_en);
		pp->dnr______ui[2] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_0.reg_mnr_enable);
		pp->dnr______ui[3] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_0.reg_dc_bnr_enable);
		pp->dnr______ui[4] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_0.reg_obj_gain_mul);
		pp->dnr______ui[5] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en);
		pp->dnr______ui[6] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en);
		pp->dnr______ui[7] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_en);
		pp->dnr______ui[8] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_en);
		pp->dnr______ui[9] =PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_min);
		pp->dnr______ui[10]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_max);
		pp->dnr______ui[11]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_min);
		pp->dnr______ui[12]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_max);
		/*dnr_____mnr*/
		pp->dnr_____mnr[0] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_1.reg_mmd_x_min);
		pp->dnr_____mnr[1] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_1.reg_mmd_x_max);
		pp->dnr_____mnr[2] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_1.reg_mmd_y_min);
		pp->dnr_____mnr[3] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_1.reg_mmd_y_max);
		pp->dnr_____mnr[4] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_3.reg_mmd_scale);
		pp->dnr_____mnr[5] =PE_CHPI_TBL0_F20_Rd(dnr.mnr_ctrl_3.reg_blur_sel);
		/*dnr___dcbnr*/
		pp->dnr___dcbnr[0] =PE_CHPI_TBL0_F20_Rd(dnr.detail_ctrl.reg_bnr_diff_p);
		pp->dnr___dcbnr[1] =PE_CHPI_TBL0_F20_Rd(dnr.detail_ctrl.reg_bnr_diff_l);
		pp->dnr___dcbnr[2] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_0.reg_dc_motion_min);
		pp->dnr___dcbnr[3] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_0.reg_dc_motion_max);
		pp->dnr___dcbnr[4] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_0.reg_dc_blur_sel);
		pp->dnr___dcbnr[5] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_1.reg_var_cut_resolution);
		pp->dnr___dcbnr[6] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_1.reg_var_h_gain);
		pp->dnr___dcbnr[7] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_1.reg_var_v_gain);
		pp->dnr___dcbnr[8] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_1.reg_luma_gain_en);
		pp->dnr___dcbnr[9] =PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_2.reg_dc_protection_th);
		pp->dnr___dcbnr[10]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_2.reg_dc_protection_en);
		pp->dnr___dcbnr[11]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_2.reg_dc_motion_en);
		pp->dnr___dcbnr[12]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_2.reg_dc_var_en);
		pp->dnr___dcbnr[13]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th0);
		pp->dnr___dcbnr[14]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th1);
		pp->dnr___dcbnr[15]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th2);
		pp->dnr___dcbnr[16]=PE_CHPI_TBL0_F20_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th3);
		pp->dnr___dcbnr[17]=PE_CHPI_TBL0_F20_Rd(dnr.sc_bnr_ctrl_0.reg_sc_bnr_en);
		pp->dnr___dcbnr[18]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x0);
		pp->dnr___dcbnr[19]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x1);
		pp->dnr___dcbnr[20]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x2);
		pp->dnr___dcbnr[21]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x3);
		pp->dnr___dcbnr[22]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x4);
		pp->dnr___dcbnr[23]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x5);
		pp->dnr___dcbnr[24]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x6);
		pp->dnr___dcbnr[25]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x7);
		pp->dnr___dcbnr[26]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y0);
		pp->dnr___dcbnr[27]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y1);
		pp->dnr___dcbnr[28]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y2);
		pp->dnr___dcbnr[29]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y3);
		pp->dnr___dcbnr[30]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y4);
		pp->dnr___dcbnr[31]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y5);
		pp->dnr___dcbnr[32]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y6);
		pp->dnr___dcbnr[33]=PE_CHPI_TBL0_F20_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y7);
		/*dnr___acbnr*/
		pp->dnr___acbnr[0] =PE_CHPI_TBL0_F20_Rd(dnr.detail_ctrl.reg_bnr_ac_detail_min);
		pp->dnr___acbnr[1] =PE_CHPI_TBL0_F20_Rd(dnr.detail_ctrl.reg_bnr_ac_detail_max);
		pp->dnr___acbnr[2] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th);
		pp->dnr___acbnr[3] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th);
		pp->dnr___acbnr[4] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h);
		pp->dnr___acbnr[5] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min);
		pp->dnr___acbnr[6] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max);
		pp->dnr___acbnr[7] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th);
		pp->dnr___acbnr[8] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_0);
		pp->dnr___acbnr[9] =PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_1);
		pp->dnr___acbnr[10]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_2);
		pp->dnr___acbnr[11]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_3);
		pp->dnr___acbnr[12]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0);
		pp->dnr___acbnr[13]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1);
		pp->dnr___acbnr[14]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2);
		pp->dnr___acbnr[15]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3);
		pp->dnr___acbnr[16]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min);
		pp->dnr___acbnr[17]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max);
		pp->dnr___acbnr[18]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v);
		pp->dnr___acbnr[19]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th1);
		pp->dnr___acbnr[20]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th2);
		pp->dnr___acbnr[21]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th3);
		pp->dnr___acbnr[22]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th4);
		pp->dnr___acbnr[23]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th);
		pp->dnr___acbnr[24]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0);
		pp->dnr___acbnr[25]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1);
		pp->dnr___acbnr[26]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2);
		pp->dnr___acbnr[27]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3);
		pp->dnr___acbnr[28]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0);
		pp->dnr___acbnr[29]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1);
		pp->dnr___acbnr[30]=PE_CHPI_TBL0_F20_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2);
		/* download dnr sq[32]=m db */
		/* see PE_NRD_HW_O[33]=20_DownloadDnrSqmCmnUserDb */
		/* PE_CHPI_DNR_SQM_F20_T				 sqm3;//14 */
		PE_CHPI_TBL0_F20_QRd(sqm3.ui32,pp->dnr__ui_val);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_F20_QRd(sqm3.data32[i],pp->dnr___sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm3.cnt32);

		/* download dnr user db */
		/* see PE_NRD_HW_O20_DownloadDnrUserDb */
		/* PE_CHPI_DNR_USER_F20_T				 usr1;//18 */
		PE_CHPI_TBL0_F20_QRd(usr1.ui32,pp->dnr__ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QRd(usr1.data32[i],pp->dnr____buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr1.cnt32);


		pd32 =	pp->dnr______ui;
		printk("set[%d] : dnr______ui\n"
		"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12]);
		pd32 = pp->dnr____buff;
		printk("set[%d] : dnr____buff\n"\
		"dnr____buff	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd = pp->dnr_____mnr;
		printk("set[%d] : dnr_____mnr\n"
		"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

		pd = pp->dnr___dcbnr;
		printk("set[%d] : dnr___dcbnr\n"
		"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33]);

		pd = pp->dnr___acbnr;
		printk("set[%d] : dnr___acbnr\n"
		"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[30]0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);

		pd32 = pp->dnr___sqmui;
		printk("[%d]dnr___sqmui:%d, cnt: %d\n", pp->win_id, pp->dnr__ui_val, i);
		printk( \
		"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);

	}while(0);
	return ret;
}


int PE_CHPI_DNR_HW_F20_SetDcntCtrl(void *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	LX_PE_NRD_DCNT_CMN_T *p_param;
	LX_PE_NRD_DCNT_ALL_CMN_T *pp;
	PE_DNR_HW_PARAM_DATA_F20_T *p_dnr = &_g_pe_dnr_hw_param_data_f20;
	PE_DNR_LED_HW_PARAM_DATA_F20_T *p_led = &_g_pe_dnr_led_hw_param_data_f20;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		CHECK_KNULL(p_led->reg_user.data);
		CHECK_KNULL(p_led->reg_mask.data);
		p_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
		pp = (LX_PE_NRD_DCNT_ALL_CMN_T *)p_param->data;

		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_0.reg_1st_out_rd_on,GET_BITS(pp->deconnd_____ui[0],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_0.reg_1st_out_rd_bit,GET_BITS(pp->deconnd_____ui[1],0,3));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_on,GET_BITS(pp->deconnd_____ui[2],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_bit,GET_BITS(pp->deconnd_____ui[3],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_17.reg_decon_1st_en,GET_BITS(pp->deconnd_____ui[4],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_69.reg_decon_2nd_en,GET_BITS(pp->deconnd_____ui[5],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconnd_____ui[6],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconnd_____ui[7],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconnd_____ui[8],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconnd_____ui[9],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconnd_____ui[10],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconnd_____ui[11],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconnd_____ui[12],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconnd_____ui[13],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconnd_____ui[14],0,8));
		/*dnr_dcnt*/
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_18.reg_var_cut_resolution,GET_BITS(pp->deconnd____cmn[0],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_18.reg_var_h_gain,GET_BITS(pp->deconnd____cmn[1],0,4));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_18.reg_var_chroma_en,GET_BITS(pp->deconnd____cmn[2],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th0,GET_BITS(pp->deconnd____cmn[3],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th1,GET_BITS(pp->deconnd____cmn[4],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th2,GET_BITS(pp->deconnd____cmn[5],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_x_th3,GET_BITS(pp->deconnd____cmn[6],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_y_th0,GET_BITS(pp->deconnd____cmn[7],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_y_th1,GET_BITS(pp->deconnd____cmn[8],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_23.reg_decon_var_y_th2,GET_BITS(pp->deconnd____cmn[9],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_23.reg_decon_var_y_th3,GET_BITS(pp->deconnd____cmn[10],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_23.reg_decon_luma_x_th0,GET_BITS(pp->deconnd____cmn[11],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th1,GET_BITS(pp->deconnd____cmn[12],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th2,GET_BITS(pp->deconnd____cmn[13],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th3,GET_BITS(pp->deconnd____cmn[14],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th4,GET_BITS(pp->deconnd____cmn[15],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th5,GET_BITS(pp->deconnd____cmn[16],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th6,GET_BITS(pp->deconnd____cmn[17],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_x_th7,GET_BITS(pp->deconnd____cmn[18],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th0,GET_BITS(pp->deconnd____cmn[19],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th1,GET_BITS(pp->deconnd____cmn[20],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th2,GET_BITS(pp->deconnd____cmn[21],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th3,GET_BITS(pp->deconnd____cmn[22],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th4,GET_BITS(pp->deconnd____cmn[23],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th5,GET_BITS(pp->deconnd____cmn[24],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th6,GET_BITS(pp->deconnd____cmn[25],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th7,GET_BITS(pp->deconnd____cmn[26],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_69.reg_2nd_var_chroma_en,GET_BITS(pp->deconnd____cmn[27],0,1));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_69.reg_2nd_var_cut_resolution,GET_BITS(pp->deconnd____cmn[28],0,3));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_69.reg_2nd_var_h_gain,GET_BITS(pp->deconnd____cmn[29],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_69.reg_2nd_var_v_gain,GET_BITS(pp->deconnd____cmn[30],0,2));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th0,GET_BITS(pp->deconnd____cmn[31],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th1,GET_BITS(pp->deconnd____cmn[32],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th2,GET_BITS(pp->deconnd____cmn[33],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th3,GET_BITS(pp->deconnd____cmn[34],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th4,GET_BITS(pp->deconnd____cmn[35],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th5,GET_BITS(pp->deconnd____cmn[36],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_72.reg_2nd_luma_x_th6,GET_BITS(pp->deconnd____cmn[37],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_72.reg_2nd_luma_x_th7,GET_BITS(pp->deconnd____cmn[38],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_72.reg_2nd_luma_y_th0,GET_BITS(pp->deconnd____cmn[39],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th1,GET_BITS(pp->deconnd____cmn[40],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th2,GET_BITS(pp->deconnd____cmn[41],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th3,GET_BITS(pp->deconnd____cmn[42],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th4,GET_BITS(pp->deconnd____cmn[43],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th5,GET_BITS(pp->deconnd____cmn[44],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th6,GET_BITS(pp->deconnd____cmn[45],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_75.reg_2nd_luma_y_th7,GET_BITS(pp->deconnd____cmn[46],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_75.reg_2nd_var_x_th0,GET_BITS(pp->deconnd____cmn[47],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_75.reg_2nd_var_x_th1,GET_BITS(pp->deconnd____cmn[48],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_76.reg_2nd_var_x_th2,GET_BITS(pp->deconnd____cmn[49],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_76.reg_2nd_var_x_th3,GET_BITS(pp->deconnd____cmn[50],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_76.reg_2nd_var_y_th0,GET_BITS(pp->deconnd____cmn[51],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th1,GET_BITS(pp->deconnd____cmn[52],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th2,GET_BITS(pp->deconnd____cmn[53],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th3,GET_BITS(pp->deconnd____cmn[54],0,10));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th3,GET_BITS(pp->deconnd____cmn[55],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th2,GET_BITS(pp->deconnd____cmn[56],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th1,GET_BITS(pp->deconnd____cmn[57],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th0,GET_BITS(pp->deconnd____cmn[58],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th3,GET_BITS(pp->deconnd____cmn[59],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th2,GET_BITS(pp->deconnd____cmn[60],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th1,GET_BITS(pp->deconnd____cmn[61],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th0,GET_BITS(pp->deconnd____cmn[62],0,8));
		/* face obj*/
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconnd___face[0],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconnd___face[1],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconnd___face[2],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconnd___face[3],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconnd___face[4],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconnd___face[5],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconnd___face[6],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconnd___face[7],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconnd___face[8],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconnd___face[9],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconnd___face[10],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconnd___face[11],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconnd___face[12],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconnd___face[13],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconnd___face[14],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconnd___face[15],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconnd___face[16],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconnd___face[17],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconnd___face[18],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconnd___face[19],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconnd___face[20],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconnd___face[21],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconnd___face[22],0,8));
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconnd___face[23],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_0.reg_1st_out_rd_on,GET_BITS(pp->deconled____ui[0],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_0.reg_1st_out_rd_bit,GET_BITS(pp->deconled____ui[1],0,3));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_7.reg_2nd_out_rd_on,GET_BITS(pp->deconled____ui[2],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_7.reg_2nd_out_rd_bit,GET_BITS(pp->deconled____ui[3],0,4));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_17.reg_decon_1st_en,GET_BITS(pp->deconled____ui[4],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_69.reg_decon_2nd_en,GET_BITS(pp->deconled____ui[5],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconled____ui[6],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconled____ui[7],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconled____ui[8],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconled____ui[9],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconled____ui[10],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconled____ui[11],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconled____ui[12],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconled____ui[13],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconled____ui[14],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_18.reg_var_cut_resolution,GET_BITS(pp->deconled___cmn[0],0,4));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_18.reg_var_h_gain,GET_BITS(pp->deconled___cmn[1],0,4));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_18.reg_var_chroma_en,GET_BITS(pp->deconled___cmn[2],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_21.reg_decon_var_x_th0,GET_BITS(pp->deconled___cmn[3],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_21.reg_decon_var_x_th1,GET_BITS(pp->deconled___cmn[4],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_21.reg_decon_var_x_th2,GET_BITS(pp->deconled___cmn[5],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_22.reg_decon_var_x_th3,GET_BITS(pp->deconled___cmn[6],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_22.reg_decon_var_y_th0,GET_BITS(pp->deconled___cmn[7],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_22.reg_decon_var_y_th1,GET_BITS(pp->deconled___cmn[8],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_23.reg_decon_var_y_th2,GET_BITS(pp->deconled___cmn[9],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_23.reg_decon_var_y_th3,GET_BITS(pp->deconled___cmn[10],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_23.reg_decon_luma_x_th0,GET_BITS(pp->deconled___cmn[11],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_24.reg_decon_luma_x_th1,GET_BITS(pp->deconled___cmn[12],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_24.reg_decon_luma_x_th2,GET_BITS(pp->deconled___cmn[13],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_24.reg_decon_luma_x_th3,GET_BITS(pp->deconled___cmn[14],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_25.reg_decon_luma_x_th4,GET_BITS(pp->deconled___cmn[15],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_25.reg_decon_luma_x_th5,GET_BITS(pp->deconled___cmn[16],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_25.reg_decon_luma_x_th6,GET_BITS(pp->deconled___cmn[17],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_26.reg_decon_luma_x_th7,GET_BITS(pp->deconled___cmn[18],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_26.reg_decon_luma_y_th0,GET_BITS(pp->deconled___cmn[19],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_26.reg_decon_luma_y_th1,GET_BITS(pp->deconled___cmn[20],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_27.reg_decon_luma_y_th2,GET_BITS(pp->deconled___cmn[21],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_27.reg_decon_luma_y_th3,GET_BITS(pp->deconled___cmn[22],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_27.reg_decon_luma_y_th4,GET_BITS(pp->deconled___cmn[23],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_28.reg_decon_luma_y_th5,GET_BITS(pp->deconled___cmn[24],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_28.reg_decon_luma_y_th6,GET_BITS(pp->deconled___cmn[25],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_28.reg_decon_luma_y_th7,GET_BITS(pp->deconled___cmn[26],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_69.reg_2nd_var_chroma_en,GET_BITS(pp->deconled___cmn[27],0,1));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_69.reg_2nd_var_cut_resolution,GET_BITS(pp->deconled___cmn[28],0,3));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_69.reg_2nd_var_h_gain,GET_BITS(pp->deconled___cmn[29],0,2));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_69.reg_2nd_var_v_gain,GET_BITS(pp->deconled___cmn[30],0,2));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_70.reg_2nd_luma_x_th0,GET_BITS(pp->deconled___cmn[31],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_70.reg_2nd_luma_x_th1,GET_BITS(pp->deconled___cmn[32],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_70.reg_2nd_luma_x_th2,GET_BITS(pp->deconled___cmn[33],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_71.reg_2nd_luma_x_th3,GET_BITS(pp->deconled___cmn[34],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_71.reg_2nd_luma_x_th4,GET_BITS(pp->deconled___cmn[35],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_71.reg_2nd_luma_x_th5,GET_BITS(pp->deconled___cmn[36],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_72.reg_2nd_luma_x_th6,GET_BITS(pp->deconled___cmn[37],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_72.reg_2nd_luma_x_th7,GET_BITS(pp->deconled___cmn[38],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_72.reg_2nd_luma_y_th0,GET_BITS(pp->deconled___cmn[39],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_73.reg_2nd_luma_y_th1,GET_BITS(pp->deconled___cmn[40],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_73.reg_2nd_luma_y_th2,GET_BITS(pp->deconled___cmn[41],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_73.reg_2nd_luma_y_th3,GET_BITS(pp->deconled___cmn[42],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_74.reg_2nd_luma_y_th4,GET_BITS(pp->deconled___cmn[43],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_74.reg_2nd_luma_y_th5,GET_BITS(pp->deconled___cmn[44],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_74.reg_2nd_luma_y_th6,GET_BITS(pp->deconled___cmn[45],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_75.reg_2nd_luma_y_th7,GET_BITS(pp->deconled___cmn[46],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_75.reg_2nd_var_x_th0,GET_BITS(pp->deconled___cmn[47],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_75.reg_2nd_var_x_th1,GET_BITS(pp->deconled___cmn[48],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_76.reg_2nd_var_x_th2,GET_BITS(pp->deconled___cmn[49],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_76.reg_2nd_var_x_th3,GET_BITS(pp->deconled___cmn[50],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_76.reg_2nd_var_y_th0,GET_BITS(pp->deconled___cmn[51],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_77.reg_2nd_var_y_th1,GET_BITS(pp->deconled___cmn[52],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_77.reg_2nd_var_y_th2,GET_BITS(pp->deconled___cmn[53],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_77.reg_2nd_var_y_th3,GET_BITS(pp->deconled___cmn[54],0,10));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_78.reg_2nd_diff_x_th3,GET_BITS(pp->deconled___cmn[55],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_78.reg_2nd_diff_x_th2,GET_BITS(pp->deconled___cmn[56],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_78.reg_2nd_diff_x_th1,GET_BITS(pp->deconled___cmn[57],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_78.reg_2nd_diff_x_th0,GET_BITS(pp->deconled___cmn[58],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_79.reg_2nd_diff_y_th3,GET_BITS(pp->deconled___cmn[59],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_79.reg_2nd_diff_y_th2,GET_BITS(pp->deconled___cmn[60],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_79.reg_2nd_diff_y_th1,GET_BITS(pp->deconled___cmn[61],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_79.reg_2nd_diff_y_th0,GET_BITS(pp->deconled___cmn[62],0,8));
		/* face obj*/
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconled__face[0],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconled__face[1],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconled__face[2],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconled__face[3],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconled__face[4],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconled__face[5],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconled__face[6],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconled__face[7],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconled__face[8],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconled__face[9],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconled__face[10],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconled__face[11],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconled__face[12],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconled__face[13],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconled__face[14],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconled__face[15],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconled__face[16],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconled__face[17],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconled__face[18],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconled__face[19],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconled__face[20],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconled__face[21],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconled__face[22],0,8));
		PE_CHPI_TBL0_F20_Wr(led.reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconled__face[23],0,8));

		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_56.udata32);
		/*dnr_dcnt*/
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_74.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_75.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_76.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_77.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_78.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_79.udata32);
		/* face obj*/
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_55.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_56.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_74.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_75.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_76.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_77.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_78.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_79.udata32);
		/* face obj*/
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_F20_WrFL(led.reg_decon_ctrl_55.udata32);

		/* download dct sqm db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntSqmCmnUserDb */
		/* PE_CHPI_DNR_DCNT_SQM_F20_T            sqm4;//15 */
		PE_CHPI_TBL0_F20_QWr(sqm4.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm4.data32[i],pp->deconnd__sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm4.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(sqm4.cnt32,i);

		/* download dct user db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntUserDb */
		/* PE_CHPI_DNR_DCNT_USER_F20_T           usr2;//19 */
		PE_CHPI_TBL0_F20_QWr(usr2.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr2.data32[i],pp->deconnd___buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr2.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(usr2.cnt32,i);

		/* download dct led sqm db */
		/* see PE_NRD_HW_O20_DownloadLedDcntSqmCmnUserDb */
		/* PE_CHPI_LED_DCNT_SQM_F20_T            sqm5;//16 */
		PE_CHPI_TBL0_F20_QWr(sqm5.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QWr(sqm5.data32[i],pp->deconled_sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm5.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(sqm5.cnt32,i);

		/* download dct led user db */
		/* see PE_NRD_HW_O20_DownloadLedDcntUserDb */
		/* PE_CHPI_LED_DCNT_USER_F20_T           usr3;//20 */
		PE_CHPI_TBL0_F20_QWr(usr3.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QWr(usr3.data32[i],pp->deconled__buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr3.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QWr(usr3.cnt32,i);

		/* count */
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_DNR);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_LED);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM4);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR2);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_SQM5);
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_USR3);

		/* set user */
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_0.reg_1st_out_rd_on,GET_BITS(pp->deconnd_____ui[0],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_0.reg_1st_out_rd_bit,GET_BITS(pp->deconnd_____ui[1],0,3));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_7.reg_2nd_out_rd_on,GET_BITS(pp->deconnd_____ui[2],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_7.reg_2nd_out_rd_bit,GET_BITS(pp->deconnd_____ui[3],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_17.reg_decon_1st_en,GET_BITS(pp->deconnd_____ui[4],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_69.reg_decon_2nd_en,GET_BITS(pp->deconnd_____ui[5],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconnd_____ui[6],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconnd_____ui[7],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconnd_____ui[8],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconnd_____ui[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconnd_____ui[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconnd_____ui[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconnd_____ui[12],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconnd_____ui[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconnd_____ui[14],0,8));
		/*dnr_dcnt*/
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_18.reg_var_cut_resolution,GET_BITS(pp->deconnd____cmn[0],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_18.reg_var_h_gain,GET_BITS(pp->deconnd____cmn[1],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_18.reg_var_chroma_en,GET_BITS(pp->deconnd____cmn[2],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th0,GET_BITS(pp->deconnd____cmn[3],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th1,GET_BITS(pp->deconnd____cmn[4],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th2,GET_BITS(pp->deconnd____cmn[5],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_x_th3,GET_BITS(pp->deconnd____cmn[6],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_y_th0,GET_BITS(pp->deconnd____cmn[7],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_y_th1,GET_BITS(pp->deconnd____cmn[8],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_23.reg_decon_var_y_th2,GET_BITS(pp->deconnd____cmn[9],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_23.reg_decon_var_y_th3,GET_BITS(pp->deconnd____cmn[10],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_23.reg_decon_luma_x_th0,GET_BITS(pp->deconnd____cmn[11],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th1,GET_BITS(pp->deconnd____cmn[12],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th2,GET_BITS(pp->deconnd____cmn[13],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th3,GET_BITS(pp->deconnd____cmn[14],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th4,GET_BITS(pp->deconnd____cmn[15],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th5,GET_BITS(pp->deconnd____cmn[16],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th6,GET_BITS(pp->deconnd____cmn[17],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_x_th7,GET_BITS(pp->deconnd____cmn[18],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_y_th0,GET_BITS(pp->deconnd____cmn[19],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_y_th1,GET_BITS(pp->deconnd____cmn[20],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th2,GET_BITS(pp->deconnd____cmn[21],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th3,GET_BITS(pp->deconnd____cmn[22],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th4,GET_BITS(pp->deconnd____cmn[23],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th5,GET_BITS(pp->deconnd____cmn[24],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th6,GET_BITS(pp->deconnd____cmn[25],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th7,GET_BITS(pp->deconnd____cmn[26],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_69.reg_2nd_var_chroma_en,GET_BITS(pp->deconnd____cmn[27],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_69.reg_2nd_var_cut_resolution,GET_BITS(pp->deconnd____cmn[28],0,3));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_69.reg_2nd_var_h_gain,GET_BITS(pp->deconnd____cmn[29],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_69.reg_2nd_var_v_gain,GET_BITS(pp->deconnd____cmn[30],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_70.reg_2nd_luma_x_th0,GET_BITS(pp->deconnd____cmn[31],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_70.reg_2nd_luma_x_th1,GET_BITS(pp->deconnd____cmn[32],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_70.reg_2nd_luma_x_th2,GET_BITS(pp->deconnd____cmn[33],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_71.reg_2nd_luma_x_th3,GET_BITS(pp->deconnd____cmn[34],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_71.reg_2nd_luma_x_th4,GET_BITS(pp->deconnd____cmn[35],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_71.reg_2nd_luma_x_th5,GET_BITS(pp->deconnd____cmn[36],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_72.reg_2nd_luma_x_th6,GET_BITS(pp->deconnd____cmn[37],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_72.reg_2nd_luma_x_th7,GET_BITS(pp->deconnd____cmn[38],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_72.reg_2nd_luma_y_th0,GET_BITS(pp->deconnd____cmn[39],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_73.reg_2nd_luma_y_th1,GET_BITS(pp->deconnd____cmn[40],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_73.reg_2nd_luma_y_th2,GET_BITS(pp->deconnd____cmn[41],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_73.reg_2nd_luma_y_th3,GET_BITS(pp->deconnd____cmn[42],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_74.reg_2nd_luma_y_th4,GET_BITS(pp->deconnd____cmn[43],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_74.reg_2nd_luma_y_th5,GET_BITS(pp->deconnd____cmn[44],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_74.reg_2nd_luma_y_th6,GET_BITS(pp->deconnd____cmn[45],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_75.reg_2nd_luma_y_th7,GET_BITS(pp->deconnd____cmn[46],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_75.reg_2nd_var_x_th0,GET_BITS(pp->deconnd____cmn[47],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_75.reg_2nd_var_x_th1,GET_BITS(pp->deconnd____cmn[48],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_76.reg_2nd_var_x_th2,GET_BITS(pp->deconnd____cmn[49],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_76.reg_2nd_var_x_th3,GET_BITS(pp->deconnd____cmn[50],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_76.reg_2nd_var_y_th0,GET_BITS(pp->deconnd____cmn[51],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_77.reg_2nd_var_y_th1,GET_BITS(pp->deconnd____cmn[52],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_77.reg_2nd_var_y_th2,GET_BITS(pp->deconnd____cmn[53],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_77.reg_2nd_var_y_th3,GET_BITS(pp->deconnd____cmn[54],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_78.reg_2nd_diff_x_th3,GET_BITS(pp->deconnd____cmn[55],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_78.reg_2nd_diff_x_th2,GET_BITS(pp->deconnd____cmn[56],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_78.reg_2nd_diff_x_th1,GET_BITS(pp->deconnd____cmn[57],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_78.reg_2nd_diff_x_th0,GET_BITS(pp->deconnd____cmn[58],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_79.reg_2nd_diff_y_th3,GET_BITS(pp->deconnd____cmn[59],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_79.reg_2nd_diff_y_th2,GET_BITS(pp->deconnd____cmn[60],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_79.reg_2nd_diff_y_th1,GET_BITS(pp->deconnd____cmn[61],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_79.reg_2nd_diff_y_th0,GET_BITS(pp->deconnd____cmn[62],0,8));
		/* face obj*/
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconnd___face[0],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconnd___face[1],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconnd___face[2],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconnd___face[3],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconnd___face[4],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconnd___face[5],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconnd___face[6],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconnd___face[7],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconnd___face[8],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconnd___face[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconnd___face[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconnd___face[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconnd___face[12],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconnd___face[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconnd___face[14],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconnd___face[15],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconnd___face[16],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconnd___face[17],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconnd___face[18],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconnd___face[19],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconnd___face[20],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconnd___face[21],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconnd___face[22],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconnd___face[23],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_0.reg_1st_out_rd_on,GET_BITS(pp->deconled____ui[0],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_0.reg_1st_out_rd_bit,GET_BITS(pp->deconled____ui[1],0,3));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_7.reg_2nd_out_rd_on,GET_BITS(pp->deconled____ui[2],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_7.reg_2nd_out_rd_bit,GET_BITS(pp->deconled____ui[3],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_17.reg_decon_1st_en,GET_BITS(pp->deconled____ui[4],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_69.reg_decon_2nd_en,GET_BITS(pp->deconled____ui[5],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconled____ui[6],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconled____ui[7],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconled____ui[8],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconled____ui[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconled____ui[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconled____ui[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconled____ui[12],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconled____ui[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconled____ui[14],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_18.reg_var_cut_resolution,GET_BITS(pp->deconled___cmn[0],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_18.reg_var_h_gain,GET_BITS(pp->deconled___cmn[1],0,4));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_18.reg_var_chroma_en,GET_BITS(pp->deconled___cmn[2],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_21.reg_decon_var_x_th0,GET_BITS(pp->deconled___cmn[3],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_21.reg_decon_var_x_th1,GET_BITS(pp->deconled___cmn[4],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_21.reg_decon_var_x_th2,GET_BITS(pp->deconled___cmn[5],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_22.reg_decon_var_x_th3,GET_BITS(pp->deconled___cmn[6],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_22.reg_decon_var_y_th0,GET_BITS(pp->deconled___cmn[7],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_22.reg_decon_var_y_th1,GET_BITS(pp->deconled___cmn[8],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_23.reg_decon_var_y_th2,GET_BITS(pp->deconled___cmn[9],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_23.reg_decon_var_y_th3,GET_BITS(pp->deconled___cmn[10],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_23.reg_decon_luma_x_th0,GET_BITS(pp->deconled___cmn[11],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_24.reg_decon_luma_x_th1,GET_BITS(pp->deconled___cmn[12],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_24.reg_decon_luma_x_th2,GET_BITS(pp->deconled___cmn[13],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_24.reg_decon_luma_x_th3,GET_BITS(pp->deconled___cmn[14],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_25.reg_decon_luma_x_th4,GET_BITS(pp->deconled___cmn[15],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_25.reg_decon_luma_x_th5,GET_BITS(pp->deconled___cmn[16],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_25.reg_decon_luma_x_th6,GET_BITS(pp->deconled___cmn[17],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_26.reg_decon_luma_x_th7,GET_BITS(pp->deconled___cmn[18],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_26.reg_decon_luma_y_th0,GET_BITS(pp->deconled___cmn[19],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_26.reg_decon_luma_y_th1,GET_BITS(pp->deconled___cmn[20],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_27.reg_decon_luma_y_th2,GET_BITS(pp->deconled___cmn[21],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_27.reg_decon_luma_y_th3,GET_BITS(pp->deconled___cmn[22],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_27.reg_decon_luma_y_th4,GET_BITS(pp->deconled___cmn[23],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_28.reg_decon_luma_y_th5,GET_BITS(pp->deconled___cmn[24],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_28.reg_decon_luma_y_th6,GET_BITS(pp->deconled___cmn[25],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_28.reg_decon_luma_y_th7,GET_BITS(pp->deconled___cmn[26],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_69.reg_2nd_var_chroma_en,GET_BITS(pp->deconled___cmn[27],0,1));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_69.reg_2nd_var_cut_resolution,GET_BITS(pp->deconled___cmn[28],0,3));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_69.reg_2nd_var_h_gain,GET_BITS(pp->deconled___cmn[29],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_69.reg_2nd_var_v_gain,GET_BITS(pp->deconled___cmn[30],0,2));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_70.reg_2nd_luma_x_th0,GET_BITS(pp->deconled___cmn[31],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_70.reg_2nd_luma_x_th1,GET_BITS(pp->deconled___cmn[32],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_70.reg_2nd_luma_x_th2,GET_BITS(pp->deconled___cmn[33],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_71.reg_2nd_luma_x_th3,GET_BITS(pp->deconled___cmn[34],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_71.reg_2nd_luma_x_th4,GET_BITS(pp->deconled___cmn[35],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_71.reg_2nd_luma_x_th5,GET_BITS(pp->deconled___cmn[36],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_72.reg_2nd_luma_x_th6,GET_BITS(pp->deconled___cmn[37],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_72.reg_2nd_luma_x_th7,GET_BITS(pp->deconled___cmn[38],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_72.reg_2nd_luma_y_th0,GET_BITS(pp->deconled___cmn[39],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_73.reg_2nd_luma_y_th1,GET_BITS(pp->deconled___cmn[40],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_73.reg_2nd_luma_y_th2,GET_BITS(pp->deconled___cmn[41],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_73.reg_2nd_luma_y_th3,GET_BITS(pp->deconled___cmn[42],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_74.reg_2nd_luma_y_th4,GET_BITS(pp->deconled___cmn[43],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_74.reg_2nd_luma_y_th5,GET_BITS(pp->deconled___cmn[44],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_74.reg_2nd_luma_y_th6,GET_BITS(pp->deconled___cmn[45],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_75.reg_2nd_luma_y_th7,GET_BITS(pp->deconled___cmn[46],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_75.reg_2nd_var_x_th0,GET_BITS(pp->deconled___cmn[47],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_75.reg_2nd_var_x_th1,GET_BITS(pp->deconled___cmn[48],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_76.reg_2nd_var_x_th2,GET_BITS(pp->deconled___cmn[49],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_76.reg_2nd_var_x_th3,GET_BITS(pp->deconled___cmn[50],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_76.reg_2nd_var_y_th0,GET_BITS(pp->deconled___cmn[51],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_77.reg_2nd_var_y_th1,GET_BITS(pp->deconled___cmn[52],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_77.reg_2nd_var_y_th2,GET_BITS(pp->deconled___cmn[53],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_77.reg_2nd_var_y_th3,GET_BITS(pp->deconled___cmn[54],0,10));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_78.reg_2nd_diff_x_th3,GET_BITS(pp->deconled___cmn[55],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_78.reg_2nd_diff_x_th2,GET_BITS(pp->deconled___cmn[56],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_78.reg_2nd_diff_x_th1,GET_BITS(pp->deconled___cmn[57],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_78.reg_2nd_diff_x_th0,GET_BITS(pp->deconled___cmn[58],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_79.reg_2nd_diff_y_th3,GET_BITS(pp->deconled___cmn[59],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_79.reg_2nd_diff_y_th2,GET_BITS(pp->deconled___cmn[60],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_79.reg_2nd_diff_y_th1,GET_BITS(pp->deconled___cmn[61],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_79.reg_2nd_diff_y_th0,GET_BITS(pp->deconled___cmn[62],0,8));
		/* face obj*/
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconled__face[0],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconled__face[1],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconled__face[2],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconled__face[3],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconled__face[4],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconled__face[5],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconled__face[6],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconled__face[7],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconled__face[8],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconled__face[9],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconled__face[10],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconled__face[11],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconled__face[12],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconled__face[13],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconled__face[14],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconled__face[15],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconled__face[16],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconled__face[17],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconled__face[18],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconled__face[19],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconled__face[20],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconled__face[21],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconled__face[22],0,8));
		PE_CHPI_DNR_HW_F20_USER(p_led,reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconled__face[23],0,8));
	}while(0);
	return ret;
}
int PE_CHPI_DNR_HW_F20_GetDcntCtrl(void)
{
	int ret = RET_OK;
	UINT32 i;
	UINT8  *pd8;
	UINT16 *pd;
	UINT32 *pd32;
	LX_PE_NRD_DCNT_ALL_CMN_T stParams;
	LX_PE_NRD_DCNT_ALL_CMN_T *pp;
	do{
		pp =&stParams;
		memset(pp,0,sizeof(LX_PE_NRD_DCNT_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_56.udata32);
		/*dnr_dcnt*/
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_74.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_75.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_76.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_77.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_78.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_79.udata32);
		/* face obj*/
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_F20_RdFL(dnr.reg_decon_ctrl_55.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_56.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_74.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_75.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_76.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_77.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_78.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_79.udata32);
		/* face obj*/
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_F20_RdFL(led.reg_decon_ctrl_55.udata32);

		pp->deconnd_____ui[0] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_0.reg_1st_out_rd_on);
		pp->deconnd_____ui[1] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_0.reg_1st_out_rd_bit);
		pp->deconnd_____ui[2] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_on);
		pp->deconnd_____ui[3] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_bit);
		pp->deconnd_____ui[4] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_17.reg_decon_1st_en);
		pp->deconnd_____ui[5] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_69.reg_decon_2nd_en);
		pp->deconnd_____ui[6] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th3);
		pp->deconnd_____ui[7] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th2);
		pp->deconnd_____ui[8] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th1);
		pp->deconnd_____ui[9] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th0);
		pp->deconnd_____ui[10]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th3);
		pp->deconnd_____ui[11]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th2);
		pp->deconnd_____ui[12]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th1);
		pp->deconnd_____ui[13]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th0);
		pp->deconnd_____ui[14]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_56.reg_face_master_gain);
		/*dnr_dcnt*/
		pp->deconnd____cmn[0] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_18.reg_var_cut_resolution);
		pp->deconnd____cmn[1] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_18.reg_var_h_gain);
		pp->deconnd____cmn[2] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_18.reg_var_chroma_en);
		pp->deconnd____cmn[3] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th0);
		pp->deconnd____cmn[4] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th1);
		pp->deconnd____cmn[5] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th2);
		pp->deconnd____cmn[6] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_x_th3);
		pp->deconnd____cmn[7] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_y_th0);
		pp->deconnd____cmn[8] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_y_th1);
		pp->deconnd____cmn[9] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_23.reg_decon_var_y_th2);
		pp->deconnd____cmn[10]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_23.reg_decon_var_y_th3);
		pp->deconnd____cmn[11]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_23.reg_decon_luma_x_th0);
		pp->deconnd____cmn[12]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th1);
		pp->deconnd____cmn[13]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th2);
		pp->deconnd____cmn[14]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th3);
		pp->deconnd____cmn[15]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th4);
		pp->deconnd____cmn[16]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th5);
		pp->deconnd____cmn[17]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th6);
		pp->deconnd____cmn[18]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_x_th7);
		pp->deconnd____cmn[19]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th0);
		pp->deconnd____cmn[20]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th1);
		pp->deconnd____cmn[21]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th2);
		pp->deconnd____cmn[22]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th3);
		pp->deconnd____cmn[23]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th4);
		pp->deconnd____cmn[24]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th5);
		pp->deconnd____cmn[25]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th6);
		pp->deconnd____cmn[26]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th7);
		pp->deconnd____cmn[27]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_69.reg_2nd_var_chroma_en);
		pp->deconnd____cmn[28]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_69.reg_2nd_var_cut_resolution);
		pp->deconnd____cmn[29]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_69.reg_2nd_var_h_gain);
		pp->deconnd____cmn[30]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_69.reg_2nd_var_v_gain);
		pp->deconnd____cmn[31]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th0);
		pp->deconnd____cmn[32]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th1);
		pp->deconnd____cmn[33]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_70.reg_2nd_luma_x_th2);
		pp->deconnd____cmn[34]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th3);
		pp->deconnd____cmn[35]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th4);
		pp->deconnd____cmn[36]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_71.reg_2nd_luma_x_th5);
		pp->deconnd____cmn[37]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_72.reg_2nd_luma_x_th6);
		pp->deconnd____cmn[38]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_72.reg_2nd_luma_x_th7);
		pp->deconnd____cmn[39]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_72.reg_2nd_luma_y_th0);
		pp->deconnd____cmn[40]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th1);
		pp->deconnd____cmn[41]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th2);
		pp->deconnd____cmn[42]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_73.reg_2nd_luma_y_th3);
		pp->deconnd____cmn[43]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th4);
		pp->deconnd____cmn[44]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th5);
		pp->deconnd____cmn[45]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_74.reg_2nd_luma_y_th6);
		pp->deconnd____cmn[46]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_75.reg_2nd_luma_y_th7);
		pp->deconnd____cmn[47]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_75.reg_2nd_var_x_th0);
		pp->deconnd____cmn[48]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_75.reg_2nd_var_x_th1);
		pp->deconnd____cmn[49]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_76.reg_2nd_var_x_th2);
		pp->deconnd____cmn[50]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_76.reg_2nd_var_x_th3);
		pp->deconnd____cmn[51]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_76.reg_2nd_var_y_th0);
		pp->deconnd____cmn[52]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th1);
		pp->deconnd____cmn[53]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th2);
		pp->deconnd____cmn[54]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_77.reg_2nd_var_y_th3);
		pp->deconnd____cmn[55]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th3);
		pp->deconnd____cmn[56]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th2);
		pp->deconnd____cmn[57]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th1);
		pp->deconnd____cmn[58]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_78.reg_2nd_diff_x_th0);
		pp->deconnd____cmn[59]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th3);
		pp->deconnd____cmn[60]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th2);
		pp->deconnd____cmn[61]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th1);
		pp->deconnd____cmn[62]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_79.reg_2nd_diff_y_th0);
		/* face obj*/
		pp->deconnd___face[0] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x0);
		pp->deconnd___face[1] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x1);
		pp->deconnd___face[2] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x2);
		pp->deconnd___face[3] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x3);
		pp->deconnd___face[4] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x0);
		pp->deconnd___face[5] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x1);
		pp->deconnd___face[6] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x2);
		pp->deconnd___face[7] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x3);
		pp->deconnd___face[8] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x0);
		pp->deconnd___face[9] =PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x1);
		pp->deconnd___face[10]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x2);
		pp->deconnd___face[11]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x3);
		pp->deconnd___face[12]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y0);
		pp->deconnd___face[13]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y1);
		pp->deconnd___face[14]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y2);
		pp->deconnd___face[15]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y3);
		pp->deconnd___face[16]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x0);
		pp->deconnd___face[17]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x1);
		pp->deconnd___face[18]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x2);
		pp->deconnd___face[19]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x3);
		pp->deconnd___face[20]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y0);
		pp->deconnd___face[21]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y1);
		pp->deconnd___face[22]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y2);
		pp->deconnd___face[23]=PE_CHPI_TBL0_F20_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y3);
		pp->deconled____ui[0] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_0.reg_1st_out_rd_on);
		pp->deconled____ui[1] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_0.reg_1st_out_rd_bit);
		pp->deconled____ui[2] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_7.reg_2nd_out_rd_on);
		pp->deconled____ui[3] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_7.reg_2nd_out_rd_bit);
		pp->deconled____ui[4] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_17.reg_decon_1st_en);
		pp->deconled____ui[5] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_69.reg_decon_2nd_en);
		pp->deconled____ui[6] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_19.reg_decon_diff_x_th3);
		pp->deconled____ui[7] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_19.reg_decon_diff_x_th2);
		pp->deconled____ui[8] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_19.reg_decon_diff_x_th1);
		pp->deconled____ui[9] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_19.reg_decon_diff_x_th0);
		pp->deconled____ui[10]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_20.reg_decon_diff_y_th3);
		pp->deconled____ui[11]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_20.reg_decon_diff_y_th2);
		pp->deconled____ui[12]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_20.reg_decon_diff_y_th1);
		pp->deconled____ui[13]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_20.reg_decon_diff_y_th0);
		pp->deconled____ui[14]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_56.reg_face_master_gain);
		pp->deconled___cmn[0] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_18.reg_var_cut_resolution);
		pp->deconled___cmn[1] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_18.reg_var_h_gain);
		pp->deconled___cmn[2] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_18.reg_var_chroma_en);
		pp->deconled___cmn[3] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_21.reg_decon_var_x_th0);
		pp->deconled___cmn[4] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_21.reg_decon_var_x_th1);
		pp->deconled___cmn[5] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_21.reg_decon_var_x_th2);
		pp->deconled___cmn[6] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_22.reg_decon_var_x_th3);
		pp->deconled___cmn[7] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_22.reg_decon_var_y_th0);
		pp->deconled___cmn[8] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_22.reg_decon_var_y_th1);
		pp->deconled___cmn[9] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_23.reg_decon_var_y_th2);
		pp->deconled___cmn[10]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_23.reg_decon_var_y_th3);
		pp->deconled___cmn[11]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_23.reg_decon_luma_x_th0);
		pp->deconled___cmn[12]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_24.reg_decon_luma_x_th1);
		pp->deconled___cmn[13]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_24.reg_decon_luma_x_th2);
		pp->deconled___cmn[14]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_24.reg_decon_luma_x_th3);
		pp->deconled___cmn[15]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_25.reg_decon_luma_x_th4);
		pp->deconled___cmn[16]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_25.reg_decon_luma_x_th5);
		pp->deconled___cmn[17]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_25.reg_decon_luma_x_th6);
		pp->deconled___cmn[18]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_26.reg_decon_luma_x_th7);
		pp->deconled___cmn[19]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_26.reg_decon_luma_y_th0);
		pp->deconled___cmn[20]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_26.reg_decon_luma_y_th1);
		pp->deconled___cmn[21]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_27.reg_decon_luma_y_th2);
		pp->deconled___cmn[22]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_27.reg_decon_luma_y_th3);
		pp->deconled___cmn[23]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_27.reg_decon_luma_y_th4);
		pp->deconled___cmn[24]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_28.reg_decon_luma_y_th5);
		pp->deconled___cmn[25]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_28.reg_decon_luma_y_th6);
		pp->deconled___cmn[26]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_28.reg_decon_luma_y_th7);
		pp->deconled___cmn[27]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_69.reg_2nd_var_chroma_en);
		pp->deconled___cmn[28]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_69.reg_2nd_var_cut_resolution);
		pp->deconled___cmn[29]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_69.reg_2nd_var_h_gain);
		pp->deconled___cmn[30]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_69.reg_2nd_var_v_gain);
		pp->deconled___cmn[31]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_70.reg_2nd_luma_x_th0);
		pp->deconled___cmn[32]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_70.reg_2nd_luma_x_th1);
		pp->deconled___cmn[33]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_70.reg_2nd_luma_x_th2);
		pp->deconled___cmn[34]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_71.reg_2nd_luma_x_th3);
		pp->deconled___cmn[35]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_71.reg_2nd_luma_x_th4);
		pp->deconled___cmn[36]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_71.reg_2nd_luma_x_th5);
		pp->deconled___cmn[37]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_72.reg_2nd_luma_x_th6);
		pp->deconled___cmn[38]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_72.reg_2nd_luma_x_th7);
		pp->deconled___cmn[39]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_72.reg_2nd_luma_y_th0);
		pp->deconled___cmn[40]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_73.reg_2nd_luma_y_th1);
		pp->deconled___cmn[41]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_73.reg_2nd_luma_y_th2);
		pp->deconled___cmn[42]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_73.reg_2nd_luma_y_th3);
		pp->deconled___cmn[43]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_74.reg_2nd_luma_y_th4);
		pp->deconled___cmn[44]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_74.reg_2nd_luma_y_th5);
		pp->deconled___cmn[45]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_74.reg_2nd_luma_y_th6);
		pp->deconled___cmn[46]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_75.reg_2nd_luma_y_th7);
		pp->deconled___cmn[47]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_75.reg_2nd_var_x_th0);
		pp->deconled___cmn[48]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_75.reg_2nd_var_x_th1);
		pp->deconled___cmn[49]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_76.reg_2nd_var_x_th2);
		pp->deconled___cmn[50]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_76.reg_2nd_var_x_th3);
		pp->deconled___cmn[51]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_76.reg_2nd_var_y_th0);
		pp->deconled___cmn[52]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_77.reg_2nd_var_y_th1);
		pp->deconled___cmn[53]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_77.reg_2nd_var_y_th2);
		pp->deconled___cmn[54]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_77.reg_2nd_var_y_th3);
		pp->deconled___cmn[55]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_78.reg_2nd_diff_x_th3);
		pp->deconled___cmn[56]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_78.reg_2nd_diff_x_th2);
		pp->deconled___cmn[57]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_78.reg_2nd_diff_x_th1);
		pp->deconled___cmn[58]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_78.reg_2nd_diff_x_th0);
		pp->deconled___cmn[59]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_79.reg_2nd_diff_y_th3);
		pp->deconled___cmn[60]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_79.reg_2nd_diff_y_th2);
		pp->deconled___cmn[61]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_79.reg_2nd_diff_y_th1);
		pp->deconled___cmn[62]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_79.reg_2nd_diff_y_th0);
		/* face obj*/
		pp->deconled__face[0] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_50.reg_lut_skin_yy_x0);
		pp->deconled__face[1] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_50.reg_lut_skin_yy_x1);
		pp->deconled__face[2] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_50.reg_lut_skin_yy_x2);
		pp->deconled__face[3] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_50.reg_lut_skin_yy_x3);
		pp->deconled__face[4] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_51.reg_lut_skin_cb_x0);
		pp->deconled__face[5] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_51.reg_lut_skin_cb_x1);
		pp->deconled__face[6] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_51.reg_lut_skin_cb_x2);
		pp->deconled__face[7] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_51.reg_lut_skin_cb_x3);
		pp->deconled__face[8] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_52.reg_lut_skin_cr_x0);
		pp->deconled__face[9] =PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_52.reg_lut_skin_cr_x1);
		pp->deconled__face[10]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_52.reg_lut_skin_cr_x2);
		pp->deconled__face[11]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_52.reg_lut_skin_cr_x3);
		pp->deconled__face[12]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_53.reg_lut_skin_y0);
		pp->deconled__face[13]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_53.reg_lut_skin_y1);
		pp->deconled__face[14]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_53.reg_lut_skin_y2);
		pp->deconled__face[15]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_53.reg_lut_skin_y3);
		pp->deconled__face[16]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_54.reg_lut_face_x0);
		pp->deconled__face[17]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_54.reg_lut_face_x1);
		pp->deconled__face[18]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_54.reg_lut_face_x2);
		pp->deconled__face[19]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_54.reg_lut_face_x3);
		pp->deconled__face[20]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_55.reg_lut_face_y0);
		pp->deconled__face[21]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_55.reg_lut_face_y1);
		pp->deconled__face[22]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_55.reg_lut_face_y2);
		pp->deconled__face[23]=PE_CHPI_TBL0_F20_Rd(led.reg_decon_ctrl_55.reg_lut_face_y3);
		/* download dct sqm db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntSqmCmnUserDb */
		/* PE_CHPI_DNR_DCNT_SQM_F20_T			 sqm4;//15 */
		PE_CHPI_TBL0_F20_QRd(sqm4.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QRd(sqm4.data32[i],pp->deconnd__sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm4.cnt32);

		/* download dct user db */
		/* see PE_NRD_HW_O20_DownloadDnrDcntUserDb */
		/* PE_CHPI_DNR_DCNT_USER_F20_T			 usr2;//19 */
		PE_CHPI_TBL0_F20_QRd(usr2.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QRd(usr2.data32[i],pp->deconnd___buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr2.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_F20_QRd(usr2.cnt32,i);

		/* download dct led sqm db */
		/* see PE_NRD_HW_O20_DownloadLedDcntSqmCmnUserDb */
		/* PE_CHPI_LED_DCNT_SQM_F20_T			 sqm5;//16 */
		PE_CHPI_TBL0_F20_QRd(sqm5.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_F20_QRd(sqm5.data32[i],pp->deconled_sqmui[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(sqm5.cnt32);

		/* download dct led user db */
		/* see PE_NRD_HW_O20_DownloadLedDcntUserDb */
		/* PE_CHPI_LED_DCNT_USER_F20_T			 usr3;//20 */
		PE_CHPI_TBL0_F20_QRd(usr3.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_F20_QRd(usr3.data32[i],pp->deconled__buff[i]);
		}
		i = PE_CHPI_TBL0_F20_Rd(usr3.cnt32);

		pd32 = pp->deconnd_____ui;
		printk("set[%d] : deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = pp->deconnd___buff;
		printk("set[%d] : deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);

		pd = pp->deconnd____cmn;
		printk("set[%d] : deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
		pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
		pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
		pd[60], pd[61], pd[62]);
		pd8 = pp->deconnd___face;
		printk("set[%d] : deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
		pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
		pd8[20], pd8[21], pd8[22], pd8[23]);
		pd32 = pp->deconnd__sqmui;
		printk("[%d]deconnd__sqmui:%d, cnt:%d\n", pp->win_id, pp->deconnd_ui_val, i);
		printk( "\n"\
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);

		pd32 = pp->deconled____ui;
		printk("set[%d] : deconled____ui\n"
		"deconled____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = pp->deconled__buff;
		printk("set[%d] : deconled__buff\n"
		"deconled__buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd = pp->deconled___cmn;
		printk("set[%d] : deconled___cmn\n"
		"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
		pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
		pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
		pd[60], pd[61], pd[62]);
		pd8 = pp->deconled__face;
		printk("set[%d] : deconled__face\n"
		"deconled__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
		pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
		pd8[20], pd8[21], pd8[22], pd8[23]);
		pd32 = pp->deconled_sqmui;
		printk("[%d]deconled_sqmui:%d, cnt:%d\n", pp->win_id, pp->deconnd_ui_val, i);
		printk( \
		"deconled_sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconled_sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconled_sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);

	}while(0);
	return ret;
}



int PE_CHPI_DNR_HW_F20_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	UINT32 enable;
	PE_DNR_HW_PARAM_DATA_F20_T *p_dnr = &_g_pe_dnr_hw_param_data_f20;
	do{
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		enable = (*onoff >0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_F20_Wr(dnr.reg_decon_ctrl_56.reg_face_en,enable);
		PE_CHPI_TBL0_F20_WrFL(dnr.reg_decon_ctrl_56.udata32);
		PE_CHPI_TBL0_F20_Wr(dnr.dc_bnr_ctrl_0.reg_obj_gain_en,enable);
		PE_CHPI_TBL0_F20_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		/* count */
		PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_DNR);
		/* set user */
		PE_CHPI_DNR_HW_F20_USER(p_dnr,reg_decon_ctrl_56.reg_face_en,enable);
		PE_CHPI_DNR_HW_F20_USER(p_dnr,dc_bnr_ctrl_0.reg_obj_gain_en,enable);
	}while(0);
	return ret;
}

