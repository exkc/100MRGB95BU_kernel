#ifndef __V4L2_GPS_DBG_H__
#define __V4L2_GPS_DBG_H__

#include "os_util.h"
#include "base_device.h"
#include "de_def.h"


#define GPS_MODULE "gps"

extern int g_gps_debug_fd;

/* logm macro */
#define	GPS_ERROR(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_ERROR,  \
												  format,               \
												   ##args)

#define	GPS_WARN(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_WARNING,\
												  format,               \
												  ##args)

#define	GPS_PRINT(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_INFO,   \
												  format,               \
												  ##args)

#define	GPS_NOTI(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_NOTI,   \
												  format,               \
												  ##args)

#define	GPS_TRACE(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_TRACE,  \
												  format,               \
												  ##args)

#define	GPS_TRACE1(format, args...)		DBG_PRINT(g_gps_debug_fd,       \
												  LX_LOGM_LEVEL_TRACE+1,  \
												  format,               \
												  ##args)

int v4l2_gps_dbg_init(void);

#endif
