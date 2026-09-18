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

/** @file pe_cmg_hw_m23.c
 *
 *  driver for picture enhance color management functions. ( used only within kdriver )
 *	
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.03.15
 *  @modified date  2015.05.24 for SWMD
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

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_fwi_m23.h"
#include "pe_inf_m23.h"
#include "pe_cmg_hw_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMG_HW_M23_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/* see PE_M23_CC_PE1_CEN_IA_DATA_T */
union cen_ia_data {
	UINT32 udata32;
	struct {
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void PE_CMG_HW_M23_Init_CenRegister(void);
static void PE_CMG_HW_M23_SetCenRegionCtrlReg(UINT32 i_ui32RegionNum, UINT32 i_ui32wdata);
static void PE_CMG_HW_M23_CEGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmg_hw_m23_trace=0x0;	//default should be off.
static PE_CMG_HW_M23_SETTINGS_T _g_pe_cmg_hw_m23_info;
static UINT32 _g_cmg_hw_m23_pre_dse_lut[(PE_CMG_HW_M23_LUT_MAX-1)];	///<previous dse lut

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init color management
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count = 0;
	int i=0;
	UINT32 *p_pre_dse_lut = _g_cmg_hw_m23_pre_dse_lut;
	UINT32 dse_lut_data[32] = {\
		   0,  64, 128, 192, 256, 320, 384, 448, 512, \
		 576, 640, 704, 768, 832, 896, 960,1023,1023, \
		1023,1023,1023,1023,1023,1023,1023,1023,1023, \
		1023,1023,1023,1023,1023};
	do{
		CHECK_KNULL(pstParams);
		memset(&_g_pe_cmg_hw_m23_info,0x0,sizeof(PE_CMG_HW_M23_SETTINGS_T));
		/*WA. adjust target saturation*/ 
		_g_pe_cmg_hw_m23_info.org_target_sat = 0x80;
		if(PE_KDRV_VER_M23)
		{
			PE_CMG_HW_M23_Init_CenRegister();
			PE_CC_PE1_M23_QWr02(pe1_cen_ctrl_00,reg_cen_bypass,0x1,demo_mode,0x0);
			/* dse lut init */
			if (!pstParams->resume_mode)	//normal init
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,dse_lut_data[count]);	//y data
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,dse_lut_data[count]);	//x data
					PE_CC_PE1_M23_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for (i=0;i<(PE_CMG_HW_M23_LUT_MAX-1);i++)
				{
					p_pre_dse_lut[i] = ((dse_lut_data[i]<<16)&0x3ff0000)|(dse_lut_data[i]&0x3ff);
				}

				PE_DBG_CMG("\n init\n");
				PE_DBG_CMG("\n   [ i]    x,    y\n");
				for (i=0;i<(PE_CMG_HW_M23_LUT_MAX-1);i++)
				{
					PE_DBG_CMG("   [%02d] %4d, %4d\n", \
						i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
				}
			}
			else
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,GET_BITS(p_pre_dse_lut[count],0,10));	//y data
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,GET_BITS(p_pre_dse_lut[count],16,10));
					PE_CC_PE1_M23_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);

				PE_DBG_CMG("\n resume init\n");
				PE_DBG_CMG("\n   [ i]    x,    y\n");
				for (i=0;i<(PE_CMG_HW_M23_LUT_MAX-1);i++)
				{
					PE_DBG_CMG("   [%02d] %4d, %4d\n", \
						i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
				}
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set cen initial param
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
static void PE_CMG_HW_M23_Init_CenRegister(void)
{
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i = 0;

	/* hue */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00001000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
	}
	/* saturation */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00001100);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
	}
	/* value */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00001200);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
	}
	/* region debug color */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00001300);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
	}
	/* global delta gain */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00001600);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_DELTANUM); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
	}
	/* normal mode */
	PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,	0x00008000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);

	/* region delta gain */
	PE_CC_PE1_M23_Wr(pe1_cen_delta_ia_ctrl,	0x00001000);
	PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_DELTA_SETNUM); i++)
	{
		PE_CC_PE1_M23_Wr(pe1_cen_delta_ia_data,0x00000000);
		PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_data);
	}
	/* normal mode */
	PE_CC_PE1_M23_Wr(pe1_cen_delta_ia_ctrl,	0x00008000);
	PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);

	/* master gain */
	PE_CC_PE1_M23_Wr(pe1_cen_ctrl_04,	0x00000000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_04);
	PE_CC_PE1_M23_Wr(pe1_cen_ctrl_05,	0x00000000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_05);
	PE_CC_PE1_M23_Wr(pe1_cen_ctrl_06,	0x00000000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_06);
	PE_CC_PE1_M23_Wr(pe1_cen_ctrl_07,	0x00000000);
	PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_07);
	#endif /*PE_HW_M23_BRINGUP*/
	return;
}

/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmg_hw_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMG)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CMG)),\
			pstParams->print_lvl,_g_cmg_hw_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}

