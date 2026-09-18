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

/** @file pe_chpi_shp_hw_e60.c
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

#include "pe_hw_e60.h"
#include "pe_reg_e60.h"
#include "pe_fwi_e60.h"
#include "pe_inf_e60.h"
#include "pe_res_hw_param_e60.h"
#include "pe_cti_dnr_hw_param_e60.h"
#include "pe_chpi_shp_hw_e60f20.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_SHP_HW_E60F20_ENABLE

#define PE_CHPI_SHP_HW_E60F20_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_SHP_HW_E60F20_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_E60F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_CTI_HW_PARAM_DATA_E60F20_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
extern const PE_REG_PARAM_T shp_l_sd_default_e60[];
extern const PE_REG_PARAM_T shp_l_hd_default_e60[];
extern const PE_REG_PARAM_T shp_l_ud_default_e60[];
extern const PE_REG_PARAM_T cti_y_l_sd_default_e60[];
extern const PE_REG_PARAM_T cti_y_l_hd_default_e60[];
extern const PE_REG_PARAM_T cti_y_l_vr_360_default_e60[];
extern const PE_REG_PARAM_T cti_y_l_atv_default_e60[];
extern const UINT32 sqm_shp_vsd_cmn_init_e60[];
extern const UINT32 sqm_shp_vsd_dtl_init_e60[];

extern const PE_REG_PARAM_T shp_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T shp_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T shp_l_ud_default_e60f20[];
extern const PE_REG_PARAM_T cti_y_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T cti_y_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T cti_y_l_vr_360_default_e60f20[];
extern const PE_REG_PARAM_T cti_y_l_atv_default_e60f20[];
#endif

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
#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
static PE_RES_HW_PARAM_DATA_E60F20_T _g_pe_res_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_E60F20_T _g_pe_cti_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
static int PE_CHPI_SHP_HW_E60F20_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	PE_RES_HW_PARAM_DATA_E60F20_T *p_res = &_g_pe_res_hw_param_data_e60f20;
	PE_CTI_HW_PARAM_DATA_E60F20_T *p_cti = &_g_pe_cti_hw_param_data_e60f20;

	/* create dflt table */
	if (p_res->reg_dflt.addr == NULL)
	{
		p_res->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_res->reg_user.addr == NULL)
	{
		p_res->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_E60F20_T));
		memset((p_res->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_res->reg_mask.addr == NULL)
	{
		p_res->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_E60F20_T));
		memset((p_res->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_res->reg_data.addr == NULL)
	{
		p_res->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_E60F20_T));
		memset((p_res->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_res->reg_dflt.addr != NULL && p_res->reg_user.addr != NULL && \
		p_res->reg_mask.addr != NULL && p_res->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_res]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_res]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_res->reg_dflt.addr == NULL)? "x":"o", \
			(p_res->reg_user.addr == NULL)? "x":"o", \
			(p_res->reg_mask.addr == NULL)? "x":"o", \
			(p_res->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_cti->reg_dflt.addr == NULL)
	{
		p_cti->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_cti->reg_user.addr == NULL)
	{
		p_cti->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));
		memset((p_cti->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_cti->reg_mask.addr == NULL)
	{
		p_cti->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));
		memset((p_cti->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_cti->reg_data.addr == NULL)
	{
		p_cti->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));
		memset((p_cti->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_cti->reg_dflt.addr != NULL && p_cti->reg_user.addr != NULL && \
		p_cti->reg_mask.addr != NULL && p_cti->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_cti]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_cti]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_cti->reg_dflt.addr == NULL)? "x":"o", \
			(p_cti->reg_user.addr == NULL)? "x":"o", \
			(p_cti->reg_mask.addr == NULL)? "x":"o", \
			(p_cti->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}
	#endif

	return ret;
}

static PE_CHPI_SHP_HW_E60F20_RES_FMT PE_CHPI_SHP_HW_E60F20_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_SHP_HW_E60F20_RES_FMT res_fmt = PE_CHPI_SHP_E60F20_RES_NUM;
	if(disp_inf->act_fmt !=0)
	{
		res_fmt = PE_CHPI_SHP_E60F20_RES_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_DTV_HD;
				}
				else
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_HD;
				}
				else
				{
					res_fmt = PE_CHPI_SHP_E60F20_RES_UHD;
				}
				break;
		}
	}
	return res_fmt;
}

static PE_CHPI_SHP_HW_E60F20_CTI_FMT PE_CHPI_SHP_HW_E60F20_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_SHP_HW_E60F20_CTI_FMT cti_fmt = PE_CHPI_SHP_E60F20_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
		cti_fmt = PE_CHPI_SHP_E60F20_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					cti_fmt = PE_CHPI_SHP_E60F20_CTI_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					cti_fmt = PE_CHPI_SHP_E60F20_CTI_SD;
				}
				else
				{
					cti_fmt = PE_CHPI_SHP_E60F20_CTI_HD;
				}
				break;
		}
	}
	return cti_fmt;
}

