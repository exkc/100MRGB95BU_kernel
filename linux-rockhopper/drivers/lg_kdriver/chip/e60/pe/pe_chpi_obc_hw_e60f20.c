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

/** @file pe_chpi_obc_hw_e60.c
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
#include "pe_chpi_obc_hw_e60f20.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_OBC_HW_E60F20_ENABLE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CHPI_OBC_HW_E60F20_CHECK_CODE(_checker, _action, fmt, args...)	\
{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_CHPI_OBC_HW_E60F20_USER(_p,_r,_d)	{_p->reg_user.data->_r=(_d);_p->reg_mask.data->_r=0;}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
typedef struct {
	union {
		UINT32			*addr;
		PE_OBC_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBC_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBC_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBC_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_OBC_FACE_HW_PARAM_DATA_E60F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_OBC_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_OBC_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_OBC_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_OBC_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_OBC_OBJT_HW_PARAM_DATA_E60F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_RCE_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RCE_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RCE_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RCE_FACE_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_RCE_FACE_HW_PARAM_DATA_E60F20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_RCE_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_RCE_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_RCE_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_RCE_OBJT_HW_PARAM_REG_E60F20_T *data;
	} reg_data;
} PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
extern const PE_REG_PARAM_T obc_objt_l_sd_default_e60[];
extern const PE_REG_PARAM_T obc_objt_l_hd_default_e60[];
extern const PE_REG_PARAM_T obc_objt_l_ud_default_e60[];
extern const PE_REG_PARAM_T obc_face_l_sd_default_e60[];
extern const PE_REG_PARAM_T obc_face_l_hd_default_e60[];
extern const PE_REG_PARAM_T obc_face_l_ud_default_e60[];
extern const PE_REG_PARAM_T rce_objt_l_sd_default_e60[];
extern const PE_REG_PARAM_T rce_objt_l_hd_default_e60[];
extern const PE_REG_PARAM_T rce_objt_l_ud_default_e60[];
extern const PE_REG_PARAM_T rce_face_l_sd_default_e60[];
extern const PE_REG_PARAM_T rce_face_l_hd_default_e60[];
extern const PE_REG_PARAM_T rce_face_l_ud_default_e60[];

extern const PE_REG_PARAM_T obc_objt_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T obc_objt_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T obc_objt_l_ud_default_e60f20[];
extern const PE_REG_PARAM_T obc_face_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T obc_face_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T obc_face_l_ud_default_e60f20[];
extern const PE_REG_PARAM_T rce_objt_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T rce_objt_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T rce_objt_l_ud_default_e60f20[];
extern const PE_REG_PARAM_T rce_face_l_sd_default_e60f20[];
extern const PE_REG_PARAM_T rce_face_l_hd_default_e60f20[];
extern const PE_REG_PARAM_T rce_face_l_ud_default_e60f20[];
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
#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
static PE_OBC_OBJT_HW_PARAM_DATA_E60F20_T _g_pe_obo_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_OBC_FACE_HW_PARAM_DATA_E60F20_T _g_pe_obf_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T _g_pe_rco_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_RCE_FACE_HW_PARAM_DATA_E60F20_T _g_pe_rcf_hw_param_data_e60f20 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
static int PE_CHPI_OBC_HW_E60F20_CreateDataTable(void)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	PE_OBC_OBJT_HW_PARAM_DATA_E60F20_T *p_obo = &_g_pe_obo_hw_param_data_e60f20;
	PE_OBC_FACE_HW_PARAM_DATA_E60F20_T *p_obf = &_g_pe_obf_hw_param_data_e60f20;
	PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T *p_rco = &_g_pe_rco_hw_param_data_e60f20;
	PE_RCE_FACE_HW_PARAM_DATA_E60F20_T *p_rcf = &_g_pe_rcf_hw_param_data_e60f20;

	/* create dflt table */
	if (p_obo->reg_dflt.addr == NULL)
	{
		p_obo->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_obo->reg_user.addr == NULL)
	{
		p_obo->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_obo->reg_user.addr), 0, sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_obo->reg_mask.addr == NULL)
	{
		p_obo->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_obo->reg_mask.addr), -1, sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_obo->reg_data.addr == NULL)
	{
		p_obo->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_obo->reg_data.addr), 0, sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_obo->reg_dflt.addr != NULL && p_obo->reg_user.addr != NULL && \
		p_obo->reg_mask.addr != NULL && p_obo->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_obo]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_obo]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_obo->reg_dflt.addr == NULL)? "x":"o", \
			(p_obo->reg_user.addr == NULL)? "x":"o", \
			(p_obo->reg_mask.addr == NULL)? "x":"o", \
			(p_obo->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_obf->reg_dflt.addr == NULL)
	{
		p_obf->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_obf->reg_user.addr == NULL)
	{
		p_obf->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_obf->reg_user.addr), 0, sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_obf->reg_mask.addr == NULL)
	{
		p_obf->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_obf->reg_mask.addr), -1, sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_obf->reg_data.addr == NULL)
	{
		p_obf->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_obf->reg_data.addr), 0, sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_obf->reg_dflt.addr != NULL && p_obf->reg_user.addr != NULL && \
		p_obf->reg_mask.addr != NULL && p_obf->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_obf]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_obf]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_obf->reg_dflt.addr == NULL)? "x":"o", \
			(p_obf->reg_user.addr == NULL)? "x":"o", \
			(p_obf->reg_mask.addr == NULL)? "x":"o", \
			(p_obf->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_rco->reg_dflt.addr == NULL)
	{
		p_rco->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_rco->reg_user.addr == NULL)
	{
		p_rco->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_rco->reg_user.addr), 0, sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_rco->reg_mask.addr == NULL)
	{
		p_rco->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_rco->reg_mask.addr), -1, sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_rco->reg_data.addr == NULL)
	{
		p_rco->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));
		memset((p_rco->reg_data.addr), 0, sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_rco->reg_dflt.addr != NULL && p_rco->reg_user.addr != NULL && \
		p_rco->reg_mask.addr != NULL && p_rco->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_rco]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_rco]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_rco->reg_dflt.addr == NULL)? "x":"o", \
			(p_rco->reg_user.addr == NULL)? "x":"o", \
			(p_rco->reg_mask.addr == NULL)? "x":"o", \
			(p_rco->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}

	/* create dflt table */
	if (p_rcf->reg_dflt.addr == NULL)
	{
		p_rcf->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));
	}
	/* create user table */
	if (p_rcf->reg_user.addr == NULL)
	{
		p_rcf->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_rcf->reg_user.addr), 0, sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* create mask table */
	if (p_rcf->reg_mask.addr == NULL)
	{
		p_rcf->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_rcf->reg_mask.addr), -1, sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));// 0xffffffff
	}
	/* create data table */
	if (p_rcf->reg_data.addr == NULL)
	{
		p_rcf->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));
		memset((p_rcf->reg_data.addr), 0, sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T));	// 0x0
	}
	/* report srsult */
	if (p_rcf->reg_dflt.addr != NULL && p_rcf->reg_user.addr != NULL && \
		p_rcf->reg_mask.addr != NULL && p_rcf->reg_data.addr != NULL)
	{
		PE_PRINT_NOTI("[p_rcf]table ready.\n");
	}
	else
	{
		PE_PRINT_NOTI("[p_rcf]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
			(p_rcf->reg_dflt.addr == NULL)? "x":"o", \
			(p_rcf->reg_user.addr == NULL)? "x":"o", \
			(p_rcf->reg_mask.addr == NULL)? "x":"o", \
			(p_rcf->reg_data.addr == NULL)? "x":"o");
		ret = RET_ERROR;
	}
	#endif

	return ret;
}

static PE_CHPI_OBC_HW_E60F20_OBF_FMT PE_CHPI_OBC_HW_E60F20_ConvDispInfoToObfFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_E60F20_OBF_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_E60F20_OBF_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_E60F20_OBF_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_E60F20_OBF_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_E60F20_OBF_UD;
			}
			break;
	}
	return fmt;
}

static PE_CHPI_OBC_HW_E60F20_OBO_FMT PE_CHPI_OBC_HW_E60F20_ConvDispInfoToOboFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_E60F20_OBO_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_E60F20_OBO_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_E60F20_OBO_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_E60F20_OBO_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_E60F20_OBO_UD;
			}
			break;
	}
	return fmt;
}

static PE_CHPI_OBC_HW_E60F20_RCF_FMT PE_CHPI_OBC_HW_E60F20_ConvDispInfoToRcfFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_E60F20_RCF_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_E60F20_RCF_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_E60F20_RCF_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_E60F20_RCF_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_E60F20_RCF_UD;
			}
			break;
	}
	return fmt;
}