/**
 * set cen enable
 *
 * @param   *pstParams [in] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get cen enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set cen region enable
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 wdata=0;
	UINT32 count=0;
	LX_PE_CMG_REGION_ENABLE_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_ENABLE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_ENABLE_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_REGION_ENABLE_T\n");
			ret=RET_OK;
			break;
		}
		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(pstParams->enable[count])
				wdata |= (0x1<<(count+LX_PE_CMG_REGION_NUM));
			else
				wdata &= ~(0x1<<(count+LX_PE_CMG_REGION_NUM));

			if(pstParams->show_region[count])
				wdata |= (0x1<<(count));
			else
				wdata &= ~(0x1<<(count));
		}
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_M23_Wr(pe1_cen_ctrl_01,wdata);
				PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_01);
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get cen region enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_cen_ctrl_01);
				rdata = PE_CC_PE1_M23_Rd(pe1_cen_ctrl_01);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M23_RdFL(pe1_cen_ctrl_01);
				rdata = PE_CO_PE1_M23_Rd(pe1_cen_ctrl_01);
			}*/
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(rdata & (0x1<<(count+LX_PE_CMG_REGION_NUM)))
				pstParams->enable[count] = 1;
			else
				pstParams->enable[count] = 0;

			if(rdata & (0x1<<(count)))
				pstParams->show_region[count] = 1;
			else
				pstParams->show_region[count] = 0;
		}
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 x_wdata,y_wdata;
	UINT32 set_flag=0;
	PE_CMG_HW_M23_SETTINGS_T *pInfo=&_g_pe_cmg_hw_m23_info;
	LX_PE_CMG_REGION_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	union cen_ia_data hue_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data sat_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data val_data[LX_PE_CMG_TBLPOINT];

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_REGION_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_M23_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"region_num(%d) is out of range.\n",pstParams->region_num);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				set_flag = 0;
				/* check double setting */
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					if(pInfo->rgn_set[pstParams->region_num].hue_x[count]!=pstParams->hue_x[count] || \
						pInfo->rgn_set[pstParams->region_num].hue_g[count]!=pstParams->hue_g[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_x[count]!=pstParams->sat_x[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_g[count]!=pstParams->sat_g[count] || \
						pInfo->rgn_set[pstParams->region_num].val_x[count]!=pstParams->val_x[count] || \
						pInfo->rgn_set[pstParams->region_num].val_g[count]!=pstParams->val_g[count])
					{
						set_flag=1;
						break;
					}
				}
				if(set_flag)
				{
					PE_DBG_CMG(" set region : num:%d\n", pstParams->region_num);
					PE_CC_PE1_M23_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable,      0x0, 	//[15] 0:host access, 1:normal mode
																hif_cen_ai,      0x1,	//[12] ai 0:disable, 1:enable
																hif_cen_address, 0x0);	//[7:0] address
					start_addr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
					/* H color region table : 000 */
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);			//[10:8]
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						/* hue_x,x_wdata : 0~1024(0~720 degree) */
						x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
						y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);

						hue_data[count].hif_cen_x_wdata = x_wdata;
						hue_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* S color region table : 001 */
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);			//[10:8]
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
						y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127

						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);

						sat_data[count].hif_cen_x_wdata = x_wdata;
						sat_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* V color region table : 010 */
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);			//[10:8]
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
						y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127

						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_M23_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);

						val_data[count].hif_cen_x_wdata = x_wdata;
						val_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* normal operation */
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
					PE_CC_PE1_M23_QWr01(pe1_cen_upd_ctrl,	cen_lut_update, 	0x1);	//[0] cen_lut_update
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						pInfo->rgn_set[pstParams->region_num].hue_x[count]=pstParams->hue_x[count];
						pInfo->rgn_set[pstParams->region_num].hue_g[count]=pstParams->hue_g[count];
						pInfo->rgn_set[pstParams->region_num].sat_x[count]=pstParams->sat_x[count];
						pInfo->rgn_set[pstParams->region_num].sat_g[count]=pstParams->sat_g[count];
						pInfo->rgn_set[pstParams->region_num].val_x[count]=pstParams->val_x[count];
						pInfo->rgn_set[pstParams->region_num].val_g[count]=pstParams->val_g[count];
					}
				}
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, j, k;
	union cen_ia_data hue_data[128];
	union cen_ia_data sat_data[128];
	union cen_ia_data val_data[128];
	static LX_PE_CMG_REGION_ALL_T prevParams;
	static UINT32 initCenRegion = 0;

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);

		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if (initCenRegion == 0)
				{
					PE_PRINT_NOTI("set 1st\n");
					initCenRegion = 1;
				}
				else if (memcmp(&prevParams, pstParams, sizeof(LX_PE_CMG_REGION_ALL_T))==0)
				{
					PE_DBG_CMG("set skip\n");
					break;
				}
				else
				{
					PE_DBG_CMG("set region\n");
				}

				memcpy(&prevParams, pstParams, sizeof(LX_PE_CMG_REGION_ALL_T));

				//LX_PE_CMG_REGION_NUM:16, LX_PE_CMG_TBLPOINT:8
				for (i=0; i<LX_PE_CMG_REGION_NUM; i++)
				{
					for (j=0; j<LX_PE_CMG_TBLPOINT; j++)
					{
						k = (i*LX_PE_CMG_TBLPOINT) + j;

						/* hue, x:0~1024(0~720 degree) */
						hue_data[k].hif_cen_x_wdata = (UINT32)GET_BITS(pstParams->cen_region_lut[i].hue_x[j],0,10);
						hue_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].hue_g[j],0,7);// 0~127

						/* saturation */
						sat_data[k].hif_cen_x_wdata = GET_BITS(pstParams->cen_region_lut[i].sat_x[j],0,7);// 0~100
						sat_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].sat_g[j],0,7);// 0~127

						/* value */
						val_data[k].hif_cen_x_wdata = GET_BITS(pstParams->cen_region_lut[i].val_x[j],0,8);// 0~255
						val_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].val_g[j],0,7);// 0~127
					}
				}

				//[10:8] reg_cen_ai_sel
				//'000'  H Color region table  :  range of address 0 ~ 127
				//'001'  S Color region table  :  range of address 0 ~ 127
				//'010'  V Color region table  :  range of address 0 ~ 127
				//'011'  Color of Region  : range of address 0 ~ 15
				//'110'  Global Delta gain : range of address 0 ~ 5

				/* H color region table : 000 */
				PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,0x00001000);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_M23_Wr(pe1_cen_ia_data,hue_data[i].udata32);
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
				}
				/* S color region table : 001 */
				PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,0x00001100);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_M23_Wr(pe1_cen_ia_data,sat_data[i].udata32);
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
				}
				/* V color region table : 010 */
				PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,0x00001200);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_M23_Wr(pe1_cen_ia_data,val_data[i].udata32);
					PE_CC_PE1_M23_WrFL(pe1_cen_ia_data);
				}
				/* normal mode */
				PE_CC_PE1_M23_Wr(pe1_cen_ia_ctrl,0x00008000);//[15] 1:normal mode,[12] ai 0:disable,[7:0] address 0
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);

				/* lut update */
				PE_CC_PE1_M23_QWr01(pe1_cen_upd_ctrl,cen_lut_update,0x1);//[0] cen_lut_update
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get cen region
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 x_wdata=0,y_wdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_M23_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"region_num(%d) is out of range.\n",pstParams->region_num);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		start_addr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_cen_ia_ctrl);
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x1);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address

				/* H color region table : 000 */
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_M23_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					/* x_wdata,hue_x 0~1024 (0~720 degree) */
					pstParams->hue_x[count] = (UINT16)GET_BITS(x_wdata,0,10);
					pstParams->hue_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* S color region table : 001 */
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_M23_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					pstParams->sat_x[count] = (UINT8)GET_BITS(x_wdata,0,7);	// 0~100
					pstParams->sat_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* V color region table : 010 */
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_M23_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_M23_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->val_x[count] = (UINT8)GET_BITS(x_wdata,0,8);	// 0~255
					pstParams->val_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* normal operation */
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_CC_PE1_M23_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 delta[3];		// -128 ~ 127, hsv or gbr
	UINT32 wdata=0;
	UINT32 region_num=0;
	PE_CMG_HW_M23_SETTINGS_T *pInfo=&_g_pe_cmg_hw_m23_info;
	LX_PE_CMG_REGION_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_REGION_CTRL_T\n");
			ret=RET_OK;
			break;
		}

		PE_CMG_HW_M23_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"region_num(%d) is out of range.\n",pstParams->region_num);

		PE_DBG_CMG(" set: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);

		region_num = pstParams->region_num;

		if(PE_KDRV_VER_M23) 
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{

				/* region delta */
				if(pInfo->rgn_ctrl[region_num].region_delta[0]!=pstParams->region_delta[0] || \
					pInfo->rgn_ctrl[region_num].region_delta[1]!=pstParams->region_delta[1] || \
					pInfo->rgn_ctrl[region_num].region_delta[2]!=pstParams->region_delta[2] || \
					pInfo->rgn_ctrl[region_num].region_delta[3]!=pstParams->region_delta[3] || \
					pInfo->rgn_ctrl[region_num].region_delta[4]!=pstParams->region_delta[4] || \
					pInfo->rgn_ctrl[region_num].region_delta[5]!=pstParams->region_delta[5])
				{

					PE_DBG_CMG(" set delta\n");

					start_addr = region_num*LX_PE_CMG_DELTA_SETNUM;

					PE_CC_PE1_M23_RdFL(pe1_cen_delta_ia_ctrl);
					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x0);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x1);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,start_addr);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);

					for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++) 
					{

						wdata=0;

						delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
						delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
						delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127

						wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);

						PE_CC_PE1_M23_Wr(pe1_cen_delta_ia_data,	wdata);
						PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_data);
					}

					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x1);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x0);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,0x0);	//[7:0] address
					PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);

					pInfo->rgn_ctrl[region_num].region_delta[0]=pstParams->region_delta[0];
					pInfo->rgn_ctrl[region_num].region_delta[1]=pstParams->region_delta[1];
					pInfo->rgn_ctrl[region_num].region_delta[2]=pstParams->region_delta[2];
					pInfo->rgn_ctrl[region_num].region_delta[3]=pstParams->region_delta[3];
					pInfo->rgn_ctrl[region_num].region_delta[4]=pstParams->region_delta[4];
					pInfo->rgn_ctrl[region_num].region_delta[5]=pstParams->region_delta[5];
				}

				/* region gain */
				if(pInfo->rgn_ctrl[region_num].master_gain!=pstParams->master_gain) {

					PE_DBG_CMG(" set master_gain\n");

					wdata = GET_BITS(pstParams->master_gain,0,8);	// 0~128~255

					PE_CMG_HW_M23_SetCenRegionCtrlReg(region_num, wdata);

					pInfo->rgn_ctrl[region_num].master_gain=pstParams->master_gain;
				}
			}
		}
		else 
		{

			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}

	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get cen region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 re_mgain=0;
	UINT32 re_delta[LX_PE_CMG_DELTA_SETNUM];	// hsv or gbr

	do {

		CHECK_KNULL(pstParams);

		PE_CHECK_WINID(pstParams->win_id);

		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id)) {

				/* region delta */
				start_addr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
				PE_CC_PE1_M23_RdFL(pe1_cen_delta_ia_ctrl);
				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x0);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x1);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,start_addr);	//[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++) {

					PE_CC_PE1_M23_RdFL(pe1_cen_delta_ia_data);
					re_delta[count] = PE_CC_PE1_M23_Rd(pe1_cen_delta_ia_data);
				}

				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x1);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x0);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,0x0);	//[7:0] address
				PE_CC_PE1_M23_WrFL(pe1_cen_delta_ia_ctrl);

				/* region gain */
				PE_CMG_HW_M23_CEGetRegGain(pstParams->region_num, &re_mgain);

				pstParams->master_gain = (UINT8)GET_BITS(re_mgain,0,8);	// region master gain, 0~128~255
				pstParams->region_delta[0] = (SINT8)GET_BITS(re_delta[0],16,8);	// h, -128 ~ 127
				pstParams->region_delta[1] = (SINT8)GET_BITS(re_delta[0],8,8);	// s, -128 ~ 127
				pstParams->region_delta[2] = (SINT8)GET_BITS(re_delta[0],0,8);	// v, -128 ~ 127
				pstParams->region_delta[3] = (SINT8)GET_BITS(re_delta[1],16,8);	// g, -128 ~ 127
				pstParams->region_delta[4] = (SINT8)GET_BITS(re_delta[1],8,8);	// b, -128 ~ 127
				pstParams->region_delta[5] = (SINT8)GET_BITS(re_delta[1],0,8);	// r, -128 ~ 127
			}
		}
		else
		{

			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}

		PE_DBG_CMG(" Get: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);

	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set cen color ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_CMG_COLOR_CTRL_T *pp =  pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_SHP_RE_EASY_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_COLOR_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			//PE_DBG_CMG("duplicated DB : LX_PE_CMG_COLOR_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMG("set pstParams[%d] : sat:%d\n", \
			pstParams->win_id,pstParams->saturation);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));//[7:0] reg_ihsv_sgain
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get cen color ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
				pstParams->saturation=(UINT16)rdata;
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M23_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
				pstParams->saturation=(UINT16)rdata;
			}*/
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
		PE_DBG_CMG("get pstParams[%d] : sat:%d\n",pstParams->win_id,pstParams->saturation);
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	LX_PE_CMG_CW_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_CW_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMG("set[%d] en:%d, yc:%d, x:%d,%d,%d,%d,%d\n"\
			" y:%d,%d,%d,%d,%d, sel:0x%x, g:%d\n", \
			pstParams->win_id, pstParams->cw_en, \
			pstParams->gain_sel, pstParams->gain_x[0], \
			pstParams->gain_x[1], pstParams->gain_x[2], pstParams->gain_x[3], \
			pstParams->gain_x[4], pstParams->gain_y[0], pstParams->gain_y[1], \
			pstParams->gain_y[2], pstParams->gain_y[3], pstParams->gain_y[4], \
			pstParams->region_sel, pstParams->region_gain);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if (hw_opt.external_chip==0)
				{
					PE_CC2_PE1_M23_QWr01(pe1_cw_ctrl_00, reg_cw_en,				GET_BITS(pstParams->cw_en,0,1));
				}
				else
				{
					PE_CC2_PE1_M23_QWr01(pe1_cw_ctrl_00, reg_cw_en,				0x0);
				}

				PE_CC2_PE1_M23_RdFL(pe1_cw_ctrl_02);
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region0_sel,	GET_BITS(pstParams->region_sel,0,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region1_sel,	GET_BITS(pstParams->region_sel,1,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region2_sel,	GET_BITS(pstParams->region_sel,2,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region3_sel,	GET_BITS(pstParams->region_sel,3,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region4_sel,	GET_BITS(pstParams->region_sel,4,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region5_sel,	GET_BITS(pstParams->region_sel,5,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region6_sel,	GET_BITS(pstParams->region_sel,6,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region7_sel,	GET_BITS(pstParams->region_sel,7,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region8_sel,	GET_BITS(pstParams->region_sel,8,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region9_sel,	GET_BITS(pstParams->region_sel,9,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region10_sel,	GET_BITS(pstParams->region_sel,10,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region11_sel,	GET_BITS(pstParams->region_sel,11,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region12_sel,	GET_BITS(pstParams->region_sel,12,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region13_sel,	GET_BITS(pstParams->region_sel,13,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region14_sel,	GET_BITS(pstParams->region_sel,14,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region15_sel,	GET_BITS(pstParams->region_sel,15,1));
				PE_CC2_PE1_M23_Wr01(pe1_cw_ctrl_02,	color_region_gain,	GET_BITS(pstParams->region_gain,0,8));
				PE_CC2_PE1_M23_WrFL(pe1_cw_ctrl_02);
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get clear white
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 sel_data;
	do{
		CHECK_KNULL(pstParams);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				if(pstParams->region_gain==0)	pstParams->region_gain=1;
				PE_CC2_PE1_M23_QRd01(pe1_cw_ctrl_00,reg_cw_en,             (pstParams->cw_en));

				PE_CC2_PE1_M23_RdFL(pe1_cw_ctrl_02);
				sel_data = PE_CC2_PE1_M23_Rd(pe1_cw_ctrl_02);
				pstParams->region_sel = GET_BITS(sel_data,0,16);	//[15:0]
				PE_CC2_PE1_M23_Rd01(pe1_cw_ctrl_02,color_region_gain, (pstParams->region_gain));
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
		PE_DBG_CMG("get[%d] en:%d, yc:%d, x:%d,%d,%d,%d,%d\n"\
			" y:%d,%d,%d,%d,%d, sel:0x%x, g:%d\n", \
			pstParams->win_id, pstParams->cw_en, \
			pstParams->gain_sel, pstParams->gain_x[0], \
			pstParams->gain_x[1], pstParams->gain_x[2], pstParams->gain_x[3], \
			pstParams->gain_x[4], pstParams->gain_y[0], pstParams->gain_y[1], \
			pstParams->gain_y[2], pstParams->gain_y[3], pstParams->gain_y[4], \
			pstParams->region_sel, pstParams->region_gain);
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set clear white gain
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_CMG_CW_GAIN_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_GAIN_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_GAIN_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_CW_GAIN_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC2_PE1_M23_QWr03(pe1_cw_ctrl_01,user_ctrl_g_gain, GET_BITS(pstParams->g_gain,0,8),\
                                                      user_ctrl_b_gain, GET_BITS(pstParams->b_gain,0,8),\
                                                      user_ctrl_r_gain, GET_BITS(pstParams->r_gain,0,8));
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get clear white gain
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC2_PE1_M23_QRd03(pe1_cw_ctrl_01,user_ctrl_g_gain, pstParams->g_gain,\
                                                     user_ctrl_b_gain, pstParams->b_gain,\
                                                     user_ctrl_r_gain, pstParams->r_gain);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M23_QRd03(pe1_cw_ctrl_01,user_ctrl_g_gain, pstParams->g_gain,\
                                                     user_ctrl_b_gain, pstParams->b_gain,\
                                                     user_ctrl_r_gain, pstParams->r_gain);
			}*/
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * Sets the cen region control registers
 *
 * @param   i_ui32RegionNum 	[in] UINT32
 * @param   i_ui32wdata 		[in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_CMG_HW_M23_SetCenRegionCtrlReg(UINT32 i_ui32RegionNum, UINT32 i_ui32wdata)
{
	#ifdef PE_HW_M23_BRINGUP
	switch(i_ui32RegionNum)
	{
		case 0:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr0,	i_ui32wdata);
			break;
		case 1:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr1,	i_ui32wdata);
			break;
		case 2:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr2,	i_ui32wdata);
			break;
		case 3:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr3,	i_ui32wdata);
			break;
		case 4:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr4,	i_ui32wdata);
			break;
		case 5:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr5,	i_ui32wdata);
			break;
		case 6:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr6,	i_ui32wdata);
			break;
		case 7:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr7,	i_ui32wdata);
			break;
		case 8:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr8,	i_ui32wdata);
			break;
		case 9:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr9,	i_ui32wdata);
			break;
		case 10:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr10,	i_ui32wdata);
			break;
		case 11:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr11,	i_ui32wdata);
			break;
		case 12:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr12,	i_ui32wdata);
			break;
		case 13:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr13,	i_ui32wdata);
			break;
		case 14:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr14,	i_ui32wdata);
			break;
		case 15:
		default:
			PE_CC_PE1_M23_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr15,	i_ui32wdata);
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return;
}