static int PE_CHPI_SHP_HW_E60F20_SetResDefault(PE_CHPI_SHP_HW_E60F20_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_res_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_res_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_res_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_res_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_res_fmt)
	{
		case PE_CHPI_SHP_E60F20_RES_SD:
			p_dflt_param = shp_l_sd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_RES_HD:
			p_dflt_param = shp_l_hd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_RES_UHD:
			p_dflt_param = shp_l_ud_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_RES_DTV_SD:
			p_dflt_param = shp_l_sd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_RES_DTV_HD:
			p_dflt_param = shp_l_hd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_RES_SEEMLESS:
		default:
			p_dflt_param = shp_l_hd_default_e60f20;
			break;
	}

	size = sizeof(PE_RES_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_00.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_01.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_02.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_ctrl_00.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_00.udata32,p_data[4]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_01.udata32,p_data[5]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_02.udata32,p_data[6]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_03.udata32,p_data[7]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_04.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_05.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_06.udata32,p_data[10]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_07.udata32,p_data[11]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_08.udata32,p_data[12]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_09.udata32,p_data[13]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0a.udata32,p_data[14]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0b.udata32,p_data[15]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0c.udata32,p_data[16]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0d.udata32,p_data[17]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0e.udata32,p_data[18]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0f.udata32,p_data[19]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_10.udata32,p_data[20]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_11.udata32,p_data[21]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_12.udata32,p_data[22]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_13.udata32,p_data[23]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_14.udata32,p_data[24]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_15.udata32,p_data[25]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_16.udata32,p_data[26]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_00.udata32,p_data[27]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_01.udata32,p_data[28]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_02.udata32,p_data[29]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_03.udata32,p_data[30]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_04.udata32,p_data[31]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_05.udata32,p_data[32]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_06.udata32,p_data[33]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_07.udata32,p_data[34]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_08.udata32,p_data[35]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_09.udata32,p_data[36]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0a.udata32,p_data[37]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0b.udata32,p_data[38]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0c.udata32,p_data[39]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_apl_ctrl_00.udata32,p_data[40]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_00.udata32,p_data[41]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_01.udata32,p_data[42]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_02.udata32,p_data[43]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_03.udata32,p_data[44]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_04.udata32,p_data[45]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_00.udata32,p_data[46]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_01.udata32,p_data[47]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_02.udata32,p_data[48]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_03.udata32,p_data[49]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_04.udata32,p_data[50]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_05.udata32,p_data[51]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_06.udata32,p_data[52]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_07.udata32,p_data[53]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_00.udata32,p_data[54]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_01.udata32,p_data[55]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_02.udata32,p_data[56]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_03.udata32,p_data[57]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_04.udata32,p_data[58]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_05.udata32,p_data[59]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_06.udata32,p_data[60]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_07.udata32,p_data[61]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_08.udata32,p_data[62]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_09.udata32,p_data[63]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0a.udata32,p_data[64]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0b.udata32,p_data[65]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0c.udata32,p_data[66]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_00.udata32,p_data[67]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_01.udata32,p_data[68]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_02.udata32,p_data[69]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_03.udata32,p_data[70]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_sti_ctrl_00.udata32,p_data[71]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_00.udata32,p_data[72]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_01.udata32,p_data[73]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_02.udata32,p_data[74]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_tgen_ctrl_03_c0.udata32,p_data[75]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_tgen_ctrl_03_c1.udata32,p_data[76]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_04.udata32,p_data[77]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_05.udata32,p_data[78]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_06.udata32,p_data[79]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_07.udata32,p_data[80]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_08.udata32,p_data[81]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_09.udata32,p_data[82]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_0a.udata32,p_data[83]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_0b.udata32,p_data[84]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_snr_ctrl_00.udata32,p_data[85]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_00.udata32,p_data[86]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_01.udata32,p_data[87]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_02.udata32,p_data[88]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_03.udata32,p_data[89]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_04.udata32,p_data[90]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_05.udata32,p_data[91]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_06.udata32,p_data[92]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_07.udata32,p_data[93]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_08.udata32,p_data[94]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_09.udata32,p_data[95]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0a.udata32,p_data[96]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0b.udata32,p_data[97]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0c.udata32,p_data[98]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0d.udata32,p_data[99]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0e.udata32,p_data[100]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0f.udata32,p_data[101]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_10.udata32,p_data[102]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_11.udata32,p_data[103]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_12.udata32,p_data[104]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_13.udata32,p_data[105]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_14.udata32,p_data[106]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_15.udata32,p_data[107]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_16.udata32,p_data[108]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_17.udata32,p_data[109]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_18.udata32,p_data[110]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_19.udata32,p_data[111]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1a.udata32,p_data[112]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1b.udata32,p_data[113]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1c.udata32,p_data[114]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1d.udata32,p_data[115]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1e.udata32,p_data[116]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1f.udata32,p_data[117]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_00.udata32,p_data[118]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_01_c0.udata32,p_data[119]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_02_c0.udata32,p_data[120]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_03_c0.udata32,p_data[121]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_04_c0.udata32,p_data[122]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_05_c0.udata32,p_data[123]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_01_c1.udata32,p_data[124]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_02_c1.udata32,p_data[125]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_03_c1.udata32,p_data[126]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_04_c1.udata32,p_data[127]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_05_c1.udata32,p_data[128]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_06.udata32,p_data[129]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_07.udata32,p_data[130]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_08.udata32,p_data[131]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_09.udata32,p_data[132]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0a.udata32,p_data[133]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0b.udata32,p_data[134]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0c.udata32,p_data[135]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0d.udata32,p_data[136]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0e.udata32,p_data[137]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0f.udata32,p_data[138]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_10.udata32,p_data[139]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_00.udata32,p_data[140]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_01.udata32,p_data[141]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_02.udata32,p_data[142]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_03.udata32,p_data[143]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_04.udata32,p_data[144]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_05.udata32,p_data[145]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_06.udata32,p_data[146]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_07.udata32,p_data[147]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_08.udata32,p_data[148]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_psp_ctrl_00.udata32,p_data[149]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_00.udata32,p_data[150]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_01.udata32,p_data[151]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_02.udata32,p_data[152]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_00.udata32,p_data[153]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_01.udata32,p_data[154]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_02.udata32,p_data[155]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_03.udata32,p_data[156]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_04.udata32,p_data[157]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_05.udata32,p_data[158]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_06.udata32,p_data[159]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_07.udata32,p_data[160]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_08.udata32,p_data[161]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_09.udata32,p_data[162]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0a.udata32,p_data[163]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0b.udata32,p_data[164]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0c.udata32,p_data[165]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_00.udata32,p_data[166]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_01.udata32,p_data[167]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_02.udata32,p_data[168]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_03.udata32,p_data[169]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_04.udata32,p_data[170]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_05.udata32,p_data[171]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_06.udata32,p_data[172]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_07.udata32,p_data[173]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_08.udata32,p_data[174]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_09.udata32,p_data[175]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0a.udata32,p_data[176]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0b.udata32,p_data[177]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0c.udata32,p_data[178]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0d.udata32,p_data[179]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0e.udata32,p_data[180]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0f.udata32,p_data[181]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_10.udata32,p_data[182]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_11.udata32,p_data[183]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_12.udata32,p_data[184]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_13.udata32,p_data[185]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_14.udata32,p_data[186]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_15.udata32,p_data[187]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_16.udata32,p_data[188]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_17.udata32,p_data[189]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_18.udata32,p_data[190]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_19.udata32,p_data[191]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1a.udata32,p_data[192]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1b.udata32,p_data[193]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1c.udata32,p_data[194]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1d.udata32,p_data[195]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1e.udata32,p_data[196]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1f.udata32,p_data[197]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_20.udata32,p_data[198]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_db_ctrl_00.udata32,p_data[199]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_db_ctrl_01.udata32,p_data[200]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_00.udata32,p_data[201]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_01.udata32,p_data[202]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_02.udata32,p_data[203]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_03.udata32,p_data[204]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_04.udata32,p_data[205]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_05.udata32,p_data[206]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_06.udata32,p_data[207]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_07.udata32,p_data[208]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_08.udata32,p_data[209]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_09.udata32,p_data[210]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0a.udata32,p_data[211]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0b.udata32,p_data[212]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0c.udata32,p_data[213]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0d.udata32,p_data[214]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0e.udata32,p_data[215]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_00.udata32,p_data[216]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_01.udata32,p_data[217]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_02.udata32,p_data[218]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_03.udata32,p_data[219]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_00.udata32,p_data[220]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_01.udata32,p_data[221]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_02.udata32,p_data[222]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_03.udata32,p_data[223]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_04.udata32,p_data[224]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_05.udata32,p_data[225]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_06.udata32,p_data[226]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_07.udata32,p_data[227]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_08.udata32,p_data[228]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_09.udata32,p_data[229]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0a.udata32,p_data[230]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0b.udata32,p_data[231]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0c.udata32,p_data[232]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_00.udata32,p_data[233]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_01.udata32,p_data[234]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_02.udata32,p_data[235]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_03.udata32,p_data[236]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_04.udata32,p_data[237]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_00.udata32,p_data[238]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_01.udata32,p_data[239]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_02.udata32,p_data[240]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_03.udata32,p_data[241]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_04.udata32,p_data[242]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_05.udata32,p_data[243]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_06.udata32,p_data[244]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_07.udata32,p_data[245]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_08.udata32,p_data[246]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_09.udata32,p_data[247]);
	PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_0a.udata32,p_data[248]);

	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RES);
	#endif

	return ret;
}

