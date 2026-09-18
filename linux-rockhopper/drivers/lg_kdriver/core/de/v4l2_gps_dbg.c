
#include "v4l2_gps_dbg.h"


int g_gps_debug_fd;


int v4l2_gps_dbg_init(void)
{

	g_gps_debug_fd = DBG_OPEN(GPS_MODULE);

	if (g_gps_debug_fd < 0) {
	    printk("can't open gps module\n" );
		return -EIO;
	}

    OS_DEBUG_EnableModule(g_gps_debug_fd);

    OS_DEBUG_EnableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_NONE);
    OS_DEBUG_EnableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE);
    OS_DEBUG_EnableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_INFO, DBG_COLOR_NONE);
    OS_DEBUG_EnableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE);
    OS_DEBUG_EnableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_TRACE, DBG_COLOR_NONE);
    OS_DEBUG_DisableModuleByIndex(g_gps_debug_fd, LX_LOGM_LEVEL_TRACE);

	return 0;
}

