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
 *  driver interface header for se device. ( used only within kdriver )
 *  this file lists the type, function lists exported to the other module outside SE.
 *
 *  @author     stan.kim@lge.com
 *  @version    2.0
 *  @date       2012.5
 *  @note       Additional information.
 *
 *	@{
 */

#ifndef	_SE_DRV_H_
#define	_SE_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define SE_MODULE	"se"
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void SE_PreInit(void);
extern int SE_Init(void);
extern void SE_Cleanup(void);

extern void SE_PROC_Init(void);
extern void SE_PROC_Cleanup(void);

extern int SE_SendMsgToUser(void *pMsg, int msgLength, void *pRetMsg, int retMsgLength);


#define SE_TBL_ID_VDEC 	(0x11)
#define SE_TBL_ID_AUD0 	(0x12)
#define SE_TBL_ID_AUD1 	(0x13)
extern int se_trusted_binary_loading(unsigned int id, void* dest, void* src, unsigned int size);

extern int lgkree_req_secure_fwload(uint32_t id, void* dest, void* src, uint32_t size);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _SE_DRV_H_ */

/** @} */