static int PE_CHPI_SHP_HW_E60F20_SetCtiDefault(PE_CHPI_SHP_HW_E60F20_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_cti_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_cti_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_cti_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_cti_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_SHP_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_cti_fmt)
	{
		case PE_CHPI_SHP_E60F20_CTI_SD:
			p_dflt_param = cti_y_l_sd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_CTI_HD:
			p_dflt_param = cti_y_l_hd_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_CTI_VR_360:
			p_dflt_param = cti_y_l_vr_360_default_e60f20;
			break;
		case PE_CHPI_SHP_E60F20_CTI_ATV:
		default:
			p_dflt_param = cti_y_l_atv_default_e60f20;
			break;
	}

	size = sizeof(PE_CTI_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(cti.cti_ctrl_0.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(cti.cti_ctrl_1.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(cti.reg_cti_ctrl_2.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(cti.reg_cti_ctrl_3.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_00.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_01.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_02.udata32,p_data[10]);

	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_CTI);
	#endif

	return ret;
}

int PE_CHPI_SHP_HW_E60F20_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_E60_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_SHP_HW_E60F20_RES_FMT pre0_res_fmt = PE_CHPI_SHP_E60F20_RES_NUM;
	static PE_CHPI_SHP_HW_E60F20_CTI_FMT pre0_cti_fmt = PE_CHPI_SHP_E60F20_CTI_NUM;
	PE_CHPI_SHP_HW_E60F20_RES_FMT cur0_res_fmt;
	PE_CHPI_SHP_HW_E60F20_CTI_FMT cur0_cti_fmt;
	do{
		ret = PE_INF_E60_GetCurInfSettings(&inf_set);
		PE_CHPI_SHP_HW_E60F20_CHECK_CODE(ret,break,"PE_INF_E60_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_res_fmt = PE_CHPI_SHP_HW_E60F20_ConvDispInfoToResFmt(disp0_inf);
		if(pre0_res_fmt!=cur0_res_fmt)
		{
			ret = PE_CHPI_SHP_HW_E60F20_SetResDefault(cur0_res_fmt);
			PE_CHPI_SHP_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_SHP_HW_E60F20_SetResDefault() error\n");
			pre0_res_fmt=cur0_res_fmt;
		}
		cur0_cti_fmt = PE_CHPI_SHP_HW_E60F20_ConvDispInfoToCtiFmt(disp0_inf);
		if(pre0_cti_fmt!=cur0_cti_fmt)
		{
			ret = PE_CHPI_SHP_HW_E60F20_SetCtiDefault(cur0_cti_fmt);
			PE_CHPI_SHP_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_SHP_HW_E60F20_SetCtiDefault() error\n");
			pre0_cti_fmt=cur0_cti_fmt;
		}
	}while(0);
	return ret;
}

int PE_CHPI_SHP_HW_E60F20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 i;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_SHP_HW_E60F20_CreateDataTable();
		if (ret)	break;
		
		if (pstParams->resume_mode == 1)	break;//if qsm,skip

		/* addr */
		PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_00.uaddr32,0xF017B100);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_01.uaddr32,0xF017B104);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_esf_ctrl_02.uaddr32,0xF017B108);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_ctrl_00.uaddr32,0xF017B150);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_00.uaddr32,0xF017B160);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_01.uaddr32,0xF017B164);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_02.uaddr32,0xF017B168);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_03.uaddr32,0xF017B16C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_04.uaddr32,0xF017B170);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_05.uaddr32,0xF017B174);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_06.uaddr32,0xF017B178);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_07.uaddr32,0xF017B17C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_08.uaddr32,0xF017B180);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_09.uaddr32,0xF017B184);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0a.uaddr32,0xF017B188);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0b.uaddr32,0xF017B18C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0c.uaddr32,0xF017B190);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0d.uaddr32,0xF017B194);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0e.uaddr32,0xF017B198);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_0f.uaddr32,0xF017B19C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_10.uaddr32,0xF017B1A0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_11.uaddr32,0xF017B1A4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_12.uaddr32,0xF017B1A8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_13.uaddr32,0xF017B1AC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_14.uaddr32,0xF017B1B0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_15.uaddr32,0xF017B1B4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_ctrl_16.uaddr32,0xF017B1B8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_00.uaddr32,0xF017B1C0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_01.uaddr32,0xF017B1C4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_02.uaddr32,0xF017B1C8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_03.uaddr32,0xF017B1CC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_04.uaddr32,0xF017B1D0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_05.uaddr32,0xF017B1D4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_06.uaddr32,0xF017B1D8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_07.uaddr32,0xF017B1DC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_08.uaddr32,0xF017B1E0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_09.uaddr32,0xF017B1E4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0a.uaddr32,0xF017B1E8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0b.uaddr32,0xF017B1EC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_mp_ctrl_0c.uaddr32,0xF017B1F0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_apl_ctrl_00.uaddr32,0xF017B1F4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_00.uaddr32,0xF017B200);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_01.uaddr32,0xF017B204);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_02.uaddr32,0xF017B208);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_03.uaddr32,0xF017B20C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_lc_ctrl_04.uaddr32,0xF017B210);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_00.uaddr32,0xF017B220);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_01.uaddr32,0xF017B224);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_02.uaddr32,0xF017B228);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_03.uaddr32,0xF017B22C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_04.uaddr32,0xF017B230);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_05.uaddr32,0xF017B234);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_06.uaddr32,0xF017B238);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_der_ctrl_07.uaddr32,0xF017B23C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_00.uaddr32,0xF017B240);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_01.uaddr32,0xF017B244);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_02.uaddr32,0xF017B248);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_03.uaddr32,0xF017B24C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_04.uaddr32,0xF017B250);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_05.uaddr32,0xF017B254);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_06.uaddr32,0xF017B258);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_07.uaddr32,0xF017B25C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_08.uaddr32,0xF017B260);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_09.uaddr32,0xF017B264);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0a.uaddr32,0xF017B268);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0b.uaddr32,0xF017B26C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sp_ctrl_0c.uaddr32,0xF017B270);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_00.uaddr32,0xF017B280);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_01.uaddr32,0xF017B284);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_02.uaddr32,0xF017B288);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_pti_ctrl_03.uaddr32,0xF017B28C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_sti_ctrl_00.uaddr32,0xF017B290);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_00.uaddr32,0xF017B2A0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_01.uaddr32,0xF017B2A4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_02.uaddr32,0xF017B2A8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_tgen_ctrl_03_c0.uaddr32,0xF017B2AC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_tgen_ctrl_03_c1.uaddr32,0xF017B2B0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_04.uaddr32,0xF017B2BC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_05.uaddr32,0xF017B2C0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_06.uaddr32,0xF017B2C4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_07.uaddr32,0xF017B2C8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_08.uaddr32,0xF017B2CC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_09.uaddr32,0xF017B2D0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_0a.uaddr32,0xF017B2D4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_tgen_ctrl_0b.uaddr32,0xF017B2D8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_snr_ctrl_00.uaddr32,0xF017B2E0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_00.uaddr32,0xF017B2F0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_01.uaddr32,0xF017B2F4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_02.uaddr32,0xF017B2F8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_03.uaddr32,0xF017B2FC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_04.uaddr32,0xF017B300);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_05.uaddr32,0xF017B304);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_06.uaddr32,0xF017B308);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_07.uaddr32,0xF017B30C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_08.uaddr32,0xF017B310);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_09.uaddr32,0xF017B314);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0a.uaddr32,0xF017B318);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0b.uaddr32,0xF017B31C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0c.uaddr32,0xF017B320);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0d.uaddr32,0xF017B324);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0e.uaddr32,0xF017B328);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_0f.uaddr32,0xF017B32C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_10.uaddr32,0xF017B330);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_11.uaddr32,0xF017B334);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_12.uaddr32,0xF017B338);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_13.uaddr32,0xF017B33C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_14.uaddr32,0xF017B340);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_15.uaddr32,0xF017B344);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_16.uaddr32,0xF017B348);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_17.uaddr32,0xF017B34C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_18.uaddr32,0xF017B350);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_19.uaddr32,0xF017B354);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1a.uaddr32,0xF017B358);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1b.uaddr32,0xF017B35C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1c.uaddr32,0xF017B360);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1d.uaddr32,0xF017B364);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1e.uaddr32,0xF017B368);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dctp_ctrl_1f.uaddr32,0xF017B36C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_00.uaddr32,0xF017B370);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_01_c0.uaddr32,0xF017B374);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_02_c0.uaddr32,0xF017B378);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_03_c0.uaddr32,0xF017B37C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_04_c0.uaddr32,0xF017B380);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_05_c0.uaddr32,0xF017B384);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_01_c1.uaddr32,0xF017B388);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_02_c1.uaddr32,0xF017B38C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_03_c1.uaddr32,0xF017B390);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_04_c1.uaddr32,0xF017B394);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_core0_nntg_ctrl_05_c1.uaddr32,0xF017B398);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_06.uaddr32,0xF017B3C4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_07.uaddr32,0xF017B3C8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_08.uaddr32,0xF017B3CC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_09.uaddr32,0xF017B3D0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0a.uaddr32,0xF017B3D4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0b.uaddr32,0xF017B3D8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0c.uaddr32,0xF017B3DC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0d.uaddr32,0xF017B3E0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0e.uaddr32,0xF017B3E4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_0f.uaddr32,0xF017B3E8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_nntg_ctrl_10.uaddr32,0xF017B3EC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_00.uaddr32,0xF017B3F0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_01.uaddr32,0xF017B3F4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_02.uaddr32,0xF017B3F8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_03.uaddr32,0xF017B3FC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_04.uaddr32,0xF017B400);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_05.uaddr32,0xF017B404);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_06.uaddr32,0xF017B408);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_07.uaddr32,0xF017B40C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dp_sum_ctrl_08.uaddr32,0xF017B410);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_psp_ctrl_00.uaddr32,0xF017B420);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_00.uaddr32,0xF017B460);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_01.uaddr32,0xF017B464);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_region_text_02.uaddr32,0xF017B468);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_00.uaddr32,0xF017B46C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_01.uaddr32,0xF017B470);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_02.uaddr32,0xF017B474);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_03.uaddr32,0xF017B478);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_04.uaddr32,0xF017B47C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_05.uaddr32,0xF017B480);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_06.uaddr32,0xF017B484);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_07.uaddr32,0xF017B488);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_08.uaddr32,0xF017B48C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_09.uaddr32,0xF017B490);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0a.uaddr32,0xF017B494);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0b.uaddr32,0xF017B498);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_fd_tmap_temp_0c.uaddr32,0xF017B49C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_00.uaddr32,0xF017B4A0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_01.uaddr32,0xF017B4A4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_02.uaddr32,0xF017B4A8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_03.uaddr32,0xF017B4AC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_04.uaddr32,0xF017B4B0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_05.uaddr32,0xF017B4B4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_06.uaddr32,0xF017B4B8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_07.uaddr32,0xF017B4BC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_08.uaddr32,0xF017B4C0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_09.uaddr32,0xF017B4C4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0a.uaddr32,0xF017B4C8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0b.uaddr32,0xF017B4CC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0c.uaddr32,0xF017B4D0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0d.uaddr32,0xF017B4D4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0e.uaddr32,0xF017B4D8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_0f.uaddr32,0xF017B4DC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_10.uaddr32,0xF017B4E0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_11.uaddr32,0xF017B4E4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_12.uaddr32,0xF017B4E8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_13.uaddr32,0xF017B4EC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_14.uaddr32,0xF017B4F0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_15.uaddr32,0xF017B4F4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_16.uaddr32,0xF017B4F8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_17.uaddr32,0xF017B4FC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_18.uaddr32,0xF017B500);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_19.uaddr32,0xF017B504);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1a.uaddr32,0xF017B508);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1b.uaddr32,0xF017B50C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1c.uaddr32,0xF017B510);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1d.uaddr32,0xF017B514);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1e.uaddr32,0xF017B518);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_1f.uaddr32,0xF017B51C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_dj_ctrl_20.uaddr32,0xF017B520);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_db_ctrl_00.uaddr32,0xF017B524);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_db_ctrl_01.uaddr32,0xF017B528);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_00.uaddr32,0xF017B560);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_01.uaddr32,0xF017B564);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_02.uaddr32,0xF017B568);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_03.uaddr32,0xF017B56C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_04.uaddr32,0xF017B570);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_05.uaddr32,0xF017B574);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_06.uaddr32,0xF017B578);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_07.uaddr32,0xF017B57C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_08.uaddr32,0xF017B580);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_09.uaddr32,0xF017B584);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0a.uaddr32,0xF017B588);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0b.uaddr32,0xF017B58C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0c.uaddr32,0xF017B590);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0d.uaddr32,0xF017B594);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_chroma_ctrl_0e.uaddr32,0xF017B598);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_00.uaddr32,0xF017B5B0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_01.uaddr32,0xF017B5B4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_02.uaddr32,0xF017B5B8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_frc_flick_ctrl_03.uaddr32,0xF017B5BC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_00.uaddr32,0xF017B620);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_01.uaddr32,0xF017B624);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_02.uaddr32,0xF017B628);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_03.uaddr32,0xF017B62C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_04.uaddr32,0xF017B630);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_05.uaddr32,0xF017B634);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_06.uaddr32,0xF017B638);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_07.uaddr32,0xF017B63C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_08.uaddr32,0xF017B640);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_09.uaddr32,0xF017B644);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0a.uaddr32,0xF017B648);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0b.uaddr32,0xF017B64C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_gain_ctrl_0c.uaddr32,0xF017B650);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_00.uaddr32,0xF017B660);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_01.uaddr32,0xF017B664);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_02.uaddr32,0xF017B668);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_03.uaddr32,0xF017B66C);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_motion_prot_ctrl_04.uaddr32,0xF017B670);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_00.uaddr32,0xF017B6C0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_01.uaddr32,0xF017B6C4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_02.uaddr32,0xF017B6C8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_03.uaddr32,0xF017B6CC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_04.uaddr32,0xF017B6D0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_05.uaddr32,0xF017B6D4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_06.uaddr32,0xF017B6D8);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_07.uaddr32,0xF017B6DC);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_08.uaddr32,0xF017B6E0);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_09.uaddr32,0xF017B6E4);
		PE_CHPI_TBL0_E60F20_QWr(res.shp_obj_ctrl_0a.uaddr32,0xF017B6E8);
		PE_CHPI_TBL0_E60F20_QWr(res.sr_merge_blend_00.uaddr32,0xF0394E50);
		PE_CHPI_TBL0_E60F20_QWr(cti.cti_ctrl_0.uaddr32,0xF022158C);
		PE_CHPI_TBL0_E60F20_QWr(cti.cti_ctrl_1.uaddr32,0xF0221590);
		PE_CHPI_TBL0_E60F20_QWr(cti.reg_cti_ctrl_2.uaddr32,0xF02217A0);
		PE_CHPI_TBL0_E60F20_QWr(cti.reg_cti_ctrl_3.uaddr32,0xF02217A4);
		PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_00.uaddr32,0xF017B5A0);
		PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_01.uaddr32,0xF017B5A4);
		PE_CHPI_TBL0_E60F20_QWr(cti.shp_cti_ctrl_02.uaddr32,0xF017B5A8);

		/* init */
		PE_CHPI_SHP_HW_E60F20_SetResDefault(PE_CHPI_SHP_E60F20_RES_HD);
		PE_CHPI_SHP_HW_E60F20_SetCtiDefault(PE_CHPI_SHP_E60F20_CTI_HD);
		PE_CHPI_TBL0_E60F20_QWr(res.sr_merge_blend_00.udata32,0x01000021);//init data 0x01000021 

		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmCmnInitDb */
		/* PE_CHPI_SHP_UI_SQM_E60F20_T              sqm0;//11 */
		PE_CHPI_TBL0_E60F20_QWr(sqm0.ui32,0);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_E60F20_QWr(sqm0.data32[i],sqm_shp_vsd_cmn_init_e60[i]);
		}
		PE_CHPI_TBL0_E60F20_QWr(sqm0.cnt32,0);

		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmDetailInitDb */
		/* PE_CHPI_SHP_CMN_SQM_E60F20_T             sqm1;//12 */
		PE_CHPI_TBL0_E60F20_QWr(sqm1.ui32,0);
		for (i=0; i<51; i++)
		{
			PE_CHPI_TBL0_E60F20_QWr(sqm1.data32[i],sqm_shp_vsd_dtl_init_e60[i]);
		}
		PE_CHPI_TBL0_E60F20_QWr(sqm1.cnt32,0);

		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_SQM0);
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_SQM1);

		PE_PRINT_NOTI("[TBL][SHP]done(resume:%d)\n",pstParams->resume_mode);
		PE_INF_HW_E60_BACKUP_CHPI1("[TBL][SHP]done(resume:%d)",pstParams->resume_mode);
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_SHP_HW_E60F20_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 i;
	LX_PE_SHP_ALL_CMN_T *pp;
	PE_RES_HW_PARAM_DATA_E60F20_T *p_res = &_g_pe_res_hw_param_data_e60f20;
	PE_CTI_HW_PARAM_DATA_E60F20_T *p_cti = &_g_pe_cti_hw_param_data_e60f20;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_res->reg_user.data);
		CHECK_KNULL(p_res->reg_mask.data);
		CHECK_KNULL(p_cti->reg_user.data);
		CHECK_KNULL(p_cti->reg_mask.data);
		pp=(LX_PE_SHP_ALL_CMN_T *)pstParams;

		/* set tbl */
		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1d.reg_dctp_gain,GET_BITS(pp->shp_ui_main_vsd[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_00.reg_tgen_master_gain,GET_BITS(pp->shp_ui_main_vsd[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_1e.reg_dj_soft_g1_mul,GET_BITS(pp->shp_ui_main_vsd[2],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_1f.reg_dj_soft_g2_mul,GET_BITS(pp->shp_ui_main_vsd[3],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_0e.reg_nntg_denoise_gain,GET_BITS(pp->shp_ui_main_vsd[4],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_der_ctrl_00.reg_derh_csft_gain,GET_BITS(pp->shp_ui_main_vsd[5],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_01.reg_mp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[8],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_01.reg_sp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[9],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_01.reg_mp_im_gain_v,GET_BITS(pp->shp_ui_main_vsd[10],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sti_ctrl_00.reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_00.reg_cti_gain,GET_BITS(pp->shp_ui_main_vsd[12],0,8));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_y_gain,GET_BITS(pp->shp_ui_main_vsd[13],0,4));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_c_gain,GET_BITS(pp->shp_ui_main_vsd[14],0,4));
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x0,GET_BITS(pp->shp_face_obj_vsd[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y0,GET_BITS(pp->shp_face_obj_vsd[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x1,GET_BITS(pp->shp_face_obj_vsd[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y1,GET_BITS(pp->shp_face_obj_vsd[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x2,GET_BITS(pp->shp_face_obj_vsd[4],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y2,GET_BITS(pp->shp_face_obj_vsd[5],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x3,GET_BITS(pp->shp_face_obj_vsd[6],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y3,GET_BITS(pp->shp_face_obj_vsd[7],0,8));
		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_der_ctrl_01.reg_derh_edge_y_filter_en,GET_BITS(pp->shp_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_der_ctrl_01.reg_derh_bflt_tap_size,GET_BITS(pp->shp_cmn_vsd[1],0,3));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_00.reg_mp_shp_en,GET_BITS(pp->shp_cmn_vsd[2],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_00.reg_sp_shp_en,GET_BITS(pp->shp_cmn_vsd[3],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_01.reg_mp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[4],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_01.reg_mp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[5],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_01.reg_sp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[6],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_01.reg_sp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[7],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_esf_ctrl_00.reg_esf_en,GET_BITS(pp->shp_cmn_vsd[8],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_esf_ctrl_01.reg_esf_min_ratio,GET_BITS(pp->shp_cmn_vsd[9],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_esf_ctrl_01.reg_esf_base,GET_BITS(pp->shp_cmn_vsd[10],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_esf_ctrl_01.reg_esf_max_clip,GET_BITS(pp->shp_cmn_vsd[11],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_00.reg_dctp_en,GET_BITS(pp->shp_cmn_vsd[12],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1e.reg_dctp_coring_en,GET_BITS(pp->shp_cmn_vsd[13],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1e.reg_dctp_coring_mode,GET_BITS(pp->shp_cmn_vsd[14],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_00.reg_tgen_on_off,GET_BITS(pp->shp_cmn_vsd[15],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0a.reg_tgen_coring_en,GET_BITS(pp->shp_cmn_vsd[16],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0a.reg_tgen_coring_mode,GET_BITS(pp->shp_cmn_vsd[17],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_00.reg_nntg_en,GET_BITS(pp->shp_cmn_vsd[18],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_0f.reg_nntg_coring_en,GET_BITS(pp->shp_cmn_vsd[19],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_0f.reg_nntg_coring_mode,GET_BITS(pp->shp_cmn_vsd[20],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en,GET_BITS(pp->shp_cmn_vsd[21],0,1));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_00.reg_cti_en,GET_BITS(pp->shp_cmn_vsd[22],0,1));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_en,GET_BITS(pp->shp_cmn_vsd[23],0,1));
		PE_CHPI_TBL0_E60F20_Wr(cti.shp_cti_ctrl_00.reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_00.reg_dj_edf_en,GET_BITS(pp->shp_djg_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_00.reg_dj_edge_adaptive_en,GET_BITS(pp->shp_djg_vsd[1],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_00.reg_dj_soft_en,GET_BITS(pp->shp_djg_vsd[2],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_03.reg_dj_edge_min,GET_BITS(pp->shp_djg_vsd[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_03.reg_dj_edge_mul,GET_BITS(pp->shp_djg_vsd[4],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_00.reg_dj_center_blur_mode,GET_BITS(pp->shp_djg_vsd[5],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_00.reg_dj_n_avg_mode,GET_BITS(pp->shp_djg_vsd[6],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dj_ctrl_01.reg_dj_n_avg_gain,GET_BITS(pp->shp_djg_vsd[7],0,8));

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x0,GET_BITS(pp->shp_map_cmn_vsd[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x1,GET_BITS(pp->shp_map_cmn_vsd[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y0,GET_BITS(pp->shp_map_cmn_vsd[4],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y1,GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_11.reg_fd_soft_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[6],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_11.reg_fd_soft_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y3,GET_BITS(pp->shp_map_cmn_vsd[8],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y2,GET_BITS(pp->shp_map_cmn_vsd[9],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y1,GET_BITS(pp->shp_map_cmn_vsd[10],0,6));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y0,GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_05.reg_mp_gb_en,GET_BITS(pp->shp_balance_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_05.reg_mp_gb_mode,GET_BITS(pp->shp_balance_vsd[1],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_05.reg_mp_gb_y1,GET_BITS(pp->shp_balance_vsd[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_06.reg_mp_gb_y2,GET_BITS(pp->shp_balance_vsd[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_06.reg_mp_gb_y3,GET_BITS(pp->shp_balance_vsd[4],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_05.reg_sp_gb_en,GET_BITS(pp->shp_balance_vsd[5],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_05.reg_sp_gb_mode,GET_BITS(pp->shp_balance_vsd[6],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_05.reg_sp_gb_y1,GET_BITS(pp->shp_balance_vsd[7],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_06.reg_sp_gb_y2,GET_BITS(pp->shp_balance_vsd[8],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_06.reg_sp_gb_y3,GET_BITS(pp->shp_balance_vsd[9],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_00.reg_lc_shp_en,GET_BITS(pp->shp_balance_vsd[10],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_00.reg_lc_gb_en,GET_BITS(pp->shp_balance_vsd[11],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_01.reg_lc_gb_y1,GET_BITS(pp->shp_balance_vsd[12],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_01.reg_lc_gb_y2,GET_BITS(pp->shp_balance_vsd[13],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_02.reg_lc_gb_y3,GET_BITS(pp->shp_balance_vsd[14],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_00.reg_lc_center_target,GET_BITS(pp->shp_balance_vsd[15],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_00.reg_lc_center_gain,GET_BITS(pp->shp_balance_vsd[16],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_00.reg_lc_local_gain,GET_BITS(pp->shp_balance_vsd[17],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y0,GET_BITS(pp->shp_balance_vsd[18],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y1,GET_BITS(pp->shp_balance_vsd[19],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y2,GET_BITS(pp->shp_balance_vsd[20],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_09.reg_mp_lum2_y0,GET_BITS(pp->shp_balance_vsd[21],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0a.reg_mp_lum2_y1,GET_BITS(pp->shp_balance_vsd[22],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0a.reg_mp_lum2_y2,GET_BITS(pp->shp_balance_vsd[23],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y0,GET_BITS(pp->shp_balance_vsd[24],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y1,GET_BITS(pp->shp_balance_vsd[25],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y2,GET_BITS(pp->shp_balance_vsd[26],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_09.reg_sp_lum2_y0,GET_BITS(pp->shp_balance_vsd[27],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0a.reg_sp_lum2_y1,GET_BITS(pp->shp_balance_vsd[28],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0a.reg_sp_lum2_y2,GET_BITS(pp->shp_balance_vsd[29],0,8));
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_00.reg_ptiv_enable,GET_BITS(pp->shp_ti_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_00.reg_ptiv_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[1],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_00.reg_ptiv_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[2],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_00.reg_ptiv_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_01.reg_ptih_enable,GET_BITS(pp->shp_ti_cmn_vsd[4],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_01.reg_ptih_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[5],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_01.reg_ptih_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[6],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_01.reg_ptih_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sti_ctrl_00.reg_sti_enable,GET_BITS(pp->shp_ti_cmn_vsd[8],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sti_ctrl_00.reg_sti_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[9],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sti_ctrl_00.reg_sti_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[10],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sti_ctrl_00.reg_sti_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_snr_ctrl_00.reg_snr_blur_en,GET_BITS(pp->shp_ti_cmn_vsd[12],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_snr_ctrl_00.reg_snr_blur_sel,GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_chroma_ctrl_00.reg_color_region_en,GET_BITS(pp->shp_chroma_vsd[0],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_chroma_ctrl_00.reg_chr_protection_en,GET_BITS(pp->shp_chroma_vsd[1],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_chroma_ctrl_00.reg_chr_compensation_en,GET_BITS(pp->shp_chroma_vsd[2],0,1));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_chroma_ctrl_0d.reg_chr_gain_r0_gain,GET_BITS(pp->shp_chroma_vsd[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_chroma_ctrl_0d.reg_chr_gain_r1_gain,GET_BITS(pp->shp_chroma_vsd[4],0,8));
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[0],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[1],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[14],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[15],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[2],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[3],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[16],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[17],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[4],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[5],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[18],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[19],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[6],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[7],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[20],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[21],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[8],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[9],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[22],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[23],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[10],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[11],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[24],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[25],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[12],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[13],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[26],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[27],0,7));
		PE_CHPI_TBL0_E60F20_Wr(res.sr_merge_blend_00.reg_blend_amp_weight,GET_BITS(pp->shp_dnn_sr_vsd[0],0,12));

		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dctp_ctrl_1d.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_1e.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_1f.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_nntg_ctrl_0e.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_der_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_der_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(cti.shp_cti_ctrl_02.udata32);
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_obj_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_obj_ctrl_0a.udata32);
		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_der_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_esf_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_esf_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dctp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dctp_ctrl_1e.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_tgen_ctrl_0a.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_nntg_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_nntg_ctrl_0f.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_motion_prot_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(cti.shp_cti_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(cti.shp_cti_ctrl_00.udata32);
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dj_ctrl_01.udata32);

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_fd_ctrl_0b.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_fd_ctrl_0d.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_fd_ctrl_11.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_fd_ctrl_14.udata32);

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_lc_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_lc_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_0a.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_0a.udata32);
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_pti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_pti_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_snr_ctrl_00.udata32);
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_chroma_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_chroma_ctrl_0d.udata32);
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_mp_ctrl_0c.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_sp_ctrl_0c.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_pti_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_lc_ctrl_04.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_dctp_ctrl_1f.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_tgen_ctrl_0b.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_nntg_ctrl_10.udata32);
		/*shp_dnn_sr_vsd - there is no default table*/
		PE_CHPI_TBL0_E60F20_WrFL(res.sr_merge_blend_00.udata32);

		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmCmnUserDb */
		/* PE_CHPI_SHP_UI_SQM_E60F20_T              sqm0;//11 */
		PE_CHPI_TBL0_E60F20_QWr(sqm0.ui32,pp->shp_val);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_E60F20_QWr(sqm0.data32[i],pp->shp_ui_sqm_vsd[i]);
		}
		i = PE_CHPI_TBL0_E60F20_Rd(sqm0.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_E60F20_QWr(sqm0.cnt32,i);

		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmDetailUserDb */
		/* PE_CHPI_SHP_CMN_SQM_E60F20_T             sqm1;//12 */
		PE_CHPI_TBL0_E60F20_QWr(sqm1.ui32,pp->shp_val);
		for (i=0; i<51; i++)
		{
			PE_CHPI_TBL0_E60F20_QWr(sqm1.data32[i],pp->shp_sqm_cmn_vsd[i]);
		}
		i = PE_CHPI_TBL0_E60F20_Rd(sqm1.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_E60F20_QWr(sqm1.cnt32,i);

		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RES);
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_CTI);
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_SQM0);
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_SQM1);

		/* set user */
		/*shp_ui_main_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1d.reg_dctp_gain,GET_BITS(pp->shp_ui_main_vsd[0],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_00.reg_tgen_master_gain,GET_BITS(pp->shp_ui_main_vsd[1],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_1e.reg_dj_soft_g1_mul,GET_BITS(pp->shp_ui_main_vsd[2],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_1f.reg_dj_soft_g2_mul,GET_BITS(pp->shp_ui_main_vsd[3],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_0e.reg_nntg_denoise_gain,GET_BITS(pp->shp_ui_main_vsd[4],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_der_ctrl_00.reg_derh_csft_gain,GET_BITS(pp->shp_ui_main_vsd[5],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_der_ctrl_02.reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_der_ctrl_02.reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_01.reg_mp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[8],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_01.reg_sp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[9],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_01.reg_mp_im_gain_v,GET_BITS(pp->shp_ui_main_vsd[10],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sti_ctrl_00.reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_00.reg_cti_gain,GET_BITS(pp->shp_ui_main_vsd[12],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_y_gain,GET_BITS(pp->shp_ui_main_vsd[13],0,4));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_c_gain,GET_BITS(pp->shp_ui_main_vsd[14],0,4));
		/*shp_face_obj_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_lut_x0,GET_BITS(pp->shp_face_obj_vsd[0],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_lut_y0,GET_BITS(pp->shp_face_obj_vsd[1],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_lut_x1,GET_BITS(pp->shp_face_obj_vsd[2],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_lut_y1,GET_BITS(pp->shp_face_obj_vsd[3],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_lut_x2,GET_BITS(pp->shp_face_obj_vsd[4],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_lut_y2,GET_BITS(pp->shp_face_obj_vsd[5],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_lut_x3,GET_BITS(pp->shp_face_obj_vsd[6],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_lut_y3,GET_BITS(pp->shp_face_obj_vsd[7],0,8));
		/*shp_cmn_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_der_ctrl_01.reg_derh_edge_y_filter_en,GET_BITS(pp->shp_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_der_ctrl_01.reg_derh_bflt_tap_size,GET_BITS(pp->shp_cmn_vsd[1],0,3));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_00.reg_mp_shp_en,GET_BITS(pp->shp_cmn_vsd[2],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_00.reg_sp_shp_en,GET_BITS(pp->shp_cmn_vsd[3],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_01.reg_mp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[4],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_01.reg_mp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[5],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_01.reg_sp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[6],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_01.reg_sp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[7],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_esf_ctrl_00.reg_esf_en,GET_BITS(pp->shp_cmn_vsd[8],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_esf_ctrl_01.reg_esf_min_ratio,GET_BITS(pp->shp_cmn_vsd[9],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_esf_ctrl_01.reg_esf_base,GET_BITS(pp->shp_cmn_vsd[10],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_esf_ctrl_01.reg_esf_max_clip,GET_BITS(pp->shp_cmn_vsd[11],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_00.reg_dctp_en,GET_BITS(pp->shp_cmn_vsd[12],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1e.reg_dctp_coring_en,GET_BITS(pp->shp_cmn_vsd[13],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1e.reg_dctp_coring_mode,GET_BITS(pp->shp_cmn_vsd[14],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_00.reg_tgen_on_off,GET_BITS(pp->shp_cmn_vsd[15],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0a.reg_tgen_coring_en,GET_BITS(pp->shp_cmn_vsd[16],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0a.reg_tgen_coring_mode,GET_BITS(pp->shp_cmn_vsd[17],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_00.reg_nntg_en,GET_BITS(pp->shp_cmn_vsd[18],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_0f.reg_nntg_coring_en,GET_BITS(pp->shp_cmn_vsd[19],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_0f.reg_nntg_coring_mode,GET_BITS(pp->shp_cmn_vsd[20],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en,GET_BITS(pp->shp_cmn_vsd[21],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_00.reg_cti_en,GET_BITS(pp->shp_cmn_vsd[22],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_en,GET_BITS(pp->shp_cmn_vsd[23],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_cti,shp_cti_ctrl_00.reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
		/*shp_djg_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_00.reg_dj_edf_en,GET_BITS(pp->shp_djg_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_00.reg_dj_edge_adaptive_en,GET_BITS(pp->shp_djg_vsd[1],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_00.reg_dj_soft_en,GET_BITS(pp->shp_djg_vsd[2],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_03.reg_dj_edge_min,GET_BITS(pp->shp_djg_vsd[3],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_03.reg_dj_edge_mul,GET_BITS(pp->shp_djg_vsd[4],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_00.reg_dj_center_blur_mode,GET_BITS(pp->shp_djg_vsd[5],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_00.reg_dj_n_avg_mode,GET_BITS(pp->shp_djg_vsd[6],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dj_ctrl_01.reg_dj_n_avg_gain,GET_BITS(pp->shp_djg_vsd[7],0,8));

		/*shp_map_cmn_vsd */
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_x0,GET_BITS(pp->shp_map_cmn_vsd[2],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_x1,GET_BITS(pp->shp_map_cmn_vsd[3],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_y0,GET_BITS(pp->shp_map_cmn_vsd[4],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_y1,GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_11.reg_fd_soft_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[6],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_11.reg_fd_soft_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y3,GET_BITS(pp->shp_map_cmn_vsd[8],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y2,GET_BITS(pp->shp_map_cmn_vsd[9],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y1,GET_BITS(pp->shp_map_cmn_vsd[10],0,6));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y0,GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

		/*shp_balance_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_en,GET_BITS(pp->shp_balance_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_mode,GET_BITS(pp->shp_balance_vsd[1],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_y1,GET_BITS(pp->shp_balance_vsd[2],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_06.reg_mp_gb_y2,GET_BITS(pp->shp_balance_vsd[3],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_06.reg_mp_gb_y3,GET_BITS(pp->shp_balance_vsd[4],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_en,GET_BITS(pp->shp_balance_vsd[5],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_mode,GET_BITS(pp->shp_balance_vsd[6],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_y1,GET_BITS(pp->shp_balance_vsd[7],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_06.reg_sp_gb_y2,GET_BITS(pp->shp_balance_vsd[8],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_06.reg_sp_gb_y3,GET_BITS(pp->shp_balance_vsd[9],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_00.reg_lc_shp_en,GET_BITS(pp->shp_balance_vsd[10],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_00.reg_lc_gb_en,GET_BITS(pp->shp_balance_vsd[11],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_01.reg_lc_gb_y1,GET_BITS(pp->shp_balance_vsd[12],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_01.reg_lc_gb_y2,GET_BITS(pp->shp_balance_vsd[13],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_02.reg_lc_gb_y3,GET_BITS(pp->shp_balance_vsd[14],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_00.reg_lc_center_target,GET_BITS(pp->shp_balance_vsd[15],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_00.reg_lc_center_gain,GET_BITS(pp->shp_balance_vsd[16],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_00.reg_lc_local_gain,GET_BITS(pp->shp_balance_vsd[17],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y0,GET_BITS(pp->shp_balance_vsd[18],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y1,GET_BITS(pp->shp_balance_vsd[19],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y2,GET_BITS(pp->shp_balance_vsd[20],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_09.reg_mp_lum2_y0,GET_BITS(pp->shp_balance_vsd[21],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0a.reg_mp_lum2_y1,GET_BITS(pp->shp_balance_vsd[22],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0a.reg_mp_lum2_y2,GET_BITS(pp->shp_balance_vsd[23],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y0,GET_BITS(pp->shp_balance_vsd[24],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y1,GET_BITS(pp->shp_balance_vsd[25],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y2,GET_BITS(pp->shp_balance_vsd[26],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_09.reg_sp_lum2_y0,GET_BITS(pp->shp_balance_vsd[27],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0a.reg_sp_lum2_y1,GET_BITS(pp->shp_balance_vsd[28],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0a.reg_sp_lum2_y2,GET_BITS(pp->shp_balance_vsd[29],0,8));
		/*shp_ti_cmn_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_00.reg_ptiv_enable,GET_BITS(pp->shp_ti_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_00.reg_ptiv_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[1],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_00.reg_ptiv_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[2],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_00.reg_ptiv_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_01.reg_ptih_enable,GET_BITS(pp->shp_ti_cmn_vsd[4],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_01.reg_ptih_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[5],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_01.reg_ptih_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[6],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_01.reg_ptih_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sti_ctrl_00.reg_sti_enable,GET_BITS(pp->shp_ti_cmn_vsd[8],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sti_ctrl_00.reg_sti_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[9],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sti_ctrl_00.reg_sti_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[10],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sti_ctrl_00.reg_sti_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_snr_ctrl_00.reg_snr_blur_en,GET_BITS(pp->shp_ti_cmn_vsd[12],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_snr_ctrl_00.reg_snr_blur_sel,GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
		/*shp_chroma_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_chroma_ctrl_00.reg_color_region_en,GET_BITS(pp->shp_chroma_vsd[0],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_chroma_ctrl_00.reg_chr_protection_en,GET_BITS(pp->shp_chroma_vsd[1],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_chroma_ctrl_00.reg_chr_compensation_en,GET_BITS(pp->shp_chroma_vsd[2],0,1));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_chroma_ctrl_0d.reg_chr_gain_r0_gain,GET_BITS(pp->shp_chroma_vsd[3],0,8));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_chroma_ctrl_0d.reg_chr_gain_r1_gain,GET_BITS(pp->shp_chroma_vsd[4],0,8));
		/*shp_ee_vsd*/
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[0],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[1],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[14],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[15],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[2],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[3],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[16],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[17],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[4],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[5],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[18],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[19],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[6],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[7],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[20],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[21],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[8],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[9],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[22],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[23],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[10],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[11],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[24],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[25],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[12],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[13],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[26],0,7));
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[27],0,7));
	}while(0);
	#endif
	return ret;
}
int PE_CHPI_SHP_HW_E60F20_GetCtrl(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 i;
	LX_PE_SHP_ALL_CMN_T stParams;
	LX_PE_SHP_ALL_CMN_T *pp;
	UINT8 *pd;
	UINT16 *pd16;
	UINT32 *pd32;
	do{
		pp=&stParams;
		memset(pp,0,sizeof(LX_PE_SHP_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized

		/* set tbl */
		/* read from phys to shdw */
		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dctp_ctrl_1d.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_1e.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_1f.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_nntg_ctrl_0e.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_der_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_der_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(cti.shp_cti_ctrl_02.udata32);
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_obj_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_obj_ctrl_0a.udata32);
		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_der_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_esf_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_esf_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dctp_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dctp_ctrl_1e.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_tgen_ctrl_0a.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_nntg_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_nntg_ctrl_0f.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_motion_prot_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(cti.shp_cti_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(cti.shp_cti_ctrl_00.udata32);
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dj_ctrl_01.udata32);

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_fd_ctrl_0b.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_fd_ctrl_0d.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_fd_ctrl_11.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_fd_ctrl_14.udata32);

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_lc_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_lc_ctrl_02.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_0a.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_0a.udata32);
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_pti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_pti_ctrl_01.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_snr_ctrl_00.udata32);
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_chroma_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_chroma_ctrl_0d.udata32);
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_mp_ctrl_0c.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_sp_ctrl_0c.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_pti_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_lc_ctrl_04.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_dctp_ctrl_1f.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_tgen_ctrl_0b.udata32);
		PE_CHPI_TBL0_E60F20_RdFL(res.shp_nntg_ctrl_10.udata32);
		/*shp_ui_main_vsd*/
		pp->shp_ui_main_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1d.reg_dctp_gain);
		pp->shp_ui_main_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_00.reg_tgen_master_gain);
		pp->shp_ui_main_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_1e.reg_dj_soft_g1_mul);
		pp->shp_ui_main_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_1f.reg_dj_soft_g2_mul);
		pp->shp_ui_main_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_0e.reg_nntg_denoise_gain);
		pp->shp_ui_main_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_der_ctrl_00.reg_derh_csft_gain);
		pp->shp_ui_main_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_w);
		pp->shp_ui_main_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_b);
		pp->shp_ui_main_vsd[8]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_01.reg_mp_im_gain_h);
		pp->shp_ui_main_vsd[9]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_01.reg_sp_im_gain_h);
		pp->shp_ui_main_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_01.reg_mp_im_gain_v);
		pp->shp_ui_main_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sti_ctrl_00.reg_sti_master_gain);
		pp->shp_ui_main_vsd[12]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_00.reg_cti_gain);
		pp->shp_ui_main_vsd[13]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_y_gain);
		pp->shp_ui_main_vsd[14]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_c_gain);
		/*shp_face_obj_vsd*/
		pp->shp_face_obj_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x0);
		pp->shp_face_obj_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y0);
		pp->shp_face_obj_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x1);
		pp->shp_face_obj_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y1);
		pp->shp_face_obj_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x2);
		pp->shp_face_obj_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y2);
		pp->shp_face_obj_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x3);
		pp->shp_face_obj_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y3);
		/*shp_cmn_vsd*/
		pp->shp_cmn_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_der_ctrl_01.reg_derh_edge_y_filter_en);
		pp->shp_cmn_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_der_ctrl_01.reg_derh_bflt_tap_size);
		pp->shp_cmn_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_00.reg_mp_shp_en);
		pp->shp_cmn_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_00.reg_sp_shp_en);
		pp->shp_cmn_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_01.reg_mp_im_os_gain);
		pp->shp_cmn_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_01.reg_mp_im_us_gain);
		pp->shp_cmn_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_01.reg_sp_im_os_gain);
		pp->shp_cmn_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_01.reg_sp_im_us_gain);
		pp->shp_cmn_vsd[8]=PE_CHPI_TBL0_E60F20_Rd(res.shp_esf_ctrl_00.reg_esf_en);
		pp->shp_cmn_vsd[9]=PE_CHPI_TBL0_E60F20_Rd(res.shp_esf_ctrl_01.reg_esf_min_ratio);
		pp->shp_cmn_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_esf_ctrl_01.reg_esf_base);
		pp->shp_cmn_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_esf_ctrl_01.reg_esf_max_clip);
		pp->shp_cmn_vsd[12]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_00.reg_dctp_en);
		pp->shp_cmn_vsd[13]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1e.reg_dctp_coring_en);
		pp->shp_cmn_vsd[14]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1e.reg_dctp_coring_mode);
		pp->shp_cmn_vsd[15]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_00.reg_tgen_on_off);
		pp->shp_cmn_vsd[16]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0a.reg_tgen_coring_en);
		pp->shp_cmn_vsd[17]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0a.reg_tgen_coring_mode);
		pp->shp_cmn_vsd[18]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_00.reg_nntg_en);
		pp->shp_cmn_vsd[19]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_0f.reg_nntg_coring_en);
		pp->shp_cmn_vsd[20]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_0f.reg_nntg_coring_mode);
		pp->shp_cmn_vsd[21]=PE_CHPI_TBL0_E60F20_Rd(res.shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en);
		pp->shp_cmn_vsd[22]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_00.reg_cti_en);
		pp->shp_cmn_vsd[23]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_en);
		pp->shp_cmn_vsd[24]=PE_CHPI_TBL0_E60F20_Rd(cti.shp_cti_ctrl_00.reg_cti_filter_tap_size);
		/*shp_djg_vsd*/
		pp->shp_djg_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_00.reg_dj_edf_en);
		pp->shp_djg_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_00.reg_dj_edge_adaptive_en);
		pp->shp_djg_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_00.reg_dj_soft_en);
		pp->shp_djg_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_03.reg_dj_edge_min);
		pp->shp_djg_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_03.reg_dj_edge_mul);
		pp->shp_djg_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_00.reg_dj_center_blur_mode);
		pp->shp_djg_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_00.reg_dj_n_avg_mode);
		pp->shp_djg_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dj_ctrl_01.reg_dj_n_avg_gain);

		/*shp_map_cmn_vsd */
		pp->shp_map_cmn_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en);
		pp->shp_map_cmn_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en);
		pp->shp_map_cmn_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x0);
		pp->shp_map_cmn_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x1);
		pp->shp_map_cmn_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y0);
		pp->shp_map_cmn_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y1);
		pp->shp_map_cmn_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_11.reg_fd_soft_gain_t_en);
		pp->shp_map_cmn_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_11.reg_fd_soft_gain_e_en);
		pp->shp_map_cmn_vsd[8]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y3);
		pp->shp_map_cmn_vsd[9]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y2);
		pp->shp_map_cmn_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y1);
		pp->shp_map_cmn_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y0);

		/*shp_balance_vsd*/
		pp->shp_balance_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_05.reg_mp_gb_en);
		pp->shp_balance_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_05.reg_mp_gb_mode);
		pp->shp_balance_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_05.reg_mp_gb_y1);
		pp->shp_balance_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_06.reg_mp_gb_y2);
		pp->shp_balance_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_06.reg_mp_gb_y3);
		pp->shp_balance_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_05.reg_sp_gb_en);
		pp->shp_balance_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_05.reg_sp_gb_mode);
		pp->shp_balance_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_05.reg_sp_gb_y1);
		pp->shp_balance_vsd[8]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_06.reg_sp_gb_y2);
		pp->shp_balance_vsd[9]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_06.reg_sp_gb_y3);
		pp->shp_balance_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_00.reg_lc_shp_en);
		pp->shp_balance_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_00.reg_lc_gb_en);
		pp->shp_balance_vsd[12]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_01.reg_lc_gb_y1);
		pp->shp_balance_vsd[13]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_01.reg_lc_gb_y2);
		pp->shp_balance_vsd[14]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_02.reg_lc_gb_y3);
		pp->shp_balance_vsd[15]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_00.reg_lc_center_target);
		pp->shp_balance_vsd[16]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_00.reg_lc_center_gain);
		pp->shp_balance_vsd[17]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_00.reg_lc_local_gain);
		pp->shp_balance_vsd[18]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y0);
		pp->shp_balance_vsd[19]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y1);
		pp->shp_balance_vsd[20]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y2);
		pp->shp_balance_vsd[21]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_09.reg_mp_lum2_y0);
		pp->shp_balance_vsd[22]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0a.reg_mp_lum2_y1);
		pp->shp_balance_vsd[23]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0a.reg_mp_lum2_y2);
		pp->shp_balance_vsd[24]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y0);
		pp->shp_balance_vsd[25]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y1);
		pp->shp_balance_vsd[26]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y2);
		pp->shp_balance_vsd[27]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_09.reg_sp_lum2_y0);
		pp->shp_balance_vsd[28]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0a.reg_sp_lum2_y1);
		pp->shp_balance_vsd[29]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0a.reg_sp_lum2_y2);
		/*shp_ti_cmn_vsd*/
		pp->shp_ti_cmn_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_00.reg_ptiv_enable);
		pp->shp_ti_cmn_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_00.reg_ptiv_ti_mode);
		pp->shp_ti_cmn_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_00.reg_ptiv_mm_tap_size);
		pp->shp_ti_cmn_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_00.reg_ptiv_avg_tap_size);
		pp->shp_ti_cmn_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_01.reg_ptih_enable);
		pp->shp_ti_cmn_vsd[5]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_01.reg_ptih_ti_mode);
		pp->shp_ti_cmn_vsd[6]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_01.reg_ptih_mm_tap_size);
		pp->shp_ti_cmn_vsd[7]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_01.reg_ptih_avg_tap_size);
		pp->shp_ti_cmn_vsd[8]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sti_ctrl_00.reg_sti_enable);
		pp->shp_ti_cmn_vsd[9]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sti_ctrl_00.reg_sti_ti_mode);
		pp->shp_ti_cmn_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sti_ctrl_00.reg_sti_mm_tap_size);
		pp->shp_ti_cmn_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sti_ctrl_00.reg_sti_avg_tap_size);
		pp->shp_ti_cmn_vsd[12]=PE_CHPI_TBL0_E60F20_Rd(res.shp_snr_ctrl_00.reg_snr_blur_en);
		pp->shp_ti_cmn_vsd[13]=PE_CHPI_TBL0_E60F20_Rd(res.shp_snr_ctrl_00.reg_snr_blur_sel);
		/*shp_chroma_vsd*/
		pp->shp_chroma_vsd[0]=PE_CHPI_TBL0_E60F20_Rd(res.shp_chroma_ctrl_00.reg_color_region_en);
		pp->shp_chroma_vsd[1]=PE_CHPI_TBL0_E60F20_Rd(res.shp_chroma_ctrl_00.reg_chr_protection_en);
		pp->shp_chroma_vsd[2]=PE_CHPI_TBL0_E60F20_Rd(res.shp_chroma_ctrl_00.reg_chr_compensation_en);
		pp->shp_chroma_vsd[3]=PE_CHPI_TBL0_E60F20_Rd(res.shp_chroma_ctrl_0d.reg_chr_gain_r0_gain);
		pp->shp_chroma_vsd[4]=PE_CHPI_TBL0_E60F20_Rd(res.shp_chroma_ctrl_0d.reg_chr_gain_r1_gain);
		/*shp_ee_vsd*/
		pp->shp_ee_vsd[0] =PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_b);
		pp->shp_ee_vsd[1] =PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_w);
		pp->shp_ee_vsd[14]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_b);
		pp->shp_ee_vsd[15]=PE_CHPI_TBL0_E60F20_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_w);
		pp->shp_ee_vsd[2] =PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_b);
		pp->shp_ee_vsd[3] =PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_w);
		pp->shp_ee_vsd[16]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_b);
		pp->shp_ee_vsd[17]=PE_CHPI_TBL0_E60F20_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_w);
		pp->shp_ee_vsd[4] =PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_b);
		pp->shp_ee_vsd[5] =PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_w);
		pp->shp_ee_vsd[18]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_b);
		pp->shp_ee_vsd[19]=PE_CHPI_TBL0_E60F20_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_w);
		pp->shp_ee_vsd[6] =PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_b);
		pp->shp_ee_vsd[7] =PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_w);
		pp->shp_ee_vsd[20]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_b);
		pp->shp_ee_vsd[21]=PE_CHPI_TBL0_E60F20_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_w);
		pp->shp_ee_vsd[8] =PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b);
		pp->shp_ee_vsd[9] =PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w);
		pp->shp_ee_vsd[22]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b);
		pp->shp_ee_vsd[23]=PE_CHPI_TBL0_E60F20_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w);
		pp->shp_ee_vsd[10]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b);
		pp->shp_ee_vsd[11]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w);
		pp->shp_ee_vsd[24]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b);
		pp->shp_ee_vsd[25]=PE_CHPI_TBL0_E60F20_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w);
		pp->shp_ee_vsd[12]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b);
		pp->shp_ee_vsd[13]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w);
		pp->shp_ee_vsd[26]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b);
		pp->shp_ee_vsd[27]=PE_CHPI_TBL0_E60F20_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w);
		PE_CHPI_TBL0_E60F20_QRd(res.sr_merge_blend_00.reg_blend_amp_weight,pp->shp_dnn_sr_vsd[0]);


		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmCmnUserDb */
		/* PE_CHPI_SHP_UI_SQM_E60F20_T 			 sqm0;//11 */
		PE_CHPI_TBL0_E60F20_QRd(sqm0.ui32,pp->shp_val);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_E60F20_QRd(sqm0.data32[i],pp->shp_ui_sqm_vsd[i]);
		}
		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_E60_DownloadShpSqmDetailUserDb */
		/* PE_CHPI_SHP_CMN_SQM_E60F20_T			 sqm1;//12 */
		PE_CHPI_TBL0_E60F20_QRd(sqm1.ui32,pp->shp_val);
		for (i=0; i<51; i++)
		{
			PE_CHPI_TBL0_E60F20_QRd(sqm1.data32[i],pp->shp_sqm_cmn_vsd[i]);
		}
		PE_CHPI_TBL0_E60F20_QRd(sqm1.cnt32,i);

		pd = pp->shp_ui_main_vsd;
		printk("get[%d] : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = pp->shp_face_obj_vsd;
		printk("get[%d] : shp_fobj_vsd\n"
		"shp_fobj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = pp->shp_cmn_vsd;
		printk("get[%d] : shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = pp->shp_djg_vsd;
		printk("get[%d] : shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = pp->shp_map_cmn_vsd;
		printk("get[%d] : shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = pp->shp_balance_vsd;
		printk("get[%d] : shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = pp->shp_ti_cmn_vsd;
		printk("get[%d] : shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = pp->shp_chroma_vsd;
		printk("get[%d] : shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		pd = pp->shp_ee_vsd;
		printk("get[%d] : shp_ee_vsd\n"
		"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
		pd16 = pp->shp_dnn_sr_vsd;
		printk("get[%d]] : shp_dnn_sr_vsd\n"
		"shp_dnn_sr_vsd   [00]0x%02X\n",\
		pp->win_id, \
		pd16[0]);

		pd32 = pp->shp_ui_sqm_vsd;
		printk("[%d]shp_ui_sqm_vsd:%d, cnt:%d\n", pp->win_id, pp->shp_val, i);
		printk( \
		"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39]);
		pd32 = pp->shp_sqm_cmn_vsd;
		printk("[%d]shp_sqm_cmn_vsd:%d, cnt:%d\n", pp->win_id, pp->shp_val, i);
		printk( \
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X\n",\
		pd32[0],  pd32[1],	pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],	pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[34],	pd32[45],  pd32[46],  pd32[47], pd32[48],  pd32[49],\
		pd32[50]);
	}while(0);
	#endif
	return ret;
}


int PE_CHPI_SHP_HW_E60F20_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_E60F20_ENABLE
	UINT32 enable;
	PE_RES_HW_PARAM_DATA_E60F20_T *p_res = &_g_pe_res_hw_param_data_e60f20;
	do{
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_res->reg_user.data);
		CHECK_KNULL(p_res->reg_mask.data);
		enable = (*onoff >0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_E60F20_Wr(res.shp_obj_ctrl_00.reg_obj_shp_en,enable);
		PE_CHPI_TBL0_E60F20_WrFL(res.shp_obj_ctrl_00.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RES);
		/* set user */
		PE_CHPI_SHP_HW_E60F20_USER(p_res,shp_obj_ctrl_00.reg_obj_shp_en,enable);
	}while(0);
	#endif
	return ret;
}