static PE_CHPI_OBC_HW_E60F20_RCO_FMT PE_CHPI_OBC_HW_E60F20_ConvDispInfoToRcoFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_CHPI_OBC_HW_E60F20_RCO_FMT fmt;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			fmt = PE_CHPI_OBC_E60F20_RCO_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				fmt = PE_CHPI_OBC_E60F20_RCO_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				fmt = PE_CHPI_OBC_E60F20_RCO_HD;
			}
			else
			{
				fmt = PE_CHPI_OBC_E60F20_RCO_UD;
			}
			break;
	}
	return fmt;
}

static int PE_CHPI_OBC_HW_E60F20_SetOboDefault(PE_CHPI_OBC_HW_E60F20_OBO_FMT cur0_obo_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_obo_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_obo_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_obo_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_obo_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_obo_fmt)
	{
		case PE_CHPI_OBC_E60F20_OBO_SD:
			p_dflt_param = obc_objt_l_sd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_OBO_HD:
			p_dflt_param = obc_objt_l_hd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_OBO_UD:
		default:
			p_dflt_param = obc_objt_l_ud_default_e60f20;
			break;
	}

	size = sizeof(PE_OBC_OBJT_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl00.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl01.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl02.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(obo.edge_th.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(obo.fg_position.udata32,p_data[4]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x0.udata32,p_data[5]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x1.udata32,p_data[6]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x2.udata32,p_data[7]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x3.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y0.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y1.udata32,p_data[10]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y2.udata32,p_data[11]);
	PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y3.udata32,p_data[12]);
	PE_CHPI_TBL0_E60F20_QWr(obo.prob_map.udata32,p_data[13]);
	PE_CHPI_TBL0_E60F20_QWr(obo.ellips_map.udata32,p_data[14]);
	PE_CHPI_TBL0_E60F20_QWr(obo.prob_diff_map.udata32,p_data[15]);
	PE_CHPI_TBL0_E60F20_QWr(obo.object_map.udata32,p_data[16]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_map.udata32,p_data[17]);
	PE_CHPI_TBL0_E60F20_QWr(obo.display_debug_map.udata32,p_data[18]);
	PE_CHPI_TBL0_E60F20_QWr(obo.psp_iir.udata32,p_data[19]);
	PE_CHPI_TBL0_E60F20_QWr(obo.psp_gain.udata32,p_data[20]);
	PE_CHPI_TBL0_E60F20_QWr(obo.vrtx_cpc_ctrl.udata32,p_data[21]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef01.udata32,p_data[22]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef23.udata32,p_data[23]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef45.udata32,p_data[24]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef67.udata32,p_data[25]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef8.udata32,p_data[26]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef01.udata32,p_data[27]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef23.udata32,p_data[28]);
	PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef4.udata32,p_data[29]);
	PE_CHPI_TBL0_E60F20_QWr(obo.l5_gain_lut1.udata32,p_data[30]);
	PE_CHPI_TBL0_E60F20_QWr(obo.l5_gain_lut2.udata32,p_data[31]);
	PE_CHPI_TBL0_E60F20_QWr(obo.l0_gain_lut1.udata32,p_data[32]);
	PE_CHPI_TBL0_E60F20_QWr(obo.l0_gain_lut2.udata32,p_data[33]);
	PE_CHPI_TBL0_E60F20_QWr(obo.edge_win_h.udata32,p_data[34]);
	PE_CHPI_TBL0_E60F20_QWr(obo.edge_win_v.udata32,p_data[35]);
	PE_CHPI_TBL0_E60F20_QWr(obo.psp_iir1.udata32,p_data[36]);
	PE_CHPI_TBL0_E60F20_QWr(obo.bg_measure_ctrl.udata32,p_data[37]);
	PE_CHPI_TBL0_E60F20_QWr(obo.face0_set.udata32,p_data[38]);
	PE_CHPI_TBL0_E60F20_QWr(obo.face1_set.udata32,p_data[39]);
	PE_CHPI_TBL0_E60F20_QWr(obo.face2_set.udata32,p_data[40]);
	PE_CHPI_TBL0_E60F20_QWr(obo.face3_set.udata32,p_data[41]);
	PE_CHPI_TBL0_E60F20_QWr(obo.ellips0_set.udata32,p_data[42]);
	PE_CHPI_TBL0_E60F20_QWr(obo.ellips1_set.udata32,p_data[43]);
	PE_CHPI_TBL0_E60F20_QWr(obo.ellips2_set.udata32,p_data[44]);
	PE_CHPI_TBL0_E60F20_QWr(obo.ellips3_set.udata32,p_data[45]);
	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_OBO);
	#endif

	return ret;
}

static int PE_CHPI_OBC_HW_E60F20_SetObfDefault(PE_CHPI_OBC_HW_E60F20_OBF_FMT cur0_obf_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_obf_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_obf_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_obf_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_obf_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_obf_fmt)
	{
		case PE_CHPI_OBC_E60F20_OBF_SD:
			p_dflt_param = obc_face_l_sd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_OBF_HD:
			p_dflt_param = obc_face_l_hd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_OBF_UD:
		default:
			p_dflt_param = obc_face_l_ud_default_e60f20;
			break;
	}

	size = sizeof(PE_OBC_FACE_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl00.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl01.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl02.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(obf.edge_th.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(obf.fg_position.udata32,p_data[4]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved0.udata32,p_data[5]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved1.udata32,p_data[6]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved2.udata32,p_data[7]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved3.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved4.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved5.udata32,p_data[10]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved6.udata32,p_data[11]);
	PE_CHPI_TBL0_E60F20_QWr(obf.reserved7.udata32,p_data[12]);
	PE_CHPI_TBL0_E60F20_QWr(obf.prob_map.udata32,p_data[13]);
	PE_CHPI_TBL0_E60F20_QWr(obf.ellips_map.udata32,p_data[14]);
	PE_CHPI_TBL0_E60F20_QWr(obf.prob_diff_map.udata32,p_data[15]);
	PE_CHPI_TBL0_E60F20_QWr(obf.object_map.udata32,p_data[16]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_map.udata32,p_data[17]);
	PE_CHPI_TBL0_E60F20_QWr(obf.display_debug_map.udata32,p_data[18]);
	PE_CHPI_TBL0_E60F20_QWr(obf.psp_iir.udata32,p_data[19]);
	PE_CHPI_TBL0_E60F20_QWr(obf.psp_gain.udata32,p_data[20]);
	PE_CHPI_TBL0_E60F20_QWr(obf.vrtx_cpc_ctrl.udata32,p_data[21]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef01.udata32,p_data[22]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef23.udata32,p_data[23]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef45.udata32,p_data[24]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef67.udata32,p_data[25]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef8.udata32,p_data[26]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef01.udata32,p_data[27]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef23.udata32,p_data[28]);
	PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef4.udata32,p_data[29]);
	PE_CHPI_TBL0_E60F20_QWr(obf.l5_gain_lut1.udata32,p_data[30]);
	PE_CHPI_TBL0_E60F20_QWr(obf.l5_gain_lut2.udata32,p_data[31]);
	PE_CHPI_TBL0_E60F20_QWr(obf.l0_gain_lut1.udata32,p_data[32]);
	PE_CHPI_TBL0_E60F20_QWr(obf.l0_gain_lut2.udata32,p_data[33]);
	PE_CHPI_TBL0_E60F20_QWr(obf.edge_win_h.udata32,p_data[34]);
	PE_CHPI_TBL0_E60F20_QWr(obf.edge_win_v.udata32,p_data[35]);
	PE_CHPI_TBL0_E60F20_QWr(obf.psp_iir1.udata32,p_data[36]);
	PE_CHPI_TBL0_E60F20_QWr(obf.bg_measure_ctrl.udata32,p_data[37]);
	PE_CHPI_TBL0_E60F20_QWr(obf.face0_set.udata32,p_data[38]);
	PE_CHPI_TBL0_E60F20_QWr(obf.face1_set.udata32,p_data[39]);
	PE_CHPI_TBL0_E60F20_QWr(obf.face2_set.udata32,p_data[40]);
	PE_CHPI_TBL0_E60F20_QWr(obf.face3_set.udata32,p_data[41]);
	PE_CHPI_TBL0_E60F20_QWr(obf.ellips0_set.udata32,p_data[42]);
	PE_CHPI_TBL0_E60F20_QWr(obf.ellips1_set.udata32,p_data[43]);
	PE_CHPI_TBL0_E60F20_QWr(obf.ellips2_set.udata32,p_data[44]);
	PE_CHPI_TBL0_E60F20_QWr(obf.ellips3_set.udata32,p_data[45]);
	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_OBF);
	#endif

	return ret;
}

