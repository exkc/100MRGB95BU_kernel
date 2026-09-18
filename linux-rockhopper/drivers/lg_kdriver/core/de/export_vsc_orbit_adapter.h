#ifndef _EXPORT_VSC_ORBIT_ADAPTER_
#define _EXPORT_VSC__ORBIT_ADAPTER_

#include "linux/v4l2-ext/v4l2-ext-vsc.h"

typedef struct ORBIT_CALLBACK_T {
    void (*pfnCalculateOrbitPosition)(
        // Input Parameter
        struct v4l2_ext_video_rect, struct v4l2_ext_video_rect, struct v4l2_ext_video_rect,
        struct v4l2_ext_vsc_orbit_policy,
        // Output Parameter
        struct v4l2_ext_vsc_orbit_position *);
} ORBIT_CALLBACK_T;
 
void vsc_registerOrbitCB(ORBIT_CALLBACK_T *pfn);
ORBIT_CALLBACK_T *vsc_getOrbitCallbackFp(void);
 
#endif // _EXPORT_VSC_ADAPTER_ORBIT_
