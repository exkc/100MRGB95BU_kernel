/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file v4l2-lge-hdmi.h
 *
 *  It is the header file for controling v4l2 hdmi driver.
 *
 *  @author     taejun.lee(taejun.lee@lge.com)
 *  @version    1.0
 *  @date       2019.05.07
 *  @note
 *  @see
 */

#ifndef _V4L2_LGE_EARC_H
#define _V4L2_LGE_EARC_H

//#include <linux/linuxtv-ext-ver.h>
#include <linux/v4l2-controls.h>

// clang-format off
//#define V4L2_CID_USER_HDMI_BASE					(V4L2_CID_USER_BASE + 0x5000)
//#define V4L2_CID_EXT_EARC						(V4L2_CID_USER_HDMI_BASE +10)
//#define V4L2_CID_EXT_EARC_CONNECTION_INFO		(V4L2_CID_USER_HDMI_BASE +11)
//#define V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ	(V4L2_CID_USER_HDMI_BASE +12)

//#define V4L2_EXT_EARC_ERX_LATENCY_REQ_MINIMIZE	0   // 0: requeset to minimize eARC RX latency
//#define V4L2_EXT_EARC_ERX_LATENCY_REQ_NON_SYNC	254 // 254: No syncronization required
//#define V4L2_EXT_EARC_ERX_LATENCY_REQ_UNKNOWN	255 // 255: unknown eARC TX latency
//#define V4L2_EXT_EARC_CAPABILITY_BYTES			255

/*
    VIDIOC_S_CTRL
	VIDIOC_G_CTRL

struct v4l2_control {
    unsigned int	id;
    signed int		value;
};
*/

/*
	VIDIOC_S_EXT_CTRLS		// Set Control EARC
	VIDIOC_G_EXT_CTRLS		// Get Control EARC
*/
/*
struct v4l2_ext_control {
    unsigned int id;
    unsigned int size;
    unsigned int reserved2[1];
    union {
        unsigned int		value;
        signed long long	value64;
        char				*string;
        unsigned char		*p_u8;
        unsigned short		*p_u16;
        unsigned int		*p_u32;
        void				*ptr;
    };
};
 
struct v4l2_ext_controls {
    unsigned int ctrl_class;
    unsigned int count;
    unsigned int error_idx;
    unsigned int reserved[2];
    struct v4l2_ext_control *controls;
};

enum v4l2_ext_earc_output_port {
    V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
    V4L2_EXT_EARC_OUTPUT_PORT_1,
    V4L2_EXT_EARC_OUTPUT_PORT_2,
    V4L2_EXT_EARC_OUTPUT_PORT_3,
    V4L2_EXT_EARC_OUTPUT_PORT_4,
    V4L2_EXT_EARC_OUTPUT_PORT_ALL,
};

enum v4l2_ext_earc_enable {
    V4L2_EXT_EARC_DISABLE = 0,
    V4L2_EXT_EARC_ENABLE  = 1,
};


enum v4l2_ext_earc_status {
    V4L2_EXT_EARC_IDLE1 = 0,
    V4L2_EXT_EARC_IDLE2 = 1,
    V4L2_EXT_EARC_DISC1 = 2,
    V4L2_EXT_EARC_DISC2 = 3,
    V4L2_EXT_EARC_EARC  = 4,
};

struct v4l2_ext_earc {
    enum v4l2_ext_earc_output_port	port;
    enum v4l2_ext_earc_enable 		earc_enable_state;
};

struct v4l2_ext_earc_connection_info {
    enum v4l2_ext_earc_output_port	port;// = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
    enum v4l2_ext_earc_status		status;// = V4L2_EXT_EARC_IDLE1;
    unsigned char				capability[V4L2_EXT_EARC_CAPABILITY_BYTES];     //Short Audio Descriptior Max 256 byte
    unsigned char				erx_latency_req;// = 0;	//0~255
    unsigned char				erx_latency;// = 0;		//0~255
};
*/

int v4l2_earc_device_init(void);

#endif /* _V4L2_LGE_HDMI_H */
