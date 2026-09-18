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

/** @file pe_chpi_tnr_hw_o22.c
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
#include "pe_hw_o22.h"
#include "pe_reg_o22.h"
#include "pe_fwi_o22.h"
#include "pe_inf_o22.h"
#include "pe_tnr_hw_param_o22.h"
#include "pe_chpi_tnr_hw_o22f22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_TNR_HW_O22F22_ENABLE

#define PE_CHPI_TNR_HW_O22F22_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_TNR_HW_O22F22_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_O22_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_O22_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_O22_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_O22_T *data;
	} reg_data;
} PE_CHPI_TNR_HW_PARAM_DATA_O22F22_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
extern const PE_REG_PARAM_T tnr_l_sd_default_o22[];
extern const PE_REG_PARAM_T tnr_l_hd_i_default_o22[];
extern const PE_REG_PARAM_T tnr_l_hd_p_default_o22[];
extern const PE_REG_PARAM_T tnr_l_ud_default_o22[];
extern const PE_REG_PARAM_T tnr_l_lut_hd_default_o22[];
extern const PE_REG_PARAM_T tnr_l_hd_i_default_o22_webos22[];
extern const PE_REG_PARAM_T tnr_l_hd_p_default_o22_webos22[];
extern const UINT32 sqm_tnr_init_o22[];

extern const PE_REG_PARAM_T tnr_l_sd_default_o22f22[];
extern const PE_REG_PARAM_T tnr_l_hd_i_default_o22f22[];
extern const PE_REG_PARAM_T tnr_l_hd_p_default_o22f22[];
extern const PE_REG_PARAM_T tnr_l_ud_default_o22f22[];
extern const PE_REG_PARAM_T tnr_l_8k_default_o22f22[];
extern const PE_REG_PARAM_T tnr_l_lut_hd_default_o22f22[];
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
#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
static PE_CHPI_TNR_HW_PARAM_DATA_O22F22_T _g_pe_tnr_hw_param_data_o22f22 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static int PE_CHPI_TNR_HW_O22F22_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
	PE_CHPI_TNR_HW_PARAM_DATA_O22F22_T *p_tnr = &_g_pe_tnr_hw_param_data_o22f22;

	/* create dflt table */
	if (p_tnr->reg_dflt.addr == NULL)
	{
		p_tnr->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O22_T));
	}
	/* create user table */
	if (p_tnr->reg_user.addr == NULL)
	{
		p_tnr->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O22_T));
		memset((p_tnr->reg_user.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_O22_T));	// 0x0
	}
	/* create mask table */
	if (p_tnr->reg_mask.addr == NULL)
	{
		p_tnr->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O22_T));
		memset((p_tnr->reg_mask.addr), -1, sizeof(PE_TNR_HW_PARAM_REG_O22_T));// 0xffffffff
	}
	/* create data table */
	if (p_tnr->reg_data.addr == NULL)
	{
		p_tnr->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O22_T));
		memset((p_tnr->reg_data.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_O22_T));	// 0x0
	}
	/* report srsult */
	if (p_tnr->reg_dflt.addr != NULL && p_tnr->reg_user.addr != NULL && \
		p_tnr->reg_mask.addr != NULL && p_tnr->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_tnr]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_tnr]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_tnr->reg_dflt.addr == NULL)? "x":"o", \
			(p_tnr->reg_user.addr == NULL)? "x":"o", \
			(p_tnr->reg_mask.addr == NULL)? "x":"o", \
			(p_tnr->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}
	#endif

	return ret;
}

static PE_CHPI_TNR_HW_O22F22_TNR_FMT PE_CHPI_TNR_HW_O22F22_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_TNR_HW_O22F22_TNR_FMT tnr_fmt = PE_CHPI_TNR_O22F22_TNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			tnr_fmt = PE_CHPI_TNR_O22F22_TNR_SD;
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_CHPI_TNR_O22F22_TNR_HD_I;
				else
					tnr_fmt = PE_CHPI_TNR_O22F22_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_UD;
			}
			else
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_UD_8K;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_CHPI_TNR_O22F22_TNR_HD_I;
				else
					tnr_fmt = PE_CHPI_TNR_O22F22_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_UD;
			}
			else
			{
				tnr_fmt = PE_CHPI_TNR_O22F22_TNR_UD_8K;
			}
			break;
	}
	return tnr_fmt;
}

