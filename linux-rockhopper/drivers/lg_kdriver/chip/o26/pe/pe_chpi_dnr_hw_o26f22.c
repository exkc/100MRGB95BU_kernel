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

/** @file pe_chpi_dnr_hw_o26.c
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
#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_fwi_o26.h"
#include "pe_inf_o26.h"
#include "pe_dnr_hw_param_o26.h"
#include "pe_dnr_psp_hw_param_o26.h"
#include "pe_chpi_dnr_hw_o26f22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_DNR_HW_O26F22_ENABLE

#define PE_CHPI_DNR_HW_O26F22_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_DNR_HW_O26F22_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_O26F22_T;

#endif

typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T *data;
	} reg_data;
} PE_DNR_OSD_HW_PARAM_DATA_O26F22_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
//#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
extern const PE_REG_PARAM_T dnr_l_hd_i_default_o26[];
extern const PE_REG_PARAM_T dnr_l_hd_p_default_o26[];
extern const PE_REG_PARAM_T dnr_l_sd_default_o26[];
extern const PE_REG_PARAM_T dnr_l_ud_default_o26[];
extern const UINT32 sqm_dnr_init_o26[];
extern const UINT32 sqm_dct_init_o26[];
extern const PE_REG_PARAM_T dnr_l_hd_i_default_o26f22[];
extern const PE_REG_PARAM_T dnr_l_hd_p_default_o26f22[];
extern const PE_REG_PARAM_T dnr_l_sd_default_o26f22[];
extern const PE_REG_PARAM_T dnr_l_ud_default_o26f22[];
extern const PE_REG_PARAM_T dnr_l_8k_default_o26f22[];
extern const PE_REG_PARAM_T dnrpsp_l_hd_default_o26f22[];
extern const PE_REG_PARAM_T dnrpsp_l_sd_default_o26f22[];
extern const PE_REG_PARAM_T dnrpsp_l_ud_default_o26f22[];
//#endif

extern const PE_REG_PARAM_T osd_dec_default_o26f22[];


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
#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
static PE_DNR_HW_PARAM_DATA_O26F22_T _g_pe_dnr_hw_param_data_o26f22 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif
static PE_DNR_OSD_HW_PARAM_DATA_O26F22_T _g_pe_dnr_osd_hw_param_data_o26f22 = {{NULL}, {NULL}, {NULL}, {NULL}};

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
static int PE_CHPI_DNR_HW_O26F22_CreateDnrDataTable(void)
{
	int ret = RET_OK;
	PE_DNR_HW_PARAM_DATA_O26F22_T *p_dnr = &_g_pe_dnr_hw_param_data_o26f22;

	/* create dflt table */
	if (p_dnr->reg_dflt.addr == NULL)
	{
		p_dnr->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
	}
	/* create user table */
	if (p_dnr->reg_user.addr == NULL)
	{
		p_dnr->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
		memset((p_dnr->reg_user.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O26_T));	// 0x0
	}
	/* create mask table */
	if (p_dnr->reg_mask.addr == NULL)
	{
		p_dnr->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
		memset((p_dnr->reg_mask.addr), -1, sizeof(PE_DNR_HW_PARAM_REG_O26_T));// 0xffffffff
	}
	/* create data table */
	if (p_dnr->reg_data.addr == NULL)
	{
		p_dnr->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
		memset((p_dnr->reg_data.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O26_T));	// 0x0
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

	return ret;
}
#endif
static int PE_CHPI_DNR_HW_O26F22_CreateOsdDataTable(void)
{
	int ret = RET_OK;
	PE_DNR_OSD_HW_PARAM_DATA_O26F22_T *p_dnr_osd = &_g_pe_dnr_osd_hw_param_data_o26f22;

	/* create dflt table */
	if (p_dnr_osd->reg_dflt.addr == NULL)
	{
		p_dnr_osd->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));
	}
	/* create user table */
	if (p_dnr_osd->reg_user.addr == NULL)
	{
		p_dnr_osd->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));
		memset((p_dnr_osd->reg_user.addr), 0, sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));	// 0x0
	}
	/* create mask table */
	if (p_dnr_osd->reg_mask.addr == NULL)
	{
		p_dnr_osd->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));
		memset((p_dnr_osd->reg_mask.addr), -1, sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));// 0xffffffff
	}
	/* create data table */
	if (p_dnr_osd->reg_data.addr == NULL)
	{
		p_dnr_osd->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));
		memset((p_dnr_osd->reg_data.addr), 0, sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T));	// 0x0
	}
	/* report srsult */
	if (p_dnr_osd->reg_dflt.addr != NULL && p_dnr_osd->reg_user.addr != NULL && \
		p_dnr_osd->reg_mask.addr != NULL && p_dnr_osd->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_dnr_osd]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_dnr_osd]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_dnr_osd->reg_dflt.addr == NULL)? "x":"o", \
			(p_dnr_osd->reg_user.addr == NULL)? "x":"o", \
			(p_dnr_osd->reg_mask.addr == NULL)? "x":"o", \
			(p_dnr_osd->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	return ret;
}

__attribute__((unused)) static int PE_CHPI_DNR_HW_O26F22_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	ret = PE_CHPI_DNR_HW_O26F22_CreateDnrDataTable();
	#endif
	ret = PE_CHPI_DNR_HW_O26F22_CreateOsdDataTable();
	return ret;
}

static PE_CHPI_DNR_HW_O26F22_DNR_FMT PE_CHPI_DNR_HW_O26F22_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_DNR_HW_O26F22_DNR_FMT dnr_fmt = PE_CHPI_DNR_O26F22_DNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				dnr_fmt = PE_CHPI_DNR_O26F22_DNR_SD;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				dnr_fmt = PE_CHPI_DNR_O26F22_DNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					dnr_fmt = PE_CHPI_DNR_O26F22_DNR_HD_I;
				else
					dnr_fmt = PE_CHPI_DNR_O26F22_DNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				dnr_fmt = PE_CHPI_DNR_O26F22_DNR_UD;
			}
			else
			{
				dnr_fmt = PE_CHPI_DNR_O26F22_DNR_UD_8K;
			}
			break;
	}
	return dnr_fmt;
}

static PE_CHPI_DNR_HW_O26F22_OSD_FMT PE_CHPI_DNR_HW_O26F22_ConvDispInfoToOsdFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_DNR_HW_O26F22_OSD_FMT osd_fmt = PE_CHPI_DNR_O26F22_OSD_NUM;
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
				osd_fmt = PE_CHPI_DNR_O26F22_OSD_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				osd_fmt = PE_CHPI_DNR_O26F22_OSD_HD;
			}
			else
			{
				osd_fmt = PE_CHPI_DNR_O26F22_OSD_UD;
			}
			break;
	}
	return osd_fmt;
}

static int PE_CHPI_DNR_HW_O26F22_SetDnrDefault(PE_CHPI_DNR_HW_O26F22_DNR_FMT cur0_dnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_dnr_hw_param_data_o26f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_dnr_hw_param_data_o26f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_dnr_hw_param_data_o26f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_dnr_hw_param_data_o26f22.reg_data.addr;

	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_dnr_fmt)
	{
		case PE_CHPI_DNR_O26F22_DNR_SD:
			p_dflt_param = dnr_l_sd_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_DNR_HD_I:
			p_dflt_param = dnr_l_hd_i_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_DNR_HD_P:
			p_dflt_param = dnr_l_hd_p_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_DNR_UD:
			p_dflt_param = dnr_l_ud_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_DNR_UD_8K:
			p_dflt_param = dnr_l_8k_default_o26f22;
			break;
		default:
			p_dflt_param = dnr_l_ud_default_o26f22;
			break;
	}

	size = sizeof(PE_DNR_HW_PARAM_REG_O26_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		PE_CHPI_TBL0_O26F22_QWr(dnr.dnr_max_ctrl.udata32,		p_data[0]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_0.udata32, 		p_data[1]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_1.udata32, 		p_data[2]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_2.udata32, 		p_data[3]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_3.udata32, 		p_data[4]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_4.udata32, 		p_data[5]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_5.udata32, 		p_data[6]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.detail_ctrl.udata32,		p_data[7]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_0.udata32,		p_data[8]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_1.udata32,		p_data[9]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_2.udata32,		p_data[10]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_3.udata32,		p_data[11]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_4.udata32,		p_data[12]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_5.udata32,		p_data[13]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_0.udata32,		p_data[14]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_1.udata32,		p_data[15]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_2.udata32,		p_data[16]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_3.udata32,		p_data[17]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_4.udata32,		p_data[18]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_5.udata32,		p_data[19]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_6.udata32,		p_data[20]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_7.udata32,		p_data[21]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_8.udata32,		p_data[22]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_9.udata32,		p_data[23]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_10.udata32, 	p_data[24]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_11.udata32, 	p_data[25]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_12.udata32, 	p_data[26]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_0.udata32, 	p_data[27]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_1.udata32, 	p_data[28]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_2.udata32, 	p_data[29]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_3.udata32, 	p_data[30]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_4.udata32, 	p_data[31]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_2.udata32,		p_data[32]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_3.udata32,		p_data[33]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_4.udata32,		p_data[34]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_5.udata32,		p_data[35]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_5.udata32, 	p_data[36]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.c_pre_blur_ctrl_0.udata32,	p_data[37]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_6.udata32, 	p_data[38]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_7.udata32, 	p_data[39]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_8.udata32, 	p_data[40]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_9.udata32, 	p_data[41]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_13.udata32, 	p_data[42]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_14.udata32, 	p_data[43]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_6.udata32,		p_data[44]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_7.udata32,		p_data[45]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_0.udata32, 		p_data[46]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_1.udata32, 		p_data[47]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_2.udata32, 		p_data[48]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_3.udata32, 		p_data[49]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_4.udata32, 		p_data[50]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_15.udata32,			p_data[51]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_16.udata32,			p_data[52]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_0.udata32,	p_data[53]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_1.udata32,	p_data[54]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_2.udata32,	p_data[55]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_3.udata32,	p_data[56]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_4.udata32,	p_data[57]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_5.udata32,	p_data[58]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_6.udata32,	p_data[59]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_7.udata32,	p_data[60]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_8.udata32,	p_data[61]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_9.udata32,	p_data[62]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_10.udata32,	p_data[63]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_8.udata32,	p_data[64]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_9.udata32,	p_data[65]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_10.udata32, p_data[66]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_11.udata32, p_data[67]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_6.udata32, 	p_data[68]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_7.udata32, 	p_data[69]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_8.udata32, 	p_data[70]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_9.udata32, 	p_data[71]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_10.udata32,	p_data[72]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_11.udata32,	p_data[73]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_12.udata32,	p_data[74]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_11.udata32,	p_data[75]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_12.udata32,	p_data[76]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_13.udata32,	p_data[77]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_14.udata32,	p_data[78]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_15.udata32,	p_data[79]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_16.udata32,	p_data[80]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_17.udata32,	p_data[81]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_18.udata32,	p_data[82]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_19.udata32,	p_data[83]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_20.udata32,	p_data[84]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_21.udata32,	p_data[85]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_22.udata32,	p_data[86]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_23.udata32,	p_data[87]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_24.udata32,	p_data[88]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_25.udata32,	p_data[89]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_26.udata32,	p_data[90]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_27.udata32,	p_data[91]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_28.udata32,	p_data[92]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_29.udata32,	p_data[93]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_30.udata32,	p_data[94]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_31.udata32,	p_data[95]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_32.udata32,	p_data[96]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_33.udata32,	p_data[97]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_34.udata32,	p_data[98]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_35.udata32,	p_data[99]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_36.udata32,	p_data[100]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_37.udata32,	p_data[101]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_38.udata32,	p_data[102]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_39.udata32,	p_data[103]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_40.udata32,	p_data[104]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_41.udata32,	p_data[105]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_42.udata32,	p_data[106]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_43.udata32,	p_data[107]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_44.udata32,	p_data[108]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_45.udata32,	p_data[109]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_46.udata32,	p_data[110]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_47.udata32,	p_data[111]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_48.udata32,	p_data[112]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_49.udata32,	p_data[113]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_50.udata32,	p_data[114]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_51.udata32,	p_data[115]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_52.udata32,	p_data[116]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_53.udata32,	p_data[117]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_54.udata32,	p_data[118]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_55.udata32,	p_data[119]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_56.udata32,	p_data[120]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_57.udata32,	p_data[121]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_58.udata32,	p_data[122]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_59.udata32,	p_data[123]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_60.udata32,	p_data[124]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_61.udata32,	p_data[125]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_62.udata32,	p_data[126]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_63.udata32,	p_data[127]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_12.udata32, p_data[128]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_13.udata32, p_data[129]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_14.udata32, p_data[130]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_15.udata32, p_data[131]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_64.udata32,	p_data[132]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_65.udata32,	p_data[133]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_66.udata32,	p_data[134]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_67.udata32,	p_data[135]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_68.udata32,	p_data[136]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_69.udata32,	p_data[137]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_70.udata32,	p_data[138]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_71.udata32,	p_data[139]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_72.udata32,	p_data[140]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_73.udata32,	p_data[141]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_74.udata32,	p_data[142]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_75.udata32,	p_data[143]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_76.udata32,	p_data[144]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_77.udata32,	p_data[145]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_78.udata32,	p_data[146]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_79.udata32,	p_data[147]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_80.udata32,	p_data[148]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_81.udata32,	p_data[149]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_82.udata32,	p_data[150]);
		//PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_83.udata32,p_data[151]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_84.udata32,	p_data[152]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_85.udata32,	p_data[153]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_86.udata32,	p_data[154]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_87.udata32,	p_data[155]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_88.udata32,	p_data[156]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_89.udata32,	p_data[157]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_90.udata32,	p_data[158]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_91.udata32,	p_data[159]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_92.udata32,	p_data[160]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_93.udata32,	p_data[161]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_94.udata32,	p_data[162]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_95.udata32,	p_data[163]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_96.udata32,	p_data[164]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_97.udata32,	p_data[165]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_98.udata32,	p_data[166]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_99.udata32,	p_data[167]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_100.udata32, p_data[168]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_101.udata32, p_data[169]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_102.udata32, p_data[170]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_103.udata32, p_data[171]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_104.udata32, p_data[172]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_105.udata32, p_data[173]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_106.udata32, p_data[174]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_107.udata32, p_data[175]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_108.udata32, p_data[176]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_109.udata32, p_data[177]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_110.udata32, p_data[178]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_111.udata32, p_data[179]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_13.udata32,		p_data[180]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_14.udata32,		p_data[181]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_15.udata32,		p_data[182]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_16.udata32,		p_data[183]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_17.udata32,		p_data[184]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_112.udata32, p_data[185]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_113.udata32, p_data[186]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_114.udata32, p_data[187]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_115.udata32, p_data[188]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_116.udata32, p_data[189]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_117.udata32, p_data[190]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_118.udata32, p_data[191]);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_119.udata32, p_data[192]);
		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_DNR);
	}while(0);
	#endif
	return ret;
}

