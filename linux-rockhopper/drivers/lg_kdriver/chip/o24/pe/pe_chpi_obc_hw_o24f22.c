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

/** @file pe_chpi_obc_hw_o24.c
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

#include "pe_hw_o24.h"
#include "pe_reg_o24.h"
#include "pe_fwi_o24.h"
#include "pe_inf_o24.h"
#include "pe_res_hw_param_o24.h"
#include "pe_chpi_obc_hw_o24f22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_OBC_HW_O24F22_ENABLE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_OBC_HW_O24F22_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_OBC_HW_O24F22_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_OBE_HW_PARAM_REG_O24F22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBE_HW_PARAM_REG_O24F22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBE_HW_PARAM_REG_O24F22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBE_HW_PARAM_REG_O24F22_T *data;
	} reg_data;
} PE_OBE_HW_PARAM_DATA_O24F22_T;

 #endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
extern const PE_REG_PARAM_T obc_body_l_sd_default_o24[];
extern const PE_REG_PARAM_T obc_body_l_hd_default_o24[];
extern const PE_REG_PARAM_T obc_body_l_ud_default_o24[];
extern const PE_REG_PARAM_T obc_head_l_sd_default_o24[];
extern const PE_REG_PARAM_T obc_head_l_hd_default_o24[];
extern const PE_REG_PARAM_T obc_head_l_ud_default_o24[]; 

extern const PE_REG_PARAM_T obc_body_l_sd_default_o24f22[];
extern const PE_REG_PARAM_T obc_body_l_hd_default_o24f22[];
extern const PE_REG_PARAM_T obc_body_l_ud_default_o24f22[];
extern const PE_REG_PARAM_T obc_head_l_sd_default_o24f22[];
extern const PE_REG_PARAM_T obc_head_l_hd_default_o24f22[];
extern const PE_REG_PARAM_T obc_head_l_ud_default_o24f22[];

extern const PE_REG_PARAM_T amg_body_l_hd_default_o24f22[];
extern const PE_REG_PARAM_T amg_body_l_sd_default_o24f22[];
extern const PE_REG_PARAM_T amg_body_l_ud_default_o24f22[];
extern const PE_REG_PARAM_T amg_head_l_hd_default_o24f22[];
extern const PE_REG_PARAM_T amg_head_l_sd_default_o24f22[];
extern const PE_REG_PARAM_T amg_head_l_ud_default_o24f22[];

extern const PE_REG_PARAM_T obe_l_sd_default_o24f22[];
extern const PE_REG_PARAM_T obe_l_hd_default_o24f22[];
extern const PE_REG_PARAM_T obe_l_ud_default_o24f22[];

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
#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
static PE_OBE_HW_PARAM_DATA_O24F22_T _g_pe_obe_hw_param_data_o24f22 = {{NULL}, {NULL}, {NULL}, {NULL}};
 #endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static int PE_CHPI_OBC_HW_O24F22_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	PE_OBE_HW_PARAM_DATA_O24F22_T *p_obe = &_g_pe_obe_hw_param_data_o24f22;
 
	/* create dflt table */
	if (p_obe->reg_dflt.addr == NULL)
	{
		p_obe->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));
	}
	/* create user table */
	if (p_obe->reg_user.addr == NULL)
	{
		p_obe->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));
		memset((p_obe->reg_user.addr), 0, sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));	// 0x0
	}
	/* create mask table */
	if (p_obe->reg_mask.addr == NULL)
	{
		p_obe->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));
		memset((p_obe->reg_mask.addr), -1, sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));// 0xffffffff
	}
	/* create data table */
	if (p_obe->reg_data.addr == NULL)
	{
		p_obe->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));
		memset((p_obe->reg_data.addr), 0, sizeof(PE_OBE_HW_PARAM_REG_O24F22_T));	// 0x0
	}
	/* report srsult */
	if (p_obe->reg_dflt.addr != NULL && p_obe->reg_user.addr != NULL && \
		p_obe->reg_mask.addr != NULL && p_obe->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_obe]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_obe]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_obe->reg_dflt.addr == NULL)? "x":"o", \
			(p_obe->reg_user.addr == NULL)? "x":"o", \
			(p_obe->reg_mask.addr == NULL)? "x":"o", \
			(p_obe->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}
	#endif

	return ret;
}

static PE_CHPI_OBC_HW_O24F22_OBC_FMT PE_CHPI_OBC_HW_O24F22_ConvDispInfoToObcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_O24F22_OBC_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_O24F22_OBC_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_O24F22_OBC_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_O24F22_OBC_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_O24F22_OBC_UD;
			}
			break;
	}
	return fmt;
}
static PE_CHPI_OBC_HW_O24F22_OBE_FMT PE_CHPI_OBC_HW_O24F22_ConvDispInfoToObeFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_O24F22_OBE_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_O24F22_OBE_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_O24F22_OBE_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_O24F22_OBE_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_O24F22_OBE_UD;
			}
			break;
	}
	return fmt;
}

static PE_CHPI_OBC_HW_O24F22_AMG_FMT PE_CHPI_OBC_HW_O24F22_ConvDispInfoToAmgFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_O24F22_AMG_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_O24F22_AMG_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_O24F22_AMG_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_O24F22_AMG_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_O24F22_AMG_UD;
			}
			break;
	}
	return fmt;
}


