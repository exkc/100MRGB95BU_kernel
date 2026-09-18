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



/** @file
 *
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2014.05.14
 *  note		Additional information.
 *
 *  @addtogroup lg115x_hdmi20
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "hdmi20_kapi.h"
#include "hdmi20_cfg.h"
#include "hdmi20_drv.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int 	g_hdmi20_number_of_ports;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
HDMI_FEC_MEM_CFG_T gMemCfgHdmiFec[] =
{
	// [0] O20/E60,M0
	{
		.frame_name = "HDMI_FEC_M0",
		.frame_base = 0x00000000,
		.frame_size = 0x00080000 // 0.5MB
	}
};

LX_MEMCFG_T gMemCfgEsm[] =
{
	// [0] O20/E60,M0
	{
		.name = "ESM_CODE",
		.base = 0x00000000,
		.size = 0x0004B000 // 300KB
	},
	{
		.name = "ESM_DATA",
		.base = 0x00000000,
		.size = 0x00020000 // 128MB
	},
};

HDMI_FEC_MEM_CFG_T *gpHdmiFecMem = NULL;
LX_MEMCFG_T *gpEsmCodeMem = NULL;
LX_MEMCFG_T *gpEsmDataMem = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
	========================================================================================*/
void    HDMI20_InitCfg ( void )
{
	HDMI20_PRINT("[%s:%d] Entered\n", __F__, __L__);

	gpEsmCodeMem	=  &gMemCfgEsm[0];
	gpEsmDataMem	=  &gMemCfgEsm[1];

	if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		g_hdmi20_number_of_ports = HDMI21_NUM_OF_PORTS_E60;
		gpHdmiFecMem	=  &gMemCfgHdmiFec[0];
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		g_hdmi20_number_of_ports = HDMI21_NUM_OF_PORTS_O20;
		gpHdmiFecMem	=  &gMemCfgHdmiFec[0];
	}
	else {
		g_hdmi20_number_of_ports = HDMI20_NUM_OF_RX_PORTS;
	}

	HDMI20_PRINT("[%s:%d] Num of Max HDMI Ports for Selected Chip is [%d]\n", __F__, __L__, g_hdmi20_number_of_ports);
}



/** @} */

