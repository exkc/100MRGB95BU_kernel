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
 *  main configuration file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_cfg.h"
#include "os_util.h"
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif


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

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
	
LX_MEMCFG_T gPeMem[10];//[0]:fw_dnn, [1~9]:none

PE_MEM_CFG_T gMemCfgPe[] =
{
	//[00] O20,E60
	{
		{
			{	"pe_db0",	0x00000000,	0x00200000},//2MB, NR,SCL,SR
			{	"pe_db1",	0x00000000,	0x00100000},//1MB, HDR
			{	"pe_db2",	0x00000000,	0x00000000},
			{	"pe_db3",	0x00000000,	0x00000000}
		},
	},
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void PE_InitCfg ( void )
{
#ifdef INCLUDE_KDRV_DE
	if ( lx_chip_rev() >= LX_CHIP_REV(O22,A0) ) {
		gPeMem[0].name = g_fw_dnn.name;
		gPeMem[0].base = g_fw_dnn.base;
		gPeMem[0].size = g_fw_dnn.size;
	}
	//PE_PRINT_NOTI(format,args...)("teg info copy done\n");
#endif
}

/** @} */


