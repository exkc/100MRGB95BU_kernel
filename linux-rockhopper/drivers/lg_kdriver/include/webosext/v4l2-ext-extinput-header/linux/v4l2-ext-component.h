/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_COMPONENT_H
#define _V4L2_EXT_COMPONENT_H

#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-ext-vsc.h>

#define V4L2_EXT_DEV_NO_ADC 11

#define V4L2_EXT_DEV_PATH_ADC "/dev/video11"

#define V4L2_CID_USER_EXT_ADC_BASE (V4L2_CID_USER_BASE + 0x6000)

/* ADC */
enum v4l2_ext_adc_input_src {
  V4L2_EXT_ADC_INPUT_SRC_NONE = 0,
  V4L2_EXT_ADC_INPUT_SRC_COMP,
  V4L2_EXT_ADC_INPUT_SRC_RGB,
  V4L2_EXT_ADC_INPUT_SRC_COMP_RESERVED2,
};

struct v4l2_ext_adc_timing_info {
  unsigned short h_freq;
  unsigned short v_freq;
  unsigned short h_total;
  unsigned short v_total;
  unsigned short h_porch;
  unsigned short v_porch;
  struct v4l2_ext_video_rect active;
  unsigned short scan_type;
  unsigned short phase;
};

struct v4l2_ext_adc_calibration_data {
  unsigned short r_gain;
  unsigned short g_gain;
  unsigned short b_gain;
  unsigned short r_offset;
  unsigned short g_offset;
  unsigned short b_offset;
};

//
// ADC class control IDs
//

