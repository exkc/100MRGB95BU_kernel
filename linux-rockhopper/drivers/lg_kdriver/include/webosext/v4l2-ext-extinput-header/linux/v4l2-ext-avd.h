/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_AVD_H
#define _V4L2_EXT_AVD_H

#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-ext-vsc.h>

#define V4L2_EXT_DEV_NO_AV 10

#define V4L2_EXT_DEV_PATH_AV "/dev/video10"

#define V4L2_CID_USER_EXT_AVD_BASE (V4L2_CID_USER_BASE + 0x7000)

enum v4l2_ext_avd_input_src {
  V4L2_EXT_AVD_INPUT_SRC_NONE = 0,
  V4L2_EXT_AVD_INPUT_SRC_ATV,
  V4L2_EXT_AVD_INPUT_SRC_AV,
  V4L2_EXT_AVD_INPUT_SRC_AVD_RESERVED1,
  V4L2_EXT_AVD_INPUT_SRC_AVD_RESERVED2,
};

struct v4l2_ext_avd_timing_info {
  unsigned short h_freq;
  unsigned short v_freq;
  unsigned short h_porch;
  unsigned short v_porch;
  struct v4l2_ext_video_rect active;
  unsigned char vd_lock;
  unsigned char h_lock;
  unsigned char v_lock;
};

//
// AVD class control IDs
//