static int PE_CHPI_OBC_HW_E60F20_SetRcoDefault(PE_CHPI_OBC_HW_E60F20_RCO_FMT cur0_rco_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_rco_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_rco_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_rco_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_rco_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_rco_fmt)
	{
		case PE_CHPI_OBC_E60F20_RCO_SD:
			p_dflt_param = rce_objt_l_sd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_RCO_HD:
			p_dflt_param = rce_objt_l_hd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_RCO_UD:
		default:
			p_dflt_param = rce_objt_l_ud_default_e60f20;
			break;
	}

	size = sizeof(PE_RCE_OBJT_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_00.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_01.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_02.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_03.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_04.udata32,p_data[4]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_05.udata32,p_data[5]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_06.udata32,p_data[6]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_07.udata32,p_data[7]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_08.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_09.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_10.udata32,p_data[10]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_11.udata32,p_data[11]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_12.udata32,p_data[12]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_13.udata32,p_data[13]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_14.udata32,p_data[14]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_15.udata32,p_data[15]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_16.udata32,p_data[16]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_17.udata32,p_data[17]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_18.udata32,p_data[18]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_19.udata32,p_data[19]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_20.udata32,p_data[20]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_21.udata32,p_data[21]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_22.udata32,p_data[22]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_23.udata32,p_data[23]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_24.udata32,p_data[24]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_25.udata32,p_data[25]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_26.udata32,p_data[26]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_27.udata32,p_data[27]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_28.udata32,p_data[28]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_29.udata32,p_data[29]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_30.udata32,p_data[30]);
	PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_31.udata32,p_data[31]);
	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCO);
	#endif

	return ret;
}

static int PE_CHPI_OBC_HW_E60F20_SetRcfDefault(PE_CHPI_OBC_HW_E60F20_RCF_FMT cur0_rcf_fmt)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	UINT32 i,size;
	const PE_REG_PARAM_T *p_dflt_param;
	UINT32 *p_dflt = _g_pe_rcf_hw_param_data_e60f20.reg_dflt.addr;
	UINT32 *p_user = _g_pe_rcf_hw_param_data_e60f20.reg_user.addr;
	UINT32 *p_mask = _g_pe_rcf_hw_param_data_e60f20.reg_mask.addr;
	UINT32 *p_data = _g_pe_rcf_hw_param_data_e60f20.reg_data.addr;

	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_dflt,return RET_ERROR,"p_dflt is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_user,return RET_ERROR,"p_user is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_mask,return RET_ERROR,"p_mask is null\n");
	PE_CHPI_OBC_HW_E60F20_CHECK_CODE(!p_data,return RET_ERROR,"p_data is null\n");

	switch(cur0_rcf_fmt)
	{
		case PE_CHPI_OBC_E60F20_RCF_SD:
			p_dflt_param = rce_face_l_sd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_RCF_HD:
			p_dflt_param = rce_face_l_hd_default_e60f20;
			break;
		case PE_CHPI_OBC_E60F20_RCF_UD:
		default:
			p_dflt_param = rce_face_l_ud_default_e60f20;
			break;
	}

	size = sizeof(PE_RCE_FACE_HW_PARAM_REG_E60F20_T)>>2;
	for (i=0; i<size; i++)
	{
		p_dflt[i] = p_dflt_param[i].data;
		p_data[i] = (p_dflt_param[i].data & p_mask[i])|(p_user[i]);
	}
	//i = size - 1;
	//PE_PRINT_NOTI("[%02d] 0x%08x = (0x%08x & 0x%08x)|(0x%08x)\n",i,p_data[i],p_dflt_param[i].data,p_mask[i],p_user[i]);

	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_00.udata32,p_data[0]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_01.udata32,p_data[1]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_02.udata32,p_data[2]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_03.udata32,p_data[3]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_04.udata32,p_data[4]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_05.udata32,p_data[5]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_06.udata32,p_data[6]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_07.udata32,p_data[7]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_08.udata32,p_data[8]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_09.udata32,p_data[9]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_10.udata32,p_data[10]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_11.udata32,p_data[11]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_12.udata32,p_data[12]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_13.udata32,p_data[13]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_14.udata32,p_data[14]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_15.udata32,p_data[15]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_16.udata32,p_data[16]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_17.udata32,p_data[17]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_18.udata32,p_data[18]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_19.udata32,p_data[19]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_20.udata32,p_data[20]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_21.udata32,p_data[21]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_22.udata32,p_data[22]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_23.udata32,p_data[23]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_24.udata32,p_data[24]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_25.udata32,p_data[25]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_26.udata32,p_data[26]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_27.udata32,p_data[27]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_28.udata32,p_data[28]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_29.udata32,p_data[29]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_30.udata32,p_data[30]);
	PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_31.udata32,p_data[31]);
	/* count */
	PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCF);
	#endif

	return ret;
}

