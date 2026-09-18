/******************************************************************************
*   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
*   Copyright(c) 2019 by LG Electronics Inc.
*
*   All rights reserved. No part of this work may be reproduced, stored in a
*   retrieval system, or transmitted by any means without prior written
*   permission of LG Electronics Inc.
*****************************************************************************/

#ifndef _FB_EXT_H
#define _FB_EXT_H

#include <linux/types.h>

#define LINUXTV_FB_EXT_VER_SUBMISSION (1)

/* ioctls
   0x46 is 'F'                                                          */
/**
 * @brief description
 *   This function put display position of opened fb device.
 *
 * @rst
 * Functional Requirements
 *   description
 *
 * Responses to abnormal situations, including
 *   description
 *
 * Performance Requirements
 *   description
 *
 * Constraints
 *   description
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //************ ioctl command ************
 *     FBEXTIO_PUT_DISPLAYPOSITION // Put display position
 *
 *     //*************** parameter *************
 *     position          [IN]      fb_ext_displayposition
 *
 * Return Value
 *   * On success 0 is returned.
 *   * On error -1 and the errno variable is set appropriately.
 *   * The generic error codes are described at the `Generic Error Codes`_ chapter.
 *
 * Control Type
 *   description
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int handle_fb_ext()
 *     {
 *         int fd = open("/dev/fb1");
 *
 *         // change position
 *         fb_ext_displayposition position = {100, 100};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYPOSITION, &position);
 *
 *         // set visibility
 *         fb_ext_displayvisible vis = {.visible = 0};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYVISIBLE, &vis);
 *
 *         // set region
 *         fb_ext_displayregion region = {0, 0, 1024, 960};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYREGION, &region);
 *     }
 *
 * Remark (optional)
 *   description
 *
 * Seealso (optional)
 *   .. _Generic Error Codes: https://linuxtv.org/downloads/v4l-dvb-apis-new/uapi/gen-errors.html#id1
 * @endrst
 */
#define FBEXTIO_PUT_DISPLAYPOSITION 0x46e01
/**
 * @brief description
 *   This function put display visible of opened fb device.
 * @rst
 * Functional Requirements
 *   description
 *
 * Responses to abnormal situations, including
 *   description
 *
 * Performance Requirements
 *   description
 *
 * Constraints
 *   description
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //************ ioctl command ************
 *     FBEXTIO_PUT_DISPLAYVISIBLE // Put display visible
 *
 *     //*************** parameter *************
 *     visible          [IN]      fb_ext_displayvisible
 *
 *
 * Return Value
 *   * On success 0 is returned.
 *   * On error -1 and the errno variable is set appropriately.
 *   * The generic error codes are described at the `Generic Error Codes`_ chapter.
 *
 * Control Type
 *   description
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int handle_fb_ext()
 *     {
 *         int fd = open("/dev/fb1");
 *
 *         // change position
 *         fb_ext_displayposition position = {100, 100};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYPOSITION, &position);
 *
 *         // set visibility
 *         fb_ext_displayvisible vis = {.visible = 0};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYVISIBLE, &vis);
 *
 *         // set region
 *         fb_ext_displayregion region = {0, 0, 1024, 960};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYREGION, &region);
 *     }
 *
 * Remark (optional)
 *   description
 *
 * Seealso (optional)
 *   description
 * .. _Generic Error Codes: https://linuxtv.org/downloads/v4l-dvb-apis-new/uapi/gen-errors.html#id1
 * @endrst
 */
#define FBEXTIO_PUT_DISPLAYVISIBLE 0x46e02
/**
 * @brief description
 *   This function put display region of opened fb device.
 *
 * @rst
 * Functional Requirements
 *   description
 *
 * Responses to abnormal situations, including
 *   description
 *
 * Performance Requirements
 *   description
 *
 * Constraints
 *   description
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *       //************ ioctl command ************
 *        FBEXTIO_PUT_DISPLAYREGION // Put display region
 *
 *       //*************** parameter *************
 *       region          [IN]      fb_ext_displayregion
 *
 *
 * Return Value
 *   * On success 0 is returned.
 *   * On error -1 and the errno variable is set appropriately.
 *   * The generic error codes are described at the `Generic Error Codes`_ chapter.
 *
 * Control Type
 *   description
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int handle_fb_ext()
 *     {
 *         int fd = open("/dev/fb1");
 *
 *         // change position
 *         fb_ext_displayposition position = {100, 100};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYPOSITION, &position);
 *
 *         // set visibility
 *         fb_ext_displayvisible vis = {.visible = 0};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYVISIBLE, &vis);
 *
 *         // set region
 *         fb_ext_displayregion region = {0, 0, 1024, 960};
 *         ioctl(fd, FBEXTIO_PUT_DISPLAYREGION, &region);
 *     }
 *
 * Remark (optional)
 *   description
 *
 * Seealso (optional)
 *   description
 * .. _Generic Error Codes: https://linuxtv.org/downloads/v4l-dvb-apis-new/uapi/gen-errors.html#id1
 * @endrst
 */
#define FBEXTIO_PUT_DISPLAYREGION 0x46e03

struct fb_ext_displayposition {
    __u32 x;
    __u32 y;
};

struct fb_ext_displayvisible {
    __u8 visible;   //** 0 = unvisible, otherwise = visible
};

struct fb_ext_displayregion {
    __u32 x;
    __u32 y;
    __u32 width;
    __u32 height;
};

/* example code:
int handle_fb_ext()
{
    int fd = open("/dev/fb1");

    // change position
    fb_ext_displayposition position = {100, 100};
    ioctl(fd, FBEXTIO_PUT_DISPLAYPOSITION, &position);

    // set visibility
    fb_ext_displayvisible vis = {.visible = 0};
    ioctl(fd, FBEXTIO_PUT_DISPLAYVISIBLE, &vis);

    // set region
    fb_ext_displayregion region = {0, 0, 1024, 960};
    ioctl(fd, FBEXTIO_PUT_DISPLAYREGION, &region);
}
*/
#endif
