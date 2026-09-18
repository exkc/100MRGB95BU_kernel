/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018-2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _VIDEODEV2_EXT_H
#define _VIDEODEV2_EXT_H

/* FIXME: gstreamer-good uses uapi/linux/videodev2.h,
 * so add to check _UAPI_XX to prevent redefinition error
 */
#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

#include <linux/v4l2-ext/v4l2-ext-broadcast.h>
#include <linux/v4l2-ext/v4l2-ext-extinput.h>
#include <linux/v4l2-ext/v4l2-ext-renderer.h>
#include <linux/v4l2-ext/v4l2-ext-panel.h>
#include <linux/v4l2-ext/v4l2-ext-screencapture.h>
#include <linux/v4l2-ext/v4l2-ext-picturequality.h>

#endif