static int PE_CHPI_TNR_HW_O22F22_SetTnrDefault(PE_CHPI_TNR_HW_O22F22_TNR_FMT cur0_tnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_tnr_hw_param_data_o22f22.reg_dflt.addr;
	UINT32 *p_user = _g_pe_tnr_hw_param_data_o22f22.reg_user.addr;
	UINT32 *p_mask = _g_pe_tnr_hw_param_data_o22f22.reg_mask.addr;
	UINT32 *p_data = _g_pe_tnr_hw_param_data_o22f22.reg_data.addr;
	UINT32 tnr_ctrl_19[4];
	UINT32 tnr_ctrl_16;
	UINT32 tnr_ctrl_17;

	PE_CHPI_TNR_HW_O22F22_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_TNR_HW_O22F22_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_TNR_HW_O22F22_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_TNR_HW_O22F22_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_tnr_fmt)
	{
		case PE_CHPI_TNR_O22F22_TNR_SD:
			p_dflt_param = tnr_l_sd_default_o22f22;
			break;
		case PE_CHPI_TNR_O22F22_TNR_HD_I:
			p_dflt_param = tnr_l_hd_i_default_o22f22;
			break;
		case PE_CHPI_TNR_O22F22_TNR_HD_P:
			p_dflt_param = tnr_l_hd_p_default_o22f22;
			break;
		case PE_CHPI_TNR_O22F22_TNR_UD:
			p_dflt_param = tnr_l_ud_default_o22f22;
			break;
		case PE_CHPI_TNR_O22F22_TNR_UD_8K:
			p_dflt_param = tnr_l_8k_default_o22f22;
			break;
		default:
			p_dflt_param = tnr_l_ud_default_o22f22;
			break;
	}

	size = sizeof(PE_TNR_HW_PARAM_REG_O22_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size-1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);
	tnr_ctrl_19[0] = p_data[19]&0xFFFFFCFF; //reg_col_overlap_mode = 0
	tnr_ctrl_19[1] = tnr_ctrl_19[2]= (p_data[19]&0xFFFFFCFF)|0x100; //reg_col_overlap_mode =1
	tnr_ctrl_19[3] = (p_data[19]&0xFFFFFCFF)|0x200; //reg_col_overlap_mode =2
	/* set large block */
	tnr_ctrl_16    = p_data[16]&0xFF00FFFF;
	tnr_ctrl_16    = tnr_ctrl_16|0x00C40000; //reg_n_hblk=4, reg_v_hblk=12
	tnr_ctrl_17    = 0x01E00168; //  reg_blk_hsize=480, reg_blk_vsize=360 
	do{
		if (!gPE_CHPI_DDR_O22)	break;
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_00.udata32,p_data[0]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_01.udata32,p_data[1]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_02.udata32,p_data[2]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_03.udata32,p_data[3]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_04.udata32,p_data[4]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_05.udata32,p_data[5]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_06.udata32,p_data[6]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_07.udata32,p_data[7]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_08.udata32,p_data[8]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_09.udata32,p_data[9]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_10.udata32,p_data[10]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_11.udata32,p_data[11]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_12.udata32,p_data[12]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_13.udata32,p_data[13]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_14.udata32,p_data[14]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_15.udata32,p_data[15]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_16.udata32,tnr_ctrl_16);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_17.udata32,tnr_ctrl_17);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_18.udata32,p_data[18]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr0_ctrl_19.udata32,tnr_ctrl_19[0]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr1_ctrl_19.udata32,tnr_ctrl_19[1]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr2_ctrl_19.udata32,tnr_ctrl_19[2]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr3_ctrl_19.udata32,tnr_ctrl_19[3]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_20.udata32,p_data[20]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_21.udata32,p_data[21]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_22.udata32,p_data[22]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_23.udata32,p_data[23]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_24.udata32,p_data[24]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_25.udata32,p_data[25]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_26.udata32,p_data[26]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_27.udata32,p_data[27]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_28.udata32,p_data[28]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_29.udata32,p_data[29]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_30.udata32,p_data[30]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_31.udata32,p_data[31]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_32.udata32,p_data[32]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_33.udata32,p_data[33]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_34.udata32,p_data[34]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_35.udata32,p_data[35]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_36.udata32,p_data[36]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_37.udata32,p_data[37]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_38.udata32,p_data[38]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_39.udata32,p_data[39]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.mmd_ctrl.udata32,p_data[40]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_40.udata32,p_data[41]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_41.udata32,p_data[42]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_42.udata32,p_data[43]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_43.udata32,p_data[44]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_44.udata32,p_data[45]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_45.udata32,p_data[46]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_46.udata32,p_data[47]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_47.udata32,p_data[48]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_48.udata32,p_data[49]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_etc_ctrl_02.udata32,p_data[50]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_56.udata32,p_data[51]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_57.udata32,p_data[52]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_58.udata32,p_data[53]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_59.udata32,p_data[54]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_60.udata32,p_data[55]);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_61.udata32,p_data[56]);

		/* count */
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_TNR);
	}while(0);
	#endif

	return ret;
}

int PE_CHPI_TNR_HW_O22F22_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_O22_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_TNR_HW_O22F22_TNR_FMT pre0_tnr_fmt = PE_CHPI_TNR_O22F22_TNR_NUM;
	PE_CHPI_TNR_HW_O22F22_TNR_FMT cur0_tnr_fmt;
	do{
		ret = PE_INF_O22_GetCurInfSettings(&inf_set);
		PE_CHPI_TNR_HW_O22F22_CHECK_CODE(ret,break,"PE_INF_O22_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_tnr_fmt = PE_CHPI_TNR_HW_O22F22_ConvDispInfoToTnrFmt(disp0_inf);
		if(pre0_tnr_fmt!=cur0_tnr_fmt)
		{
			ret = PE_CHPI_TNR_HW_O22F22_SetTnrDefault(cur0_tnr_fmt);
			PE_CHPI_TNR_HW_O22F22_CHECK_CODE(ret,break,"PE_CHPI_TNR_HW_O22F22_SetTnrDefault() error\n");
			pre0_tnr_fmt=cur0_tnr_fmt;
		}
	}while(0);
	return ret;
}

