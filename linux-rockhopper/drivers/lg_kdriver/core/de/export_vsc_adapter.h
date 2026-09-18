#ifndef _EXPORT_VSC_ADAPTER_
#define _EXPORT_VSC_ADAPTER_

#include "linux/v4l2-ext/v4l2-ext-vsc.h"

typedef struct ASPECTRATIO_CALLBACK
{
    int (*pfnAspectratiodrvCalculate)(
			struct v4l2_ext_video_rect,     // source_rect, Resolution of input source
			struct v4l2_ext_video_rect,     // output_rect, Output region to display video
			unsigned short,                 // wss_afd, AFD or WSS of input source
			unsigned short,                 // par_width, PAR width of input source
			unsigned short,                 // par_height, PAR height of input source
			struct v4l2_ext_system_policy,  // system_policy, webOS policy of system
			struct v4l2_ext_setting_policy, // setting_policy, webOS policy of setting
			struct v4l2_ext_video_rect *,   // calculated_input_rect, calculated crop region for input source
			struct v4l2_ext_video_rect *    // calculated_output_rect, calculated output region to display video
			);

    int (*pfnOrbitdrvMoveConvert)(struct v4l2_ext_system_policy,	// system_policy, webOS policy of system
				 struct v4l2_ext_vsc_orbit_window, // old_orbit_window
				 struct v4l2_ext_vsc_orbit_window, // new_orbit_window
				 struct v4l2_ext_vsc_orbit_move,   // orbit_move
				 struct v4l2_ext_vsc_orbit_move *  // calculated_orbit_move
				 );

    int (*pfnOrbitdrvWindowConvert)(
        struct v4l2_ext_system_policy,     // system_policy, webOS policy of system
        struct v4l2_ext_video_rect,        // input_rect, calculated crop region for input source
        struct v4l2_ext_video_rect,        // output_rect, calculated output region to display video
        struct v4l2_ext_vsc_orbit_window,  // orbit_window
        struct v4l2_ext_vsc_orbit_window * // calculated_orbit_window
        );
} ASPECTRATIO_CALLBACK_T;

void vsc_registerAspectratioCB(ASPECTRATIO_CALLBACK_T *pfn);
ASPECTRATIO_CALLBACK_T *vsc_getAspectratioCallbackFp(void);

#endif //_EXPORT_VSC_ADAPTER_

