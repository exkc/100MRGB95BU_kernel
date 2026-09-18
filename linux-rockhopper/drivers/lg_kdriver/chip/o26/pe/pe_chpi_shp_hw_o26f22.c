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

/** @file pe_chpi_shp_hw_o26.c
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
#include "pe_res_hw_param_o26.h"
#include "pe_cti_dnr_hw_param_o26.h"
#include "pe_chpi_shp_hw_o26f22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_SHP_HW_O26F22_ENABLE

#define PE_CHPI_SHP_HW_O26F22_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_SHP_HW_O26F22_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O26F22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O26F22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RES_HW_PARAM_REG_O26F22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RES_HW_PARAM_REG_O26F22_T *data;
	} reg_data;
} PE_RES_HW_PARAM_DATA_O26F22_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_CTI_HW_PARAM_DATA_O26F22_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
extern const PE_REG_PARAM_T shp_l_sd_default_o26[];
extern const PE_REG_PARAM_T shp_l_hd_default_o26[];
extern const PE_REG_PARAM_T shp_l_ud_default_o26[];
extern const PE_REG_PARAM_T cti_y_l_sd_default_o26[];
extern const PE_REG_PARAM_T cti_y_l_hd_default_o26[];
extern const PE_REG_PARAM_T cti_y_l_vr_360_default_o26[];
extern const PE_REG_PARAM_T cti_y_l_atv_default_o26[];
extern const UINT32 sqm_shp_vsd_cmn_init_o26[];
extern const UINT32 sqm_shp_vsd_dtl_init_o26[];

extern const PE_REG_PARAM_T shp_l_sd_default_o26f22[];
extern const PE_REG_PARAM_T shp_l_hd_default_o26f22[];
extern const PE_REG_PARAM_T shp_l_ud_default_o26f22[];
extern const PE_REG_PARAM_T shp_l_8k_default_o26f22[];
extern const PE_REG_PARAM_T cti_y_l_sd_default_o26f22[];
extern const PE_REG_PARAM_T cti_y_l_hd_default_o26f22[];
extern const PE_REG_PARAM_T cti_y_l_vr_360_default_o26f22[];
extern const PE_REG_PARAM_T cti_y_l_atv_default_o26f22[];
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
#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
static PE_RES_HW_PARAM_DATA_O26F22_T _g_pe_res_hw_param_data_o26f22 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_O26F22_T _g_pe_cti_hw_param_data_o26f22 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static int PE_CHPI_SHP_HW_O26F22_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	PE_RES_HW_PARAM_DATA_O26F22_T *p_res = &_g_pe_res_hw_param_data_o26f22;
	PE_CTI_HW_PARAM_DATA_O26F22_T *p_cti = &_g_pe_cti_hw_param_data_o26f22;

	/* create dflt table */
	if (p_res->reg_dflt.addr == NULL)
	{
		p_res->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O26F22_T));
	}
	/* create user table */
	if (p_res->reg_user.addr == NULL)
	{
		p_res->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O26F22_T));
		memset((p_res->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O26F22_T));	// 0x0
	}
	/* create mask table */
	if (p_res->reg_mask.addr == NULL)
	{
		p_res->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O26F22_T));
		memset((p_res->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_O26F22_T));// 0xffffffff
	}
	/* create data table */
	if (p_res->reg_data.addr == NULL)
	{
		p_res->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O26F22_T));
		memset((p_res->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O26F22_T));	// 0x0
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
		p_cti->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O26_T));
	}
	/* create user table */
	if (p_cti->reg_user.addr == NULL)
	{
		p_cti->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O26_T));
		memset((p_cti->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O26_T));	// 0x0
	}
	/* create mask table */
	if (p_cti->reg_mask.addr == NULL)
	{
		p_cti->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O26_T));
		memset((p_cti->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_O26_T));// 0xffffffff
	}
	/* create data table */
	if (p_cti->reg_data.addr == NULL)
	{
		p_cti->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O26_T));
		memset((p_cti->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O26_T));	// 0x0
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

static PE_CHPI_SHP_HW_O26F22_RES_FMT PE_CHPI_SHP_HW_O26F22_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_SHP_HW_O26F22_RES_FMT res_fmt = PE_CHPI_SHP_O26F22_RES_NUM;
	if(disp_inf->act_fmt !=0)
	{
		res_fmt = PE_CHPI_SHP_O26F22_RES_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_DTV_HD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_UHD;
				}
				else
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_UHD_8K;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_HD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_UHD;
				}
				else
				{
					res_fmt = PE_CHPI_SHP_O26F22_RES_UHD_8K;
				}
				break;
		}
	}
	return res_fmt;
}

static PE_CHPI_SHP_HW_O26F22_CTI_FMT PE_CHPI_SHP_HW_O26F22_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_SHP_HW_O26F22_CTI_FMT cti_fmt = PE_CHPI_SHP_O26F22_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
		cti_fmt = PE_CHPI_SHP_O26F22_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					cti_fmt = PE_CHPI_SHP_O26F22_CTI_ATV;
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
					cti_fmt = PE_CHPI_SHP_O26F22_CTI_SD;
				}
				else
				{
					cti_fmt = PE_CHPI_SHP_O26F22_CTI_HD;
				}
				break;
		}
	}
	return cti_fmt;
}

