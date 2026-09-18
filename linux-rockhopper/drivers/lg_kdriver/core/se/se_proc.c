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

/** @file
 *
 *  proc interface header for se device.
 *
 *  @author     stan.kim@lge.com
 *  @version    2.0
 *  @date       2012.5
 *  @note       Additional information.
 *
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "se_drv_impl.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PROC_MAX_MSG_LENGTH		2048

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_CMD 	= 1,
	PROC_ID_RES 	= 2,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
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
#ifndef _SE_STANDALONE_
 static OS_PROC_DESC_TABLE_T	_g_se_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , 	OS_PROC_FLAG_READ },
	{ "cmd",		PROC_ID_CMD,		OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 	0 }
};

static char _gCmd[256] = "";
#endif	// _SE_STANDALONE_

/*========================================================================================
	Implementation Group
========================================================================================*/

#ifndef _SE_STANDALONE_

/*
 * read_proc implementation of se
 *
*/
static int _SE_PROC_ReadFunc(uint32_t procId, char *pBuffer)
{
	int ret = 0;

	/* TODO: add your proc_write implementation */
	switch (procId) {
		case PROC_ID_AUTHOR:
			ret = sprintf(pBuffer, "%s\n", "stan.kim (stan.kim@lge.com)");
			break;

		case PROC_ID_CMD :
			if (SE_SendMsgToUser(_gCmd, strlen(_gCmd)+1, pBuffer, PROC_MAX_MSG_LENGTH)==0) {
				ret = strlen(pBuffer);
				ret = (ret < PROC_MAX_MSG_LENGTH ? ret : PROC_MAX_MSG_LENGTH);
			}
			break;

		default:
			ret = sprintf(pBuffer, "%s(%d)\n", "unimplemented read proc", procId);
			break;
	}

	return ret;
}

/*
 * write_proc implementation of se
 *
*/
static int _SE_PROC_WriteFunc(uint32_t procId, char *pCommand)
{
	/* TODO: add your proc_write implementation */
	switch (procId) {
		case PROC_ID_CMD :
			snprintf(_gCmd, sizeof(_gCmd), "p-%s", pCommand);
			_gCmd[sizeof(_gCmd)-1] = '\0';
			break;

		default:
			break;
	}

	return strlen(pCommand);
}

/* initialize proc utility for se
 *
 * @see GFX_Init
*/
void SE_PROC_Init(void)
{
	OS_PROC_CreateEntryEx(SE_MODULE, _g_se_device_proc_table, _SE_PROC_ReadFunc, _SE_PROC_WriteFunc);
}

/* cleanup proc utility for se
 *
 * @see GFX_Cleanup
*/
void SE_PROC_Cleanup(void)
{
	OS_PROC_RemoveEntry(SE_MODULE);
}

#else	// _SE_STANDALONE_

void SE_PROC_Init(void)
{
	;
}

void SE_PROC_Cleanup(void)
{
	;
}

#endif	// _SE_STANDALONE_

/** @} */