static int PE_CHPI_DNR_HW_O26F22_SetOsdDefault(PE_CHPI_DNR_HW_O26F22_OSD_FMT cur0_osd_fmt)
{
	int ret = RET_OK;
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_dnr_osd_hw_param_data_o26f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_dnr_osd_hw_param_data_o26f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_dnr_osd_hw_param_data_o26f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_dnr_osd_hw_param_data_o26f22.reg_data.addr;

	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_DNR_HW_O26F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_osd_fmt)
	{
		case PE_CHPI_DNR_O26F22_OSD_SD:
			p_dflt_param = osd_dec_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_OSD_HD:
			p_dflt_param = osd_dec_default_o26f22;
			break;
		case PE_CHPI_DNR_O26F22_OSD_UD:
		default:
			p_dflt_param = osd_dec_default_o26f22;
			break;
	}

	size = sizeof(PE_DNR_OSD_HW_PARAM_REG_O26F22_PARAM_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_0.udata32,  p_data[0]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_1.udata32,  p_data[1]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_2.udata32,  p_data[2]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_3.udata32,  p_data[3]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_4.udata32,  p_data[4]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_5.udata32,  p_data[5]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_6.udata32,  p_data[6]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_7.udata32,  p_data[7]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_8.udata32,  p_data[8]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_9.udata32,  p_data[9]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_10.udata32, p_data[10]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_11.udata32, p_data[11]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_12.udata32, p_data[12]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_13.udata32, p_data[13]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_14.udata32, p_data[14]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_15.udata32, p_data[15]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_16.udata32, p_data[16]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_17.udata32, p_data[17]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_18.udata32, p_data[18]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_19.udata32, p_data[19]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_20.udata32, p_data[20]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_21.udata32, p_data[21]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_22.udata32, p_data[22]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_23.udata32, p_data[23]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_24.udata32, p_data[24]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_25.udata32, p_data[25]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_26.udata32, p_data[26]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_27.udata32, p_data[27]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_28.udata32, p_data[28]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_29.udata32, p_data[29]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_30.udata32, p_data[30]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_31.udata32, p_data[31]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_32.udata32, p_data[32]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_33.udata32, p_data[33]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_34.udata32, p_data[34]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_35.udata32, p_data[35]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_36.udata32, p_data[36]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_37.udata32, p_data[37]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_38.udata32, p_data[38]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_39.udata32, p_data[39]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_40.udata32, p_data[40]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_41.udata32, p_data[41]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_42.udata32, p_data[42]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_43.udata32, p_data[43]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_44.udata32, p_data[44]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_45.udata32, p_data[45]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_46.udata32, p_data[46]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_47.udata32, p_data[47]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_48.udata32, p_data[48]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_49.udata32, p_data[49]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_50.udata32, p_data[50]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_51.udata32, p_data[51]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_52.udata32, p_data[52]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_53.udata32, p_data[53]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_54.udata32, p_data[54]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_55.udata32, p_data[55]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_56.udata32, p_data[56]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_57.udata32, p_data[57]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_58.udata32, p_data[58]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_59.udata32, p_data[59]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_60.udata32, p_data[60]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_61.udata32, p_data[61]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_62.udata32, p_data[62]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_63.udata32, p_data[63]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_64.udata32, p_data[64]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_65.udata32, p_data[65]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_66.udata32, p_data[66]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_67.udata32, p_data[67]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_68.udata32, p_data[68]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_69.udata32, p_data[69]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_70.udata32, p_data[70]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_71.udata32, p_data[71]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_72.udata32, p_data[72]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_73.udata32, p_data[73]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_74.udata32, p_data[74]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_75.udata32, p_data[75]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_76.udata32, p_data[76]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_77.udata32, p_data[77]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_78.udata32, p_data[78]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_79.udata32, p_data[79]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_80.udata32, p_data[80]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_81.udata32, p_data[81]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_82.udata32, p_data[82]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_83.udata32, p_data[83]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_84.udata32, p_data[84]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_85.udata32, p_data[85]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_86.udata32, p_data[86]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_87.udata32, p_data[87]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_88.udata32, p_data[88]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_89.udata32, p_data[89]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_90.udata32, p_data[90]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_91.udata32, p_data[91]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_92.udata32, p_data[92]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_93.udata32, p_data[93]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_94.udata32, p_data[94]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_95.udata32, p_data[95]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_96.udata32, p_data[96]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_97.udata32, p_data[97]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_98.udata32, p_data[98]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_99.udata32, p_data[99]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_100.udata32,p_data[100]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_101.udata32,p_data[101]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_102.udata32,p_data[102]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_103.udata32,p_data[103]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_104.udata32,p_data[104]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_105.udata32,p_data[105]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_106.udata32,p_data[106]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_107.udata32,p_data[107]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_108.udata32,p_data[108]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_109.udata32,p_data[109]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_110.udata32,p_data[110]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_111.udata32,p_data[111]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_112.udata32,p_data[112]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_113.udata32,p_data[113]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_114.udata32,p_data[114]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_115.udata32,p_data[115]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_116.udata32,p_data[116]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_117.udata32,p_data[117]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_118.udata32,p_data[118]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_119.udata32,p_data[119]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_120.udata32,p_data[120]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_121.udata32,p_data[121]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_122.udata32,p_data[122]);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_123.udata32,p_data[123]);
	}while(0);
 	/* count */
	PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_OSD);

	return ret;
}

int PE_CHPI_DNR_HW_O26F22_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_O26_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_DNR_HW_O26F22_DNR_FMT pre0_dnr_fmt = PE_CHPI_DNR_O26F22_DNR_NUM;
	PE_CHPI_DNR_HW_O26F22_DNR_FMT cur0_dnr_fmt;
	static PE_CHPI_DNR_HW_O26F22_OSD_FMT pre0_osd_fmt = PE_CHPI_DNR_O26F22_OSD_NUM;
	PE_CHPI_DNR_HW_O26F22_OSD_FMT cur0_osd_fmt;
	do{
		ret = PE_INF_O26_GetCurInfSettings(&inf_set);
		PE_CHPI_DNR_HW_O26F22_CHECK_CODE(ret,break,"PE_INF_O26_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_dnr_fmt = PE_CHPI_DNR_HW_O26F22_ConvDispInfoToDnrFmt(disp0_inf);
		if(pre0_dnr_fmt!=cur0_dnr_fmt)
		{
			ret = PE_CHPI_DNR_HW_O26F22_SetDnrDefault(cur0_dnr_fmt);
			PE_CHPI_DNR_HW_O26F22_CHECK_CODE(ret,break,"PE_CHPI_DNR_HW_O26F22_SetDnrDefault() error\n");
			pre0_dnr_fmt=cur0_dnr_fmt;
		}
		cur0_osd_fmt = PE_CHPI_DNR_HW_O26F22_ConvDispInfoToOsdFmt(disp0_inf);
		if(pre0_osd_fmt!=cur0_osd_fmt)
		{
			ret = PE_CHPI_DNR_HW_O26F22_SetOsdDefault(cur0_osd_fmt);
			PE_CHPI_DNR_HW_O26F22_CHECK_CODE(ret,break,"PE_CHPI_DNR_HW_O26F22_SetOsdDefault() error\n");
			pre0_osd_fmt=cur0_osd_fmt;
		}
	}while(0);
	return ret;
}