static int PE_CHPI_SHP_HW_O26F22_SetResDefault(PE_CHPI_SHP_HW_O26F22_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_res_hw_param_data_o26f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_res_hw_param_data_o26f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_res_hw_param_data_o26f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_res_hw_param_data_o26f22.reg_data.addr;

	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_res_fmt)
	{
		case PE_CHPI_SHP_O26F22_RES_SD:
			p_dflt_param = shp_l_sd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_HD:
			p_dflt_param = shp_l_hd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_UHD:
			p_dflt_param = shp_l_ud_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_UHD_8K:
			p_dflt_param = shp_l_8k_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_DTV_SD:
			p_dflt_param = shp_l_sd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_DTV_HD:
			p_dflt_param = shp_l_hd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_RES_SEEMLESS:
		default:
			p_dflt_param = shp_l_hd_default_o26f22;
			break;
	}

	size = sizeof(PE_RES_HW_PARAM_REG_O26F22_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	do {
		if (!gPE_CHPI_DDR_O26)	break;
		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_00.udata32,p_data[0]);	//0xF3410020
		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_01.udata32,p_data[1]);	//0xF3410024
		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_02.udata32,p_data[2]);	//0xF3410028
		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_03.udata32,p_data[3]);	//0xF341002C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_04.udata32,p_data[4]);	//0xF3410030
		PE_CHPI_TBL0_O26F22_QWr(res.shp_text_region_map_00.udata32,p_data[5]);	//0xF3410034
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_00.udata32,p_data[6]);	//0xF3410100
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_01.udata32,p_data[7]);	//0xF3410104
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_02.udata32,p_data[8]);	//0xF3410108
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_ctrl_00.udata32,p_data[9]);	//0xF3410150
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_00.udata32,p_data[10]);	//0xF3410160
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_01.udata32,p_data[11]);	//0xF3410164
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_02.udata32,p_data[12]);	//0xF3410168
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_03.udata32,p_data[13]);	//0xF341016C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_04.udata32,p_data[14]);	//0xF3410170
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_05.udata32,p_data[15]);	//0xF3410174
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_06.udata32,p_data[16]);	//0xF3410178
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_07.udata32,p_data[17]);	//0xF341017C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_08.udata32,p_data[18]);	//0xF3410180
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_09.udata32,p_data[19]);	//0xF3410184
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0a.udata32,p_data[20]);	//0xF3410188
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0b.udata32,p_data[21]);	//0xF341018C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0c.udata32,p_data[22]);	//0xF3410190
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0d.udata32,p_data[23]);	//0xF3410194
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0e.udata32,p_data[24]);	//0xF3410198
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0f.udata32,p_data[25]);	//0xF341019C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_10.udata32,p_data[26]);	//0xF34101A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_11.udata32,p_data[27]);	//0xF34101A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_12.udata32,p_data[28]);	//0xF34101A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_13.udata32,p_data[29]);	//0xF34101AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_14.udata32,p_data[30]);	//0xF34101B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_15.udata32,p_data[31]);	//0xF34101B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_16.udata32,p_data[32]);	//0xF34101B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_00.udata32,p_data[33]);	//0xF34101C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_01.udata32,p_data[34]);	//0xF34101C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_02.udata32,p_data[35]);	//0xF34101C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_03.udata32,p_data[36]);	//0xF34101CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_04.udata32,p_data[37]);	//0xF34101D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_05.udata32,p_data[38]);	//0xF34101D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_06.udata32,p_data[39]);	//0xF34101D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_07.udata32,p_data[40]);	//0xF34101DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_08.udata32,p_data[41]);	//0xF34101E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_09.udata32,p_data[42]);	//0xF34101E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0a.udata32,p_data[43]);	//0xF34101E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0b.udata32,p_data[44]);	//0xF34101EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0c.udata32,p_data[45]);	//0xF34101F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_apl_ctrl_00.udata32,p_data[46]);	//0xF34101F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_00.udata32,p_data[47]);	//0xF3410200
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_01.udata32,p_data[48]);	//0xF3410204
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_02.udata32,p_data[49]);	//0xF3410208
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_03.udata32,p_data[50]);	//0xF341020C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_04.udata32,p_data[51]);	//0xF3410210
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_00.udata32,p_data[52]);	//0xF3410220
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_01.udata32,p_data[53]);	//0xF3410224
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_02.udata32,p_data[54]);	//0xF3410228
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_03.udata32,p_data[55]);	//0xF341022C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_04.udata32,p_data[56]);	//0xF3410230
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_05.udata32,p_data[57]);	//0xF3410234
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_06.udata32,p_data[58]);	//0xF3410238
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_07.udata32,p_data[59]);	//0xF341023C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_00.udata32,p_data[60]);	//0xF3410240
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_01.udata32,p_data[61]);	//0xF3410244
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_02.udata32,p_data[62]);	//0xF3410248
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_03.udata32,p_data[63]);	//0xF341024C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_04.udata32,p_data[64]);	//0xF3410250
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_05.udata32,p_data[65]);	//0xF3410254
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_06.udata32,p_data[66]);	//0xF3410258
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_07.udata32,p_data[67]);	//0xF341025C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_08.udata32,p_data[68]);	//0xF3410260
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_09.udata32,p_data[69]);	//0xF3410264
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0a.udata32,p_data[70]);	//0xF3410268
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0b.udata32,p_data[71]);	//0xF341026C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0c.udata32,p_data[72]);	//0xF3410270
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_00.udata32,p_data[73]);	//0xF3410280
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_01.udata32,p_data[74]);	//0xF3410284
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_02.udata32,p_data[75]);	//0xF3410288
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_03.udata32,p_data[76]);	//0xF341028C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sti_ctrl_00.udata32,p_data[77]);	//0xF3410290
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_00.udata32,p_data[78]);	//0xF34102A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_01.udata32,p_data[79]);	//0xF34102A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_02.udata32,p_data[80]);	//0xF34102A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_tgen_ctrl_03_c0.udata32,p_data[81]);	//0xF34102AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_tgen_ctrl_03_c1.udata32,p_data[82]);	//0xF34102B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_tgen_ctrl_03_c0.udata32,p_data[83]);	//0xF34102B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_tgen_ctrl_03_c1.udata32,p_data[84]);	//0xF34102B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_04.udata32,p_data[85]);	//0xF34102BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_05.udata32,p_data[86]);	//0xF34102C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_06.udata32,p_data[87]);	//0xF34102C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_07.udata32,p_data[88]);	//0xF34102C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_08.udata32,p_data[89]);	//0xF34102CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_09.udata32,p_data[90]);	//0xF34102D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_0a.udata32,p_data[91]);	//0xF34102D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_0b.udata32,p_data[92]);	//0xF34102D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_snr_ctrl_00.udata32,p_data[93]);	//0xF34102E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_00.udata32,p_data[94]);	//0xF34102F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_01.udata32,p_data[95]);	//0xF34102F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_02.udata32,p_data[96]);	//0xF34102F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_03.udata32,p_data[97]);	//0xF34102FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_04.udata32,p_data[98]);	//0xF3410300
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_05.udata32,p_data[99]);	//0xF3410304
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_06.udata32,p_data[100]);	//0xF3410308
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_07.udata32,p_data[101]);	//0xF341030C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_08.udata32,p_data[102]);//0xF3410310
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_09.udata32,p_data[103]);//0xF3410314
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0a.udata32,p_data[104]);//0xF3410318
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0b.udata32,p_data[105]);//0xF341031C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0c.udata32,p_data[106]);//0xF3410320
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0d.udata32,p_data[107]);//0xF3410324
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0e.udata32,p_data[108]);//0xF3410328
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0f.udata32,p_data[109]);//0xF341032C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_10.udata32,p_data[110]);//0xF3410330
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_11.udata32,p_data[111]);//0xF3410334
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_12.udata32,p_data[112]);//0xF3410338
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_13.udata32,p_data[113]);//0xF341033C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_14.udata32,p_data[114]);//0xF3410340
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_15.udata32,p_data[115]);//0xF3410344
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_16.udata32,p_data[116]);//0xF3410348
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_17.udata32,p_data[117]);//0xF341034C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_18.udata32,p_data[118]);//0xF3410350
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_19.udata32,p_data[119]);//0xF3410354
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1a.udata32,p_data[120]);//0xF3410358
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1b.udata32,p_data[121]);//0xF341035C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1c.udata32,p_data[122]);//0xF3410360
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1d.udata32,p_data[123]);//0xF3410364
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1e.udata32,p_data[124]);//0xF3410368
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1f.udata32,p_data[125]);//0xF341036C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_00.udata32,p_data[126]);//0xF3410370
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_01_c0.udata32,p_data[127]);	//0xF3410374
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_02_c0.udata32,p_data[128]);	//0xF3410378
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_03_c0.udata32,p_data[129]);	//0xF341037C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_04_c0.udata32,p_data[130]);	//0xF3410380
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_05_c0.udata32,p_data[131]);	//0xF3410384
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_01_c1.udata32,p_data[132]);	//0xF3410388
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_02_c1.udata32,p_data[133]);	//0xF341038C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_03_c1.udata32,p_data[134]);	//0xF3410390
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_04_c1.udata32,p_data[135]);	//0xF3410394
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_05_c1.udata32,p_data[136]);	//0xF3410398
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_01_c0.udata32,p_data[137]);	//0xF341039C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_02_c0.udata32,p_data[138]);	//0xF34103A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_03_c0.udata32,p_data[139]);	//0xF34103A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_04_c0.udata32,p_data[140]);	//0xF34103A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_05_c0.udata32,p_data[141]);	//0xF34103AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_01_c1.udata32,p_data[142]);	//0xF34103B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_02_c1.udata32,p_data[143]);	//0xF34103B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_03_c1.udata32,p_data[144]);	//0xF34103B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_04_c1.udata32,p_data[145]);	//0xF34103BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_05_c1.udata32,p_data[146]);	//0xF34103C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_06.udata32,p_data[147]);	//0xF34103C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_07.udata32,p_data[148]);	//0xF34103C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_08.udata32,p_data[149]);	//0xF34103CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_09.udata32,p_data[150]);	//0xF34103D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0a.udata32,p_data[151]);	//0xF34103D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0b.udata32,p_data[152]);	//0xF34103D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0c.udata32,p_data[153]);	//0xF34103DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0d.udata32,p_data[154]);	//0xF34103E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0e.udata32,p_data[155]);	//0xF34103E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0f.udata32,p_data[156]);	//0xF34103E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_10.udata32,p_data[157]);	//0xF34103EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_00.udata32,p_data[158]);	//0xF34103F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_01.udata32,p_data[159]);	//0xF34103F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_02.udata32,p_data[160]);	//0xF34103F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_03.udata32,p_data[161]);	//0xF34103FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_04.udata32,p_data[162]);	//0xF3410400
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_05.udata32,p_data[163]);	//0xF3410404
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_06.udata32,p_data[164]);	//0xF3410408
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_07.udata32,p_data[165]);	//0xF341040C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_08.udata32,p_data[166]);	//0xF3410410
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_09.udata32,p_data[167]);	//0xF3410414
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0a.udata32,p_data[168]);	//0xF3410418
		PE_CHPI_TBL0_O26F22_QWr(res.shp_psp_ctrl_00.udata32,p_data[169]);	    //0xF3410420
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0b.udata32,p_data[170]);	//0xF3410424
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0c.udata32,p_data[171]);	//0xF3410428
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_00.udata32,p_data[172]);	//0xF3410460
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_01.udata32,p_data[173]);	//0xF3410464
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_02.udata32,p_data[174]);	//0xF3410468
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_00.udata32,p_data[175]);	//0xF341046C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_01.udata32,p_data[176]);	//0xF3410470
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_02.udata32,p_data[177]);	//0xF3410474
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_03.udata32,p_data[178]);	//0xF3410478
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_04.udata32,p_data[179]);	//0xF341047C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_05.udata32,p_data[180]);	//0xF3410480
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_06.udata32,p_data[181]);	//0xF3410484
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_07.udata32,p_data[182]);	//0xF3410488
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_08.udata32,p_data[183]);	//0xF341048C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_09.udata32,p_data[184]);	//0xF3410490
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0a.udata32,p_data[185]);	//0xF3410494
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0b.udata32,p_data[186]);	//0xF3410498
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0c.udata32,p_data[187]);	//0xF341049C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_00.udata32,p_data[188]);	//0xF34104A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_01.udata32,p_data[189]);	//0xF34104A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_02.udata32,p_data[190]);	//0xF34104A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_03.udata32,p_data[191]);	//0xF34104AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_04.udata32,p_data[192]);	//0xF34104B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_05.udata32,p_data[193]);	//0xF34104B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_06.udata32,p_data[194]);	//0xF34104B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_07.udata32,p_data[195]);	//0xF34104BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_08.udata32,p_data[196]);	//0xF34104C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_09.udata32,p_data[197]);	//0xF34104C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0a.udata32,p_data[198]);	//0xF34104C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0b.udata32,p_data[199]);	//0xF34104CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0c.udata32,p_data[200]);	//0xF34104D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0d.udata32,p_data[201]);	//0xF34104D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0e.udata32,p_data[202]);	//0xF34104D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0f.udata32,p_data[203]);	//0xF34104DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_10.udata32,p_data[204]);	//0xF34104E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_11.udata32,p_data[205]);	//0xF34104E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_12.udata32,p_data[206]);	//0xF34104E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_13.udata32,p_data[207]);	//0xF34104EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_14.udata32,p_data[208]);	//0xF34104F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_15.udata32,p_data[209]);	//0xF34104F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_16.udata32,p_data[210]);	//0xF34104F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_17.udata32,p_data[211]);	//0xF34104FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_18.udata32,p_data[212]);	//0xF3410500
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_19.udata32,p_data[213]);	//0xF3410504
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1a.udata32,p_data[214]);	//0xF3410508
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1b.udata32,p_data[215]);	//0xF341050C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1c.udata32,p_data[216]);	//0xF3410510
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1d.udata32,p_data[217]);	//0xF3410514
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1e.udata32,p_data[218]);	//0xF3410518
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1f.udata32,p_data[219]);	//0xF341051C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_20.udata32,p_data[220]);	//0xF3410520
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_00.udata32,p_data[221]);	//0xF3410560
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_01.udata32,p_data[222]);	//0xF3410564
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_02.udata32,p_data[223]);	//0xF3410568
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_03.udata32,p_data[224]);	//0xF341056C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_04.udata32,p_data[225]);	//0xF3410570
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_05.udata32,p_data[226]);	//0xF3410574
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_06.udata32,p_data[227]);	//0xF3410578
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_07.udata32,p_data[228]);	//0xF341057C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_08.udata32,p_data[229]);	//0xF3410580
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_09.udata32,p_data[230]);	//0xF3410584
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0a.udata32,p_data[231]);	//0xF3410588
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0b.udata32,p_data[232]);	//0xF341058C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0c.udata32,p_data[233]);	//0xF3410590
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0d.udata32,p_data[234]);	//0xF3410594
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0e.udata32,p_data[235]);	//0xF3410598
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_00.udata32,p_data[236]);	//0xF34105B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_01.udata32,p_data[237]);	//0xF34105B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_02.udata32,p_data[238]);	//0xF34105B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_03.udata32,p_data[239]);	//0xF34105BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_00.udata32,p_data[240]);	//0xF34105C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_01.udata32,p_data[241]);	//0xF34105C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_02.udata32,p_data[242]);	//0xF34105C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_03.udata32,p_data[243]);	//0xF34105CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_04.udata32,p_data[244]);	//0xF34105D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_05.udata32,p_data[245]);	//0xF34105D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_06.udata32,p_data[246]);	//0xF34105D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_00.udata32,p_data[247]);	//0xF34105E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_01.udata32,p_data[248]);	//0xF34105E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_02.udata32,p_data[249]);	//0xF34105E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_03.udata32,p_data[250]);	//0xF34105EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_00.udata32,p_data[251]);	//0xF3410620
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_01.udata32,p_data[252]);	//0xF3410624
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_02.udata32,p_data[253]);	//0xF3410628
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_03.udata32,p_data[254]);	//0xF341062C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_04.udata32,p_data[255]);	//0xF3410630
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_05.udata32,p_data[256]);	//0xF3410634
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_06.udata32,p_data[257]);	//0xF3410638
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_07.udata32,p_data[258]);	//0xF341063C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_08.udata32,p_data[259]);	//0xF3410640
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_09.udata32,p_data[260]);	//0xF3410644
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0a.udata32,p_data[261]);	//0xF3410648
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0b.udata32,p_data[262]);	//0xF341064C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0c.udata32,p_data[263]);	//0xF3410650
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_00.udata32,p_data[264]);	//0xF3410660
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_01.udata32,p_data[265]);	//0xF3410664
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_02.udata32,p_data[266]);	//0xF3410668
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_03.udata32,p_data[267]);	//0xF341066C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_04.udata32,p_data[268]);	//0xF3410670
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_00.udata32,p_data[269]);	//0xF34106C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_01.udata32,p_data[270]);	//0xF34106C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_02.udata32,p_data[271]);	//0xF34106C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_03.udata32,p_data[272]);	//0xF34106CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_04.udata32,p_data[273]);	//0xF34106D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_05.udata32,p_data[274]);	//0xF34106D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_06.udata32,p_data[275]);	//0xF34106D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_07.udata32,p_data[276]);	//0xF34106DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_08.udata32,p_data[277]);	//0xF34106E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_09.udata32,p_data[278]);	//0xF34106E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0a.udata32,p_data[279]);	//0xF34106E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0b.udata32,p_data[280]);	//0xF34106EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0c.udata32,p_data[281]);	//0xF34106F0
		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_RES);
	}while(0);
	#endif

	return ret;
}