static int PE_CHPI_OBC_HW_O24F22_SetObcDefault(PE_CHPI_OBC_HW_O24F22_OBC_FMT cur0_obc_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	// UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param1;
	const PE_REG_PARAM_T *p_dflt_param2;

	switch(cur0_obc_fmt)
	{
		case PE_CHPI_OBC_O24F22_OBC_SD:
			p_dflt_param1 = obc_head_l_sd_default_o24f22;
			p_dflt_param2 = obc_body_l_sd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_OBC_HD:
			p_dflt_param1 = obc_head_l_hd_default_o24f22;
			p_dflt_param2 = obc_body_l_hd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_OBC_UD:
		default:
			p_dflt_param1 = obc_head_l_ud_default_o24f22;
			p_dflt_param2 = obc_body_l_ud_default_o24f22;
			break;
	}

	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	do{
		if (!gPE_CHPI_DDR_O24)	break;
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl00.udata32,  p_dflt_param1[0].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl01.udata32,  p_dflt_param1[1].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl02.udata32,  p_dflt_param1[2].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl0.udata32,p_dflt_param1[3].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl1.udata32,p_dflt_param1[4].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl2.udata32,p_dflt_param1[5].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl00.udata32,                  p_dflt_param2[0].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl01.udata32,                  p_dflt_param2[1].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl02.udata32,                  p_dflt_param2[2].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl0.udata32,                p_dflt_param2[3].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl1.udata32,                p_dflt_param2[4].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl2.udata32,                p_dflt_param2[5].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_00.udata32,p_dflt_param2[6].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_01.udata32,p_dflt_param2[7].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_02.udata32,p_dflt_param2[8].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_03.udata32,p_dflt_param2[9].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_04.udata32,p_dflt_param2[10].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_05.udata32,p_dflt_param2[11].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_06.udata32,p_dflt_param2[12].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_07.udata32,p_dflt_param2[13].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_08.udata32,p_dflt_param2[14].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_09.udata32,p_dflt_param2[15].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_10.udata32,p_dflt_param2[16].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_11.udata32,p_dflt_param2[17].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_12.udata32,p_dflt_param2[18].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_13.udata32,p_dflt_param2[19].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_14.udata32,p_dflt_param2[20].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_15.udata32,p_dflt_param2[21].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_16.udata32,p_dflt_param2[22].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_17.udata32,p_dflt_param2[23].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_18.udata32,p_dflt_param2[24].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_19.udata32,p_dflt_param2[25].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_20.udata32,p_dflt_param2[26].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_21.udata32,p_dflt_param2[27].data);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_22.udata32,p_dflt_param2[28].data);
	}while(0);

	/* count */
	PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_OBC);
	#endif

	return ret;
}

static int PE_CHPI_OBC_HW_O24F22_SetObeDefault(PE_CHPI_OBC_HW_O24F22_OBE_FMT cur0_obe_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_obe_hw_param_data_o24f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_obe_hw_param_data_o24f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_obe_hw_param_data_o24f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_obe_hw_param_data_o24f22.reg_data.addr;

	PE_CHPI_OBC_HW_O24F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_OBC_HW_O24F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_OBC_HW_O24F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_OBC_HW_O24F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_obe_fmt)
	{
		case PE_CHPI_OBC_O24F22_OBE_SD:
			p_dflt_param = obe_l_sd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_OBE_HD:
			p_dflt_param = obe_l_hd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_OBE_UD:
		default:
			p_dflt_param = obe_l_ud_default_o24f22;
			break;
	}

	size = sizeof(PE_OBE_HW_PARAM_REG_O24F22_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	do{
		if (!gPE_CHPI_DDR_O24)	break;
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_001.udata32,p_data[0]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_002.udata32,p_data[1]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_003.udata32,p_data[2]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_004.udata32,p_data[3]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_005.udata32,p_data[4]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_025.udata32,p_data[5]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_026.udata32,p_data[6]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_027.udata32,p_data[7]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_086.udata32,p_data[8]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_087.udata32,p_data[9]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_088.udata32,p_data[10]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_089.udata32,p_data[11]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_090.udata32,p_data[12]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_091.udata32,p_data[13]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_092.udata32,p_data[14]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_093.udata32,p_data[15]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_094.udata32,p_data[16]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_095.udata32,p_data[17]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_096.udata32,p_data[18]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_097.udata32,p_data[19]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_098.udata32,p_data[20]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_099.udata32,p_data[21]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_100.udata32,p_data[22]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_101.udata32,p_data[23]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_102.udata32,p_data[24]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_103.udata32,p_data[25]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_104.udata32,p_data[26]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_105.udata32,p_data[27]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_106.udata32,p_data[28]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_107.udata32,p_data[29]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_126.udata32,p_data[30]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_127.udata32,p_data[31]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_136.udata32,p_data[32]);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_137.udata32,p_data[33]);
		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_OBE);
	}while(0);
	#endif

	return ret;
}