#if (CONFIG_LX_O26_CHIP_FIRMWARE == 1)
int PE_CHPI_DNR_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_DNR_HW_O26F22_CreateDataTable();
		if (ret)	break;
		if (pstParams->resume_mode == 1)	break;//if qsm,skip
 		if (!gPE_CHPI_DDR_O26)	break;

		/* addr */
		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		PE_CHPI_TBL0_O26F22_QWr(dnr.dnr_max_ctrl.uaddr32,		0xF2000594);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_0.uaddr32, 		0xF20005A0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_1.uaddr32, 		0xF20005A4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_2.uaddr32, 		0xF20005A8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_3.uaddr32, 		0xF20005AC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_4.uaddr32, 		0xF20005B0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_5.uaddr32, 		0xF20005B4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.detail_ctrl.uaddr32,		0xF20005B8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_0.uaddr32,	0xF20005BC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_1.uaddr32,	0xF20005C0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_2.uaddr32,	0xF20005C4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_3.uaddr32,	0xF20005C8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_4.uaddr32,	0xF20005CC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_5.uaddr32,	0xF20005D0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_0.uaddr32,	0xF20005D4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_1.uaddr32,	0xF20005D8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_2.uaddr32,	0xF20005DC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_3.uaddr32,	0xF20005E4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_4.uaddr32,	0xF20005E8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_5.uaddr32,	0xF20005F0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_6.uaddr32,	0xF20005F4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_7.uaddr32,	0xF20005F8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_8.uaddr32,	0xF2000600);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_9.uaddr32,	0xF2000604);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_10.uaddr32, 0xF2000608);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_11.uaddr32, 0xF200060C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_12.uaddr32, 0xF2000610);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_0.uaddr32, 0xF2000638);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_1.uaddr32, 0xF200063C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_2.uaddr32, 0xF2000640);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_3.uaddr32, 0xF200066C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_4.uaddr32, 0xF2000670);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_2.uaddr32,	0xF2000674);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_3.uaddr32,	0xF2000678);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_4.uaddr32,	0xF200067C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sc_bnr_ctrl_5.uaddr32,	0xF2000680);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_5.uaddr32, 0xF2000684);
		PE_CHPI_TBL0_O26F22_QWr(dnr.c_pre_blur_ctrl_0.uaddr32,0xF2000688);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_6.uaddr32, 	0xF200068C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_7.uaddr32,   0xF2000690);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_8.uaddr32, 	0xF2000694);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ellipse_ctrl_9.uaddr32, 	0xF2000698);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_13.uaddr32, 	0xF200069C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_ctrl_14.uaddr32, 	0xF20006A0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_6.uaddr32,		0xF20006A4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.dc_bnr_ctrl_7.uaddr32,		0xF20006A8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_0.uaddr32, 		  0xF20006AC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_1.uaddr32, 		  0xF20006B0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_2.uaddr32, 		  0xF20006B4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_3.uaddr32, 		  0xF20006B8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.sqm_ctrl_4.uaddr32, 		  0xF20006BC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_15.uaddr32,				0xF2000730);
		PE_CHPI_TBL0_O26F22_QWr(dnr.ac_bnr_16.uaddr32,				0xF2000734);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_0.uaddr32,	0xF2000764);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_1.uaddr32,	0xF2000768);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_2.uaddr32,	0xF200076C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_3.uaddr32,	0xF2000770);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_4.uaddr32,	0xF2000774);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_5.uaddr32,	0xF2000778);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_6.uaddr32,	0xF200077C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_7.uaddr32,	0xF2000780);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_8.uaddr32,	0xF2000784);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_9.uaddr32,	0xF2000788);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_10.uaddr32,0xF200078C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_8.uaddr32,0xF2000790);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_9.uaddr32,0xF2000794);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_10.uaddr32, 0xF2000798);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_11.uaddr32, 0xF200079C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_6.uaddr32, 	  0xF20007A8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_7.uaddr32, 	  0xF20007AC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_8.uaddr32, 	  0xF20007B0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_9.uaddr32, 	  0xF20007B4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_10.uaddr32,		0xF20007B8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_11.uaddr32,		0xF20007BC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_mnr_ctrl_12.uaddr32,		0xF20007C0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_11.uaddr32,	0xF20007C4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_12.uaddr32,	0xF20007C8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_13.uaddr32,	0xF20007CC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_14.uaddr32,	0xF20007D0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_15.uaddr32,	0xF20007D4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_16.uaddr32,	0xF20007D8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_17.uaddr32,	0xF20007DC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_18.uaddr32,	0xF20007E0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_19.uaddr32,	0xF20007E4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_20.uaddr32,	0xF20007E8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_21.uaddr32,	0xF20007EC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_22.uaddr32,	0xF20007F0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_23.uaddr32,	0xF20007F4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_24.uaddr32,	0xF20007F8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_25.uaddr32,	0xF20007FC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_26.uaddr32,	0xF2000800);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_27.uaddr32,	0xF2000804);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_28.uaddr32,	0xF2000808);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_29.uaddr32,	0xF200080C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_30.uaddr32,	0xF2000810);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_31.uaddr32,	0xF2000814);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_32.uaddr32,	0xF2000818);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_33.uaddr32,	0xF200081C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_34.uaddr32,	0xF2000820);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_35.uaddr32,	0xF2000824);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_36.uaddr32,	0xF2000828);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_37.uaddr32,	0xF200082C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_38.uaddr32,	0xF2000830);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_39.uaddr32,	0xF2000834);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_40.uaddr32,	0xF2000838);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_41.uaddr32,	0xF200083C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_42.uaddr32,	0xF2000840);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_43.uaddr32,	0xF2000844);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_44.uaddr32,	0xF2000848);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_45.uaddr32,	0xF200084C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_46.uaddr32,	0xF2000850);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_47.uaddr32,	0xF2000854);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_48.uaddr32,	0xF2000858);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_49.uaddr32,	0xF200085C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_50.uaddr32,	0xF2000860);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_51.uaddr32,	0xF2000864);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_52.uaddr32,	0xF2000868);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_53.uaddr32,	0xF200086C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_54.uaddr32,	0xF2000870);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_55.uaddr32,	0xF2000874);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_56.uaddr32,	0xF2000878);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_57.uaddr32,	0xF200087C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_58.uaddr32,	0xF2000880);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_59.uaddr32,	0xF2000884);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_60.uaddr32,	0xF2000888);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_61.uaddr32,	0xF200088C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_62.uaddr32,	0xF2000890);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_63.uaddr32,	0xF2000894);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_12.uaddr32, 0xF2000898);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_13.uaddr32, 0xF200089C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_14.uaddr32, 0xF20008A0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_dc_bnr_ctrl_15.uaddr32, 0xF20008A4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_64.uaddr32,	0xF20008A8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_65.uaddr32,	0xF20008AC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_66.uaddr32,	0xF20008B0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_67.uaddr32,	0xF20008B4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_68.uaddr32,	0xF20008B8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_69.uaddr32,	0xF20008BC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_70.uaddr32,	0xF20008C0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_71.uaddr32,	0xF20008C4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_72.uaddr32,	0xF20008C8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_73.uaddr32,	0xF20008CC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_74.uaddr32,	0xF20008D0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_75.uaddr32,	0xF20008D4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_76.uaddr32,	0xF20008D8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_77.uaddr32,	0xF20008DC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_78.uaddr32,	0xF20008E0);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_79.uaddr32,	0xF20008E4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_80.uaddr32,	0xF20008E8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_81.uaddr32,	0xF20008EC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_82.uaddr32,	0xF20008F0);
		//PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_83.uaddr32,	0xF20008F4);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_84.uaddr32,	0xF20008F8);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_85.uaddr32,	0xF20008FC);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_86.uaddr32,	0xF2000900);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_87.uaddr32,	0xF2000904);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_88.uaddr32,	0xF2000908);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_89.uaddr32,	0xF200090C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_90.uaddr32,	0xF2000910);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_91.uaddr32,	0xF2000914);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_92.uaddr32,	0xF2000918);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_93.uaddr32,	0xF200091C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_94.uaddr32,	0xF2000920);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_95.uaddr32,	0xF2000924);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_96.uaddr32,	0xF2000928);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_97.uaddr32,	0xF200092C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_98.uaddr32,	0xF2000930);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_99.uaddr32,	0xF2000934);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_100.uaddr32, 0xF2000938);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_101.uaddr32, 0xF200093C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_102.uaddr32, 0xF2000940);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_103.uaddr32, 0xF2000944);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_104.uaddr32, 0xF2000948);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_105.uaddr32, 0xF200094C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_106.uaddr32, 0xF2000950);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_107.uaddr32, 0xF2000954);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_108.uaddr32, 0xF2000958);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_109.uaddr32, 0xF200095C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_110.uaddr32, 0xF2000960);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_111.uaddr32, 0xF2000964);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_13.uaddr32,		  0xF2000968);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_14.uaddr32,		  0xF200096C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_15.uaddr32,		  0xF2000970);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_16.uaddr32,		  0xF2000974);
		PE_CHPI_TBL0_O26F22_QWr(dnr.mnr_ctrl_17.uaddr32,		  0xF2000978);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_112.uaddr32, 0xF200097C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_113.uaddr32, 0xF2000980);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_114.uaddr32, 0xF2000984);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_115.uaddr32, 0xF2000988);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_116.uaddr32, 0xF200098C);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_117.uaddr32, 0xF2000990);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_118.uaddr32, 0xF2000994);
		PE_CHPI_TBL0_O26F22_QWr(dnr.reg_decon_ctrl_119.uaddr32, 0xF2000998);

		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_0.uaddr32,0xF3012380);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_1.uaddr32,0xF3012384);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_2.uaddr32,0xF3012388);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_3.uaddr32,0xF301238C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_4.uaddr32,0xF3012390);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_5.uaddr32,0xF3012394);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_6.uaddr32,0xF3012398);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_7.uaddr32,0xF301239C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_8.uaddr32,0xF30123A0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_9.uaddr32,0xF30123A4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_10.uaddr32,0xF30123A8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_11.uaddr32,0xF30123AC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_12.uaddr32,0xF30123B0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_13.uaddr32,0xF30123B4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_14.uaddr32,0xF30123B8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_15.uaddr32,0xF30123BC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_16.uaddr32,0xF30123C0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_17.uaddr32,0xF30123C4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_18.uaddr32,0xF30123C8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_19.uaddr32,0xF30123CC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_20.uaddr32,0xF30123D0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_21.uaddr32,0xF30123D4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_22.uaddr32,0xF30123D8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_23.uaddr32,0xF30123DC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_24.uaddr32,0xF30123E0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_25.uaddr32,0xF30123E4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_26.uaddr32,0xF30123E8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_27.uaddr32,0xF30123EC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_28.uaddr32,0xF30123F0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_29.uaddr32,0xF30123F4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_30.uaddr32,0xF30123F8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_31.uaddr32,0xF30123FC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_32.uaddr32,0xF3012400);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_33.uaddr32,0xF3012404);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_34.uaddr32,0xF3012408);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_35.uaddr32,0xF301240C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_36.uaddr32,0xF3012410);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_37.uaddr32,0xF3012414);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_38.uaddr32,0xF3012418);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_39.uaddr32,0xF301241C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_40.uaddr32,0xF3012420);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_41.uaddr32,0xF3012424);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_42.uaddr32,0xF3012428);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_43.uaddr32,0xF301242C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_44.uaddr32,0xF3012430);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_45.uaddr32,0xF3012434);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_46.uaddr32,0xF3012438);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_47.uaddr32,0xF301243C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_48.uaddr32,0xF3012440);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_49.uaddr32,0xF3012444);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_50.uaddr32,0xF3012448);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_51.uaddr32,0xF301244C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_52.uaddr32,0xF3012450);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_53.uaddr32,0xF3012454);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_54.uaddr32,0xF3012458);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_55.uaddr32,0xF301245C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_56.uaddr32,0xF3012460);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_57.uaddr32,0xF3012464);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_58.uaddr32,0xF3012468);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_59.uaddr32,0xF301246C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_60.uaddr32,0xF3012470);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_61.uaddr32,0xF3012474);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_62.uaddr32,0xF3012478);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_63.uaddr32,0xF301247C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_64.uaddr32,0xF3012480);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_65.uaddr32,0xF3012484);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_66.uaddr32,0xF3012488);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_67.uaddr32,0xF301248C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_68.uaddr32,0xF3012490);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_69.uaddr32,0xF3012494);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_70.uaddr32,0xF3012498);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_71.uaddr32,0xF301249C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_72.uaddr32,0xF30124A0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_73.uaddr32,0xF30124A4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_74.uaddr32,0xF30124A8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_75.uaddr32,0xF30124AC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_76.uaddr32,0xF30124B0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_77.uaddr32,0xF30124B4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_78.uaddr32,0xF30124B8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_79.uaddr32,0xF30124BC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_80.uaddr32,0xF30124C0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_81.uaddr32,0xF30124C4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_82.uaddr32,0xF30124C8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_83.uaddr32,0xF30124CC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_84.uaddr32,0xF30124D0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_85.uaddr32,0xF30124D4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_86.uaddr32,0xF30124D8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_87.uaddr32,0xF30124DC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_88.uaddr32,0xF30124E0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_89.uaddr32,0xF30124E4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_90.uaddr32,0xF30124E8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_91.uaddr32,0xF30124EC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_92.uaddr32,0xF30124F0);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_93.uaddr32,0xF30124F4);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_94.uaddr32,0xF30124F8);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_95.uaddr32,0xF30124FC);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_96.uaddr32,0xF3012500);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_97.uaddr32,0xF3012504);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_98.uaddr32,0xF3012508);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_99.uaddr32,0xF301250C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_100.uaddr32,0xF3012510);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_101.uaddr32,0xF3012514);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_102.uaddr32,0xF3012518);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_103.uaddr32,0xF301251C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_104.uaddr32,0xF3012520);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_105.uaddr32,0xF3012524);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_106.uaddr32,0xF3012528);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_107.uaddr32,0xF301252C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_108.uaddr32,0xF3012530);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_109.uaddr32,0xF3012534);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_110.uaddr32,0xF3012538);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_111.uaddr32,0xF301253C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_112.uaddr32,0xF3012540);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_113.uaddr32,0xF3012544);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_114.uaddr32,0xF3012548);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_115.uaddr32,0xF301254C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_116.uaddr32,0xF3012550);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_117.uaddr32,0xF3012554);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_118.uaddr32,0xF3012558);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_119.uaddr32,0xF301255C);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_120.uaddr32,0xF3012560);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_121.uaddr32,0xF3012564);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_122.uaddr32,0xF3012568);
		PE_CHPI_TBL0_O26F22_QWr(osd.reg_decon_ctrl_123.uaddr32,0xF301256C);
		#endif

		/* init */
		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		PE_CHPI_DNR_HW_O26F22_SetDnrDefault(PE_CHPI_DNR_O26F22_DNR_HD_P);
		#endif
		PE_CHPI_DNR_HW_O26F22_SetOsdDefault(PE_CHPI_DNR_O26F22_OSD_HD);

		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		/* download dnr sqm db */
		/* see PE_NRD_HW_O26_DownloadDnrSqmCmnInitDb */
		/* PE_CHPI_DNR_SQM_O26F22_T                 sqm3;//14 */
		PE_CHPI_TBL0_O26F22_QWr(sqm3.ui32,0);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm3.data32[i],sqm_dnr_init_o26[i]);
		}
		PE_CHPI_TBL0_O26F22_QWr(sqm3.cnt32,0);

		/* download dnr user db */
		/* see PE_NRD_HW_O26_DownloadDnrInitDb */
		/* PE_CHPI_DNR_USER_O26F22_T                usr1;//18 */
		PE_CHPI_TBL0_O26F22_QWr(usr1.ui32,0);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(usr1.data32[i],0);
		}
		PE_CHPI_TBL0_O26F22_QWr(usr1.cnt32,0);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM3);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_USR1);

		/* download dct sqm db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntSqmCmnInitDb */
		/* PE_CHPI_DNR_DCNT_SQM_O26F22_T            sqm4;//15 */
		PE_CHPI_TBL0_O26F22_QWr(sqm4.ui32,0);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm4.data32[i],sqm_dct_init_o26[i]);
		}
		PE_CHPI_TBL0_O26F22_QWr(sqm4.cnt32,0);

		/* download dct user db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntInitDb */
		/* PE_CHPI_DNR_DCNT_USER_O26F22_T           usr2;//19 */
		PE_CHPI_TBL0_O26F22_QWr(usr2.ui32,0);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(usr2.data32[i],0);
		}
		PE_CHPI_TBL0_O26F22_QWr(usr2.cnt32,0);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM4);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_USR2);
		#endif
		PE_INF_HW_O26_BACKUP_CHPI1("[TBL][DNR]done(resume:%d)",pstParams->resume_mode);
	}while(0);
	return ret;
}
#else
int PE_CHPI_DNR_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams)
{
	 PE_PRINT_NOTI("not supported\n");
	 return RET_ERROR;
}
#endif