static int PE_CHPI_SHP_HW_O26F22_SetCtiDefault(PE_CHPI_SHP_HW_O26F22_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_cti_hw_param_data_o26f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_cti_hw_param_data_o26f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_cti_hw_param_data_o26f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_cti_hw_param_data_o26f22.reg_data.addr;

	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_SHP_HW_O26F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_cti_fmt)
	{
		case PE_CHPI_SHP_O26F22_CTI_SD:
			p_dflt_param = cti_y_l_sd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_CTI_HD:
			p_dflt_param = cti_y_l_hd_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_CTI_VR_360:
			p_dflt_param = cti_y_l_vr_360_default_o26f22;
			break;
		case PE_CHPI_SHP_O26F22_CTI_ATV:
		default:
			p_dflt_param = cti_y_l_atv_default_o26f22;
			break;
	}

	size = sizeof(PE_CTI_HW_PARAM_REG_O26_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	
	do {
		if (!gPE_CHPI_DDR_O26)	break;
		PE_CHPI_TBL0_O26F22_QWr(cti.cti_ctrl_0.udata32,p_data[0]);
		PE_CHPI_TBL0_O26F22_QWr(cti.cti_ctrl_1.udata32,p_data[1]);
		PE_CHPI_TBL0_O26F22_QWr(cti.reg_cti_ctrl_2.udata32,p_data[2]);
		PE_CHPI_TBL0_O26F22_QWr(cti.reg_cti_ctrl_3.udata32,p_data[3]);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_00.udata32,p_data[8]);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_01.udata32,p_data[9]);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_02.udata32,p_data[10]);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_CTI);
	}while(0);
	#endif

	return ret;
}

int PE_CHPI_SHP_HW_O26F22_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_O26_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_SHP_HW_O26F22_RES_FMT pre0_res_fmt = PE_CHPI_SHP_O26F22_RES_NUM;
	static PE_CHPI_SHP_HW_O26F22_CTI_FMT pre0_cti_fmt = PE_CHPI_SHP_O26F22_CTI_NUM;
	PE_CHPI_SHP_HW_O26F22_RES_FMT cur0_res_fmt;
	PE_CHPI_SHP_HW_O26F22_CTI_FMT cur0_cti_fmt;
	do{
		ret = PE_INF_O26_GetCurInfSettings(&inf_set);
		PE_CHPI_SHP_HW_O26F22_CHECK_CODE(ret,break,"PE_INF_O26_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_res_fmt = PE_CHPI_SHP_HW_O26F22_ConvDispInfoToResFmt(disp0_inf);
		if(pre0_res_fmt!=cur0_res_fmt)
		{
			ret = PE_CHPI_SHP_HW_O26F22_SetResDefault(cur0_res_fmt);
			PE_CHPI_SHP_HW_O26F22_CHECK_CODE(ret,break,"PE_CHPI_SHP_HW_O26F22_SetResDefault() error\n");
			pre0_res_fmt=cur0_res_fmt;
		}
		cur0_cti_fmt = PE_CHPI_SHP_HW_O26F22_ConvDispInfoToCtiFmt(disp0_inf);
		if(pre0_cti_fmt!=cur0_cti_fmt)
		{
			ret = PE_CHPI_SHP_HW_O26F22_SetCtiDefault(cur0_cti_fmt);
			PE_CHPI_SHP_HW_O26F22_CHECK_CODE(ret,break,"PE_CHPI_SHP_HW_O26F22_SetCtiDefault() error\n");
			pre0_cti_fmt=cur0_cti_fmt;
		}
	}while(0);
	return ret;
}

