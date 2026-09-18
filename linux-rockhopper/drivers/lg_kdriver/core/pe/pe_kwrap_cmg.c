/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file pe_kwrap_cmg.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- color management
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
		
#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
		
#include "pe_def.h"

#include "pe_cmg.h"

#include "pe_kwrap.h"
#include "pe_kwrap_def.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
/* cmg region(ver0) */
const LX_PE_CMG_REGION_T g_pe_kwrap_p_cmg_rgn_v0[LX_PE_CMG_REGION_NUM] = {
	{0,	PE_KWRAP_CMG_RGN_COL_WHT, \
		{0, 35, 100, 150, 200, 250, 300, 360}, \
		{127, 127, 127, 127, 127, 127, 127, 127}, \
		{0, 5, 10, 15, 17, 21, 24, 27}, \
		{127, 127, 127, 127, 110, 70, 30, 0}, \
		{60, 100, 120, 140, 160, 190, 250, 255}, \
		{0, 45, 65, 80, 100, 80, 50, 20}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_WTB, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 1}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLK, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_SKN, \
		{359, 370, 380, 390, 395, 400, 410, 415}, \
		{0, 95, 120, 127, 127, 127, 80, 0}, \
		{30, 40, 50, 60, 90, 95, 98, 100}, \
		{0, 50, 95, 127, 127, 127, 127, 127}, \
		{15, 35, 55, 100, 170, 210, 230, 255}, \
		{0, 70, 127, 127, 127, 60, 30, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_GRN, \
		{60, 68, 75, 80, 120, 130, 140, 150}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{30, 35, 40, 50, 70, 80, 90, 100}, \
		{0, 35, 70, 127, 127, 127, 127, 127}, \
		{30, 50, 80, 100, 144, 180, 216, 255}, \
		{0, 80, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLU, \
		{155, 165, 175, 190, 240, 250, 260, 275}, \
		{0, 75, 127, 127, 127, 127, 100, 0}, \
		{0, 15, 30, 40, 80, 90, 98, 100}, \
		{0, 50, 100, 127, 127, 127, 127, 127}, \
		{0, 50, 70, 90, 100, 140, 245, 255}, \
		{0, 50, 75, 110, 127, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_RED, \
		{320, 325, 330, 335, 363, 366, 372, 375}, \
		{0, 45, 90, 127, 127, 127, 90, 0}, \
		{35, 45, 55, 60, 75, 80, 90, 100}, \
		{0, 50, 100, 127, 127, 127, 127, 127}, \
		{35, 60, 90, 120, 150, 180, 210, 230}, \
		{0, 70, 110, 127, 127, 100, 40, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_YEL, \
		{41, 50, 55, 60, 65, 70, 75, 80}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{35, 40, 45, 54, 65, 75, 85, 100}, \
		{0, 35, 70, 127, 127, 127, 127, 127}, \
		{20, 50, 75, 108, 144, 180, 216, 255}, \
		{0, 70, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_MGT, \
		{275, 280, 285, 290, 300, 305, 310, 315}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{0, 25, 40, 50, 60, 70, 90, 100}, \
		{0, 80, 127, 127, 127, 127, 127, 0}, \
		{30, 55, 80, 108, 144, 180, 216, 255}, \
		{0, 60, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_CYN, \
		{150, 158, 167, 175, 184, 192, 201, 210}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R10, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R11, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R12, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R13, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R14, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R15, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};
/* cmg region(ver1) */
const LX_PE_CMG_REGION_T g_pe_kwrap_p_cmg_rgn_v1[LX_PE_CMG_REGION_NUM] = {
	{0,	PE_KWRAP_CMG_RGN_COL_WHT, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	PE_KWRAP_CMG_RGN_COL_WTB, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLK, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	PE_KWRAP_CMG_RGN_COL_SKN, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	PE_KWRAP_CMG_RGN_COL_GRN, \
		{90, 98, 107, 115, 124, 132, 141, 150}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLU, \
		{210, 218, 227, 235, 244, 252, 261, 270}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_RED, \
		{330, 338, 347, 355, 364, 372, 381, 390}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 115, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_YEL, \
		{30, 38, 47, 55, 64, 72, 81, 90}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_MGT, \
		{270, 278, 287, 295, 304, 312, 321, 330}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_CYN, \
		{150, 158, 167, 175, 184, 192, 201, 210}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R10, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R11, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R12, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R13, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R14, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R15, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};
/* cmg region control */
const LX_PE_CMG_REGION_CTRL_T g_pe_kwrap_p_cmg_rgn_ctrl[LX_PE_CMG_REGION_NUM] = {
	{0,	PE_KWRAP_CMG_RGN_COL_WHT,	{0, 0, 0, 0, 25, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_WTB,	{0, 0, 0, 0, 0, 0}, 			0}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLK,	{0, 0, 0, 0, 0, 0}, 			0}, \
	{0,	PE_KWRAP_CMG_RGN_COL_SKN,	{-9, 0, 0, -15, -18, 18}, 		170}, \
	{0,	PE_KWRAP_CMG_RGN_COL_GRN,	{15, 10, -10, 23, -15, -25}, 	255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_BLU,	{0, 25, 0, -14, 19, -19}, 		255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_RED,	{-10, 15, 0, -5, -5, 10}, 		255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_YEL,	{0, 5, 0, 0, -10, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_MGT,	{0, 30, -5, 0, 15, 5}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_CYN,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R10,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R11,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R12,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R13,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R14,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	PE_KWRAP_CMG_RGN_COL_R15,	{0, 0, 0, 0, 0, 0}, 			255}
	};


/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

#define _KWRAP_PE_CMG_
/**
 * set color enhance enable
 * - use input struct LX_PE_CMG_ENABLE_T for H15, M14BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenEnable(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_ENABLE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_ENABLE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_ENABLE_T *)param;
			PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d, en:%d\n", pp->win_id, pp->enable);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_ENABLE_T, CMG);
			#endif
			ret = PE_CMG_SetCenEnable(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance enable
 * - use input struct LX_PE_CMG_ENABLE_T for H15, M14BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenEnable(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenEnable((LX_PE_CMG_ENABLE_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set color enhance region enable
 * - use input struct LX_PE_CMG_REGION_ENABLE_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenRgnEnable(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_REGION_ENABLE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		__attribute__((unused)) static LX_PE_CMG_REGION_ENABLE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_REGION_ENABLE_T *)param;
			PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d\n", pp->win_id);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			//PE_KWRAP_CHECK_WINID(LX_PE_CMG_REGION_ENABLE_T, CMG);
			#endif
			ret = PE_CMG_SetCenRegionEnable(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance region enable
 * - use input struct LX_PE_CMG_REGION_ENABLE_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenRgnEnable(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenRegionEnable((LX_PE_CMG_REGION_ENABLE_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance region default settings
 *	- input data : [31:16] see PE_KWRAP_CMG_RGN_TYPE,
 *					[15:0] 0~LX_PE_CMG_REGION_MAX
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenRgnDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 rgn_num=0, rgn_ver=0;
	const LX_PE_CMG_REGION_T *p_val=NULL;
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		rgn_num = (PE_GET_BITS(param->data, 0, 16)<LX_PE_CMG_REGION_NUM)? \
			PE_GET_BITS(param->data, 0, 16):0;
		rgn_ver = PE_GET_BITS(param->data, 16, 16);
		p_val = (rgn_ver==PE_KWRAP_CMG_RGN_V00)? \
			g_pe_kwrap_p_cmg_rgn_v0:g_pe_kwrap_p_cmg_rgn_v1;
		memcpy(param->st_data, &(p_val[rgn_num]), sizeof(LX_PE_CMG_REGION_T));
	}while (0);
	return ret;
}
/**
 * set color enhance region by specific value
 *	- input data : see PE_KWRAP_CMG_RGN_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenRgnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 i=0, j=0;
	LX_PE_CMG_REGION_T ctrl;
	PE_KWRAP_CTRL_T rgn_param;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(CMG, \
			"wid:%d, data:%d\n", param->wid, param->data);
		for (i=0;i<LX_PE_CMG_REGION_NUM;i++)
		{
			rgn_param.data = ((param->data&0xffff)<<16)|(i&0xffff);
			rgn_param.st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetCenRgnDefaultSettings(&rgn_param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetCenRgnDefaultSettings() error.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
			LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			for (j=0;j<LX_PE_CMG_TBLPOINT;j++)
			{
				ctrl.hue_x[j]=PE_KWRAP_CONV_DEGREE_TO_10BIT(ctrl.hue_x[j]);
				ctrl.sat_x[j]=PE_KWRAP_CONV_PERCENT_TO_8BIT(ctrl.sat_x[j]);
			}
			ret = KWRAP_PE_SetCenRgnParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetCenRgnParam() error.\n", __F__, __L__);
		}
	}while (0);
	return ret;
}
/**
 * set color enhance region parameter
 * - use input struct LX_PE_CMG_REGION_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenRgnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_REGION_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0, i=0, num=0;
		static UINT32 chk[PE_KWRAP_CEN_RGN_NUM] = \
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		static LX_PE_CMG_REGION_T prev[PE_KWRAP_CEN_RGN_NUM][LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_REGION_T *)param;
			PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d, rgn:%d\n", pp->win_id, pp->region_num);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			num = pp->region_num;
			PE_CHECK_CODE(num>=PE_KWRAP_CEN_RGN_NUM, ret=RET_ERROR;break, \
				"[%s,%d]region_num(%d) is over.\n", __F__, __L__, num);
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				prev[num][i].win_id=pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk[num], __F__, __L__);
			size = sizeof(LX_PE_CMG_REGION_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk[num], (void *)prev[num], (void *)pp, size);
			PE_KWRAP_SHOW_CHK(CMG, wid, chk[num]);
			//PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			//pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_CMG_SetCenRegion(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance region parameter
 * - use input struct LX_PE_CMG_REGION_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenRgnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenRegion((LX_PE_CMG_REGION_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance region gain default settings
 *	- input data : 0~LX_PE_CMG_REGION_MAX
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenRgnGainDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 rgn_num = 0;
	const LX_PE_CMG_REGION_CTRL_T *p_val=NULL;
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		rgn_num = (param->data<LX_PE_CMG_REGION_NUM)? param->data:0;
		p_val = g_pe_kwrap_p_cmg_rgn_ctrl;
		memcpy(param->st_data, &(p_val[rgn_num]), sizeof(LX_PE_CMG_REGION_CTRL_T));
	}while (0);
	return ret;
}
/**
 * set color enhance region gain by specific value
 *	- input data : see PE_KWRAP_CMG_CTRL_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenRgnGainCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 i=0;
	LX_PE_CMG_REGION_CTRL_T ctrl;
	PE_KWRAP_CTRL_T rgn_param;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(CMG, \
			"wid:%d, data:%d\n", param->wid, param->data);
		for (i=0;i<LX_PE_CMG_REGION_NUM;i++)
		{
			rgn_param.data = i;
			rgn_param.st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetCenRgnGainDefaultSettings(&rgn_param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetCenRgnGainDefaultSettings() error.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			if (param->data==PE_KWRAP_CMG_CTRL_LOW)
				ctrl.master_gain = (ctrl.master_gain>>1);
			else if (param->data==PE_KWRAP_CMG_CTRL_OFF)
				ctrl.master_gain = 0;
			ret = KWRAP_PE_SetCenRgnGainParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetCenRgnGainParam() error.\n", __F__, __L__);
		}
	}while (0);
	return ret;
}
/**
 * set color enhance region gain parameter
 * - use input struct LX_PE_CMG_REGION_CTRL_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenRgnGainParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_REGION_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0, i=0, num=0;
		static UINT32 chk[PE_KWRAP_CEN_RGN_NUM] = \
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		static LX_PE_CMG_REGION_CTRL_T prev[PE_KWRAP_CEN_RGN_NUM][LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_REGION_CTRL_T *)param;
			/* too many print */
			/*PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d, rgn:%d, delt:%d, %d, %d, %d, %d, %d, m_g:%d\n", \
				pp->win_id, pp->region_num, pp->region_delta[0], \
				pp->region_delta[1], pp->region_delta[2], \
				pp->region_delta[3], pp->region_delta[4], \
				pp->region_delta[5], pp->master_gain);*/
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			num = pp->region_num;
			PE_CHECK_CODE(num>=PE_KWRAP_CEN_RGN_NUM, ret=RET_ERROR;break, \
				"[%s,%d]region_num(%d) is over.\n", __F__, __L__, num);
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				prev[num][i].win_id=pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk[num], __F__, __L__);
			size = sizeof(LX_PE_CMG_REGION_CTRL_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk[num], (void *)prev[num], (void *)pp, size);
			/*PE_KWRAP_SHOW_CHK(CMG, wid, chk[num]);*//* too many print */
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_CMG_SetCenRegionCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance region gain parameter
 * - use input struct LX_PE_CMG_REGION_CTRL_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenRgnGainParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenRegionCtrl((LX_PE_CMG_REGION_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set color enhance global gain parameter
 * - use input struct LX_PE_CMG_GLOBAL_CTRL_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenGblGainParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_GLOBAL_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_GLOBAL_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_GLOBAL_CTRL_T *)param;
			PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d, gl_delt:%d, %d, %d, %d, %d, %d\n", pp->win_id, \
				pp->global_delta[0], pp->global_delta[1], pp->global_delta[2], \
				pp->global_delta[3], pp->global_delta[4], pp->global_delta[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_GLOBAL_CTRL_T, CMG);
			#endif
			ret = PE_CMG_SetCenGlobalCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance global gain parameter
 * - use input struct LX_PE_CMG_GLOBAL_CTRL_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenGblGainParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenGlobalCtrl((LX_PE_CMG_GLOBAL_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set color enhance color parameter
 * - use input struct LX_PE_CMG_COLOR_CTRL_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetCenColorParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_COLOR_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0, i=0;
		static UINT32 chk = 0x0;
		static LX_PE_CMG_COLOR_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_COLOR_CTRL_T *)param;
			/* too many print */
			//PE_KWRAP_DBG_PRINT(CMG, "wid:%d, sat:%d\n", pp->win_id, pp->saturation);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				prev[i].win_id=pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, NULL, 0);
			size = sizeof(LX_PE_CMG_COLOR_CTRL_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)pp, size);
			/* too many print */
			//PE_KWRAP_SHOW_CHK(CMG, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_CMG_SetCenColorCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get color enhance color parameter
 * - use input struct LX_PE_CMG_COLOR_CTRL_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCenColorParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetCenColorCtrl((LX_PE_CMG_COLOR_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set clear white parameter
 * - use input struct LX_PE_CMG_CW_CTRL_T for H15, M14BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetClearWhiteParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_CMG_CW_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_CW_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_CW_CTRL_T *)param;
			PE_KWRAP_DBG_PRINT(CMG, \
				"wid:%d, en:%d, yc:%d, x:%d,%d,%d,%d,%d\n"\
				" y:%d,%d,%d,%d,%d, sel:0x%x, g:%d\n", \
				pp->win_id, pp->cw_en, pp->gain_sel, pp->gain_x[0], \
				pp->gain_x[1], pp->gain_x[2], pp->gain_x[3], \
				pp->gain_x[4], pp->gain_y[0], pp->gain_y[1], \
				pp->gain_y[2], pp->gain_y[3], pp->gain_y[4], \
				pp->region_sel, pp->region_gain);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_CW_CTRL_T, CMG);
			#endif
			ret = PE_CMG_SetClearWhiteCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get clear white parameter
 * - use input struct LX_PE_CMG_CW_CTRL_T for H15, M14BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetClearWhiteParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetClearWhiteCtrl((LX_PE_CMG_CW_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set clear white gain parameter
 * - use input struct LX_PE_CMG_CW_GAIN_CTRL_T for H15, M14BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetClearWhiteGainParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19)
	{
		LX_PE_CMG_CW_GAIN_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0, i=0;
		static UINT32 chk = 0x0;
		static LX_PE_CMG_CW_GAIN_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_CW_GAIN_CTRL_T *)param;
			/* too many print */
			/*PE_KWRAP_DBG_PRINT(CMG, "wid:%d, rgb_g:%d, %d, %d\n", \
				pp->win_id, pp->r_gain, pp->r_gain, pp->r_gain);*/
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				prev[i].win_id=pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, NULL, 0);
			size = sizeof(LX_PE_CMG_CW_GAIN_CTRL_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)pp, size);
			/* too many print */
			//PE_KWRAP_SHOW_CHK(CMG, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_CMG_SetClearWhiteGainCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get clear white gain parameter
 * - use input struct LX_PE_CMG_CW_GAIN_CTRL_T for H15, M14BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetClearWhiteGainParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_CMG_GetClearWhiteGainCtrl((LX_PE_CMG_CW_GAIN_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set saturation gain LUT
 * - use input struct LX_PE_CMG_SAT_GAIN_LUT_T for O18, M17CX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSaturationGainLUT(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19)
	{
		LX_PE_CMG_SAT_GAIN_LUT_T *pp = NULL;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size = 0, wid = 0, i = 0;
		static UINT32 chk = 0x0;
		static LX_PE_CMG_SAT_GAIN_LUT_T prev[LX_PE_WIN_NUM];
#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_SAT_GAIN_LUT_T *)param;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			for (i = 0; i < LX_PE_WIN_ALL; i++)
			{
				prev[i].win_id = pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, NULL, 0);
			size = sizeof(LX_PE_CMG_CW_GAIN_CTRL_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)pp, size);
			PE_CHECK_ACTION(wid > LX_PE_WIN_ALL, ret = RET_OK; break);
			pp->win_id = (LX_PE_WIN_ID)wid;
#endif
			ret = PE_CMG_SetSaturationGainLUT(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		} while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get saturation gain LUT
 * - use input struct LX_PE_CMG_SAT_GAIN_LUT_T for O18, M17CX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSaturationGainLUT(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18 || PE_KDRV_VER_M17CX)
	{
		ret = PE_CMG_GetSaturationGainLUT((LX_PE_CMG_SAT_GAIN_LUT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set ext/inner pattern
 * - use input struct LX_PE_CMG_EXT_PATTERN_INFO_T for M16P3, O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetExtInnerPattern(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 || PE_KDRV_VER_M19)
	{
		LX_PE_CMG_EXT_PATTERN_INFO_T *pp = NULL;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size = 0, wid = 0, i = 0;
		static UINT32 chk = 0x0;
		static LX_PE_CMG_EXT_PATTERN_INFO_T prev[LX_PE_WIN_NUM];
#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_EXT_PATTERN_INFO_T *)param;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			for (i = 0; i < LX_PE_WIN_ALL; i++)
			{
				prev[i].win_id = pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, NULL, 0);
			size = sizeof(LX_PE_CMG_EXT_PATTERN_INFO_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)pp, size);
			PE_CHECK_ACTION(wid > LX_PE_WIN_ALL, ret = RET_OK; break);
			pp->win_id = (LX_PE_WIN_ID)wid;
#endif
			ret = PE_CMG_SetExtInnerPattern(param);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		} while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set clear white table parameter
 * - use input struct LX_PE_CMG_CW_TABLE_CTRL_T for o20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetClearWhiteTableParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_CMG_CW_TABLE_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_CW_TABLE_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_CW_TABLE_CTRL_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_CW_TABLE_CTRL_T, CMG);
			#endif
			ret = PE_CMG_SetClearWhiteTableCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set clear white table parameter
 * - use input struct LX_PE_CMG_CW_TABLE_CTRL_T for o20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetVspccParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_CMG_VSPCC_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_VSPCC_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_VSPCC_CTRL_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_VSPCC_CTRL_T, CMG);
			#endif
			ret = PE_CMG_SetVspccCtrl((void *)pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dse parameter
 * - use input struct LX_PE_CMG_DSE_CTRL_T for o20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDseParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(CMG);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_CMG_DSE_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_CMG_DSE_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CMG_DSE_CTRL_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_CMG_DSE_CTRL_T, CMG);
			#endif
			ret = PE_CMG_SetDseCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}


/**
 * get dse parameter
 * - use input struct LX_PE_CMG_DSE_CTRL_T for o20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDseParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		ret = PE_CMG_GetDseCtrl((LX_PE_CMG_DSE_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

