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

/** @file pe_proc_dbg.h
 *
 *  application test header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

#ifndef	_PE_PROC_DBG_H_
#define	_PE_PROC_DBG_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

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
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/
extern int pe_proc_dbg_wrap_help(char* buffer);
extern void pe_proc_dbg_wrap_func(char *command);
extern void pe_proc_dbg_kdrv_help(void);
extern void pe_proc_dbg_kdrv_func(char *command);
extern int pe_proc_show_status(struct seq_file *m);
extern int pe_proc_dbg_printmisctable(int func_num,int *cmd,int size,struct seq_file *m);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_PROC_DBG_H_ */
