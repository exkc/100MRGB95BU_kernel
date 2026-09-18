#ifndef _SYS_LOG_H_
#define _SYS_LOG_H_

#include "logm.h"

#define	SYS_PRINT(format, args...)		logm_noti(sys, format, ##args)
#define	SYS_TRACE(format, args...)		logm_trace(sys, format, ##args)
#define	SYS_DEBUG(format, args...)		logm_debug(sys, format, ##args)
#define	SYS_NOTI(format, args...)		logm_noti(sys, format, ##args)
#define	SYS_ERROR(format, args...)		logm_error(sys, format, ##args)

#endif
