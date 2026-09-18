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
 * de sync 
 *
 * author     
 * version    1.0
 * date       
 * note       
 *
 * @addtogroup 
 * @{
 */

#ifndef _DE_SYNC_h
#define _DE_SYNC_h
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define MAX_CB_NUM 8
#define MAX_CB_STR 64

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum {
	SYNC_WAIT_JPG,
	SYNC_WAIT_USB,
	SYNC_WAIT_WEL,
	SYNC_WAIT_WER,
	SYNC_WAIT_DELAY,
	SYNC_WAIT_MUTEOFF,
	SYNC_WAIT_VIDEO_DELAY,
	SYNC_WAIT_VSYNC
} DE_SYNC_WAIT_TYPE_T;

typedef struct {
	int (*f)(void);
	char s[MAX_CB_STR];
} DE_SYNC_CB_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int de_sync_init(void);
int de_sync_free(void);
int de_sync_wait(DE_SYNC_WAIT_TYPE_T type);
int de_sync_wait_with_window(unsigned int wid, DE_SYNC_WAIT_TYPE_T type);
int de_sync_signal(DE_SYNC_WAIT_TYPE_T type);
int de_sync_register(BOOLEAN flag, int (*func)(void), char *str);
int de_srcsync_register(BOOLEAN flag, int (*func)(void), char *str);
int de_sync_display(void);
int de_sync_vsync_enable(BOOLEAN enable);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */



