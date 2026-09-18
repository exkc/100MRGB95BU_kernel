/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
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
#ifndef _AUDIO_LOGM_H_
#define _AUDIO_LOGM_H_

#include <linux/kernel.h>

#include "logm_kapi.h"

enum
{
    log_level_error = LX_LOGM_LEVEL_ERROR,
    log_level_warning = LX_LOGM_LEVEL_WARNING,
    log_level_noti = LX_LOGM_LEVEL_NOTI,
    log_level_info = LX_LOGM_LEVEL_INFO,
    log_level_debug = LX_LOGM_LEVEL_DEBUG,
    log_level_trace = LX_LOGM_LEVEL_TRACE,
};

#define logm_define(name,level) \
	int __logm_fd_##name = -1; \
	EXPORT_SYMBOL(__logm_fd_##name); \
	static char *__logm_name_##name = #name; \
	void __logm_init_logm_##name (void); \
	void __logm_init_logm_##name (void) \
	{ \
		__logm_fd_##name = LOGM_ObjRegister (__logm_name_##name); \
		LOGM_ObjMaskAdd (__logm_fd_##name, (1<<(level+1))-1); \
	} \
	EXPORT_SYMBOL(__logm_init_logm_##name);


#define logm_error(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T) log_level_error, \
			format, ##args); }while(0)
#define logm_warning(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T)log_level_warning, \
			format, ##args); }while(0)
#define logm_noti(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T)log_level_noti, \
			format, ##args); }while(0)
#define logm_info(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T)log_level_info, \
			format, ##args); }while(0)
#define logm_debug(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T)log_level_debug, \
			format, ##args); }while(0)
#define logm_trace(m,format, args...)	do{ \
	extern int __logm_fd_##m; \
	extern void __logm_init_logm_##m (void); \
	if (unlikely(__logm_fd_##m<0)) \
		__logm_init_logm_##m(); \
	LOGM_PRINT (__logm_fd_##m, (LX_LOGM_LOGLEVEL_T)log_level_trace, \
			format, ##args); }while(0)

#define logm_enabled(m,l)		({ \
		extern int __logm_fd_##m; \
		extern void __logm_init_logm_##m (void); \
		unsigned int mask; \
		if (unlikely(__logm_fd_##m<0)) \
			__logm_init_logm_##m(); \
		LOGM_ObjMaskGet (__logm_fd_##m, &mask); \
		mask&(1<<l); \
		})

#endif
