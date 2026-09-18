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


/** @file vpq_hwrap.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_VPQ_HWRAP_H_
#define	_VPQ_HWRAP_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define VPQ_HWRAP_CHECK_CODE(__checker, __if_action, fmt, args...)   \
	if (__checker){PE_PRINT_ERROR(fmt, ##args);__if_action;}

#define	VPQ_HWRAP_CHECK_PRINT(__checker, fmt, args...)		\
	if (__checker){printk(fmt, ##args);}

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/
extern int vpq_hwrap_setforcepattern(int type);
extern int vpq_hwrap_getforcepattern(void);
extern int vpq_hwrap_initialize(unsigned int resume_mode);
extern int vpq_hwrap_uninitialize(void);
extern int vpq_hwrap_isinitialized(void);
extern int vpq_hwrap_setbypassblocks(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getbypassblocks(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_setpqmodeinfo(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getcurpqmodeinfo(unsigned int wid, unsigned int index);
extern int vpq_hwrap_getpqmodeinfo(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_setextpattern(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getextpattern(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getpicdisplayinfo(void *p_param);
extern int vpq_hwrap_setpicdisplayinfo(void *p_param);
extern int vpq_hwrap_setdefaultsettings(void *param);
extern int vpq_hwrap_setinputcscparam(void *p_param);
#endif /* _VPQ_HWRAP_H_ */