#if (CONFIG_LX_O26_CHIP_FIRMWARE == 1)
int PE_CHPI_SHP_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 i;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_SHP_HW_O26F22_CreateDataTable();
		if (ret)	break;
		if (pstParams->resume_mode == 1)	break;//if qsm,skip
		if (!gPE_CHPI_DDR_O26)	break;

		/* addr */
 		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_00.uaddr32,0xF3410020);	//0xF3410020
 		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_01.uaddr32,0xF3410024);	//0xF3410024
 		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_02.uaddr32,0xF3410028);	//0xF3410028
 		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_03.uaddr32,0xF341002C);	//0xF341002C
 		PE_CHPI_TBL0_O26F22_QWr(res.shp_new_fd_ctrl_04.uaddr32,0xF3410030);	//0xF3410030
		PE_CHPI_TBL0_O26F22_QWr(res.shp_text_region_map_00.uaddr32,0xF3410034);	//0xF3410034
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_00.uaddr32,0xF3410100);	//0xF3410100
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_01.uaddr32,0xF3410104);	//0xF3410104
		PE_CHPI_TBL0_O26F22_QWr(res.shp_esf_ctrl_02.uaddr32,0xF3410108);	//0xF3410108
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_ctrl_00.uaddr32,0xF3410150);	//0xF3410150
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_00.uaddr32,0xF3410160);	//0xF3410160
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_01.uaddr32,0xF3410164);	//0xF3410164
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_02.uaddr32,0xF3410168);	//0xF3410168
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_03.uaddr32,0xF341016C);	//0xF341016C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_04.uaddr32,0xF3410170);	//0xF3410170
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_05.uaddr32,0xF3410174);	//0xF3410174
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_06.uaddr32,0xF3410178);	//0xF3410178
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_07.uaddr32,0xF341017C);	//0xF341017C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_08.uaddr32,0xF3410180);	//0xF3410180
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_09.uaddr32,0xF3410184);	//0xF3410184
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0a.uaddr32,0xF3410188);	//0xF3410188
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0b.uaddr32,0xF341018C);	//0xF341018C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0c.uaddr32,0xF3410190);	//0xF3410190
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0d.uaddr32,0xF3410194);	//0xF3410194
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0e.uaddr32,0xF3410198);	//0xF3410198
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_0f.uaddr32,0xF341019C);	//0xF341019C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_10.uaddr32,0xF34101A0);	//0xF34101A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_11.uaddr32,0xF34101A4);	//0xF34101A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_12.uaddr32,0xF34101A8);	//0xF34101A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_13.uaddr32,0xF34101AC);	//0xF34101AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_14.uaddr32,0xF34101B0);	//0xF34101B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_15.uaddr32,0xF34101B4);	//0xF34101B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_ctrl_16.uaddr32,0xF34101B8);	//0xF34101B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_00.uaddr32,0xF34101C0);	//0xF34101C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_01.uaddr32,0xF34101C4);	//0xF34101C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_02.uaddr32,0xF34101C8);	//0xF34101C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_03.uaddr32,0xF34101CC);	//0xF34101CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_04.uaddr32,0xF34101D0);	//0xF34101D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_05.uaddr32,0xF34101D4);	//0xF34101D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_06.uaddr32,0xF34101D8);	//0xF34101D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_07.uaddr32,0xF34101DC);	//0xF34101DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_08.uaddr32,0xF34101E0);	//0xF34101E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_09.uaddr32,0xF34101E4);	//0xF34101E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0a.uaddr32,0xF34101E8);	//0xF34101E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0b.uaddr32,0xF34101EC);	//0xF34101EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_mp_ctrl_0c.uaddr32,0xF34101F0);	//0xF34101F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_apl_ctrl_00.uaddr32,0xF34101F4);	//0xF34101F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_00.uaddr32,0xF3410200);	//0xF3410200
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_01.uaddr32,0xF3410204);	//0xF3410204
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_02.uaddr32,0xF3410208);	//0xF3410208
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_03.uaddr32,0xF341020C);	//0xF341020C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_lc_ctrl_04.uaddr32,0xF3410210);	//0xF3410210
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_00.uaddr32,0xF3410220);	//0xF3410220
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_01.uaddr32,0xF3410224);	//0xF3410224
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_02.uaddr32,0xF3410228);	//0xF3410228
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_03.uaddr32,0xF341022C);	//0xF341022C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_04.uaddr32,0xF3410230);	//0xF3410230
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_05.uaddr32,0xF3410234);	//0xF3410234
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_06.uaddr32,0xF3410238);	//0xF3410238
		PE_CHPI_TBL0_O26F22_QWr(res.shp_der_ctrl_07.uaddr32,0xF341023C);	//0xF341023C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_00.uaddr32,0xF3410240);	//0xF3410240
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_01.uaddr32,0xF3410244);	//0xF3410244
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_02.uaddr32,0xF3410248);	//0xF3410248
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_03.uaddr32,0xF341024C);	//0xF341024C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_04.uaddr32,0xF3410250);	//0xF3410250
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_05.uaddr32,0xF3410254);	//0xF3410254
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_06.uaddr32,0xF3410258);	//0xF3410258
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_07.uaddr32,0xF341025C);	//0xF341025C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_08.uaddr32,0xF3410260);	//0xF3410260
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_09.uaddr32,0xF3410264);	//0xF3410264
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0a.uaddr32,0xF3410268);	//0xF3410268
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0b.uaddr32,0xF341026C);	//0xF341026C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sp_ctrl_0c.uaddr32,0xF3410270);	//0xF3410270
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_00.uaddr32,0xF3410280);	//0xF3410280
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_01.uaddr32,0xF3410284);	//0xF3410284
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_02.uaddr32,0xF3410288);	//0xF3410288
		PE_CHPI_TBL0_O26F22_QWr(res.shp_pti_ctrl_03.uaddr32,0xF341028C);	//0xF341028C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_sti_ctrl_00.uaddr32,0xF3410290);	//0xF3410290
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_00.uaddr32,0xF34102A0);	//0xF34102A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_01.uaddr32,0xF34102A4);	//0xF34102A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_02.uaddr32,0xF34102A8);	//0xF34102A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_tgen_ctrl_03_c0.uaddr32,0xF34102AC);	//0xF34102AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_tgen_ctrl_03_c1.uaddr32,0xF34102B0);	//0xF34102B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_tgen_ctrl_03_c0.uaddr32,0xF34102B4);	//0xF34102B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_tgen_ctrl_03_c1.uaddr32,0xF34102B8);	//0xF34102B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_04.uaddr32,0xF34102BC);	//0xF34102BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_05.uaddr32,0xF34102C0);	//0xF34102C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_06.uaddr32,0xF34102C4);	//0xF34102C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_07.uaddr32,0xF34102C8);	//0xF34102C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_08.uaddr32,0xF34102CC);	//0xF34102CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_09.uaddr32,0xF34102D0);	//0xF34102D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_0a.uaddr32,0xF34102D4);	//0xF34102D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_tgen_ctrl_0b.uaddr32,0xF34102D8);	//0xF34102D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_snr_ctrl_00.uaddr32,0xF34102E0);	//0xF34102E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_00.uaddr32,0xF34102F0);	//0xF34102F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_01.uaddr32,0xF34102F4);	//0xF34102F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_02.uaddr32,0xF34102F8);	//0xF34102F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_03.uaddr32,0xF34102FC);	//0xF34102FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_04.uaddr32,0xF3410300);	//0xF3410300
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_05.uaddr32,0xF3410304);	//0xF3410304
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_06.uaddr32,0xF3410308);	//0xF3410308
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_07.uaddr32,0xF341030C);	//0xF341030C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_08.uaddr32,0xF3410310);//0xF3410310
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_09.uaddr32,0xF3410314);//0xF3410314
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0a.uaddr32,0xF3410318);//0xF3410318
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0b.uaddr32,0xF341031C);//0xF341031C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0c.uaddr32,0xF3410320);//0xF3410320
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0d.uaddr32,0xF3410324);//0xF3410324
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0e.uaddr32,0xF3410328);//0xF3410328
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_0f.uaddr32,0xF341032C);//0xF341032C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_10.uaddr32,0xF3410330);//0xF3410330
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_11.uaddr32,0xF3410334);//0xF3410334
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_12.uaddr32,0xF3410338);//0xF3410338
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_13.uaddr32,0xF341033C);//0xF341033C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_14.uaddr32,0xF3410340);//0xF3410340
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_15.uaddr32,0xF3410344);//0xF3410344
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_16.uaddr32,0xF3410348);//0xF3410348
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_17.uaddr32,0xF341034C);//0xF341034C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_18.uaddr32,0xF3410350);//0xF3410350
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_19.uaddr32,0xF3410354);//0xF3410354
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1a.uaddr32,0xF3410358);//0xF3410358
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1b.uaddr32,0xF341035C);//0xF341035C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1c.uaddr32,0xF3410360);//0xF3410360
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1d.uaddr32,0xF3410364);//0xF3410364
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1e.uaddr32,0xF3410368);//0xF3410368
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dctp_ctrl_1f.uaddr32,0xF341036C);//0xF341036C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_00.uaddr32,0xF3410370);//0xF3410370
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_01_c0.uaddr32,0xF3410374);	//0xF3410374
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_02_c0.uaddr32,0xF3410378);	//0xF3410378
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_03_c0.uaddr32,0xF341037C);	//0xF341037C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_04_c0.uaddr32,0xF3410380);	//0xF3410380
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_05_c0.uaddr32,0xF3410384);	//0xF3410384
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_01_c1.uaddr32,0xF3410388);	//0xF3410388
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_02_c1.uaddr32,0xF341038C);	//0xF341038C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_03_c1.uaddr32,0xF3410390);	//0xF3410390
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_04_c1.uaddr32,0xF3410394);	//0xF3410394
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core0_nntg_ctrl_05_c1.uaddr32,0xF3410398);	//0xF3410398
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_01_c0.uaddr32,0xF341039C);	//0xF341039C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_02_c0.uaddr32,0xF34103A0);	//0xF34103A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_03_c0.uaddr32,0xF34103A4);	//0xF34103A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_04_c0.uaddr32,0xF34103A8);	//0xF34103A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_05_c0.uaddr32,0xF34103AC);	//0xF34103AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_01_c1.uaddr32,0xF34103B0);	//0xF34103B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_02_c1.uaddr32,0xF34103B4);	//0xF34103B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_03_c1.uaddr32,0xF34103B8);	//0xF34103B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_04_c1.uaddr32,0xF34103BC);	//0xF34103BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_core1_nntg_ctrl_05_c1.uaddr32,0xF34103C0);	//0xF34103C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_06.uaddr32,0xF34103C4);	//0xF34103C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_07.uaddr32,0xF34103C8);	//0xF34103C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_08.uaddr32,0xF34103CC);	//0xF34103CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_09.uaddr32,0xF34103D0);	//0xF34103D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0a.uaddr32,0xF34103D4);	//0xF34103D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0b.uaddr32,0xF34103D8);	//0xF34103D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0c.uaddr32,0xF34103DC);	//0xF34103DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0d.uaddr32,0xF34103E0);	//0xF34103E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0e.uaddr32,0xF34103E4);	//0xF34103E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_0f.uaddr32,0xF34103E8);	//0xF34103E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_nntg_ctrl_10.uaddr32,0xF34103EC);	//0xF34103EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_00.uaddr32,0xF34103F0);	//0xF34103F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_01.uaddr32,0xF34103F4);	//0xF34103F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_02.uaddr32,0xF34103F8);	//0xF34103F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_03.uaddr32,0xF34103FC);	//0xF34103FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_04.uaddr32,0xF3410400);	//0xF3410400
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_05.uaddr32,0xF3410404);	//0xF3410404
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_06.uaddr32,0xF3410408);	//0xF3410408
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_07.uaddr32,0xF341040C);	//0xF341040C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_08.uaddr32,0xF3410410);	//0xF3410410
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_09.uaddr32,0xF3410414);	//0xF3410414
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0a.uaddr32,0xF3410418);	//0xF3410418
		PE_CHPI_TBL0_O26F22_QWr(res.shp_psp_ctrl_00.uaddr32,0xF3410420);	    //0xF3410420
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0b.uaddr32,0xF3410424);	//0xF3410424
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dp_sum_ctrl_0c.uaddr32,0xF3410428);	//0xF3410428
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_00.uaddr32,0xF3410460);	//0xF3410460
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_01.uaddr32,0xF3410464);	//0xF3410464
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_region_text_02.uaddr32,0xF3410468);	//0xF3410468
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_00.uaddr32,0xF341046C);	//0xF341046C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_01.uaddr32,0xF3410470);	//0xF3410470
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_02.uaddr32,0xF3410474);	//0xF3410474
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_03.uaddr32,0xF3410478);	//0xF3410478
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_04.uaddr32,0xF341047C);	//0xF341047C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_05.uaddr32,0xF3410480);	//0xF3410480
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_06.uaddr32,0xF3410484);	//0xF3410484
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_07.uaddr32,0xF3410488);	//0xF3410488
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_08.uaddr32,0xF341048C);	//0xF341048C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_09.uaddr32,0xF3410490);	//0xF3410490
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0a.uaddr32,0xF3410494);	//0xF3410494
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0b.uaddr32,0xF3410498);	//0xF3410498
		PE_CHPI_TBL0_O26F22_QWr(res.shp_fd_tmap_temp_0c.uaddr32,0xF341049C);	//0xF341049C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_00.uaddr32,0xF34104A0);	//0xF34104A0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_01.uaddr32,0xF34104A4);	//0xF34104A4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_02.uaddr32,0xF34104A8);	//0xF34104A8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_03.uaddr32,0xF34104AC);	//0xF34104AC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_04.uaddr32,0xF34104B0);	//0xF34104B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_05.uaddr32,0xF34104B4);	//0xF34104B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_06.uaddr32,0xF34104B8);	//0xF34104B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_07.uaddr32,0xF34104BC);	//0xF34104BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_08.uaddr32,0xF34104C0);	//0xF34104C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_09.uaddr32,0xF34104C4);	//0xF34104C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0a.uaddr32,0xF34104C8);	//0xF34104C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0b.uaddr32,0xF34104CC);	//0xF34104CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0c.uaddr32,0xF34104D0);	//0xF34104D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0d.uaddr32,0xF34104D4);	//0xF34104D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0e.uaddr32,0xF34104D8);	//0xF34104D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_0f.uaddr32,0xF34104DC);	//0xF34104DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_10.uaddr32,0xF34104E0);	//0xF34104E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_11.uaddr32,0xF34104E4);	//0xF34104E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_12.uaddr32,0xF34104E8);	//0xF34104E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_13.uaddr32,0xF34104EC);	//0xF34104EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_14.uaddr32,0xF34104F0);	//0xF34104F0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_15.uaddr32,0xF34104F4);	//0xF34104F4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_16.uaddr32,0xF34104F8);	//0xF34104F8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_17.uaddr32,0xF34104FC);	//0xF34104FC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_18.uaddr32,0xF3410500);	//0xF3410500
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_19.uaddr32,0xF3410504);	//0xF3410504
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1a.uaddr32,0xF3410508);	//0xF3410508
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1b.uaddr32,0xF341050C);	//0xF341050C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1c.uaddr32,0xF3410510);	//0xF3410510
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1d.uaddr32,0xF3410514);	//0xF3410514
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1e.uaddr32,0xF3410518);	//0xF3410518
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_1f.uaddr32,0xF341051C);	//0xF341051C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_dj_ctrl_20.uaddr32,0xF3410520);	//0xF3410520
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_00.uaddr32,0xF3410560);	//0xF3410560
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_01.uaddr32,0xF3410564);	//0xF3410564
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_02.uaddr32,0xF3410568);	//0xF3410568
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_03.uaddr32,0xF341056C);	//0xF341056C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_04.uaddr32,0xF3410570);	//0xF3410570
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_05.uaddr32,0xF3410574);	//0xF3410574
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_06.uaddr32,0xF3410578);	//0xF3410578
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_07.uaddr32,0xF341057C);	//0xF341057C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_08.uaddr32,0xF3410580);	//0xF3410580
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_09.uaddr32,0xF3410584);	//0xF3410584
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0a.uaddr32,0xF3410588);	//0xF3410588
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0b.uaddr32,0xF341058C);	//0xF341058C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0c.uaddr32,0xF3410590);	//0xF3410590
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0d.uaddr32,0xF3410594);	//0xF3410594
		PE_CHPI_TBL0_O26F22_QWr(res.shp_chroma_ctrl_0e.uaddr32,0xF3410598);	//0xF3410598
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_00.uaddr32,0xF34105B0);	//0xF34105B0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_01.uaddr32,0xF34105B4);	//0xF34105B4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_02.uaddr32,0xF34105B8);	//0xF34105B8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_flick_ctrl_03.uaddr32,0xF34105BC);	//0xF34105BC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_00.uaddr32,0xF34105C0);	//0xF34105C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_01.uaddr32,0xF34105C4);	//0xF34105C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_02.uaddr32,0xF34105C8);	//0xF34105C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_03.uaddr32,0xF34105CC);	//0xF34105CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_04.uaddr32,0xF34105D0);	//0xF34105D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_05.uaddr32,0xF34105D4);	//0xF34105D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_blur_ctrl_06.uaddr32,0xF34105D8);	//0xF34105D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_00.uaddr32,0xF34105E0);	//0xF34105E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_01.uaddr32,0xF34105E4);	//0xF34105E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_02.uaddr32,0xF34105E8);	//0xF34105E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_frc_halo_ctrl_03.uaddr32,0xF34105EC);	//0xF34105EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_00.uaddr32,0xF3410620);	//0xF3410620
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_01.uaddr32,0xF3410624);	//0xF3410624
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_02.uaddr32,0xF3410628);	//0xF3410628
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_03.uaddr32,0xF341062C);	//0xF341062C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_04.uaddr32,0xF3410630);	//0xF3410630
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_05.uaddr32,0xF3410634);	//0xF3410634
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_06.uaddr32,0xF3410638);	//0xF3410638
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_07.uaddr32,0xF341063C);	//0xF341063C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_08.uaddr32,0xF3410640);	//0xF3410640
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_09.uaddr32,0xF3410644);	//0xF3410644
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0a.uaddr32,0xF3410648);	//0xF3410648
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0b.uaddr32,0xF341064C);	//0xF341064C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_gain_ctrl_0c.uaddr32,0xF3410650);	//0xF3410650
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_00.uaddr32,0xF3410660);	//0xF3410660
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_01.uaddr32,0xF3410664);	//0xF3410664
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_02.uaddr32,0xF3410668);	//0xF3410668
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_03.uaddr32,0xF341066C);	//0xF341066C
		PE_CHPI_TBL0_O26F22_QWr(res.shp_motion_prot_ctrl_04.uaddr32,0xF3410670);	//0xF3410670
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_00.uaddr32,0xF34106C0);	//0xF34106C0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_01.uaddr32,0xF34106C4);	//0xF34106C4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_02.uaddr32,0xF34106C8);	//0xF34106C8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_03.uaddr32,0xF34106CC);	//0xF34106CC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_04.uaddr32,0xF34106D0);	//0xF34106D0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_05.uaddr32,0xF34106D4);	//0xF34106D4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_06.uaddr32,0xF34106D8);	//0xF34106D8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_07.uaddr32,0xF34106DC);	//0xF34106DC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_08.uaddr32,0xF34106E0);	//0xF34106E0
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_09.uaddr32,0xF34106E4);	//0xF34106E4
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0a.uaddr32,0xF34106E8);	//0xF34106E8
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0b.uaddr32,0xF34106EC);	//0xF34106EC
		PE_CHPI_TBL0_O26F22_QWr(res.shp_obj_ctrl_0c.uaddr32,0xF34106F0);	//0xF34106F0
		PE_CHPI_TBL0_O26F22_QWr(res.sr_merge_blend_00.uaddr32,0xF1402950);
		PE_CHPI_TBL0_O26F22_QWr(cti.cti_ctrl_0.uaddr32,0xF200058C);
		PE_CHPI_TBL0_O26F22_QWr(cti.cti_ctrl_1.uaddr32,0xF2000590);
		PE_CHPI_TBL0_O26F22_QWr(cti.reg_cti_ctrl_2.uaddr32,0xF20007A0);
		PE_CHPI_TBL0_O26F22_QWr(cti.reg_cti_ctrl_3.uaddr32,0xF20007A4);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_00.uaddr32,0xF34105A0);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_01.uaddr32,0xF34105A4);
		PE_CHPI_TBL0_O26F22_QWr(cti.shp_cti_ctrl_02.uaddr32,0xF34105A8);

		/* init */
		PE_CHPI_SHP_HW_O26F22_SetResDefault(PE_CHPI_SHP_O26F22_RES_HD);
		PE_CHPI_SHP_HW_O26F22_SetCtiDefault(PE_CHPI_SHP_O26F22_CTI_HD);
		PE_CHPI_TBL0_O26F22_QWr(res.sr_merge_blend_00.udata32,0x01000021);//init data 0x01000021 

		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmCmnInitDb */
		/* PE_CHPI_SHP_UI_SQM_O26F22_T              sqm0;//11 */
		PE_CHPI_TBL0_O26F22_QWr(sqm0.ui32,0);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm0.data32[i],sqm_shp_vsd_cmn_init_o26[i]);
		}
		PE_CHPI_TBL0_O26F22_QWr(sqm0.cnt32,0);

		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmDetailInitDb */
		/* PE_CHPI_SHP_CMN_SQM_O26F22_T             sqm1;//12 */
		PE_CHPI_TBL0_O26F22_QWr(sqm1.ui32,0);
		for (i=0; i<51; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm1.data32[i],sqm_shp_vsd_dtl_init_o26[i]);
		}
		PE_CHPI_TBL0_O26F22_QWr(sqm1.cnt32,0);

		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM0);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM1);

		PE_INF_HW_O26_BACKUP_CHPI1("[TBL][SHP]done(resume:%d)",pstParams->resume_mode);
	}while(0);
	#endif
	return ret;
}
#else
int PE_CHPI_SHP_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams)
{
	 PE_PRINT_NOTI("not supported\n");
	 return RET_ERROR;
}
#endif