#if (CONFIG_LX_O22_CHIP_FIRMWARE == 1)
int PE_CHPI_TNR_HW_O22F22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
	UINT32 i;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_TNR_HW_O22F22_CreateDataTable();
		if (ret)	break;
		if (pstParams->resume_mode == 1)	break;//if qsm,skip
 		if (!gPE_CHPI_DDR_O22)	break;

		/* addr */
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_00.uaddr32,0xF200048C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_01.uaddr32,0xF2000144);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_02.uaddr32,0xF2000148);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_03.uaddr32,0xF200014C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_04.uaddr32,0xF2000150);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_05.uaddr32,0xF2000154);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_06.uaddr32,0xF2000158);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_07.uaddr32,0xF200015C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_08.uaddr32,0xF2000160);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_09.uaddr32,0xF2000164);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_10.uaddr32,0xF2000168);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_11.uaddr32,0xF200016C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_12.uaddr32,0xF2000170);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_13.uaddr32,0xF2000174);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_14.uaddr32,0xF2000178);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_15.uaddr32,0xF200017C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_16.uaddr32,0xF2000180);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_17.uaddr32,0xF2000184);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_18.uaddr32,0xF2000188);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr0_ctrl_19.uaddr32,0xF200018C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr1_ctrl_19.uaddr32,0xF200318C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr2_ctrl_19.uaddr32,0xF200518C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr3_ctrl_19.uaddr32,0xF200718C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_20.uaddr32,0xF2000190);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_21.uaddr32,0xF2000194);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_22.uaddr32,0xF2000198);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_23.uaddr32,0xF200019C);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_24.uaddr32,0xF20001A0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_25.uaddr32,0xF20001A4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_26.uaddr32,0xF20001A8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_27.uaddr32,0xF20001AC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_28.uaddr32,0xF20001B0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_29.uaddr32,0xF20001B4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_30.uaddr32,0xF20001B8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_31.uaddr32,0xF20001BC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_32.uaddr32,0xF20001E0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_33.uaddr32,0xF20001E4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_34.uaddr32,0xF20001E8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_35.uaddr32,0xF20001EC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_36.uaddr32,0xF20001F0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_37.uaddr32,0xF20001F4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_38.uaddr32,0xF20001F8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_39.uaddr32,0xF20001FC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.mmd_ctrl.uaddr32,   0xF20002E0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_40.uaddr32,0xF20003D0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_41.uaddr32,0xF20003D4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_42.uaddr32,0xF20003D8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_43.uaddr32,0xF20003DC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_44.uaddr32,0xF20003E0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_45.uaddr32,0xF20003E4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_46.uaddr32,0xF20003E8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_47.uaddr32,0xF20003EC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_48.uaddr32,0xF20003F0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_etc_ctrl_02.uaddr32,0xF2000498);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_56.uaddr32,0xF20004A0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_57.uaddr32,0xF20004A4);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_58.uaddr32,0xF20004A8);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_59.uaddr32,0xF20004AC);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_60.uaddr32,0xF20004B0);
		PE_CHPI_TBL0_O22F22_QWr(tnr.tnr_ctrl_61.uaddr32,0xF20004B4);

		/* init */
		PE_CHPI_TNR_HW_O22F22_SetTnrDefault(PE_CHPI_TNR_O22F22_TNR_HD_P);

		/* download tnr sqm db */
		/* see PE_NRD_HW_O22_DownloadTnrSqmCmnInitDb */
		/* PE_CHPI_TNR_SQM_O22F22_T                 sqm2;//13 */
		PE_CHPI_TBL0_O22F22_QWr(sqm2.ui32,0);
		for (i=0; i<11; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(sqm2.data32[i],sqm_tnr_init_o22[i]);
		}
		PE_CHPI_TBL0_O22F22_QWr(sqm2.cnt32,0);

		/* download tnr user db */
		/* see PE_NRD_HW_O22_DownloadTnrDb */
		/* PE_CHPI_TNR_USER_O22F22_T                usr0;//17 */
		PE_CHPI_TBL0_O22F22_QWr(usr0.ui32,0);
		for (i=0; i<16; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i],tnr_l_lut_hd_default_o22f22[i+7].data);
		}
		for (i=0; i<5; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i+16],0);
		}
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i+16+5],0);
		}
		PE_CHPI_TBL0_O22F22_QWr(usr0.cnt32,0);

		/* count */
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_SQM2);
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_USR0);

		PE_INF_HW_O22_BACKUP_CHPI1("[TBL][TNR]done(resume:%d)",pstParams->resume_mode);
	}while(0);
	#endif
	return ret;
}
#else
int PE_CHPI_TNR_HW_O22F22_Init(PE_CFG_CTRL_T *pstParams)
{
	 PE_PRINT_NOTI("not supported\n");
	 return RET_ERROR;
}
#endif