/**
 * @brief Set/Get AVD Port
 *
 * @rst
 * Functional Requirements
 *   Select the HW port that is actually connected when AVD Connect. It is an
 * item that changes depending
 *   on the circuit configuration and should be called before VIDIOC_S_INPUT.
 *   This value is related with "Ext. Input Adjust" Video Index in the Adjust
 * menu.
 *
 *   AVD Connect 시 실제 연결되는 HW port 를 선택한다. 회로 구성에 따라 바뀌는
 * 항목이고 VIDIOC_S_INPUT 전에 호출되어야 한다.
 *   Adjust menu 의 "Ext. Input Adjust"  Video Index 와 연동되는 값이다.
 *
 * Responses to abnormal situations, including
 *   Nothing special. See return value field.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   There are no constraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set connected AVD port number
 *     VIDIOC_G_CTRL        // Get connected AVD port number
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AVD_PORT
 *
 *     //
 *     // control value
 *     //
 *     0 ~ 255
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Input (connect)
 *     int input = V4L2_EXT_AVD_INPUT_SRC_AV;
 *     ioctl(fd, VIDIOC_S_INPUT, &input);
 *
 *     // Set port number
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_PORT;
 *     control.value = 2;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get port number
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_PORT;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AVD_PORT (V4L2_CID_USER_EXT_AVD_BASE + 0)

/**
 * @brief Get AVD timing info
 *
 * @rst
 * Functional Requirements
 *   This function carries the information of the input signal of the current
 * Analog Video Decoder.
 *   If AVD is in the open / connect state and there is no signal change,
 * decoding should continue
 *   and Timing information should be maintained even if VSC (main / sub scaler)
 * is connected / disconnected.
 *   When the signal is physically changed (no signal-> good signal), all timing
 * information is stabilized
 *   and updated at once. When input is switched to analog TV, active.w and
 * active.h should be fixed
 *   value as follows, The other hFreq, vFreq, hPorch, and vProch must deliver
 * the physical values detected
 *   in the real HW.
 *
 *   이 함수는 현재 Analog Video Decoder의 입력 신호의 정보를 전달한다. AVD 가
 * open/connect 유지 상태이고,
 *   신호 변경이 없으면 VSC(main/sub scaler)가 connect/disconnect 되더라도
 * Decoding 은 지속되어야 하고,
 *   Timing 정보도 유지되어야 한다. 신호가 물리적으로 변경 시(no signal->good
 * signal) 모든 timing 정보가
 *   안정화 된 후 한번에 update 한다.  Analog TV 로 입력 전환 되었을 때,
 * active.w 와 active.h 는 다음과 같이
 *   고정된 값이 전달되어야 하고, 그 외의 hFreq, vFreq, hPorch, vProch 는 실제
 * HW 에서 detection 하는
 *   물리적인 값을 전달해야 한다.
 *
 *   ======= ======== ========= ========== ========
 *   ..      active.x active.y  active.w   active.h
 *   ======= ======== ========= ========== ========
 *   NTSC    0        0         704        480
 *   PAL     0        0         704        576
 *   ======= ======== ========= ========== ========
 *
 *   This function is related to the color system setting of the VIDIOC_S_STD
 * function.
 *   When the NTSC system is set up with the above function,if 576i-PAL-Signal
 * is applied
 *   to the analog TV input, 480i should be returned, If the PAL series is set,
 * if 480i-NTSC-signal is applied
 *   to the analog TV input, 576i should be returned. If analog TV input of TV
 * model supporting PAL 576i
 *   and NTSC 480i (PAL-M, PAL-N, NTSC) is white noise (no signal), active.w and
 * active.h transmit
 *   the last valid signal information, If there is no valid signal information
 * when the TV is turned on
 *   in white noise (no signal) state, active.w should transmit 704 and active.h
 * should transmit 480.
 *   When AVD disconnect and close, all timing information should be reset to
 * '0'.
 *   If Vertical Frequency is 0, the driver should not transmit video timing
 * information.
 *
 *   본 함수는 VIDIOC_S_STD 함수의 color system setting 과 관련이 있다. 위의
 * 함수로 NTSC 계열이 setting 되었는데
 *   Analog TV 입력에 576i-PAL-Signal 이 인가되면, 480i 가 반환 되어야 하고, PAL
 * 계열이 setting 되면 Analog TV 입력에
 *   480i-NTSC-Signal 이 인가되면, 576i 가 반환 되어야 한다. PAL 576i와 NTSC
 * 480i (PAL-M, PAL-N, NTSC) 지원 TV model 의
 *   Analog TV 입력이 white noise (no signal) 상태이면, active.w 와 active.h 는
 * 마지막 valid 신호 정보를 전달 하고,
 *   만약 white noise (no signal) 상태에서 TV 전원이 켜져서 valid 신호 정보가
 * 없으면, active.w 는 704, active.h는 480을
 *   전달해야 한다. AVD disconnect, close 시 timing 정보는 모두 '0' 으로 reset
 * 되어야 한다.
 *   Vertical Frequency 가 0 이면 Driver는 video timing 정보를 전달하지 않아야
 * 한다.
 *
 *   Use Case
 *     * In the Video MW Periodic Task, use V4L2_CID_EXT_AVD_TIMING_INFO to get
 * Timing information in 40ms cycle.
 *     * Video MW Periodic Task에서 40ms 주기로 V4L2_CID_EXT_AVD_TIMING_INFO 를
 * 이용하여 Timing 정보를 얻는다.
 *
 * Responses to abnormal situations, including
 *   Nothing special. See return value field.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   There are no constraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get AVD Timinginfo
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AVD_TIMING_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;   // horizontal start position
 *         unsigned short y;   // vertical start position
 *         unsigned short w;   // horizontal size(width)
 *         unsigned short h;   // vertical size(height)
 *     };
 *
 *     struct v4l2_ext_avd_timing_info
 *     {
 *         unsigned short h_freq;
 *         unsigned short v_freq;
 *         unsigned short h_porch;
 *         unsigned short v_porch;
 *         struct v4l2_ext_video_rect active;
 *         unsigned char vd_lock;
 *         unsigned char h_lock;
 *         unsigned char v_lock;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Video Timing Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_avd_timing_info avd_timing_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&avd_timing_info, 0, sizeof(struct v4l2_ext_avd_timing_info));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_AVD_TIMING_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_avd_timing_info);
 *     ext_controls.controls->ptr = (void *)&avd_timing_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AVD_TIMING_INFO (V4L2_CID_USER_EXT_AVD_BASE + 1)

/**
 * @brief Get Sync Status
 *
 * @rst
 * Functional Requirements
 *   This function says whether Sync exists or Not.
 *
 * .. image:: ../extinput/resources/avd-V4L2_CID_EXT_AVD_VIDEO_SYNC-1.png
 *
 * Responses to abnormal situations, including
 *   Nothing special. See return value field.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   There are no constraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get Sync Status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AVD_VIDEO_SYNC
 *
 *     //
 *     // control value
 *     //
 *     0 (AVD Sync Not Locked), 1 (AVD Sync Locked)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Check Video Sync
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_VIDEO_SYNC;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AVD_VIDEO_SYNC (V4L2_CID_USER_EXT_AVD_BASE + 2)

/**
 * @brief Set/Get avd auto tuning mode
 *
 * @rst
 * Functional Requirements
 *   This function controls the sensitivity of V4L2_CID_EXT_AVD_VIDEO_SYNC.
 *   If V4L2_CID_EXT_AVD_AUTO_TUNING_MODE is necessary it used for AutoTuning in
 * FE-Tuner Side
 *   because avoid tuning garbage channel.
 *   This function is called with "True" when ATV-Auto-Channel-Searching is
 * performed.
 *   This function controls the sensitivity of detecting Analog-Video-Decoder
 * Sync-Lock.
 *   When V4L2_CID_EXT_AVD_AUTO_TUNING_MODE is on, the sensitivity of
 * Sync-detection becomes lower than
 *   before so that garbage channel may not be searched.
 *
 *   During ATV-Auto-Channel-Searching, V4L2_CID_EXT_AVD_AUTO_TUNING_MODE is
 * on.(if it necessary)
 *   During Normal-User-Using condition, V4L2_CID_EXT_AVD_AUTO_TUNING_MODE is
 * off.
 *   This function is only for ATV, so it should not affect Composite and Scart.
 *
 * Responses to abnormal situations, including
 *   Nothing special. See return value field.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   There are no constraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set avd auto tuning mode
 *     VIDIOC_G_CTRL        // Get avd auto tuning mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AVD_AUTO_TUNING_MODE
 *
 *     //
 *     // control value
 *     //
 *     0 (Off), 1 (On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Auto Tuning Mode
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_AUTO_TUNING_MODE;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get Auto Tuning Mode
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_AUTO_TUNING_MODE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AVD_AUTO_TUNING_MODE (V4L2_CID_USER_EXT_AVD_BASE + 3)

/**
 * @brief Set/Get avd channel change
 *
 * @rst
 * Functional Requirements
 *   This function lets AVD driver know channel change. (Replace
 * HAL_VFE_AVD_SetChannelChange())
 *   Call this function when do change channel for platforms which need to know
 * channel change timing.
 *
 *   This function is not necessary. Only some SOC need this to enhance channel
 * change speed.
 *   If driver does not need this api, do not implement this and just return
 * error -1 and the errno EINVAL.
 *
 * Responses to abnormal situations, including
 *   Nothing special. See return value field.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   There are no constraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set avd channel change
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AVD_CHANNEL_CHANGE
 *
 *     //
 *     // control value
 *     //
 *     // Parameter is not necessary, but set default value as "1" for
 * consistency.
 *     1 (On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *   If driver does not support this, just return EINVAL.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Channel Change
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_AVD_CHANNEL_CHANGE;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AVD_CHANNEL_CHANGE (V4L2_CID_USER_EXT_AVD_BASE + 4)

#endif /* _V4L2_EXT_AVD_H */