/**
 * Gets CE region gain register value
 *
 * @param   i_ui32RegionNum 	[in] 	UINT32
 * @param   *o_ui32RegGain		[out] 	UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_CMG_HW_M23_CEGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain)
{
	#ifndef PE_HW_M23_BRINGUP
	UINT32 re_mgain = 0;

	switch(i_ui32RegionNum)
	{
		case 0:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr0,	re_mgain);
			break;
		case 1:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr1,	re_mgain);
			break;
		case 2:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr2,	re_mgain);
			break;
		case 3:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr3,	re_mgain);
			break;
		case 4:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr4,	re_mgain);
			break;
		case 5:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr5,	re_mgain);
			break;
		case 6:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr6,	re_mgain);
			break;
		case 7:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr7,	re_mgain);
			break;
		case 8:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr8,	re_mgain);
			break;
		case 9:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr9,	re_mgain);
			break;
		case 10:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr10,	re_mgain);
			break;
		case 11:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr11,	re_mgain);
			break;
		case 12:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr12,	re_mgain);
			break;
		case 13:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr13,	re_mgain);
			break;
		case 14:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr14,	re_mgain);
			break;
		case 15:
		default:
			PE_CC_PE1_M23_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr15,	re_mgain);
			break;
	}

	*o_ui32RegGain = re_mgain;
	#endif /*PE_HW_M23_BRINGUP*/
	return;
}