int PE_CHPI_OBC_HW_E60F20_SetDefault(void)
{
	int ret = RET_OK;
	PE_INF_E60_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	static PE_CHPI_OBC_HW_E60F20_OBO_FMT pre0_obo_fmt = PE_CHPI_OBC_E60F20_OBO_NUM;
	static PE_CHPI_OBC_HW_E60F20_OBF_FMT pre0_obf_fmt = PE_CHPI_OBC_E60F20_OBF_NUM;
	static PE_CHPI_OBC_HW_E60F20_RCO_FMT pre0_rco_fmt = PE_CHPI_OBC_E60F20_RCO_NUM;
	static PE_CHPI_OBC_HW_E60F20_RCF_FMT pre0_rcf_fmt = PE_CHPI_OBC_E60F20_RCF_NUM;
	PE_CHPI_OBC_HW_E60F20_OBO_FMT cur0_obo_fmt;
	PE_CHPI_OBC_HW_E60F20_OBF_FMT cur0_obf_fmt;
	PE_CHPI_OBC_HW_E60F20_RCO_FMT cur0_rco_fmt;
	PE_CHPI_OBC_HW_E60F20_RCF_FMT cur0_rcf_fmt;
	do{
		ret = PE_INF_E60_GetCurInfSettings(&inf_set);
		PE_CHPI_OBC_HW_E60F20_CHECK_CODE(ret,break,"PE_INF_E60_GetCurInfSettings() error\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		CHECK_KNULL(disp0_inf);
		cur0_obo_fmt = PE_CHPI_OBC_HW_E60F20_ConvDispInfoToOboFmt(disp0_inf);
		if(pre0_obo_fmt!=cur0_obo_fmt)
		{
			ret = PE_CHPI_OBC_HW_E60F20_SetOboDefault(cur0_obo_fmt);
			PE_CHPI_OBC_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_E60F20_SetOboDefault() error\n");
			pre0_obo_fmt=cur0_obo_fmt;
		}
		cur0_obf_fmt = PE_CHPI_OBC_HW_E60F20_ConvDispInfoToObfFmt(disp0_inf);
		if(pre0_obf_fmt!=cur0_obf_fmt)
		{
			ret = PE_CHPI_OBC_HW_E60F20_SetObfDefault(cur0_obf_fmt);
			PE_CHPI_OBC_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_E60F20_SetObfDefault() error\n");
			pre0_obf_fmt=cur0_obf_fmt;
		}
		cur0_rco_fmt = PE_CHPI_OBC_HW_E60F20_ConvDispInfoToRcoFmt(disp0_inf);
		if(pre0_rco_fmt!=cur0_rco_fmt)
		{
			ret = PE_CHPI_OBC_HW_E60F20_SetRcoDefault(cur0_rco_fmt);
			PE_CHPI_OBC_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_E60F20_SetRcoDefault() error\n");
			pre0_rco_fmt=cur0_rco_fmt;
		}
		cur0_rcf_fmt = PE_CHPI_OBC_HW_E60F20_ConvDispInfoToRcfFmt(disp0_inf);
		if(pre0_rcf_fmt!=cur0_rcf_fmt)
		{
			ret = PE_CHPI_OBC_HW_E60F20_SetRcfDefault(cur0_rcf_fmt);
			PE_CHPI_OBC_HW_E60F20_CHECK_CODE(ret,break,"PE_CHPI_OBC_HW_E60F20_SetRcfDefault() error\n");
			pre0_rcf_fmt=cur0_rcf_fmt;
		}
	}while(0);
	return ret;
}

int PE_CHPI_OBC_HW_E60F20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	do{
		CHECK_KNULL(pstParams);
		ret = PE_CHPI_OBC_HW_E60F20_CreateDataTable();
		if (ret)	break;

		if (pstParams->resume_mode == 1)	break;//if qsm,skip

		/* addr */
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl00.uaddr32,0xF0175300);
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl01.uaddr32,0xF0175304);
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_ctrl02.uaddr32,0xF0175308);
		PE_CHPI_TBL0_E60F20_QWr(obo.edge_th.uaddr32,0xF017530C);
		PE_CHPI_TBL0_E60F20_QWr(obo.fg_position.uaddr32,0xF0175310);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x0.uaddr32,0xF0175314);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x1.uaddr32,0xF0175318);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x2.uaddr32,0xF017531C);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_x3.uaddr32,0xF0175320);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y0.uaddr32,0xF0175324);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y1.uaddr32,0xF0175328);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y2.uaddr32,0xF017532C);
		PE_CHPI_TBL0_E60F20_QWr(obo.perspect_lut_y3.uaddr32,0xF0175330);
		PE_CHPI_TBL0_E60F20_QWr(obo.prob_map.uaddr32,0xF0175334);
		PE_CHPI_TBL0_E60F20_QWr(obo.ellips_map.uaddr32,0xF0175338);
		PE_CHPI_TBL0_E60F20_QWr(obo.prob_diff_map.uaddr32,0xF017533C);
		PE_CHPI_TBL0_E60F20_QWr(obo.object_map.uaddr32,0xF0175340);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_map.uaddr32,0xF0175344);
		PE_CHPI_TBL0_E60F20_QWr(obo.display_debug_map.uaddr32,0xF0175348);
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_iir.uaddr32,0xF017534C);
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_gain.uaddr32,0xF0175350);
		PE_CHPI_TBL0_E60F20_QWr(obo.vrtx_cpc_ctrl.uaddr32,0xF017535C);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef01.uaddr32,0xF0175360);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef23.uaddr32,0xF0175364);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef45.uaddr32,0xF0175368);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef67.uaddr32,0xF017536C);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_hcoef8.uaddr32,0xF0175370);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef01.uaddr32,0xF0175374);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef23.uaddr32,0xF0175378);
		PE_CHPI_TBL0_E60F20_QWr(obo.blur_vcoef4.uaddr32,0xF017537C);
		PE_CHPI_TBL0_E60F20_QWr(obo.l5_gain_lut1.uaddr32,0xF0175400);
		PE_CHPI_TBL0_E60F20_QWr(obo.l5_gain_lut2.uaddr32,0xF0175404);
		PE_CHPI_TBL0_E60F20_QWr(obo.l0_gain_lut1.uaddr32,0xF0175408);
		PE_CHPI_TBL0_E60F20_QWr(obo.l0_gain_lut2.uaddr32,0xF017540C);
		PE_CHPI_TBL0_E60F20_QWr(obo.edge_win_h.uaddr32,0xF0175410);
		PE_CHPI_TBL0_E60F20_QWr(obo.edge_win_v.uaddr32,0xF0175414);
		PE_CHPI_TBL0_E60F20_QWr(obo.psp_iir1.uaddr32,0xF0175428);
		PE_CHPI_TBL0_E60F20_QWr(obo.bg_measure_ctrl.uaddr32,0xF017542C);
		PE_CHPI_TBL0_E60F20_QWr(obo.face0_set.uaddr32,0xF0175444);
		PE_CHPI_TBL0_E60F20_QWr(obo.face1_set.uaddr32,0xF0175448);
		PE_CHPI_TBL0_E60F20_QWr(obo.face2_set.uaddr32,0xF017544C);
		PE_CHPI_TBL0_E60F20_QWr(obo.face3_set.uaddr32,0xF0175450);
		PE_CHPI_TBL0_E60F20_QWr(obo.ellips0_set.uaddr32,0xF0175454);
		PE_CHPI_TBL0_E60F20_QWr(obo.ellips1_set.uaddr32,0xF0175458);
		PE_CHPI_TBL0_E60F20_QWr(obo.ellips2_set.uaddr32,0xF017545C);
		PE_CHPI_TBL0_E60F20_QWr(obo.ellips3_set.uaddr32,0xF0175460);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl00.uaddr32,0xF0175500);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl01.uaddr32,0xF0175504);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_ctrl02.uaddr32,0xF0175508);
		PE_CHPI_TBL0_E60F20_QWr(obf.edge_th.uaddr32,0xF017550C);
		PE_CHPI_TBL0_E60F20_QWr(obf.fg_position.uaddr32,0xF0175510);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved0.uaddr32,0xF0175514);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved1.uaddr32,0xF0175518);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved2.uaddr32,0xF017551C);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved3.uaddr32,0xF0175520);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved4.uaddr32,0xF0175524);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved5.uaddr32,0xF0175528);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved6.uaddr32,0xF017552C);
		PE_CHPI_TBL0_E60F20_QWr(obf.reserved7.uaddr32,0xF0175530);
		PE_CHPI_TBL0_E60F20_QWr(obf.prob_map.uaddr32,0xF0175534);
		PE_CHPI_TBL0_E60F20_QWr(obf.ellips_map.uaddr32,0xF0175538);
		PE_CHPI_TBL0_E60F20_QWr(obf.prob_diff_map.uaddr32,0xF017553C);
		PE_CHPI_TBL0_E60F20_QWr(obf.object_map.uaddr32,0xF0175540);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_map.uaddr32,0xF0175544);
		PE_CHPI_TBL0_E60F20_QWr(obf.display_debug_map.uaddr32,0xF0175548);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_iir.uaddr32,0xF017554C);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_gain.uaddr32,0xF0175550);
		PE_CHPI_TBL0_E60F20_QWr(obf.vrtx_cpc_ctrl.uaddr32,0xF017555C);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef01.uaddr32,0xF0175560);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef23.uaddr32,0xF0175564);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef45.uaddr32,0xF0175568);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef67.uaddr32,0xF017556C);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_hcoef8.uaddr32,0xF0175570);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef01.uaddr32,0xF0175574);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef23.uaddr32,0xF0175578);
		PE_CHPI_TBL0_E60F20_QWr(obf.blur_vcoef4.uaddr32,0xF017557C);
		PE_CHPI_TBL0_E60F20_QWr(obf.l5_gain_lut1.uaddr32,0xF0175600);
		PE_CHPI_TBL0_E60F20_QWr(obf.l5_gain_lut2.uaddr32,0xF0175604);
		PE_CHPI_TBL0_E60F20_QWr(obf.l0_gain_lut1.uaddr32,0xF0175608);
		PE_CHPI_TBL0_E60F20_QWr(obf.l0_gain_lut2.uaddr32,0xF017560C);
		PE_CHPI_TBL0_E60F20_QWr(obf.edge_win_h.uaddr32,0xF0175610);
		PE_CHPI_TBL0_E60F20_QWr(obf.edge_win_v.uaddr32,0xF0175614);
		PE_CHPI_TBL0_E60F20_QWr(obf.psp_iir1.uaddr32,0xF0175628);
		PE_CHPI_TBL0_E60F20_QWr(obf.bg_measure_ctrl.uaddr32,0xF017562C);
		PE_CHPI_TBL0_E60F20_QWr(obf.face0_set.uaddr32,0xF0175644);
		PE_CHPI_TBL0_E60F20_QWr(obf.face1_set.uaddr32,0xF0175648);
		PE_CHPI_TBL0_E60F20_QWr(obf.face2_set.uaddr32,0xF017564C);
		PE_CHPI_TBL0_E60F20_QWr(obf.face3_set.uaddr32,0xF0175650);
		PE_CHPI_TBL0_E60F20_QWr(obf.ellips0_set.uaddr32,0xF0175654);
		PE_CHPI_TBL0_E60F20_QWr(obf.ellips1_set.uaddr32,0xF0175658);
		PE_CHPI_TBL0_E60F20_QWr(obf.ellips2_set.uaddr32,0xF017565C);
		PE_CHPI_TBL0_E60F20_QWr(obf.ellips3_set.uaddr32,0xF0175660);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_00.uaddr32,0xF0175200);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_01.uaddr32,0xF0175204);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_02.uaddr32,0xF0175208);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_03.uaddr32,0xF017520C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_04.uaddr32,0xF0175210);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_05.uaddr32,0xF0175214);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_06.uaddr32,0xF0175218);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_07.uaddr32,0xF017521C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_08.uaddr32,0xF0175220);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_09.uaddr32,0xF0175224);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_10.uaddr32,0xF0175228);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_11.uaddr32,0xF017522C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_12.uaddr32,0xF0175230);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_13.uaddr32,0xF0175234);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_14.uaddr32,0xF0175238);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_15.uaddr32,0xF017523C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_16.uaddr32,0xF0175240);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_17.uaddr32,0xF0175244);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_18.uaddr32,0xF0175248);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_19.uaddr32,0xF017524C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_20.uaddr32,0xF0175250);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_21.uaddr32,0xF0175254);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_22.uaddr32,0xF0175258);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_23.uaddr32,0xF017525C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_24.uaddr32,0xF0175260);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_25.uaddr32,0xF0175264);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_26.uaddr32,0xF0175268);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_27.uaddr32,0xF017526C);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_28.uaddr32,0xF0175270);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_29.uaddr32,0xF0175274);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_30.uaddr32,0xF0175278);
		PE_CHPI_TBL0_E60F20_QWr(rco.reg_rce_objt_ctrl_31.uaddr32,0xF017527C);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_00.uaddr32,0xF0175280);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_01.uaddr32,0xF0175284);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_02.uaddr32,0xF0175288);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_03.uaddr32,0xF017528C);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_04.uaddr32,0xF0175290);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_05.uaddr32,0xF0175294);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_06.uaddr32,0xF0175298);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_07.uaddr32,0xF017529C);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_08.uaddr32,0xF01752A0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_09.uaddr32,0xF01752A4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_10.uaddr32,0xF01752A8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_11.uaddr32,0xF01752AC);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_12.uaddr32,0xF01752B0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_13.uaddr32,0xF01752B4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_14.uaddr32,0xF01752B8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_15.uaddr32,0xF01752BC);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_16.uaddr32,0xF01752C0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_17.uaddr32,0xF01752C4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_18.uaddr32,0xF01752C8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_19.uaddr32,0xF01752CC);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_20.uaddr32,0xF01752D0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_21.uaddr32,0xF01752D4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_22.uaddr32,0xF01752D8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_23.uaddr32,0xF01752DC);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_24.uaddr32,0xF01752E0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_25.uaddr32,0xF01752E4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_26.uaddr32,0xF01752E8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_27.uaddr32,0xF01752EC);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_28.uaddr32,0xF01752F0);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_29.uaddr32,0xF01752F4);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_30.uaddr32,0xF01752F8);
		PE_CHPI_TBL0_E60F20_QWr(rcf.reg_rce_face_ctrl_31.uaddr32,0xF01752FC);

		/* init */
		PE_CHPI_OBC_HW_E60F20_SetOboDefault(PE_CHPI_OBC_E60F20_OBO_HD);
		PE_CHPI_OBC_HW_E60F20_SetObfDefault(PE_CHPI_OBC_E60F20_OBF_HD);
		PE_CHPI_OBC_HW_E60F20_SetRcoDefault(PE_CHPI_OBC_E60F20_RCO_HD);
		PE_CHPI_OBC_HW_E60F20_SetRcfDefault(PE_CHPI_OBC_E60F20_RCF_HD);

		PE_PRINT_NOTI("[TBL][OBC]done(resume::%d)\n",pstParams->resume_mode);
		PE_INF_HW_E60_BACKUP_CHPI1("[TBL][OBC]done(resume::%d)",pstParams->resume_mode);
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_OBC_HW_E60F20_SetCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	LX_PE_VSD_OBC2_CONT_T *pp;
	PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T *p_rco = &_g_pe_rco_hw_param_data_e60f20;
	PE_RCE_FACE_HW_PARAM_DATA_E60F20_T *p_rcf = &_g_pe_rcf_hw_param_data_e60f20;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_rcf->reg_user.data);
		CHECK_KNULL(p_rcf->reg_mask.data);
		CHECK_KNULL(p_rco->reg_user.data);
		CHECK_KNULL(p_rco->reg_mask.data);
 		pp=(LX_PE_VSD_OBC2_CONT_T *)pstParams;
		/* set apb */
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_19.reg_psp_gain_lut0_y0,	GET_BITS(pp->obj_fg_gain_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_19.reg_psp_gain_lut0_x0,	GET_BITS(pp->obj_fg_gain_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_19.reg_psp_gain_lut0_y1,	GET_BITS(pp->obj_fg_gain_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_19.reg_psp_gain_lut0_x1,	GET_BITS(pp->obj_fg_gain_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_20.reg_psp_gain_lut1_y0,	GET_BITS(pp->obj_bg_gain_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_20.reg_psp_gain_lut1_x0,	GET_BITS(pp->obj_bg_gain_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_20.reg_psp_gain_lut1_y1,	GET_BITS(pp->obj_bg_gain_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_20.reg_psp_gain_lut1_x1,	GET_BITS(pp->obj_bg_gain_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_00.reg_sat_gain_en,		GET_BITS(pp->obj_sat_enable,0,1));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_00.reg_cbst_en,			GET_BITS(pp->obj_ch_bst_enable,0,1));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_21.reg_yy_lut_pts_x0,	GET_BITS(pp->obj_yy_lut_pts_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_21.reg_yy_lut_pts_x1,	GET_BITS(pp->obj_yy_lut_pts_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_22.reg_yy_lut_pts_x2,	GET_BITS(pp->obj_yy_lut_pts_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_22.reg_yy_lut_pts_x3,	GET_BITS(pp->obj_yy_lut_pts_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_23.reg_yy_lut_pts_y0,	GET_BITS(pp->obj_yy_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_23.reg_yy_lut_pts_y1,	GET_BITS(pp->obj_yy_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_23.reg_yy_lut_pts_y2,	GET_BITS(pp->obj_yy_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_23.reg_yy_lut_pts_y3,	GET_BITS(pp->obj_yy_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_24.reg_cc_lut_pts_y0,	GET_BITS(pp->obj_cc_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_24.reg_cc_lut_pts_x0,	GET_BITS(pp->obj_cc_lut_pts_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_24.reg_cc_lut_pts_y1,	GET_BITS(pp->obj_cc_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_24.reg_cc_lut_pts_x1,	GET_BITS(pp->obj_cc_lut_pts_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_25.reg_cc_lut_pts_y2,	GET_BITS(pp->obj_cc_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_25.reg_cc_lut_pts_x2,	GET_BITS(pp->obj_cc_lut_pts_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_25.reg_cc_lut_pts_y3,	GET_BITS(pp->obj_cc_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_25.reg_cc_lut_pts_x3,	GET_BITS(pp->obj_cc_lut_pts_x[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_26.reg_cbst_lut_pts_y0,	GET_BITS(pp->obj_cbst_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_26.reg_cbst_lut_pts_x0,	GET_BITS(pp->obj_cbst_lut_pts_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_26.reg_cbst_lut_pts_y1,	GET_BITS(pp->obj_cbst_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_26.reg_cbst_lut_pts_x1,	GET_BITS(pp->obj_cbst_lut_pts_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_27.reg_cbst_lut_pts_y2,	GET_BITS(pp->obj_cbst_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_27.reg_cbst_lut_pts_x2,	GET_BITS(pp->obj_cbst_lut_pts_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_27.reg_cbst_lut_pts_y3,	GET_BITS(pp->obj_cbst_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_27.reg_cbst_lut_pts_x3,	GET_BITS(pp->obj_cbst_lut_pts_x[3],0,8));
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_19.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_20.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_21.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_22.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_23.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_24.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_25.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_26.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_27.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCO);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_19.reg_psp_gain_lut0_y0,	GET_BITS(pp->obj_fg_gain_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_19.reg_psp_gain_lut0_x0,	GET_BITS(pp->obj_fg_gain_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_19.reg_psp_gain_lut0_y1,	GET_BITS(pp->obj_fg_gain_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_19.reg_psp_gain_lut0_x1,	GET_BITS(pp->obj_fg_gain_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_20.reg_psp_gain_lut1_y0,	GET_BITS(pp->obj_bg_gain_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_20.reg_psp_gain_lut1_x0,	GET_BITS(pp->obj_bg_gain_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_20.reg_psp_gain_lut1_y1,	GET_BITS(pp->obj_bg_gain_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_20.reg_psp_gain_lut1_x1,	GET_BITS(pp->obj_bg_gain_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_00.reg_sat_gain_en,		GET_BITS(pp->obj_sat_enable,0,1));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_00.reg_cbst_en,			GET_BITS(pp->obj_ch_bst_enable,0,1));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_21.reg_yy_lut_pts_x0,	GET_BITS(pp->obj_yy_lut_pts_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_21.reg_yy_lut_pts_x1,	GET_BITS(pp->obj_yy_lut_pts_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_22.reg_yy_lut_pts_x2,	GET_BITS(pp->obj_yy_lut_pts_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_22.reg_yy_lut_pts_x3,	GET_BITS(pp->obj_yy_lut_pts_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_23.reg_yy_lut_pts_y0,	GET_BITS(pp->obj_yy_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_23.reg_yy_lut_pts_y1,	GET_BITS(pp->obj_yy_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_23.reg_yy_lut_pts_y2,	GET_BITS(pp->obj_yy_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_23.reg_yy_lut_pts_y3,	GET_BITS(pp->obj_yy_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_24.reg_cc_lut_pts_y0,	GET_BITS(pp->obj_cc_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_24.reg_cc_lut_pts_x0,	GET_BITS(pp->obj_cc_lut_pts_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_24.reg_cc_lut_pts_y1,	GET_BITS(pp->obj_cc_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_24.reg_cc_lut_pts_x1,	GET_BITS(pp->obj_cc_lut_pts_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_25.reg_cc_lut_pts_y2,	GET_BITS(pp->obj_cc_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_25.reg_cc_lut_pts_x2,	GET_BITS(pp->obj_cc_lut_pts_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_25.reg_cc_lut_pts_y3,	GET_BITS(pp->obj_cc_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_25.reg_cc_lut_pts_x3,	GET_BITS(pp->obj_cc_lut_pts_x[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_26.reg_cbst_lut_pts_y0,	GET_BITS(pp->obj_cbst_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_26.reg_cbst_lut_pts_x0,	GET_BITS(pp->obj_cbst_lut_pts_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_26.reg_cbst_lut_pts_y1,	GET_BITS(pp->obj_cbst_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_26.reg_cbst_lut_pts_x1,	GET_BITS(pp->obj_cbst_lut_pts_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_27.reg_cbst_lut_pts_y2,	GET_BITS(pp->obj_cbst_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_27.reg_cbst_lut_pts_x2,	GET_BITS(pp->obj_cbst_lut_pts_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_27.reg_cbst_lut_pts_y3,	GET_BITS(pp->obj_cbst_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_27.reg_cbst_lut_pts_x3,	GET_BITS(pp->obj_cbst_lut_pts_x[3],0,8));
		/* set apb */
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_19.reg_psp_gain_lut0_y0,	GET_BITS(pp->face_fg_gain_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_19.reg_psp_gain_lut0_x0,	GET_BITS(pp->face_fg_gain_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_19.reg_psp_gain_lut0_y1,	GET_BITS(pp->face_fg_gain_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_19.reg_psp_gain_lut0_x1,	GET_BITS(pp->face_fg_gain_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_20.reg_psp_gain_lut1_y0,	GET_BITS(pp->face_bg_gain_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_20.reg_psp_gain_lut1_x0,	GET_BITS(pp->face_bg_gain_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_20.reg_psp_gain_lut1_y1,	GET_BITS(pp->face_bg_gain_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_20.reg_psp_gain_lut1_x1,	GET_BITS(pp->face_bg_gain_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_00.reg_sat_gain_en,		GET_BITS(pp->face_sat_enable,0,1));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_00.reg_cbst_en,			GET_BITS(pp->face_ch_bst_enable,0,1));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_21.reg_yy_lut_pts_x0,	GET_BITS(pp->face_yy_lut_pts_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_21.reg_yy_lut_pts_x1,	GET_BITS(pp->face_yy_lut_pts_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_22.reg_yy_lut_pts_x2,	GET_BITS(pp->face_yy_lut_pts_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_22.reg_yy_lut_pts_x3,	GET_BITS(pp->face_yy_lut_pts_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_23.reg_yy_lut_pts_y0,	GET_BITS(pp->face_yy_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_23.reg_yy_lut_pts_y1,	GET_BITS(pp->face_yy_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_23.reg_yy_lut_pts_y2,	GET_BITS(pp->face_yy_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_23.reg_yy_lut_pts_y3,	GET_BITS(pp->face_yy_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_24.reg_cc_lut_pts_y0,	GET_BITS(pp->face_cc_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_24.reg_cc_lut_pts_x0,	GET_BITS(pp->face_cc_lut_pts_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_24.reg_cc_lut_pts_y1,	GET_BITS(pp->face_cc_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_24.reg_cc_lut_pts_x1,	GET_BITS(pp->face_cc_lut_pts_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_25.reg_cc_lut_pts_y2,	GET_BITS(pp->face_cc_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_25.reg_cc_lut_pts_x2,	GET_BITS(pp->face_cc_lut_pts_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_25.reg_cc_lut_pts_y3,	GET_BITS(pp->face_cc_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_25.reg_cc_lut_pts_x3,	GET_BITS(pp->face_cc_lut_pts_x[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_26.reg_cbst_lut_pts_y0,	GET_BITS(pp->face_cbst_lut_pts_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_26.reg_cbst_lut_pts_x0,	GET_BITS(pp->face_cbst_lut_pts_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_26.reg_cbst_lut_pts_y1,	GET_BITS(pp->face_cbst_lut_pts_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_26.reg_cbst_lut_pts_x1,	GET_BITS(pp->face_cbst_lut_pts_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_27.reg_cbst_lut_pts_y2,	GET_BITS(pp->face_cbst_lut_pts_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_27.reg_cbst_lut_pts_x2,	GET_BITS(pp->face_cbst_lut_pts_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_27.reg_cbst_lut_pts_y3,	GET_BITS(pp->face_cbst_lut_pts_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_27.reg_cbst_lut_pts_x3,	GET_BITS(pp->face_cbst_lut_pts_x[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_29.reg_face_objt_lut_y0,	GET_BITS(pp->face_obj_lut_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_29.reg_face_objt_lut_x0,	GET_BITS(pp->face_obj_lut_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_29.reg_face_objt_lut_y1,	GET_BITS(pp->face_obj_lut_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_29.reg_face_objt_lut_x1,	GET_BITS(pp->face_obj_lut_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_28.reg_face_objt_lut_y2,	GET_BITS(pp->face_obj_lut_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_28.reg_face_objt_lut_x2,	GET_BITS(pp->face_obj_lut_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_28.reg_face_objt_lut_y3,	GET_BITS(pp->face_obj_lut_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_28.reg_face_objt_lut_x3,	GET_BITS(pp->face_obj_lut_x[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_31.reg_objt_face_lut_y0,	GET_BITS(pp->obj_face_lut_y[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_31.reg_objt_face_lut_x0,	GET_BITS(pp->obj_face_lut_x[0],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_31.reg_objt_face_lut_y1,	GET_BITS(pp->obj_face_lut_y[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_31.reg_objt_face_lut_x1,	GET_BITS(pp->obj_face_lut_x[1],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_30.reg_objt_face_lut_y2,	GET_BITS(pp->obj_face_lut_y[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_30.reg_objt_face_lut_x2,	GET_BITS(pp->obj_face_lut_x[2],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_30.reg_objt_face_lut_y3,	GET_BITS(pp->obj_face_lut_y[3],0,8));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_30.reg_objt_face_lut_x3,	GET_BITS(pp->obj_face_lut_x[3],0,8));
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_19.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_20.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_00.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_21.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_22.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_23.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_24.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_25.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_26.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_27.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_29.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_28.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_31.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_30.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCF);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_19.reg_psp_gain_lut0_y0,	GET_BITS(pp->face_fg_gain_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_19.reg_psp_gain_lut0_x0,	GET_BITS(pp->face_fg_gain_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_19.reg_psp_gain_lut0_y1,	GET_BITS(pp->face_fg_gain_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_19.reg_psp_gain_lut0_x1,	GET_BITS(pp->face_fg_gain_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_20.reg_psp_gain_lut1_y0,	GET_BITS(pp->face_bg_gain_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_20.reg_psp_gain_lut1_x0,	GET_BITS(pp->face_bg_gain_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_20.reg_psp_gain_lut1_y1,	GET_BITS(pp->face_bg_gain_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_20.reg_psp_gain_lut1_x1,	GET_BITS(pp->face_bg_gain_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_00.reg_sat_gain_en,		GET_BITS(pp->face_sat_enable,0,1));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_00.reg_cbst_en,			GET_BITS(pp->face_ch_bst_enable,0,1));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_21.reg_yy_lut_pts_x0,	GET_BITS(pp->face_yy_lut_pts_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_21.reg_yy_lut_pts_x1,	GET_BITS(pp->face_yy_lut_pts_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_22.reg_yy_lut_pts_x2,	GET_BITS(pp->face_yy_lut_pts_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_22.reg_yy_lut_pts_x3,	GET_BITS(pp->face_yy_lut_pts_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_23.reg_yy_lut_pts_y0,	GET_BITS(pp->face_yy_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_23.reg_yy_lut_pts_y1,	GET_BITS(pp->face_yy_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_23.reg_yy_lut_pts_y2,	GET_BITS(pp->face_yy_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_23.reg_yy_lut_pts_y3,	GET_BITS(pp->face_yy_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_24.reg_cc_lut_pts_y0,	GET_BITS(pp->face_cc_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_24.reg_cc_lut_pts_x0,	GET_BITS(pp->face_cc_lut_pts_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_24.reg_cc_lut_pts_y1,	GET_BITS(pp->face_cc_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_24.reg_cc_lut_pts_x1,	GET_BITS(pp->face_cc_lut_pts_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_25.reg_cc_lut_pts_y2,	GET_BITS(pp->face_cc_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_25.reg_cc_lut_pts_x2,	GET_BITS(pp->face_cc_lut_pts_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_25.reg_cc_lut_pts_y3,	GET_BITS(pp->face_cc_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_25.reg_cc_lut_pts_x3,	GET_BITS(pp->face_cc_lut_pts_x[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_26.reg_cbst_lut_pts_y0,	GET_BITS(pp->face_cbst_lut_pts_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_26.reg_cbst_lut_pts_x0,	GET_BITS(pp->face_cbst_lut_pts_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_26.reg_cbst_lut_pts_y1,	GET_BITS(pp->face_cbst_lut_pts_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_26.reg_cbst_lut_pts_x1,	GET_BITS(pp->face_cbst_lut_pts_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_27.reg_cbst_lut_pts_y2,	GET_BITS(pp->face_cbst_lut_pts_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_27.reg_cbst_lut_pts_x2,	GET_BITS(pp->face_cbst_lut_pts_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_27.reg_cbst_lut_pts_y3,	GET_BITS(pp->face_cbst_lut_pts_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_27.reg_cbst_lut_pts_x3,	GET_BITS(pp->face_cbst_lut_pts_x[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_29.reg_face_objt_lut_y0,	GET_BITS(pp->face_obj_lut_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_29.reg_face_objt_lut_x0,	GET_BITS(pp->face_obj_lut_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_29.reg_face_objt_lut_y1,	GET_BITS(pp->face_obj_lut_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_29.reg_face_objt_lut_x1,	GET_BITS(pp->face_obj_lut_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_28.reg_face_objt_lut_y2,	GET_BITS(pp->face_obj_lut_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_28.reg_face_objt_lut_x2,	GET_BITS(pp->face_obj_lut_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_28.reg_face_objt_lut_y3,	GET_BITS(pp->face_obj_lut_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_28.reg_face_objt_lut_x3,	GET_BITS(pp->face_obj_lut_x[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_31.reg_objt_face_lut_y0,	GET_BITS(pp->obj_face_lut_y[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_31.reg_objt_face_lut_x0,	GET_BITS(pp->obj_face_lut_x[0],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_31.reg_objt_face_lut_y1,	GET_BITS(pp->obj_face_lut_y[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_31.reg_objt_face_lut_x1,	GET_BITS(pp->obj_face_lut_x[1],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_30.reg_objt_face_lut_y2,	GET_BITS(pp->obj_face_lut_y[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_30.reg_objt_face_lut_x2,	GET_BITS(pp->obj_face_lut_x[2],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_30.reg_objt_face_lut_y3,	GET_BITS(pp->obj_face_lut_y[3],0,8));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_30.reg_objt_face_lut_x3,	GET_BITS(pp->obj_face_lut_x[3],0,8));
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_OBC_HW_E60F20_SetLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	LX_PE_VSD_OBC1_LUT_T *pp;
	PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T *p_rco = &_g_pe_rco_hw_param_data_e60f20;
	PE_RCE_FACE_HW_PARAM_DATA_E60F20_T *p_rcf = &_g_pe_rcf_hw_param_data_e60f20;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_rcf->reg_user.data);
		CHECK_KNULL(p_rcf->reg_mask.data);
		CHECK_KNULL(p_rco->reg_user.data);
		CHECK_KNULL(p_rco->reg_mask.data);
		pp=(LX_PE_VSD_OBC1_LUT_T *)pstParams;
		/* set apb */
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_03.reg_psp_lut0_x0,GET_BITS(pp->object_fg_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_03.reg_psp_lut0_y0,GET_BITS(pp->object_fg_y[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_04.reg_psp_lut0_x1,GET_BITS(pp->object_fg_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_04.reg_psp_lut0_y1,GET_BITS(pp->object_fg_y[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_05.reg_psp_lut0_x2,GET_BITS(pp->object_fg_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_05.reg_psp_lut0_y2,GET_BITS(pp->object_fg_y[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_06.reg_psp_lut0_x3,GET_BITS(pp->object_fg_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_06.reg_psp_lut0_y3,GET_BITS(pp->object_fg_y[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_07.reg_psp_lut0_x4,GET_BITS(pp->object_fg_x[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_07.reg_psp_lut0_y4,GET_BITS(pp->object_fg_y[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_08.reg_psp_lut0_x5,GET_BITS(pp->object_fg_x[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_08.reg_psp_lut0_y5,GET_BITS(pp->object_fg_y[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_09.reg_psp_lut0_x6,GET_BITS(pp->object_fg_x[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_09.reg_psp_lut0_y6,GET_BITS(pp->object_fg_y[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_10.reg_psp_lut0_x7,GET_BITS(pp->object_fg_x[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_10.reg_psp_lut0_y7,GET_BITS(pp->object_fg_y[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_11.reg_psp_lut1_x0,GET_BITS(pp->object_bg_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_11.reg_psp_lut1_y0,GET_BITS(pp->object_bg_y[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_12.reg_psp_lut1_x1,GET_BITS(pp->object_bg_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_12.reg_psp_lut1_y1,GET_BITS(pp->object_bg_y[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_13.reg_psp_lut1_x2,GET_BITS(pp->object_bg_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_13.reg_psp_lut1_y2,GET_BITS(pp->object_bg_y[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_14.reg_psp_lut1_x3,GET_BITS(pp->object_bg_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_14.reg_psp_lut1_y3,GET_BITS(pp->object_bg_y[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_15.reg_psp_lut1_x4,GET_BITS(pp->object_bg_x[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_15.reg_psp_lut1_y4,GET_BITS(pp->object_bg_y[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_16.reg_psp_lut1_x5,GET_BITS(pp->object_bg_x[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_16.reg_psp_lut1_y5,GET_BITS(pp->object_bg_y[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_17.reg_psp_lut1_x6,GET_BITS(pp->object_bg_x[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_17.reg_psp_lut1_y6,GET_BITS(pp->object_bg_y[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_18.reg_psp_lut1_x7,GET_BITS(pp->object_bg_x[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_18.reg_psp_lut1_y7,GET_BITS(pp->object_bg_y[7],0,10));
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_04.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_07.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_10.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_11.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_12.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_13.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_14.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_15.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_16.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_17.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_18.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCO);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_03.reg_psp_lut0_x0,GET_BITS(pp->object_fg_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_03.reg_psp_lut0_y0,GET_BITS(pp->object_fg_y[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_04.reg_psp_lut0_x1,GET_BITS(pp->object_fg_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_04.reg_psp_lut0_y1,GET_BITS(pp->object_fg_y[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_05.reg_psp_lut0_x2,GET_BITS(pp->object_fg_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_05.reg_psp_lut0_y2,GET_BITS(pp->object_fg_y[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_06.reg_psp_lut0_x3,GET_BITS(pp->object_fg_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_06.reg_psp_lut0_y3,GET_BITS(pp->object_fg_y[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_07.reg_psp_lut0_x4,GET_BITS(pp->object_fg_x[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_07.reg_psp_lut0_y4,GET_BITS(pp->object_fg_y[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_08.reg_psp_lut0_x5,GET_BITS(pp->object_fg_x[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_08.reg_psp_lut0_y5,GET_BITS(pp->object_fg_y[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_09.reg_psp_lut0_x6,GET_BITS(pp->object_fg_x[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_09.reg_psp_lut0_y6,GET_BITS(pp->object_fg_y[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_10.reg_psp_lut0_x7,GET_BITS(pp->object_fg_x[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_10.reg_psp_lut0_y7,GET_BITS(pp->object_fg_y[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_11.reg_psp_lut1_x0,GET_BITS(pp->object_bg_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_11.reg_psp_lut1_y0,GET_BITS(pp->object_bg_y[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_12.reg_psp_lut1_x1,GET_BITS(pp->object_bg_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_12.reg_psp_lut1_y1,GET_BITS(pp->object_bg_y[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_13.reg_psp_lut1_x2,GET_BITS(pp->object_bg_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_13.reg_psp_lut1_y2,GET_BITS(pp->object_bg_y[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_14.reg_psp_lut1_x3,GET_BITS(pp->object_bg_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_14.reg_psp_lut1_y3,GET_BITS(pp->object_bg_y[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_15.reg_psp_lut1_x4,GET_BITS(pp->object_bg_x[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_15.reg_psp_lut1_y4,GET_BITS(pp->object_bg_y[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_16.reg_psp_lut1_x5,GET_BITS(pp->object_bg_x[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_16.reg_psp_lut1_y5,GET_BITS(pp->object_bg_y[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_17.reg_psp_lut1_x6,GET_BITS(pp->object_bg_x[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_17.reg_psp_lut1_y6,GET_BITS(pp->object_bg_y[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_18.reg_psp_lut1_x7,GET_BITS(pp->object_bg_x[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_18.reg_psp_lut1_y7,GET_BITS(pp->object_bg_y[7],0,10));
		/* set apb */
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_03.reg_psp_lut0_x0,GET_BITS(pp->face_fg_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_03.reg_psp_lut0_y0,GET_BITS(pp->face_fg_y[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_04.reg_psp_lut0_x1,GET_BITS(pp->face_fg_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_04.reg_psp_lut0_y1,GET_BITS(pp->face_fg_y[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_05.reg_psp_lut0_x2,GET_BITS(pp->face_fg_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_05.reg_psp_lut0_y2,GET_BITS(pp->face_fg_y[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_06.reg_psp_lut0_x3,GET_BITS(pp->face_fg_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_06.reg_psp_lut0_y3,GET_BITS(pp->face_fg_y[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_07.reg_psp_lut0_x4,GET_BITS(pp->face_fg_x[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_07.reg_psp_lut0_y4,GET_BITS(pp->face_fg_y[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_08.reg_psp_lut0_x5,GET_BITS(pp->face_fg_x[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_08.reg_psp_lut0_y5,GET_BITS(pp->face_fg_y[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_09.reg_psp_lut0_x6,GET_BITS(pp->face_fg_x[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_09.reg_psp_lut0_y6,GET_BITS(pp->face_fg_y[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_10.reg_psp_lut0_x7,GET_BITS(pp->face_fg_x[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_10.reg_psp_lut0_y7,GET_BITS(pp->face_fg_y[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_11.reg_psp_lut1_x0,GET_BITS(pp->face_bg_x[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_11.reg_psp_lut1_y0,GET_BITS(pp->face_bg_y[0],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_12.reg_psp_lut1_x1,GET_BITS(pp->face_bg_x[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_12.reg_psp_lut1_y1,GET_BITS(pp->face_bg_y[1],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_13.reg_psp_lut1_x2,GET_BITS(pp->face_bg_x[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_13.reg_psp_lut1_y2,GET_BITS(pp->face_bg_y[2],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_14.reg_psp_lut1_x3,GET_BITS(pp->face_bg_x[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_14.reg_psp_lut1_y3,GET_BITS(pp->face_bg_y[3],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_15.reg_psp_lut1_x4,GET_BITS(pp->face_bg_x[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_15.reg_psp_lut1_y4,GET_BITS(pp->face_bg_y[4],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_16.reg_psp_lut1_x5,GET_BITS(pp->face_bg_x[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_16.reg_psp_lut1_y5,GET_BITS(pp->face_bg_y[5],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_17.reg_psp_lut1_x6,GET_BITS(pp->face_bg_x[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_17.reg_psp_lut1_y6,GET_BITS(pp->face_bg_y[6],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_18.reg_psp_lut1_x7,GET_BITS(pp->face_bg_x[7],0,10));
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_18.reg_psp_lut1_y7,GET_BITS(pp->face_bg_y[7],0,10));
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_03.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_04.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_05.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_06.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_07.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_08.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_09.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_10.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_11.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_12.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_13.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_14.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_15.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_16.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_17.udata32);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_18.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCF);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_03.reg_psp_lut0_x0,GET_BITS(pp->face_fg_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_03.reg_psp_lut0_y0,GET_BITS(pp->face_fg_y[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_04.reg_psp_lut0_x1,GET_BITS(pp->face_fg_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_04.reg_psp_lut0_y1,GET_BITS(pp->face_fg_y[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_05.reg_psp_lut0_x2,GET_BITS(pp->face_fg_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_05.reg_psp_lut0_y2,GET_BITS(pp->face_fg_y[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_06.reg_psp_lut0_x3,GET_BITS(pp->face_fg_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_06.reg_psp_lut0_y3,GET_BITS(pp->face_fg_y[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_07.reg_psp_lut0_x4,GET_BITS(pp->face_fg_x[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_07.reg_psp_lut0_y4,GET_BITS(pp->face_fg_y[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_08.reg_psp_lut0_x5,GET_BITS(pp->face_fg_x[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_08.reg_psp_lut0_y5,GET_BITS(pp->face_fg_y[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_09.reg_psp_lut0_x6,GET_BITS(pp->face_fg_x[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_09.reg_psp_lut0_y6,GET_BITS(pp->face_fg_y[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_10.reg_psp_lut0_x7,GET_BITS(pp->face_fg_x[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_10.reg_psp_lut0_y7,GET_BITS(pp->face_fg_y[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_11.reg_psp_lut1_x0,GET_BITS(pp->face_bg_x[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_11.reg_psp_lut1_y0,GET_BITS(pp->face_bg_y[0],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_12.reg_psp_lut1_x1,GET_BITS(pp->face_bg_x[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_12.reg_psp_lut1_y1,GET_BITS(pp->face_bg_y[1],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_13.reg_psp_lut1_x2,GET_BITS(pp->face_bg_x[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_13.reg_psp_lut1_y2,GET_BITS(pp->face_bg_y[2],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_14.reg_psp_lut1_x3,GET_BITS(pp->face_bg_x[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_14.reg_psp_lut1_y3,GET_BITS(pp->face_bg_y[3],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_15.reg_psp_lut1_x4,GET_BITS(pp->face_bg_x[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_15.reg_psp_lut1_y4,GET_BITS(pp->face_bg_y[4],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_16.reg_psp_lut1_x5,GET_BITS(pp->face_bg_x[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_16.reg_psp_lut1_y5,GET_BITS(pp->face_bg_y[5],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_17.reg_psp_lut1_x6,GET_BITS(pp->face_bg_x[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_17.reg_psp_lut1_y6,GET_BITS(pp->face_bg_y[6],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_18.reg_psp_lut1_x7,GET_BITS(pp->face_bg_x[7],0,10));
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_18.reg_psp_lut1_y7,GET_BITS(pp->face_bg_y[7],0,10));
	}while(0);
	#endif
	return ret;
}

int PE_CHPI_OBC_HW_E60F20_SetEnable(UINT32 *onoff)
{
	int ret = RET_OK;
	#ifdef PE_CHPI_OBC_HW_E60F20_ENABLE
	UINT32 enable;
	PE_RCE_OBJT_HW_PARAM_DATA_E60F20_T *p_rco = &_g_pe_rco_hw_param_data_e60f20;
	PE_RCE_FACE_HW_PARAM_DATA_E60F20_T *p_rcf = &_g_pe_rcf_hw_param_data_e60f20;
	do{
		CHECK_KNULL(onoff);
		CHECK_KNULL(p_rcf->reg_user.data);
		CHECK_KNULL(p_rcf->reg_mask.data);
		CHECK_KNULL(p_rco->reg_user.data);
		CHECK_KNULL(p_rco->reg_mask.data);
		enable = (*onoff > 0)? 1:0;
		/* set tbl */
		PE_CHPI_TBL0_E60F20_Wr(rco.reg_rce_objt_ctrl_00.reg_psp_en,enable);
		PE_CHPI_TBL0_E60F20_WrFL(rco.reg_rce_objt_ctrl_00.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCO);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rco,reg_rce_objt_ctrl_00.reg_psp_en,enable);
		/* set tbl */
		PE_CHPI_TBL0_E60F20_Wr(rcf.reg_rce_face_ctrl_00.reg_psp_en,enable);
		PE_CHPI_TBL0_E60F20_WrFL(rcf.reg_rce_face_ctrl_00.udata32);
		/* count */
		PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_RCF);
		/* set user */
		PE_CHPI_OBC_HW_E60F20_USER(p_rcf,reg_rce_face_ctrl_00.reg_psp_en,enable);
	}while(0);
	#endif
	return ret;
}