int PE_CHPI_TNR_HW_O22F22_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
	UINT32 i;
	LX_PE_NRD_TNR_CMN_T *p_param;
	LX_PE_NRD_TNR_ALL_CMN_T *pp;
	PE_CHPI_TNR_HW_PARAM_DATA_O22F22_T *p_tnr = &_g_pe_tnr_hw_param_data_o22f22;
	do{
 		if (!gPE_CHPI_DDR_O22)	break;
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_tnr->reg_user.data);
		CHECK_KNULL(p_tnr->reg_mask.data);
		p_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
		pp = (LX_PE_NRD_TNR_ALL_CMN_T *)p_param->data;

		/* set tbl */
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_00.reg_sad_8x3_iir_alpha,GET_BITS(pp->tnr0__ctl[0],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_00.reg_sad_8x3_chroma_en,GET_BITS(pp->tnr0__ctl[1],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_00.reg_sad_8x3_iir_en,GET_BITS(pp->tnr0__ctl[2],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_00.reg_sad_8x3_res,GET_BITS(pp->tnr0__ctl[3],0,2));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_th_memc,GET_BITS(pp->tnr0__ctl[4],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_th_ma,GET_BITS(pp->tnr0__ctl[5],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_out_mode,GET_BITS(pp->tnr0__ctl[6],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_chroma_gain,GET_BITS(pp->tnr0__ctl[7],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_max_flt_tap,GET_BITS(pp->tnr0__ctl[8],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_scale,GET_BITS(pp->tnr0__ctl[9],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_chroma_en,GET_BITS(pp->tnr0__ctl[10],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_calc_prev_hist,GET_BITS(pp->tnr0__ctl[11],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_max_flt_en,GET_BITS(pp->tnr0__ctl[12],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_02.sc_en,GET_BITS(pp->tnr0__ctl[13],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_05.reg_mamc_mc_sad_cut,GET_BITS(pp->tnr0__ctl[14],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_05.reg_mamc_ma_sad_cut,GET_BITS(pp->tnr0__ctl[15],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_05.reg_mamc_blend_mv_max_or_sum,GET_BITS(pp->tnr0__ctl[16],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_05.reg_mamc_blend_mode,GET_BITS(pp->tnr0__ctl[17],0,2));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_06.reg_me_pv_base,GET_BITS(pp->tnr0__ctl[18],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_06.reg_me_lb_base,GET_BITS(pp->tnr0__ctl[19],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_21.reg_svar_scale,GET_BITS(pp->tnr0__ctl[20],0,3));
		/*tnr0___ma*/
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_07.reg_sc_en,GET_BITS(pp->tnr0___ma[0],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_07.reg_5x5_sad_cut,GET_BITS(pp->tnr0___ma[1],0,2));
		/*tnr0___me*/
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_09.reg_pv_smooth_clip,GET_BITS(pp->tnr0___me[0],0,6));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_09.reg_lb_smooth_clip,GET_BITS(pp->tnr0___me[1],0,6));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_09.reg_sad_base,GET_BITS(pp->tnr0___me[2],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_11.reg_me_n15_protection,GET_BITS(pp->tnr0___me[3],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_11.pv_smooth_en,GET_BITS(pp->tnr0___me[4],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_11.lb_smooth_en,GET_BITS(pp->tnr0___me[5],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_13.reg_zero_sad_adv,GET_BITS(pp->tnr0___me[6],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_13.reg_zero_sad_ratio,GET_BITS(pp->tnr0___me[7],0,8));
		/*tnr0__mlb*/
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_16.reg_sad_acc_mode,GET_BITS(pp->tnr0__mlb[0],0,2));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bmv_pmv_tl_en,GET_BITS(pp->tnr0__mlb[1],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bmv_pmv_tl,GET_BITS(pp->tnr0__mlb[2],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bmv_gmv_tl_en,GET_BITS(pp->tnr0__mlb[3],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bmv_gmv_tl,GET_BITS(pp->tnr0__mlb[4],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_gmv_gmv_tl_en,GET_BITS(pp->tnr0__mlb[5],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_gmv_gmv_tl,GET_BITS(pp->tnr0__mlb[6],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_gsad_scale,GET_BITS(pp->tnr0__mlb[7],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bmv_rst_mode,GET_BITS(pp->tnr0__mlb[8],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_18.reg_bsad_scale,GET_BITS(pp->tnr0__mlb[9],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr0_ctrl_19.bmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[10],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr0_ctrl_19.bmv_0mv_tl,GET_BITS(pp->tnr0__mlb[11],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr0_ctrl_19.gmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[12],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr0_ctrl_19.gmv_0mv_tl,GET_BITS(pp->tnr0__mlb[13],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr0_ctrl_19.bmv_coring_th,GET_BITS(pp->tnr0__mlb[14],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr1_ctrl_19.bmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[10],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr1_ctrl_19.bmv_0mv_tl,GET_BITS(pp->tnr0__mlb[11],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr1_ctrl_19.gmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[12],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr1_ctrl_19.gmv_0mv_tl,GET_BITS(pp->tnr0__mlb[13],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr1_ctrl_19.bmv_coring_th,GET_BITS(pp->tnr0__mlb[14],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr2_ctrl_19.bmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[10],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr2_ctrl_19.bmv_0mv_tl,GET_BITS(pp->tnr0__mlb[11],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr2_ctrl_19.gmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[12],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr2_ctrl_19.gmv_0mv_tl,GET_BITS(pp->tnr0__mlb[13],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr2_ctrl_19.bmv_coring_th,GET_BITS(pp->tnr0__mlb[14],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr3_ctrl_19.bmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[10],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr3_ctrl_19.bmv_0mv_tl,GET_BITS(pp->tnr0__mlb[11],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr3_ctrl_19.gmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[12],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr3_ctrl_19.gmv_0mv_tl,GET_BITS(pp->tnr0__mlb[13],0,7));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr3_ctrl_19.bmv_coring_th,GET_BITS(pp->tnr0__mlb[14],0,8));
		/*tnr0__mc*/
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_chroma_sad_en,GET_BITS(pp->tnr0___mc[0],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_cnt_mode,GET_BITS(pp->tnr0___mc[1],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_avg_cmp_res,GET_BITS(pp->tnr0___mc[2],0,3));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_avg_cmp_en,GET_BITS(pp->tnr0___mc[3],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_5x5_sad_cut,GET_BITS(pp->tnr0___mc[4],0,2));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_chroma_sad_res,GET_BITS(pp->tnr0___mc[5],0,2));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_crgn_gain_en,GET_BITS(pp->tnr0___mc[6],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_luma_gain_en,GET_BITS(pp->tnr0___mc[7],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_24.reg_ombc_en,GET_BITS(pp->tnr0___mc[8],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_x3,GET_BITS(pp->tnr0___mc[9],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_y3,GET_BITS(pp->tnr0___mc[10],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_x2,GET_BITS(pp->tnr0___mc[11],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_y2,GET_BITS(pp->tnr0___mc[12],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_x1,GET_BITS(pp->tnr0___mc[13],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_y1,GET_BITS(pp->tnr0___mc[14],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_28.reg_tnr_final_lut_yy_x0,GET_BITS(pp->tnr0___mc[15],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_28.reg_tnr_final_lut_yy_y0,GET_BITS(pp->tnr0___mc[16],0,10));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_x3,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_y3,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_x2,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_y2,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_x1,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_y1,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_31.reg_tnr_final_lut_cb_x0,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_31.reg_tnr_final_lut_cb_y0,0x0);
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_32.reg_blur_coef,GET_BITS(pp->tnr0___mc[25],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_32.reg_gf_gain,GET_BITS(pp->tnr0___mc[26],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_33.reg_move_step,GET_BITS(pp->tnr0___mc[27],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_33.reg_same_sad_th,GET_BITS(pp->tnr0___mc[28],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_33.reg_p_mv0_only,GET_BITS(pp->tnr0___mc[29],0,1));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_33.same_protection_en,GET_BITS(pp->tnr0___mc[30],0,1));
		/*tnr0_blnd*/
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[0],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[1],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[2],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[3],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[4],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[5],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[6],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[7],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[8],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[9],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[10],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[11],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[12],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[13],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[14],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[15],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[16],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[17],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[18],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[19],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[20],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[21],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[22],0,8));
		PE_CHPI_TBL0_O22F22_Wr(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[23],0,8));

		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_00.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_02.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_05.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_06.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_21.udata32);
		/*tnr0___ma*/
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_07.udata32);
		/*tnr0___me*/
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_09.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_11.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_13.udata32);
		/*tnr0__mlb*/
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_16.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_18.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr0_ctrl_19.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr1_ctrl_19.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr2_ctrl_19.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr3_ctrl_19.udata32);
		/*tnr0__mc*/
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_24.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_26.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_27.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_28.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_29.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_30.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_31.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_32.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_33.udata32);
		/*tnr0_blnd*/
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_56.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_57.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_58.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_59.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_60.udata32);
		PE_CHPI_TBL0_O22F22_WrFL(tnr.tnr_ctrl_61.udata32);

		/* download tnr sqm db */
		/* see PE_NRD_HW_O22_DownloadTnrSqmCmnUserDb */
		/* PE_CHPI_TNR_SQM_O22F22_T                 sqm2;//13 */
		PE_CHPI_TBL0_O22F22_QWr(sqm2.ui32,pp->tnr___val);
		for (i=0; i<11; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(sqm2.data32[i],pp->tnr0__sqm[i]);
		}
		i = PE_CHPI_TBL0_O22F22_Rd(sqm2.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O22F22_QWr(sqm2.cnt32,i);

		/* download tnr user db */
		/* see PE_NRD_HW_O22_DownloadTnrUserDb */
		/* PE_CHPI_TNR_USER_O22F22_T                usr0;//17 */
		PE_CHPI_TBL0_O22F22_QWr(usr0.ui32,pp->tnr___val);
		for (i=0; i<16; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i],pp->tnr0__lut[i]);
		}
		for (i=0; i<5; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i+16],pp->tnr0_gain[i]);
		}
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O22F22_QWr(usr0.data32[i+16+5],pp->tnr0_buff[i]);
		}
		i = PE_CHPI_TBL0_O22F22_Rd(usr0.cnt32);
		i = (i<0xff)? (i+1):0;
		PE_CHPI_TBL0_O22F22_QWr(usr0.cnt32,i);

		/* count */
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_TNR);
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_SQM2);
		PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_USR0);

		/* set user */
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_00.reg_sad_8x3_iir_alpha,GET_BITS(pp->tnr0__ctl[0],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_00.reg_sad_8x3_chroma_en,GET_BITS(pp->tnr0__ctl[1],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_00.reg_sad_8x3_iir_en,GET_BITS(pp->tnr0__ctl[2],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_00.reg_sad_8x3_res,GET_BITS(pp->tnr0__ctl[3],0,2));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_th_memc,GET_BITS(pp->tnr0__ctl[4],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_th_ma,GET_BITS(pp->tnr0__ctl[5],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_out_mode,GET_BITS(pp->tnr0__ctl[6],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_chroma_gain,GET_BITS(pp->tnr0__ctl[7],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_max_flt_tap,GET_BITS(pp->tnr0__ctl[8],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_scale,GET_BITS(pp->tnr0__ctl[9],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_chroma_en,GET_BITS(pp->tnr0__ctl[10],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_calc_prev_hist,GET_BITS(pp->tnr0__ctl[11],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_max_flt_en,GET_BITS(pp->tnr0__ctl[12],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_02.sc_en,GET_BITS(pp->tnr0__ctl[13],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_05.reg_mamc_mc_sad_cut,GET_BITS(pp->tnr0__ctl[14],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_05.reg_mamc_ma_sad_cut,GET_BITS(pp->tnr0__ctl[15],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_05.reg_mamc_blend_mv_max_or_sum,GET_BITS(pp->tnr0__ctl[16],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_05.reg_mamc_blend_mode,GET_BITS(pp->tnr0__ctl[17],0,2));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_06.reg_me_pv_base,GET_BITS(pp->tnr0__ctl[18],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_06.reg_me_lb_base,GET_BITS(pp->tnr0__ctl[19],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_21.reg_svar_scale,GET_BITS(pp->tnr0__ctl[20],0,3));
		/*tnr0___ma*/
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_07.reg_sc_en,GET_BITS(pp->tnr0___ma[0],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_07.reg_5x5_sad_cut,GET_BITS(pp->tnr0___ma[1],0,2));
		/*tnr0___me*/
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_09.reg_pv_smooth_clip,GET_BITS(pp->tnr0___me[0],0,6));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_09.reg_lb_smooth_clip,GET_BITS(pp->tnr0___me[1],0,6));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_09.reg_sad_base,GET_BITS(pp->tnr0___me[2],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_11.reg_me_n15_protection,GET_BITS(pp->tnr0___me[3],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_11.pv_smooth_en,GET_BITS(pp->tnr0___me[4],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_11.lb_smooth_en,GET_BITS(pp->tnr0___me[5],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_13.reg_zero_sad_adv,GET_BITS(pp->tnr0___me[6],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_13.reg_zero_sad_ratio,GET_BITS(pp->tnr0___me[7],0,8));
		/*tnr0__mlb*/
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_16.reg_sad_acc_mode,GET_BITS(pp->tnr0__mlb[0],0,2));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bmv_pmv_tl_en,GET_BITS(pp->tnr0__mlb[1],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bmv_pmv_tl,GET_BITS(pp->tnr0__mlb[2],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bmv_gmv_tl_en,GET_BITS(pp->tnr0__mlb[3],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bmv_gmv_tl,GET_BITS(pp->tnr0__mlb[4],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_gmv_gmv_tl_en,GET_BITS(pp->tnr0__mlb[5],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_gmv_gmv_tl,GET_BITS(pp->tnr0__mlb[6],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_gsad_scale,GET_BITS(pp->tnr0__mlb[7],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bmv_rst_mode,GET_BITS(pp->tnr0__mlb[8],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_18.reg_bsad_scale,GET_BITS(pp->tnr0__mlb[9],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_19.bmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[10],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_19.bmv_0mv_tl,GET_BITS(pp->tnr0__mlb[11],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_19.gmv_0mv_tl_en,GET_BITS(pp->tnr0__mlb[12],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_19.gmv_0mv_tl,GET_BITS(pp->tnr0__mlb[13],0,7));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_19.bmv_coring_th,GET_BITS(pp->tnr0__mlb[14],0,8));
		/*tnr0__mc*/
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_chroma_sad_en,GET_BITS(pp->tnr0___mc[0],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_cnt_mode,GET_BITS(pp->tnr0___mc[1],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_avg_cmp_res,GET_BITS(pp->tnr0___mc[2],0,3));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_avg_cmp_en,GET_BITS(pp->tnr0___mc[3],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_5x5_sad_cut,GET_BITS(pp->tnr0___mc[4],0,2));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_chroma_sad_res,GET_BITS(pp->tnr0___mc[5],0,2));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_crgn_gain_en,GET_BITS(pp->tnr0___mc[6],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_luma_gain_en,GET_BITS(pp->tnr0___mc[7],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_24.reg_ombc_en,GET_BITS(pp->tnr0___mc[8],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_26.reg_tnr_final_lut_yy_x3,GET_BITS(pp->tnr0___mc[9],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_26.reg_tnr_final_lut_yy_y3,GET_BITS(pp->tnr0___mc[10],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_26.reg_tnr_final_lut_yy_x2,GET_BITS(pp->tnr0___mc[11],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_27.reg_tnr_final_lut_yy_y2,GET_BITS(pp->tnr0___mc[12],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_27.reg_tnr_final_lut_yy_x1,GET_BITS(pp->tnr0___mc[13],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_27.reg_tnr_final_lut_yy_y1,GET_BITS(pp->tnr0___mc[14],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_28.reg_tnr_final_lut_yy_x0,GET_BITS(pp->tnr0___mc[15],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_28.reg_tnr_final_lut_yy_y0,GET_BITS(pp->tnr0___mc[16],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_29.reg_tnr_final_lut_cb_x3,GET_BITS(pp->tnr0___mc[17],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_29.reg_tnr_final_lut_cb_y3,GET_BITS(pp->tnr0___mc[18],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_29.reg_tnr_final_lut_cb_x2,GET_BITS(pp->tnr0___mc[19],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_30.reg_tnr_final_lut_cb_y2,GET_BITS(pp->tnr0___mc[20],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_30.reg_tnr_final_lut_cb_x1,GET_BITS(pp->tnr0___mc[21],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_30.reg_tnr_final_lut_cb_y1,GET_BITS(pp->tnr0___mc[22],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_31.reg_tnr_final_lut_cb_x0,GET_BITS(pp->tnr0___mc[23],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_31.reg_tnr_final_lut_cb_y0,GET_BITS(pp->tnr0___mc[24],0,10));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_32.reg_blur_coef,GET_BITS(pp->tnr0___mc[25],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_32.reg_gf_gain,GET_BITS(pp->tnr0___mc[26],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_33.reg_move_step,GET_BITS(pp->tnr0___mc[27],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_33.reg_same_sad_th,GET_BITS(pp->tnr0___mc[28],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_33.reg_p_mv0_only,GET_BITS(pp->tnr0___mc[29],0,1));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_33.same_protection_en,GET_BITS(pp->tnr0___mc[30],0,1));
		/*tnr0_blnd*/
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_56.reg_sad_mc_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[0],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_56.reg_sad_mc_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[1],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_56.reg_sad_mc_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[2],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_56.reg_sad_mc_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[3],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_57.reg_sad_mc_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[4],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_57.reg_sad_mc_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[5],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_57.reg_sad_mc_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[6],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_57.reg_sad_mc_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[7],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_58.reg_abs_mv_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[8],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_58.reg_abs_mv_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[9],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_58.reg_abs_mv_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[10],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_58.reg_abs_mv_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[11],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_59.reg_abs_mv_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[12],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_59.reg_abs_mv_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[13],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_59.reg_abs_mv_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[14],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_59.reg_abs_mv_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[15],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_60.reg_sad_ma_ctrl_pt_x1,GET_BITS(pp->tnr0_blnd[16],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_60.reg_sad_ma_ctrl_pt_y1,GET_BITS(pp->tnr0_blnd[17],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_60.reg_sad_ma_ctrl_pt_x0,GET_BITS(pp->tnr0_blnd[18],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_60.reg_sad_ma_ctrl_pt_y0,GET_BITS(pp->tnr0_blnd[19],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_61.reg_sad_ma_ctrl_pt_x3,GET_BITS(pp->tnr0_blnd[20],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_61.reg_sad_ma_ctrl_pt_y3,GET_BITS(pp->tnr0_blnd[21],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_61.reg_sad_ma_ctrl_pt_x2,GET_BITS(pp->tnr0_blnd[22],0,8));
		PE_CHPI_TNR_HW_O22F22_USER(p_tnr,tnr_ctrl_61.reg_sad_ma_ctrl_pt_y2,GET_BITS(pp->tnr0_blnd[23],0,8));
	}while(0);
	#endif
	return ret;
}
int PE_CHPI_TNR_HW_O22F22_GetCtrl(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_TNR_HW_O22F22_ENABLE
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	UINT32 *pd32;
	UINT32 i;
	LX_PE_NRD_TNR_ALL_CMN_T stParams;
	LX_PE_NRD_TNR_ALL_CMN_T *pp;
	do{
 		if (!gPE_CHPI_DDR_O22)	break;
		pp = &stParams;
		memset(pp,0,sizeof(LX_PE_NRD_TNR_ALL_CMN_T));//fix warning: 'stParams' is used uninitialized
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_00.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_02.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_05.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_06.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_21.udata32);
		/*tnr0___ma*/
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_07.udata32);
		/*tnr0___me*/
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_09.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_11.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_13.udata32);
		/*tnr0__mlb*/
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_16.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_18.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr0_ctrl_19.udata32);
		/*tnr0__mc*/
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_24.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_26.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_27.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_28.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_29.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_30.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_31.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_32.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_33.udata32);
		/*tnr0_blnd*/
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_56.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_57.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_58.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_59.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_60.udata32);
		PE_CHPI_TBL0_O22F22_RdFL(tnr.tnr_ctrl_61.udata32);
		/* set tbl */
		pp->tnr0__ctl[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_00.reg_sad_8x3_iir_alpha);
		pp->tnr0__ctl[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_00.reg_sad_8x3_chroma_en);
		pp->tnr0__ctl[2] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_00.reg_sad_8x3_iir_en);
		pp->tnr0__ctl[3] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_00.reg_sad_8x3_res);
		pp->tnr0__ctl[4] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_th_memc);
		pp->tnr0__ctl[5] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_th_ma);
		pp->tnr0__ctl[6] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_out_mode);
		pp->tnr0__ctl[7] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_chroma_gain);
		pp->tnr0__ctl[8] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_max_flt_tap);
		pp->tnr0__ctl[9] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_scale);
		pp->tnr0__ctl[10]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_chroma_en);
		pp->tnr0__ctl[11]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_calc_prev_hist);
		pp->tnr0__ctl[12]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_max_flt_en);
		pp->tnr0__ctl[13]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_02.sc_en);
		pp->tnr0__ctl[14]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_05.reg_mamc_mc_sad_cut);
		pp->tnr0__ctl[15]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_05.reg_mamc_ma_sad_cut);
		pp->tnr0__ctl[16]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_05.reg_mamc_blend_mv_max_or_sum);
		pp->tnr0__ctl[17]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_05.reg_mamc_blend_mode);
		pp->tnr0__ctl[18]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_06.reg_me_pv_base);
		pp->tnr0__ctl[19]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_06.reg_me_lb_base);
		pp->tnr0__ctl[20]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_21.reg_svar_scale);
		/*tnr0___ma*/
		pp->tnr0___ma[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_07.reg_sc_en);
		pp->tnr0___ma[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_07.reg_5x5_sad_cut);
		/*tnr0___me*/
		pp->tnr0___me[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_09.reg_pv_smooth_clip);
		pp->tnr0___me[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_09.reg_lb_smooth_clip);
		pp->tnr0___me[2] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_09.reg_sad_base);
		pp->tnr0___me[3] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_11.reg_me_n15_protection);
		pp->tnr0___me[4] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_11.pv_smooth_en);
		pp->tnr0___me[5] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_11.lb_smooth_en);
		pp->tnr0___me[6] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_13.reg_zero_sad_adv);
		pp->tnr0___me[7] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_13.reg_zero_sad_ratio);
		/*tnr0__mlb*/
		pp->tnr0__mlb[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_16.reg_sad_acc_mode);
		pp->tnr0__mlb[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bmv_pmv_tl_en);
		pp->tnr0__mlb[2] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bmv_pmv_tl);
		pp->tnr0__mlb[3] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bmv_gmv_tl_en);
		pp->tnr0__mlb[4] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bmv_gmv_tl);
		pp->tnr0__mlb[5] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_gmv_gmv_tl_en);
		pp->tnr0__mlb[6] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_gmv_gmv_tl);
		pp->tnr0__mlb[7] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_gsad_scale);
		pp->tnr0__mlb[8] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bmv_rst_mode);
		pp->tnr0__mlb[9] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_18.reg_bsad_scale);
		pp->tnr0__mlb[10]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr0_ctrl_19.bmv_0mv_tl_en);
		pp->tnr0__mlb[11]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr0_ctrl_19.bmv_0mv_tl);
		pp->tnr0__mlb[12]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr0_ctrl_19.gmv_0mv_tl_en);
		pp->tnr0__mlb[13]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr0_ctrl_19.gmv_0mv_tl);
		pp->tnr0__mlb[14]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr0_ctrl_19.bmv_coring_th);
		/*tnr0__mc*/
		pp->tnr0___mc[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_chroma_sad_en);
		pp->tnr0___mc[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_cnt_mode);
		pp->tnr0___mc[2] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_avg_cmp_res);
		pp->tnr0___mc[3] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_avg_cmp_en);
		pp->tnr0___mc[4] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_5x5_sad_cut);
		pp->tnr0___mc[5] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_chroma_sad_res);
		pp->tnr0___mc[6] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_crgn_gain_en);
		pp->tnr0___mc[7] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_luma_gain_en);
		pp->tnr0___mc[8] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_24.reg_ombc_en);
		pp->tnr0___mc[9] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_x3);
		pp->tnr0___mc[10]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_y3);
		pp->tnr0___mc[11]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_26.reg_tnr_final_lut_yy_x2);
		pp->tnr0___mc[12]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_y2);
		pp->tnr0___mc[13]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_x1);
		pp->tnr0___mc[14]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_27.reg_tnr_final_lut_yy_y1);
		pp->tnr0___mc[15]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_28.reg_tnr_final_lut_yy_x0);
		pp->tnr0___mc[16]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_28.reg_tnr_final_lut_yy_y0);
		pp->tnr0___mc[17]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_x3);
		pp->tnr0___mc[18]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_y3);
		pp->tnr0___mc[19]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_29.reg_tnr_final_lut_cb_x2);
		pp->tnr0___mc[20]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_y2);
		pp->tnr0___mc[21]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_x1);
		pp->tnr0___mc[22]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_30.reg_tnr_final_lut_cb_y1);
		pp->tnr0___mc[23]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_31.reg_tnr_final_lut_cb_x0);
		pp->tnr0___mc[24]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_31.reg_tnr_final_lut_cb_y0);
		pp->tnr0___mc[25]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_32.reg_blur_coef);
		pp->tnr0___mc[26]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_32.reg_gf_gain);
		pp->tnr0___mc[27]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_33.reg_move_step);
		pp->tnr0___mc[28]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_33.reg_same_sad_th);
		pp->tnr0___mc[29]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_33.reg_p_mv0_only);
		pp->tnr0___mc[30]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_33.same_protection_en);
		/*tnr0_blnd*/
		pp->tnr0_blnd[0] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_x1);
		pp->tnr0_blnd[1] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_y1);
		pp->tnr0_blnd[2] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_x0);
		pp->tnr0_blnd[3] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_56.reg_sad_mc_ctrl_pt_y0);
		pp->tnr0_blnd[4] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_x3);
		pp->tnr0_blnd[5] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_y3);
		pp->tnr0_blnd[6] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_x2);
		pp->tnr0_blnd[7] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_57.reg_sad_mc_ctrl_pt_y2);
		pp->tnr0_blnd[8] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_x1);
		pp->tnr0_blnd[9] =PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_y1);
		pp->tnr0_blnd[10]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_x0);
		pp->tnr0_blnd[11]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_58.reg_abs_mv_ctrl_pt_y0);
		pp->tnr0_blnd[12]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_x3);
		pp->tnr0_blnd[13]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_y3);
		pp->tnr0_blnd[14]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_x2);
		pp->tnr0_blnd[15]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_59.reg_abs_mv_ctrl_pt_y2);
		pp->tnr0_blnd[16]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_x1);
		pp->tnr0_blnd[17]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_y1);
		pp->tnr0_blnd[18]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_x0);
		pp->tnr0_blnd[19]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_60.reg_sad_ma_ctrl_pt_y0);
		pp->tnr0_blnd[20]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_x3);
		pp->tnr0_blnd[21]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_y3);
		pp->tnr0_blnd[22]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_x2);
		pp->tnr0_blnd[23]=PE_CHPI_TBL0_O22F22_Rd(tnr.tnr_ctrl_61.reg_sad_ma_ctrl_pt_y2);


		/* download tnr sqm db */
		/* see PE_NRD_HW_O22_DownloadTnrSqmCmnUserDb */
		/* PE_CHPI_TNR_SQM_O22F22_T				 sqm2;//13 */
		PE_CHPI_TBL0_O22F22_QRd(sqm2.ui32,pp->tnr___val);
		for (i=0; i<11; i++)
		{
			PE_CHPI_TBL0_O22F22_QRd(sqm2.data32[i],pp->tnr0__sqm[i]);
		}
		i = PE_CHPI_TBL0_O22F22_Rd(sqm2.cnt32);

		/* download tnr user db */
		/* see PE_NRD_HW_O22_DownloadTnrUserDb */
		/* PE_CHPI_TNR_USER_O22F22_T				 usr0;//17 */
		PE_CHPI_TBL0_O22F22_QRd(usr0.ui32,pp->tnr___val);
		for (i=0; i<16; i++)
		{
			PE_CHPI_TBL0_O22F22_QRd(usr0.data32[i],pp->tnr0__lut[i]);
		}
		for (i=0; i<5; i++)
		{
			PE_CHPI_TBL0_O22F22_QRd(usr0.data32[i+16],pp->tnr0_gain[i]);
		}
		for (i=0; i<15; i++)
		{
			PE_CHPI_TBL0_O22F22_QRd(usr0.data32[i+16+5],pp->tnr0_buff[i]);
		}
		i = PE_CHPI_TBL0_O22F22_Rd(usr0.cnt32);

		pd32 = pp->tnr0__lut;
		printk("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
		printk( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],  pd32[1],	pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],  pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = pp->tnr0_gain;
		printk(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],  pd32[1],	pd32[2],  pd32[3], pd32[4]);
		pd32 = pp->tnr0_buff;
		printk(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],  pd32[1],	pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],  pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = pp->tnr0__ctl;
		printk("set[%d] : tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);

		pd = pp->tnr0___ma;
		printk("set[%d] : tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1]);

		pd = pp->tnr0___me;
		printk("set[%d] : tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

		pd = pp->tnr0__mlb;
		printk("set[%d] : tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);

		pd16 = pp->tnr0___mc;
		printk("set[%d] : tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pp->win_id, \
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);

		pd = pp->tnr0_blnd;
		printk("set[%d] : tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);

		pd32 = pp->tnr0__sqm;
		printk("[%d]tnr0__sqm:%d, cnt:%d\n", pp->win_id, pp->tnr___val, i);
		printk( \
		"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__sqm[10]0x%08X\n", \
		pd32[0],  pd32[1],	pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],  pd32[9],	pd32[10]);

	}while(0);
	#endif
	return ret;
}