static int PE_CHPI_OBC_HW_O24F22_SetAmgDefault(PE_CHPI_OBC_HW_O24F22_AMG_FMT cur0_amg_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	// UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param1;
	const PE_REG_PARAM_T *p_dflt_param2;

	switch(cur0_amg_fmt)
	{
		case PE_CHPI_OBC_O24F22_AMG_SD:
			p_dflt_param1 = amg_head_l_sd_default_o24f22;
			p_dflt_param2 = amg_body_l_sd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_AMG_HD:
			p_dflt_param1 = amg_head_l_hd_default_o24f22;
			p_dflt_param2 = amg_body_l_hd_default_o24f22;
			break;
		case PE_CHPI_OBC_O24F22_AMG_UD:
		default:
			p_dflt_param1 = amg_head_l_hd_default_o24f22;
			p_dflt_param2 = amg_body_l_hd_default_o24f22;
			break;
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	do{
		if (!gPE_CHPI_DDR_O24)	break;
		/* amg header*/
		PE_CHPI_TBL0_O24F22_QWr(amg.histogram_ctrl_00.udata32,p_dflt_param1[0 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.histogram_ctrl_01.udata32,p_dflt_param1[1 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_00.udata32, p_dflt_param1[2 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_01.udata32, p_dflt_param1[3 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_02.udata32, p_dflt_param1[4 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_03.udata32, p_dflt_param1[5 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_00.udata32,  p_dflt_param1[6 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_01.udata32,  p_dflt_param1[7 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_02.udata32,  p_dflt_param1[8 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_03.udata32,  p_dflt_param1[9 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_04.udata32,  p_dflt_param1[10].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_05.udata32,  p_dflt_param1[11].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_06.udata32,  p_dflt_param1[12].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_07.udata32,  p_dflt_param1[13].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_08.udata32,  p_dflt_param1[14].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_09.udata32,  p_dflt_param1[15].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_10.udata32,  p_dflt_param1[16].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_11.udata32,  p_dflt_param1[17].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_12.udata32,  p_dflt_param1[18].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_13.udata32,  p_dflt_param1[19].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_14.udata32,  p_dflt_param1[20].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_15.udata32,  p_dflt_param1[21].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_16.udata32,  p_dflt_param1[22].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_17.udata32,  p_dflt_param1[23].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_prob_ctrl_00.udata32, p_dflt_param1[24].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_prob_ctrl_01.udata32, p_dflt_param1[25].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_00.udata32,     p_dflt_param1[26].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_01.udata32,     p_dflt_param1[27].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_02.udata32,     p_dflt_param1[28].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_03.udata32,     p_dflt_param1[29].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_04.udata32,     p_dflt_param1[30].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_05.udata32,     p_dflt_param1[31].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_06.udata32,     p_dflt_param1[32].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_07.udata32,     p_dflt_param1[33].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_08.udata32,     p_dflt_param1[34].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.iir_ctrl_00.udata32,      p_dflt_param1[35].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.iir_ctrl_01.udata32,      p_dflt_param1[36].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_00.udata32,  p_dflt_param1[37].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_01.udata32,  p_dflt_param1[38].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_02.udata32,  p_dflt_param1[39].data);
		/* amg body*/
		PE_CHPI_TBL0_O24F22_QWr(amg.body_histogram_ctrl_00.udata32,p_dflt_param2[0 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_histogram_ctrl_01.udata32,p_dflt_param2[1 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_00.udata32, p_dflt_param2[2 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_01.udata32, p_dflt_param2[3 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_02.udata32, p_dflt_param2[4 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_03.udata32, p_dflt_param2[5 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_00.udata32,  p_dflt_param2[6 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_01.udata32,  p_dflt_param2[7 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_02.udata32,  p_dflt_param2[8 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_03.udata32,  p_dflt_param2[9 ].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_04.udata32,  p_dflt_param2[10].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_05.udata32,  p_dflt_param2[11].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_06.udata32,  p_dflt_param2[12].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_07.udata32,  p_dflt_param2[13].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_08.udata32,  p_dflt_param2[14].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_09.udata32,  p_dflt_param2[15].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_10.udata32,  p_dflt_param2[16].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_11.udata32,  p_dflt_param2[17].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_12.udata32,  p_dflt_param2[18].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_13.udata32,  p_dflt_param2[19].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_14.udata32,  p_dflt_param2[20].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_15.udata32,  p_dflt_param2[21].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_16.udata32,  p_dflt_param2[22].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_17.udata32,  p_dflt_param2[23].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_prob_ctrl_00.udata32, p_dflt_param2[24].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_prob_ctrl_01.udata32, p_dflt_param2[25].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_00.udata32,     p_dflt_param2[26].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_01.udata32,     p_dflt_param2[27].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_02.udata32,     p_dflt_param2[28].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_03.udata32,     p_dflt_param2[29].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_04.udata32,     p_dflt_param2[30].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_05.udata32,     p_dflt_param2[31].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_06.udata32,     p_dflt_param2[32].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_07.udata32,     p_dflt_param2[33].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_08.udata32,     p_dflt_param2[34].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_ctrl_00.udata32,p_dflt_param2[35].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_ctrl_01.udata32,p_dflt_param2[36].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_00.udata32,p_dflt_param2[37].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_01.udata32,p_dflt_param2[38].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_02.udata32,p_dflt_param2[39].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_03.udata32,p_dflt_param2[40].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_04.udata32,p_dflt_param2[41].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_05.udata32,p_dflt_param2[42].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_06.udata32,p_dflt_param2[43].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_07.udata32,p_dflt_param2[44].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_08.udata32,p_dflt_param2[45].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_09.udata32,p_dflt_param2[46].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_10.udata32,p_dflt_param2[47].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_11.udata32,p_dflt_param2[48].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_12.udata32,p_dflt_param2[49].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_13.udata32,p_dflt_param2[50].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_14.udata32,p_dflt_param2[51].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_15.udata32,p_dflt_param2[52].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_16.udata32,p_dflt_param2[53].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_17.udata32,p_dflt_param2[54].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_18.udata32,p_dflt_param2[55].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_19.udata32,p_dflt_param2[56].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_20.udata32,p_dflt_param2[57].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_21.udata32,p_dflt_param2[58].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_00.udata32,p_dflt_param2[59].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_01.udata32,p_dflt_param2[60].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_02.udata32,p_dflt_param2[61].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_03.udata32,p_dflt_param2[62].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_00.udata32,      p_dflt_param2[63].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_01.udata32,      p_dflt_param2[64].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_02.udata32,      p_dflt_param2[65].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_03.udata32,      p_dflt_param2[66].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_iir_ctrl_00.udata32,          p_dflt_param2[67].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_iir_ctrl_01.udata32,          p_dflt_param2[68].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_00.udata32,      p_dflt_param2[69].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_01.udata32,      p_dflt_param2[70].data);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_02.udata32,      p_dflt_param2[71].data);
		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_AMG);
	}while(0);
	#endif
	return ret;
}
int PE_CHPI_OBC_HW_O24F22_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_O24_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_OBC_HW_O24F22_OBC_FMT pre0_obc_fmt = PE_CHPI_OBC_O24F22_OBC_NUM;
	static PE_CHPI_OBC_HW_O24F22_OBE_FMT pre0_obe_fmt = PE_CHPI_OBC_O24F22_OBE_NUM;
	static PE_CHPI_OBC_HW_O24F22_AMG_FMT pre0_amg_fmt = PE_CHPI_OBC_O24F22_AMG_NUM;
	PE_CHPI_OBC_HW_O24F22_OBC_FMT cur0_obc_fmt;
	PE_CHPI_OBC_HW_O24F22_OBE_FMT cur0_obe_fmt;
	PE_CHPI_OBC_HW_O24F22_AMG_FMT cur0_amg_fmt;
	do{
		ret = PE_INF_O24_GetCurInfSettings(&inf_set);
		PE_CHPI_OBC_HW_O24F22_CHECK_CODE(ret,break,"PE_INF_O24_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_obc_fmt = PE_CHPI_OBC_HW_O24F22_ConvDispInfoToObcFmt(disp0_inf);
		if(pre0_obc_fmt!=cur0_obc_fmt)
		{
			ret = PE_CHPI_OBC_HW_O24F22_SetObcDefault(cur0_obc_fmt);
			PE_CHPI_OBC_HW_O24F22_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_O24F22_SetOboDefault() error\n");
			pre0_obc_fmt=cur0_obc_fmt;
		}
		cur0_obe_fmt = PE_CHPI_OBC_HW_O24F22_ConvDispInfoToObeFmt(disp0_inf);
		if(pre0_obe_fmt!=cur0_obe_fmt)
		{
			ret = PE_CHPI_OBC_HW_O24F22_SetObeDefault(cur0_obe_fmt);
			PE_CHPI_OBC_HW_O24F22_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_O24F22_SetObeDefault() error\n");
			pre0_obe_fmt=cur0_obe_fmt;
		}
		cur0_amg_fmt = PE_CHPI_OBC_HW_O24F22_ConvDispInfoToAmgFmt(disp0_inf);
		if(pre0_amg_fmt!=cur0_amg_fmt)
		{
			ret = PE_CHPI_OBC_HW_O24F22_SetAmgDefault(cur0_amg_fmt);
			PE_CHPI_OBC_HW_O24F22_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_O24F22_SetAmgDefault() error\n");
			pre0_amg_fmt=cur0_amg_fmt;
		}
	}while(0);
	return ret;
}

#if (CONFIG_LX_O24_CHIP_FIRMWARE == 1)
int PE_CHPI_OBC_HW_O24F22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_OBC_HW_O24F22_CreateDataTable();
		if (ret)	break;
		if (pstParams->resume_mode == 1)	break;//if qsm,skip
		if (!gPE_CHPI_DDR_O24)	break;

		/* addr */
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl00.uaddr32,0xF3030800);
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl01.uaddr32,0xF3030804);
		PE_CHPI_TBL0_O24F22_QWr(obc.psp_ctrl02.uaddr32,0xF3030808);
		PE_CHPI_TBL0_O24F22_QWr(obc.display_debug_map.uaddr32,0xF3030848);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl0.uaddr32,0xF3030870);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl1.uaddr32,0xF3030874);
		PE_CHPI_TBL0_O24F22_QWr(obc.refine_ctrl2.uaddr32,0xF3030878);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl00.uaddr32,0xF3030600);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl01.uaddr32,0xF3030604);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_psp_ctrl02.uaddr32,0xF3030608);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_display_debug_map.uaddr32,0xF3030648);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl0.uaddr32,0xF3030670);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl1.uaddr32,0xF3030674);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_refine_ctrl2.uaddr32,0xF3030678);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_00.uaddr32,0xF3030690);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_01.uaddr32,0xF3030694);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_02.uaddr32,0xF3030698);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_03.uaddr32,0xF303069C);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_04.uaddr32,0xF30306A0);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_05.uaddr32,0xF30306A4);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_06.uaddr32,0xF30306A8);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_07.uaddr32,0xF30306AC);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_08.uaddr32,0xF30306B0);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_09.uaddr32,0xF30306B4);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_10.uaddr32,0xF30306B8);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_11.uaddr32,0xF30306BC);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_12.uaddr32,0xF30306C0);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_13.uaddr32,0xF30306C4);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_14.uaddr32,0xF30306C8);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_15.uaddr32,0xF30306CC);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_16.uaddr32,0xF30306D0);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_17.uaddr32,0xF30306D4);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_18.uaddr32,0xF30306D8);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_19.uaddr32,0xF30306DC);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_20.uaddr32,0xF30306E0);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_21.uaddr32,0xF30306E4);
		PE_CHPI_TBL0_O24F22_QWr(obc.obj_refine_body_gain_ctrl_22.uaddr32,0xF30306E8);

		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_001.uaddr32,0xF3030204);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_002.uaddr32,0xF3030208);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_003.uaddr32,0xF303020C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_004.uaddr32,0xF3030210);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_005.uaddr32,0xF3030214);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_025.uaddr32,0xF3030264);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_026.uaddr32,0xF3030268);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_027.uaddr32,0xF303026C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_086.uaddr32,0xF3030358);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_087.uaddr32,0xF303035C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_088.uaddr32,0xF3030360);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_089.uaddr32,0xF3030364);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_090.uaddr32,0xF3030368);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_091.uaddr32,0xF303036C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_092.uaddr32,0xF3030370);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_093.uaddr32,0xF3030374);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_094.uaddr32,0xF3030378);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_095.uaddr32,0xF303037C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_096.uaddr32,0xF3030380);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_097.uaddr32,0xF3030384);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_098.uaddr32,0xF3030388);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_099.uaddr32,0xF303038C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_100.uaddr32,0xF3030390);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_101.uaddr32,0xF3030394);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_102.uaddr32,0xF3030398);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_103.uaddr32,0xF303039C);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_104.uaddr32,0xF30303A0);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_105.uaddr32,0xF30303A4);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_106.uaddr32,0xF30303A8);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_107.uaddr32,0xF30303AC);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_126.uaddr32,0xF30303F8);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_127.uaddr32,0xF30303FC);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_136.uaddr32,0xF3030420);
		PE_CHPI_TBL0_O24F22_QWr(obe.reg_obe_ctrl_137.uaddr32,0xF3030424);

		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_028.uaddr32,0xF3030270);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_029.uaddr32,0xF3030274);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_030.uaddr32,0xF3030278);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_031.uaddr32,0xF303027C);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_032.uaddr32,0xF3030280);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_033.uaddr32,0xF3030284);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_034.uaddr32,0xF3030288);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_035.uaddr32,0xF303028C);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_036.uaddr32,0xF3030290);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_037.uaddr32,0xF3030294);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_038.uaddr32,0xF3030298);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_039.uaddr32,0xF303029C);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_040.uaddr32,0xF30302A0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_041.uaddr32,0xF30302A4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_042.uaddr32,0xF30302A8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_043.uaddr32,0xF30302AC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_044.uaddr32,0xF30302B0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_045.uaddr32,0xF30302B4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_046.uaddr32,0xF30302B8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_047.uaddr32,0xF30302BC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_048.uaddr32,0xF30302C0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_049.uaddr32,0xF30302C4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_050.uaddr32,0xF30302C8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_051.uaddr32,0xF30302CC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_052.uaddr32,0xF30302D0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_053.uaddr32,0xF30302D4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_054.uaddr32,0xF30302D8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_055.uaddr32,0xF30302DC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_056.uaddr32,0xF30302E0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_057.uaddr32,0xF30302E4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_058.uaddr32,0xF30302E8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_059.uaddr32,0xF30302EC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_060.uaddr32,0xF30302F0);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_061.uaddr32,0xF30302F4);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_062.uaddr32,0xF30302F8);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_063.uaddr32,0xF30302FC);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_082.uaddr32,0xF3030348);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_083.uaddr32,0xF303034C);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_084.uaddr32,0xF3030350);
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_085.uaddr32,0xF3030354);

		/*head*/
		PE_CHPI_TBL0_O24F22_QWr(amg.histogram_ctrl_00.uaddr32,0xF3011D20);
		PE_CHPI_TBL0_O24F22_QWr(amg.histogram_ctrl_01.uaddr32,0xF3011D24);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_00.uaddr32,0xF3011DB0);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_01.uaddr32,0xF3011DB4);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_02.uaddr32,0xF3011DB8);
		PE_CHPI_TBL0_O24F22_QWr(amg.objt_map_ctrl_03.uaddr32,0xF3011DBC);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_00.uaddr32,0xF3011E00);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_01.uaddr32,0xF3011E04);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_02.uaddr32,0xF3011E08);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_03.uaddr32,0xF3011E0C);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_04.uaddr32,0xF3011E10);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_05.uaddr32,0xF3011E14);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_06.uaddr32,0xF3011E18);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_07.uaddr32,0xF3011E1C);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_08.uaddr32,0xF3011E20);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_09.uaddr32,0xF3011E24);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_10.uaddr32,0xF3011E28);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_11.uaddr32,0xF3011E2C);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_12.uaddr32,0xF3011E30);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_13.uaddr32,0xF3011E34);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_14.uaddr32,0xF3011E38);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_15.uaddr32,0xF3011E3C);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_16.uaddr32,0xF3011E40);
		PE_CHPI_TBL0_O24F22_QWr(amg.ellipse_ctrl_17.uaddr32,0xF3011E44);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_prob_ctrl_00.uaddr32,0xF3011E50);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_prob_ctrl_01.uaddr32,0xF3011E54);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_00.uaddr32,0xF3011E60);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_01.uaddr32,0xF3011E64);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_02.uaddr32,0xF3011E68);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_03.uaddr32,0xF3011E6C);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_04.uaddr32,0xF3011E70);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_05.uaddr32,0xF3011E74);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_06.uaddr32,0xF3011E78);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_07.uaddr32,0xF3011E7C);
		PE_CHPI_TBL0_O24F22_QWr(amg.blur_ctrl_08.uaddr32,0xF3011E80);
		PE_CHPI_TBL0_O24F22_QWr(amg.iir_ctrl_00.uaddr32,0xF3011F20);
		PE_CHPI_TBL0_O24F22_QWr(amg.iir_ctrl_01.uaddr32,0xF3011F24);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_00.uaddr32,0xF3011F30);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_01.uaddr32,0xF3011F34);
		PE_CHPI_TBL0_O24F22_QWr(amg.lut_iir_ctrl_02.uaddr32,0xF3011F38);
		/*body*/
		PE_CHPI_TBL0_O24F22_QWr(amg.body_histogram_ctrl_00.uaddr32,0xF3012020);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_histogram_ctrl_01.uaddr32,0xF3012024);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_00.uaddr32,0xF30120B0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_01.uaddr32,0xF30120B4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_02.uaddr32,0xF30120B8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_objt_map_ctrl_03.uaddr32,0xF30120BC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_00.uaddr32,0xF3012100);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_01.uaddr32,0xF3012104);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_02.uaddr32,0xF3012108);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_03.uaddr32,0xF301210C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_04.uaddr32,0xF3012110);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_05.uaddr32,0xF3012114);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_06.uaddr32,0xF3012118);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_07.uaddr32,0xF301211C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_08.uaddr32,0xF3012120);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_09.uaddr32,0xF3012124);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_10.uaddr32,0xF3012128);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_11.uaddr32,0xF301212C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_12.uaddr32,0xF3012130);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_13.uaddr32,0xF3012134);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_14.uaddr32,0xF3012138);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_15.uaddr32,0xF301213C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_16.uaddr32,0xF3012140);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_ellipse_ctrl_17.uaddr32,0xF3012144);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_prob_ctrl_00.uaddr32,0xF3012150);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_prob_ctrl_01.uaddr32,0xF3012154);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_00.uaddr32,0xF3012160);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_01.uaddr32,0xF3012164);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_02.uaddr32,0xF3012168);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_03.uaddr32,0xF301216C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_04.uaddr32,0xF3012170);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_05.uaddr32,0xF3012174);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_06.uaddr32,0xF3012178);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_07.uaddr32,0xF301217C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_blur_ctrl_08.uaddr32,0xF3012180);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_ctrl_00.uaddr32,0xF3012190);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_ctrl_01.uaddr32,0xF3012194);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_00.uaddr32,0xF30121A0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_01.uaddr32,0xF30121A4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_02.uaddr32,0xF30121A8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_03.uaddr32,0xF30121AC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_04.uaddr32,0xF30121B0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_05.uaddr32,0xF30121B4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_06.uaddr32,0xF30121B8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_07.uaddr32,0xF30121BC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_08.uaddr32,0xF30121C0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_09.uaddr32,0xF30121C4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_10.uaddr32,0xF30121C8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_11.uaddr32,0xF30121CC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_12.uaddr32,0xF30121D0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_13.uaddr32,0xF30121D4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_14.uaddr32,0xF30121D8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_15.uaddr32,0xF30121DC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_16.uaddr32,0xF30121E0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_17.uaddr32,0xF30121E4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_18.uaddr32,0xF30121E8);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_19.uaddr32,0xF30121EC);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_20.uaddr32,0xF30121F0);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_region_gain_ctrl_21.uaddr32,0xF30121F4);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_00.uaddr32,0xF3012200);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_01.uaddr32,0xF3012204);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_02.uaddr32,0xF3012208);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_depth_iir_ctrl_03.uaddr32,0xF301220C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_00.uaddr32,0xF3012210);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_01.uaddr32,0xF3012214);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_02.uaddr32,0xF3012218);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_bld_ctrl_03.uaddr32,0xF301221C);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_iir_ctrl_00.uaddr32,0xF3012220);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_iir_ctrl_01.uaddr32,0xF3012224);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_00.uaddr32,0xF3012230);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_01.uaddr32,0xF3012234);
		PE_CHPI_TBL0_O24F22_QWr(amg.body_lut_iir_ctrl_02.uaddr32,0xF3012238);
		/* init */
		PE_CHPI_TBL0_O24F22_QWr(obc.display_debug_map.udata32,0x00000044);
		PE_CHPI_TBL0_O24F22_QWr(obc.body_display_debug_map.udata32,0x00000044);
		PE_CHPI_OBC_HW_O24F22_SetObcDefault(PE_CHPI_OBC_O24F22_OBC_HD);
		PE_CHPI_OBC_HW_O24F22_SetObeDefault(PE_CHPI_OBC_O24F22_OBE_HD);
		//setting init exept from obe default group 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_028.udata32,0x00000000);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_029.udata32,0x001A0021);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_030.udata32,0x04680441);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_031.udata32,0x267D3FFF);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_032.udata32,0x3BBD3FFF);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_033.udata32,0x3FFF3FFF);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_034.udata32,0x00000000);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_035.udata32,0x001A0021);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_036.udata32,0x04680441);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_037.udata32,0x027D03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_038.udata32,0x03BD03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_039.udata32,0x03FF03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_040.udata32,0x00000000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_041.udata32,0x001A0021); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_042.udata32,0x04680441); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_043.udata32,0x027D03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_044.udata32,0x03BD03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_045.udata32,0x03FF03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_046.udata32,0x00000000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_047.udata32,0x001A0000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_048.udata32,0x00C80000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_049.udata32,0x267D3FFF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_050.udata32,0x3BBD3FFF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_051.udata32,0x3FFF3FFF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_052.udata32,0x00000000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_053.udata32,0x001A0000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_054.udata32,0x00C80000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_055.udata32,0x027D03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_056.udata32,0x03BD03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_057.udata32,0x03FF03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_058.udata32,0x00000000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_059.udata32,0x001A0000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_060.udata32,0x00C80000); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_061.udata32,0x027D03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_062.udata32,0x03BD03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_063.udata32,0x03FF03FF); 
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_082.udata32,0xFFFF6EB4);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_083.udata32,0x1E000000);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_084.udata32,0xFFFF6EB4);  
		PE_CHPI_TBL0_O24F22_QWr(obec.reg_obe_ctrl_085.udata32,0x1E000000); 
		PE_CHPI_OBC_HW_O24F22_SetAmgDefault(PE_CHPI_OBC_O24F22_AMG_HD);

		PE_INF_HW_O24_BACKUP_CHPI1("[TBL][OBC]done(resume::%d)",pstParams->resume_mode);
	}while(0);
	#endif
	return ret;
}
#else
int PE_CHPI_OBC_HW_O24F22_Init(PE_CFG_CTRL_T *pstParams)
{
	 PE_PRINT_NOTI("not supported\n");
	 return RET_ERROR;
}
#endif


