/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file apr_cmn.c
 *
 *  Common functions for APR module usage
 *	- Like sorting or finding max of n numbers etc
 *	- Result of refactoring of apr_core.c
 *
 *	@author		harish.singh
 *	@version	1.0
 *	@note
 *	@date		2015.06.10
 *	@see
 */


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "os_util.h"

#include "apr_def.h"
#include "apr_core.h"
#include "apr_hal.h"
#include "apr_osd.h"
#include "apr_ldf.h"
#include "apr_hfd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define APR_MSG			if(_g_apr_trace == LX_APR_CMD_LOG) APR_PRINT

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_APR_CMD _g_apr_trace ;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int APR_GetUSecTimerVal(UINT32 *tv);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/


static int APR_GetUSecTimerVal(UINT32 *tv)
{
	int ret = RET_OK;
	ret = APR_HAL_GetUSecTimerVal(tv);
	return ret;
}

int APR_CheckTime(char *fn_str,APR_INFO_T *i_pstAprInfo, APR_GET_TIME_T location, APR_TIME_T pos)
{
	int ret = RET_OK;
	static APR_TIME_INFO_T time_info;
	APR_CFG_T *pCfg = &i_pstAprInfo->cfg;
	UINT32 time_diff;
	UINT32 usec;

	do {
		switch(pos)
		{
			case APR_GET_START :
				APR_GetUSecTimerVal(&usec);
				time_info.tick_start_time[location] = usec;
				break;
			default :
			case APR_GET_END :
				APR_GetUSecTimerVal(&usec);
				time_info.tick_end_time[location] = usec;
				if(time_info.tick_end_time[location] >= time_info.tick_start_time[location])
					time_diff = time_info.tick_end_time[location] - time_info.tick_start_time[location];
				else
					time_diff = time_info.tick_start_time[location] + (0xFFFFFFFF - time_info.tick_end_time[location]);
				time_diff = (time_diff==0)?1:time_diff;
				if(location == APR_GET_TIME_CAP)
					pCfg->time.capture = time_diff;
				else if(location == APR_GET_TIME_MAT)
					pCfg->time.measure = time_diff;
				else if(location == APR_GET_TIME_DRW)
					pCfg->time.draw    = time_diff;
				else if(location == APR_GET_TIME_FD3)
					pCfg->time.fd3     = time_diff;
				if(pCfg->cap.enb == LX_APR_CAP_TIME) APR_MSG("%s :	%d usec  elapsed\n", fn_str, time_diff);
				break;
		}
	} while(0);

	return ret;
}

/**
 * Find Max of given numbers
 *
 * Calculate maximum of g_diff/r_diff/b_diff input data and return to diff_max
 *
 * @return  Fn status
 * @remarks  No Remark
 * @see
*/

int APR_GetMax3(UINT32 *g_diff, UINT32 *b_diff, UINT32 *r_diff, UINT32 *diff_max)
{
    int ret = RET_OK;

    if(*g_diff>=*b_diff)
    {
    	if(*g_diff>=*r_diff)
        	*diff_max = *g_diff;
        else
			*diff_max = *r_diff;
    }
    else
    {
    	if(*b_diff>=*r_diff)
        	*diff_max = *b_diff;
        else
			*diff_max = *r_diff;
    }

	return ret;
}

void APR_FormatPatternToString(LX_APR_FORMAT i_eFmt,APR_OSD_PATTERN *i_ePtn,char **io_pPatternString1,char **io_pPatternString2)
{
	if(NULL == i_ePtn || NULL == io_pPatternString1 || NULL == io_pPatternString2){
		APR_MSG("    NULL Input Parameters\n");
		return;
	}

	switch (i_eFmt)
    {
	    case LX_APR_FMT_2D_2D :
	    	*i_ePtn = APR_OSD_2D;
		    *io_pPatternString1  = "2d";
		    *io_pPatternString2  = "2d";
		    break;
	    case LX_APR_FMT_3D_3D :
	    	*i_ePtn = APR_OSD_MAX;
		    *io_pPatternString1  = "3d";
		    *io_pPatternString2  = "3d";
		    break;
		case LX_APR_FMT_3D_SS :
    		*i_ePtn = APR_OSD_SS;
    		*io_pPatternString1  = "side by side";
    		*io_pPatternString2  = "ss";
    		break;
	    case LX_APR_FMT_3D_TB :
	    	*i_ePtn = APR_OSD_TB;
	    	*io_pPatternString1  = "top and bottom";
	    	*io_pPatternString2  = "tb";
	    	break;
    	case LX_APR_FMT_3D_CB :
	    	*i_ePtn = APR_OSD_CB;
	    	*io_pPatternString1  = "checker board";
	    	*io_pPatternString2  = "cb";
	    	break;
    	case LX_APR_FMT_3D_CC :
	    	*i_ePtn = APR_OSD_CC;
	    	*io_pPatternString1  = "column by column";
	    	*io_pPatternString2  = "cc";
	    	break;
    	case LX_APR_FMT_3D_LL :
	    	*i_ePtn = APR_OSD_LL;
    		*io_pPatternString1  = "line by line";
    		*io_pPatternString2  = "ll";
	    	break;
    	case LX_APR_FMT_UNKNOWN :
     	default :
	    	*i_ePtn = APR_OSD_NONE;
	    	*io_pPatternString1  = "unknown";
	    	*io_pPatternString2  = "un";
		    break;
    }
}

/**
*
*/
void APR_ConvertOutToString(LX_PE_OUT_TYPE i_ePEOutType,char **io_pPETypeToString)
{
	switch (i_ePEOutType)
	{
		case LX_PE_OUT_3D_2D :
	    	*io_pPETypeToString  = "3D-2D";
			break;
		case LX_PE_OUT_2D_3D :
	    	*io_pPETypeToString  = "2D-3D";
			break;
		case LX_PE_OUT_UD :
	    	*io_pPETypeToString  = "UD";
			break;
		case LX_PE_OUT_TB :
	    	*io_pPETypeToString  = "SINGLE_TB";
			break;
		case LX_PE_OUT_SS :
	    	*io_pPETypeToString  = "SINGLE_SS";
			break;
		case LX_PE_OUT_FS :
	    	*io_pPETypeToString  = "SINGLE_FS";
			break;
		case LX_PE_OUT_LA :
	    	*io_pPETypeToString  = "SINGLE_LA";
			break;
		case LX_PE_OUT_DUAL_TB :
	    	*io_pPETypeToString  = "DUAL_TB";
			break;
		case LX_PE_OUT_DUAL_SS :
	    	*io_pPETypeToString  = "DUAL_SS";
			break;
		case LX_PE_OUT_DUAL_FULL :
	    	*io_pPETypeToString  = "DUAL_FULL";
			break;
		case LX_PE_OUT_PIP :
	    	*io_pPETypeToString  = "PIP";
			break;
		case LX_PE_OUT_2D :
		default :
	    	*io_pPETypeToString  = "2D";
			break;
	}
}