int PE_CHPI_DNR_HW_O26F22_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	UINT32 i;
	LX_PE_NRD_DNR_CMN_T *p_param;
	LX_PE_NRD_DNR_ALL_CMN_T *pp;
	PE_DNR_HW_PARAM_DATA_O26F22_T *p_dnr = &_g_pe_dnr_hw_param_data_o26f22;
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		p_param = (LX_PE_NRD_DNR_CMN_T *)pstParams;
		pp = (LX_PE_NRD_DNR_ALL_CMN_T *)p_param->data;

		/* set tbl */
		PE_CHPI_TBL0_O26F22_Wr(dnr.dnr_max_ctrl.reg_dnr_max_enable,GET_BITS(pp->dnr______ui[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_0.reg_mnr_chroma_en,GET_BITS(pp->dnr______ui[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_0.reg_mnr_enable,GET_BITS(pp->dnr______ui[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_dc_bnr_enable,GET_BITS(pp->dnr______ui[3],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_obj_gain_mul,GET_BITS(pp->dnr______ui[4],0,2));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en,GET_BITS(pp->dnr______ui[5],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en,GET_BITS(pp->dnr______ui[6],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_en,GET_BITS(pp->dnr______ui[7],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_en,GET_BITS(pp->dnr______ui[8],0,1));
		//PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_min,GET_BITS(pp->dnr______ui[9],0,8));
		//PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_max,GET_BITS(pp->dnr______ui[10],0,8));
		//PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_min,GET_BITS(pp->dnr______ui[11],0,8));
		//PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_max,GET_BITS(pp->dnr______ui[12],0,8));
		/*dnr_____mnr*/
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_1.reg_mmd_x_min,GET_BITS(pp->dnr_____mnr[0],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_1.reg_mmd_x_max,GET_BITS(pp->dnr_____mnr[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_1.reg_mmd_y_min,GET_BITS(pp->dnr_____mnr[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_1.reg_mmd_y_max,GET_BITS(pp->dnr_____mnr[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_3.reg_mmd_scale,GET_BITS(pp->dnr_____mnr[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.mnr_ctrl_3.reg_blur_sel,GET_BITS(pp->dnr_____mnr[5],0,1));
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_O26F22_Wr(dnr.detail_ctrl.reg_bnr_diff_p,GET_BITS(pp->dnr___dcbnr[0],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.detail_ctrl.reg_bnr_diff_l,GET_BITS(pp->dnr___dcbnr[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_dc_motion_min,GET_BITS(pp->dnr___dcbnr[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_dc_motion_max,GET_BITS(pp->dnr___dcbnr[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_dc_blur_sel,GET_BITS(pp->dnr___dcbnr[4],0,2));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_1.reg_var_cut_resolution,GET_BITS(pp->dnr___dcbnr[5],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_1.reg_var_h_gain,GET_BITS(pp->dnr___dcbnr[6],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_1.reg_var_v_gain,GET_BITS(pp->dnr___dcbnr[7],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_1.reg_luma_gain_en,GET_BITS(pp->dnr___dcbnr[8],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_2.reg_dc_protection_th,GET_BITS(pp->dnr___dcbnr[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_2.reg_dc_protection_en,GET_BITS(pp->dnr___dcbnr[10],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_2.reg_dc_motion_en,GET_BITS(pp->dnr___dcbnr[11],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_2.reg_dc_var_en,GET_BITS(pp->dnr___dcbnr[12],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th0,GET_BITS(pp->dnr___dcbnr[13],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th1,GET_BITS(pp->dnr___dcbnr[14],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th2,GET_BITS(pp->dnr___dcbnr[15],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th3,GET_BITS(pp->dnr___dcbnr[16],0,8));
		//PE_CHPI_TBL0_O26F22_Wr(dnr.sc_bnr_ctrl_0.reg_sc_bnr_en,GET_BITS(pp->dnr___dcbnr[17],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x0,GET_BITS(pp->dnr___dcbnr[18],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x1,GET_BITS(pp->dnr___dcbnr[19],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x2,GET_BITS(pp->dnr___dcbnr[20],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_8.reg_gain_x3,GET_BITS(pp->dnr___dcbnr[21],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x4,GET_BITS(pp->dnr___dcbnr[22],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x5,GET_BITS(pp->dnr___dcbnr[23],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x6,GET_BITS(pp->dnr___dcbnr[24],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_9.reg_gain_x7,GET_BITS(pp->dnr___dcbnr[25],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y0,GET_BITS(pp->dnr___dcbnr[26],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y1,GET_BITS(pp->dnr___dcbnr[27],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y2,GET_BITS(pp->dnr___dcbnr[28],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_10.reg_gain_y3,GET_BITS(pp->dnr___dcbnr[29],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y4,GET_BITS(pp->dnr___dcbnr[30],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y5,GET_BITS(pp->dnr___dcbnr[31],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y6,GET_BITS(pp->dnr___dcbnr[32],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_dc_bnr_ctrl_11.reg_gain_y7,GET_BITS(pp->dnr___dcbnr[33],0,8));
		/*dnr___acbnr*/
		PE_CHPI_TBL0_O26F22_Wr(dnr.detail_ctrl.reg_bnr_ac_detail_min,GET_BITS(pp->dnr___acbnr[0],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.detail_ctrl.reg_bnr_ac_detail_max,GET_BITS(pp->dnr___acbnr[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th,GET_BITS(pp->dnr___acbnr[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th,GET_BITS(pp->dnr___acbnr[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h,GET_BITS(pp->dnr___acbnr[4],0,2));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min,GET_BITS(pp->dnr___acbnr[5],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max,GET_BITS(pp->dnr___acbnr[6],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th,GET_BITS(pp->dnr___acbnr[7],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_0,GET_BITS(pp->dnr___acbnr[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_1,GET_BITS(pp->dnr___acbnr[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_2,GET_BITS(pp->dnr___acbnr[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_3,GET_BITS(pp->dnr___acbnr[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0,GET_BITS(pp->dnr___acbnr[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1,GET_BITS(pp->dnr___acbnr[13],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2,GET_BITS(pp->dnr___acbnr[14],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3,GET_BITS(pp->dnr___acbnr[15],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min,GET_BITS(pp->dnr___acbnr[16],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max,GET_BITS(pp->dnr___acbnr[17],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v,GET_BITS(pp->dnr___acbnr[18],0,2));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th1,GET_BITS(pp->dnr___acbnr[19],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th2,GET_BITS(pp->dnr___acbnr[20],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th3,GET_BITS(pp->dnr___acbnr[21],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th4,GET_BITS(pp->dnr___acbnr[22],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th,GET_BITS(pp->dnr___acbnr[23],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0,GET_BITS(pp->dnr___acbnr[24],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1,GET_BITS(pp->dnr___acbnr[25],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2,GET_BITS(pp->dnr___acbnr[26],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3,GET_BITS(pp->dnr___acbnr[27],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0,GET_BITS(pp->dnr___acbnr[28],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1,GET_BITS(pp->dnr___acbnr[29],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2,GET_BITS(pp->dnr___acbnr[30],0,8));

		PE_CHPI_TBL0_O26F22_WrFL(dnr.dnr_max_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.mnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_0.udata32);
		//PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_dc_bnr_ctrl_12.udata32);
		/*dnr_____mnr*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.mnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.mnr_ctrl_3.udata32);
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_3.udata32);
		//PE_CHPI_TBL0_O26F22_WrFL(dnr.sc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_dc_bnr_ctrl_8.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_dc_bnr_ctrl_9.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_dc_bnr_ctrl_10.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_dc_bnr_ctrl_11.udata32);
		/*dnr___acbnr*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_4.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_5.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_6.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.ac_bnr_ctrl_7.udata32);

		/* download dnr sqm db */
		/* see PE_NRD_HW_O26_DownloadDnrSqmCmnUserDb */
		/* PE_CHPI_DNR_SQM_O26F22_T                 sqm3;//14 */
		PE_CHPI_TBL0_O26F22_QWr(sqm3.ui32,pp->dnr__ui_val);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm3.data32[i],pp->dnr___sqmui[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm3.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(sqm3.cnt32,i);

		/* download dnr user db */
		/* see PE_NRD_HW_O26_DownloadDnrUserDb */
		/* PE_CHPI_DNR_USER_O26F22_T                usr1;//18 */
		PE_CHPI_TBL0_O26F22_QWr(usr1.ui32,pp->dnr__ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(usr1.data32[i],pp->dnr____buff[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(usr1.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(usr1.cnt32,i);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_DNR);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM3);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_USR1);

		/* set user */
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dnr_max_ctrl.reg_dnr_max_enable,GET_BITS(pp->dnr______ui[0],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_0.reg_mnr_chroma_en,GET_BITS(pp->dnr______ui[1],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_0.reg_mnr_enable,GET_BITS(pp->dnr______ui[2],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_bnr_enable,GET_BITS(pp->dnr______ui[3],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_obj_gain_mul,GET_BITS(pp->dnr______ui[4],0,2));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en,GET_BITS(pp->dnr______ui[5],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en,GET_BITS(pp->dnr______ui[6],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_v_en,GET_BITS(pp->dnr______ui[7],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_h_en,GET_BITS(pp->dnr______ui[8],0,1));
		//PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_x_min,GET_BITS(pp->dnr______ui[9],0,8));
		//PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_x_max,GET_BITS(pp->dnr______ui[10],0,8));
		//PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_y_min,GET_BITS(pp->dnr______ui[11],0,8));
		//PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_12.reg_psp_blur_y_max,GET_BITS(pp->dnr______ui[12],0,8));
		/*dnr_____mnr*/
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_1.reg_mmd_x_min,GET_BITS(pp->dnr_____mnr[0],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_1.reg_mmd_x_max,GET_BITS(pp->dnr_____mnr[1],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_1.reg_mmd_y_min,GET_BITS(pp->dnr_____mnr[2],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_1.reg_mmd_y_max,GET_BITS(pp->dnr_____mnr[3],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_3.reg_mmd_scale,GET_BITS(pp->dnr_____mnr[4],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,mnr_ctrl_3.reg_blur_sel,GET_BITS(pp->dnr_____mnr[5],0,1));
		/*dnr___dcbnr*/
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,detail_ctrl.reg_bnr_diff_p,GET_BITS(pp->dnr___dcbnr[0],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,detail_ctrl.reg_bnr_diff_l,GET_BITS(pp->dnr___dcbnr[1],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_motion_min,GET_BITS(pp->dnr___dcbnr[2],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_motion_max,GET_BITS(pp->dnr___dcbnr[3],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_dc_blur_sel,GET_BITS(pp->dnr___dcbnr[4],0,2));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_1.reg_var_cut_resolution,GET_BITS(pp->dnr___dcbnr[5],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_1.reg_var_h_gain,GET_BITS(pp->dnr___dcbnr[6],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_1.reg_var_v_gain,GET_BITS(pp->dnr___dcbnr[7],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_1.reg_luma_gain_en,GET_BITS(pp->dnr___dcbnr[8],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_protection_th,GET_BITS(pp->dnr___dcbnr[9],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_protection_en,GET_BITS(pp->dnr___dcbnr[10],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_motion_en,GET_BITS(pp->dnr___dcbnr[11],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_2.reg_dc_var_en,GET_BITS(pp->dnr___dcbnr[12],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th0,GET_BITS(pp->dnr___dcbnr[13],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th1,GET_BITS(pp->dnr___dcbnr[14],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th2,GET_BITS(pp->dnr___dcbnr[15],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_3.reg_dc_bnr_var_th3,GET_BITS(pp->dnr___dcbnr[16],0,8));
		//PE_CHPI_DNR_HW_O26F22_USER(p_dnr,sc_bnr_ctrl_0.reg_sc_bnr_en,GET_BITS(pp->dnr___dcbnr[17],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x0,GET_BITS(pp->dnr___dcbnr[18],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x1,GET_BITS(pp->dnr___dcbnr[19],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x2,GET_BITS(pp->dnr___dcbnr[20],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_8.reg_gain_x3,GET_BITS(pp->dnr___dcbnr[21],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x4,GET_BITS(pp->dnr___dcbnr[22],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x5,GET_BITS(pp->dnr___dcbnr[23],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x6,GET_BITS(pp->dnr___dcbnr[24],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_9.reg_gain_x7,GET_BITS(pp->dnr___dcbnr[25],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y0,GET_BITS(pp->dnr___dcbnr[26],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y1,GET_BITS(pp->dnr___dcbnr[27],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y2,GET_BITS(pp->dnr___dcbnr[28],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_10.reg_gain_y3,GET_BITS(pp->dnr___dcbnr[29],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y4,GET_BITS(pp->dnr___dcbnr[30],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y5,GET_BITS(pp->dnr___dcbnr[31],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y6,GET_BITS(pp->dnr___dcbnr[32],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_dc_bnr_ctrl_11.reg_gain_y7,GET_BITS(pp->dnr___dcbnr[33],0,8));
		/*dnr___acbnr*/
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,detail_ctrl.reg_bnr_ac_detail_min,GET_BITS(pp->dnr___acbnr[0],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,detail_ctrl.reg_bnr_ac_detail_max,GET_BITS(pp->dnr___acbnr[1],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th,GET_BITS(pp->dnr___acbnr[2],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th,GET_BITS(pp->dnr___acbnr[3],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h,GET_BITS(pp->dnr___acbnr[4],0,2));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min,GET_BITS(pp->dnr___acbnr[5],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max,GET_BITS(pp->dnr___acbnr[6],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th,GET_BITS(pp->dnr___acbnr[7],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_0,GET_BITS(pp->dnr___acbnr[8],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_1,GET_BITS(pp->dnr___acbnr[9],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_2,GET_BITS(pp->dnr___acbnr[10],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_2.reg_bnr_ac_motion_3,GET_BITS(pp->dnr___acbnr[11],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0,GET_BITS(pp->dnr___acbnr[12],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1,GET_BITS(pp->dnr___acbnr[13],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2,GET_BITS(pp->dnr___acbnr[14],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3,GET_BITS(pp->dnr___acbnr[15],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min,GET_BITS(pp->dnr___acbnr[16],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max,GET_BITS(pp->dnr___acbnr[17],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v,GET_BITS(pp->dnr___acbnr[18],0,2));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th1,GET_BITS(pp->dnr___acbnr[19],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th2,GET_BITS(pp->dnr___acbnr[20],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th3,GET_BITS(pp->dnr___acbnr[21],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_5.reg_bnr_ac_detail_th4,GET_BITS(pp->dnr___acbnr[22],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th,GET_BITS(pp->dnr___acbnr[23],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0,GET_BITS(pp->dnr___acbnr[24],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1,GET_BITS(pp->dnr___acbnr[25],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2,GET_BITS(pp->dnr___acbnr[26],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3,GET_BITS(pp->dnr___acbnr[27],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0,GET_BITS(pp->dnr___acbnr[28],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1,GET_BITS(pp->dnr___acbnr[29],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2,GET_BITS(pp->dnr___acbnr[30],0,8));
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_DNR_HW_O26F22_GetCtrl(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	UINT32 i;
	LX_PE_NRD_DNR_ALL_CMN_T stParams;
	LX_PE_NRD_DNR_ALL_CMN_T *pp;
	UINT8 *pd;
	UINT32 *pd32;
	do{
 		if (!gPE_CHPI_DDR_O26)	break;
		pp = &stParams;
		memset(pp,0,sizeof(LX_PE_NRD_DNR_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dnr_max_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.mnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_dc_bnr_ctrl_12.udata32);
		/*dnr_____mnr*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.mnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.mnr_ctrl_3.udata32);
		/*dnr___dcbnr*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dc_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dc_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.dc_bnr_ctrl_3.udata32);
		//PE_CHPI_TBL0_O26F22_RdFL(dnr.sc_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_dc_bnr_ctrl_8.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_dc_bnr_ctrl_9.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_dc_bnr_ctrl_10.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_dc_bnr_ctrl_11.udata32);
		/*dnr___acbnr*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.detail_ctrl.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_1.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_2.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_3.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_4.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_5.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_6.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.ac_bnr_ctrl_7.udata32);


		/* set tbl */
		pp->dnr______ui[0] =PE_CHPI_TBL0_O26F22_Rd(dnr.dnr_max_ctrl.reg_dnr_max_enable);
		pp->dnr______ui[1] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_0.reg_mnr_chroma_en);
		pp->dnr______ui[2] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_0.reg_mnr_enable);
		pp->dnr______ui[3] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_0.reg_dc_bnr_enable);
		pp->dnr______ui[4] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_0.reg_obj_gain_mul);
		pp->dnr______ui[5] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_chroma_en);
		pp->dnr______ui[6] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_chroma_en);
		pp->dnr______ui[7] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_v_en);
		pp->dnr______ui[8] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_h_en);
		//pp->dnr______ui[9] =PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_min);
		//pp->dnr______ui[10]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_x_max);
		//pp->dnr______ui[11]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_min);
		//pp->dnr______ui[12]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_12.reg_psp_blur_y_max);
		/*dnr_____mnr*/
		pp->dnr_____mnr[0] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_1.reg_mmd_x_min);
		pp->dnr_____mnr[1] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_1.reg_mmd_x_max);
		pp->dnr_____mnr[2] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_1.reg_mmd_y_min);
		pp->dnr_____mnr[3] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_1.reg_mmd_y_max);
		pp->dnr_____mnr[4] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_3.reg_mmd_scale);
		pp->dnr_____mnr[5] =PE_CHPI_TBL0_O26F22_Rd(dnr.mnr_ctrl_3.reg_blur_sel);
		/*dnr___dcbnr*/
		pp->dnr___dcbnr[0] =PE_CHPI_TBL0_O26F22_Rd(dnr.detail_ctrl.reg_bnr_diff_p);
		pp->dnr___dcbnr[1] =PE_CHPI_TBL0_O26F22_Rd(dnr.detail_ctrl.reg_bnr_diff_l);
		pp->dnr___dcbnr[2] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_0.reg_dc_motion_min);
		pp->dnr___dcbnr[3] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_0.reg_dc_motion_max);
		pp->dnr___dcbnr[4] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_0.reg_dc_blur_sel);
		pp->dnr___dcbnr[5] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_1.reg_var_cut_resolution);
		pp->dnr___dcbnr[6] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_1.reg_var_h_gain);
		pp->dnr___dcbnr[7] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_1.reg_var_v_gain);
		pp->dnr___dcbnr[8] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_1.reg_luma_gain_en);
		pp->dnr___dcbnr[9] =PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_2.reg_dc_protection_th);
		pp->dnr___dcbnr[10]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_2.reg_dc_protection_en);
		pp->dnr___dcbnr[11]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_2.reg_dc_motion_en);
		pp->dnr___dcbnr[12]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_2.reg_dc_var_en);
		pp->dnr___dcbnr[13]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th0);
		pp->dnr___dcbnr[14]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th1);
		pp->dnr___dcbnr[15]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th2);
		pp->dnr___dcbnr[16]=PE_CHPI_TBL0_O26F22_Rd(dnr.dc_bnr_ctrl_3.reg_dc_bnr_var_th3);
		//pp->dnr___dcbnr[17]=PE_CHPI_TBL0_O26F22_Rd(dnr.sc_bnr_ctrl_0.reg_sc_bnr_en);
		pp->dnr___dcbnr[18]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x0);
		pp->dnr___dcbnr[19]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x1);
		pp->dnr___dcbnr[20]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x2);
		pp->dnr___dcbnr[21]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_8.reg_gain_x3);
		pp->dnr___dcbnr[22]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x4);
		pp->dnr___dcbnr[23]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x5);
		pp->dnr___dcbnr[24]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x6);
		pp->dnr___dcbnr[25]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_9.reg_gain_x7);
		pp->dnr___dcbnr[26]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y0);
		pp->dnr___dcbnr[27]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y1);
		pp->dnr___dcbnr[28]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y2);
		pp->dnr___dcbnr[29]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_10.reg_gain_y3);
		pp->dnr___dcbnr[30]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y4);
		pp->dnr___dcbnr[31]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y5);
		pp->dnr___dcbnr[32]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y6);
		pp->dnr___dcbnr[33]=PE_CHPI_TBL0_O26F22_Rd(dnr.reg_dc_bnr_ctrl_11.reg_gain_y7);
		/*dnr___acbnr*/
		pp->dnr___acbnr[0] =PE_CHPI_TBL0_O26F22_Rd(dnr.detail_ctrl.reg_bnr_ac_detail_min);
		pp->dnr___acbnr[1] =PE_CHPI_TBL0_O26F22_Rd(dnr.detail_ctrl.reg_bnr_ac_detail_max);
		pp->dnr___acbnr[2] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_h_th);
		pp->dnr___acbnr[3] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_diff_min_v_th);
		pp->dnr___acbnr[4] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_0.reg_bnr_ac_acness_resol_h);
		pp->dnr___acbnr[5] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_min);
		pp->dnr___acbnr[6] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_h_acness_max);
		pp->dnr___acbnr[7] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_1.reg_bnr_ac_global_motion_th);
		pp->dnr___acbnr[8] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_0);
		pp->dnr___acbnr[9] =PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_1);
		pp->dnr___acbnr[10]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_2);
		pp->dnr___acbnr[11]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_2.reg_bnr_ac_motion_3);
		pp->dnr___acbnr[12]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_0);
		pp->dnr___acbnr[13]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_1);
		pp->dnr___acbnr[14]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_2);
		pp->dnr___acbnr[15]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_3.reg_bnr_ac_motion_y_3);
		pp->dnr___acbnr[16]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_min);
		pp->dnr___acbnr[17]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_v_acness_max);
		pp->dnr___acbnr[18]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_4.reg_bnr_ac_acness_resol_v);
		pp->dnr___acbnr[19]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th1);
		pp->dnr___acbnr[20]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th2);
		pp->dnr___acbnr[21]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th3);
		pp->dnr___acbnr[22]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_5.reg_bnr_ac_detail_th4);
		pp->dnr___acbnr[23]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_detail_gain_th);
		pp->dnr___acbnr[24]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h0);
		pp->dnr___acbnr[25]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h1);
		pp->dnr___acbnr[26]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_6.reg_bnr_ac_pos_gain_h2);
		pp->dnr___acbnr[27]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_h3);
		pp->dnr___acbnr[28]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l0);
		pp->dnr___acbnr[29]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l1);
		pp->dnr___acbnr[30]=PE_CHPI_TBL0_O26F22_Rd(dnr.ac_bnr_ctrl_7.reg_bnr_ac_pos_gain_l2);
		/* download dnr sq[32]=m db */
		/* see PE_NRD_HW_O[33]=20_DownloadDnrSqmCmnUserDb */
		/* PE_CHPI_DNR_SQM_O26F22_T				 sqm3;//14 */
		PE_CHPI_TBL0_O26F22_QRd(sqm3.ui32,pp->dnr__ui_val);
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(sqm3.data32[i],pp->dnr___sqmui[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm3.cnt32);

		/* download dnr user db */
		/* see PE_NRD_HW_O26_DownloadDnrUserDb */
		/* PE_CHPI_DNR_USER_O26F22_T				 usr1;//18 */
		PE_CHPI_TBL0_O26F22_QRd(usr1.ui32,pp->dnr__ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(usr1.data32[i],pp->dnr____buff[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(usr1.cnt32);


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
	#endif
	return ret;
}


int PE_CHPI_DNR_HW_O26F22_SetDcntCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	UINT32 i;
	LX_PE_NRD_DCNT_CMN_T *p_param;
	LX_PE_NRD_DCNT1_ALL_CMN_T *pp;
	PE_DNR_HW_PARAM_DATA_O26F22_T *p_dnr = &_g_pe_dnr_hw_param_data_o26f22;
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		p_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
		pp = (LX_PE_NRD_DCNT1_ALL_CMN_T *)p_param->data;
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_0.reg_1st_out_rd_on,    GET_BITS(pp->deconnd_____ui[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_0.reg_1st_out_rd_bit,   GET_BITS(pp->deconnd_____ui[1],0,3));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_on,    GET_BITS(pp->deconnd_____ui[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_bit,   GET_BITS(pp->deconnd_____ui[3],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_17.reg_decon_1st_en,    GET_BITS(pp->deconnd_____ui[4],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconnd_____ui[5],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconnd_____ui[6],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconnd_____ui[7],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconnd_____ui[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconnd_____ui[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconnd_____ui[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconnd_____ui[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconnd_____ui[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconnd_____ui[13],0,8));

		/*dnr_dcnt*/
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_18.reg_var_cut_resolution, GET_BITS(pp->deconnd____cmn[0],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_18.reg_var_h_gain, 		GET_BITS(pp->deconnd____cmn[1],0,4));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_18.reg_var_chroma_en,		GET_BITS(pp->deconnd____cmn[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th0,	GET_BITS(pp->deconnd____cmn[3],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th1,	GET_BITS(pp->deconnd____cmn[4],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_21.reg_decon_var_x_th2,	GET_BITS(pp->deconnd____cmn[5],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_x_th3,	GET_BITS(pp->deconnd____cmn[6],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_y_th0,	GET_BITS(pp->deconnd____cmn[7],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_22.reg_decon_var_y_th1,	GET_BITS(pp->deconnd____cmn[8],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_23.reg_decon_var_y_th2,	GET_BITS(pp->deconnd____cmn[9],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_23.reg_decon_var_y_th3,	GET_BITS(pp->deconnd____cmn[10],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_23.reg_decon_luma_x_th0,	GET_BITS(pp->deconnd____cmn[11],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th1,	GET_BITS(pp->deconnd____cmn[12],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th2,	GET_BITS(pp->deconnd____cmn[13],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th3,	GET_BITS(pp->deconnd____cmn[14],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th4,	GET_BITS(pp->deconnd____cmn[15],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th5,	GET_BITS(pp->deconnd____cmn[16],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th6,	GET_BITS(pp->deconnd____cmn[17],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_x_th7,	GET_BITS(pp->deconnd____cmn[18],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th0,	GET_BITS(pp->deconnd____cmn[19],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th1,	GET_BITS(pp->deconnd____cmn[20],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th2,	GET_BITS(pp->deconnd____cmn[21],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th3,	GET_BITS(pp->deconnd____cmn[22],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th4,	GET_BITS(pp->deconnd____cmn[23],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th5,	GET_BITS(pp->deconnd____cmn[24],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th6,	GET_BITS(pp->deconnd____cmn[25],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th7,	GET_BITS(pp->deconnd____cmn[26],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_44.reg_motion_gain_x0, 	GET_BITS(pp->deconnd____cmn[27],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_44.reg_motion_gain_x1, 	GET_BITS(pp->deconnd____cmn[28],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_44.reg_motion_gain_x2, 	GET_BITS(pp->deconnd____cmn[29],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_44.reg_motion_gain_x3, 	GET_BITS(pp->deconnd____cmn[30],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_45.reg_motion_gain_y0, 	GET_BITS(pp->deconnd____cmn[31],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_45.reg_motion_gain_y1, 	GET_BITS(pp->deconnd____cmn[32],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_45.reg_motion_gain_y2, 	GET_BITS(pp->deconnd____cmn[33],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_45.reg_motion_gain_y3, 	GET_BITS(pp->deconnd____cmn[34],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x0,	GET_BITS(pp->deconnd____cmn[35],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x1,	GET_BITS(pp->deconnd____cmn[36],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x2,	GET_BITS(pp->deconnd____cmn[37],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x3,	GET_BITS(pp->deconnd____cmn[38],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y0,	GET_BITS(pp->deconnd____cmn[39],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y1,	GET_BITS(pp->deconnd____cmn[40],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y2,	GET_BITS(pp->deconnd____cmn[41],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y3,	GET_BITS(pp->deconnd____cmn[42],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x0,	GET_BITS(pp->deconnd____cmn[43],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x1,	GET_BITS(pp->deconnd____cmn[44],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x2,	GET_BITS(pp->deconnd____cmn[45],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_x3,	GET_BITS(pp->deconnd____cmn[46],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_y0,	GET_BITS(pp->deconnd____cmn[47],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_y1,	GET_BITS(pp->deconnd____cmn[48],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_71.reg_var_lowapl_lut_y2,	GET_BITS(pp->deconnd____cmn[49],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_71.reg_var_lowapl_lut_y3,	GET_BITS(pp->deconnd____cmn[50],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_71.reg_var_lowapl_blend_x0,GET_BITS(pp->deconnd____cmn[51],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x1,GET_BITS(pp->deconnd____cmn[52],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x2,GET_BITS(pp->deconnd____cmn[53],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x3,GET_BITS(pp->deconnd____cmn[54],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y0,GET_BITS(pp->deconnd____cmn[55],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y1,GET_BITS(pp->deconnd____cmn[56],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y2,GET_BITS(pp->deconnd____cmn[57],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y3,GET_BITS(pp->deconnd____cmn[58],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_84.reg_1st_rd_luma_en, 	GET_BITS(pp->deconnd____cmn[59],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_84.reg_2nd_rd_luma_en, 	GET_BITS(pp->deconnd____cmn[60],0,1));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_87.reg_1st_rd_luma_x0, 	GET_BITS(pp->deconnd____cmn[61],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_87.reg_1st_rd_luma_x1, 	GET_BITS(pp->deconnd____cmn[62],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_88.reg_1st_rd_luma_x2, 	GET_BITS(pp->deconnd____cmn[63],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_88.reg_1st_rd_luma_x3, 	GET_BITS(pp->deconnd____cmn[64],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_89.reg_1st_rd_luma_x4, 	GET_BITS(pp->deconnd____cmn[65],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_89.reg_1st_rd_luma_x5, 	GET_BITS(pp->deconnd____cmn[66],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_90.reg_1st_rd_luma_x6, 	GET_BITS(pp->deconnd____cmn[67],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_90.reg_1st_rd_luma_x7, 	GET_BITS(pp->deconnd____cmn[68],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_91.reg_1st_rd_luma_y0, 	GET_BITS(pp->deconnd____cmn[69],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_91.reg_1st_rd_luma_y1, 	GET_BITS(pp->deconnd____cmn[70],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_92.reg_1st_rd_luma_y2, 	GET_BITS(pp->deconnd____cmn[71],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_92.reg_1st_rd_luma_y3, 	GET_BITS(pp->deconnd____cmn[72],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_93.reg_1st_rd_luma_y4, 	GET_BITS(pp->deconnd____cmn[73],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_93.reg_1st_rd_luma_y5, 	GET_BITS(pp->deconnd____cmn[74],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_94.reg_1st_rd_luma_y6, 	GET_BITS(pp->deconnd____cmn[75],0,10));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_94.reg_1st_rd_luma_y7, 	GET_BITS(pp->deconnd____cmn[76],0,10));
		/* face obj*/
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconnd___face[0],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconnd___face[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconnd___face[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconnd___face[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconnd___face[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconnd___face[5],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconnd___face[6],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconnd___face[7],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconnd___face[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconnd___face[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconnd___face[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconnd___face[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconnd___face[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconnd___face[13],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconnd___face[14],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconnd___face[15],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconnd___face[16],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconnd___face[17],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconnd___face[18],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconnd___face[19],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconnd___face[20],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconnd___face[21],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconnd___face[22],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconnd___face[23],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x3,	GET_BITS(pp->deconnd___face[24],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x2,	GET_BITS(pp->deconnd___face[25],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x1,	GET_BITS(pp->deconnd___face[26],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x0,	GET_BITS(pp->deconnd___face[27],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y3,	GET_BITS(pp->deconnd___face[28],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y2,	GET_BITS(pp->deconnd___face[29],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y1,	GET_BITS(pp->deconnd___face[30],0,8));
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y0,	GET_BITS(pp->deconnd___face[31],0,8));

		/*dnr_dcnt_ui*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_56.udata32);

		/*dnr_dcnt*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_44.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_45.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_48.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_49.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_84.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_87.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_88.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_89.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_90.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_91.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_92.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_93.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_94.udata32);
		/* face obj*/
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_55.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_97.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_98.udata32);

		/* download dct sqm db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb */
		/* PE_CHPI_DNR_DCNT_SQM_O26F22_T            sqm4;//15 */
		PE_CHPI_TBL0_O26F22_QWr(sqm4.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm4.data32[i],pp->deconnd__sqmui[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm4.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(sqm4.cnt32,i);

		/* download dct user db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntUserDb */
		/* PE_CHPI_DNR_DCNT_USER_O26F22_T           usr2;//19 */
		PE_CHPI_TBL0_O26F22_QWr(usr2.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(usr2.data32[i],pp->deconnd___buff[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(usr2.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(usr2.cnt32,i);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_DNR);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM4);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_USR2);

		/* set user */
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_0.reg_1st_out_rd_on,GET_BITS(pp->deconnd_____ui[0],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_0.reg_1st_out_rd_bit,GET_BITS(pp->deconnd_____ui[1],0,3));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_7.reg_2nd_out_rd_on,GET_BITS(pp->deconnd_____ui[2],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_7.reg_2nd_out_rd_bit,GET_BITS(pp->deconnd_____ui[3],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_17.reg_decon_1st_en,GET_BITS(pp->deconnd_____ui[4],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th3,GET_BITS(pp->deconnd_____ui[5],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th2,GET_BITS(pp->deconnd_____ui[6],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th1,GET_BITS(pp->deconnd_____ui[7],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_19.reg_decon_diff_x_th0,GET_BITS(pp->deconnd_____ui[8],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th3,GET_BITS(pp->deconnd_____ui[9],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th2,GET_BITS(pp->deconnd_____ui[10],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th1,GET_BITS(pp->deconnd_____ui[11],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_20.reg_decon_diff_y_th0,GET_BITS(pp->deconnd_____ui[12],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_56.reg_face_master_gain,GET_BITS(pp->deconnd_____ui[13],0,8));
		/*dnr_dcnt*/
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_18.reg_var_cut_resolution, GET_BITS(pp->deconnd____cmn[0],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_18.reg_var_h_gain, 		GET_BITS(pp->deconnd____cmn[1],0,4));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_18.reg_var_chroma_en,		GET_BITS(pp->deconnd____cmn[2],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th0,	GET_BITS(pp->deconnd____cmn[3],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th1,	GET_BITS(pp->deconnd____cmn[4],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_21.reg_decon_var_x_th2,	GET_BITS(pp->deconnd____cmn[5],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_x_th3,	GET_BITS(pp->deconnd____cmn[6],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_y_th0,	GET_BITS(pp->deconnd____cmn[7],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_22.reg_decon_var_y_th1,	GET_BITS(pp->deconnd____cmn[8],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_23.reg_decon_var_y_th2,	GET_BITS(pp->deconnd____cmn[9],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_23.reg_decon_var_y_th3,	GET_BITS(pp->deconnd____cmn[10],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_23.reg_decon_luma_x_th0,	GET_BITS(pp->deconnd____cmn[11],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th1,	GET_BITS(pp->deconnd____cmn[12],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th2,	GET_BITS(pp->deconnd____cmn[13],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_24.reg_decon_luma_x_th3,	GET_BITS(pp->deconnd____cmn[14],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th4,	GET_BITS(pp->deconnd____cmn[15],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th5,	GET_BITS(pp->deconnd____cmn[16],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_25.reg_decon_luma_x_th6,	GET_BITS(pp->deconnd____cmn[17],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_x_th7,	GET_BITS(pp->deconnd____cmn[18],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_y_th0,	GET_BITS(pp->deconnd____cmn[19],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_26.reg_decon_luma_y_th1,	GET_BITS(pp->deconnd____cmn[20],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th2,	GET_BITS(pp->deconnd____cmn[21],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th3,	GET_BITS(pp->deconnd____cmn[22],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_27.reg_decon_luma_y_th4,	GET_BITS(pp->deconnd____cmn[23],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th5,	GET_BITS(pp->deconnd____cmn[24],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th6,	GET_BITS(pp->deconnd____cmn[25],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_28.reg_decon_luma_y_th7,	GET_BITS(pp->deconnd____cmn[26],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_44.reg_motion_gain_x0, 	GET_BITS(pp->deconnd____cmn[27],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_44.reg_motion_gain_x1, 	GET_BITS(pp->deconnd____cmn[28],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_44.reg_motion_gain_x2, 	GET_BITS(pp->deconnd____cmn[29],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_44.reg_motion_gain_x3, 	GET_BITS(pp->deconnd____cmn[30],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_45.reg_motion_gain_y0, 	GET_BITS(pp->deconnd____cmn[31],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_45.reg_motion_gain_y1, 	GET_BITS(pp->deconnd____cmn[32],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_45.reg_motion_gain_y2, 	GET_BITS(pp->deconnd____cmn[33],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_45.reg_motion_gain_y3, 	GET_BITS(pp->deconnd____cmn[34],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_48.reg_lut_blur_sim_x0,	GET_BITS(pp->deconnd____cmn[35],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_48.reg_lut_blur_sim_x1,	GET_BITS(pp->deconnd____cmn[36],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_48.reg_lut_blur_sim_x2,	GET_BITS(pp->deconnd____cmn[37],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_48.reg_lut_blur_sim_x3,	GET_BITS(pp->deconnd____cmn[38],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_49.reg_lut_blur_sim_y0,	GET_BITS(pp->deconnd____cmn[39],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_49.reg_lut_blur_sim_y1,	GET_BITS(pp->deconnd____cmn[40],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_49.reg_lut_blur_sim_y2,	GET_BITS(pp->deconnd____cmn[41],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_49.reg_lut_blur_sim_y3,	GET_BITS(pp->deconnd____cmn[42],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_69.reg_var_lowapl_lut_x0,	GET_BITS(pp->deconnd____cmn[43],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_69.reg_var_lowapl_lut_x1,	GET_BITS(pp->deconnd____cmn[44],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_69.reg_var_lowapl_lut_x2,	GET_BITS(pp->deconnd____cmn[45],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_70.reg_var_lowapl_lut_x3,	GET_BITS(pp->deconnd____cmn[46],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_70.reg_var_lowapl_lut_y0,	GET_BITS(pp->deconnd____cmn[47],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_70.reg_var_lowapl_lut_y1,	GET_BITS(pp->deconnd____cmn[48],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_71.reg_var_lowapl_lut_y2,	GET_BITS(pp->deconnd____cmn[49],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_71.reg_var_lowapl_lut_y3,	GET_BITS(pp->deconnd____cmn[50],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_71.reg_var_lowapl_blend_x0,GET_BITS(pp->deconnd____cmn[51],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_72.reg_var_lowapl_blend_x1,GET_BITS(pp->deconnd____cmn[52],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_72.reg_var_lowapl_blend_x2,GET_BITS(pp->deconnd____cmn[53],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_72.reg_var_lowapl_blend_x3,GET_BITS(pp->deconnd____cmn[54],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_73.reg_var_lowapl_blend_y0,GET_BITS(pp->deconnd____cmn[55],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_73.reg_var_lowapl_blend_y1,GET_BITS(pp->deconnd____cmn[56],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_73.reg_var_lowapl_blend_y2,GET_BITS(pp->deconnd____cmn[57],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_73.reg_var_lowapl_blend_y3,GET_BITS(pp->deconnd____cmn[58],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_84.reg_1st_rd_luma_en, 	GET_BITS(pp->deconnd____cmn[59],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_84.reg_2nd_rd_luma_en, 	GET_BITS(pp->deconnd____cmn[60],0,1));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_87.reg_1st_rd_luma_x0, 	GET_BITS(pp->deconnd____cmn[61],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_87.reg_1st_rd_luma_x1, 	GET_BITS(pp->deconnd____cmn[62],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_88.reg_1st_rd_luma_x2, 	GET_BITS(pp->deconnd____cmn[63],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_88.reg_1st_rd_luma_x3, 	GET_BITS(pp->deconnd____cmn[64],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_89.reg_1st_rd_luma_x4, 	GET_BITS(pp->deconnd____cmn[65],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_89.reg_1st_rd_luma_x5, 	GET_BITS(pp->deconnd____cmn[66],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_90.reg_1st_rd_luma_x6, 	GET_BITS(pp->deconnd____cmn[67],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_90.reg_1st_rd_luma_x7, 	GET_BITS(pp->deconnd____cmn[68],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_91.reg_1st_rd_luma_y0, 	GET_BITS(pp->deconnd____cmn[69],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_91.reg_1st_rd_luma_y1, 	GET_BITS(pp->deconnd____cmn[70],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_92.reg_1st_rd_luma_y2, 	GET_BITS(pp->deconnd____cmn[71],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_92.reg_1st_rd_luma_y3, 	GET_BITS(pp->deconnd____cmn[72],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_93.reg_1st_rd_luma_y4, 	GET_BITS(pp->deconnd____cmn[73],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_93.reg_1st_rd_luma_y5, 	GET_BITS(pp->deconnd____cmn[74],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_94.reg_1st_rd_luma_y6, 	GET_BITS(pp->deconnd____cmn[75],0,10));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_94.reg_1st_rd_luma_y7, 	GET_BITS(pp->deconnd____cmn[76],0,10));
		/* face obj*/
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x0,GET_BITS(pp->deconnd___face[0],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x1,GET_BITS(pp->deconnd___face[1],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x2,GET_BITS(pp->deconnd___face[2],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_50.reg_lut_skin_yy_x3,GET_BITS(pp->deconnd___face[3],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x0,GET_BITS(pp->deconnd___face[4],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x1,GET_BITS(pp->deconnd___face[5],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x2,GET_BITS(pp->deconnd___face[6],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_51.reg_lut_skin_cb_x3,GET_BITS(pp->deconnd___face[7],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x0,GET_BITS(pp->deconnd___face[8],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x1,GET_BITS(pp->deconnd___face[9],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x2,GET_BITS(pp->deconnd___face[10],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_52.reg_lut_skin_cr_x3,GET_BITS(pp->deconnd___face[11],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y0,GET_BITS(pp->deconnd___face[12],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y1,GET_BITS(pp->deconnd___face[13],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y2,GET_BITS(pp->deconnd___face[14],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_53.reg_lut_skin_y3,GET_BITS(pp->deconnd___face[15],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x0,GET_BITS(pp->deconnd___face[16],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x1,GET_BITS(pp->deconnd___face[17],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x2,GET_BITS(pp->deconnd___face[18],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_54.reg_lut_face_x3,GET_BITS(pp->deconnd___face[19],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y0,GET_BITS(pp->deconnd___face[20],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y1,GET_BITS(pp->deconnd___face[21],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y2,GET_BITS(pp->deconnd___face[22],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_55.reg_lut_face_y3,GET_BITS(pp->deconnd___face[23],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_97.reg_ref_mmd_gain_x3,	GET_BITS(pp->deconnd___face[24],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_97.reg_ref_mmd_gain_x2,	GET_BITS(pp->deconnd___face[25],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_97.reg_ref_mmd_gain_x1,	GET_BITS(pp->deconnd___face[26],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_97.reg_ref_mmd_gain_x0,	GET_BITS(pp->deconnd___face[27],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_98.reg_ref_mmd_gain_y3,	GET_BITS(pp->deconnd___face[28],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_98.reg_ref_mmd_gain_y2,	GET_BITS(pp->deconnd___face[29],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_98.reg_ref_mmd_gain_y1,	GET_BITS(pp->deconnd___face[30],0,8));
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_98.reg_ref_mmd_gain_y0,	GET_BITS(pp->deconnd___face[31],0,8));
	}while(0);
		#endif
	return ret;
}
int PE_CHPI_DNR_HW_O26F22_GetDcntCtrl(void)
{
	int ret = RET_OK;
	UINT32 i = 0;
	UINT8  *pd8;
	UINT16 *pd;
	UINT32 *pd32;
	LX_PE_NRD_DCNT1_ALL_CMN_T stParams;
	LX_PE_NRD_DCNT1_ALL_CMN_T *pp;
	do{
 		if (!gPE_CHPI_DDR_O26)	break;
		pp =&stParams;
		memset(pp,0,sizeof(LX_PE_NRD_DCNT1_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized
		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		/*dnr_dcnt_ui*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_0.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_7.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_17.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_19.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_20.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_56.udata32);
		/*dnr_dcnt*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_18.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_21.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_22.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_23.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_24.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_25.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_26.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_27.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_28.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_44.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_45.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_48.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_49.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_69.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_70.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_71.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_72.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_73.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_84.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_87.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_88.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_89.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_90.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_91.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_92.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_93.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_94.udata32);
		/* face obj*/
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_50.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_51.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_52.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_53.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_54.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_55.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_97.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(dnr.reg_decon_ctrl_98.udata32);
		#endif

		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		pp->deconnd_____ui[0] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_0.reg_1st_out_rd_on    );
		pp->deconnd_____ui[1] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_0.reg_1st_out_rd_bit   );
		pp->deconnd_____ui[2] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_on    );
		pp->deconnd_____ui[3] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_7.reg_2nd_out_rd_bit   );
		pp->deconnd_____ui[4] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_17.reg_decon_1st_en    );
		pp->deconnd_____ui[5] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th3);
		pp->deconnd_____ui[6] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th2);
		pp->deconnd_____ui[7] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th1);
		pp->deconnd_____ui[8] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_19.reg_decon_diff_x_th0);
		pp->deconnd_____ui[9] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th3);
		pp->deconnd_____ui[10]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th2);
		pp->deconnd_____ui[11]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th1);
		pp->deconnd_____ui[12]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_20.reg_decon_diff_y_th0);
		pp->deconnd_____ui[13]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_56.reg_face_master_gain);
		pp->deconnd____cmn[0] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_18.reg_var_cut_resolution);
		pp->deconnd____cmn[1] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_18.reg_var_h_gain);
		pp->deconnd____cmn[2] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_18.reg_var_chroma_en);
		pp->deconnd____cmn[3] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th0);
		pp->deconnd____cmn[4] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th1);
		pp->deconnd____cmn[5] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_21.reg_decon_var_x_th2);
		pp->deconnd____cmn[6] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_x_th3);
		pp->deconnd____cmn[7] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_y_th0);
		pp->deconnd____cmn[8] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_22.reg_decon_var_y_th1);
		pp->deconnd____cmn[9] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_23.reg_decon_var_y_th2);
		pp->deconnd____cmn[10] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_23.reg_decon_var_y_th3);
		pp->deconnd____cmn[11] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_23.reg_decon_luma_x_th0);
		pp->deconnd____cmn[12] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th1);
		pp->deconnd____cmn[13] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th2);
		pp->deconnd____cmn[14] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_24.reg_decon_luma_x_th3);
		pp->deconnd____cmn[15] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th4);
		pp->deconnd____cmn[16] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th5);
		pp->deconnd____cmn[17] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_25.reg_decon_luma_x_th6);
		pp->deconnd____cmn[18] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_x_th7);
		pp->deconnd____cmn[19] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th0);
		pp->deconnd____cmn[20] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_26.reg_decon_luma_y_th1);
		pp->deconnd____cmn[21] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th2);
		pp->deconnd____cmn[22] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th3);
		pp->deconnd____cmn[23] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_27.reg_decon_luma_y_th4);
		pp->deconnd____cmn[24] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th5);
		pp->deconnd____cmn[25] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th6);
		pp->deconnd____cmn[26] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_28.reg_decon_luma_y_th7);
		pp->deconnd____cmn[27]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_44.reg_motion_gain_x0);
		pp->deconnd____cmn[28]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_44.reg_motion_gain_x1);
		pp->deconnd____cmn[29]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_44.reg_motion_gain_x2);
		pp->deconnd____cmn[30]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_44.reg_motion_gain_x3);
		pp->deconnd____cmn[31]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_45.reg_motion_gain_y0);
		pp->deconnd____cmn[32]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_45.reg_motion_gain_y1);
		pp->deconnd____cmn[33]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_45.reg_motion_gain_y2);
		pp->deconnd____cmn[34]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_45.reg_motion_gain_y3);
		pp->deconnd____cmn[35]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x0);
		pp->deconnd____cmn[36]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x1);
		pp->deconnd____cmn[37]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x2);
		pp->deconnd____cmn[38]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_48.reg_lut_blur_sim_x3);
		pp->deconnd____cmn[39]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y0);
		pp->deconnd____cmn[40]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y1);
		pp->deconnd____cmn[41]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y2);
		pp->deconnd____cmn[42]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_49.reg_lut_blur_sim_y3);
		pp->deconnd____cmn[43] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x0);
		pp->deconnd____cmn[44] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x1);
		pp->deconnd____cmn[45] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_69.reg_var_lowapl_lut_x2);
		pp->deconnd____cmn[46] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_x3);
		pp->deconnd____cmn[47] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_y0);
		pp->deconnd____cmn[48] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_70.reg_var_lowapl_lut_y1);
		pp->deconnd____cmn[49] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_71.reg_var_lowapl_lut_y2);
		pp->deconnd____cmn[50] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_71.reg_var_lowapl_lut_y3);
		pp->deconnd____cmn[51] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_71.reg_var_lowapl_blend_x0);
		pp->deconnd____cmn[52] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x1);
		pp->deconnd____cmn[53] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x2);
		pp->deconnd____cmn[54] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_72.reg_var_lowapl_blend_x3);
		pp->deconnd____cmn[55] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y0);
		pp->deconnd____cmn[56] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y1);
		pp->deconnd____cmn[57] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y2);
		pp->deconnd____cmn[58] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_73.reg_var_lowapl_blend_y3);
		pp->deconnd____cmn[59] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_84.reg_1st_rd_luma_en);
		pp->deconnd____cmn[60] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_84.reg_2nd_rd_luma_en);
		pp->deconnd____cmn[61] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_87.reg_1st_rd_luma_x0);
		pp->deconnd____cmn[62] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_87.reg_1st_rd_luma_x1);
		pp->deconnd____cmn[63] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_88.reg_1st_rd_luma_x2);
		pp->deconnd____cmn[64] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_88.reg_1st_rd_luma_x3);
		pp->deconnd____cmn[65] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_89.reg_1st_rd_luma_x4);
		pp->deconnd____cmn[66] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_89.reg_1st_rd_luma_x5);
		pp->deconnd____cmn[67] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_90.reg_1st_rd_luma_x6);
		pp->deconnd____cmn[68] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_90.reg_1st_rd_luma_x7);
		pp->deconnd____cmn[69] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_91.reg_1st_rd_luma_y0);
		pp->deconnd____cmn[70] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_91.reg_1st_rd_luma_y1);
		pp->deconnd____cmn[71] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_92.reg_1st_rd_luma_y2);
		pp->deconnd____cmn[72] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_92.reg_1st_rd_luma_y3);
		pp->deconnd____cmn[73] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_93.reg_1st_rd_luma_y4);
		pp->deconnd____cmn[74] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_93.reg_1st_rd_luma_y5);
		pp->deconnd____cmn[75] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_94.reg_1st_rd_luma_y6);
		pp->deconnd____cmn[76] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_94.reg_1st_rd_luma_y7);

		/* face obj*/
		pp->deconnd___face[0] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x0);
		pp->deconnd___face[1] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x1);
		pp->deconnd___face[2] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x2);
		pp->deconnd___face[3] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_50.reg_lut_skin_yy_x3);
		pp->deconnd___face[4] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x0);
		pp->deconnd___face[5] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x1);
		pp->deconnd___face[6] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x2);
		pp->deconnd___face[7] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_51.reg_lut_skin_cb_x3);
		pp->deconnd___face[8] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x0);
		pp->deconnd___face[9] = PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x1);
		pp->deconnd___face[10]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x2);
		pp->deconnd___face[11]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_52.reg_lut_skin_cr_x3);
		pp->deconnd___face[12]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y0);
		pp->deconnd___face[13]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y1);
		pp->deconnd___face[14]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y2);
		pp->deconnd___face[15]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_53.reg_lut_skin_y3);
		pp->deconnd___face[16]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x0);
		pp->deconnd___face[17]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x1);
		pp->deconnd___face[18]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x2);
		pp->deconnd___face[19]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_54.reg_lut_face_x3);
		pp->deconnd___face[20]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y0);
		pp->deconnd___face[21]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y1);
		pp->deconnd___face[22]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y2);
		pp->deconnd___face[23]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_55.reg_lut_face_y3);
		pp->deconnd___face[24]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x3);
		pp->deconnd___face[25]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x2);
		pp->deconnd___face[26]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x1);
		pp->deconnd___face[27]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_97.reg_ref_mmd_gain_x0);
		pp->deconnd___face[28]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y3);
		pp->deconnd___face[29]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y2);
		pp->deconnd___face[30]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y1);
		pp->deconnd___face[31]= PE_CHPI_TBL0_O26F22_Rd(dnr.reg_decon_ctrl_98.reg_ref_mmd_gain_y0);


		#endif

		#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
		/* download dct sqm db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb */
		/* PE_CHPI_DNR_DCNT_SQM_O26F22_T			 sqm4;//15 */
		PE_CHPI_TBL0_O26F22_QRd(sqm4.ui32,pp->deconnd_ui_val);
		for (i=0; i<23; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(sqm4.data32[i],pp->deconnd__sqmui[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm4.cnt32);

		/* download dct user db */
		/* see PE_NRD_HW_O26_DownloadDnrDcntUserDb */
		/* PE_CHPI_DNR_DCNT_USER_O26F22_T			 usr2;//19 */
		PE_CHPI_TBL0_O26F22_QRd(usr2.ui32,pp->deconnd_ui_val);
		for (i=0; i<8; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(usr2.data32[i],pp->deconnd___buff[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(usr2.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QRd(usr2.cnt32,i);

		#endif

		pd32 = pp->deconnd_____ui;
		printk("set[%d] : deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pp->win_id, \
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
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
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
		pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
		pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
		pd[60], pd[61], pd[62], pd[63], pd[64], pd[65], pd[66], pd[67], pd[68], pd[69],\
		pd[70], pd[71], pd[72], pd[73], pd[74], pd[75], pd[76]);
		pd8 = pp->deconnd___face;
		printk("set[%d] : deconnd___face\n"
			"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"deconnd___face    [30]0x%02X,0x%02X\n",\
			pp->win_id, \
			pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
			pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
			pd8[20], pd8[21], pd8[22], pd8[23], pd8[24], pd8[25], pd8[26], pd8[27], pd8[28], pd8[29],\
			pd8[30], pd8[31]);	
		pd32 = pp->deconnd__sqmui;
		printk("[%d]deconnd__sqmui:%d, cnt:%d\n", pp->win_id, pp->deconnd_ui_val, i);
		printk( "\n"\
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
	}while(0);
	return ret;
}

int PE_CHPI_DNR_HW_O26F22_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_DNR_HW_O26F22_ENABLE
	UINT32 enable;
	PE_DNR_HW_PARAM_DATA_O26F22_T *p_dnr = &_g_pe_dnr_hw_param_data_o26f22;
	do{
 		if (!gPE_CHPI_DDR_O26)	break;
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_dnr->reg_user.data);
		CHECK_KNULL(p_dnr->reg_mask.data);
		enable = (*onoff >0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_O26F22_Wr(dnr.reg_decon_ctrl_56.reg_face_en,enable);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.reg_decon_ctrl_56.udata32);
		PE_CHPI_TBL0_O26F22_Wr(dnr.dc_bnr_ctrl_0.reg_obj_gain_en,enable);
		PE_CHPI_TBL0_O26F22_WrFL(dnr.dc_bnr_ctrl_0.udata32);
		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_DNR);
		/* set user */
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,reg_decon_ctrl_56.reg_face_en,enable);
		PE_CHPI_DNR_HW_O26F22_USER(p_dnr,dc_bnr_ctrl_0.reg_obj_gain_en,enable);
	}while(0);
	#endif
	return ret;
}