/**
 * set Ext/Inner Pattern
 *
 * @param	*pstParams [in] LX_PE_CMG_EXT_PATTERN_INFO_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *p)
{
	int ret = RET_OK;
	UINT32 iter, ia_data;
	UINT32 x_ofst,y_ofst,x_size,y_size;

#define PE_CMG_HW_M23_4K_H_MAX			3840
#define PE_CMG_HW_M23_4K_V_MAX			2160
#define PE_CMG_HW_M23_CORE_NUM			1

	do {
		CHECK_KNULL(p);
		#ifdef PE_HW_M23_BRINGUP
		if (PE_KDRV_VER_M23)
		{
			LX_PE_CMG_EXT_PATTERN_INFO_T *pp = (LX_PE_CMG_EXT_PATTERN_INFO_T *)p;
			static LX_PE_CMG_EXT_PATTERN_INFO_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_CMG_EXT_PATTERN_INFO_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_CMG("duplicated DB : LX_PE_CMG_EXT_PATTERN_INFO_T\n");
				ret=RET_OK;
				break;
			}
 			if (PE_CHECK_WIN0(p->win_id))
			{
				PE_DBG_CMG("set[%d] bOnOff:%d, eMode:%d\n"\
				" stGradInfo: numGrad   : %d\n" \
				"             eGradMode : %d\n" \
				" stWinboxInfo: u8NumWin: %d\n", \
				p->win_id, p->bOnOff, p->eMode, p->stGradInfo.numGrad, p->stGradInfo.eGradMode,\
				p->stWinboxInfo.u8NumWin);
				PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_00, 0x00000000);
				PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_00);
				PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_01, 0x00000000);
				PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_01);
				PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_02, 0x00000000);
				PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_02);
				PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_03, 0x00000000);
				PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_03);
				PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00000000);
				PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
				OS_MsecSleep(30);

				if (!p->bOnOff)
					break;

				if (p->eMode == LX_PE_EXT_PATTERN_WINBOX)
				{
					if (p->stWinboxInfo.u8NumWin > LX_PE_MAX_EXT_PATTERN_WINBOX)
						p->stWinboxInfo.u8NumWin = LX_PE_MAX_EXT_PATTERN_WINBOX;

					PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_00, 0x07800000);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_00);

					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001000);	// patch color
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						ia_data = p->stWinboxInfo.stWinBoxAttr[iter].fill_R |
							(p->stWinboxInfo.stWinBoxAttr[iter].fill_B << 10) |
							(p->stWinboxInfo.stWinBoxAttr[iter].fill_G << 20);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001020);	// patch start (x,y)
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						x_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].x);
						y_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].y);
						ia_data = ((x_ofst / PE_CMG_HW_M23_CORE_NUM) << 16) | (y_ofst);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001040);	// patch end (x,y)
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						x_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].x);
						y_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].y);
						x_size = (p->stWinboxInfo.stWinBoxAttr[iter].w);
						y_size = (p->stWinboxInfo.stWinBoxAttr[iter].h);
						ia_data = (((x_ofst + x_size) / PE_CMG_HW_M23_CORE_NUM) << 16) | (y_ofst + y_size);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}
					if (p->stWinboxInfo.u8NumWin > 0)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_0_en, 1);
					if (p->stWinboxInfo.u8NumWin > 1)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_1_en, 1);
					if (p->stWinboxInfo.u8NumWin > 2)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_2_en, 1);
					if (p->stWinboxInfo.u8NumWin > 3)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_3_en, 1);
					if (p->stWinboxInfo.u8NumWin > 4)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_4_en, 1);
					if (p->stWinboxInfo.u8NumWin > 5)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_5_en, 1);
					if (p->stWinboxInfo.u8NumWin > 6)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_6_en, 1);
					if (p->stWinboxInfo.u8NumWin > 7)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_7_en, 1);
					if (p->stWinboxInfo.u8NumWin > 8)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_8_en, 1);
					if (p->stWinboxInfo.u8NumWin > 9)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_02, patch_9_en, 1);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_02);
					PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_03, 0x00000000);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_03);
					PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_00, 0x07800001);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_00);
				}
				else if (p->eMode == LX_PE_EXT_PATTERN_GRADATION)
				{
					if (p->stGradInfo.numGrad > LX_PE_MAX_EXT_PATTERN_GRADATION_LINE)
						p->stGradInfo.numGrad = LX_PE_MAX_EXT_PATTERN_GRADATION_LINE;
					if (p->stGradInfo.numGrad % 2)
					{
						PE_DBG_CMG("ERROR.\n");
						ret = RET_ERROR;
						break;
					}

					PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_00, 0x07800002);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_00);

					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001060);	// gradation start color
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						ia_data = p->stGradInfo.stLineAttr[iter].start_R |
							(p->stGradInfo.stLineAttr[iter].start_B << 10) |
							(p->stGradInfo.stLineAttr[iter].start_G << 20);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001064);	// gradation step color
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						ia_data = p->stGradInfo.stLineAttr[iter].step_R |
							(p->stGradInfo.stLineAttr[iter].step_B << 10) |
							(p->stGradInfo.stLineAttr[iter].step_G << 20);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_M23_Wr(pe1_tpg_ia_ctrl, 0x00001068);	// gradation region size
					PE_CC_PE1_M23_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						if (p->stGradInfo.eGradMode == LX_PE_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL)
							ia_data = ((PE_CMG_HW_M23_4K_V_MAX) / p->stGradInfo.numGrad) * (iter + 1);
						else
							ia_data = ((PE_CMG_HW_M23_4K_H_MAX / PE_CMG_HW_M23_CORE_NUM) / p->stGradInfo.numGrad) * (iter + 1);
						PE_CC_PE1_M23_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_M23_WrFL(pe1_tpg_ia_data);
					}

					PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_direction, p->stGradInfo.eGradMode ? 0 : 1);
					PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_stride, p->stGradInfo.stLineAttr[0].strideSize);
					if (p->stGradInfo.numGrad > 0)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_bar_0_en, 1);
					if (p->stGradInfo.numGrad > 1)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_bar_1_en, 1);
					if (p->stGradInfo.numGrad > 2)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_bar_2_en, 1);
					if (p->stGradInfo.numGrad > 3)
						PE_CC_PE1_M23_Wr01(pe1_tpg_ctrl_01, gradation_bar_3_en, 1);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_01);
					PE_CC_PE1_M23_Wr(pe1_tpg_ctrl_00, 0x07800003);
					PE_CC_PE1_M23_WrFL(pe1_tpg_ctrl_00);
				}
				else
				{
					PE_DBG_CMG("ERROR.\n");	ret = RET_ERROR;
				}
			}
			OS_MsecSleep(30);
 		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
		#endif
	} while (0);
	return ret;
}
/**
 * set clear white table setting
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_CMG_CW_TABLE_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_TABLE_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_TABLE_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_CW_TABLE_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMG("set[%d] \n"\
			" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" hue_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_y: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
			pstParams->win_id, \
			pstParams->cw_hue_x[0], pstParams->cw_hue_x[1], pstParams->cw_hue_x[2], pstParams->cw_hue_x[3], \
			pstParams->cw_hue_x[4], pstParams->cw_hue_x[5], pstParams->cw_hue_x[6], pstParams->cw_hue_x[7], \
			pstParams->cw_hue_y[0], pstParams->cw_hue_y[1], pstParams->cw_hue_y[2], pstParams->cw_hue_y[3], \
			pstParams->cw_hue_y[4], pstParams->cw_hue_y[5], pstParams->cw_hue_y[6], pstParams->cw_hue_y[7], \
			pstParams->cw_sat_x[0], pstParams->cw_sat_x[1], pstParams->cw_sat_x[2], pstParams->cw_sat_x[3], \
			pstParams->cw_sat_x[4], pstParams->cw_sat_x[5], pstParams->cw_sat_x[6], pstParams->cw_sat_x[7], \
			pstParams->cw_sat_y[0], pstParams->cw_sat_y[1], pstParams->cw_sat_y[2], pstParams->cw_sat_y[3], \
			pstParams->cw_sat_y[4], pstParams->cw_sat_y[5], pstParams->cw_sat_y[6], pstParams->cw_sat_y[7], \
			pstParams->cw_val_x[0], pstParams->cw_val_x[1], pstParams->cw_val_x[2], pstParams->cw_val_x[3], \
			pstParams->cw_val_x[4], pstParams->cw_val_x[5], pstParams->cw_val_x[6], pstParams->cw_val_x[7], \
			pstParams->cw_val_y[0], pstParams->cw_val_y[1], pstParams->cw_val_y[2], pstParams->cw_val_y[3], \
			pstParams->cw_val_y[4], pstParams->cw_val_y[5], pstParams->cw_val_y[6], pstParams->cw_val_y[7]);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* hue */
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_00, reg_crgn_hue_gain_y0,	GET_BITS(pstParams->cw_hue_y[0],0,8),\
														   reg_crgn_hue_gain_x0,	GET_BITS(pstParams->cw_hue_x[0],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_01, reg_crgn_hue_gain_y1,	GET_BITS(pstParams->cw_hue_y[1],0,8),\
														   reg_crgn_hue_gain_x1,	GET_BITS(pstParams->cw_hue_x[1],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_02, reg_crgn_hue_gain_y2,	GET_BITS(pstParams->cw_hue_y[2],0,8),\
														   reg_crgn_hue_gain_x2,	GET_BITS(pstParams->cw_hue_x[2],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_03, reg_crgn_hue_gain_y3,	GET_BITS(pstParams->cw_hue_y[3],0,8),\
														   reg_crgn_hue_gain_x3,	GET_BITS(pstParams->cw_hue_x[3],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_04, reg_crgn_hue_gain_y4,	GET_BITS(pstParams->cw_hue_y[4],0,8),\
														   reg_crgn_hue_gain_x4,	GET_BITS(pstParams->cw_hue_x[4],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_05, reg_crgn_hue_gain_y5,	GET_BITS(pstParams->cw_hue_y[5],0,8),\
														   reg_crgn_hue_gain_x5,	GET_BITS(pstParams->cw_hue_x[5],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_06, reg_crgn_hue_gain_y6,	GET_BITS(pstParams->cw_hue_y[6],0,8),\
														   reg_crgn_hue_gain_x6,	GET_BITS(pstParams->cw_hue_x[6],0,10));
				PE_CC2_PE1_M23_QWr02(pe1_cw_crgn_ctrl_07, reg_crgn_hue_gain_y7,	GET_BITS(pstParams->cw_hue_y[7],0,8),\
														   reg_crgn_hue_gain_x7,	GET_BITS(pstParams->cw_hue_x[7],0,10));
				/* sat */
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_08, reg_crgn_sat_gain_y0,	GET_BITS(pstParams->cw_sat_y[0],0,8),\
														   reg_crgn_sat_gain_x0,	GET_BITS(pstParams->cw_sat_x[0],0,8),\
														   reg_crgn_sat_gain_y1,	GET_BITS(pstParams->cw_sat_y[1],0,8),\
														   reg_crgn_sat_gain_x1,	GET_BITS(pstParams->cw_sat_x[1],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_09, reg_crgn_sat_gain_y2,	GET_BITS(pstParams->cw_sat_y[2],0,8),\
														   reg_crgn_sat_gain_x2,	GET_BITS(pstParams->cw_sat_x[2],0,8),\
														   reg_crgn_sat_gain_y3,	GET_BITS(pstParams->cw_sat_y[3],0,8),\
														   reg_crgn_sat_gain_x3,	GET_BITS(pstParams->cw_sat_x[3],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_10, reg_crgn_sat_gain_y4,	GET_BITS(pstParams->cw_sat_y[4],0,8),\
														   reg_crgn_sat_gain_x4,	GET_BITS(pstParams->cw_sat_x[4],0,8),\
														   reg_crgn_sat_gain_y5,	GET_BITS(pstParams->cw_sat_y[5],0,8),\
														   reg_crgn_sat_gain_x5,	GET_BITS(pstParams->cw_sat_x[5],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_11, reg_crgn_sat_gain_y6,	GET_BITS(pstParams->cw_sat_y[6],0,8),\
														   reg_crgn_sat_gain_x6,	GET_BITS(pstParams->cw_sat_x[6],0,8),\
														   reg_crgn_sat_gain_y7,	GET_BITS(pstParams->cw_sat_y[7],0,8),\
														   reg_crgn_sat_gain_x7,	GET_BITS(pstParams->cw_sat_x[7],0,8));
				/* val */
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_12, reg_crgn_val_gain_y0,	GET_BITS(pstParams->cw_val_y[0],0,8),\
														   reg_crgn_val_gain_x0,	GET_BITS(pstParams->cw_val_x[0],0,8),\
														   reg_crgn_val_gain_y1,	GET_BITS(pstParams->cw_val_y[1],0,8),\
														   reg_crgn_val_gain_x1,	GET_BITS(pstParams->cw_val_x[1],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_13, reg_crgn_val_gain_y2,	GET_BITS(pstParams->cw_val_y[2],0,8),\
														   reg_crgn_val_gain_x2,	GET_BITS(pstParams->cw_val_x[2],0,8),\
														   reg_crgn_val_gain_y3,	GET_BITS(pstParams->cw_val_y[3],0,8),\
														   reg_crgn_val_gain_x3,	GET_BITS(pstParams->cw_val_x[3],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_14, reg_crgn_val_gain_y4,	GET_BITS(pstParams->cw_val_y[4],0,8),\
														   reg_crgn_val_gain_x4,	GET_BITS(pstParams->cw_val_x[4],0,8),\
														   reg_crgn_val_gain_y5,	GET_BITS(pstParams->cw_val_y[5],0,8),\
														   reg_crgn_val_gain_x5,	GET_BITS(pstParams->cw_val_x[5],0,8));
				PE_CC2_PE1_M23_QWr04(pe1_cw_crgn_ctrl_15, reg_crgn_val_gain_y6,	GET_BITS(pstParams->cw_val_y[6],0,8),\
														   reg_crgn_val_gain_x6,	GET_BITS(pstParams->cw_val_x[6],0,8),\
														   reg_crgn_val_gain_y7,	GET_BITS(pstParams->cw_val_y[7],0,8),\
														   reg_crgn_val_gain_x7,	GET_BITS(pstParams->cw_val_x[7],0,8));
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set clear white table setting
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_CMG_HW_M23_SETTINGS_T *pInfo=&_g_pe_cmg_hw_m23_info;
	LX_PE_CMG_VSPCC_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_VSPCC_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_VSPCC_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMG("duplicated DB : LX_PE_CMG_VSPCC_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMG("set[%d] \n"\
			"satTarget : %d\n" \
			"objMapGainLUT_x : %d, %d, %d, %d" \
			"objMapGainLUT_y : %d, %d, %d, %d" \
			"faceMapGainLUT_x : %d, %d, %d, %d" \
			"faceMapGainLUT_y : %d, %d, %d, %d" \
			" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" hue_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_g: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
			pstParams->win_id, \
			pstParams->satTarget,\
			pstParams->objMapGainLUT_x[0],pstParams->objMapGainLUT_x[1],pstParams->objMapGainLUT_x[2],pstParams->objMapGainLUT_x[3],\
			pstParams->objMapGainLUT_y[0],pstParams->objMapGainLUT_y[1],pstParams->objMapGainLUT_y[2],pstParams->objMapGainLUT_y[3],\
			pstParams->faceMapGainLUT_x[0],pstParams->faceMapGainLUT_x[1],pstParams->faceMapGainLUT_x[2],pstParams->faceMapGainLUT_x[3],\
			pstParams->faceMapGainLUT_y[0],pstParams->faceMapGainLUT_y[1],pstParams->faceMapGainLUT_y[2],pstParams->faceMapGainLUT_y[3],\
			pstParams->hue_x[0], pstParams->hue_x[1], pstParams->hue_x[2], pstParams->hue_x[3], \
			pstParams->hue_x[4], pstParams->hue_x[5], pstParams->hue_x[6], pstParams->hue_x[7], \
			pstParams->hue_g[0], pstParams->hue_g[1], pstParams->hue_g[2], pstParams->hue_g[3], \
			pstParams->hue_g[4], pstParams->hue_g[5], pstParams->hue_g[6], pstParams->hue_g[7], \
			pstParams->sat_x[0], pstParams->sat_x[1], pstParams->sat_x[2], pstParams->sat_x[3], \
			pstParams->sat_x[4], pstParams->sat_x[5], pstParams->sat_x[6], pstParams->sat_x[7], \
			pstParams->sat_g[0], pstParams->sat_g[1], pstParams->sat_g[2], pstParams->sat_g[3], \
			pstParams->sat_g[4], pstParams->sat_g[5], pstParams->sat_g[6], pstParams->sat_g[7], \
			pstParams->val_x[0], pstParams->val_x[1], pstParams->val_x[2], pstParams->val_x[3], \
			pstParams->val_x[4], pstParams->val_x[5], pstParams->val_x[6], pstParams->val_x[7], \
			pstParams->val_g[0], pstParams->val_g[1], pstParams->val_g[2], pstParams->val_g[3], \
			pstParams->val_g[4], pstParams->val_g[5], pstParams->val_g[6], pstParams->val_g[7]);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* to adjust target_sat according to vsp saturation see */
				//PE_CEO_PE1_M23_QWr01(pe1_vspyc_ctrl_01, saturation_target, GET_BITS(pstParams->satTarget, 0, 8));
				pInfo->org_target_sat = pstParams->satTarget;

				/* hue_g,x */
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_00,	reg_crgn_hue_gain_y0, GET_BITS(pstParams->hue_g[0], 0, 8),\
															reg_crgn_hue_gain_x0, GET_BITS(pstParams->hue_x[0], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_01,	reg_crgn_hue_gain_y1, GET_BITS(pstParams->hue_g[1], 0, 8),\
															reg_crgn_hue_gain_x1, GET_BITS(pstParams->hue_x[1], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_02,	reg_crgn_hue_gain_y2, GET_BITS(pstParams->hue_g[2], 0, 8),\
															reg_crgn_hue_gain_x2, GET_BITS(pstParams->hue_x[2], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_03,	reg_crgn_hue_gain_y3, GET_BITS(pstParams->hue_g[3], 0, 8),\
															reg_crgn_hue_gain_x3, GET_BITS(pstParams->hue_x[3], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_04,	reg_crgn_hue_gain_y4, GET_BITS(pstParams->hue_g[4], 0, 8),\
															reg_crgn_hue_gain_x4, GET_BITS(pstParams->hue_x[4], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_05,	reg_crgn_hue_gain_y5, GET_BITS(pstParams->hue_g[5], 0, 8),\
															reg_crgn_hue_gain_x5, GET_BITS(pstParams->hue_x[5], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_06,	reg_crgn_hue_gain_y6, GET_BITS(pstParams->hue_g[6], 0, 8),\
															reg_crgn_hue_gain_x6, GET_BITS(pstParams->hue_x[6], 0, 10));
				PE_CC2_PE1_M23_QWr02(pe1_vsp_crgn_ctrl_07,	reg_crgn_hue_gain_y7, GET_BITS(pstParams->hue_g[7], 0, 8),\
															reg_crgn_hue_gain_x7, GET_BITS(pstParams->hue_x[7], 0, 10));
				/* sat_g,x */
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_08,	reg_crgn_sat_gain_y0, GET_BITS(pstParams->sat_g[0], 0, 8),\
															reg_crgn_sat_gain_x0, GET_BITS(pstParams->sat_x[0], 0, 7),\
															reg_crgn_sat_gain_y1, GET_BITS(pstParams->sat_g[1], 0, 8),\
															reg_crgn_sat_gain_x1, GET_BITS(pstParams->sat_x[1], 0, 7));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_09,	reg_crgn_sat_gain_y2, GET_BITS(pstParams->sat_g[2], 0, 8),\
															reg_crgn_sat_gain_x2, GET_BITS(pstParams->sat_x[2], 0, 7),\
															reg_crgn_sat_gain_y3, GET_BITS(pstParams->sat_g[3], 0, 8),\
															reg_crgn_sat_gain_x3, GET_BITS(pstParams->sat_x[3], 0, 7));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_10,	reg_crgn_sat_gain_y4, GET_BITS(pstParams->sat_g[4], 0, 8),\
															reg_crgn_sat_gain_x4, GET_BITS(pstParams->sat_x[4], 0, 7),\
															reg_crgn_sat_gain_y5, GET_BITS(pstParams->sat_g[5], 0, 8),\
															reg_crgn_sat_gain_x5, GET_BITS(pstParams->sat_x[5], 0, 7));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_11,	reg_crgn_sat_gain_y6, GET_BITS(pstParams->sat_g[6], 0, 8),\
															reg_crgn_sat_gain_x6, GET_BITS(pstParams->sat_x[6], 0, 7),\
															reg_crgn_sat_gain_y7, GET_BITS(pstParams->sat_g[7], 0, 8),\
															reg_crgn_sat_gain_x7, GET_BITS(pstParams->sat_x[7], 0, 7));
				/* val_g,x */
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_12,	reg_crgn_val_gain_y0, GET_BITS(pstParams->val_g[0], 0, 8),\
															reg_crgn_val_gain_x0, GET_BITS(pstParams->val_x[0], 0, 8),\
															reg_crgn_val_gain_y1, GET_BITS(pstParams->val_g[1], 0, 8),\
															reg_crgn_val_gain_x1, GET_BITS(pstParams->val_x[1], 0, 8));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_13,	reg_crgn_val_gain_y2, GET_BITS(pstParams->val_g[2], 0, 8),\
															reg_crgn_val_gain_x2, GET_BITS(pstParams->val_x[2], 0, 8),\
															reg_crgn_val_gain_y3, GET_BITS(pstParams->val_g[3], 0, 8),\
															reg_crgn_val_gain_x3, GET_BITS(pstParams->val_x[3], 0, 8));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_14,	reg_crgn_val_gain_y4, GET_BITS(pstParams->val_g[4], 0, 8),\
															reg_crgn_val_gain_x4, GET_BITS(pstParams->val_x[4], 0, 8),\
															reg_crgn_val_gain_y5, GET_BITS(pstParams->val_g[5], 0, 8),\
															reg_crgn_val_gain_x5, GET_BITS(pstParams->val_x[5], 0, 8));
				PE_CC2_PE1_M23_QWr04(pe1_vsp_crgn_ctrl_15,	reg_crgn_val_gain_y6, GET_BITS(pstParams->val_g[6], 0, 8),\
															reg_crgn_val_gain_x6, GET_BITS(pstParams->val_x[6], 0, 8),\
															reg_crgn_val_gain_y7, GET_BITS(pstParams->val_g[7], 0, 8),\
															reg_crgn_val_gain_x7, GET_BITS(pstParams->val_x[7], 0, 8));
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set dse ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count = 0;
	UINT32 color_out_gain, x_data, y_data;
	UINT32 dse_lut_param[PE_CMG_HW_M23_LUT_STEP];
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_CMG_DSE_CTRL_T *pp=(LX_PE_CMG_DSE_CTRL_T *)pstParams;
			static LX_PE_CMG_DSE_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_CMG_DSE_CTRL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_CMG("duplicated DB : LX_PE_CMG_DSE_CTRL_T\n");
				ret=RET_OK;
				break;
			}
			color_out_gain = (pp->saturation_region_gain==0)? \
				0x1:pp->saturation_region_gain;
			PE_DBG_CMG("[wid:%d] set: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->saturation_cr_mode, pp->saturation_region_gain, \
				pp->region_onoff[0],pp->region_onoff[1],pp->region_onoff[2],pp->region_onoff[3],\
				pp->region_onoff[4],pp->region_onoff[5],pp->region_onoff[6],pp->region_onoff[7],\
				pp->region_onoff[8],pp->region_onoff[9],pp->region_onoff[10],pp->region_onoff[11],\
				pp->region_onoff[12],pp->region_onoff[13],pp->region_onoff[14],pp->region_onoff[15]);
			PE_DBG_CMG("[wid:%d] set: n"\
				"dse_gain_h_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_h_y:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_y:%d,%d,%d,%d,%d,%d,%d,%d\n", \
				pp->win_id,\
				pp->dse_h_x[0],pp->dse_h_x[1],pp->dse_h_x[2],pp->dse_h_x[3],\
				pp->dse_h_x[4],pp->dse_h_x[5],pp->dse_h_x[6],pp->dse_h_x[7],\
				pp->dse_h_y[0],pp->dse_h_y[1],pp->dse_h_y[2],pp->dse_h_y[3],\
				pp->dse_h_y[4],pp->dse_h_y[5],pp->dse_h_y[6],pp->dse_h_y[7],\
				pp->dse_y_x[0],pp->dse_y_x[1],pp->dse_y_x[2],pp->dse_y_x[3],\
				pp->dse_y_x[4],pp->dse_y_x[5],pp->dse_y_x[6],pp->dse_y_x[7],\
				pp->dse_y_y[0],pp->dse_y_y[1],pp->dse_y_y[2],pp->dse_y_y[3],\
				pp->dse_y_y[4],pp->dse_y_y[5],pp->dse_y_y[6],pp->dse_y_y[7]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region0_sel,	GET_BITS(pp->region_onoff[0],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region1_sel,	GET_BITS(pp->region_onoff[1],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region2_sel,	GET_BITS(pp->region_onoff[2],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region3_sel,	GET_BITS(pp->region_onoff[3],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region4_sel,	GET_BITS(pp->region_onoff[4],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region5_sel,	GET_BITS(pp->region_onoff[5],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region6_sel,	GET_BITS(pp->region_onoff[6],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region7_sel,	GET_BITS(pp->region_onoff[7],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region8_sel,	GET_BITS(pp->region_onoff[8],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region9_sel,	GET_BITS(pp->region_onoff[9],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region10_sel,	GET_BITS(pp->region_onoff[10],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region11_sel,	GET_BITS(pp->region_onoff[11],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region12_sel,	GET_BITS(pp->region_onoff[12],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region13_sel,	GET_BITS(pp->region_onoff[13],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region14_sel,	GET_BITS(pp->region_onoff[14],0,1));
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	color_region15_sel,	GET_BITS(pp->region_onoff[15],0,1));
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_00);

				PE_CC_PE1_M23_QWr03(pe1_dse_ctrl_01,	reg_dse_cr_mode_sel,GET_BITS(pp->saturation_cr_mode,0,1),\
														reg_yh_cr_en,		GET_BITS(pp->saturation_cr_mode,0,1),\
														color_region_gain,	GET_BITS(color_out_gain,0,8));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	GET_BITS(pp->dse_y_y[0],0,8),\
															reg_y_region_pt0_x,	GET_BITS(pp->dse_y_x[0],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	GET_BITS(pp->dse_y_y[1],0,8),\
															reg_y_region_pt1_x,	GET_BITS(pp->dse_y_x[1],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	GET_BITS(pp->dse_y_y[2],0,8),\
															reg_y_region_pt2_x,	GET_BITS(pp->dse_y_x[2],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	GET_BITS(pp->dse_y_y[3],0,8),\
															reg_y_region_pt3_x,	GET_BITS(pp->dse_y_x[3],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	GET_BITS(pp->dse_y_y[4],0,8),\
															reg_y_region_pt4_x,	GET_BITS(pp->dse_y_x[4],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	GET_BITS(pp->dse_y_y[5],0,8),\
															reg_y_region_pt5_x,	GET_BITS(pp->dse_y_x[5],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	GET_BITS(pp->dse_y_y[6],0,8),\
															reg_y_region_pt6_x,	GET_BITS(pp->dse_y_x[6],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	GET_BITS(pp->dse_y_y[7],0,8),\
															reg_y_region_pt7_x,	GET_BITS(pp->dse_y_x[7],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	GET_BITS(pp->dse_h_y[0],0,8),\
															reg_h_region_pt0_x,	GET_BITS(pp->dse_h_x[0],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	GET_BITS(pp->dse_h_y[1],0,8),\
															reg_h_region_pt1_x,	GET_BITS(pp->dse_h_x[1],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	GET_BITS(pp->dse_h_y[2],0,8),\
															reg_h_region_pt2_x,	GET_BITS(pp->dse_h_x[2],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	GET_BITS(pp->dse_h_y[3],0,8),\
															reg_h_region_pt3_x,	GET_BITS(pp->dse_h_x[3],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	GET_BITS(pp->dse_h_y[4],0,8),\
															reg_h_region_pt4_x,	GET_BITS(pp->dse_h_x[4],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	GET_BITS(pp->dse_h_y[5],0,8),\
															reg_h_region_pt5_x,	GET_BITS(pp->dse_h_x[5],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	GET_BITS(pp->dse_h_y[6],0,8),\
															reg_h_region_pt6_x,	GET_BITS(pp->dse_h_x[6],0,10));
				PE_CC_PE1_M23_QWr02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	GET_BITS(pp->dse_h_y[7],0,8),\
															reg_h_region_pt7_x,	GET_BITS(pp->dse_h_x[7],0,10));
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_data);
				PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_08);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<PE_CMG_HW_M23_LUT_STEP;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,hif_dse_wdata_y,GET_BITS(pp->sSaturationLUT_y[count],0,10));	//y data
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,hif_dse_wdata_x,GET_BITS(pp->sSaturationLUT_x[count],0,10));//x data
					PE_CC_PE1_M23_WrFL(pe1_dse_ia_data);
					x_data = (UINT32)(pp->sSaturationLUT_x[count])<<16;
					y_data = (UINT32)(pp->sSaturationLUT_y[count]);
					if (y_data>1023)
					{
						y_data=1023;
					}
					dse_lut_param[count] = x_data + y_data;
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				memcpy(_g_cmg_hw_m23_pre_dse_lut, dse_lut_param, sizeof(UINT32)*PE_CMG_HW_M23_LUT_STEP);

				PE_DBG_CMG("\n update dse lut\n");
				PE_DBG_CMG("\n   [ i]    x,    y\n");
				for (count=0;count<(PE_CMG_HW_M23_LUT_MAX-1);count++)
				{
					PE_DBG_CMG("   [%02d] %4d, %4d\n", \
						count, (_g_cmg_hw_m23_pre_dse_lut[count]>>16)&0x3ff, _g_cmg_hw_m23_pre_dse_lut[count]&0x3ff);
				}
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * get dse ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 count = 0;
	//int i = 0;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_CMG_DSE_CTRL_T *pp=(LX_PE_CMG_DSE_CTRL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region0_sel,	pp->region_onoff[0]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region1_sel,	pp->region_onoff[1]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region2_sel,	pp->region_onoff[2]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region3_sel,	pp->region_onoff[3]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region4_sel,	pp->region_onoff[4]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region5_sel,	pp->region_onoff[5]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region6_sel,	pp->region_onoff[6]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region7_sel,	pp->region_onoff[7]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region8_sel,	pp->region_onoff[8]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region9_sel,	pp->region_onoff[9]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region10_sel,	pp->region_onoff[10]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region11_sel,	pp->region_onoff[11]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region12_sel,	pp->region_onoff[12]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region13_sel,	pp->region_onoff[13]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region14_sel,	pp->region_onoff[14]);
				PE_CC_PE1_M23_Rd01(pe1_dse_ctrl_00,	color_region15_sel,	pp->region_onoff[15]);
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_00);

				PE_CC_PE1_M23_QRd03(pe1_dse_ctrl_01,		reg_dse_cr_mode_sel,pp->saturation_cr_mode,\
															reg_yh_cr_en,		pp->saturation_cr_mode,\
															color_region_gain,	pp->saturation_region_gain);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	pp->dse_y_y[0],\
															reg_y_region_pt0_x,	pp->dse_y_x[0]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	pp->dse_y_y[1],\
															reg_y_region_pt1_x,	pp->dse_y_x[1]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	pp->dse_y_y[2],\
															reg_y_region_pt2_x,	pp->dse_y_x[2]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	pp->dse_y_y[3],\
															reg_y_region_pt3_x,	pp->dse_y_x[3]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	pp->dse_y_y[4],\
															reg_y_region_pt4_x,	pp->dse_y_x[4]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	pp->dse_y_y[5],\
															reg_y_region_pt5_x,	pp->dse_y_x[5]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	pp->dse_y_y[6],\
															reg_y_region_pt6_x,	pp->dse_y_x[6]);
				PE_CC_PE1_M23_QRd02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	pp->dse_y_y[7],\
															reg_y_region_pt7_x,	pp->dse_y_x[7]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	pp->dse_h_y[0],\
															reg_h_region_pt0_x,	pp->dse_h_x[0]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	pp->dse_h_y[1],\
															reg_h_region_pt1_x,	pp->dse_h_x[1]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	pp->dse_h_y[2],\
															reg_h_region_pt2_x,	pp->dse_h_x[2]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	pp->dse_h_y[3],\
															reg_h_region_pt3_x,	pp->dse_h_x[3]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	pp->dse_h_y[4],\
															reg_h_region_pt4_x,	pp->dse_h_x[4]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	pp->dse_h_y[5],\
															reg_h_region_pt5_x,	pp->dse_h_x[5]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	pp->dse_h_y[6],\
															reg_h_region_pt6_x,	pp->dse_h_x[6]);
				PE_CC_PE1_M23_QRd02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	pp->dse_h_y[7],\
															reg_h_region_pt7_x,	pp->dse_h_x[7]);
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<PE_CMG_HW_M23_LUT_STEP;count++)
				{
					PE_CC_PE1_M23_QRd02(pe1_dse_ia_data, hif_dse_wdata_y, pp->sSaturationLUT_y[count],\
														 hif_dse_wdata_x, pp->sSaturationLUT_x[count]);//x data
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
			}

			PE_DBG_CMG("[wid:%d] get: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->saturation_cr_mode, pp->saturation_region_gain, \
				pp->region_onoff[0],pp->region_onoff[1],pp->region_onoff[2],pp->region_onoff[3],\
				pp->region_onoff[4],pp->region_onoff[5],pp->region_onoff[6],pp->region_onoff[7],\
				pp->region_onoff[8],pp->region_onoff[9],pp->region_onoff[10],pp->region_onoff[11],\
				pp->region_onoff[12],pp->region_onoff[13],pp->region_onoff[14],pp->region_onoff[15]);
			PE_DBG_CMG("[wid:%d] get: n"\
				"dse_gain_h_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_h_y:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_y:%d,%d,%d,%d,%d,%d,%d,%d\n", \
				pp->win_id,\
				pp->dse_h_x[0],pp->dse_h_x[1],pp->dse_h_x[2],pp->dse_h_x[3],\
				pp->dse_h_x[4],pp->dse_h_x[5],pp->dse_h_x[6],pp->dse_h_x[7],\
				pp->dse_h_y[0],pp->dse_h_y[1],pp->dse_h_y[2],pp->dse_h_y[3],\
				pp->dse_h_y[4],pp->dse_h_y[5],pp->dse_h_y[6],pp->dse_h_y[7],\
				pp->dse_y_x[0],pp->dse_y_x[1],pp->dse_y_x[2],pp->dse_y_x[3],\
				pp->dse_y_x[4],pp->dse_y_x[5],pp->dse_y_x[6],pp->dse_y_x[7],\
				pp->dse_y_y[0],pp->dse_y_y[1],pp->dse_y_y[2],pp->dse_y_y[3],\
				pp->dse_y_y[4],pp->dse_y_y[5],pp->dse_y_y[6],pp->dse_y_y[7]);
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * set target saturation
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_M23_SetTargetSat(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_CMG_HW_M23_SETTINGS_T *pInfo=&_g_pe_cmg_hw_m23_info;
	UINT32 vsp_sat;
	UINT32 org_target_sat = pInfo->org_target_sat;
	UINT32 target_sat;
	do {
		if(PE_KDRV_VER_M23)
		{
			PE_CC2_PE1_M23_QRd01(pe1_vspyc_ctrl_01, saturation, vsp_sat);
			target_sat = (vsp_sat * org_target_sat)>>7; // now 9bit data
			if(target_sat > 255)
				target_sat = 255;
			else
				target_sat &= 0xff; //now 8bit
			if(pInfo->pre_target_sat != target_sat)
			{
				PE_DBG_CMG("vsp_sat 0x%02x org_target_sat 0x%02x target sat 0x%02x -> 0x%02x\n",vsp_sat, org_target_sat, pInfo->pre_target_sat, target_sat);
				PE_CC2_PE1_M23_QWr01(pe1_vspyc_ctrl_01, saturation_target, GET_BITS(target_sat, 0, 8));
				pInfo->pre_target_sat = target_sat;
			}
		}
		else
		{
			PE_DBG_CMG("nothing to do.\n");
		}
	} while (0);
	#endif
	return ret;
}