/**
 * @brief Get ADC timing info
 *
 * @rst
 * Functional Requirements
 *   This function reads signal timing information such as H / V frequency,
 *   total H / V length of signal (Sync width + active) and H / V length in the
 * active
 *   period of ADC block. If the ADC is in the open / connect state and there is
 *   no signal change, the decoding should continue and the timing information
 * should be
 *   maintained even if the VSC (main / sub scaler) is connected / disconnected.
 *   Timing information should be reset to all '0' at ADC disconnect and close.
 *   Do not arbitrarily pass timing information to '0' for unsupported specs or
 * specific timing.
 *   V frequency must be multiplied by 10 and passed as Integer. When a signal
 * is physically
 *   changed (no signal-> good signal), timing information should not be
 * partially transmitted
 *   several times, and all timing information must be transmitted at a time.
 *   The VIDEO_RECT_T information shall be transmitted as follows. For example,
 * 720x480i@59.94Hz signal.
 *
 *   - some driver use double sampling so result of ADC may be 1440*480 or
 * 720*240 because it's a interlace signal.
 *   - but at this case this function should return like this x=0, y=0, w=720,
 * h=480, vFreq=599, scanType=0.
 *   - also all of input/output window setting will be done base on this values.
 *
 *   Basically, it should support the following VESA standard format and Timing
 * information should be transmitted correctly.
 *   Formats that are included in VESA but are not listed in the table below are
 * not mandatory, but must be supported.
 *
 *   .. image:: /v4l2/adc-V4L2_CID_EXT_ADC_TIMING_INFO-1.png
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get ADC Timinginfo
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_TIMING_INFO
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
 *     struct v4l2_ext_adc_timing_info
 *     {
 *         unsigned short h_freq;
 *         unsigned short v_freq;
 *         unsigned short h_total;
 *         unsigned short v_total;
 *         unsigned short h_porch;
 *         unsigned short v_porch;
 *         struct v4l2_ext_video_rect active;
 *         unsigned short scan_type;
 *         unsigned short phase;
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
 *     struct v4l2_ext_adc_timing_info adc_timing_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&adc_timing_info, 0, sizeof(struct v4l2_ext_adc_timing_info));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_ADC_TIMING_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_adc_timing_info);
 *     ext_controls.controls->ptr = (void *)&adc_timing_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_TIMING_INFO (V4L2_CID_USER_EXT_ADC_BASE + 0)

/**
 * @brief Get ADC OTP Data
 *
 * @rst
 * Functional Requirements
 *   This function is called once at booting to obtain ADC calibration data
 * stored in the OTP area.
 *   The chip-vendor must complete the ADC calibration before the chip is
 * released.
 *   All input OTP data (YCbCr and SCART-RGB (DVB system)) should be transmitted
 * at one time.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get ADC OTP Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_OTP_DATA
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_adc_calibration_data
 *     {
 *         unsigned short r_gain;
 *         unsigned short g_gain;
 *         unsigned short b_gain;
 *         unsigned short r_offset;
 *         unsigned short g_offset;
 *         unsigned short b_offset;
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
 *     // Get ADC Calibration Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_adc_calibration_data otp_data;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&otp_data, 0, sizeof(struct v4l2_ext_adc_calibration_data));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_ADC_OTP_DATA;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_adc_calibration_data);
 *     ext_controls.controls->ptr = (void *)&otp_data;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_OTP_DATA (V4L2_CID_USER_EXT_ADC_BASE + 1)

/**
 * @brief Set/Get ADC Calibration Data
 *
 * @rst
 * Functional Requirements
 *   - Set: This function sets the ADC calibration data (gain / offset) in the
 * ADC register.
 *     When booting, when input is switched to Component or Scart-RGB, ADC
 * calibration data is read
 *     from EEPROM and set through this function.
 *   - Get: This function obtains the ADC calibration data (gain / offset) from
 * the register after external
 *     or internal calibration. The obtained data is written to the EEPROM.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS        // Set ADC Calibration Data
 *     VIDIOC_G_EXT_CTRLS        // Get ADC Calibration Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_CALIBRATION_DATA
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_adc_calibration_data
 *     {
 *         unsigned short r_gain;
 *         unsigned short g_gain;
 *         unsigned short b_gain;
 *         unsigned short r_offset;
 *         unsigned short g_offset;
 *         unsigned short b_offset;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set ADC Calibration Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_adc_calibration_data cal_data;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&cal_data, 0, sizeof(struct v4l2_ext_adc_calibration_data));
 *
 *     cal_data.rGain  = 192;
 *     cal_data.gGain  = 192;
 *     cal_data.bGain  = 192;
 *     cal_data.rOffset= 128;
 *     cal_data.gOffset= 128;
 *     cal_data.bOffset= 128;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_ADC_CALIBRATION_DATA;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_adc_calibration_data);
 *     ext_controls.controls->ptr = (void *)&cal_data;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get ADC Calibration Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_adc_calibration_data cal_data;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&cal_data, 0, sizeof(struct v4l2_ext_adc_calibration_data));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_ADC_CALIBRATION_DATA;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_adc_calibration_data);
 *     ext_controls.controls->ptr = (void *)&cal_data;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_CALIBRATION_DATA (V4L2_CID_USER_EXT_ADC_BASE + 2)

/**
 * @brief Set/Get ADC Calibration Type
 *
 * @rst
 * Functional Requirements
 *   This function performs an analog-to-digital calibration.
 *   External ADC: calibration (MSPG timing : 225 (1920x1080@60Hz), pattern: 65)
 *   performed by the external pattern input by the instrument.
 *   Internal ADC: Calibration performed by the pattern supported in the driver.
 *   OTP ADC: The chip-set itself is calibrated and the data is stored in the
 * OTP area.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set ADC Calibration Type
 *     VIDIOC_G_CTRL        // Get ADC Calibration Type
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_CALIBRATION_TYPE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_adc_calibration_type
 *     {
 *         V4L2_EXT_ADC_CALIBRATION_TYPE_OTP = 0,
 *         V4L2_EXT_ADC_CALIBRATION_TYPE_EXTERNAL,
 *         V4L2_EXT_ADC_CALIBRATION_TYPE_INTERNAL,
 *         V4L2_EXT_ADC_CALIBRATION_TYPE_USER,
 *     };
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
 *     // Set ADC Calibration Type
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_ADC_CALIBRATION_TYPE;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get ADC Calibration Type
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_ADC_CALIBRATION_TYPE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_CALIBRATION_TYPE (V4L2_CID_USER_EXT_ADC_BASE + 3)
enum v4l2_ext_adc_calibration_type {
  V4L2_EXT_ADC_CALIBRATION_TYPE_OTP = 0,
  V4L2_EXT_ADC_CALIBRATION_TYPE_EXTERNAL,
  V4L2_EXT_ADC_CALIBRATION_TYPE_INTERNAL,
  V4L2_EXT_ADC_CALIBRATION_TYPE_USER,
};

/**
 * @brief Set ADC reset Calibration
 *
 * @rst
 * Functional Requirements
 *   This function resets the value of ADC Calibration data register to default
 * value.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set ADC Calibration Type
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_RESET_CALIBRATION
 *
 *     //
 *     // control value
 *     //
 *     0 (Ignore), 1 (Reset)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Reset Calibration Data
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_ADC_RESET_CALIBRATION;
 *     control.value = 1;      // Reset
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_RESET_CALIBRATION (V4L2_CID_USER_EXT_ADC_BASE + 4)

/**
 * @brief Set/Get ADC fast switch
 *
 * @rst
 * Functional Requirements
 *   This function enables Fast-InputChange to Component,
 *   This function is called when test mode in Factory Line.
 *   In Factory Line, for improving productivity, Input Change speed must be
 * fast.
 *   For High productivity, we call V4L2_CID_EXT_ADC_FAST_SWITCH as on.
 *   After testing in FactoryMode,  we call V4L2_CID_EXT_ADC_FAST_SWITCH as off.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Component input is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set ADC fast switch
 *     VIDIOC_G_CTRL        // Get ADC fast switch
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_ADC_FAST_SWITCH
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
 *     // Set Fast Switch Mode
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_ADC_FAST_SWITCH;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get Fast Switch Mode
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_ADC_FAST_SWITCH;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_ADC_FAST_SWITCH (V4L2_CID_USER_EXT_ADC_BASE + 5)

#endif /* _V4L2_EXT_COMPONENT_H */