int PE_CHPI_SHP_HW_O26F22_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 i;
	LX_PE_SHP1_ALL_CMN_T *pp;
	PE_RES_HW_PARAM_DATA_O26F22_T *p_res = &_g_pe_res_hw_param_data_o26f22;
	PE_CTI_HW_PARAM_DATA_O26F22_T *p_cti = &_g_pe_cti_hw_param_data_o26f22;
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_res->reg_user.data);
		CHECK_KNULL(p_res->reg_mask.data);
		CHECK_KNULL(p_cti->reg_user.data);
		CHECK_KNULL(p_cti->reg_mask.data);
		pp=(LX_PE_SHP1_ALL_CMN_T *)pstParams;

		/* set tbl */
		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1d.reg_dctp_gain,GET_BITS(pp->shp_ui_main_vsd[0],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_00.reg_tgen_master_gain,GET_BITS(pp->shp_ui_main_vsd[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_1e.reg_dj_soft_g1_mul,GET_BITS(pp->shp_ui_main_vsd[2],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_1f.reg_dj_soft_g2_mul,GET_BITS(pp->shp_ui_main_vsd[3],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_0e.reg_nntg_denoise_gain,GET_BITS(pp->shp_ui_main_vsd[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_der_ctrl_00.reg_derh_csft_gain,GET_BITS(pp->shp_ui_main_vsd[5],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_01.reg_mp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_01.reg_sp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_01.reg_mp_im_gain_v,GET_BITS(pp->shp_ui_main_vsd[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sti_ctrl_00.reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_00.reg_cti_gain,GET_BITS(pp->shp_ui_main_vsd[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_y_gain,GET_BITS(pp->shp_ui_main_vsd[13],0,4));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_c_gain,GET_BITS(pp->shp_ui_main_vsd[14],0,4));
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_00.reg_obj_sel_bit,						GET_BITS(pp->shp_face_obj_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[1],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[5],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[6],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[7],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[13],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[14],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[15],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[16],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[17],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[18],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[19],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[20],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[21],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[22],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[23],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[24],0,8));

		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_der_ctrl_01.reg_derh_edge_y_filter_en,GET_BITS(pp->shp_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_der_ctrl_01.reg_derh_bflt_tap_size,GET_BITS(pp->shp_cmn_vsd[1],0,3));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_00.reg_mp_shp_en,GET_BITS(pp->shp_cmn_vsd[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_00.reg_sp_shp_en,GET_BITS(pp->shp_cmn_vsd[3],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_01.reg_mp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[4],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_01.reg_mp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[5],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_01.reg_sp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[6],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_01.reg_sp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[7],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_esf_ctrl_00.reg_esf_en,GET_BITS(pp->shp_cmn_vsd[8],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_esf_ctrl_01.reg_esf_min_ratio,GET_BITS(pp->shp_cmn_vsd[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_esf_ctrl_01.reg_esf_base,GET_BITS(pp->shp_cmn_vsd[10],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_esf_ctrl_01.reg_esf_max_clip,GET_BITS(pp->shp_cmn_vsd[11],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_00.reg_dctp_en,GET_BITS(pp->shp_cmn_vsd[12],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1e.reg_dctp_coring_en,GET_BITS(pp->shp_cmn_vsd[13],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1e.reg_dctp_coring_mode,GET_BITS(pp->shp_cmn_vsd[14],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_00.reg_tgen_on_off,GET_BITS(pp->shp_cmn_vsd[15],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0a.reg_tgen_coring_en,GET_BITS(pp->shp_cmn_vsd[16],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0a.reg_tgen_coring_mode,GET_BITS(pp->shp_cmn_vsd[17],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_00.reg_nntg_en,GET_BITS(pp->shp_cmn_vsd[18],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_0f.reg_nntg_coring_en,GET_BITS(pp->shp_cmn_vsd[19],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_0f.reg_nntg_coring_mode,GET_BITS(pp->shp_cmn_vsd[20],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en,GET_BITS(pp->shp_cmn_vsd[21],0,1));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_00.reg_cti_en,GET_BITS(pp->shp_cmn_vsd[22],0,1));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_02.reg_cti_ycm_en,GET_BITS(pp->shp_cmn_vsd[23],0,1));
		PE_CHPI_TBL0_O26F22_Wr(cti.shp_cti_ctrl_00.reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_00.reg_dj_edf_en,GET_BITS(pp->shp_djg_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_00.reg_dj_edge_adaptive_en,GET_BITS(pp->shp_djg_vsd[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_00.reg_dj_soft_en,GET_BITS(pp->shp_djg_vsd[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_03.reg_dj_edge_min,GET_BITS(pp->shp_djg_vsd[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_03.reg_dj_edge_mul,GET_BITS(pp->shp_djg_vsd[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_00.reg_dj_center_blur_mode,GET_BITS(pp->shp_djg_vsd[5],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_00.reg_dj_n_avg_mode,GET_BITS(pp->shp_djg_vsd[6],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dj_ctrl_01.reg_dj_n_avg_gain,GET_BITS(pp->shp_djg_vsd[7],0,8));

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x0,GET_BITS(pp->shp_map_cmn_vsd[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x1,GET_BITS(pp->shp_map_cmn_vsd[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y0,GET_BITS(pp->shp_map_cmn_vsd[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y1,GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_11.reg_fd_soft_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[6],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_11.reg_fd_soft_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y3,GET_BITS(pp->shp_map_cmn_vsd[8],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y2,GET_BITS(pp->shp_map_cmn_vsd[9],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y1,GET_BITS(pp->shp_map_cmn_vsd[10],0,6));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_fd_ctrl_14.reg_fd_soft_score_y0,GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_05.reg_mp_gb_en,GET_BITS(pp->shp_balance_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_05.reg_mp_gb_mode,GET_BITS(pp->shp_balance_vsd[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_05.reg_mp_gb_y1,GET_BITS(pp->shp_balance_vsd[2],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_06.reg_mp_gb_y2,GET_BITS(pp->shp_balance_vsd[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_06.reg_mp_gb_y3,GET_BITS(pp->shp_balance_vsd[4],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_05.reg_sp_gb_en,GET_BITS(pp->shp_balance_vsd[5],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_05.reg_sp_gb_mode,GET_BITS(pp->shp_balance_vsd[6],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_05.reg_sp_gb_y1,GET_BITS(pp->shp_balance_vsd[7],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_06.reg_sp_gb_y2,GET_BITS(pp->shp_balance_vsd[8],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_06.reg_sp_gb_y3,GET_BITS(pp->shp_balance_vsd[9],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_00.reg_lc_shp_en,GET_BITS(pp->shp_balance_vsd[10],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_00.reg_lc_gb_en,GET_BITS(pp->shp_balance_vsd[11],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_01.reg_lc_gb_y1,GET_BITS(pp->shp_balance_vsd[12],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_01.reg_lc_gb_y2,GET_BITS(pp->shp_balance_vsd[13],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_02.reg_lc_gb_y3,GET_BITS(pp->shp_balance_vsd[14],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_00.reg_lc_center_target,GET_BITS(pp->shp_balance_vsd[15],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_00.reg_lc_center_gain,GET_BITS(pp->shp_balance_vsd[16],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_00.reg_lc_local_gain,GET_BITS(pp->shp_balance_vsd[17],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y0,GET_BITS(pp->shp_balance_vsd[18],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y1,GET_BITS(pp->shp_balance_vsd[19],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_08.reg_mp_lum1_y2,GET_BITS(pp->shp_balance_vsd[20],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_09.reg_mp_lum2_y0,GET_BITS(pp->shp_balance_vsd[21],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0a.reg_mp_lum2_y1,GET_BITS(pp->shp_balance_vsd[22],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0a.reg_mp_lum2_y2,GET_BITS(pp->shp_balance_vsd[23],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y0,GET_BITS(pp->shp_balance_vsd[24],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y1,GET_BITS(pp->shp_balance_vsd[25],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_08.reg_sp_lum1_y2,GET_BITS(pp->shp_balance_vsd[26],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_09.reg_sp_lum2_y0,GET_BITS(pp->shp_balance_vsd[27],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0a.reg_sp_lum2_y1,GET_BITS(pp->shp_balance_vsd[28],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0a.reg_sp_lum2_y2,GET_BITS(pp->shp_balance_vsd[29],0,8));
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_00.reg_ptiv_enable,GET_BITS(pp->shp_ti_cmn_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_00.reg_ptiv_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_00.reg_ptiv_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[2],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_00.reg_ptiv_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_01.reg_ptih_enable,GET_BITS(pp->shp_ti_cmn_vsd[4],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_01.reg_ptih_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[5],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_01.reg_ptih_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[6],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_01.reg_ptih_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sti_ctrl_00.reg_sti_enable,GET_BITS(pp->shp_ti_cmn_vsd[8],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sti_ctrl_00.reg_sti_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[9],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sti_ctrl_00.reg_sti_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[10],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sti_ctrl_00.reg_sti_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_snr_ctrl_00.reg_snr_blur_en,GET_BITS(pp->shp_ti_cmn_vsd[12],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_snr_ctrl_00.reg_snr_blur_sel,GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_chroma_ctrl_00.reg_color_region_en,GET_BITS(pp->shp_chroma_vsd[0],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_chroma_ctrl_00.reg_chr_protection_en,GET_BITS(pp->shp_chroma_vsd[1],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_chroma_ctrl_00.reg_chr_compensation_en,GET_BITS(pp->shp_chroma_vsd[2],0,1));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_chroma_ctrl_0d.reg_chr_gain_r0_gain,GET_BITS(pp->shp_chroma_vsd[3],0,8));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_chroma_ctrl_0d.reg_chr_gain_r1_gain,GET_BITS(pp->shp_chroma_vsd[4],0,8));
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[0],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[1],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[14],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[15],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[2],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[3],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[16],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[17],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[4],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[5],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[18],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[19],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[6],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[7],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[20],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[21],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[8],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[9],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[22],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[23],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[10],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[11],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[24],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[25],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[12],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[13],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[26],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[27],0,7));
		PE_CHPI_TBL0_O26F22_Wr(res.sr_merge_blend_00.reg_blend_amp_weight,GET_BITS(pp->shp_dnn_sr_vsd[0],0,12));

		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dctp_ctrl_1d.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_1e.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_1f.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_nntg_ctrl_0e.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_der_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_der_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(cti.shp_cti_ctrl_02.udata32);
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dp_sum_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dp_sum_ctrl_0a.udata32);
		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_der_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_esf_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_esf_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dctp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dctp_ctrl_1e.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_tgen_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_nntg_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_nntg_ctrl_0f.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_motion_prot_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(cti.shp_cti_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(cti.shp_cti_ctrl_00.udata32);
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_03.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dj_ctrl_01.udata32);

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_fd_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_fd_ctrl_0d.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_fd_ctrl_11.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_fd_ctrl_14.udata32);

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_05.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_06.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_05.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_06.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_lc_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_lc_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_08.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_08.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_0a.udata32);
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_pti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_pti_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_snr_ctrl_00.udata32);
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_chroma_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_chroma_ctrl_0d.udata32);
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_mp_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_sp_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_pti_ctrl_03.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_lc_ctrl_04.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_dctp_ctrl_1f.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_tgen_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_nntg_ctrl_10.udata32);
		/*shp_dnn_sr_vsd - there is no default table*/
		PE_CHPI_TBL0_O26F22_WrFL(res.sr_merge_blend_00.udata32);

		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmCmnUserDb */
		/* PE_CHPI_SHP_UI_SQM_O26F22_T              sqm0;//11 */
		PE_CHPI_TBL0_O26F22_QWr(sqm0.ui32,pp->shp_val);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm0.data32[i],pp->shp_ui_sqm_vsd[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm0.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(sqm0.cnt32,i);

		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmDetailUserDb */
		/* PE_CHPI_SHP_CMN_SQM_O26F22_T             sqm1;//12 */
		PE_CHPI_TBL0_O26F22_QWr(sqm1.ui32,pp->shp_val);
		for (i=0; i<71; i++)
		{
			PE_CHPI_TBL0_O26F22_QWr(sqm1.data32[i],pp->shp_sqm_cmn_vsd[i]);
		}
		i = PE_CHPI_TBL0_O26F22_Rd(sqm1.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O26F22_QWr(sqm1.cnt32,i);

		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_RES);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_CTI);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM0);
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_SQM1);

		/* set user */
		/*shp_ui_main_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1d.reg_dctp_gain,GET_BITS(pp->shp_ui_main_vsd[0],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_00.reg_tgen_master_gain,GET_BITS(pp->shp_ui_main_vsd[1],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_1e.reg_dj_soft_g1_mul,GET_BITS(pp->shp_ui_main_vsd[2],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_1f.reg_dj_soft_g2_mul,GET_BITS(pp->shp_ui_main_vsd[3],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_0e.reg_nntg_denoise_gain,GET_BITS(pp->shp_ui_main_vsd[4],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_der_ctrl_00.reg_derh_csft_gain,GET_BITS(pp->shp_ui_main_vsd[5],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_der_ctrl_02.reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_der_ctrl_02.reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_01.reg_mp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[8],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_01.reg_sp_im_gain_h,GET_BITS(pp->shp_ui_main_vsd[9],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_01.reg_mp_im_gain_v,GET_BITS(pp->shp_ui_main_vsd[10],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sti_ctrl_00.reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_00.reg_cti_gain,GET_BITS(pp->shp_ui_main_vsd[12],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_y_gain,GET_BITS(pp->shp_ui_main_vsd[13],0,4));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_c_gain,GET_BITS(pp->shp_ui_main_vsd[14],0,4));
		/*shp_face_obj_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_00.reg_obj_sel_bit,				GET_BITS(pp->shp_face_obj_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_a_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[1],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_a_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[2],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_a_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[3],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_09.reg_obj_master_gain_a_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[4],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_a_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[5],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_a_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[6],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_a_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[7],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0a.reg_obj_master_gain_a_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[8],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[9],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[10],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[11],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[12],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[13],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[14],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[15],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[16],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[17],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[18],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[19],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[20],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[21],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[22],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[23],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[24],0,8));
		/*shp_cmn_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_der_ctrl_01.reg_derh_edge_y_filter_en,GET_BITS(pp->shp_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_der_ctrl_01.reg_derh_bflt_tap_size,GET_BITS(pp->shp_cmn_vsd[1],0,3));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_00.reg_mp_shp_en,GET_BITS(pp->shp_cmn_vsd[2],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_00.reg_sp_shp_en,GET_BITS(pp->shp_cmn_vsd[3],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_01.reg_mp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[4],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_01.reg_mp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[5],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_01.reg_sp_im_os_gain,GET_BITS(pp->shp_cmn_vsd[6],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_01.reg_sp_im_us_gain,GET_BITS(pp->shp_cmn_vsd[7],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_esf_ctrl_00.reg_esf_en,GET_BITS(pp->shp_cmn_vsd[8],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_esf_ctrl_01.reg_esf_min_ratio,GET_BITS(pp->shp_cmn_vsd[9],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_esf_ctrl_01.reg_esf_base,GET_BITS(pp->shp_cmn_vsd[10],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_esf_ctrl_01.reg_esf_max_clip,GET_BITS(pp->shp_cmn_vsd[11],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_00.reg_dctp_en,GET_BITS(pp->shp_cmn_vsd[12],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1e.reg_dctp_coring_en,GET_BITS(pp->shp_cmn_vsd[13],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1e.reg_dctp_coring_mode,GET_BITS(pp->shp_cmn_vsd[14],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_00.reg_tgen_on_off,GET_BITS(pp->shp_cmn_vsd[15],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0a.reg_tgen_coring_en,GET_BITS(pp->shp_cmn_vsd[16],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0a.reg_tgen_coring_mode,GET_BITS(pp->shp_cmn_vsd[17],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_00.reg_nntg_en,GET_BITS(pp->shp_cmn_vsd[18],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_0f.reg_nntg_coring_en,GET_BITS(pp->shp_cmn_vsd[19],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_0f.reg_nntg_coring_mode,GET_BITS(pp->shp_cmn_vsd[20],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en,GET_BITS(pp->shp_cmn_vsd[21],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_00.reg_cti_en,GET_BITS(pp->shp_cmn_vsd[22],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_02.reg_cti_ycm_en,GET_BITS(pp->shp_cmn_vsd[23],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_cti,shp_cti_ctrl_00.reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
		/*shp_djg_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_00.reg_dj_edf_en,GET_BITS(pp->shp_djg_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_00.reg_dj_edge_adaptive_en,GET_BITS(pp->shp_djg_vsd[1],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_00.reg_dj_soft_en,GET_BITS(pp->shp_djg_vsd[2],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_03.reg_dj_edge_min,GET_BITS(pp->shp_djg_vsd[3],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_03.reg_dj_edge_mul,GET_BITS(pp->shp_djg_vsd[4],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_00.reg_dj_center_blur_mode,GET_BITS(pp->shp_djg_vsd[5],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_00.reg_dj_n_avg_mode,GET_BITS(pp->shp_djg_vsd[6],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dj_ctrl_01.reg_dj_n_avg_gain,GET_BITS(pp->shp_djg_vsd[7],0,8));

		/*shp_map_cmn_vsd */
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_x0,GET_BITS(pp->shp_map_cmn_vsd[2],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_x1,GET_BITS(pp->shp_map_cmn_vsd[3],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_y0,GET_BITS(pp->shp_map_cmn_vsd[4],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_0d.reg_fd_mnr_gain_y1,GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_11.reg_fd_soft_gain_t_en,GET_BITS(pp->shp_map_cmn_vsd[6],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_11.reg_fd_soft_gain_e_en,GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y3,GET_BITS(pp->shp_map_cmn_vsd[8],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y2,GET_BITS(pp->shp_map_cmn_vsd[9],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y1,GET_BITS(pp->shp_map_cmn_vsd[10],0,6));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_fd_ctrl_14.reg_fd_soft_score_y0,GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

		/*shp_balance_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_en,GET_BITS(pp->shp_balance_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_mode,GET_BITS(pp->shp_balance_vsd[1],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_05.reg_mp_gb_y1,GET_BITS(pp->shp_balance_vsd[2],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_06.reg_mp_gb_y2,GET_BITS(pp->shp_balance_vsd[3],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_06.reg_mp_gb_y3,GET_BITS(pp->shp_balance_vsd[4],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_en,GET_BITS(pp->shp_balance_vsd[5],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_mode,GET_BITS(pp->shp_balance_vsd[6],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_05.reg_sp_gb_y1,GET_BITS(pp->shp_balance_vsd[7],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_06.reg_sp_gb_y2,GET_BITS(pp->shp_balance_vsd[8],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_06.reg_sp_gb_y3,GET_BITS(pp->shp_balance_vsd[9],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_00.reg_lc_shp_en,GET_BITS(pp->shp_balance_vsd[10],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_00.reg_lc_gb_en,GET_BITS(pp->shp_balance_vsd[11],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_01.reg_lc_gb_y1,GET_BITS(pp->shp_balance_vsd[12],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_01.reg_lc_gb_y2,GET_BITS(pp->shp_balance_vsd[13],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_02.reg_lc_gb_y3,GET_BITS(pp->shp_balance_vsd[14],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_00.reg_lc_center_target,GET_BITS(pp->shp_balance_vsd[15],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_00.reg_lc_center_gain,GET_BITS(pp->shp_balance_vsd[16],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_00.reg_lc_local_gain,GET_BITS(pp->shp_balance_vsd[17],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y0,GET_BITS(pp->shp_balance_vsd[18],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y1,GET_BITS(pp->shp_balance_vsd[19],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_08.reg_mp_lum1_y2,GET_BITS(pp->shp_balance_vsd[20],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_09.reg_mp_lum2_y0,GET_BITS(pp->shp_balance_vsd[21],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0a.reg_mp_lum2_y1,GET_BITS(pp->shp_balance_vsd[22],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0a.reg_mp_lum2_y2,GET_BITS(pp->shp_balance_vsd[23],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y0,GET_BITS(pp->shp_balance_vsd[24],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y1,GET_BITS(pp->shp_balance_vsd[25],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_08.reg_sp_lum1_y2,GET_BITS(pp->shp_balance_vsd[26],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_09.reg_sp_lum2_y0,GET_BITS(pp->shp_balance_vsd[27],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0a.reg_sp_lum2_y1,GET_BITS(pp->shp_balance_vsd[28],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0a.reg_sp_lum2_y2,GET_BITS(pp->shp_balance_vsd[29],0,8));
		/*shp_ti_cmn_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_00.reg_ptiv_enable,GET_BITS(pp->shp_ti_cmn_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_00.reg_ptiv_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[1],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_00.reg_ptiv_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[2],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_00.reg_ptiv_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_01.reg_ptih_enable,GET_BITS(pp->shp_ti_cmn_vsd[4],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_01.reg_ptih_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[5],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_01.reg_ptih_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[6],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_01.reg_ptih_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sti_ctrl_00.reg_sti_enable,GET_BITS(pp->shp_ti_cmn_vsd[8],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sti_ctrl_00.reg_sti_ti_mode,GET_BITS(pp->shp_ti_cmn_vsd[9],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sti_ctrl_00.reg_sti_mm_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[10],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sti_ctrl_00.reg_sti_avg_tap_size,GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_snr_ctrl_00.reg_snr_blur_en,GET_BITS(pp->shp_ti_cmn_vsd[12],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_snr_ctrl_00.reg_snr_blur_sel,GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
		/*shp_chroma_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_chroma_ctrl_00.reg_color_region_en,GET_BITS(pp->shp_chroma_vsd[0],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_chroma_ctrl_00.reg_chr_protection_en,GET_BITS(pp->shp_chroma_vsd[1],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_chroma_ctrl_00.reg_chr_compensation_en,GET_BITS(pp->shp_chroma_vsd[2],0,1));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_chroma_ctrl_0d.reg_chr_gain_r0_gain,GET_BITS(pp->shp_chroma_vsd[3],0,8));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_chroma_ctrl_0d.reg_chr_gain_r1_gain,GET_BITS(pp->shp_chroma_vsd[4],0,8));
		/*shp_ee_vsd*/
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[0],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[1],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[14],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_mp_ctrl_0c.reg_mp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[15],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[2],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[3],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[16],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_sp_ctrl_0c.reg_sp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[17],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[4],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[5],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[18],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_pti_ctrl_03.reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[19],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[6],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[7],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[20],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_lc_ctrl_04.reg_lc_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[21],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[8],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[9],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[22],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[23],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[10],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[11],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[24],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[25],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b,GET_BITS(pp->shp_ee_vsd[12],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w,GET_BITS(pp->shp_ee_vsd[13],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b,GET_BITS(pp->shp_ee_vsd[26],0,7));
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w,GET_BITS(pp->shp_ee_vsd[27],0,7));
	}while(0);
	#endif
	return ret;
}
int PE_CHPI_SHP_HW_O26F22_GetCtrl(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 i;
	LX_PE_SHP1_ALL_CMN_T stParams;
	LX_PE_SHP1_ALL_CMN_T *pp;
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	UINT32 *pd32;
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		pp=&stParams;
		memset(pp,0,sizeof(LX_PE_SHP1_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized

		/* set tbl */
		/* read from phys to shdw */
		/*shp_ui_main_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dctp_ctrl_1d.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_1e.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_1f.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_nntg_ctrl_0e.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_der_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_der_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(cti.shp_cti_ctrl_02.udata32);
		/*shp_face_obj_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_obj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_obj_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_obj_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_obj_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_obj_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dp_sum_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dp_sum_ctrl_0a.udata32);
		/*shp_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_der_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_esf_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_esf_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dctp_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dctp_ctrl_1e.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_tgen_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_tgen_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_nntg_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_nntg_ctrl_0f.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_motion_prot_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(cti.shp_cti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(cti.shp_cti_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(cti.shp_cti_ctrl_00.udata32);
		/*shp_djg_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_03.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dj_ctrl_01.udata32);

		/*shp_map_cmn_vsd */
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_fd_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_fd_ctrl_0d.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_fd_ctrl_11.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_fd_ctrl_14.udata32);

		/*shp_balance_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_05.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_06.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_05.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_06.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_lc_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_lc_ctrl_02.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_lc_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_08.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_0a.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_08.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_09.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_0a.udata32);
		/*shp_ti_cmn_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_pti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_pti_ctrl_01.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sti_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_snr_ctrl_00.udata32);
		/*shp_chroma_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_chroma_ctrl_00.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_chroma_ctrl_0d.udata32);
		/*shp_ee_vsd*/
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_mp_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_sp_ctrl_0c.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_pti_ctrl_03.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_lc_ctrl_04.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_dctp_ctrl_1f.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_tgen_ctrl_0b.udata32);
		PE_CHPI_TBL0_O26F22_RdFL(res.shp_nntg_ctrl_10.udata32);
		/*shp_ui_main_vsd*/
		pp->shp_ui_main_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1d.reg_dctp_gain);
		pp->shp_ui_main_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_00.reg_tgen_master_gain);
		pp->shp_ui_main_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_1e.reg_dj_soft_g1_mul);
		pp->shp_ui_main_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_1f.reg_dj_soft_g2_mul);
		pp->shp_ui_main_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_0e.reg_nntg_denoise_gain);
		pp->shp_ui_main_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_der_ctrl_00.reg_derh_csft_gain);
		pp->shp_ui_main_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_w);
		pp->shp_ui_main_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_der_ctrl_02.reg_derh_edge_filter_gain_b);
		pp->shp_ui_main_vsd[8]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_01.reg_mp_im_gain_h);
		pp->shp_ui_main_vsd[9]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_01.reg_sp_im_gain_h);
		pp->shp_ui_main_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_01.reg_mp_im_gain_v);
		pp->shp_ui_main_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sti_ctrl_00.reg_sti_master_gain);
		pp->shp_ui_main_vsd[12]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_00.reg_cti_gain);
		pp->shp_ui_main_vsd[13]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_y_gain);
		pp->shp_ui_main_vsd[14]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_c_gain);
		/*shp_face_obj_vsd*/
		pp->shp_face_obj_vsd[0] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_00.reg_obj_sel_bit);
		pp->shp_face_obj_vsd[1] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x1);
		pp->shp_face_obj_vsd[2] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y1);
		pp->shp_face_obj_vsd[3] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_x0);
		pp->shp_face_obj_vsd[4] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_09.reg_obj_master_gain_lut_y0);
		pp->shp_face_obj_vsd[5] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x3);
		pp->shp_face_obj_vsd[6] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y3);
		pp->shp_face_obj_vsd[7] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_x2);
		pp->shp_face_obj_vsd[8] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0a.reg_obj_master_gain_lut_y2);
		pp->shp_face_obj_vsd[9] = PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x1);
		pp->shp_face_obj_vsd[10]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y1);
		pp->shp_face_obj_vsd[11]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_x0);
		pp->shp_face_obj_vsd[12]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0b.reg_obj_master_gain_t_map_lut_y0);
		pp->shp_face_obj_vsd[13]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x3);
		pp->shp_face_obj_vsd[14]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y3);
		pp->shp_face_obj_vsd[15]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_x2);
		pp->shp_face_obj_vsd[16]= PE_CHPI_TBL0_O26F22_Rd(res.shp_obj_ctrl_0c.reg_obj_master_gain_t_map_lut_y2);
		pp->shp_face_obj_vsd[17]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x1);
		pp->shp_face_obj_vsd[18]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y1);
		pp->shp_face_obj_vsd[19]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_x0);
		pp->shp_face_obj_vsd[20]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_09.reg_dp_sum_cg_lut_y0);
		pp->shp_face_obj_vsd[21]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x3);
		pp->shp_face_obj_vsd[22]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y3);
		pp->shp_face_obj_vsd[23]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_x2);
		pp->shp_face_obj_vsd[24]= PE_CHPI_TBL0_O26F22_Rd(res.shp_dp_sum_ctrl_0a.reg_dp_sum_cg_lut_y2);
		/*shp_cmn_vsd*/
		pp->shp_cmn_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_der_ctrl_01.reg_derh_edge_y_filter_en);
		pp->shp_cmn_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_der_ctrl_01.reg_derh_bflt_tap_size);
		pp->shp_cmn_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_00.reg_mp_shp_en);
		pp->shp_cmn_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_00.reg_sp_shp_en);
		pp->shp_cmn_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_01.reg_mp_im_os_gain);
		pp->shp_cmn_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_01.reg_mp_im_us_gain);
		pp->shp_cmn_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_01.reg_sp_im_os_gain);
		pp->shp_cmn_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_01.reg_sp_im_us_gain);
		pp->shp_cmn_vsd[8]=PE_CHPI_TBL0_O26F22_Rd(res.shp_esf_ctrl_00.reg_esf_en);
		pp->shp_cmn_vsd[9]=PE_CHPI_TBL0_O26F22_Rd(res.shp_esf_ctrl_01.reg_esf_min_ratio);
		pp->shp_cmn_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_esf_ctrl_01.reg_esf_base);
		pp->shp_cmn_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_esf_ctrl_01.reg_esf_max_clip);
		pp->shp_cmn_vsd[12]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_00.reg_dctp_en);
		pp->shp_cmn_vsd[13]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1e.reg_dctp_coring_en);
		pp->shp_cmn_vsd[14]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1e.reg_dctp_coring_mode);
		pp->shp_cmn_vsd[15]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_00.reg_tgen_on_off);
		pp->shp_cmn_vsd[16]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0a.reg_tgen_coring_en);
		pp->shp_cmn_vsd[17]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0a.reg_tgen_coring_mode);
		pp->shp_cmn_vsd[18]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_00.reg_nntg_en);
		pp->shp_cmn_vsd[19]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_0f.reg_nntg_coring_en);
		pp->shp_cmn_vsd[20]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_0f.reg_nntg_coring_mode);
		pp->shp_cmn_vsd[21]=PE_CHPI_TBL0_O26F22_Rd(res.shp_motion_prot_ctrl_00.reg_motion_prot_adaptive_en);
		pp->shp_cmn_vsd[22]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_00.reg_cti_en);
		pp->shp_cmn_vsd[23]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_02.reg_cti_ycm_en);
		pp->shp_cmn_vsd[24]=PE_CHPI_TBL0_O26F22_Rd(cti.shp_cti_ctrl_00.reg_cti_filter_tap_size);
		/*shp_djg_vsd*/
		pp->shp_djg_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_00.reg_dj_edf_en);
		pp->shp_djg_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_00.reg_dj_edge_adaptive_en);
		pp->shp_djg_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_00.reg_dj_soft_en);
		pp->shp_djg_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_03.reg_dj_edge_min);
		pp->shp_djg_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_03.reg_dj_edge_mul);
		pp->shp_djg_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_00.reg_dj_center_blur_mode);
		pp->shp_djg_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_00.reg_dj_n_avg_mode);
		pp->shp_djg_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dj_ctrl_01.reg_dj_n_avg_gain);

		/*shp_map_cmn_vsd */
		pp->shp_map_cmn_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_e_en);
		pp->shp_map_cmn_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0b.reg_fd_mnr_gain_t_en);
		pp->shp_map_cmn_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x0);
		pp->shp_map_cmn_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_x1);
		pp->shp_map_cmn_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y0);
		pp->shp_map_cmn_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_0d.reg_fd_mnr_gain_y1);
		pp->shp_map_cmn_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_11.reg_fd_soft_gain_t_en);
		pp->shp_map_cmn_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_11.reg_fd_soft_gain_e_en);
		pp->shp_map_cmn_vsd[8]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y3);
		pp->shp_map_cmn_vsd[9]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y2);
		pp->shp_map_cmn_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y1);
		pp->shp_map_cmn_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_fd_ctrl_14.reg_fd_soft_score_y0);

		/*shp_balance_vsd*/
		pp->shp_balance_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_05.reg_mp_gb_en);
		pp->shp_balance_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_05.reg_mp_gb_mode);
		pp->shp_balance_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_05.reg_mp_gb_y1);
		pp->shp_balance_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_06.reg_mp_gb_y2);
		pp->shp_balance_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_06.reg_mp_gb_y3);
		pp->shp_balance_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_05.reg_sp_gb_en);
		pp->shp_balance_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_05.reg_sp_gb_mode);
		pp->shp_balance_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_05.reg_sp_gb_y1);
		pp->shp_balance_vsd[8]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_06.reg_sp_gb_y2);
		pp->shp_balance_vsd[9]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_06.reg_sp_gb_y3);
		pp->shp_balance_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_00.reg_lc_shp_en);
		pp->shp_balance_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_00.reg_lc_gb_en);
		pp->shp_balance_vsd[12]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_01.reg_lc_gb_y1);
		pp->shp_balance_vsd[13]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_01.reg_lc_gb_y2);
		pp->shp_balance_vsd[14]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_02.reg_lc_gb_y3);
		pp->shp_balance_vsd[15]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_00.reg_lc_center_target);
		pp->shp_balance_vsd[16]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_00.reg_lc_center_gain);
		pp->shp_balance_vsd[17]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_00.reg_lc_local_gain);
		pp->shp_balance_vsd[18]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y0);
		pp->shp_balance_vsd[19]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y1);
		pp->shp_balance_vsd[20]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_08.reg_mp_lum1_y2);
		pp->shp_balance_vsd[21]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_09.reg_mp_lum2_y0);
		pp->shp_balance_vsd[22]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0a.reg_mp_lum2_y1);
		pp->shp_balance_vsd[23]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0a.reg_mp_lum2_y2);
		pp->shp_balance_vsd[24]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y0);
		pp->shp_balance_vsd[25]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y1);
		pp->shp_balance_vsd[26]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_08.reg_sp_lum1_y2);
		pp->shp_balance_vsd[27]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_09.reg_sp_lum2_y0);
		pp->shp_balance_vsd[28]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0a.reg_sp_lum2_y1);
		pp->shp_balance_vsd[29]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0a.reg_sp_lum2_y2);
		/*shp_ti_cmn_vsd*/
		pp->shp_ti_cmn_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_00.reg_ptiv_enable);
		pp->shp_ti_cmn_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_00.reg_ptiv_ti_mode);
		pp->shp_ti_cmn_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_00.reg_ptiv_mm_tap_size);
		pp->shp_ti_cmn_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_00.reg_ptiv_avg_tap_size);
		pp->shp_ti_cmn_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_01.reg_ptih_enable);
		pp->shp_ti_cmn_vsd[5]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_01.reg_ptih_ti_mode);
		pp->shp_ti_cmn_vsd[6]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_01.reg_ptih_mm_tap_size);
		pp->shp_ti_cmn_vsd[7]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_01.reg_ptih_avg_tap_size);
		pp->shp_ti_cmn_vsd[8]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sti_ctrl_00.reg_sti_enable);
		pp->shp_ti_cmn_vsd[9]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sti_ctrl_00.reg_sti_ti_mode);
		pp->shp_ti_cmn_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sti_ctrl_00.reg_sti_mm_tap_size);
		pp->shp_ti_cmn_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sti_ctrl_00.reg_sti_avg_tap_size);
		pp->shp_ti_cmn_vsd[12]=PE_CHPI_TBL0_O26F22_Rd(res.shp_snr_ctrl_00.reg_snr_blur_en);
		pp->shp_ti_cmn_vsd[13]=PE_CHPI_TBL0_O26F22_Rd(res.shp_snr_ctrl_00.reg_snr_blur_sel);
		/*shp_chroma_vsd*/
		pp->shp_chroma_vsd[0]=PE_CHPI_TBL0_O26F22_Rd(res.shp_chroma_ctrl_00.reg_color_region_en);
		pp->shp_chroma_vsd[1]=PE_CHPI_TBL0_O26F22_Rd(res.shp_chroma_ctrl_00.reg_chr_protection_en);
		pp->shp_chroma_vsd[2]=PE_CHPI_TBL0_O26F22_Rd(res.shp_chroma_ctrl_00.reg_chr_compensation_en);
		pp->shp_chroma_vsd[3]=PE_CHPI_TBL0_O26F22_Rd(res.shp_chroma_ctrl_0d.reg_chr_gain_r0_gain);
		pp->shp_chroma_vsd[4]=PE_CHPI_TBL0_O26F22_Rd(res.shp_chroma_ctrl_0d.reg_chr_gain_r1_gain);
		/*shp_ee_vsd*/
		pp->shp_ee_vsd[0] =PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_b);
		pp->shp_ee_vsd[1] =PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_e_w);
		pp->shp_ee_vsd[14]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_b);
		pp->shp_ee_vsd[15]=PE_CHPI_TBL0_O26F22_Rd(res.shp_mp_ctrl_0c.reg_mp_coring_gain_t_w);
		pp->shp_ee_vsd[2] =PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_b);
		pp->shp_ee_vsd[3] =PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_e_w);
		pp->shp_ee_vsd[16]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_b);
		pp->shp_ee_vsd[17]=PE_CHPI_TBL0_O26F22_Rd(res.shp_sp_ctrl_0c.reg_sp_coring_gain_t_w);
		pp->shp_ee_vsd[4] =PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_b);
		pp->shp_ee_vsd[5] =PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_e_w);
		pp->shp_ee_vsd[18]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_b);
		pp->shp_ee_vsd[19]=PE_CHPI_TBL0_O26F22_Rd(res.shp_pti_ctrl_03.reg_pti_coring_gain_t_w);
		pp->shp_ee_vsd[6] =PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_b);
		pp->shp_ee_vsd[7] =PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_e_w);
		pp->shp_ee_vsd[20]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_b);
		pp->shp_ee_vsd[21]=PE_CHPI_TBL0_O26F22_Rd(res.shp_lc_ctrl_04.reg_lc_coring_gain_t_w);
		pp->shp_ee_vsd[8] =PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_b);
		pp->shp_ee_vsd[9] =PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_e_w);
		pp->shp_ee_vsd[22]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_b);
		pp->shp_ee_vsd[23]=PE_CHPI_TBL0_O26F22_Rd(res.shp_dctp_ctrl_1f.reg_dctp_coring_gain_t_w);
		pp->shp_ee_vsd[10]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_b);
		pp->shp_ee_vsd[11]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_e_w);
		pp->shp_ee_vsd[24]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_b);
		pp->shp_ee_vsd[25]=PE_CHPI_TBL0_O26F22_Rd(res.shp_tgen_ctrl_0b.reg_tgen_coring_gain_t_w);
		pp->shp_ee_vsd[12]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_b);
		pp->shp_ee_vsd[13]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_e_w);
		pp->shp_ee_vsd[26]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_b);
		pp->shp_ee_vsd[27]=PE_CHPI_TBL0_O26F22_Rd(res.shp_nntg_ctrl_10.reg_nntg_coring_gain_t_w);
		PE_CHPI_TBL0_O26F22_QRd(res.sr_merge_blend_00.reg_blend_amp_weight,pp->shp_dnn_sr_vsd[0]);


		/* shp_ui_sqm_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmCmnUserDb */
		/* PE_CHPI_SHP_UI_SQM_O26F22_T 			 sqm0;//11 */
		PE_CHPI_TBL0_O26F22_QRd(sqm0.ui32,pp->shp_val);
		for (i=0; i<40; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(sqm0.data32[i],pp->shp_ui_sqm_vsd[i]);
		}
		/* shp_sqm_cmn_vsd */
		/* see PE_SHP_HW_O26_DownloadShpSqmDetailUserDb */
		/* PE_CHPI_SHP_CMN_SQM_O26F22_T			 sqm1;//12 */
		PE_CHPI_TBL0_O26F22_QRd(sqm1.ui32,pp->shp_val);
		for (i=0; i<51; i++)
		{
			PE_CHPI_TBL0_O26F22_QRd(sqm1.data32[i],pp->shp_sqm_cmn_vsd[i]);
		}
		PE_CHPI_TBL0_O26F22_QRd(sqm1.cnt32,i);

		pd = pp->shp_ui_main_vsd;
		printk("get[%d] : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = pp->shp_face_obj_vsd;
		printk("get[%d] : shp_fobj_vsd\n"
		"shp_face_obj_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
		pd[20], pd[21], pd[22], pd[23], pd[24]);
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
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[70]0x%08X\n",\
		pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
		pd[10],pd[11],	pd[12],  pd[13], pd[14],  pd[15],  pd[16],	pd[17], pd[18],  pd[19], \
		pd[20],pd[21],	pd[22],  pd[23], pd[24],  pd[25],  pd[26],	pd[27], pd[28],  pd[29],\
		pd[30],pd[31],	pd[32],  pd[33], pd[34],  pd[35],  pd[36],	pd[37], pd[38],  pd[39],\
		pd[40],pd[41],	pd[42],  pd[43], pd[34],  pd[45],  pd[46],	pd[47], pd[48],  pd[49],\
		pd[50],pd[51],	pd[52],  pd[53], pd[34],  pd[55],  pd[56],	pd[57], pd[58],  pd[59],\
		pd[60],pd[61],	pd[62],  pd[63], pd[34],  pd[65],  pd[66],	pd[67], pd[68],  pd[69],\
		pd[70]);
	}while(0);
	#endif
	return ret;
}


int PE_CHPI_SHP_HW_O26F22_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_SHP_HW_O26F22_ENABLE
	UINT32 enable;
	PE_RES_HW_PARAM_DATA_O26F22_T *p_res = &_g_pe_res_hw_param_data_o26f22;
	do{
		if (!gPE_CHPI_DDR_O26)	break;
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_res->reg_user.data);
		CHECK_KNULL(p_res->reg_mask.data);
		enable = (*onoff >0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_O26F22_Wr(res.shp_obj_ctrl_00.reg_obj_shp_en,enable);
		PE_CHPI_TBL0_O26F22_WrFL(res.shp_obj_ctrl_00.udata32);
		/* count */
		PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_RES);
		/* set user */
		PE_CHPI_SHP_HW_O26F22_USER(p_res,shp_obj_ctrl_00.reg_obj_shp_en,enable);
	}while(0);
	#endif
	return ret;
}