int PE_CHPI_OBC_HW_O24F22_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	LX_PE_VSD_OBC4_CONT_T *pp;
	PE_OBE_HW_PARAM_DATA_O24F22_T *p_obe = &_g_pe_obe_hw_param_data_o24f22;
	do{
		if (!gPE_CHPI_DDR_O24)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_obe->reg_user.data);
		CHECK_KNULL(p_obe->reg_mask.data);
 		pp=(LX_PE_VSD_OBC4_CONT_T *)pstParams;
		/* set apb */
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_083.reg_head_gain_lut_y0,	GET_BITS(pp->head_gain_y[0],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_083.reg_head_gain_lut_x0,	GET_BITS(pp->head_gain_x[0],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_083.reg_head_gain_lut_y1,	GET_BITS(pp->head_gain_y[1],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_083.reg_head_gain_lut_x1,	GET_BITS(pp->head_gain_x[1],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_082.reg_head_gain_lut_y2,	GET_BITS(pp->head_gain_y[2],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_082.reg_head_gain_lut_x2,	GET_BITS(pp->head_gain_x[2],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_082.reg_head_gain_lut_y3,	GET_BITS(pp->head_gain_y[3],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_082.reg_head_gain_lut_x3,	GET_BITS(pp->head_gain_x[3],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_085.reg_body_gain_lut_y0,	GET_BITS(pp->body_gain_y[0],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_085.reg_body_gain_lut_x0,	GET_BITS(pp->body_gain_x[0],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_085.reg_body_gain_lut_y1,	GET_BITS(pp->body_gain_y[1],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_085.reg_body_gain_lut_x1,	GET_BITS(pp->body_gain_x[1],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_084.reg_body_gain_lut_y2,	GET_BITS(pp->body_gain_y[2],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_084.reg_body_gain_lut_x2,	GET_BITS(pp->body_gain_x[2],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_084.reg_body_gain_lut_y3,	GET_BITS(pp->body_gain_y[3],0,8));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_084.reg_body_gain_lut_x3,	GET_BITS(pp->body_gain_x[3],0,8));
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_083.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_082.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_085.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_084.udata32);
		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_OBEC);
		/* set user */
		#if 0
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_083.reg_head_gain_lut_y0,	GET_BITS(pp->head_gain_y[0],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_083.reg_head_gain_lut_x0,	GET_BITS(pp->head_gain_x[0],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_083.reg_head_gain_lut_y1,	GET_BITS(pp->head_gain_y[1],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_083.reg_head_gain_lut_x1,	GET_BITS(pp->head_gain_x[1],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_082.reg_head_gain_lut_y2,	GET_BITS(pp->head_gain_y[2],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_082.reg_head_gain_lut_x2,	GET_BITS(pp->head_gain_x[2],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_082.reg_head_gain_lut_y3,	GET_BITS(pp->head_gain_y[3],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_082.reg_head_gain_lut_x3,	GET_BITS(pp->head_gain_x[3],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_085.reg_body_gain_lut_y0,	GET_BITS(pp->body_gain_y[0],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_085.reg_body_gain_lut_x0,	GET_BITS(pp->body_gain_x[0],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_085.reg_body_gain_lut_y1,	GET_BITS(pp->body_gain_y[1],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_085.reg_body_gain_lut_x1,	GET_BITS(pp->body_gain_x[1],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_084.reg_body_gain_lut_y2,	GET_BITS(pp->body_gain_y[2],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_084.reg_body_gain_lut_x2,	GET_BITS(pp->body_gain_x[2],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_084.reg_body_gain_lut_y3,	GET_BITS(pp->body_gain_y[3],0,8));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_084.reg_body_gain_lut_x3,	GET_BITS(pp->body_gain_x[3],0,8));
		#endif

	}while(0);
	#endif
	return ret;
}

int PE_CHPI_OBC_HW_O24F22_SetLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_O24F22_ENABLE
	LX_PE_VSD_OBC2_LUT_T *pp;
	PE_OBE_HW_PARAM_DATA_O24F22_T *p_obe = &_g_pe_obe_hw_param_data_o24f22;
	do{
		if (!gPE_CHPI_DDR_O24)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_obe->reg_user.data);
		CHECK_KNULL(p_obe->reg_mask.data);
		pp=(LX_PE_VSD_OBC2_LUT_T *)pstParams;
		/* set apb */
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_028.reg_head_r_lut_x0, GET_BITS(pp->head_r_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_028.reg_head_r_lut_y0, GET_BITS(pp->head_r_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_029.reg_head_r_lut_x1, GET_BITS(pp->head_r_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_029.reg_head_r_lut_y1, GET_BITS(pp->head_r_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_030.reg_head_r_lut_x2, GET_BITS(pp->head_r_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_030.reg_head_r_lut_y2, GET_BITS(pp->head_r_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_031.reg_head_r_lut_x3, GET_BITS(pp->head_r_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_031.reg_head_r_lut_y3, GET_BITS(pp->head_r_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_032.reg_head_r_lut_x4, GET_BITS(pp->head_r_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_032.reg_head_r_lut_y4, GET_BITS(pp->head_r_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_033.reg_head_r_lut_x5, GET_BITS(pp->head_r_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_033.reg_head_r_lut_y5, GET_BITS(pp->head_r_lut_y[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_034.reg_head_g_lut_x0, GET_BITS(pp->head_g_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_034.reg_head_g_lut_y0, GET_BITS(pp->head_g_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_035.reg_head_g_lut_x1, GET_BITS(pp->head_g_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_035.reg_head_g_lut_y1, GET_BITS(pp->head_g_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_036.reg_head_g_lut_x2, GET_BITS(pp->head_g_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_036.reg_head_g_lut_y2, GET_BITS(pp->head_g_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_037.reg_head_g_lut_x3, GET_BITS(pp->head_g_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_037.reg_head_g_lut_y3, GET_BITS(pp->head_g_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_038.reg_head_g_lut_x4, GET_BITS(pp->head_g_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_038.reg_head_g_lut_y4, GET_BITS(pp->head_g_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_039.reg_head_g_lut_x5, GET_BITS(pp->head_g_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_039.reg_head_g_lut_y5, GET_BITS(pp->head_g_lut_y[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_040.reg_head_b_lut_x0, GET_BITS(pp->head_b_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_040.reg_head_b_lut_y0, GET_BITS(pp->head_b_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_041.reg_head_b_lut_x1, GET_BITS(pp->head_b_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_041.reg_head_b_lut_y1, GET_BITS(pp->head_b_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_042.reg_head_b_lut_x2, GET_BITS(pp->head_b_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_042.reg_head_b_lut_y2, GET_BITS(pp->head_b_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_043.reg_head_b_lut_x3, GET_BITS(pp->head_b_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_043.reg_head_b_lut_y3, GET_BITS(pp->head_b_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_044.reg_head_b_lut_x4, GET_BITS(pp->head_b_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_044.reg_head_b_lut_y4, GET_BITS(pp->head_b_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_045.reg_head_b_lut_x5, GET_BITS(pp->head_b_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_045.reg_head_b_lut_y5, GET_BITS(pp->head_b_lut_y[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_046.reg_body_r_lut_x0, GET_BITS(pp->body_r_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_046.reg_body_r_lut_y0, GET_BITS(pp->body_r_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_047.reg_body_r_lut_x1, GET_BITS(pp->body_r_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_047.reg_body_r_lut_y1, GET_BITS(pp->body_r_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_048.reg_body_r_lut_x2, GET_BITS(pp->body_r_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_048.reg_body_r_lut_y2, GET_BITS(pp->body_r_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_049.reg_body_r_lut_x3, GET_BITS(pp->body_r_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_049.reg_body_r_lut_y3, GET_BITS(pp->body_r_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_050.reg_body_r_lut_x4, GET_BITS(pp->body_r_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_050.reg_body_r_lut_y4, GET_BITS(pp->body_r_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_051.reg_body_r_lut_x5, GET_BITS(pp->body_r_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_051.reg_body_r_lut_y5, GET_BITS(pp->body_r_lut_y[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_052.reg_body_g_lut_x0, GET_BITS(pp->body_g_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_052.reg_body_g_lut_y0, GET_BITS(pp->body_g_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_053.reg_body_g_lut_x1, GET_BITS(pp->body_g_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_053.reg_body_g_lut_y1, GET_BITS(pp->body_g_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_054.reg_body_g_lut_x2, GET_BITS(pp->body_g_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_054.reg_body_g_lut_y2, GET_BITS(pp->body_g_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_055.reg_body_g_lut_x3, GET_BITS(pp->body_g_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_055.reg_body_g_lut_y3, GET_BITS(pp->body_g_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_056.reg_body_g_lut_x4, GET_BITS(pp->body_g_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_056.reg_body_g_lut_y4, GET_BITS(pp->body_g_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_057.reg_body_g_lut_x5, GET_BITS(pp->body_g_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_057.reg_body_g_lut_y5, GET_BITS(pp->body_g_lut_y[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_058.reg_body_b_lut_x0, GET_BITS(pp->body_b_lut_x[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_058.reg_body_b_lut_y0, GET_BITS(pp->body_b_lut_y[0],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_059.reg_body_b_lut_x1, GET_BITS(pp->body_b_lut_x[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_059.reg_body_b_lut_y1, GET_BITS(pp->body_b_lut_y[1],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_060.reg_body_b_lut_x2, GET_BITS(pp->body_b_lut_x[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_060.reg_body_b_lut_y2, GET_BITS(pp->body_b_lut_y[2],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_061.reg_body_b_lut_x3, GET_BITS(pp->body_b_lut_x[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_061.reg_body_b_lut_y3, GET_BITS(pp->body_b_lut_y[3],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_062.reg_body_b_lut_x4, GET_BITS(pp->body_b_lut_x[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_062.reg_body_b_lut_y4, GET_BITS(pp->body_b_lut_y[4],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_063.reg_body_b_lut_x5, GET_BITS(pp->body_b_lut_x[5],0,10));
		PE_CHPI_TBL0_O24F22_Wr(obec.reg_obe_ctrl_063.reg_body_b_lut_y5, GET_BITS(pp->body_b_lut_y[5],0,10));

		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_028.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_029.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_030.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_031.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_032.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_033.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_034.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_035.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_036.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_037.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_038.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_039.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_040.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_041.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_042.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_043.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_044.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_045.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_046.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_047.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_048.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_049.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_050.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_051.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_052.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_053.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_054.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_055.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_056.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_057.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_058.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_059.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_060.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_061.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_062.udata32);
		PE_CHPI_TBL0_O24F22_WrFL(obec.reg_obe_ctrl_063.udata32);

		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_OBEC);
		/* set user */
		#if 0
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_028.reg_head_r_lut_x0, GET_BITS(pp->head_r_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_028.reg_head_r_lut_y0, GET_BITS(pp->head_r_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_029.reg_head_r_lut_x1, GET_BITS(pp->head_r_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_029.reg_head_r_lut_y1, GET_BITS(pp->head_r_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_030.reg_head_r_lut_x2, GET_BITS(pp->head_r_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_030.reg_head_r_lut_y2, GET_BITS(pp->head_r_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_031.reg_head_r_lut_x3, GET_BITS(pp->head_r_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_031.reg_head_r_lut_y3, GET_BITS(pp->head_r_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_032.reg_head_r_lut_x4, GET_BITS(pp->head_r_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_032.reg_head_r_lut_y4, GET_BITS(pp->head_r_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_033.reg_head_r_lut_x5, GET_BITS(pp->head_r_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_033.reg_head_r_lut_y5, GET_BITS(pp->head_r_lut_y[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_034.reg_head_g_lut_x0, GET_BITS(pp->head_g_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_034.reg_head_g_lut_y0, GET_BITS(pp->head_g_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_035.reg_head_g_lut_x1, GET_BITS(pp->head_g_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_035.reg_head_g_lut_y1, GET_BITS(pp->head_g_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_036.reg_head_g_lut_x2, GET_BITS(pp->head_g_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_036.reg_head_g_lut_y2, GET_BITS(pp->head_g_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_037.reg_head_g_lut_x3, GET_BITS(pp->head_g_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_037.reg_head_g_lut_y3, GET_BITS(pp->head_g_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_038.reg_head_g_lut_x4, GET_BITS(pp->head_g_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_038.reg_head_g_lut_y4, GET_BITS(pp->head_g_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_039.reg_head_g_lut_x5, GET_BITS(pp->head_g_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_039.reg_head_g_lut_y5, GET_BITS(pp->head_g_lut_y[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_040.reg_head_b_lut_x0, GET_BITS(pp->head_b_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_040.reg_head_b_lut_y0, GET_BITS(pp->head_b_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_041.reg_head_b_lut_x1, GET_BITS(pp->head_b_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_041.reg_head_b_lut_y1, GET_BITS(pp->head_b_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_042.reg_head_b_lut_x2, GET_BITS(pp->head_b_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_042.reg_head_b_lut_y2, GET_BITS(pp->head_b_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_043.reg_head_b_lut_x3, GET_BITS(pp->head_b_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_043.reg_head_b_lut_y3, GET_BITS(pp->head_b_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_044.reg_head_b_lut_x4, GET_BITS(pp->head_b_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_044.reg_head_b_lut_y4, GET_BITS(pp->head_b_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_045.reg_head_b_lut_x5, GET_BITS(pp->head_b_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_045.reg_head_b_lut_y5, GET_BITS(pp->head_b_lut_y[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_046.reg_body_r_lut_x0, GET_BITS(pp->body_r_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_046.reg_body_r_lut_y0, GET_BITS(pp->body_r_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_047.reg_body_r_lut_x1, GET_BITS(pp->body_r_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_047.reg_body_r_lut_y1, GET_BITS(pp->body_r_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_048.reg_body_r_lut_x2, GET_BITS(pp->body_r_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_048.reg_body_r_lut_y2, GET_BITS(pp->body_r_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_049.reg_body_r_lut_x3, GET_BITS(pp->body_r_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_049.reg_body_r_lut_y3, GET_BITS(pp->body_r_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_050.reg_body_r_lut_x4, GET_BITS(pp->body_r_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_050.reg_body_r_lut_y4, GET_BITS(pp->body_r_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_051.reg_body_r_lut_x5, GET_BITS(pp->body_r_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_051.reg_body_r_lut_y5, GET_BITS(pp->body_r_lut_y[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_052.reg_body_g_lut_x0, GET_BITS(pp->body_g_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_052.reg_body_g_lut_y0, GET_BITS(pp->body_g_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_053.reg_body_g_lut_x1, GET_BITS(pp->body_g_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_053.reg_body_g_lut_y1, GET_BITS(pp->body_g_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_054.reg_body_g_lut_x2, GET_BITS(pp->body_g_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_054.reg_body_g_lut_y2, GET_BITS(pp->body_g_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_055.reg_body_g_lut_x3, GET_BITS(pp->body_g_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_055.reg_body_g_lut_y3, GET_BITS(pp->body_g_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_056.reg_body_g_lut_x4, GET_BITS(pp->body_g_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_056.reg_body_g_lut_y4, GET_BITS(pp->body_g_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_057.reg_body_g_lut_x5, GET_BITS(pp->body_g_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_057.reg_body_g_lut_y5, GET_BITS(pp->body_g_lut_y[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_058.reg_body_b_lut_x0, GET_BITS(pp->body_b_lut_x[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_058.reg_body_b_lut_y0, GET_BITS(pp->body_b_lut_y[0],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_059.reg_body_b_lut_x1, GET_BITS(pp->body_b_lut_x[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_059.reg_body_b_lut_y1, GET_BITS(pp->body_b_lut_y[1],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_060.reg_body_b_lut_x2, GET_BITS(pp->body_b_lut_x[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_060.reg_body_b_lut_y2, GET_BITS(pp->body_b_lut_y[2],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_061.reg_body_b_lut_x3, GET_BITS(pp->body_b_lut_x[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_061.reg_body_b_lut_y3, GET_BITS(pp->body_b_lut_y[3],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_062.reg_body_b_lut_x4, GET_BITS(pp->body_b_lut_x[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_062.reg_body_b_lut_y4, GET_BITS(pp->body_b_lut_y[4],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_063.reg_body_b_lut_x5, GET_BITS(pp->body_b_lut_x[5],0,10));
		PE_CHPI_OBC_HW_O24F22_USER(p_obe,reg_obe_ctrl_063.reg_body_b_lut_y5, GET_BITS(pp->body_b_lut_y[5],0,10));
		#endif
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_OBC_HW_O24F22_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	#if 0 // not used
	UINT32 enable;
	PE_RCE_OBJT_HW_PARAM_DATA_O24F22_T *p_rco = &_g_pe_rco_hw_param_data_o24f22;
	PE_RCE_FACE_HW_PARAM_DATA_O24F22_T *p_rcf = &_g_pe_rcf_hw_param_data_o24f22;
	do{
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_rcf->reg_user.data);
		CHECK_KNULL(p_rcf->reg_mask.data);
		CHECK_KNULL(p_rco->reg_user.data);
		CHECK_KNULL(p_rco->reg_mask.data);
		enable = (*onoff > 0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_O24F22_Wr(rco.reg_rce_objt_ctrl_00.reg_psp_en,enable);
		PE_CHPI_TBL0_O24F22_WrFL(rco.reg_rce_objt_ctrl_00.udata32);
		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_RCO);
		/* set user */
		PE_CHPI_OBC_HW_O24F22_USER(p_rco,reg_rce_objt_ctrl_00.reg_psp_en,enable);
		/* set tbl */
		PE_CHPI_TBL0_O24F22_Wr(rcf.reg_rce_face_ctrl_00.reg_psp_en,enable);
		PE_CHPI_TBL0_O24F22_WrFL(rcf.reg_rce_face_ctrl_00.udata32);
		/* count */
		PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_RCF);
		/* set user */
		PE_CHPI_OBC_HW_O24F22_USER(p_rcf,reg_rce_face_ctrl_00.reg_psp_en,enable);
	}while(0);
	#endif
	return ret;
}

