/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2024 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_PICTUREQUALITY_H
#define _V4L2_EXT_PICTUREQUALITY_H


#include <linux/v4l2-controls.h>

#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 1
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_DEV_NO_PQ 50
 *
 * @endrst
 */
#define V4L2_EXT_DEV_NO_PQ 50

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 1 Path
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define 4L2_EXT_DEV_PATH_PQ "/dev/video50"
 *
 * @endrst
 */
#define V4L2_EXT_DEV_PATH_PQ "/dev/video50"

//
// PQ control Bases
//
#define V4L2_CID_USER_EXT_PQ_BASE (V4L2_CID_USER_BASE + 0x3000)


/******************************************************************************
            PQ class control IDs
******************************************************************************/

#define V4L2_CID_EXT_LED_BASE (V4L2_CID_USER_EXT_PQ_BASE)

/**
 * @brief
 *   Initialize the LED block using the given information.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      It provide informations for initializing LED block.
 *      BSP have ready turnning on LED block using this informations
 *   - Details of Feature
 *      This function Initialize LED block.
 *   - Target Hardware Block
 *      LED block : it includes local dimming(and related others)
 *   - Call frequency and timing
 *      Event : triggered by system power off_on
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Any sudden flicker(brightness) should not happen caused by this.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_INIT
 *
 *     //
 *     // parameter
 *     //
 *     stPanelInfo          [IN]      v4l2_ext_vpq_cmn_data
 *     cf... (struct v4l2_ext_led_panel_info *)stPanelInfo.p_data
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Remarks
 *   useInterLocalDimming : This is for LED block of platform with external
 *   local dimming IC. A specific platform can use external local dimming IC
 *   even if SoC has it.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // LED initialize v1 with v4l2_ext_led_panel_info
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_led_panel_info stRealInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.panel_inch;  = inchType;
 *     stRealInfo.backlight_type = ledType;
 *     stRealInfo.bar_type = barType;
 *     stRealInfo.module_maker = moduleMaker;
 *     stRealInfo.local_dim_ic_type = icType;
 *     stRealInfo.panel_type = pnelType;
 *
 *     // set version = 1
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_INIT;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 *     // LED initialize v2 with v4l2_ext_led_panel_info_v2 from webOS26 and WEE3.0
 *     // Note oled model may still use v4l2_ext_led_panel_info.
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_led_panel_info_v2 stRealInfo_v2;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo_v2, 0, sizeof(stRealInfo_v2));
 *
 *     stRealInfo_v2.backlight_type = ledType;
 *     stRealInfo_v2.horizontal_block_num = 6;
 *     stRealInfo_v2.vertical_block_num  = 2;
 *
 *     stRealInfo_v2.spi_speed_hz = 1200000;
 *     stRealInfo_v2.spi_signal_strength = 0;
 *     stRealInfo_v2.spi_port = 0;
 *     strncpy(stRealInfo_v2.led_driver_id, "lge_default", 15);
 *
 *     // set version = 2
 *     stPqContainer.version=2;
 *     stPqContainer.length = sizeof(stRealInfo_v2);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo_v2;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_INIT;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 * @endrst
 */
#define V4L2_CID_EXT_LED_INIT (V4L2_CID_EXT_LED_BASE + 0)

/**
 * @brief
 *   Control local dimming level by lut index
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for controlling local dimming level
 *   - Details of Feature
 *      This function control local dimming level by lut index.
 *   - Target Hardware Block
 *      Local Dimming
 *   - Call frequency and timing
 *      Event : triggered by UI/video meta info such as HDR/video Connection
 *                 /system power off_on

 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   A flicker caused by lut change, should be minimized.
 *   You may use some temporal filters to minimize it
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL // Set PQ Data
 *     VIDIOC_G_CTRL // Get VDO info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_DB_IDX
 *
 *     //
 *     // parameter
 *     //
 *     0 ~ maxNum : index number of LUT branch.
 *                  The maxNum is defined by other documents, because it has variance on chipInfo policy
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // LED Set LUT
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_LED_LUT;
 *     control.value = uiIndex;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *     // LED Get LUT
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_LED_DB_IDX;
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * See Also
 *   V4L2_CID_EXT_LED_DB_DATA
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_DB_IDX (V4L2_CID_EXT_LED_BASE + 1)

/**
 * @brief
 *   Control local dimming demo mode
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for controlling local dimming demo mode.
 *      The demo mode is used in special case
 *      such as h/w defect test is manufacture site
 *      The demo mode should show current localdimming h/w's integrity
 *      as an internal moving pattern
 *   - Details of Feature
 *      This function control local dimming demo mode. When demo mode on,
 *      LED is on/off sequentially
 *   - Target Hardware Block
 *      Local Dimming
 *   - Call frequency and timing
 *      Event : triggered by user action like UI change
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   The demo mode should judge current TV's localdimming h/w's integrity
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_DEMOMODE
 *
 *     //
 *     // parameter
 *     //
 *     stModeInfo          [IN]      v4l2_ext_vpq_cmn_data
 *     cf... (struct v4l2_ext_led_ldim_demo_info *)stPanelInfo.p_data
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // LED demo mode
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_led_ldim_demo_info stRealInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.bOnOff = TRUE;
 *     stRealInfo.eType = v4l2_ext_led_ldim_demo_type_linedemo;
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_DEMOMODE;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_DEMOMODE (V4L2_CID_EXT_LED_BASE + 2)

/**
 * @brief
 *   Control local dimming block on/off
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for controlling local dimming block.
 *   - Details of Feature
 *      This function control local dimming block on/off.
 *   - Target Hardware Block
 *      Local Dimming
 *   - Call frequency and timing
 *      Event : triggered by system power off/on
 *
 * Responses to abnormal situations, including
 *   If "V4L2_CID_EXT_LED_INIT & V4L2_CID_EXT_LED_DB_IDX" is not called ahead of this v4l2 call,
 *   it can return error and not turn on
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get VDO info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_EN
 *
 *     //
 *     // control value
 *     //
 *     0(Off), 1(On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set LED Local Dimming Enable
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_LED_EN;
 *     control.value = true;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_EN (V4L2_CID_EXT_LED_BASE + 3)

/**
 * @brief
 *   Uninitialize Local Dimming
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for Uninitializing local dimming
 *   - Details of Feature
 *      Uninitialize Local Dimming and use for debug
 *   - Target Hardware Block
 *      LED block : it includes local dimming(and related others)
 *   - Call frequency and timing
 *      Event : triggered by system power off(like QSM suspend)
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_FIN
 *
 *     //
 *     // parameter
 *     //
 *     void
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Finalize LED Local Dimming
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_LED_FIN;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_FIN (V4L2_CID_EXT_LED_BASE + 4)

/**
 * @brief
 *   Set Local Dimming DB Look up table
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *      for setting Local Dimming DB Look up table
 *   Details of Feature
 *      Set Local Dimming DB Look up table
 *   Target Hardware Block
 *      Local Dimming
 *   Call frequency and timing
 *      Event : triggered by system power off/on
 *   Requirements for High Contrast BPL
 *      .. image:: /picturequality/resources/pq-V4L2_CID_EXT_LED_DB_DATA-1.png
 *      Implement an interface that can receive AI depth level and AI Logo apl results in the local dimming block.
 *      Add gain curve in DB  that depth/logo local dimming gain can be set in LG DB structure.(Implemented in the same 2D LUT structure as before)
 *      Implement an algorithm in the F/W to process by multiplying the gain value by the originallocal dimming data
 *
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Requirements for High Contrast BPL
 *       The function is disabled when the value is set to 0, because it is related to V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_DB_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_ext_vpq_cmn_data
 *     cf... (struct v4l2_led_lut *)stContainer.p_data
 *     // v4l2_led_lut means Local dimming LUT Data
 *          It should have multiple rooms(index struct).
 *          It would be defined on another document,
 *              because it has a dependency on SoC's characteristics
 *
 *     struct v4l2_led_db_info {
 *        unsigned int size;
 *        union {
 *             unsigned int *pData;
 *             unsigned int compat_pData;
 *             unsigned long long sizer;
 *         };
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set LED DB Data
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     struct v4l2_led_lut stRealInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.lutVersion = 0x01;
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_DB_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * See Also
 *   V4L2_CID_EXT_LED_DB_IDX
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_DB_DATA (V4L2_CID_EXT_LED_BASE + 5)

/**
 * @brief
 *   Control SPI command bit
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for controlling SPI command bit
 *   - Details of Feature
 *      Control SPI command bit connected to LED driver
 *      It's bit mask operation(set/clear).
 *          So Driver should remember the last every bit values
 *   - Target Hardware Block
 *      LED block : it includes SPI connected to LED driver
 *   - Call frequency and timing
 *      Event & Periodical Polling
 *      Event : triggered by UI/video meta info
 *      Periodical Polling : triggered by environments changes like light sensor /
 *                           or triggered by video scene change
 *                           minimum calling period is 30ms
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_CONTROL_SPI
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_ext_vpq_cmn_data
 *     cf... (struct v4l2_ext_led_spi_ctrl_info *)stContainer.p_data : only for version 0x01
 *     we don't use v4l2_ext_led_spi_ctrl_info anymore,
 *     v4l2_ext_vpq_cmn_data's version is equal or over 0x10
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Control LED SPI
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     unsigned short stRealInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo = 0x84;   // 0x84 means final spi command to send to LED driver
 *
 *     // 0x01 : old version using v4l2_ext_led_spi_ctrl_info
 *     // 0x10 : new version NOT using v4l2_ext_led_spi_ctrl_info
 *     stPqContainer.version = 0x10;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_CONTROL_SPI;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_CONTROL_SPI (V4L2_CID_EXT_LED_BASE + 6)

/**
 * @brief
 *   Get Local Dimming APL value
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting Local Dimming APL value
 *   - Details of Feature
 *      Get Local Dimming APL Min/Max value and use fort BPL On/Off Condition
 *   - Target Hardware Block
 *      Local Dimming
 *   - Call frequency and timing
 *      Periodical Polling : minimum calling period is 30ms
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_APL_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_ext_vpq_cmn_data
 *     cf... (struct v4l2_led_apl_info *)stContainer.p_data
 *     // currently common struct for all platform. But it may have different struct for other new platform
 *     struct v4l2_led_apl_info
 *     {
 *        unsinged short block_apl_min;
 *        unsinged short block_apl_max;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get LED block apl info
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_vpq_cmn_data stPqContainer;
 *     struct v4l2_led_apl_info stRealInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_APL_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_APL_DATA (V4L2_CID_EXT_LED_BASE + 7)

/**
 * @brief Set/Get BPL DATA
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting/getting BPL data
 *   - Details of Feature
 *      This function set/get a data to BPL Algorithm of Local Dimming firmware
 *   - Target Hardware Block
 *      Local Dimming
 *   - Call frequency and timing
 *      Periodical Polling : triggered by light sensor data
 *                           minimum calling period is 30ms
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_BPL_DATA
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_led_bpl_info {
 *        unsigned char ai_brightness; //0(Off), 1(On)
 *        unsigned char sensor_level; // 0~100
 *        unsigned char blooming_mode; //0(Off), 1(On)
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
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set BPL Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_led_bpl_info bpl_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&bpl_info, 0, sizeof(v4l2_ext_led_bpl_info));
 *
 *     bpl_info.ai_brightness= 1;
 *     bpl_info.sensor_level= 100;
 *     bpl_info.blooming_mode= 1;
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_led_bpl_info);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&bpl_info;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_BPL_DATA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_BPL_DATA (V4L2_CID_EXT_LED_BASE + 8)

/**
 * @brief Set/Get ABI(Adaptive BlackFrame Insertion) control
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting/getting ABI module
 *   - Details of Feature
 *      When it's auto mode, it's output duty gain will be controlled dynamically by motion vector
 *      When it's manual mode, it will make only fixed output duty gain output by given manual value
 *   - Target Hardware Block
 *      Local Dimming / ABI
 *   - Call frequency and timing
 *      Event : triggered by UI/video meta info
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_LED_ABI
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_led_abi_ctrl
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set BPL Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_led_abi_ctrl ctrl;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(pqData));
 *     memset(&ctrl, 0, sizeof(ctrl));
 *
 *     ctrl.autoMode = false;
 *     ctrl.manualGain = 80;
 *     ctrl.settings.gain_step = 10;
 *     ctrl.settings.memc_info_diff = 10;
 *     ctrl.settings.gain_lut = NULL;
 *     pqData.version=1;
 *     pqData.length = sizeof(ctrl);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&ctrl;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_LED_ABI;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_LED_ABI (V4L2_CID_EXT_LED_BASE + 9)

#define V4L2_CID_EXT_MEMC_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x100)

/**
 * @brief
 *   Defines the Control ID to initialize the MEMC(Motion Estimation
 *   Motion Compensation) block.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for initializing the MEMC block.
 *   - Details of Feature
 *      All the MEMC related functions must be called after initialization of the
 *      MEMC block. It calls the library functions of chip vendor for
 *      initialization and initializes the global variables for MEMC operations.
 *   - Target Hardware Block
 *      MEMC Block
 *   - Call frequency and timing
 *      It is called once when the system is power on.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no performance degradation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL // Set PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEMC_INIT
 *
 *     //
 *     // parameter
 *     //
 *     void
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              Initialize MEMC block.
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_MEMC_INIT;
 *     control.value = 0;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_MEMC_INIT (V4L2_CID_EXT_MEMC_BASE + 0)

/**
 * @brief
 *  Defines the Control ID to set/get the control of frame delay.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting the control of frame delay.
 *   - Details of Feature
 *      This function controls the frame delay due to
 *      MEMC(Motion Estimation Motion Compensation) working.
 *      The VIDIOC_S_CTRL is used for setting the control data and the VIDIOC_G_CTRL
 *      is used for getting the control data.
 *   - Target Hardware Block
 *      MEMC Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not
 *      send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL // Set PQ Data
 *     VIDIOC_G_CTRL // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEMC_LOWDELAY_MODE
 *
 *     //
 *     // parameter
 *     //
 *     UINT8 type [IN]
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              IF u8DelayMode = 1
 *                        Reduce frame buffer for low frame delay
 *              ELSE
 *                        Normal mode
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     memset(&control, 0, sizeof(v4l2_control));
 *     control.id = V4L2_CID_EXT_MEMC_LOW_DELAY_MODE;
 *     control.value = 1;
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_MEMC_LOW_DELAY_MODE (V4L2_CID_EXT_MEMC_BASE + 1)

/**
 * @brief
 *   Defines the Control ID to set/get the MEMC(Motion Estimation Motion
 *   Compensation) level.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting the MEMC level.
 *   - Details of Feature
 *      There are seven MEMC levels.
 *      The Blur and Judder values are passed with the MEMC level to BSP layer.
 *       - MEMC_OFF
 *       - MEMC_CINEMA_CLEAR (Blur value 3 and Judder value 3)
 *       - MEMC_NATUREAL (Blur value 5 and Judder value 5)
 *       - MEMC_SMOOTH (Blur value 7 and Judder value 7)
 *       - MEMC_USER (Blur value and Judder value are user specific)
 *       - MEMC_PULLDOWN_55 (Blur value 0 and Judder value 0)
 *       - MEMC_SMALL_OBJ (Blur value and Judder value are from webOS)
 *
 *      At the level of MEMC_OFF, the MEMC function should be turned off.
 *      At the level of MEMC_CINEMA_CLEAR, the Blur value 3 and the Judder value 3
 *      are passed with the MEMC level. De-judder 3 and De-blur 3 should be applied.
 *      At the level of MEMC_TYPE_NATUREAL, the Blur value 5 and the Judder value 5
 *      are passed with the MEMC level. De-judder 5 and De-blur 5 should be applied.
 *      At the level of MEMC_TYPE_SMOOTH, the Blur value 7 and the Judder value 7
 *      are passed with the MEMC level. De-judder 7 and De-blur 7 should be applied.
 *      At the level of MEMC_TYPE_USER, the specific Blur value and the Judder value
 *      are passed with the MEMC level. the judder and blur levels should be applied
 *      with the passed values. At the level of MEMC_PULLDOWN_55, the Blur value 0 and
 *      the Judder value 0 are passed with the MEMC level. In this case, On 5:5 Pull-down
 *      for 24Hz Film source should be applied. MEMC_TYPE_SMALL_OBJ is a new enum that
 *      needs to be added. It applies MEMC tuning for small object. The VIDIOC_S_EXT_CTRLS
 *      is used for setting data and the VIDIOC_G_EXT_CTRLS is used for getting data.
 *   - Target Hardware Block
 *      MEMC Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEMC_MOTION_COMP
 *
 *     //
 *     // parameter
 *     //
 *     // MEMC Type Definition
 *     enum v4l2_ext_memc_type_old {
 *         V4L2_EXT_MEMC_TYPE_OFF = 0,
 *         V4L2_EXT_MEMC_TYPE_LOW,
 *         V4L2_EXT_MEMC_TYPE_HIGH,
 *         V4L2_EXT_MEMC_TYPE_USER,
 *         V4L2_EXT_MEMC_TYPE_55_PULLDOWN,
 *         V4L2_EXT_MEMC_TYPE_MEDIUM,
 *         V4L2_EXT_MEMC_TYPE_OLD_MAX
 *     };
 *     enum v4l2_ext_memc_type {
 *         V4L2_EXT_MEMC_OFF          = V4L2_EXT_MEMC_TYPE_OFF,
 *         V4L2_EXT_MEMC_CINEMA_CLEAR = V4L2_EXT_MEMC_TYPE_MEDIUM,
 *         V4L2_EXT_MEMC_NATURAL      = V4L2_EXT_MEMC_TYPE_LOW,
 *         V4L2_EXT_MEMC_SMOOTH       = V4L2_EXT_MEMC_TYPE_HIGH,       //
 *         V4L2_EXT_MEMC_USER         = V4L2_EXT_MEMC_TYPE_USER,
 *         V4L2_EXT_MEMC_PULLDOWN_55  = V4L2_EXT_MEMC_TYPE_55_PULLDOWN,
 *         V4L2_EXT_MEMC_SMALL_OBJ    = V4L2_EXT_MEMC_TYPE_OLD_MAX
 *     };
 *     struct v4l2_ext_memc_motion_comp_info {
 *         unsigned char blur_level;
 *         unsigned char judder_level;
 *         enum v4l2_ext_memc_type memc_type;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       IF motion = V4L2_EXT_MEMC_TYPE_OFF
 *           OFF memc
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_CINEMA_CLEAR
 *           Set De-judder 3, De-blur 3
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_NATURAL
 *           Set De-judder 5, De-blur 5
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_SMOOTH
 *           Set De-judder 7, De-blur 7
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_USER
 *           Set blurLevel to blur_level    //50,60Hz 1:1 source
 *           Set JudderLevel to judder_level    //24,25,30Hz 1:1 source and 50, 60Hz pull-down source.
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_55_PULLDOWN
 *           On 5:5 Pull-down for 24Hz Film source
 *       ELSE IF motion = V4L2_EXT_MEMC_TYPE_OLD_MAX
 *           It applies MEMC tuning for small object
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *           RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set MEMC Motion comp
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_memc_motion_comp_info motion_comp_info;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&motion_comp_info, 0, sizeof(v4l2_ext_memc_motion_comp_info));
 *     motion_comp_info.blur_level=blurlevel;
 *     motion_comp_info.judder_level=judderlevel;
 *     motion_comp_info.v4l2_ext_memc_type=memctype;
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_memc_motion_comp_info);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&motion_comp_info;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_MEMC_MOTION_COMP;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_MEMC_MOTION_COMP (V4L2_CID_EXT_MEMC_BASE + 2)

/**
 * @brief
 *   Defines the Control ID to set/get the control of Motion Pro.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting the controls of Motion Pro.
 *   - Details of Feature
 *      Motion Pro makes video clearer by eliminating afterimgages.
 *      If Motion Pro enables, then the BFI(Black Frame Insertion) function should
 *      be working. On the other hand, if Motion Pro diables, the the BFI function
 *      should be stop working. The VIDIOC_S_CTRL is used for setting data and the
 *      VIDIOC_G_CTRL  is used for getting data.
 *   - Target Hardware Block
 *      MEMC Blcok
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEMC_MOTION_PRO
 *
 *     //
 *     // parameter
 *     //
 *     bMotionPro[IN] bool
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              IF bMotionPro= TRUE
 *                        Enable BFI Function
 *              ELSE
 *                        Disable BFI Function
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     memset(&control, 0, sizeof(v4l2_control));
 *     control.id = V4L2_CID_EXT_MEMC_MOTION_PRO;
 *     control.value = true;
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_MEMC_MOTION_PRO (V4L2_CID_EXT_MEMC_BASE + 3)

#define V4L2_CID_EXT_HDR_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x200)

/**
 * @brief
 *   Set inverse gamma on/off
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *
 *   Not Use
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_INV_GAMMA (V4L2_CID_EXT_HDR_BASE + 0)

/**
 * @brief
 *   Get histogram in front of hdr block
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting hdr block histogram
 *   - Details of Feature
 *      Get histogram in front of hdr block. Detailed information about
 *      histogram is discussed with the PQ team.
 *   - Target Hardware Block
 *      HDR Block
 *   - Call frequency and timing
 *      every 30ms after pq starts
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get Pic info
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_HDR_PIC_INFO
 *
 *     //
 *     // parameter
 *     //
 *     #define V4L2_EXT_HDR_PICINFO_SIZE 128
 *     unsigned int picInfo[V4L2_EXT_HDR_PICINFO_SIZE];
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         //GET  RGB max histogram
 *         unsigned int pstPicInfo[V4L2_EXT_HDR_PICINFO_SIZE]
 *         memcpy(p_data->picInfo, pstPicInfo, sizeof(pstPicInfo));
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get hdr picture info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     unsigned int hdrPicInfo[V4L2_EXT_HDR_PICINFO_SIZE];
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version = 1;
 *     pqData.length = sizeof(hdrPicInfo);
 *     pqData.wId = 0;
 *     pqData.p_data = (char*)hdrPicInfo;
 *     ext_control.id = V4L2_CID_EXT_HDR_PIC_INFO;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_PIC_INFO (V4L2_CID_EXT_HDR_BASE + 1)

/**
 * @brief
 *   Set Tone Mapping Look up table(3D LUT) in HDR Block
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Tone Mapping 3D LUT
 *   - Details of Feature
 *      Set Tone Mapping Look up table(3D LUT) in HDR Block. LUT size can be
 *      changed by SoC spec. hdr type of current video(check enum
 *      v4l2_ext_hdr_mode) and 3D LUT pointer will be send to
 *      v4l2_ext_hdr_3dlut which are described in below parameter section.
 *   - Target Hardware Block
 *      HDR block
 *   - Call frequency and timing
 *      Call this API per 30ms. But if the data of parameter is same as
 *      previous call, call will be skipped.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDR_3DLUT
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdr_mode {
 *         V4L2_EXT_HDR_MODE_SDR,
 *         V4L2_EXT_HDR_MODE_DOLBY,
 *         V4L2_EXT_HDR_MODE_HDR10,
 *         V4L2_EXT_HDR_MODE_HLG,
 *         V4L2_EXT_HDR_MODE_TECHNICOLOR,
 *         V4L2_EXT_HDR_MODE_HDREFFECT,
 *         V4L2_EXT_HDR_MODE_MAX
 *     };
 *     struct v4l2_ext_hdr_3dlut {
 *         enum v4l2_ext_hdr_mode hdr_mode;
 *         union {
 *             unsigned short *p3dlut; ///< p_data
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         SET HDR 3D LUT
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set HDR 3D LUT
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_hdr_3dlut st3dlut;
 *     static unsigned short u3DLUT[3DLUT_SIZE] = {0,};
 *     unsinged int u3dlut_size = sizeof(u3DLUT);
 *     Get3DLUT(u3DLUT);
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&st3dlut, 0, sizeof(v4l2_ext_hdr_3dlut));
 *     st3dlut.hdr_mode = V4L2_EXT_HDR_MODE_HDR10;
 *     st3dlut.data_size = u3dlut_size;
 *     st3dlut.p3dlut = &u3DLUT[0];
 *     pqData.version=1;
 *     pqData.length = sizeof(st3dlut);
 *     pqData.wId=0;
 *     pqData.p_data = (char*)st3dlut;
 *     ext_control.id = V4L2_CID_EXT_HDR_3DLUT;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_3DLUT (V4L2_CID_EXT_HDR_BASE + 2)

/**
 * @brief
 *   Set EOTF data table
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *
 *   Not Use
 *
 * @endrst

 */
#define V4L2_CID_EXT_HDR_EOTF (V4L2_CID_EXT_HDR_BASE + 3)

/**
 * @brief
 *   Set OETF data table
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *
 *   Not Use
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_OETF (V4L2_CID_EXT_HDR_BASE + 4)

/**
 * @brief
 *   Set Tone Mapping data table
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting 1D Tone Mapping data table
 *   - Details of Feature
 *      The function set Tone Mapping data table for HDR.
 *   - Target Hardware Block
 *      HDR block
 *   - Call frequency and timing
 *      Call this API per 30ms. But if the data of parameter is same as
 *      previous call, call will be skipped.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   LUT size can be changed by SoC spec
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_HDR_TONEMAP
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdr_mode {
 *         V4L2_EXT_HDR_MODE_SDR,
 *         V4L2_EXT_HDR_MODE_DOLBY,
 *         V4L2_EXT_HDR_MODE_HDR10,
 *         V4L2_EXT_HDR_MODE_HLG,
 *         V4L2_EXT_HDR_MODE_TECHNICOLOR,
 *         V4L2_EXT_HDR_MODE_HDREFFECT,
 *         V4L2_EXT_HDR_MODE_MAX
 *     };
 *     struct v4l2_ext_hdr_tonemap {
 *         enum v4l2_ext_hdr_mode hdr_mode;
 *         unsigned int r_data[66]; ///<0~4294967295, 33point x,y data
 *         unsigned int g_data[66]; ///<0~4294967295, 33point x,y data
 *         unsigned int b_data[66]; ///<0~4294967295, 33point x,y data
 *     };
 *
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set HDR Tone Mapping
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     v4l2_ext_hdr_tonemap stToneMapData;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_CMN_DATA_T));
 *     memset(&stToneMapData, 0, sizeof(HAL_VPQ_HDR_TONEMAP_T));
 *     stToneMapData.hdrMode = HAL_VPQ_HDR_MODE_HDR10;
 *     memcpy(stToneMapData.uRdata, toneMapLUT, sizeof(unsigned int)*66);
 *     memcpy(stToneMapData.uGdata, toneMapLUT, sizeof(unsigned int)*66);
 *     memcpy(stToneMapData.uBdata, toneMapLUT, sizeof(unsigned int)*66);
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(HAL_VPQ_HDR_TONEMAP_T);
 *     pqData.wId=0;
 *     pqData.pData=(char*)&stToneMapData;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_HDR_TONEMAP;
 *     ext_control.ptr = (void *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_TONEMAP (V4L2_CID_EXT_HDR_BASE + 5)

/**
 * @brief
 *   Control hue shift & saturation compensation block
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for controlling hue shift & saturation compensation block
 *   - Details of Feature
 *      This function controls hue shift & saturation compensation block for
 *      HDR. LUT size can be changed by SoC spec
 *   - Target Hardware Block
 *      HDR block
 *   - Call frequency and timing
 *      UI change about Color Correction. Dynamic Contrast, Dynamic Tone
 *      Mapping
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDR_COLOR_CORRECTION
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdr_color_correction {
 *         unsigned int hue_blend; ///< 0~1023
 *         unsigned int sat_blend; ///< 0~1023
 *         unsigned int l_gain_x[8]; // L gain LUT x point
 *         unsigned int l_gain_y[8]; // L gain LUT y point
 *         unsigned int s_gain_x[8]; // S gain LUT x point
 *         unsigned int s_gain_y[8]; // S gain LUT y point
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set HDR Color Correction
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_hdr_color_correction stColorCorrectionData;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_CMN_DATA_T));
 *     memset(&stColorCorrectionData, 0, sizeof(v4l2_ext_hdr_color_correction));
 *     stColorCorrectionData.uHueBlend = 240;
 *     stColorCorrectionData.uSatBlend = 512;
 *     stColorCorrectionData.uLgainx[8] = {0, 5000, 10000, 15000, 20000, 25000, 30000, 65535};
 *     stColorCorrectionData.uLgainy[8] = {255, 255, 255, 255, 255, 255, 255, 255};
 *     stColorCorrectionData.uSgainx[8] = {0, 5000, 10000, 15000, 20000, 25000, 30000, 65535};
 *     stColorCorrectionData.uSgainy[8] = {255, 255, 255, 255, 255, 255, 255, 255};
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_hdr_color_correction);
 *     pqData.wId = 0;
 *     pqData.p_data = (char*)&stColorCorrectionData;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_HDR_COLOR_CORRECTION;
 *     ext_control.ptr = (void *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_COLOR_CORRECTION (V4L2_CID_EXT_HDR_BASE + 6)

/**
 * @brief
 *   Set HLG Y Gain table
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting HLG Y Gain table
 *   - Details of Feature
 *      The function set Y Gain for HLG.
 *      Data is unsigned short array of length 66.
 *      Array index 0~32 is x axis.
 *      Array index 33~65 is y axis.
 *   - Target Hardware Block
 *      HDR block
 *   - Call frequency and timing
 *      videoInfo changed
 *
 * Responses to abnormal situations, including
 *   if video signal is not HLG, bsp should set error
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HLG_Y_GAIN_TBL
 *
 *     //
 *     // parameter
 *     //
 *     unsigned short uYgaindata[V4L2_EXT_HDR_HLG_YGAIN_TBL_SIZE]
 *     #define V4L2_EXT_HDR_HLG_YGAIN_TBL_SIZE 66
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set HLG Curve Table
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     unsigned short uYgaindata[V4L2_EXT_HDR_HLG_YGAIN_TBL_SIZE] = {0, };
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_CMN_DATA_T));
 *     GetYgainData(uYgaindata);
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(uYgaindata);
 *     pqData.wId = 0;
 *     pqData.p_data=(char*) uYgaindata;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_HLG_Y_GAIN_TBL;
 *     ext_control.ptr = (char *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL (V4L2_CID_EXT_HDR_BASE + 7)

/**
 * @brief
 *   Set Local Tone Mapping data structure
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      To set local Tone Mapping processing on each 8x6 local blocks.
 *      Conventional TM has been processed using global one TM curve based on a peak of a scene.
 *      New Local TM is processed using local peak and local TM curve(8x6 local peaks are matched with 8x6 local block region)
 *   - Details of Feature
 *      This data structure including below members sets for Local Tone Mapping processing
 *      1) LocalDTM_enable : When 1, local DTM processing. When 0, conventional global 1 TM processing
 *      2) LocalDTM_PeakPercentile : percent threshold to decide peak value on each local block histogram
 *      3) LocalDTM_ToneIdx[12] : peak index for seperating 12 TM LUTs
 *      4) LocalDTM_1D_LUT[12][33] : 33 point 1D TM LUT of 12 sets --> concept of gain table to be used in synthesis with 1D TM LUT
 *   - Target Hardware Block
 *      HDR block
 *   - Call frequency and timing
 *      Call this API per 30ms. But if the data of parameter is same as
 *      previous call, call will be skipped.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   Local DTM HW must be implemented in HDR block
 *   Local DTM HW consists of Local block histogram module, calculation module for block peak,
 *   block peak interpolation module and Locally RGB TM processing module
 *   This structure only works when the Local DTM enable bit = 1
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_HDR_LOCAL_TONEMAP
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdr_local_tonemap {
 *         unsigned int local_dtm_enable;               // Local DTM enable bit
 *         unsigned int local_dtm_peak_per;             // Local DTM percentage for deciding local peak
 *         unsigned int local_dtm_tone_idx[12];         // Local DTM peak index for each curve LUT
 *         unsigned int local_dtm_tone_lut[12][33];     // Local DTM curve LUT(Concept of gain table for synthesis with 1D TM LUT)
 *     };
 *
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set HDR Local DTM
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     v4l2_ext_hdr_local_tonemap stLocalToneMapData;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_LOCALDTM_DATA_T));
 *     memset(&stLocalToneMapData, 0, sizeof(HAL_VPQ_HDR_LOCALTONEMAP_T));
 *     memcpy(stLocalToneMapData.local_dtm_enable, localDTM_enable_bit, sizeof(unsigned int));
 *     memcpy(stLocalToneMapData.local_dtm_peak_per, localDTM_peak_per, sizeof(unsigned int));
 *     memcpy(stLocalToneMapData.local_dtm_tone_idx, localtoneMapIdx, sizeof(unsigned int)*12);
 *     memcpy(stLocalToneMapData.local_dtm_tone_lut, localtoneMapLUT, sizeof(unsigned int)*12*33);
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(HAL_VPQ_HDR_LOCALTONEMAP_T);
 *     pqData.wId=0;
 *     pqData.pData=(char*)&stToneMapData;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_HDR_LOCAL_TONEMAP;
 *     ext_control.ptr = (void *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDR_LOCAL_TONEMAP (V4L2_CID_EXT_HDR_BASE + 8)

#define V4L2_CID_EXT_DOLBY_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x300)

/**
 * @brief
 *   Set path of Dolby Picture configuration file
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting path of Dolby Picture configuration file
 *   - Details of Feature
 *      Set path of Dolby Picture configuration file to dolby vision module.
 *      V4L2_EXT_DOLBY_CONFIG_MAIN = primary, V4L2_EXT_DOLBY_CONFIG_BEST = for
 *      calibration data. only working on Dolby Vision input. If there is no
 *      problem on setting the path, BSP should set configuration using
 *      parameters on the file.
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      Once on each TV config init and Events about cfg file(update and also)
 *
 * Responses to abnormal situations, including
 *   if file cannot be read on the path, set error.
 *   if video signal is not Dolby Vision, set error.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_CFG_PATH
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_dolby_config_type{
 *         V4L2_EXT_DOLBY_CONFIG_MAIN = 0,
 *         V4L2_EXT_DOLBY_CONFIG_BEST
 *     }
 *     struct v4l2_ext_dolby_config_path{
 *         enum v4l2_ext_dolby_config_type eConfigType;
 *         char sConfigPath[255];
 *     }
 *     v4l2_ext_dolby_config_path configFilePath [IN]
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *     SET path of Dolby Picture configuration
 *     return;
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_ext_dolby_config_path stConfigPathMain;
 *     v4l2_ext_dolby_config_path stConfigPathBest;
 *     #define DOLBY_MAIN "primary.cfg"
 *     #define DOLBY_BEST "best.cfg"
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     stConfigPathMain.eConfigType = V4L2_EXT_DOLBY_CONFIG_MAIN;
 *     strcpy(stConfigPathMain.sConfigPath, DOLBY_MAIN);
 *     pqData.version=1;
 *     pqData.length = sizeof(stConfigPathMain);
 *     pqData.wId=0;
 *     pqData.pData= (char*)stConfigPathMain;
 *     ext_control.id = V4L2_CID_EXT_DOLBY_CFG_PATH;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_CFG_PATH (V4L2_CID_EXT_DOLBY_BASE + 0)

/**
 * @brief
 *   Set Dolby HDR On/Off and Dolby Picture Mode
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Dolby HDR On/Off and Dolby Picture Mode
 *   - Details of Feature
 *      Set Dolby HDR On/Off and Dolby Picture Mode.
 *      only working on Dolby Vision input.
 *
 *      uPictureMode = 0 ; //CINEMA,
 *
 *      uPictureMode = 1 ; //CINEMA_HOME(CINEMA_BRIGHT),
 *
 *      uPictureMode = 2 ; //VIVID,
 *
 *      uPictureMode = 3 ; //STANDARD,
 *
 *      uPictureMode = 4 ; //GAME,
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      if Dolby Picture Mode changed after each setPQ
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_PICTURE_MODE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_dolby_picture_mode[IN]
 *     struct v4l2_ext_dolby_picture_mode{
 *         unsigned int bOnOff;
 *         unsigned int uPictureMode;
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         IF bOnOff == ON
 *             IF uPictureMode == VIVID
 *                 Set Dolby HDR VIVID picture mode
 *             Else IF uPictureMode == CINEMAHOME
 *                 Set Dolby HDR CINEMAHOME picture mode
 *             Else IF uPictureMode == CINEMA
 *                 Set Dolby HDR CINEMA picture mode
 *             Else IF uPictureMode == STANDARD
 *                 Set Dolby HDR STANDARD picture mode
 *             Else IF uPictureMode == GAME
 *                 Set Dolby HDR GAME picture mode
 *         ELSE
 *             Not Set
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_dolby_picture_mode stDolbyPictureMode;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&stDolbyPictureMode, 0, sizeof(v4l2_ext_dolby_picture_mode));
 *     if(dolby vision)
 *     {
 *          stDolbyPictureMode.bOnOff = 1;
 *          stDolbyPictureMode.uPictureMode = currentPictureMode;
 *     }
 *     else
 *     {
 *          stDolbyPictureMode.bOnOff = 0;
 *     }
 *     pqData.version = 1;
 *     pqData.length = sizeof(v4l2_ext_dolby_picture_mode);
 *     pqData.wId = 0;
 *     pqData.pData=(char*)&stDolbyPictureMode;
 *     ext_control.id = V4L2_CID_EXT_DOLBY_PICTURE_MODE;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_PICTURE_MODE (V4L2_CID_EXT_DOLBY_BASE + 1)

/**
 * @brief
 *   Set Dolby HDR On/Off and Picture Menu value
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Dolby HDR On/Off and Picture Menu value
 *   - Details of Feature
 *      Set Dolby HDR On/Off and Picture Menu value(Backlight, Brightness,
 *      Color, Contrast). if set On for each menu value, dolby control menu
 *      value. Currently, this API only set Backlight value which is required
 *      by Dolby Vision SDK. only working on Dolby Vision input.
 *
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      if input is Dolby Vision on each setPQ
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_PICTURE_MENU
 *
 *     //
 *     // parameter
 *     //
 *     v4l2_ext_dolby_picture_data pictureData [IN]
 *
 *     //  dolby picture menu
 *     enum v4l2_ext_dolby_picture_menu {
 *         V4L2_EXT_DOLBY_BACKLIGHT = 0,   ///< backlight
 *         V4L2_EXT_DOLBY_BRIGHTNESS,      /// brightness
 *         V4L2_EXT_DOLBY_COLOR,           ///< color
 *         V4L2_EXT_DOLBY_CONTRAST,        ///< contrast
 *         V4L2_EXT_DOLBY_PICTURE_MENU_MAX ///< max num
 *     };
 *
 *     // dolby picture menu data
 *     struct v4l2_ext_dolby_picture_data {
 *         enum v4l2_ext_dolby_picture_menu picture_menu; ///< picture menu
 *         unsigned int on_off;                           ///<0:off, 1:on
 *         int setting_value;                             ///< setting value
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         IF pictureData.pictureMenu == V4L2_EXT_DOLBY_BACKLIGHT THEN
 *             IF bOnOff == ON
 *                 Set DolbyBacklight value to pictureData.nValue.
 *             ELSE
 *                 Not Set
 *         ELSE IF pictureData.pictureMenu == V4L2_EXT_DOLBY_BRIGHTNESS THEN
 *             IF bOnOff == ON
 *                 Set DolbyBrightness value to pictureData.nValue.
 *             ELSE
 *                 Not Set
 *         ELSE IF pictureData.pictureMenu == V4L2_EXT_DOLBY_COLOR THEN
 *             IF bOnOff == ON
 *                 Set DolbyColor value to pictureData.nValue.
 *             ELSE
 *                 Not Set
 *         ELSE IF pictureData.pictureMenu ==V4L2_EXT_DOLBY_CONTRAST THEN
 *             IF bOnOff == ON
 *                 Set DolbyContrast value to pictureData.nValue.
 *             ELSE
 *                 Not Set
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_ext_dolby_picture_data stPicData;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&stPicData, 0, sizeof(v4l2_ext_dolby_picture_data));
 *     stPicData.pictureMenu = V4L2_EXT_DOLBY_BACKLIGHT;
 *     stPicData.onoff = 1;
 *     stPicData.value = uBacklightValue;
 *     pqData.version = 1;
 *     pqData.length = sizeof(v4l2_ext_dolby_picture_data );
 *     pqData.wId = 0;
 *     pqData.pData=(char*)&stPicData;
 *     ext_control.id = V4L2_CID_EXT_DOLBY_PICTURE_MENU;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_PICTURE_MENU (V4L2_CID_EXT_DOLBY_BASE + 2)

/**
 * @brief
 *   Get dolby software version
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting dolby SW version
 *   - Details of Feature
 *      Get dolby software version. If Dolby SW Version string is null, return
 *      NOT_OK. this function should be worked even if input is not Dolby
 *      Vision.
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      when Dolby Vision Version is needed(according to UI scenario).
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get Dolby Version
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_SW_VERSION
 *
 *     //
 *     // parameter
 *     //
 *     char cDolbyVersion[128]
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         char * pVersion =  (char *)control.value;
 *         char cVersion[128];
 *         GET Dolby SW Version
 *         memcpy(pVersion, cVersion, sizeof(char)*128);
 *
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Dolby SW Version
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     char cDolbyVersion[128] = {0,};
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version=1;
 *     pqData.length = sizeof(pcDolbyVersion);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)cDolbyVersion;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DOLBY_SW_VERSION;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *     return cDolbyVersion;
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_SW_VERSION (V4L2_CID_EXT_DOLBY_BASE + 3)

/**
 * @brief
 *   Pass the dimming info
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for passing dimming information (energy saving / backlight ratio)
 *   - Details of Feature
 *      This function passes the backlight dimming information including
 *      energy saving / backlight ratio. Dolby PWM multiplies this ratio and
 *      outputs the brightness. only working on Dolby Vision input. This
 *      function is not using on OLED models.
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      Call this API per 30ms.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_PWM_RATIO
 *
 *     //
 *     // parameter
 *     //
 *     type               [IN] UINT8
 *     UINT8 u8Percent;
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Dolby Backlight output  = Dolby PWM x u8Percent/100
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
  *        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Dolby Pwm Ratio
 *     struct v4l2_control control;
 *     UINT8 u8Percent;
 *     //Calculate PWM ratio
 *     u8Percent = (PWM ratio)
 *     memset(&control, 0, sizeof(v4l2_control));
 *     control.id = V4L2_CID_EXT_DOLBY_PWM_RATIO;
 *     control.value = u8Percent;
 *     ioctl(fd, VIDIOC_S_CTRL, &controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_PWM_RATIO (V4L2_CID_EXT_DOLBY_BASE + 4)

/**
 * @brief
 *   Set delay table value
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting delay table value
 *   - Details of Feature
 *      Set different Global Dimming Delay values according to frame
 *      rate(24Hz, 30Hz, 50hz, 60Hz), input(HDMI, OTT), Picture Mode(Vivid,
 *      Standard, Cinema, Cinema Home, Game) and Dolby Vision Latency Mode.
 *      only working on Dolby Vision input
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      Once on TV power ON and Events about cfg file(update and also)
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ info
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_GD_DELAY
 *
 *     //
 *     // parameter
 *     //
 *     // dolby global dimming delay data
 *     struct v4l2_ext_dolby_gd_delay
 *     {
 *         unsigned short ott_24;
 *         unsigned short ott_30;
 *         unsigned short ott_50;
 *         unsigned short ott_60;
 *         unsigned short ott_100; // not using now
 *         unsigned short ott_120; // not using now
 *         unsigned short hdmi_24;
 *         unsigned short hdmi_30;
 *         unsigned short hdmi_50;
 *         unsigned short hdmi_60;
 *         unsigned short hdmi_100; // not using now
 *         unsigned short hdmi_120; // not using now
 *     };
 *     struct v4l2_ext_dolby_gd_delay_lut
 *     {
 *         struct v4l2_ext_dolby_gd_delay standard_frc_off;
 *         struct v4l2_ext_dolby_gd_delay standard_frc_on;
 *         struct v4l2_ext_dolby_gd_delay vivid_frc_off;
 *         struct v4l2_ext_dolby_gd_delay vivid__frc_on;
 *         struct v4l2_ext_dolby_gd_delay cinema_home_frc_off;
 *         struct v4l2_ext_dolby_gd_delay cinema_home_frc_on;
 *         struct v4l2_ext_dolby_gd_delay cinema_frc_off;
 *         struct v4l2_ext_dolby_gd_delay cinema_frc_on;
 *         struct v4l2_ext_dolby_gd_delay game_frc_off;
 *         struct v4l2_ext_dolby_gd_delay game_frc_on;
 *     };
 *     struct v4l2_ext_dolby_gd_delay_param
 *     {
 *         struct v4l2_ext_dolby_gd_delay_lut dolby_GD_standard;
 *         struct v4l2_ext_dolby_gd_delay_lut dolby_GD_latency;
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This V4L2 is only for model supporting Dolby Vision.
 *
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set standard/latency delay table
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Dolby GD Delay
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_datapqData;
 *     v4l2_dolby_gd_delay_param dolbyGDVal;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&dolbyGDVal, 0, sizeof(v4l2_dolby_gd_delay_param));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_dolby_gd_delay_param);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&dolbyGDVal;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DOLBY_GD_DELAY;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_GD_DELAY (V4L2_CID_EXT_DOLBY_BASE + 5)

/**
 * @brief
 *   Setting on/off flag and sensor raw data and lux data
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting on/off flag and lux data(LG calculated) and sensor raw
 *      data
 *   - Details of Feature
 *      Correct the illuminance based picture quality of the viewing
 *      environment(Dolby tone mapping by sensor). only working on Dolby
 *      Vision input
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      Call this API per 30ms.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ info
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT
 *
 *     //
 *     // parameter
 *     //
 *     // dolby ambient light param
 *     struct v4l2_ext_dolby_ambient_light_param
 *     {
 *       unsigned int onoff;
 *       unsigned int luxdata;
 *       union {
 *         unsigned int *rawdata; ///< p_data
 *         unsigned int compat_data;
 *         unsigned long long sizer;
 *       };
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This V4L2 is only for model supporting Dolby Vision.
 *
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Check On/Off flag
 *         IF On status
 *             Set sensor raw data and lux data.
 *
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Dolby Ambient Light
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_dolby_ambient_light_param dolbyAmbientLight;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&dolbyGDVal, 0, sizeof(v4l2_dolby_ambient_light_param));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_dolby_ambient_light_param);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&dolbyAmbientLight;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT (V4L2_CID_EXT_DOLBY_BASE + 6)

/**
 * @brief
 *   Get the Dolby Vision contents type metadata
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting the Dolby Vision contents type metadata
 *   - Details of Feature
 *      This function is used to get the Dolby Vision contents type metadata
 *      (L11 contents-aware metadata), including content type and intended
 *      white point. only working on Dolby Vision input
 *
 *      .. image:: /picturequality/resources/pq-V4L2_CID_EXT_DOLBY_CONTENTS_TYPE.png
 *   - Target Hardware Block
 *      Dolby block
 *   - Call frequency and timing
 *      Call this API per 500ms.
 *
 * Responses to abnormal situations, including
 *   If this function is not called, BSP must operate at its default value.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_CONTENTS_TYPE
 *
 *     //
 *     // parameter
 *     //
 *     unsigned char contentType[4];
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This V4L2 is only for model supporting Dolby Vision.
 *
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         //GET  Dolby Content Type
 *         unsigned char contentType[4] = {?,?,?,?};
 *         memcpy(vpq_cmn_data->p_data, contentType, sizeof(contentType));
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Dolby Content Type
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     unsigned char apoType[4] = {0,};
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version = 1;
 *     pqData.length = sizeof(apoType);
 *     pqData.wId = 0;
 *     pqData.p_data = (char*)apoType;
 *     ext_control.id = V4L2_CID_EXT_DOLBY_CONTENTS_TYPE;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *     contentType = apoType[0]&0x0F;
 *     intendedWhitePoint = apoType[1]&0x0F;
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_CONTENTS_TYPE (V4L2_CID_EXT_DOLBY_BASE + 7)

/**
 * @brief
 *   Set the Dolby Precision Rendering on/off
 *
 * @rst
 * Functional Requirements
 *   This function enable Dolby HW5 Precision Rendering.
 *
 *   - Purpose
 *      set Dolby HW5 Precision Rendering.
 *   - Details of Feature
 *      This function enable Dolby HW5 Precision Rendering. only working on
 *      Dolby Vision input
 *   - Target Hardware Block
 *      Dolby HW5 Precision Rendering block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will
 *      not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DOLBY_PD_CTRL
 *
 *     //
 *     // parameter
 *     //
 *     int ctrl;  // (0:off, 1:on)
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This V4L2 is only for model supporting Dolby Vision.
 *
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         set V4L2 Dolby Precision Detail On/Off
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
  *        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Dolby Precision Detail
 *     struct v4l2_control control;
 *     int ctrl; // 1:on, 0:off
 *     memset(&control, 0, sizeof(v4l2_control));
 *     control.id = V4L2_CID_EXT_DOLBY_PD_CTRL;
 *     control.value = ctrl;
 *     ioctl(fd, VIDIOC_S_CTRL, &controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_DOLBY_PD_CTRL (V4L2_CID_EXT_DOLBY_BASE + 8)

#define V4L2_CID_EXT_VPQ_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x400)

/**
 * @brief
 *  Defines the Control ID to initialize the VPQ(Video Picture Quality) module.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for initializing the VPQ module.
 *   - Details of Feature
 *      All the VPQ related functions must be called after initialization of the
 *      VPQ module. It calls the library functions of chip vendor for
 *      initialization and initializes the global variables for VPQ operations.
 *   - Target Hardware Block
 *      PQ Block
 *   - Call frequency and timing
 *      It is called once when the system is power on.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There sould be no performance degration.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_INIT
 *
 *     //
 *     // parameter
 *     //
 *     - true : initializing
 *     - false : de-initializing (for future use)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_INIT (V4L2_CID_EXT_VPQ_BASE + 0)

/**
 * @brief
 *   Defines the Control ID to set/get the picture controls.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting the picture controls.
 *   - Details of Feature
 *      The picture controls such as contrast, brightness, color and tint
 *      are set by this Control ID. Each corresponding UI(User Interface) values
 *      of the picture controls are passed with this Control ID. The sPcVal
 *      values in Example code below are the UI setting values ( LG UI : Contrast, Black Level, 
 *      Color Depth, Tint). The sContrast, sBrightness, sSaturation and sHue
 *      values in Example code below are tunning data made by LG.
 *      The value range of sContrast and sBrightness is 0 ~ 1023.
 *      And the value range of sSaturation and sHue is 0 ~ 255.Refer to the Remarks section.
 *      The VIDIOC_S_EXT_CTRLS is used for setting data and the VIDIOC_G_EXT_CTRLS
 *      is used for getting data.
 *   - Target Hardware Block
 *      PQ Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_PICTURE_CTRL
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_picture_ctrl_data{
 *      signed int sPcVal[4];
 *      signed int sContrast;
 *      signed int sBrightness;
 *      signed int sSaturation;
 *      signed int sHue;
 *     };
 *   Description of UI Params
 *      Basic VPQ UI
 *       + Value of Contrast/Brightness/Saturation/Hue in UI
 *       + sPcVal[0] Contrast ( LG UI : Adjust Contrast ) : 0 ~ 100
 *       + sPcVal[1] Brightness ( LG UI : Black Level ) : 0 ~ 100
 *       + sPcVal[2] Saturation ( LG UI : Color Depth ) : 0 ~ 100
 *       + sPcVal[3] Hue ( LG UI : Tint ) : -50 ~ 50 ( R50 ~ G50 )
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.

 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input Parameters
 *       SET appropriate data on the structure with sample data
 *
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_picture_ctrl_data pictureCtrl;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&pictureCtrl, 0, sizeof(v4l2_picture_ctrl_data));
 *     pictureCtrl.sPcVal[0] = contrastUiValue;
 *     pictureCtrl.sPcVal[1] = brightnessUiValue;
 *     pictureCtrl.sPcVal[2] = colorUiValue;
 *     pictureCtrl.sPcVal[3] = tintUiValue;
 *     pictureCtrl.sContrast = contrastVal;
 *     pictureCtrl.sBrightness= brightnessVal;
 *     pictureCtrl.sSaturation= saturationVal;
 *     pictureCtrl.sHue= hueVal;
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_picture_ctrl_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&pictureCtrl;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_PICTURE_CTRL;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_PICTURE_CTRL (V4L2_CID_EXT_VPQ_BASE + 1)

/**
 * @brief
 *   Set sharpness
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting sharpness
 *   - Details of Feature
 *      Set the value of registers for Sharpness.
 *      Parameter contains UI value and register data pointer.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + The registers will be defined from PQ team. Refer to the "Remarks" section.
 *       + If register data structure is not defined, BSP should work by UI value.
 *      It also pass the additional info.
 *      The info is below.
 *       - sharpnessUiValue : The value of Sharpness UI. The range is 0 ~ 50.
 *       - superResolutionUi : The value of Super Resolution UI. The value are off/low/medium/high(0/1/2/3).
 *       - currentInputInfo : refer to v4l2_ext_vpq_input in videodev2-ext.h
 *       - 360VRMode : on/off 360VR mode
 *   - Target Hardware Block
 *      Sharpness
 *   - Call frequency and timing
 *      1.Periodically called every 30ms
 *      2.When an event such as UI/Input/App change occurs, it may be sent.
 *        But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_SHARPNESS
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_sharpness_data {
 *        unsigned short ui_value[4];
 *        union {
 *          unsigned char *pst_chip_data;
 *          unsigned int compat_data;
 *          unsigned long long sizer;
 *     };
 *     container : v4l2_ext_vpq_cmn_data
 *   Description of UI Params
 *      Sharpness UI Value
 *       + Value of Sharpness in UI.
 *       + ui_value[0] ( Adjust Sharpness ) : 0 ~ 50
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 *   In case of 2-chip struct. AP will use a member "wId" of
 *   struct v4l2_ext_vpq_cmn_data to distinguish it's target chip.
 *
 *   wId : 0 - main chip's main-path
 *
 *   wId : 1 - main chip's sub-path (reserved for future)
 *
 *   wId : 2 - sub chip's main-path
 *
 *   wId : 3 - sub chip's sub-path (reserved for future)
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_sharpness_data sharpness;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_ext_vpq_cmn_data));
 *     memset(&sharpness, 0, sizeof(v4l2_ext_vpq_sharpness_data));
 *     sharpness.ui_value[0] = sharpnessUiValue;
 *     sharpness.ui_value[1] = superResolutionUi;
 *     sharpness.ui_value[2] = currentInputInfo;
 *     sharpness.ui_value[3] = 360VRMode;
 *     sharpness.pst_chip_data = PQL_DB_....();
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_sharpness_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&sharpness;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_SHARPNESS;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_SHARPNESS (V4L2_CID_EXT_VPQ_BASE + 2)

/**
 * @brief
 *   Get histogram data
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Return histogram data of video from SoC
 *   - Details of Feature
 *      Get histogram data of current video from SoC. When this api called, return histogra data.
 *      BSP should provide Y histogram, Saturation histogram, Hue histogram, APL(average picture level)
 *   - Target Hardware Block
 *      Get histogram after Input CSC, before picture enhance(luma enhance, color enhance, etc,...).
 *   - Call frequency and timing
 *      Call this API per 30ms.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get VDO info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_HISTO_DATA
 *
 *     //
 *     // parameter
 *     //
 *     *pHistoInfo         [IN] v4l2_vpq_dc2p_histodata_info
 *     #define HAL_VPQ_BIN_NUM 64
 *     #define HAL_VPQ_C_BIN_NUM 32
 *     #define HAL_VPQ_H_BIN_NUM 32
 *
 *     //
 *     // dc2p histogram data info
 *     //
 *     struct v4l2_ext_vpq_dc2p_histodata_info {
 *         unsigned int apl;                              ///< Average Picture Level
 *         signed int min;                                ///< min : unused
 *         signed int max;                                ///< max : unused
 *         signed int peak_low;                           ///< peak low : unused
 *         signed int peak_high;                          ///< peak high : unused
 *         unsigned int skin_count;                       ///< skin count : unused
 *         unsigned int sat_status;                       ///< saturation status : unused
 *         unsigned int diff_sum;                         ///< diff sum : unused
 *         unsigned int motion;                           ///< motion : LG platform Only
 *         unsigned int texture;                          ///< texture : unused
 *         unsigned int bin[V4L2_EXT_VPQ_BIN_NUM];        ///< Y Histogram, 64 bin
 *         unsigned int chrm_bin[V4L2_EXT_VPQ_C_BIN_NUM]; ///< Chroma Historgram, 32 bin
 *         unsigned int hue_bin[V4L2_EXT_VPQ_H_BIN_NUM];  ///< Saturation 32 bin
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       IF pHistoInfo == NULL THEN
 *           RETURN NOT_OK
 *       END IF
 *       FOR i=0 i < V4L2_VPQ_BIN_NUM
 *           Fill pHistoInfo->bin[i] from chip specific API
 *       END FOR
 *       FOR i=0 i < V4L2_VPQ_C_BIN_NUM
 *           Fill pHistoInfo->chrm_bin[i] from chip specific API
 *       END FOR
 *       FOR i=0 i < V4L2_VPQ_H_BIN_NUM
 *           Fill pHistoInfo->hue_bin[i] from chip specific API
 *       END FOR
 *
 *       Fill pHistoInf->apl from chip specific API
 *       Fill pHistoInf->min from chip specific API(not used)
 *       Fill pHistoInfo->max from chip specific API(not used)
 *       Fill pHistoInfo->peak_low from chip specific API(not used)
 *       Fill pHistoInfo->peak_high from chip specific API(not used)
 *       Fill pHistoInfo->skin_count from chip specific API(not used)
 *       Fill pHistoInfo->sat_statust from chip specific API(not used)
 *       Fill pHistoInfo->diff_sum from chip specific API(not used)
 *       Fill pHistoInfo->motion from chip specific API
 *       Fill pHistoInfo->texure from chip specific API(not used)
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Histo Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_dc2p_histodata_info histdata;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&histdata, 0, sizeof(v4l2_vpq_dc2p_histodata_info));
 *     pqData.version = 1;
 *     pqData.length = sizeof(v4l2_vpq_dc2p_histodata_info);
 *     pqData.p_data =(unsigned char*)&histdata;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_HISTO_DATA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_HISTO_DATA (V4L2_CID_EXT_VPQ_BASE + 3)

/**
 * @brief
 *   Set Contrast(luma, Y) Enhancement control
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *     For setting Dynamic Contrast, Set Contrast(Y) Enhancement control registers.
 *
 *   Details of Feature
 *     Contrast Enahncement H/W can be have control registers and LUT.
 *     This API set control registers.
 *      + Parameter contains UI value and pointer of register data.
 *      + Control registers are different each SoC, need to define data structure for each SoC's register.
 *      + Register data structure should be defined each BSP and application side.
 *      + If register data structure is not defined BSP should work by UI value.
 * 
 *   Target Hardware Block
 *     Contrast(luma, Y) Enhancement control H/W
 *
 *   Call frequency and timing
 *     + This API will be called sevaral times when Input/App changed
 *     + This API be called once when user change Dynamic Contrast UI.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_dynamnic_contrast_ctrl {
 *         unsigned short uDcVal; //UI value of Dynamic contrast
 *         union {
 *             unsigned char *pst_chip_data; // Pointer to data that structure defined for each SoC.
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *   Description of UI Params
 *      Adjust Dynamic Contrast : uDcVal
 *       + Level of Dynamic Contrast in UI
 *       + 0/ 1/ 2/ 3 (off/low/medium/high)
 * 
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input Parameters
 *       DECLARE locally data structures for executing vendor specific chip API
 *       SET appropriate data on the structure with sample data
 *       v4l2_vpq_dc_dynamic_contrast *chipData;
 *       chipData = (v4l2_vpq_dynamic_contrast ) &pstDynamicContrast;
 *       CALL the "vendor-specific chip functions" with that vendor-specific data structure which is declared above
 *       IF any error has occurred THEN
 *         RETURN NOT_OK
 *       END IF
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Dynamic Contrast Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_ext_dynamnic_contrast_ctrl dynamiccontrast;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&dynamiccontrast, 0, sizeof(v4l2_ext_dynamnic_contrast_ctrl));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_dynamnic_contrast_ctrl);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&dynamiccontrast;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST (V4L2_CID_EXT_VPQ_BASE + 4)

/**
 * @brief
 *   Set Contrast(luma, Y) Enhancement LUT(lookup table)
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      For setting Dynamic Contrast, Set Contrast(Y) Enhancement LUT(lookup table).
 *   - Details of Feature
 *      Contrast Enahncement H/W can be have control registers and LUT.
 *      This API set LUT.
 *       + Number of LUT, LUT size are different each SoC, need to define data structure for each SoC's register.
 *       + Register data structure should be defined each BSP and application side.
 *       + Other LUT can be included in data structure if SoC support.
 *        For example, saturation LUT for compenstate color shift by luma LUT.
 *   - Target Hardware Block
 *      Contrast(luma, Y) Enhancement control H/W
 *   - Call frequency and timing
 *      Call this API per 30ms. But if data is same as previous call, skip call.
 *
 * Responses to abnormal situations, including
 *   SoC support this HW but register data structure is not defined yet, just return OK
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   No constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT
 *
 *     //
 *     // parameter
 *     //
 *
 *     // Each SoC should define data structure internally.
 *     // Example
 *     struct v4l2_ext_dynamnic_contrast_lut {
 *         signed int sLumaLutY[MAX_DYNAMIC_CONTRAST_LUT_SIZE];
 *         signed int sLumaLutX[MAX_DYNAMIC_CONTRAST_LUT_SIZE];
 *         unsigned int uSaturationY[MAX_DYNAMIC_CONTRAST_SATURATION_LUT_SIZE];
 *         unsigned int uSaturationX[MAX_DYNAMIC_CONTRAST_SATURATION_LUT_SIZE];
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input Parameters
 *       DECLARE locally data structures for executing vendor specific chip API
 *       SET appropriate data on the structure with sample data
 *         v4l2_vpq_dynamic_contrast_lut  *chipData;
 *       chipData = (v4l2_vpq_dynamic_contrast_lut  ) *pstDynamicContrastLut;
 *       CALL the "vendor-specific chip functions" with that vendor-specific data structure which is declared above
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     #define CHIP_NUM_TRANSCURVE 32 //mstar only 16
 *     // Set Dynamic Contrast LUT
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct v4l2_vpq_dynamnic_contrast_lut{  //application defined structure
 *         lumaLUT_X[33];
 *         lumaLUT_Y[33];
 *     };
 *     struct v4l2_vpq_dynamnic_contrast_lut dynamiccontrastlut =
 *     {
 *          {0	32	64	96	128	160	192	224	256	288	320	352	384	416	448	480	512	544	576	608	640	672	704	736	768	800	832	864	896	928	960	992	1024},
 *          {0	25	40	96	100	130	170	192	230	260	300	330	360	400	430	460	512	560	586	638	670	692	734	776	798	820	832	864	896	928	960	992	1024},
 *     };
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&dynamiccontrast, 0, sizeof(dynamiccontrastlut));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_dynamnic_contrast_lut);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&dynamiccontrastlut;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT (V4L2_CID_EXT_VPQ_BASE + 5)

/**
 * @brief
 *   Set color management parameters
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set color management parameters for control selective colors.
 *   - Details of Feature
 *      Control selective color by input(dtv, hdmi, etc, ..) by UI value.
 *      Parameter contains UI value and register data pointer.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + Register data structure should be defined each side BSP and application(discuss with LG PQ Team).
 *       + If register data structure is not defined or wrong data, BSP should work with UI value only.
 *   - Target Hardware Block
 *      Color Management H/W
 *   - Call frequency and timing
 *      This API will be called sevaral times when Input/App changed
 *      This API be called once when user change Color UI.
 *      If dynamic algorithm enabled, set data per 30ms.
 *
 * Responses to abnormal situations, including
 *   If register data structure is not defined or wrong data, BSP work by UI value.
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VPQ_CM_DB_DATA
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_cm_info {
 *         unsigned char use_internal_cm_db;    // 0: use dbInfo(Data structure defined for each SoC),
 *                                              // 1: use driver internal db by uiInfo(v4l2_ext_cm_ui_status)
 *         struct v4l2_ext_cm_ui_status uiInfo  // UI information for use driver internal data
 *         {
 *             struct v4l2_ext_cm_dynamic_color_ui dynamic {
 *                 unsigned char enable; // 0: disable, 1: enable
 *                 enum v4l2_ext_cm_dynamic_color_level value; // Color Adjustment UI level. enhance selective color(skin, grass, sky).
 *             };
 *             struct v4l2_ext_cm_perferred_color_ui preferred; // not used from webOS 5.0
 *             struct v4l2_ext_cm_cms_ui cms { // Color Management System
 *                 unsigned char enable; // 0: disable, 1: enable
 *                 signed char gain_saturation[V4L2_EXT_CM_CMS_MAX];  // ui value per each color_type
 *                 signed char gain_hue[V4L2_EXT_CM_CMS_MAX];         // ui value per each color_type
 *                 signed char gain_luminance[V4L2_EXT_CM_CMS_MAX];   // ui value per each color_type
 *             };
 *         }
 *         union {
 *             unsigned char *dbInfo;           // Pointer to data that structure defined for each SoC.
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *     //stContainer          [IN]      v4l2_vpq_cmn_data
 *   Description of UI Params
 *      Dynamic color ( Color Adjustment in UI ) : uiInfo.dynamic.value
 *          - 0/ 1/ 2/ 3/ 4 (off/low/medium/high/user)
 *          - if Usermode, User can set additional color setting.
 *      In User selection mode 
 *          + index 0/ 1/ 2/ 3/ 4/ 5 (Red/Green/Blue/Cyan/Magenta/Yellow)
 *          + uiInfo.cms.gain_saturation[] ( Saturation UI ) : -30 ~ 30 (per each color index)
 *          + uiInfo.cms.gain_hue[] ( Hue UI ) : -30 ~ 30 (per each color index)
 *          + uiInfo.cms.gain_luminance[] ( luminance UI ) -30 ~ 30 (per each color index)
 * 
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Change Dynamic Color UI
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer; //PQ common container
 *     struct v4l2_ext_cm_info stRealInfo;     //V4L2_CID_EXT_VPQ_CM_DB_DATA container
 *     struct v4l2_vpq_cm_db stCmDb;           //Each SoC defined structure
 *     struct v4l2_vpq_cm_ui_status
 *       stUiInfo = {{TRUE, V4L2_EXT_CM_DYNAMIC_COLOR_LOW}, {FALSE, {0,0,0}}, {FALSE,{0,},{0,},{0,}};
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.use_internal_cm_db = FALSE;
 *     memset(&stRealInfo.uiInfo , stUiInfo, sizeof(stRealInfo.uiInfo));
 *     stRealInfo.dbInfo = &stCmDb; // stCmDb setting
 *      ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_CM_DB_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 *     // Change Dynamic Color UI, work BSP internal
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer; //PQ common container
 *     struct v4l2_ext_cm_info stRealInfo;     //V4L2_CID_EXT_VPQ_CM_DB_DATA container
 *     struct v4l2_vpq_cm_ui_status stUiInfo = {
 *         {TRUE, V4L2_EXT_CM_DYNAMIC_COLOR_LOW}, {FALSE, {0,0,0}}, {FALSE,{0,},{0,},{0,}
 *     };
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.use_internal_cm_db = TRUE; // use BSP internal setting
 *     memset(&stRealInfo.uiInfo , stUiInfo, sizeof(stRealInfo.uiInfo));
 *     stRealInfo.dbInfo = NULL; // stCmDb setting
 *      ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_CM_DB_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 * @endrst
 */

#define V4L2_CID_EXT_VPQ_CM_DB_DATA (V4L2_CID_EXT_VPQ_BASE + 6)

/**
 * @brief
 *   Set noise reduction
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting noise reduction
 *   - Details of Feature
 *      Set the value of registers for Noise Reduction(Temporal & Spatial Noise).
 *      Parameter contains UI value and register data pointer.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + The registers will be defined from PQ team. Refer to the "Remarks" section.
 *       + If register data structure is not defined, BSP should work by UI value.
 *      It also pass the additional info.
 *      The info is below.
 *       - noiseReductionUiValue : The value of NoiseReduction UI. The value are off/low/medium/high(0/1/2/3).
 *       - currentInputInfo : refer to v4l2_ext_vpq_input in videodev2-ext.h
 *   - Target Hardware Block
 *      Noise Reduction
 *   - Call frequency and timing
 *      1.Periodically called every 30ms
 *      2.When an event such as UI/Input/App change occurs, it may be sent.
 *        But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_NOISE_REDUCTION*
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_noise_reduction_data{
 *      unsigned short ui_value[2]; //UI value for noise reduction 0~3:off,low,med,high
 *      union {
 *             unsigned char *pst_chip_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *     // container : v4l2_ext_vpq_cmn_data
 *   Description of UI Params
 *      Noise Reduction : ui_value[0]
 *          + Level of Noise Reduction in UI
 *          + 0/ 1/ 2/ 3 (off/low/meduim/high)
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 *   In case of 2-chip struct. AP will use a member "wId" of struct
 *   v4l2_ext_vpq_cmn_data to distinguish it's target chip.
 *
 *   wId : 0 - main chip's main-path
 *
 *   wId : 1 - main chip's sub-path (reserved for future)
 *
 *   wId : 2 - sub chip's main-path
 *
 *   wId : 3 - sub chip's sub-path (reserved for future)
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_noise_reduction_data noiseReduction;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_ext_vpq_cmn_data));
 *     memset(&noiseReduction, 0, sizeof(v4l2_ext_vpq_noise_reduction_data));
 *     noiseReduction.ui_value[0] = noiseReductionUiValue;
 *     noiseReduction.ui_value[1] = currentInputInfo;
 *     noiseReduction.pst_chip_data = PQL_DB_....();
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_noise_reduction_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&noiseReduction;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_NOISE_REDUCTION;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_NOISE_REDUCTION (V4L2_CID_EXT_VPQ_BASE + 7)

/**
 * @brief
 *   Set Mpeg NR
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Mpeg NR
 *   - Details of Feature
 *      Set the value of registers for Mpeg Noise Reduction.
 *      To remove unwanted ringing and block noise from images that have undergone
 *      MPEG or JPEG compression and decompression.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + The registers will be defined from PQ team. Refer to the "Remarks" section.
 *       + If register data structure is not defined, BSP should work by UI value.
 *      It also pass the additional info.
 *      The info is below.
 *       - mpegNrUiValue : The value of MPEG NoiseReduction UI. The value are off/low/medium/high(0/1/2/3).
 *   - Target Hardware Block
 *      Mpeg Noise Reduction
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS   // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS   // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_mpeg_noise_reduction_data{
 *      unsigned char ui_value;
 *      union {
 *             unsigned char *pst_chip_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *     // container : v4l2_ext_vpq_cmn_data
 *   Description of UI Params
 *      MPEG Noise Reduction : ui_value[0]
 *          + Level of MPEG Noise Reduction in UI
 *          + 0/ 1/ 2/ 3 (off/low/meduim/high)
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 *   In case of 2-chip struct. AP will use a member "wId" of struct
 *   v4l2_ext_vpq_cmn_data to distinguish it's target chip.
 *
 *   wId : 0 - main chip's main-path
 *
 *   wId : 1 - main chip's sub-path (reserved for future)
 *
 *   wId : 2 - sub chip's main-path
 *
 *   wId : 3 - sub chip's sub-path (reserved for future)
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_mpeg_noise_reduction_data mpegNoiseReduction;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_ext_vpq_cmn_data));
 *     memset(&mpegNoiseReduction, 0, sizeof(v4l2_ext_vpq_mpeg_noise_reduction_data));
 *     mpegNoiseReduction.ui_value = mpegNrUiValue;
 *     mpegNoiseReduction.pst_chip_data = PQL_DB_....();
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_mpeg_noise_reduction_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&mpegNoiseReduction;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION (V4L2_CID_EXT_VPQ_BASE + 8)

/**
 * @brief
 *   Defines the Control ID to set/get bypass pq(picture quility) blocks.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting bypass pq blocks.
 *   - Details of Feature
 *      HDR(High Dynamic Range) block sometimes needs to be set on/off
 *      for calibration. With this Control ID, the HDR bypass pq block without
 *      the HDR gamut matrix can be used. The VIDIOC_S_EXT_CTRLS is used for setting
 *      data and the VIDIOC_G_EXT_CTRLS is used for getting data.
 *      There are several bypass masks.
 *       - BIT0 is used for sharpness enhancer.
 *       - BIT1 is used for object contrast.
 *       - BIT2 is used for contrast, local contrast and color enhancer.
 *       - BIT3 is used for local dimming and gamma UI.
 *       - BIT4 is used for WB, DGA-4CH, POD, PCID, ODC.
 *       - BIT5 is used for HDR.
 *       - BIT6 is used for HDR bypass and HDR-PCC(Pearson correlation
 *         coefficients) enable.
 *       - BIT7 is used for FRC function.
 *       - BIT8 is used for MEMC bypass and FRC enable.
 *       - BIT9~11 is used for Reserved
 *   - Target Hardware Block
 *      Refer to BIT masks
 *   - Call frequency and timing
 *      It is calleld during calibration.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There sould be no performance degration.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_BYPASS_BLOCK
 *
 *     //
 *     // parameter
 *     // typedef enum v4l2_vpq_bypass_mask {
 *      V4L2_VPQ_BYPASS_MASK_NONE = 0x00000000,
 *      V4L2_VPQ_BYPASS_MASK_SHARP_ENHANCE = 0x00000001,             // BIT0: Sharpness Enhancer
 *      V4L2_VPQ_BYPASS_MASK_OBJECT_CONTRAST = 0x00000002,           // BIT1: Object Contrast
 *      V4L2_VPQ_BYPASS_MASK_CONTRAST_COLOR_ENHANCE = 0x00000004,    // BIT2: Contrast, Local Contrast, Color Enhancer
 *      V4L2_VPQ_BYPASS_MASK_GAMMA_LOCALDIMMING = 0x00000008,        // BIT3: Local dimming, Gamma UI
 *      V4L2_VPQ_BYPASS_MASK_NEAR_BE = 0x00000010,                   // BIT4: WB,DGA-4CH,POD,PCID,ODC
 *      V4L2_VPQ_BYPASS_MASK_HDR_ALL = 0x00000020,                   // BIT5: HDR
 *      V4L2_VPQ_BYPASS_MASK_HDR_EXCEPT_PCC = 0x00000040,            // BIT6: HDR bypass, HDR-PCC enable
 *      V4L2_VPQ_BYPASS_MASK_FRC_ALL = 0x00000080,                   // BIT7: FRC Bypass
 *      V4L2_VPQ_BYPASS_MASK_FRC_MEMC = 0x00000100,                  // BIT8: MEMC Bypass, FRC enable
 *      V4L2_VPQ_BYPASS_MASK_RESERVED_1 = 0x00000200,                // BIT9: Bypass reserve block1
 *      V4L2_VPQ_BYPASS_MASK_RESERVED_2 = 0x00000400,                // BIT10: Bypass reserve block2
 *      V4L2_VPQ_BYPASS_MASK_RESERVED_3 = 0x00000800,                // BIT11: Bypass reserve block3
 *      V4L2_VPQ_BYPASS_MASK_ALL = 0xFFFFFFFF,                       // VPQ Bypass All
 *     };
 *     struct v4l2_ext_vpq_block_bypass {
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input
 *       DECLARE locally data structures for executing vendor specific chip API
 *       SET appropriate data on the structure with sample data
 *       PQ_CMN_DATA_T *dataHal;
 *       dataHal = (PQ_CMN_DATA_T) *pstData;
 *       CALL the "vendor-specific chip functions" with that vendor-specific data structure which is declared above
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_block_bypass blockbypass;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&blockbypass, 0, sizeof(VPQ_BLOCKS_BYPASS));
 *     blockbypass.bOnOff=onOff;
 *     blockbypass.bypassMask=V4L2_VPQ_BYPASS_MASK_HDR_ALL;
 *     pqData.version=1;
 *     pqData.length = sizeof(blockbypass);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&blockbypass;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_BYPASS_BLOCK ;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_BYPASS_BLOCK (V4L2_CID_EXT_VPQ_BASE + 9)

/**
 * @brief
 *   Set the Black Level of ATV and Video Range of Others
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Black Level and Video Range.
 *   - Details of Feature
 *      Pass the black_level_type(enum v4l2_ext_vpq_black_level_type_v2) of Color Space Conversion of input.
 *      Suitable CSC value should be set by "black_level_type".
 *      "black_level_type" is changed by input video signal or "Video Range" UI(Limited/Full/Auto).
 *      It also pass the additional info. The info is below.
 *      ui_value : The value of Video Range UI. The value are Limited/Full/Auto(0/1/2).
 *      curr_input : refer to v4l2_ext_vpq_input in videodev2-ext.h
 *      color_space : The value are 1(HDR, BT709), 2(HDR, BT2020), 3(DOLBY, BT709), 4(DOLBY, BT2020).
 *   - Target Hardware Block
 *      Input CSC(Color Space Conversion)
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VPQ_BLACK_LEVEL
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_black_level_info_v2 {
 *         unsigned char ui_value;
 *         unsigned char curr_input;
 *         unsigned char color_space;
 *         enum v4l2_ext_vpq_black_level_type_v2 black_level_type;
 *     };
 *   Description of UI Params
 *      Video Range : ui_value
 *          - Level of Video Range in UI
 *          - 0/ 1/ 2 (Limited/Full/Auto).
 *          - if Limited, convert input Color bit 16~235 to 0~255.
 *          - if Full, display input color bit as is.
 *          - if Auto, set level low or High, checking HDMI InfoFrame Range.
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   ui_value: 0 = Limited, 1 = Full, 2 = Auto
 *
 *   curr_input: refer to enum v4l2_ext_vpq_input
 *
 *   color_space:
 *   | 0 = SDR
 *   | 1 = HDR10/HLG, BT709
 *   | 2 = HDR10/HLG, BT2020
 *   | 3 = DOLBY, BT709
 *   | 4 = DOLBY, BT2020
 *
 *   black_level_type: refer to enum v4l2_ext_vpq_black_level_type_v2
 *
 *   For main path(wId of v4l2_vpq_cmn_data is 0), set CSC value by "black_level_type" and use additional
 *   information for avoid error case or transition noise.
 *
 *   For Sub path, BSP must set CSC value automatically. Application set ui_value auto(2) normally.
 *   Exception case, for support airplay mirroring mode of ios, application will set ui_value to high(1).
 *   Singal range of airplay mirroring mode is YCbCr 0 ~ 255
 *   Ignore other paremters black_level_type, curr_input, color_space when sub path(wId of v4l2_vpq_cmn_data is 1)
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input
 *       DECLARE locally data structures for executing vendor specific chip API
 *       SET appropriate data on the structure with sample data
 *       CHIP_CSC_COEFF_T  *chipData;
 *       chipData = (CHIP_CSC_COEFF_T ) *pstData;
 *       CALL the "vendor-specific chip functions" with that vendor-specific data structure which is declared above
 *
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Black Level
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_black_level_info_v2 blackLevel;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&blackLevel, 0, sizeof(v4l2_ext_vpq_black_level_info_v2 ));
 *     blackLevel.ui_value= level;
 *     blackLevel.curr_input= input;
 *     blackLevel.color_space = 0;
 *     blackLevel.black_level_type_v2 = V4L2_EXT_VPQ_BLK_LVL_Y709_LINEAR_LIMIT_HIGH;
 *     // if the version is equal or over than 0x60, it will use v4l2_ext_vpq_black_level_info_v2 instead of v4l2_ext_vpq_black_level_info
 *     pqData.version=0x60;
 *     pqData.length = sizeof(v4l2_ext_vpq_black_level_info_v2);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&blackLevel;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_BLACK_LEVEL;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 *     //for sub path
 *     // Set Black Level
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_black_level_info_v2 blackLevel;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&blackLevel, 0, sizeof(v4l2_ext_vpq_black_level_info_v2 ));
 *
 *     if(appStatus == "airplay mirroring")
 *      blackLevel.ui_value= 1; //high
 *     else
 *      blackLevel.ui_value= 2; //auto
 *     pqData.version=0x60;
 *     pqData.length = sizeof(v4l2_ext_vpq_black_level_info_v2);
 *     pqData.wid=1;
 *     pqData.p_data=(UINT8*)&blackLevel;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_BLACK_LEVEL;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_BLACK_LEVEL (V4L2_CID_EXT_VPQ_BASE + 10)

/**
 * @brief
 *   Set gamma LUT data
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting gamma LUT data.
 *   - Details of Feature
 *      Set gamma LUT data. Set each RGB gamma table.
 *   - Target Hardware Block
 *      Gamma(Since it must be set including the OSD, the gamma block at the rear must be used.)
 *   - Call frequency and timing
 *      Periodically called every 30ms
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no temporary flickering during operation.
 *
 * Constraints
 *   The return for v4l2 is made immediately, and after the return,
 *   the actual register data setting must be done within the porch section.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_GAMMA_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stPanelInfo          [IN]      v4l2_ext_vpq_cmn_data
 *     struct v4l2_ext_gamma_lut {
 *         unsigned int table_num; // number of table elements
 *         union {
 *             unsigned int *table_red;
 *             unsigned int compat_table_red;
 *             unsigned long long sizer_r;
 *         };
 *         union {
 *             unsigned int *table_green;
 *             unsigned int compat_table_green;
 *             unsigned long long sizer_g;
 *         };
 *         union {
 *             unsigned int *table_blue;
 *             unsigned int compat_table_blue;
 *             unsigned long long sizer_b;
 *         };
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set gamma DB Data
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_gamma_lut stRealInfo;
 *     unsigned int gammaRed[1024] = {0,1,2, ... , 1023};
 *     unsigned int gammaBlue[1024] = {0,1,2, ... , 1023};
 *     ...
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.table_num = 1024;
 *     stRealInfo.table_red = &gammaRed[0];
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_GAMMA_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_GAMMA_DATA (V4L2_CID_EXT_VPQ_BASE + 11)

/**
 * @brief
 *   Set Super Resolution
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Super Resolution
 *   - Details of Feature
 *      Set Super Resolution Parameters.
 *      Parameter contains UI value and register data pointer.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + Register data structure should be defined each side BSP and application(discuss with LG PQ Team).
 *       + If register data structure is not defined or wrong data, BSP should work with UI value only.
 *      It also pass the additional info.
 *      The info is below.
 *       - superResolutionUiValue : The value of Super Resolution UI.
 *         The value are off/low/medium/high(0/1/2/3).
 *   - Target Hardware Block
 *      Super Resolution
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_SUPER_RESOLUTION
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_super_resolution_data{
 *      unsigned char ui_value;
 *      union {
 *             unsigned char *pst_chip_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *   Description of UI Params
 *      Super Resolution : ui_value
 *          - Level of Super Resolution in UI
 *          - 0/ 1/ 2/ 3 (off/low/medium/high).
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of input parameters
 *       DECLARE locally data structures for executing vendor specific chip API
 *       SET appropriate data on the structure with sample data
 *       PQ_CMN_DATA_T *dataHal;
 *       dataHal = (PQ_CMN_DATA_T) *pstData;
 *       CALL the "vendor-specific chip functions" with that vendor-specific data structure which is declared above
 *
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_super_resolution_data superResolution;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_ext_vpq_cmn_data));
 *     memset(&superResolution, 0, sizeof(v4l2_ext_vpq_super_resolution_data));
 *     superResolution.ui_val = superResolutionUiValue;
 *     superResolution.pst_chip_data = PQL_DB_....();
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_super_resolution_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&superResolution;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_SUPER_RESOLUTION;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_SUPER_RESOLUTION (V4L2_CID_EXT_VPQ_BASE + 12)

/**
 * @brief
 *   Get Noise Level
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it removed from webOS 24
 *
 * @rst
 * .. warning::
 *   Not use.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_NOISE_LEVEL (V4L2_CID_EXT_VPQ_BASE + 13)

/**
 * @brief
 *   Defines the Control ID to set/get the control of Game Mode.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting the control of Game Mode.
 *   - Details of Feature
 *      If Game Mode enables, then the low delay mode should be working.
 *      On the other hand, if Game Mode disables, then the low delay mode
 *      should be stop working. The VIDIOC_S_CTRL is used for setting data
 *      and the VIDIOC_G_CTRL is used for getting data.
 *   - Target Hardware Block
 *      MEMC Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_LOW_DELAY_MODE
 *
 *     //
 *     // parameter
 *     //
 *     BOOLEAN bGameMode
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       IF bGameMode == TRUE THEN
 *           enable low-delay mode
 *       ELSE
 *           disable low-delay mode
 *       END
 *
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VPQ_LOW_DELAY_MODE;
 *     control.value = TRUE;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_LOW_DELAY_MODE (V4L2_CID_EXT_VPQ_BASE + 14)

/**
 * @brief
 *   Get Chip Bypass LUT for Dynamic Contrast
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *   Not use.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT                           \
    (V4L2_CID_EXT_VPQ_BASE + 15)

/**
 * @brief
 *   Set Color Gain for Auto Dynamic Contrast
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set Color Gain for compensate saturation
 *   - Details of Feature
 *      For compensate color weak or strong by luma LUT(V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT),
 *      set Color Gain(saturation).
 *      Value is signed int, persent(gain).
 *      If same H/W(V4L2_CID_EXT_VPQ_PICTURE_CTRL) used, gaining to saturation of V4L2_CID_EXT_VPQ_PICTURE_CTRL.
 *      If This API not called, default value is 100(1.0).
 *   - Target Hardware Block
 *      Saturation control H/W
 *   - Call frequency and timing
 *      Call this API per 30ms. But if data is same as previous call, skip call.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL // Set PQ Data
 *     VIDIOC_G_CTRL // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN
 *
 *     //
 *     // parameter
 *     //
 *     int nColorGain; //signed int, persent value
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN ;
 *     control.value = 30; //30%, 0.3
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN                           \
    (V4L2_CID_EXT_VPQ_BASE + 16)

/**
 * @brief
 *   Set IRE Inner Pattern
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting IRE Inner Pattern
 *   - Details of Feature
 *      Set IRE(Institute of Radio Engineer) Inner Pattern. A value of 100IRE indicates a white level of a video signal,
 *      and 0IRE indicates a blanking level. It has a range of 0-100 as a relative standard for Black & White. (White: 100IRE, Black: 1IRE)
 *   - Target Hardware Block
 *      Video pattern before gamma
 *   - Call frequency and timing
 *      When an WB pattern is on, it may be sent.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set PQ Data
 *     VIDIOC_G_CTRL       // Get VDO info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_TESTPATTERN
 *
 *     //
 *     // control value
 *     //
 *     V4L2_VPQ_INNER_PATTERN_IRE_0 ~ V4L2_VPQ_INNER_PATTERN_IRE_100 : display ire pattern corresponding level
 *     V4L2_VPQ_INNER_PATTERN_DISABLE : disable IRE pattern
 *
 *     V4L2_VPQ_INNER_PATTERN_24P_IRE_0 ~ V4L2_VPQ_INNER_PATTERN_24P_IRE_100 : display 24 point ire pattern corresponding level
 *     V4L2_VPQ_INNER_PATTERN_24P_DISABLE : disable 24 point IRE pattern
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * See Also
 *   v4l2_vpq_inner_pattern_ire
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_TESTPATTERN (V4L2_CID_EXT_VPQ_BASE + 17)

/**
 * @brief
 *   Set offset and gain value of RGB for adjusting Colortemperature
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set offset and gain value of RGB for adjusting Colortemperature
 *   - Details of Feature
 *      Gain Value mapping
 *         +---------------------------+
 *         | passed Value      | Gain  |
 *         +===========================+
 *         | 0                 | 0.5   |
 *         +---------------------------+
 *         | 192               | 1.0   |
 *         +---------------------------+
 *         | 255               | 1.164 |
 *         +---------------------------+
 *      Offset Value mapping
 *         +---------------------------+
 *         | passed Value      | Offset|
 *         +===========================+
 *         | 0                 | -64   |
 *         +---------------------------+
 *         | 64                |  0    |
 *         +---------------------------+
 *         | 127               |  63   |
 *         +---------------------------+
 *   - Target Hardware Block
 *      RGB gain/offset(Color Temperature) Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_COLORTEMP_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_vpq_cmn_data
 *
 *     cf... (struct v4l2_ext_vpq_color_temp *)stContainer.p_data
 *     stChipData.pData [IN] chip data for color temperature
 *     struct v4l2_ext_vpq_color_temp {
 *         unsigned short rgb_gain[3];   ///< gain. 0:red, 1:green, 2:blue
 *         unsigned short rgb_offset[3]; ///< offset. 0:red, 1:green, 2:blue
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Color temperature Data
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_vpq_color_temp stRealInfo;
 *     unsigned char gain[v4l2_vpq_rgb_max] = {192,192,192};
 *     unsigned char offset[v4l2_vpq_rgb_max] = {64,64,64};
 *     ...
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     memcpy(stRealInfo.rgb_gain, gain, sizeof(stRealInfo.rgb_gain));
 *     memcpy(stRealInfo.rgb_offset, offset, sizeof(stRealInfo.rgb_offset));
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_COLORTEMP_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_COLORTEMP_DATA (V4L2_CID_EXT_VPQ_BASE + 18)

/**
 * @brief
 *   Control the Film Detection
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Turn on/off the film detec source(ex.3:2 pull down) and converts them to original frame rate.
 *   - Details of Feature
 *      This is a function that detects film source(ex.3:2 pull down) and converts them to original frame rate.
 *      RealCinema On
 *       + Input Video: 60i
 *          Removes jagging noise using Motion Adaptive Deinterlacing Processing (MADP) or similar functions.
 *       + Input Video: 24p
 *          SoC outputs at 48Hz (2:2 pulldown).
 *      RealCinema Off
 *       + Input Video: 60i
 *          Performs basic deinterlacing processing (interlaced to progressive).
 *       + Input Video: 24p
 *          SoC outputs at 60Hz (3:2 pulldown).
 *   - Target Hardware Block
 *      De-Interlace
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Set pull down for each input and model to prevent judder from occurring.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL    // Set PQ Data
 *     VIDIOC_G_CTRL    // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_REAL_CINEMA
 *
 *     //
 *     // parameter
 *     //
 *     int film_mode; // 0/1 off/on
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              IF bFilmMode = TRUE
 *                      Set PQ data for filmmode
 *              Else
 *                      Set PQ data for other mode
 *              IF chip_data != NULL
 *                      Set PQ by chip_data
 *
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VPQ_REAL_CINEMA ;
 *     control.value = true;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_REAL_CINEMA (V4L2_CID_EXT_VPQ_BASE + 19)

/**
 * @brief
 *   Set color gamut LUT
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *     Adjust Panel color gamut by 3D(RGB) LUT
 *   Details of Feature
 *     Set 3D(RGB) LUT for adjust color gamut.
 *     Parameter contains 3D LUT data and signal information.
 *
 *     + 3D LUT is array of unsigned short. Array size should be defined each BSP and Application.

 *     + total_section_num is number of 3D LUT in p_section_data. Currently total_section_num is always 1.
 *     + Signal informations are in addInfo(v4l2_ext_vpq_gamut_add_info). If BSP need to check character of LUT refer this additional information.
 *
 *        + v4l2_ext_vpq_gamut_add_info.p_info_data is address of UINT32(unsigned int) array.
 *          Even index is data type(input type, colorimetry), Odd index is data.
 *          - array[0] = 0x01 (input type)
 *          - array[1] = 0(SDR), 1(Dolby), 2(HDR10), 3(HLG), 4(Technicolor), 5(HDR
 *          Effect, not used)
 *          - array[2] = 0x02 (colorimetry)
 *          - array[3] = 0(colorimetry BT601), 1(colorimetry BT709), 2(colorimetry BT2020)
 *          - array[4~6] = LG platform only.
 *
 *   Target Hardware Block
 *     3D LUT for gamut mapping
 *   Call frequency and timing
 *     + This API will be called sevaral times when Input/App changed
 *     + This API be called once when user change Color Gamut UI
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_GAMUT_3DLUT
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_gamut_add_info {
 *         unsigned int info_size;
 *         union {
 *             unsigned int *p_info_data; ///< p_data
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *     struct v4l2_ext_vpq_gamut_lut {
 *         unsigned int lut_version;
 *         unsigned int total_section_num;
 *         union {
 *             unsigned short *p_section_data; ///< p_data
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *         struct v4l2_ext_vpq_gamut_add_info add_info;
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Gamut 3D LUT
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_gamut_lut gamutLut;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&gamutLut, 0, sizeof(v4l2_ext_vpq_gamut_lut ));
 *     unsigned int addInfo[7];
 *     addInfo[0] = 0x01;
 *     addInfo[1] = hdrMode;
 *     addInfo[2] = 0x02;
 *     addInfo[3] = colorimetry;
 *     v4l2_ext_vpq_gamut_lut.lut_version = 1;
 *     v4l2_ext_vpq_gamut_lut.total_section_num = 1;
 *     v4l2_ext_vpq_gamut_lut.p_section_data = &g3dLut[modelIdx][colorStandard][0];
 *     v4l2_ext_vpq_gamut_lut.add_info.info_size = sizeof(addInfo);
 *     v4l2_ext_vpq_gamut_lut.add_info.info_size = addInfo;
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_gamut_lut );
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)gamutLut;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_GAMUT_3DLUT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_GAMUT_3DLUT (V4L2_CID_EXT_VPQ_BASE + 20)

/**
 * @brief
 *   Control look up table for OD
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for Control look up table data for OD(Frame)
 *   - Details of Feature
 *      This function controls look up table data for OD(Frame)
 *      The LUT data struct is 1-Dimension
 *      The LUT data's size has dependency on each SoC's H/W
 *   - Target Hardware Block
 *      FOD(Frame Over Drive)
 *   - Call frequency and timing
 *      Event : triggered by system power off/on
 *                  or video characteristics changes such as VRR on/off
 *
 * Responses to abnormal situations, including
 *   If the length of LUT is not match to H/W spec,
 *      return error & do nothing
 *
 * Performance Requirements
 *   No special reqirements
 *
 * Constraints
 *   The LUT change should not make any flicker
 *      using double buffer may be a good solution to handle it
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OD_TABLE
 *
 *     //
 *     // parameter
 *     //
 *     unsigned char pData[OD_LUT_SIZE];
 *     #define LUT_SIZE_OD      // it depends on each platform's H/W LUT size. Not fixed value for all Platform
 *
 * Return Value
 *    If the function succeeds, the return value is OK.
 *    If the function fails, the return value is NOT_OK.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *      Write OD look up table with size and pTable.
 *      IF any error has occurred THEN
 *              RETURN NOT_OK
 *      END IF
 *              RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OD
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     unsigned char pOdTable[OD_LUT_SIZE];
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version=1;
 *     pqData.length = OD_LUT_SIZE;
 *     pqData.p_data = pOdTable;
 *     pqData.wid=0;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_OD_TABLE;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OD_TABLE (V4L2_CID_EXT_VPQ_BASE + 21)

/**
 * @brief
 *   Control LUT for OD extension POD or PCID
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting LUT for OD extension(POD or PCID)
 *   - Details of Feature
 *      Set LUT for OD extension(POD or PCID)
 *   - Target Hardware Block
 *      POD(Pixel Over Drive)
 *      PCID(Patternd Retard Crosstalk Improvement Device)
 *   - Call frequency and timing
 *      Event : triggered by system power off/on
 *
 * Responses to abnormal situations, including
 *   If the length of LUT is not match to H/W spec,
 *      return error & do nothing
 *
 * Performance Requirements
 *   No special reqirements
 *
 * Constraints
 *   The LUT change should not make any flicker
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OD_EXTENSION
 *
 *     //
 *     // parameter
 *     //
 *     *pData        [IN] v4l2_vpq_cmn_data: *pData
 *     struct v4l2_vpq_od_extension
 *     {
 *      unsigned char ext_type;  ///< 0: POD, 1: PCID, 2: NONE
 *      unsigned int ext_length; ///< LUT data size
 *      union
 *      {
 *       unsigned char *p_ext_data; ///< LUT data
 *       unsigned int compat_data;
 *       unsigned long long sizer;
 *      };
 *     };
 *
 * Return Value
 *   If the function succeeds, the return value is OK.
 *   If the function fails, the return value is NOT_OK.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OD Extension
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct v4l2_vpq_od_extension odExtInfo;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&panelInfo, 0, sizeof(LED_PANEL_INFO_T));
 *     odExtInfo.ext_type = 1; //PCID
 *     odExtInfo.ext_length = LUT_SIZE_PCID;
 *     odExtInfo.p_ext_data = pTable;
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_od_extension);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&odExtInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_OD_EXTENSION;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OD_EXTENSION (V4L2_CID_EXT_VPQ_BASE + 22)

/**
 * @brief
 *   Set LUT table of local contrast of LG SoC
 *
 * @rst
 * .. warning::
 *   LG SoC only
 *
 * Functional Requirements
 *   Purpose
 *     for setting LUT table of local contrast
 *
 *   Details of Feature
 *     Local Contrast is enhancing contrast each block of picture indivisually.
 *     This API set local contrast LUT.
 *     Set LUT table according to the APL.
 *     Only LG SoC
 *     Need to define LUT data structure for each SoC's register.
 *     LUT data structure should be defined each BSP and application side.
 *
 *   Target Hardware Block
 *     Local contrast enhancement H/W of LG platform
 *
 *   Call frequency and timing
 *     This API will be called sevaral times when Input/App changed
 *     This API be called once when user change Dynamic Contrast UI.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_vpq_dc2p_histodata_info
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE
 *
 *     //
 *     // parameter
 *     //
 *     p_data = struct v4l2_ext_vpq_dc2p_localcontrast_table
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              Set Local Contrast Talbe
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Local Contrast Table
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_dc2p_localcontrast_table localcontTable;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&localcontTable, 0, sizeof(v4l2_vpq_dc2p_localcontrast_table ));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_dc2p_localcontrast_table );
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&localcontTable;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE (V4L2_CID_EXT_VPQ_BASE + 23)

/**
 * @brief
 *   Control Local Contrast
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *     Control Local Contrast
 *
 *   Details of Feature
 *     Local Contrast is enhancing contrast each block of picture indivisually.
 *     This API control local contrast by set registers.
 *
 *     + Register values will be set by "Auto Dynamic Contrast" UI(off,low,medium,High)
 *     + Control registers are different each SoC, need to define data structure for each SoC's register.
 *     + Register data structure should be defined each BSP and application side(discuss with LG PQ Team).
 *
 *   Target Hardware Block
 *     Local Contrast Enahance H/W
 *
 *   Call frequency and timing
 *     This API will be called sevaral times when Input/App changed
 *     This API be called once when user change Auto Dynamic Contrast UI.
 *
 * Responses to abnormal situations, including
 *   SoC support this HW but register data structure is not defined yet, just return OK
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   No constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA
 *
 *     //
 *     // parameter
 *     //
 *     p_data = chipdata
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              Set Local Contrast Parameter
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Local Contrast Param
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_dc2p_localcontrast_param localcontParam;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&localcontParam, 0, sizeof(v4l2_vpq_dc2p_localcontrast_param));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_dc2p_localcontrast_param );
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&localcontParam;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA (V4L2_CID_EXT_VPQ_BASE + 24)

/**
 * @brief
 *   Control the contrast between the object and the background
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *   Not use.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_PSP (V4L2_CID_EXT_VPQ_BASE + 25)

/**
 * @brief
 *   Color Gamut Mapping for HDR block.
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it removed from webOS 24
 *
 * @rst
 * .. warning::
 *   Not use.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE (V4L2_CID_EXT_VPQ_BASE + 26)

/**
 * @brief
 *   Set 3x3 Matrix for adjust color gamut
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *     Adjust Color Gamut by 3x3 matrix(color gamut Mapping)
 *   - Details of Feature
 *      Setting Color Gamut Mapping 3x3 matrix, gamma, degamma, mux setting.
 *
 *      gamma: set enable/disable gamma function front of 3x3 Matrix. So input of 3x3 matrix is lineaer
 *      degamma: set enable/disable degamma function back of 3x3 Matrix. So output of 3x3 matrix is o.45 gamma
 *      matrix: set 3x3 matrix. each value scale up x10000. (ex: 1.0 ==> 10000)
 *      mux_blend: set blending option for 3DLUT and 3x3 matrix result. LG platform ONLY.
 *      ┌─────┐ ┌──────┐ ┌────────┐ ┌─────┐
 *      │gamma│→│3x3   │→│de-gamma│→│mux  │→
 *      │     │ │matrix│ │        │ │blend│
 *      └─────┘ └──────┘ └────────┘ └─────┘
 *
 *      pst_chip_data: If SoC support additional HW for gamut mapping, additional data can be set by this.
 *      Data structure should be defined each side BSP and application(discuss with LG PQ Team).
 *      If SoC not support, value is null.

 *   - Target Hardware Block
 *      3 by 3 matrix for Color Gamut Mapping
 *   - Call frequency and timing
 *      - This API will be called sevaral times when Input/App changed.
 *      - This API be called once when user change Color Gamut UI.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST
 *
 *     //
 *     // parameter
 *     //
 *     *pGamutData         [IN] v4l2_ext_gamut_post
 *
 *     #define CSC_MUX_LUT_SIZE 4
 *     struct v4l2_ext_csc_mux_lut { //LG platform only
 *         unsigned int mux_l3d_in;
 *         unsigned int mux_blend_in;
 *         unsigned int mux_4p_lut_in;
 *         unsigned int mux_oetf_out;
 *         unsigned int b4p_lut_x[CSC_MUX_LUT_SIZE];
 *         unsigned int b4p_lut_y[CSC_MUX_LUT_SIZE];
 *     };
 *
 *     struct v4l2_ext_gamut_post {
 *         unsigned char gamma;
 *         unsigned char degamma;
 *         short matrix[9];
 *         struct v4l2_ext_csc_mux_lut mux_blend; //Used LG platform only
 *         union {
 *             unsigned char *pst_chip_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set Gamut Matrix(SDR PCC)
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OD Extension
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_vpq_gamut_post gamutPost;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(pqData));
 *     memset(&gamutPost, 0, sizeof(gamutPost));
 *     //gamut mapping post
 *     PQL_DB_GetColorGamutParam(&gamutPost);
 *     pqData.version=1;
 *     pqData.length = sizeof(gamutPost);
 *     pqData.wId=0;
 *     pqData.pData=(UINT8*)&gamutPost;
 *     ext_control.id = V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST (V4L2_CID_EXT_VPQ_BASE + 27)

/**
 * @brief
 *   Defines the Control ID to set/get mode info of PQ(Picture Quility).
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for setting/getting mode info of PQ.
 *   - Details of Feature
 *      The mode info is consist of UINT32 array which length is 5 and stores
 *      four entities below.
 *       - HDR mode
 *       - Colorimetry info
 *       - Panel peak value
 *       - Flag that represents for supporting prime.
 *
 *      The VIDIOC_S_EXT_CTRLS is used for setting data and the VIDIOC_G_EXT_CTRLS
 *      is used for getting data.
 *   - Target Hardware Block
 *      NA
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_PQ_MODE_INFO
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_colorimetry_info {
 *      V4L2_EXT_COLORIMETRY_BT601,
 *      V4L2_EXT_COLORIMETRY_BT709,
 *      V4L2_EXT_COLORIMETRY_BT2020,
 *      V4L2_EXT_COLORIMETRY_MAX
 *     };
 *     enum v4l2_ext_hdr_mode {
 *         V4L2_EXT_HDR_MODE_SDR,
 *         V4L2_EXT_HDR_MODE_DOLBY,
 *         V4L2_EXT_HDR_MODE_HDR10,
 *         V4L2_EXT_HDR_MODE_HLG,
 *         V4L2_EXT_HDR_MODE_TECHNICOLOR,
 *         V4L2_EXT_HDR_MODE_HDREFFECT,
 *         V4L2_EXT_HDR_MODE_MAX
 *     };
 *     UINT32 pqModeInfo[5];
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set Mode info for PQ
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OD Extension
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     UINT32 pqModeInfo[5];
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(pqData));
 *     memset(&pqModeInfo, 0, sizeof(pqModeInfo));
 *     pqModeInfo[0] = hdrMode;
 *     pqModeInfo[1] = colorimetry;   // see v4l2_ext_colorimetry_info
 *     pqModeInfo[2] = peakLuminance;    // peakLuminance of panel
 *     pqModeInfo[3] = supportPrime;  // support Prime
 *     pqData.version=1;
 *     pqData.length = sizeof(pqModeInfo);
 *     pqData.wId=0;
 *     pqData.pData=(UINT8*)&pqModeInfo;
 *     ext_control.id = V4L2_CID_EXT_VPQ_PQ_MODE_INFO;
 *     ext_control.ptr = (void *)&pqData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_PQ_MODE_INFO (V4L2_CID_EXT_VPQ_BASE + 28)

/**
 * @brief
 *   Set Degamma data
 *
 * @deprecated
 *   Deprecated since webOS 5.0, it will be removed from webOS 24
 *
 */
#define V4L2_CID_EXT_VPQ_DEGAMMA_DATA (V4L2_CID_EXT_VPQ_BASE + 29)

/**
 * @brief
 *   Control video 10to11-bit conversion block registers
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *       for 10to11-bit conversion block registers
 *       useally, it's used for white boost
 *   - Details of Feature
 *       It contains many registers control related to the conversion
 *       But it doesn't contain apl mapping of the target block
 *   - Target Hardware Block
 *      post HDR(it handle conversion from 10bit to 11bit of bit resolution)
 *   - Call frequency and timing
 *      Event : triggered by UI/video meta info such as HDR/video Connection
 *                 /system power off_on
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements
 *
 * Performance Requirements
 *   Nothing special requirements
 *
 * Constraints
 *   Nothing special requirements
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_LUMINANCE_BOOST
 *     //
 *     // parameter
 *     //
 *     p_data = chipdata
 *
 * Return Value
 *    If the function succeeds, the return value is OK.
 *
 *    If the function fails, the return value is NOT_OK.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set Luminence boost LUT
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OLED Luminance Boost
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_vpq_post_hdr_lut v4l2PostHdrLut;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&v4l2PostHdrLut, 0, sizeof(v4l2_vpq_post_hdr_lut));
 *     PQDB_Get_DB_Data(&v4l2PostHdrLut);
 *     pqData.version = V4L2_CID_EXT_VPQ_LUMINANCE_BOOST_VERSION;
 *     pqData.length = sizeof(v4l2_vpq_post_hdr_lut);
 *     pqData.wid=0;
 *     pqData.pData = (unsigned char *)&v4l2PostHdrLut;;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_LUMINANCE_BOOST;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_LUMINANCE_BOOST (V4L2_CID_EXT_VPQ_BASE + 30)

/**
 * @brief
 *   Get object data for Object based contrast
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *     Get APL(Average Picture Level) of object.
 *
 *   Details of Feature
 *     Return AI Depth Map data. AI Depth Map data is Depth Map APL information.
 *     SoC/BSP detect background and object(ex. head of human). Calulate each APL.
 *
 *     + Need to define data structure for each SoC's register data(discuss with LG PQ Team).
 *     + Register data structure should be defined each BSP and application side.
 *     + If register data structure is not defined BSP should work by UI value.
 *
 *   Target Hardware Block
 *     Object detection H/W
 *
 *   Call frequency and timing
 *     Call this API per 30ms.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OBC_DATA
 *
 *     //
 *     // parameter
 *     //
 *     // Each SoC should define data structure internally.
 *     // Example
 *     struct v4l2_vpq_obc_data {
 *       unsigned short head_apl;
 *       unsigned short depth_apl;
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Get OBC Data
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get OBC Data
 *     struct v4l2_vpq_obc_data { //Each SoC defined structure
 *       unsigned short head_apl;
 *       unsigned short depth_apl;
 *     };
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_obc_data obcdata; //Each SoC defined structure
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&obcdata, 0, sizeof(v4l2_vpq_obc_data));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_obc_data);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&obcdata;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_OBC_DATA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OBC_DATA (V4L2_CID_EXT_VPQ_BASE + 31)

/**
 * @brief
 *   Set Foreground/Background LUT to OBC/OBE(Object Based Contrast)
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *     For setting Foreground/Background LUT for OBC
 *
 *   Details of Feature
 *     + For setting Foreground/Background LUT for OBC
 *     + only LG Platform
 *
 *   Target Hardware Block
 *     Object Based Contrast(OBC/OBE) H/W
 *
 *   Call frequency and timing
 *     Call this API per 30ms. But if data is same as previous call, skip call.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ info
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OBC_LUT
 *
 *     //
 *     // parameter
 *     //
 *     1. LG
 *     struct v4l2_vpq_obc_lut
 *     {
 *         unsigned short object_fg_x[8];
 *     };
 *
 *     2. RTK
 *     Not Use
 *
 *     3. MTK
 *     Not Use
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This function is only supported by LG platform.
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set FG/BG LUT factor
 *             v4l2_vpq_cmn_data *chipData;
 *             chipData = (v4l2_vpq_cmn_data ) *pData;
 *             CALL the "vendor-specific chip functions" with that vendor-specific data structure
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OBC LUT
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_obc_lut obcLut;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data ));
 *     memset(&obcLut, 0, sizeof(v4l2_vpq_obc_lut ));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_obc_lut );
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&obcLut;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_OBC_LUT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS     , &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OBC_LUT (V4L2_CID_EXT_VPQ_BASE + 32)

/**
 * @brief
 *   Set OBC/OBE(Object Based Contrast) control
 *
 * @rst
 * Functional Requirements
 *   Purpose
 *    Set OBC/OBE(Object Based Contrast) control
 *
 *   Details of Feature
 *     + Set FG/BG control factor for OBC.
 *     + only LG Platform.
 *   Target Hardware Block
 *     Object Based Contrast(OBC/OBE) H/W
 *
 *   Call frequency and timing
 *     + This API will be called sevaral times when Input/App changed
 *     + This API be called once when user change Dynamic Contrast UI.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   There are no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ info
 *     VIDIOC_G_EXT_CTRLS       // Get PQ info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OBC_CTRL
 *
 *     //
 *     // parameter
 *     //
 *     1. LG
 *     struct v4l2_vpq_obc_ctrl
 *     {
 *         bool bOBC_enable;
 *      unsigned char fg_gain_y1;
 *      unsigned char bg_gain_y1;
 *      bool bOBC_sat_enable;
 *      unsigned short reg_yy_lut_pts_x2;
 *      unsigned char char reg_yy_lut_pts_y2;
 *      unsigned char reg_cc_lut_pts_x0;
 *      unsigned char reg_cc_lut_pts_y0;
 *
 *      unsigned char reg_cbst_lut_pts_x2;
 *      unsigned char reg_cbst_lut_pts_y2;
 *     };
 *
 *     2. RTK
 *     Not Use
 *
 *     3. MTK
 *     Not Use
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Remarks
 *   This function is only supported by LG platform.
 *   Other chip will implement it as dummy.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set FG/BG  control factor
 *             v4l2_vpq_cmn_data *chipData;
 *             chipData = (v4l2_vpq_cmn_data) *pData;
 *             CALL the "vendor-specific chip functions" with that vendor-specific data structure
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OBC Ctrl
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_vpq_obc_ctrl obccttrl;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&obccttrl, 0, sizeof(v4l2_vpq_obc_ctrl));
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_obc_ctrl);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&obccttrl;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_OBC_CTRL;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OBC_CTRL (V4L2_CID_EXT_VPQ_BASE + 33)

/**
 * @brief
 *   Control the De-Contour function
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Control the De-Contour function
 *   - Details of Feature
 *      Set De-Contour parameters.
 *      Parameter contains UI value and register data pointer.
 *       + Control registers are different each SoC, need to define data structure for each SoC's register.
 *       + The registers will be defined from PQ team. Refer to the "Remarks" section.
 *       + If register data structure is not defined, BSP should work by UI value.
 *      It also pass the additional info.
 *      The info is below.
 *       - decontourUiValue : The value of De-contour-related UI. The value are off/low/medium/high(0/1/2/3).
 *   - Target Hardware Block
 *      Decontour
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DECONTOUR
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_decontour_data {
 *         unsigned char ui_value;
 *         union {
 *             unsigned char *pst_chip_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     // container : v4l2_ext_vpq_cmn_data
 *   Description of UI Params
 *      De-contour( LG UI : Smooth Gradation ) : ui_value
 *          - Level of De-contour in UI
 *          - 0/ 1/ 2/ 3 (off/low/medium/high)
 * 
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 *   In case of 2-chip struct. AP will use a member "wId" of struct
 *   v4l2_ext_vpq_cmn_data to distinguish it's target chip.
 *
 *   wId : 0 - main chip's main-path
 *
 *   wId : 1 - main chip's sub-path (reserved for future)
 *
 *   wId : 2 - sub chip's main-path
 *
 *   wId : 3 - sub chip's sub-path (reserved for future)
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Picture Control
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_decontour_data decontour;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&decontour, 0, sizeof(v4l2_ext_vpq_decontour_data));
 *     decontour.ui_value= decontourUiValue;
 *     decontour.chip_data = PQL_DB_....();
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_ext_vpq_ctrl_data);
 *     pqData.wid=0;
 *     pqData.p_data=(UINT8*)&decontour;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DECONTOUR;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DECONTOUR (V4L2_CID_EXT_VPQ_BASE + 34)

/**
 * @brief
 *   Set extra inner pattern display
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting extra inner pattern display
 *   - Details of Feature
 *      For special use case(eg. PQ calibration), TV wants to display BSP's extra
 *      internal pattern. This is an extra inner pattern displaying requirement.
 *      (different pattern type to IREInnerPattern)
 *
 *      We need two kinds of pattern.
 *
 *      1) multiple window fill box
 *      2) multiple line gradiation
 *   - Target Hardware Block
 *      Any Video pattern generator Block (in front of hdr block)
 *   - Call frequency and timing
 *      When an external pq calibration starts, it may be sent.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS      // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     VV4L2_CID_EXT_VPQ_EXTRA_PATTERN
 *
 *     //
 *     // parameter
 *     //
 *     stContainer [IN] v4l2_vpq_cmn_data
 *     cf... (struct v4l2_vpq_ext_pattern_info *)stContainer.p_data
 *     enum V4L2_VPQ_EXT_PATTERN_MODE {
 *       V4L2_VPQ_EXT_PATTERN_WINBOX,
 *       V4L2_VPQ_EXT_PATTERN_GRADATION,
 *       V4L2_VPQ_EXT_PATTERN_MAX
 *     };
 *
 *     enum V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION {
 *       V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL,
 *       V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_VERTICAL,
 *       V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_MAX
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_gradation_line_attr{
 *       unsigned char lineIdx; // gradation line index
 *       unsigned short start_R; // 1st gradation block's red level as a 10bit resolution
 *       unsigned short start_G; // 1st gradation block's green level as a 10bit resolution
 *       unsigned short start_B; // 1st gradation block's blue level as a 10bit resolution
 *       unsigned short step_R; // step size for next gradation block
 *       unsigned short step_G; // step size for next gradation block
 *       unsigned short step_B; // step size for next gradation block
 *       unsigned short strideSize; // gradation block's width(horizontal mode)/height(vertical mode)
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_gradation_info{
 *       unsigned char numGrad; // number of gradation lines in a screen
 *       enum V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION eGradMode;
 *       struct v4l2_vpq_ext_pattern_gradation_line_attr stLineAttr[MAX_EXT_PATTERN_GRADATION_LINE];
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_winbox_win_attr{
 *       unsigned short winIdx; // window layer index. 0:background
 *       unsigned short x;
 *       unsigned short y;
 *       unsigned short w;
 *       unsigned short h;
 *       unsigned short fill_R, // 10 bit resolution
 *       unsigned short fill_G, // 10 bit resolution
 *       unsigned short fill_B, // 10 bit resolution
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_winbox_info{
 *       unsigned char u8NumWin; // number of windows in a screen(including background window)
 *       struct v4l2_vpq_ext_pattern_winbox_win_attr stWinBoxAttr[MAX_EXT_PATTERN_WINBOX];
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_info{
 *       unsigned char bOnOff;
 *       enum V4L2_VPQ_EXT_PATTERN_MODE eMode;
 *       struct v4l2_vpq_ext_pattern_gradation_info* pstGradInfo;
 *       struct v4l2_vpq_ext_pattern_winbox_info* pstWinboxInfo;
 *     };
 *
 *     typedef struct v4l2_vpq_ext_pattern_info_v2 {
 *       unsigned char bOnOff;
 *       enum V4L2_VPQ_EXT_PATTERN_MODE eMode;
 *       struct v4l2_vpq_ext_pattern_gradation_info stGradInfo;
 *       struct v4l2_vpq_ext_pattern_winbox_info stWinboxInfo;
 *     };
 *
 *     // chip dependent settings
 *     #define SUPPORT_EXT_INNER_PATTERN
 *     #ifdef SUPPORT_EXT_INNER_PATTERN
 *     #define MAX_EXT_PATTERN_GRADATION_LINE (4) // it depends on chip limitation
 *     #define MAX_EXT_PATTERN_WINBOX (10) // it depends on chip limitation
 *     #define MAX_EXT_PATTERN_GRADATION_H_STRIDE_SIZE (254) // it depends on chip limitation
 *     #define EXT_PATTERN_GRADATION_H_STRIDE_STEP (2) // it depends on chip limitation
 *     #define MAX_EXT_PATTERN_GRADATION_V_STRIDE_SIZE (127) // it depends on chip limitation
 *     #define EXT_PATTERN_GRADATION_V_STRIDE_STEP (1) // it depends on chip limitation
 *     #define EXT_PATTERN_WIDTH (3840) // it depends on chip limitation
 *     #define EXT_PATTERN_HEIGHT (2160) // it depends on chip limitation
 *     #endif
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set multi-window fill box inner pattern
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer;
 *     struct v4l2_vpq_ext_pattern_info_v2 stRealInfo;
 *     ...
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     stRealInfo.bOnOff = TRUE;
 *     stRealInfo.eMode = V4L2_VPQ_EXT_PATTERN_WINBOX;
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = VV4L2_CID_EXT_VPQ_EXTRA_PATTERN;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_EXTRA_PATTERN (V4L2_CID_EXT_VPQ_BASE + 35)

/**
 * @brief
 *   Stereo Face effect for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting Stereo Face effect for AI picture
 *   - Details of Feature
 *      Stereo Face effect is face recognition according to AI menu setting status and constraints.
 *      Controls the "AI StereoFace" function, one of the "AI Picture" functions. Turn "AI StereoFace" on/off with VIDIOC_S_CTRL.
 *      Returns on/off/demo status of AI StereoFace function as VIDIOC_G_CTRL.
 *      The demo mode is used in special case such as h/w defect test manufacture site. In demo mode, 3d effect can be on/off by toggle.
 *   - Target Hardware Block
 *      AI PQ block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL        // Set PQ Data
 *     VIDIOC_G_CTRL        // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL
 *
 *     //
 *     // parameter
 *     //
 *     V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL {
 *     #define V4L2_VPQ_EXT_STEREO_FACE_OFF   (0)             // off
 *     #define V4L2_VPQ_EXT_STEREO_FACE_ON    (1)             // normal on
 *     #define V4L2_VPQ_EXT_STEREO_FACE_DEMO  (2)             // demo mode
 *     }
 *
 * Return Value
 *   If the function succeeds, the return value is OK.
 *
 *   If the function fails, the return value is NOT_OK.
 *
 * Remarks
 *   In this function, there are some access the LG DB to get the data set for
 *   vendor-specific chip API. But this process should not be concerned by chip
 *   vendor. Thus, at the first of this function, the "chip-specific data
 *   structure" should be declared locally. The "chip-specific data structure"
 *   is identical to the data structure which is used as the input parameter of
 *   the vendor-specific chip API function. And, after the declaration the
 *   structure, the data for "chip-specific data structure" have to be assigned
 *   with the best sample values. The values is to make the vendor-specific
 *   chip API function work normally.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL;
 *     control.value = V4L2_VPQ_EXT_STEREO_FACE_ON;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL (V4L2_CID_EXT_VPQ_BASE + 36)

/**
 * @brief
 *   Defines the Control ID to get video latency timing info.
 *
 * @deprecated
 *   Deprecated since webOS 6.0, it will be removed from webOS 24
 *
 * @rst
 * .. warning::
 *   Not use.
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_VIDEO_LATENCY (V4L2_CID_EXT_VPQ_BASE + 37)

/**
 * @brief Set extra PQDB data to driver for special case
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for setting extra PQDB data to driver for special case
 *   - Details of Feature
 *      This function transfers extra PQDB data to external 2nd chip(like FRC)
 *      Currently, it will be used for only for LG SoC platform
 *   - Target Hardware Block
 *      2nd chip like external FRC
 *   - Call frequency and timing
 *      Event : triggered by system power off_on
 *
 * Responses to abnormal situations, including
 *   Nothingspecial requirements.
 *
 * Performance Requirements
 *   Nothingspecial requirements.
 *
 * Constraints
 *   Nothingspecial requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VPQ_DB_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_vpq_cmn_data
 *     cf... (struct v4l2_ext_cm_info *)stContainer.p_data *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can Set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_S_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OBC Ctrl
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct pqdb_dc_db_f20 pqdbData;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     PQDB_Get_DB_Data(&pqdbData);
 *     pqData.version=1;
 *     pqData.length = sizeof(pqdbData);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&pqdbData;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DB_DATA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DB_DATA (V4L2_CID_EXT_VPQ_BASE + 38)

/**
 * @brief
 *   Defines the Control ID to subscribe Video latency time.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for subscribing video latency time.
 *   - Details of Feature
 *      This function is used to adjust audio and video sync. Driver should make the
 *      EVENT of file_handler whenever video latency time changed. For example input,
 *      TruMotion, game mode changed. Don't create EVENT while doing input chage. 
 *      EVENT should be created by stable information of input timing after input change finished.
 *      Time unit is 1/1000second(ms)
 *        - After the event of "V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY" is registered by
 *          the command of "VIDIOC_SUBSCRIBE_EVENT" in driver, driver should generate
 *          the event of "V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY" when video latency time
 *          changed
 *        - Driver should implement epoll() operation for this flow. You need to
 *          implement the feature of epoll() in driver side. User client gets the
 *          kernel event from epoll().
 *   - Target Hardware Block
 *      NA
 *   - Call frequency and timing
 *      It is called once when the video latency time needs to be subscribed.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no flicker transient during operation.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 *     // data[0] - low bit of time
 *     // data[1] - high bit of time.
 *     // data[2~63] - reserved
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY;
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY;
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     //de queue
 *     struct v4l2_event ev{0};
 *     ioctl(fd, VIDIOC_DQEVENT, &ev);
 *
 *     if(ev.id == V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY)
 *     {
 *         uint16 videoLatency = ev.u.data[1] << 8 + ev.u.data[0];
 *         // use videoLatency
 *         // luna send to audio service
 *     }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY (V4L2_CID_EXT_VPQ_BASE + 39)

/**
 * @brief
 *   Control video 10to11_bit conversion apl gain setting
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for 10to11-bit conversion block registers
 *      especially, focused on apl gain control of the block
 *   - Details of Feature
 *      apl gain mapping table used for the conversion block
 *   - Target Hardware Block
 *      post HDR(it handle conversion from 10bit to 11bit of bit resolution)
 *   - Call frequency and timing
 *      Periodical Polling : triggered by platform's runtime algorithm
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements
 *
 * Performance Requirements
 *   Nothing special requirements
 *
 * Constraints
 *   Nothing special requirements
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT
 *     //
 *     // parameter
 *     //
 *     p_data = chipdata
 *
 * Return Value
 *    If the function succeeds, the return value is OK.
 *
 *    If the function fails, the return value is NOT_OK.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *             Set Luminence boost LUT
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set OLED Luminance Boost
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_vpq_cmn_data pqData;
 *     struct v4l2_vpq_phdr_apl_gain_lut v4l2PostHdrAplGain;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&v4l2PostHdrAplGain, 0, sizeof(v4l2_vpq_phdr_apl_gain_lut));
 *     PQDB_Get_DB_Data(&v4l2PostHdrAplGain);
 *     pqData.version=1;
 *     pqData.length = sizeof(v4l2_vpq_phdr_apl_gain_lut);
 *     pqData.wid=0;
 *     pqData.pData = (unsigned char *)&v4l2PostHdrAplGain;;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT (V4L2_CID_EXT_VPQ_BASE + 40)

/**
 * @brief To set/get the register directly
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      To set/get the register directly
 *   - Details of Feature
 *      * registerAddress - the address of the register
 *      * registerMask - the bit-mask of the register
 *      * registerValue - the value of the register
 *
 *      When accessreg option is write, set the register directly with VIDIOC_S_EXT_CTRLS. When accessreg option is not write,
 *      get the register directly with VIDIOC_G_EXT_CTRLS.
 *
 *   - Target Hardware Block
 *      PQ related register
 *   - Call frequency and timing
 *      When an DebuggingData indicates accessreg, it may be sent.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set Register
 *     VIDIOC_G_EXT_CTRLS       // Get Register
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_REGISTER_CTRL
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vpq_register_data
 *     {
 *       unsigned int registerAddress;
 *       unsigned int registerMask;
 *       unsigned int registerValue;
 *     };
 *
 *     struct v4l2_ext_vpq_register_ctrl
 *     {
 *       unsigned int number __aligned(8);


 *       union {
 *               v4l2_ext_vpq_register_data *registerData;

 *               unsigned int compat_registerData;

 *               unsigned long long sizer;
 *     };
 *
 * Return Value
 *    If the function succeeds, the return value is OK.
 *
 *    If the function fails, the return value is NOT_OK.
 *
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Register
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_register_ctrl registerCtrl;
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(struct v4l2_ext_vpq_cmn_data));
 *     memset(&registerCtrl, 0, sizeof(struct v4l2_ext_vpq_register_ctrl));
 *
 *     struct v4l2_ext_vpq_register_data regData[reg_number] = {{0,},};
 *     ...
 *
 *     registerCtrl.number = reg_number;
 *     registerCtrl.registerData = regData;
 *
 *     pqData.version=1;
 *     pqData.length = sizeof(struct v4l2_ext_vpq_register_ctrl);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&registerCtrl;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_REGISTER_CTRL;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */

#define V4L2_CID_EXT_VPQ_REGISTER_CTRL (V4L2_CID_EXT_VPQ_BASE + 41)

/**
 * @brief
 *   Send LUT for DBC(Delta Brightness Compensation)
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Send LUT for DBC(Delta Brightness Compensation)
 *   - Details of Feature
 *      Delta Brightness Compensation is a function for compensating the Contrast and Brightness of video
 *      according to the framerate of the VRR signal.
 *      The LUT consists of Framerate and Contrast/Brightness values.
 *      When the signal is VRR, set the Contrast and Brightness values
 *      corresponding to the frame rate to the target H/W.
 *      The range of Contrast and Brightness values is 0~512, and 512 is a bypass value that is not corrected.
 *      If the signal is not VRR, set the bypass value.
 *   - Target Hardware Block
 *      Contrast & Brightness Control Block
 *      (It must be separated from the Contast/Brightness setting block of V4L2_CID_EXT_VPQ_PICTURE_CTRL.)
 *   - Call frequency and timing
 *      It will called when power on(DC/AD Power)
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   No constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT
 *
 *     //
 *     // parameter
 *     //
 *     #define DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE 17
 *     struct v4l2_ext_vpq_delta_brightness_conpensation_lut {
 *         unsigned short input_freq[DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
 *         unsigned short contrast_gain[DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
 *         unsigned short brightness_gain [DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of LUT
 *       STORE LUT for reference
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     //Store the LUT of DBC
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     struct v4l2_ext_vpq_delta_brightness_conpensation_lut dbc_lut =
 *     {
 *         { 48, 52, 57, 61, 66, 70, 75, 79, 84, 88, 93, 97, 102, 106, 111, 115, 120 },
 *         { 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512 },
 *         { 512, 511, 511, 510, 509, 509, 508, 506, 505, 505, 504, 504, 503, 502, 501, 500, 499 },
 *     };
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&dbc_lut, 0, sizeof(dbc_lut));
 *     pqData.version=0x50;
 *     pqData.length = sizeof(v4l2_ext_vpq_delta_brightness_conpensation_lut);
 *     pqData.wid=0;
 *     pqData.p_data=(unsigned char*)&dbc_lut;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT (V4L2_CID_EXT_VPQ_BASE + 42)

/**
 * @brief
 *   Send enable bits of gamut blocks for multiwindow gamut setting
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Send enable bits of gamut blocks for multiwindow gamut setting
 *   - Details of Feature
 *      enable/disable gamma/degamma/3x3 gamut/gamut 3d lut block
 *   - Target Hardware Block
 *      color gamut(Gamma/De-gamma/3x3 gamut/gamut 3d lut)
 *   - Call frequency and timing
 *      when video signal changed(input changed, videoInfo changed, ..)
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements
 *
 * Constraints
 *   No constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE
 *
 *     //
 *     // parameter
 *     //
 *     bool gamut_enable[4] = {
 *         1, // gamma
 *         1, // degamma
 *         1, // 3x3 gamut
 *         0, // gamut 3d lut
 *     };
 *
 * Return Value
 *   - On success 0 is returned, on error -1 and the ``errno`` variable is set
 *     appropriately. The generic error codes are described at the
 *     :ref:`Generic Error Codes <gen-errors>` chapter.
 *   - If SoC not support this API, return error -1 and errno = ENOTTY
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the value of LUT
 *       SET enable bit for each block
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     bool gamut_enable[4] = {0,0,1,0};
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version=0x60;
 *     pqData.length = sizeof(gamut_enable);
 *     pqData.wid=wID; // 0:MAIN, 1~:SUB#
 *     pqData.p_data=(unsigned char*)gamut_enable;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *     // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE (V4L2_CID_EXT_VPQ_BASE + 43)

/**
 * @brief
 *   Defines the Control ID to subscribe the BSP Error Log.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used for subscribing the BSP Error Log.
 *   - Details of Feature
 *      This function is used to send the error message of PQ BSP. Driver should make the
 *      EVENT of file_handler when an error occurs in PQ BSP.
 *      Time unit is 1/1000second(ms)
 *        - After the event of "V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR" is registered by
 *          the command of "VIDIOC_SUBSCRIBE_EVENT" in driver, driver should generate
 *          the event of "V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR" when the BSP error is detectied.
 *        - Driver should implement epoll() operation for this flow. You need to
 *          implement the feature of epoll() in driver side. User client gets the
 *          kernel event from epoll().
 *   - Target Hardware Block
 *      NA
 *   - Call frequency and timing
 *      It is called from BSP-side when there are the error in PQ BSP.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   There should be no effect to screen.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 *     data[64] - error description string(Maximum string size 63)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     // Get data
 *     ioctl(fd, VIDIOC_DQEVENT, &ev);
 *
 *      if(ev.id == V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR)
 *      {
 *          // get error description string data[64];
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR (V4L2_CID_EXT_VPQ_BASE + 44)

/**
 * @brief
 *   Defines the Control ID to control OLED APL's
 *   max value.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Transfer the received integer value to FW.
 *      Increase luminance by changing the max value of OLED APL according
 *      to the color temperature UI value in a specific video mode.
 *
 *   - Target Hardware Block
 *      OLED t-con.
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before,
 *      webOS will not send it again
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   When changing the weight value, a smooth brightness change
 *   should be applied without any transient effects
 *   such as flicker.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL // Set PQ Data
 *     VIDIOC_G_CTRL // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT
 *
 *     //
 *     // parameter
 *     //
 *     Int
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
  *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *              //Set color temperature value
 *              IF any error has occurred THEN
 *                        RETURN NOT_OK
 *              END IF
 *                        RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT;
 *     control.value = 0;
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT (V4L2_CID_EXT_VPQ_BASE + 45)

/**
 * @brief
 *   Set MCC data table
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      For setting MCC data table
 *      MCC is a new feature that is a function that improves the color temperature.
 *      MCC has RGB gain/offset, Luma LUT and Saturation LUT register.
 *      MCC uses an extended 13bit, which allows to increase the color temperature without losing luminance.
 *   - Details of Feature
 *      The function set MCC data table for MCC enable and RGB gain / offset
 *      MCC enable is a register that enables MCC block
 *      RGB gain / offset are functions to adjust the color temperature of White.
 *   - Target Hardware Block
 *      MCC block (Multi Color temperature Compensation)
 *   - Call frequency and timing
 *      This structure only works when the MCC enable bit = 1
 *      Transfer the MCC data to the bsp according to the conditions (Color Adjustment UI)
 *      Call this API once according to UI (100 step Color temperature) change
 *      The received data to the BSP is simply written in the MCC register Then the color temperature of the white is changed
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   Depending on the Color temperature value (W50~C50) , the MCC data is transfered differently.
 *   Data and LUT size can be changed by SoC spec
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VPQ_MCC_DATA
 *
 *     //
 *     // parameter
 *     //
 *
 *     p_data = chipdata
 *
 * Return Value
 *
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set MCC data
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     v4l2_ext_vpq_mcc_data stMccData;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_PHDR_MCC_DATA_T));
 *     memset(&stMccData, 0, sizeof(v4l2_ext_vpq_mcc_data));
 *     PQDB_Get_DB_Data(&stMccData);
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(HAL_VPQ_PHDR_MCC_DATA_T);
 *     pqData.wId=0;
 *     pqData.pData=(char*)&stMccData;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_VPQ_MCC_DATA;
 *     ext_control.ptr = (void *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */

#define V4L2_CID_EXT_VPQ_MCC_DATA (V4L2_CID_EXT_VPQ_BASE + 46)

/**
 * @brief
 *   Set MCC LUT table
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      For setting MCC data table
 *      MCC is a new feature that is a function that improves the color temperature.
 *      MCC has RGB gain/offset, Luma LUT and Saturation LUT register.
 *      MCC uses an extended 13bit, which allows to increase the color temperature without losing luminance.
 *   - Details of Feature
 *      The function set MCC LUT data for luma and saturation LUT
 *      MCC luma LUT is a table that adjusts Y (luminance level)
 *      MCC satu LUT is  a table that adjusts Saturation for white-color
 *   - Target Hardware Block
 *      MCC block (Multi Color temperature Compensation)
 *   - Call frequency and timing
 *      This structure only works when the MCC enable bit = 1 (MCC enable bit is included in V4L2_CID_EXT_VPQ_MCC_DATA)
 *      Transfer the MCC data to the bsp according to the conditions (Color Adjustment UI)
 *      Call this API once according to UI (Color Adjustment) change
 *      The received data to the BSP is simply written in the MCC register Then the color temperature of the white is changed
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Function should return ASAP
 *
 * Constraints
 *   Depending on the Color Adjustment value (off/low/medium/high) , the MCC data is transfered differently.
 *   Data and LUT size can be changed by SoC spec
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VPQ_MCC_LUT
 *
 *     //
 *     // parameter
 *     //
 *
 *     p_data = chipdata
 *
 * Return Value
 *
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *         Set MCC LUT
 *         IF any error has occurred THEN
 *             RETURN NOT_OK
 *         RETURN OK
 *     }
 *
 * Example
 *	.. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_ext_vpq_cmn_data pqData;
 *     v4l2_ext_vpq_mcc_lut stMccLut;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(PQ_PHDR_MCC_LUT_T));
 *     memset(&stMccLut, 0, sizeof(v4l2_ext_vpq_mcc_lut));
 *     PQDB_Get_Data(&stMccLut);
 *     //PQ DATA
 *     pqData.version=1;
 *     pqData.length = sizeof(HAL_VPQ_PHDR_MCC_LUT_T);
 *     pqData.wId=0;
 *     pqData.pData=(char*)&stMccLut;
 *     //EXT CONTROL
 *     ext_control.id = V4L2_CID_EXT_VPQ_MCC_LUT;
 *     ext_control.ptr = (void *)&pqData;
 *     //EXT CONTROLS
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement

 * @endrst
 */

#define V4L2_CID_EXT_VPQ_MCC_LUT (V4L2_CID_EXT_VPQ_BASE + 47)

#define V4L2_CID_EXT_AIPQ_BASE (V4L2_CID_USER_EXT_PQ_BASE + 0x500)

/**
 * @brief Set/Get SQM Mode for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for set/getting SQM Mode for AI picture
 *   - Details of Feature
 *      SQM(Source Quality Measurement) is used for estimating original source quality. Analysis the original resolution of the input image
 *      and apply the PQ DB based on it.
 *      Controls the "AI SQM" function, one of the "AI Picture" functions. Turn "AI SQM" on/off with VIDIOC_S_CTRL.
 *      Returns on/off status of AI SQM function as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ Mode
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_SQM_MODE
 *
 *     //
 *     // parameter
 *     //
 *     0(Off), 1(On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set/get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_SQM_MODE;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_SQM_MODE (V4L2_CID_EXT_AIPQ_BASE + 0)

/**
 * @brief Set/Get Super Resolution Mode for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for set/getting Super Resolution Mode for AI picture
 *   - Details of Feature
 *      AI SR(Super Resolution) improves detailed expression by removing noise from low-resolution images
 *      and converting them to high-resolution.
 *      Controls the "AI SR" function, one of the "AI Picture" functions. Turn "AI SR" on/off with VIDIOC_S_CTRL.
 *      Returns on/off/demo_on status of AI SR function as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ Mode
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_SR_MODE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_aipq_mode {
 *          V4L2_EXT_AIPQ_MODE_OFF = 0,
 *          V4L2_EXT_AIPQ_MODE_ON = 1,
 *          V4L2_EXT_AIPQ_MODE_DEMO_ON = 2,
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set/get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_SR_MODE;
 *     control.value = V4L2_EXT_AIPQ_MODE_ON;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_SR_MODE (V4L2_CID_EXT_AIPQ_BASE + 1)

/**
 * @brief Set/Get Depth for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for set/getting Depth for AI picture
 *   - Details of Feature
 *      Controls the "AI Depth" function, one of the "AI Picture" functions. Turn "AI Depth" on/off with VIDIOC_S_CTRL.
 *      Returns on/off/demo_on status of AI Depth function as VIDIOC_G_CTRL. When the "AI Depth" function is turned on,
 *      the "Depth Map" or "Depth APL" information of the image is created through AI Deep Learning. The generated
 *      information is used for tuning such as sharpness/contrast according to the request of the PQ Team.
 *      And, the "Depth APL" information is included in the data transmitted by V4L2_CID_EXT_VPQ_OBC_DATA.
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not  send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ Mode
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_DEPTH_MODE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_aipq_mode {
 *          V4L2_EXT_AIPQ_MODE_OFF = 0,
 *          V4L2_EXT_AIPQ_MODE_ON = 1,
 *          V4L2_EXT_AIPQ_MODE_DEMO_ON = 2,
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set/get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_DEPTH_MODE;
 *     control.value = V4L2_EXT_AIPQ_MODE_ON;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_DEPTH_MODE (V4L2_CID_EXT_AIPQ_BASE + 2)

/**
 * @brief Set/Get SCENE Detect Mode for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for set/getting SCENE Detect Mode for AI picture
 *   - Details of Feature
 *      Picture quality setting according to the scene (building/landscape/night view/indoor) by AI scene recognition function.
 *      Controls the "AI SCENE" function, one of the "AI Picture" functions. Turn "AI SCENE" on/off with VIDIOC_S_CTRL.
 *      Returns on/off status of AI SCENE function as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ Mode
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_SCENE_MODE
 *
 *     //
 *     // parameter
 *     //
 *     0(Off), 1(On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set/get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_SCENE_MODE;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_SCENE_MODE (V4L2_CID_EXT_AIPQ_BASE + 3)

/**
 * @brief Get a result of SCENE Detect
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting a scene_info of SCENE Detect
 *   - Details of Feature
 *      Returns SceneInfo(STANDARD, BUILDING, LANDSCAPE, NIGHT) of SCENE Detect as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      Periodical Polling : When the AI Scene is active, it is called every second. (1 sec)
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_SCENE_INFO
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_aipq_scene_info
 *     {
 *         V4L2_EXT_AIPQ_SCENE_STANDARD = 0,
 *         V4L2_EXT_AIPQ_SCENE_BUILDING = 1,
 *         V4L2_EXT_AIPQ_SCENE_LANDSCAPE = 2,
 *         V4L2_EXT_AIPQ_SCENE_NIGHT = 3,
 *         V4L2_EXT_AIPQ_SCENE_INFO_MAX
 *     };
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *   This control id supports VIDIOC_G_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_SCENE_INFO;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_SCENE_INFO (V4L2_CID_EXT_AIPQ_BASE + 4)

/**
 * @brief Set/Get Genre Selection Mode for AI picture
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for set/getting Genre Selection Mode for AI picture
 *   - Details of Feature
 *      Analyze the genre of content based on the input image and automatically provide a user-specified picture quality mode.
 *      Controls the "AI GENRE" function, one of the "AI Picture" functions. Turn "AI GENRE" on/off with VIDIOC_S_CTRL.
 *      Returns on/off status of AI GENRE function as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ Mode
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_GENRE_MODE
 *
 *     //
 *     // parameter
 *     //
 *     0(Off), 1(On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set/get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_GENRE_MODE;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_GENRE_MODE (V4L2_CID_EXT_AIPQ_BASE + 5)

/**
 * @brief Get a result of Auto Genre Selection
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting a genre_info of Auto Genre Selection
 *   - Details of Feature
 *      Returns GenreInfo(STANDARD, SPORTS, ANIMATION, MOVIE) of Auto Genre Selection as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      Periodical Polling : When the AI Genre is active, it is called every second. (1 sec)
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL      // Get AIPQ Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_GENRE_INFO
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_aipq_genre_info
 *     {
 *         V4L2_EXT_AIPQ_GENRE_STANDARD = 0,
 *         V4L2_EXT_AIPQ_GENRE_SPORTS = 1,
 *         V4L2_EXT_AIPQ_GENRE_ANIMATION = 2,
 *         V4L2_EXT_AIPQ_GENRE_MOVIE = 3,
 *         V4L2_EXT_AIPQ_GENRE_INFO_MAX
 *     };
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *   This control id supports VIDIOC_G_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_GENRE_INFO;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_GENRE_INFO (V4L2_CID_EXT_AIPQ_BASE + 6)

/**
 * @brief Set AI PQ's NPU access permission
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for control AI PQ's NPU access permission
 *   - Details of Feature
 *      As a temporal method to control NPU's resource,
 *      AI PQ's NPU permission should be controled
 *   - Target Hardware Block
 *      AI PQ Block
 *   - Call frequency and timing
 *      When an event of other NPU use case occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   In the case of AI functions that need to refer to the video buffer, if the NN path is not located in the SVP (Secure Video Path),
 *   do not perform the function in the SVP_ON situation even if AI is On.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL      // Set AIPQ's NPU access permission
 *     VIDIOC_G_CTRL      // Get AIPQ's NPU access permission
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_AIPQ_NPU_ENABLE
 *
 *     //
 *     // parameter
 *     //
 *     bool (false : disable AI PQ's NPU access, true : permit AI PQ's NPU access)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_AIPQ_NPU_ENABLE;
 *     control.value = true;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_AIPQ_NPU_ENABLE (V4L2_CID_EXT_AIPQ_BASE + 7)

/**
 * @brief
 *   Get information of video pattern
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      for getting information of video pattern
 *   - Details of Feature
 *      Transmission of image characteristic information is required to improve compression quality performance.
 *      Returns information of video pattern as VIDIOC_G_CTRL.
 *   - Target Hardware Block
 *      Videopattern Block
 *   - Call frequency and timing
 *      This API be called once when user wants to get information of video pattern.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special requirements.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get info of video pattern
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO
 *
 *     //
 *     // parameter
 *     //
 *     char* pPatternInfo         [IN]
 *
 *
 * Return Value
 *   If the function succeeds, the return value is OK.
 *
 *   If the function fails, the return value is NOT_OK.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *
 *       IF patternInfo == NULL THEN
 *           RETURN NOT_OK
 *       END IF
 *       IF pqData.length < (size of patternInfo) THEN
 *           RETURN NOT_OK
 *       END IF
 *
 *       COPY patternInfo to pqData.p_data
 *       WRITE size of patternInfo to pqData.length

 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Histo Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     char patternInfo[500] = {0,};
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     pqData.version = 1;
 *     pqData.length = sizeof(patternInfo);
 *     pqData.p_data =(unsigned char*)patternInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO (V4L2_CID_USER_EXT_PQ_BASE + 0x601)

#define V4L2_CID_EXT_VPQ_BASE_COMMER (V4L2_CID_USER_EXT_PQ_BASE + 0xA00)

/**
 * @brief Set degamma regamma data
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set Degamma Regamma for each color Gamut
 *   - Details of Feature
 *      For control EOTF(degamma) and OETF(regamma), need to deliver data to pqe
 *   - Target Hardware Block
 *      PQ Block
 *   - Call frequency and timing
 *      When an event of pq menu use case occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   Nothing special requirements.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA
 *
 *     //
 *     // parameter
 *     //
 *	   // struct v4l2_ext_vpq_degamma_regamma {
 *     	// degamma (EOTF) : 1024 entry (15bit resolution)
 *		union {
 *			unsigned short *u16pT_degamma;
 *			unsigned int compat_degamma;
 *			unsigned long long sizer_degamma;
 *		};
 *		unsigned int degamma_size_num;
 *		// regamma (OETF) : 2048 entry (12bit resolution)
 *		union {
 *			unsigned short *u16pT_regamma;
 *			unsigned int compat_regamma;
 *			unsigned long long sizer_regamma;
 *		};
 *		unsigned int regamma_size_num;
 *	   }
 *
 *
 * Return Value
 *   If the function succeeds, the return value is OK.
 *
 *   If the function fails, the return value is NOT_OK.
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *        WRITE DEGAMMA DATA
 *        WRITE REGAMMA DATA
 *        IF write OK
 *           value = OK
 *        ELSE
 *           value = NOT_OK
 *        RETURN value;
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Histo Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_ext_vpq_degamma_regamma degamma_regamma;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&degamma_regamma, 0, sizeof(v4l2_ext_vpq_degamma_regamma));
 *     pqData.version = 1;
 *     pqData.length = sizeof(v4l2_ext_vpq_degamma_regamma);
 *     pqData.p_data =(unsigned char*)&degamma_regamma;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA (V4L2_CID_EXT_VPQ_BASE_COMMER)

/**
 * @brief Set frame delay mode data
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set  Set frame delay mode data
 *   - Details of Feature
 *      For control frame delay mode to One frame delay which control screen sync difference between many sets.
 *   - Target Hardware Block
 *      PQEFW
 *   - Call frequency and timing
 *      When an event of pq menu use case occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special requirements. See "Return Value" for generic things.
 *
 * Performance Requirements
 *   When deliver delay data, video must change immediately
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE
 *
 *     //
 *     // parameter
 *     //
 *	   struct v4l2_ext_vpq_frame_delay_mode {
 *	   // Frame delay mode
 *	   // delay mode : 0 -> Not use. Defend on LOW_DELAY, MEMC_DELAY
 *	   // delay mode : 1 -> One frame Delay Mode
 *     // delay mode : other -> TBD
 *		unsigned int frame_delay_mode;
 *	   }
 *
 *
 * Return Value
 *   If the function succeeds, the return value is OK.
 *
 *   If the function fails, the return value is NOT_OK.
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *        WRITE DELAY MODE DATA
 *        IF write OK
 *           value = OK
 *        ELSE
 *           value = NOT_OK
 *        RETURN value;
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     v4l2_vpq_cmn_data pqData;
 *     v4l2_ext_vpq_frame_delay_mode frame_delay_mode;
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pqData, 0, sizeof(v4l2_vpq_cmn_data));
 *     memset(&frame_delay_mode, 0, sizeof(v4l2_ext_vpq_frame_delay_mode));
 *     pqData.version = 1;
 *     pqData.length = sizeof(v4l2_ext_vpq_frame_delay_mode);
 *     pqData.p_data =(unsigned char*)&frame_delay_mode;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE;
 *     ext_controls.controls->ptr = (void *)&pqData;
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls); // implement
 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE (V4L2_CID_EXT_VPQ_BASE_COMMER + 1)

/**
 * @brief Set offset, gain and WB_GAIN_STEP2 value of RGB for adjusting signage Colortemperature
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      Set offset, gain and WB_GAIN_STEP2 value of RGB for adjusting signage Colortemperature
 *   - Details of Feature
 *      Gain Value mapping
 *         +---------------------------+
 *         | passed Value      | Gain  |
 *         +===========================+
 *         | 0                 | 0.5   |
 *         +---------------------------+
 *         | 192               | 1.0   |
 *         +---------------------------+
 *         | 255               | 1.164 |
 *         +---------------------------+
 *      Offset Value mapping
 *         +---------------------------+
 *         | passed Value      | Offset|
 *         +===========================+
 *         | 0                 | -64   |
 *         +---------------------------+
 *         | 64                |  0    |
 *         +---------------------------+
 *         | 127               |  63   |
 *         +---------------------------+
 *      set OVI_HW_XXX(chip name)_WB_GAIN_STEP2 to 38
 *   - Target Hardware Block
 *      RGB gain/offset(Color Temperature) Block
 *   - Call frequency and timing
 *      When an event such as UI/Input/App change occurs, it may be sent.
 *      But if the value(parameter) is exactly same as just before, webOS will not send it again.
 *
 * Responses to abnormal situations, including
 *   Nothing special. see return value field.
 *
 * Performance Requirements
 *   Nothing special.
 *
 * Constraints
 *   Nothing special.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS       // Set PQ Data
 *     VIDIOC_G_EXT_CTRLS       // Get PQ Data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VPQ_SIGNAGE_COLORTEMP_DATA
 *
 *     //
 *     // parameter
 *     //
 *     stContainer          [IN]      v4l2_vpq_cmn_data
 *
 *     cf... (struct v4l2_ext_vpq_color_temp *)stContainer.p_data
 *     stChipData.pData [IN] chip data for color temperature
 *     struct v4l2_ext_vpq_color_temp {
 *         unsigned short rgb_gain[3];   ///< gain. 0:red, 1:green, 2:blue
 *         unsigned short rgb_offset[3]; ///< offset. 0:red, 1:green, 2:blue
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Color temperature Data
 *     v4l2_ext_controls ext_controls;
 *     struct v4l2_vpq_cmn_data stPqContainer;
 *     struct v4l2_ext_vpq_color_temp stRealInfo;
 *     unsigned char gain[v4l2_vpq_rgb_max] = {192,192,192};
 *     unsigned char offset[v4l2_vpq_rgb_max] = {64,64,64};
 *     ...
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&stPqContainer, 0, sizeof(stPqContainer));
 *     memset(&stRealInfo, 0, sizeof(stRealInfo));
 *     memcpy(stRealInfo.rgb_gain, gain, sizeof(stRealInfo.rgb_gain));
 *     memcpy(stRealInfo.rgb_offset, offset, sizeof(stRealInfo.rgb_offset));
 *     ...
 *     stPqContainer.version=1;
 *     stPqContainer.length = sizeof(stRealInfo);
 *     stPqContainer.wId=0;
 *     stPqContainer.p_data=(unsigned char *)&stRealInfo;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VPQ_SIGNAGE_COLORTEMP_DATA;
 *     ext_controls.controls->ptr = (void *)&stPqContainer;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls); // implement

 *
 * @endrst
 */
#define V4L2_CID_EXT_VPQ_SIGNAGE_COLORTEMP_DATA (V4L2_CID_EXT_VPQ_BASE_COMMER + 2)



/******************************************************************************
            Constant Definitions
*******************************************************************************/

/**
  * LED SPI Control, v4l2_ext_led_spi_bit_mask
  */
#define V4L2_EXT_LED_SPI_LDIM_EN 0x01      // bit0		enable local dimming
#define V4L2_EXT_LED_SPI_BPL_BIT1 0x02     // bit1		bpl strength
#define V4L2_EXT_LED_SPI_STOREMODE_EN 0x04 // bit2		enable led store
                                           // mode
#define V4L2_EXT_LED_SPI_HALO_BIT1                                             \
    0x08                                   // bit3		halo reduction strength
#define V4L2_EXT_LED_SPI_MOTIONPRO_EN 0x10 // bit4		enable motion
                                           // pro
#define V4L2_EXT_LED_SPI_HALO_BIT2                                             \
    0x20                               // bit5		halo reduction strength
#define V4L2_EXT_LED_SPI_BPL_BIT2 0x40 // bit6		bpl strength
#define V4L2_EXT_LED_SPI_REVERSE 0x80  // bit7		screen reverse

/**
  * VPQ BYPASS, v4l2_ext_VPQ_BYPASS_mask
  */
#define V4L2_EXT_VPQ_BYPASS_MASK_NONE 0x00000000
#define V4L2_EXT_VPQ_BYPASS_MASK_SHARP_ENHANCE                                 \
    0x00000001 // BIT0: //SharpnessEnhancer
#define V4L2_EXT_VPQ_BYPASS_MASK_OBJECT_CONTRAST                               \
    0x00000002 // BIT1: //ObjectContrast
#define V4L2_EXT_VPQ_BYPASS_MASK_CONTRAST_COLOR_ENHANCE                        \
    0x00000004 // BIT2: //Contrast, Local Contrast, Color Enhancer
#define V4L2_EXT_VPQ_BYPASS_MASK_GAMMA_LOCALDIMMING                            \
    0x00000008 // BIT3: //Localdimming, Gamma UI
#define V4L2_EXT_VPQ_BYPASS_MASK_NEAR_BE                                       \
    0x00000010 // BIT4: //WB,DGA-4CH,POD,PCID,ODC
#define V4L2_EXT_VPQ_BYPASS_MASK_HDR_ALL 0x00000020 // BIT5: HDR
#define V4L2_EXT_VPQ_BYPASS_MASK_HDR_EXCEPT_PCC                                \
    0x00000040 // BIT6: //HDR bypass,HDR-PCC enable
#define V4L2_EXT_VPQ_BYPASS_MASK_FRC_ALL 0x00000080 // BIT7: FRC Bypass
#define V4L2_EXT_VPQ_BYPASS_MASK_FRC_MEMC                                      \
    0x00000100 // BIT8: //MEMC Bypass, FRC enable
#define V4L2_EXT_VPQ_BYPASS_MASK_RESERVED_1                                    \
    0x00000200 // BIT9: //Bypass reserve block1
#define V4L2_EXT_VPQ_BYPASS_MASK_RESERVED_2                                    \
    0x00000400 // BIT11: //Bypass reserve block2
#define V4L2_EXT_VPQ_BYPASS_MASK_RESERVED_3                                    \
    0x00000800 // BIT12: //Bypass reserve block3
#define V4L2_EXT_VPQ_BYPASS_MASK_ALL                                           \
    0xFFFFFFFF // VPQ Bypass All

// histogram bin, chroma bin num
#define V4L2_EXT_VPQ_BIN_NUM 64
#define V4L2_EXT_VPQ_C_BIN_NUM 32
#define V4L2_EXT_VPQ_H_BIN_NUM 32
#define V4L2_EXT_LED_SMART_ADJ_ON (0x10)

// PQ COMMON DATA TYPE
struct v4l2_ext_vpq_cmn_data {
    unsigned int version; ///< version = 0 : wild card(default data)
    unsigned int length;  ///< pData Length
    unsigned char wid;    ///< 0 : main
    union {
        unsigned char *p_data; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

//  LED Type Definition
/**
 * LOCALDIMMING DemoMode Type Enum.
*/
enum v4l2_ext_led_localdimming_demo_type {
    V4L2_EXT_LED_ONOFF = 0,   // each led block flicker sequentially.
    V4L2_EXT_LED_H_ONOFF_EXT, // led horizontal moving box pattern on for
                              // external localdimming chip.
    V4L2_EXT_LED_V_ONOFF_EXT, // led vertical moving box pattern on for external
                              // localdimming chip.
    V4L2_EXT_LED_SPLIT_SCREEN, // half of screen is made from white pattern, and
                               // show local dimming effect.
    V4L2_EXT_LED_DEMOTYPE_SIZE_MAX
};
/**
 * Backlight Type Enum.
*/
enum v4l2_ext_led_backlight_type {
    V4L2_EXT_LED_BACKLIGHT_DIRECT_L = 0,
    V4L2_EXT_LED_BACKLIGHT_EDGE_LED,
    V4L2_EXT_LED_BACKLIGHT_OLED,
    V4L2_EXT_LED_BACKLIGHT_DIRECT_VI,
    V4L2_EXT_LED_BACKLIGHT_DIRECT_SKY,
    V4L2_EXT_LED_BACKLIGHT_MINI_LED,
    V4L2_EXT_LED_BACKLIGHT_MLS,
    V4L2_EXT_LED_BACKLIGHT_END,
};

/**
 * Panel size Enum.
*/
enum v4l2_ext_led_panel_inch_type {
    V4L2_EXT_LED_INCH_32 = 0,
    V4L2_EXT_LED_INCH_39,
    V4L2_EXT_LED_INCH_42,
    V4L2_EXT_LED_INCH_47,
    V4L2_EXT_LED_INCH_49,
    V4L2_EXT_LED_INCH_50,
    V4L2_EXT_LED_INCH_55,
    V4L2_EXT_LED_INCH_58,
    V4L2_EXT_LED_INCH_60,
    V4L2_EXT_LED_INCH_65,
    V4L2_EXT_LED_INCH_70,
    V4L2_EXT_LED_INCH_77,
    V4L2_EXT_LED_INCH_79,
    V4L2_EXT_LED_INCH_84,
    V4L2_EXT_LED_INCH_98,
    V4L2_EXT_LED_INCH_105, // TV model
    V4L2_EXT_LED_INCH_23,
    V4L2_EXT_LED_INCH_24,
    V4L2_EXT_LED_INCH_26,
    V4L2_EXT_LED_INCH_27, // Smart Monitor TV
    V4L2_EXT_LED_INCH_22,
    V4L2_EXT_LED_INCH_28,
    V4L2_EXT_LED_INCH_40,
    V4L2_EXT_LED_INCH_43,
    V4L2_EXT_LED_INCH_86,
    V4L2_EXT_LED_INCH_BASE
};
/**
 * Panel Led_bar Type Enum.
*/
enum v4l2_ext_led_bar_type {
    V4L2_EXT_LED_BAR_6 = 0,
    V4L2_EXT_LED_BAR_12,
    V4L2_EXT_LED_BAR_32,
    V4L2_EXT_LED_BAR_36,
    V4L2_EXT_LED_BAR_40,
    V4L2_EXT_LED_BAR_48,
    V4L2_EXT_LED_BAR_50,
    V4L2_EXT_LED_BAR_90,
    V4L2_EXT_LED_BAR_96,
    V4L2_EXT_LED_BAR_120,
    V4L2_EXT_LED_BAR_60,
    V4L2_EXT_LED_BAR_144,
    V4L2_EXT_LED_BAR_108,
    V4L2_EXT_LED_BAR_160,
    V4L2_EXT_LED_BAR_720,
    V4L2_EXT_LED_BAR_960,
    V4L2_EXT_LED_BAR_1440,
    V4L2_EXT_LED_BAR_1800,
    V4L2_EXT_LED_BAR_1920,
    V4L2_EXT_LED_BAR_2400,
    V4L2_EXT_LED_BAR_1200,
    V4L2_EXT_LED_BAR_288,
    V4L2_EXT_LED_BAR_216,
    V4L2_EXT_LED_BAR_180,
    V4L2_EXT_LED_BAR_225,
    V4L2_EXT_LED_BAR_192,
    V4L2_EXT_LED_BAR_640,
    V4L2_EXT_LED_BAR_504,
    V4L2_EXT_LED_BAR_308,
    V4L2_EXT_LED_BAR_126,
    V4L2_EXT_LED_BAR_154,
    V4L2_EXT_LED_BAR_208,
    V4L2_EXT_LED_BAR_270,
    V4L2_EXT_LED_BAR_MAX,
    V4L2_EXT_LED_BAR_DEFALT = V4L2_EXT_LED_BAR_MAX,
};

/**
 * Panel Led_bar Type Enum.
*/
enum v4l2_ext_led_module_maker_type {
    V4L2_EXT_LED_MODULE_LGD = 0,
    V4L2_EXT_LED_MODULE_CMI,
    V4L2_EXT_LED_MODULE_AUO,
    V4L2_EXT_LED_MODULE_SHARP,
    V4L2_EXT_LED_MODULE_IPS,
    V4L2_EXT_LED_MODULE_BOE,
    V4L2_EXT_LED_MODULE_CSOT,
    V4L2_EXT_LED_MODULE_INNOLUX,
    V4L2_EXT_LED_MODULE_LCD_END,
    V4L2_EXT_LED_MODULE_LGE = V4L2_EXT_LED_MODULE_LCD_END,
    V4L2_EXT_LED_MODULE_PANASONIC,
    V4L2_EXT_LED_MODULE_PDP_END,
    V4L2_EXT_LED_MODULE_BASE = V4L2_EXT_LED_MODULE_PDP_END,
};
/**
 * Panel Led_Lut index.
*/
enum v4l2_ext_led_lut_number_type {
    V4L2_EXT_LED_LUT_FRIST = 0,
    V4L2_EXT_LED_LUT_SECOND,
    V4L2_EXT_LED_LUT_THIRD,
    V4L2_EXT_LED_LUT_MAX
};
/**
  * Local dimming block type
  */
enum v4l2_ext_led_ldim_ic {
    V4L2_EXT_LED_LDIM_NONE     = 0, // Not support Local dimming.
    V4L2_EXT_LED_LDIM_INTERNAL = 1, // Use internal Local dimming block.
    V4L2_EXT_LED_LDIM_EXTERNAL = 2, // Use external Local dimming IC.
};
/**
  * Panel type
  */
enum v4l2_ext_led_wcg_panel_type {
    V4L2_EXT_LED_WCG_PANEL_LED          = 0,
    V4L2_EXT_LED_WCG_PANEL_LED_ULTRAHD  = 1,
    V4L2_EXT_LED_WCG_PANEL_OLED         = 2,
    V4L2_EXT_LED_WCG_PANEL_OLED_ULTRAHD = 3
};
/**
 * Panel information
 */
struct v4l2_ext_led_panel_info {
    enum v4l2_ext_led_panel_inch_type panel_inch; // panel size   ex) 47, 55
    enum v4l2_ext_led_backlight_type
        backlight_type;                  // led backlight type  ex) alef, edge
    enum v4l2_ext_led_bar_type bar_type; // led bar type   ex) h6,h12, v12
    enum v4l2_ext_led_module_maker_type
        module_maker;                            // panel maker   ex) lgd, auo
    enum v4l2_ext_led_ldim_ic local_dim_ic_type; // localdimming control type
                                                 // ex) internal localdiming
                                                 // block
    enum v4l2_ext_led_wcg_panel_type panel_type;
};

struct v4l2_ext_led_panel_info_v2{
    enum v4l2_ext_led_backlight_type backlight_type;
    unsigned short horizontal_block_num;
    unsigned short vertical_block_num;
    unsigned int spi_speed_hz;
    short spi_signal_strength; // 0:default, -4,-3,-2,-1,0,1,2,3,4
    unsigned short spi_port;   // 0:default for lg model
    char led_driver_id[16];    // 'lge_default':default for lg model
};

/**
  * Local dimming Demo Mode
  */
enum v4l2_ext_led_ldim_demo_type {
    v4l2_ext_led_ldim_demo_type_linedemo  = 0,
    v4l2_ext_led_ldim_demo_type_leftright = 1,
    v4l2_ext_led_ldim_demo_type_topbottom = 2,
    v4l2_ext_led_ldim_demo_type_max
};
struct v4l2_ext_led_ldim_demo_info {
    enum v4l2_ext_led_ldim_demo_type eType;
    unsigned char bOnOff;
};
/**
  * Local dimming block apl info
  */
struct v4l2_ext_led_apl_info {
    unsigned short block_apl_min;
    unsigned short block_apl_max;
};
struct v4l2_ext_led_spi_ctrl_info {
    unsigned char bitMask; // see V4L2_EXT_LED_SPI_XXX for reference
    unsigned int ctrlValue;
};

/**
  * Local dimming block bpl info
  */
struct v4l2_ext_led_bpl_info {
    unsigned short ai_brightness;
    unsigned short sensor_level;
    unsigned short blooming_mode;
};

#define V4L2_EXT_LED_ABI_GAIN_LUT_SIZE (17)
struct v4l2_ext_led_abi_settings {
    unsigned short gain_step;
    unsigned short memc_info_diff;
    unsigned short gain_lut[V4L2_EXT_LED_ABI_GAIN_LUT_SIZE];     // if it's NULL, use BSP's default LUT data
};

struct v4l2_ext_led_abi_ctrl {
	// manual mode : Don't sync to the motion vector && received gain(manualGain) will be applied to the global duty
	// auto mode : the global duty will be sync to the motion vector. ignoring received manualGain
	unsigned char autoMode; // false(manual mode) , true(auto mode)
	unsigned char manualGain;
	struct v4l2_ext_led_abi_settings settings;
};

// MEMC Type Definition
enum v4l2_ext_memc_type_old {
    V4L2_EXT_MEMC_TYPE_OFF = 0,
    V4L2_EXT_MEMC_TYPE_LOW,
    V4L2_EXT_MEMC_TYPE_HIGH,
    V4L2_EXT_MEMC_TYPE_USER,
    V4L2_EXT_MEMC_TYPE_55_PULLDOWN,
    V4L2_EXT_MEMC_TYPE_MEDIUM,
    V4L2_EXT_MEMC_TYPE_OLD_MAX
};

enum v4l2_ext_memc_type {
    V4L2_EXT_MEMC_OFF          = V4L2_EXT_MEMC_TYPE_OFF,
    V4L2_EXT_MEMC_CINEMA_CLEAR = V4L2_EXT_MEMC_TYPE_MEDIUM,
    V4L2_EXT_MEMC_NATURAL      = V4L2_EXT_MEMC_TYPE_LOW,
    V4L2_EXT_MEMC_SMOOTH       = V4L2_EXT_MEMC_TYPE_HIGH, //
    V4L2_EXT_MEMC_USER         = V4L2_EXT_MEMC_TYPE_USER,
    V4L2_EXT_MEMC_PULLDOWN_55  = V4L2_EXT_MEMC_TYPE_55_PULLDOWN,
    V4L2_EXT_MEMC_SMALL_OBJ    = V4L2_EXT_MEMC_TYPE_OLD_MAX
};

struct v4l2_ext_memc_motion_comp_info {
    unsigned char blur_level;
    unsigned char judder_level;
    enum v4l2_ext_memc_type memc_type;
};

// VPQ Type Definition
enum v4l2_ext_vpq_rgb_index {
    V4L2_EXT_VPQ_RED     = 0,
    V4L2_EXT_VPQ_GREEN   = 1,
    V4L2_EXT_VPQ_BLUE    = 2,
    V4L2_EXT_VPQ_RGB_MAX = 3
};

#define V4L2_EXT_HDR_PICINFO_SIZE 128

// HDR Type Definition
struct v4l2_ext_hdr_color_correction {
    unsigned int hue_blend; ///< 0~1023
    unsigned int sat_blend; ///< 0~1023

    unsigned int l_gain_x[8]; // L gain LUT x point
    unsigned int l_gain_y[8]; // L gain LUT y point

    unsigned int s_gain_x[8]; // S gain LUT x point
    unsigned int s_gain_y[8]; // S gain LUT y point
};

enum v4l2_ext_hdr_mode {
    V4L2_EXT_HDR_MODE_SDR,
    V4L2_EXT_HDR_MODE_DOLBY,
    V4L2_EXT_HDR_MODE_HDR10,
    V4L2_EXT_HDR_MODE_HLG,
    V4L2_EXT_HDR_MODE_TECHNICOLOR,
    V4L2_EXT_HDR_MODE_HDREFFECT,
    V4L2_EXT_HDR_MODE_MAX
};

enum v4l2_ext_colorimetry_info {
    V4L2_EXT_COLORIMETRY_BT601,
    V4L2_EXT_COLORIMETRY_BT709,
    V4L2_EXT_COLORIMETRY_BT2020,
    V4L2_EXT_COLORIMETRY_MAX
};

struct v4l2_ext_pq_mode_info {
    unsigned int hdrStatus;     // see v4l2_ext_hdr_mode
    unsigned int colorimetry;   // see v4l2_ext_colorimetry_info
    unsigned int peakLuminance; // peakLuminance of panel
    unsigned int supportPrime;  // support Prime
    unsigned int reserved;
};

struct v4l2_ext_hdr_tonemap {
    enum v4l2_ext_hdr_mode hdr_mode;
    unsigned int r_data[66]; ///<0~4294967295, 33point x,y data
    unsigned int g_data[66]; ///<0~4294967295, 33point x,y data
    unsigned int b_data[66]; ///<0~4294967295, 33point x,y data
};

struct v4l2_ext_hdr_local_tonemap {
    unsigned int local_dtm_enable;              // Local DTM enable bit
    unsigned int local_dtm_peak_per;            // Local DTM percentage for deciding local peak
    unsigned int local_dtm_tone_idx[12];        // Local DTM peak index for each curve LUT
    unsigned int local_dtm_tone_lut[12][33];    // Local DTM curve LUT
};

struct v4l2_ext_hdr_3dlut {
    enum v4l2_ext_hdr_mode hdr_mode;
    unsigned int data_size;
    union {
        unsigned int *p3dlut; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

enum v4l2_ext_dolby_config_type {
    V4L2_EXT_DOLBY_CONFIG_MAIN = 0,
    V4L2_EXT_DOLBY_CONFIG_BEST
};

struct v4l2_ext_dolby_config_path {
    enum v4l2_ext_dolby_config_type eConfigType;
    char sConfigPath[255];
};

struct v4l2_ext_dolby_picture_mode {
    unsigned int bOnOff;
    unsigned int uPictureMode;
};

enum v4l2_ext_dolby_picture_menu {
    V4L2_EXT_DOLBY_BACKLIGHT = 0,   ///< backlight
    V4L2_EXT_DOLBY_BRIGHTNESS,      /// brightness
    V4L2_EXT_DOLBY_COLOR,           ///< color
    V4L2_EXT_DOLBY_CONTRAST,        ///< contrast
    V4L2_EXT_DOLBY_PICTURE_MENU_MAX ///< max num
};

struct v4l2_ext_dolby_picture_data {
    enum v4l2_ext_dolby_picture_menu picture_menu; ///< picture menu
    unsigned int on_off;                           ///<0:off, 1:on
    int setting_value;                             ///< setting value
};

struct v4l2_ext_dolby_gd_delay {
    unsigned short ott_24;
    unsigned short ott_30;
    unsigned short ott_50;
    unsigned short ott_60;
    unsigned short ott_100;
    unsigned short ott_120;

    unsigned short hdmi_24;
    unsigned short hdmi_30;
    unsigned short hdmi_50;
    unsigned short hdmi_60;
    unsigned short hdmi_100;
    unsigned short hdmi_120;
};

struct v4l2_ext_dolby_gd_delay_lut {
    struct v4l2_ext_dolby_gd_delay standard_frc_off;
    struct v4l2_ext_dolby_gd_delay standard_frc_on;

    struct v4l2_ext_dolby_gd_delay vivid_frc_off;
    struct v4l2_ext_dolby_gd_delay vivid__frc_on;

    struct v4l2_ext_dolby_gd_delay cinema_home_frc_off;
    struct v4l2_ext_dolby_gd_delay cinema_home_frc_on;

    struct v4l2_ext_dolby_gd_delay cinema_frc_off;
    struct v4l2_ext_dolby_gd_delay cinema_frc_on;

    struct v4l2_ext_dolby_gd_delay game_frc_off;
    struct v4l2_ext_dolby_gd_delay game_frc_on;
};

struct v4l2_ext_dolby_gd_delay_param {
    struct v4l2_ext_dolby_gd_delay_lut dolby_GD_standard;
    struct v4l2_ext_dolby_gd_delay_lut dolby_GD_latency;
};

struct v4l2_ext_dolby_ambient_light_param {
    unsigned int onoff;
    unsigned int luxdata;
    union {
        unsigned int *rawdata; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

// VPQ Type Definition
enum v4l2_ext_vpq_inner_pattern_ire {
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_0 = 0, ///< ire 0
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_2DOT5, ///< ire 2.5
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_5,     ///< ire 5
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_7DOT5, ///< ire 7.5
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_10,    ///< ire 10
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_15,    ///< ire 15
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_20,    ///< ire 20
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_25,    ///< ire 25
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_30,    ///< ire 30
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_35,    ///< ire 35
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_40,    ///< ire 40
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_45,    ///< ire 45
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_50,    ///< ire 50
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_55,    ///< ire 55
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_60,    ///< ire 60
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_65,    ///< ire 65
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_70,    ///< ire 70
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_75,    ///< ire 75
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_80,    ///< ire 80
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_85,    ///< ire 85
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_90,    ///< ire 90
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_95,    ///< ire 95
    V4L2_EXT_VPQ_INNER_PATTERN_IRE_100,   ///< ire 100
    V4L2_EXT_VPQ_INNER_PATTERN_DISABLE,   ///< disable IRE pattern

    V4L2_EXT_VPQ_INNER_PATTERN_24P_BASE = 0x100, ///< 24 point ire Base
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_0 = V4L2_EXT_VPQ_INNER_PATTERN_24P_BASE, ///< 24 point ire 0
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_1,        ///< 24 point ire 1
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_2,        ///< 24 point ire 2
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_3,        ///< 24 point ire 3
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_5,        ///< 24 point ire 5
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_7DOT5,    ///< 24 point ire 7.5
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_10,       ///< 24 point ire 10
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_15,       ///< 24 point ire 15
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_20,       ///< 24 point ire 20
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_25,       ///< 24 point ire 25
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_30,       ///< 24 point ire 30
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_35,       ///< 24 point ire 35
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_40,       ///< 24 point ire 40
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_45,       ///< 24 point ire 45
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_50,       ///< 24 point ire 50
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_55,       ///< 24 point ire 55
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_60,       ///< 24 point ire 60
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_65,       ///< 24 point ire 65
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_70,       ///< 24 point ire 70
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_75,       ///< 24 point ire 75
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_80,       ///< 24 point ire 80
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_85,       ///< 24 point ire 85
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_90,       ///< 24 point ire 90
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_95,       ///< 24 point ire 95
    V4L2_EXT_VPQ_INNER_PATTERN_24P_IRE_100,      ///< 24 point ire 100
    V4L2_EXT_VPQ_INNER_PATTERN_24P_DISABLE       ///< disable 24 point IRE pattern
};

enum v4l2_ext_vpq_input {
    V4L2_EXT_VPQ_INPUT_ATV = 0,     ///< analog rf
    V4L2_EXT_VPQ_INPUT_AV,          ///< cvbs,svideo
    V4L2_EXT_VPQ_INPUT_SCARTRGB,    ///< scart-rgb
    V4L2_EXT_VPQ_INPUT_COMP,        ///< component
    V4L2_EXT_VPQ_INPUT_RGB_PC,      ///< rgb-pc
    V4L2_EXT_VPQ_INPUT_HDMI_TV,     ///< hdmi non-pc(hdmi-av,dvi-dtv,mcam)
    V4L2_EXT_VPQ_INPUT_HDMI_PC,     ///< hdmi pc(dvi-pc)
    V4L2_EXT_VPQ_INPUT_DTV,         ///< digital rf
    V4L2_EXT_VPQ_INPUT_PICWIZ,      ///< dtv pic wiz
    V4L2_EXT_VPQ_INPUT_PICTEST,     ///< dtv pic test
    V4L2_EXT_VPQ_INPUT_MEDIA_MOVIE, ///< divx, cp-divx
    V4L2_EXT_VPQ_INPUT_MEDIA_PHOTO, ///< photo, cp-photo
    V4L2_EXT_VPQ_INPUT_CAMERA,      ///< vcs
    V4L2_EXT_VPQ_INPUT_PVR_DTV,     ///< pvr dtv
    V4L2_EXT_VPQ_INPUT_PVR_ATV,     ///< pvr atv
    V4L2_EXT_VPQ_INPUT_PVR_AV,      ///< pvr av,scart-rgb
    V4L2_EXT_VPQ_INPUT_MAX          ///< max num
};

struct v4l2_ext_vpq_dc2p_histodata_info {
    unsigned int apl;                              ///< apl
    signed int min;                                ///< min
    signed int max;                                ///< max
    signed int peak_low;                           ///< peak low
    signed int peak_high;                          ///< peak high
    unsigned int skin_count;                       ///< skin count
    unsigned int sat_status;                       ///< saturation status
    unsigned int diff_sum;                         ///< diff sum
    unsigned int motion;                           ///< motion
    unsigned int texture;                          ///< texture
    unsigned int bin[V4L2_EXT_VPQ_BIN_NUM];        ///< count bin
    unsigned int chrm_bin[V4L2_EXT_VPQ_C_BIN_NUM]; ///< count chroma bin
    unsigned int hue_bin[V4L2_EXT_VPQ_H_BIN_NUM];  ///< count chroma bin
};

struct v4l2_ext_vpq_color_temp {
    unsigned short rgb_gain[3];   ///< gain. 0:red, 1:green, 2:blue
    unsigned short rgb_offset[3]; ///< offset. 0:red, 1:green, 2:blue
};

struct v4l2_ext_vpq_gamut_add_info {
    unsigned int info_size;
    union {
        unsigned int *p_info_data; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_gamut_lut {
    unsigned int lut_version;
    unsigned int total_section_num;
    union {
        unsigned short *p_section_data; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
    struct v4l2_ext_vpq_gamut_add_info add_info;
};

struct v4l2_ext_oled_luminance_boost {
    unsigned int length; ///< LUT data size to get/set
    union {
        unsigned int *p_data; ///< 4-byte unit LUT data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_block_bypass {
    unsigned int bypassMask; // see V4L2_EXT_VPQ_BYPASS_MASK_XXX
    unsigned char bOnOff;
};

struct v4l2_ext_vpq_od {
    unsigned int length; ///< LUT data size
    union {
        unsigned char *p_data; ///< LUT data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_od_extension {
    unsigned char ext_type;  ///< 0: POD, 1: PCID, 2: NONE
    unsigned int ext_length; ///< LUT data size
    union {
        unsigned char *p_ext_data; ///< LUT data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

/**
* set gamma data
*/
struct v4l2_ext_gamma_lut {
    unsigned int table_num; // number of table elements
    union {
        unsigned int *table_red;
        unsigned int compat_table_red;
        unsigned long long sizer_r;
    };
    union {
        unsigned int *table_green;
        unsigned int compat_table_green;
        unsigned long long sizer_g;
    };
    union {
        unsigned int *table_blue;
        unsigned int compat_table_blue;
        unsigned long long sizer_b;
    };
};

/**
* set gamut matrix
*/
#define CSC_MUX_LUT_SIZE 4
struct v4l2_ext_csc_mux_lut {
    unsigned int mux_l3d_in;
    unsigned int mux_blend_in;
    unsigned int mux_4p_lut_in;
    unsigned int mux_oetf_out;
    unsigned int b4p_lut_x[CSC_MUX_LUT_SIZE];
    unsigned int b4p_lut_y[CSC_MUX_LUT_SIZE];
};

struct v4l2_ext_gamut_post {
    unsigned char gamma;
    unsigned char degamma;
    short matrix[9];
    struct v4l2_ext_csc_mux_lut mux_blend;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

#define CSC_PPCC_LUMA_SIZE 4
#define CSC_PPCC_SAT_SIZE 5

struct v4l2_vpq_csc_post_pcc_lut {
    unsigned int sat_gain;
    unsigned int hue_comp_gain;
    unsigned int sat_comp_gain;
    unsigned int luma_lut_x[CSC_PPCC_LUMA_SIZE];
    unsigned int luma_lut_y[CSC_PPCC_LUMA_SIZE];
    unsigned int sat_lut_x[CSC_PPCC_SAT_SIZE];
    unsigned int sat_lut_y[CSC_PPCC_SAT_SIZE];
};

struct v4l2_vpq_csc_luma_pcc_lut {
    short matrix_by_4level[4][9];
    unsigned char adaptive_y_en;
    unsigned int luma_th0;
    unsigned int luma_th1;
    unsigned int luma_th2;
    unsigned int luma_th3;
};

struct v4l2_ext_gamut_post_v2 {
    unsigned char gamma;
    unsigned char degamma;
    short matrix[9];
    struct v4l2_ext_csc_mux_lut mux_blend;
    struct v4l2_vpq_csc_post_pcc_lut post_pcc;
    struct v4l2_vpq_csc_luma_pcc_lut luma_pcc;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

/**
* ui type related to CM(color manager) per region
*/
enum v4l2_ext_cm_dynamic_color_level {
    V4L2_EXT_CM_DYNAMIC_COLOR_OFF     = 0,
    V4L2_EXT_CM_DYNAMIC_COLOR_LOW     = 1,
    V4L2_EXT_CM_DYNAMIC_COLOR_MEDIUM  = 2,
    V4L2_EXT_CM_DYNAMIC_COLOR_HIGH    = 3,
    V4L2_EXT_CM_DYNAMIC_COLOR_INVALID = 4
};
enum v4l2_ext_cm_perferred_color_type {
    V4L2_EXT_CM_PREFERRED_COLOR_SKIN    = 0,
    V4L2_EXT_CM_PREFERRED_COLOR_GRASS   = 1,
    V4L2_EXT_CM_PREFERRED_COLOR_SKYBLUE = 2,
    V4L2_EXT_CM_PREFERRED_COLOR_MAX
};
enum v4l2_ext_cm_cms_color_type { // Color Management System
    V4L2_EXT_CM_CMS_RED     = 0,
    V4L2_EXT_CM_CMS_GREEN   = 1,
    V4L2_EXT_CM_CMS_BLUE    = 2,
    V4L2_EXT_CM_CMS_CYAN    = 3,
    V4L2_EXT_CM_CMS_MAGENTA = 4,
    V4L2_EXT_CM_CMS_YELLOW  = 5,
    V4L2_EXT_CM_CMS_MAX
};
struct v4l2_ext_cm_dynamic_color_ui {
    unsigned char enable; // 0: don't reference preferred_value(expert_control),
                          // 1: reference preferred_value(not_use_cm_db==1 &&
                          // advanced_control)
    enum v4l2_ext_cm_dynamic_color_level value; // ui value
};
struct v4l2_ext_cm_perferred_color_ui {
    unsigned char enable; // 0: don't reference preferred_value(expert_control),
                          // 1: reference preferred_value(advanced_control)
    signed char
        value[V4L2_EXT_CM_PREFERRED_COLOR_MAX]; // ui value per each color_type
};
struct v4l2_ext_cm_cms_ui { // Color Management System
    unsigned char enable;   // 0: don't reference value(advanced_control),  1:
    // reference value(not_use_cm_db==1 && expert_control)
    signed char
        gain_saturation[V4L2_EXT_CM_CMS_MAX];  // ui value per each color_type
    signed char gain_hue[V4L2_EXT_CM_CMS_MAX]; // ui value per each color_type
    signed char
        gain_luminance[V4L2_EXT_CM_CMS_MAX]; // ui value per each color_type
};
struct v4l2_ext_cm_ui_status {
    struct v4l2_ext_cm_dynamic_color_ui dynamic;
    struct v4l2_ext_cm_perferred_color_ui preferred;
    struct v4l2_ext_cm_cms_ui cms;
};
struct v4l2_ext_cm_info {
    unsigned char
        use_internal_cm_db; // 0: use dbInfo, 1: use driver internal db
    struct v4l2_ext_cm_ui_status uiInfo;
    union {
        unsigned char *dbInfo; ///< p_data
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

/* dynamic contrast */
struct v4l2_ext_dynamnic_contrast_ctrl {
    unsigned short uDcVal;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};
#define MAX_DYNAMIC_CONTRAST_LUT_SIZE 16
#define MAX_DYNAMIC_CONTRAST_SATURATION_LUT_SIZE 10
struct v4l2_ext_dynamnic_contrast_lut {
    signed int sLumaLutY[MAX_DYNAMIC_CONTRAST_LUT_SIZE];
    /* if support luma LUT variable X coordination */
    signed int sLumaLutX[MAX_DYNAMIC_CONTRAST_LUT_SIZE];
    /* if support DYNAMIC_CONTRAST_SATURATION_XY */
    unsigned int uSaturationY[MAX_DYNAMIC_CONTRAST_SATURATION_LUT_SIZE];
    unsigned int uSaturationX[MAX_DYNAMIC_CONTRAST_SATURATION_LUT_SIZE];
};

/* black level */
enum v4l2_ext_vpq_black_level_type {
    V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH,
    V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH,
    V4L2_EXT_VPQ_BLACKLEVEL_Y709_COMP_LOW,
    V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW,
    V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH,
};

struct v4l2_ext_vpq_black_level_info {
    unsigned char ui_value;
    unsigned char curr_input;
    unsigned char color_space;
    enum v4l2_ext_vpq_black_level_type black_level_type;
};

enum v4l2_ext_vpq_black_level_type_v2 {
    /* legarcy, same as v1*/
    V4L2_EXT_VPQ_BLK_LVL_Y709_LINEAR_LIMIT_HIGH,    // V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH
    V4L2_EXT_VPQ_BLK_LVL_Y709_BYPASS,               // V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS
    V4L2_EXT_VPQ_BLK_LVL_Y709_COMP_LOW,             // V4L2_EXT_VPQ_BLACKLEVEL_Y709_COMP_LOW
    V4L2_EXT_VPQ_BLK_LVL_AV_RF_EXTENSION,           // V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION

    /* more specified in v2 */
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_LIMIT_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_LIMIT_FULL,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_FULL_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_FULL_FULL,

    V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_LIMIT_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_LIMIT_FULL,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_FULL_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_FULL_FULL,

    V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_LIMIT_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_LIMIT_FULL,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_FULL_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_FULL_FULL,

    V4L2_EXT_VPQ_BLK_LVL_YCBCR_LIMIT_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_YCBCR_LIMIT_FULL,
    V4L2_EXT_VPQ_BLK_LVL_YCBCR_FULL_LIMIT,
    V4L2_EXT_VPQ_BLK_LVL_YCBCR_FULL_FULL,

    V4L2_EXT_VPQ_BLK_LVL_MAX_INDEX
};

struct v4l2_ext_vpq_black_level_info_v2 {
    unsigned char ui_value;
    unsigned char curr_input;
    unsigned char color_space;
    enum v4l2_ext_vpq_black_level_type_v2 black_level_type;
};

enum v4l2_ext_vpq_picture_ctrl_type {
    V4L2_EXT_VPQ_PICTURE_CTRL_CONTRAST   = 0,
    V4L2_EXT_VPQ_PICTURE_CTRL_BRIGHTNESS = 1,
    V4L2_EXT_VPQ_PICTURE_CTRL_SATURATION = 2,
    V4L2_EXT_VPQ_PICTURE_CTRL_HUE        = 3,
    V4L2_EXT_VPQ_PICTURE_CTRL_MAX
};

struct v4l2_ext_vpq_picture_ctrl_data {
    signed int picture_ui_value[V4L2_EXT_VPQ_PICTURE_CTRL_MAX];
    signed int chipData_contrast;
    signed int chipData_brightness;
    signed int chipData_saturation;
    signed int chipData_hue;
};

struct v4l2_ext_vpq_super_resolution_data {
    unsigned char ui_value;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_mpeg_noise_reduction_data {
    unsigned char ui_value;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_decontour_data {
    unsigned char ui_value;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_sharpness_data {
    unsigned short ui_value[4];
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

struct v4l2_ext_vpq_noise_reduction_data {
    unsigned short ui_value[2];
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
};

/* V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL */
#define V4L2_VPQ_EXT_STEREO_FACE_OFF (0)  // off
#define V4L2_VPQ_EXT_STEREO_FACE_ON (1)   // normal on
#define V4L2_VPQ_EXT_STEREO_FACE_DEMO (2) // demo mode

/* extra PQ inner pattern */
#define MAX_EXT_PATTERN_GRADATION_LINE (4) // it may depends on chip limitation
#define MAX_EXT_PATTERN_WINBOX (10)        // it may depends on chip limitation
#define MAX_EXT_PATTERN_GRADATION_H_STRIDE_SIZE                                \
    (254) // it may depends on chip limitation
#define EXT_PATTERN_GRADATION_H_STRIDE_STEP                                    \
    (2) // it may depends on chip limitation
#define MAX_EXT_PATTERN_GRADATION_V_STRIDE_SIZE                                \
    (127) // it may depends on chip limitation
#define EXT_PATTERN_GRADATION_V_STRIDE_STEP                                    \
    (1)                           // it may depends on chip limitation
#define EXT_PATTERN_WIDTH (3840)  // it may depends on chip limitation
#define EXT_PATTERN_HEIGHT (2160) // it may depends on chip limitation

enum V4L2_VPQ_EXT_PATTERN_MODE {
    V4L2_VPQ_EXT_PATTERN_WINBOX,
    V4L2_VPQ_EXT_PATTERN_GRADATION,
    V4L2_VPQ_EXT_PATTERN_MAX
};
enum V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION {
    V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL,
    V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_VERTICAL,
    V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_MAX
};
struct v4l2_vpq_ext_pattern_gradation_line_attr {
    unsigned char lineIdx; // gradation line index
    unsigned short
        start_R; // 1st gradation block's red level as a 10bit resolution
    unsigned short
        start_G; // 1st gradation block's green level as a 10bit resolution
    unsigned short
        start_B; // 1st gradation block's blue level as a 10bit resolution
    unsigned short step_R;     // step size for next gradation block
    unsigned short step_G;     // step size for next gradation block
    unsigned short step_B;     // step size for next gradation block
    unsigned short strideSize; // gradation block's width(horizontal
                               // mode)/height(vertical mode)
};
struct v4l2_vpq_ext_pattern_gradation_info {
    unsigned char numGrad; // number of gradation lines in a screen
    enum V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION eGradMode;
    struct v4l2_vpq_ext_pattern_gradation_line_attr
        stLineAttr[MAX_EXT_PATTERN_GRADATION_LINE];
};
struct v4l2_vpq_ext_pattern_winbox_win_attr {
    unsigned short winIdx; // window layer index. 0:background
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
    unsigned short fill_R; // 10 bit resolution
    unsigned short fill_G; // 10 bit resolution
    unsigned short fill_B; // 10 bit resolution
};
struct v4l2_vpq_ext_pattern_winbox_info {
    unsigned char
        u8NumWin; // number of windows in a screen(including background window)
    struct v4l2_vpq_ext_pattern_winbox_win_attr
        stWinBoxAttr[MAX_EXT_PATTERN_WINBOX];
};
struct
    v4l2_vpq_ext_pattern_info { // old version : this will be removed in near-time
    unsigned char bOnOff;
    enum V4L2_VPQ_EXT_PATTERN_MODE eMode;
    struct v4l2_vpq_ext_pattern_gradation_info *pstGradInfo;
    struct v4l2_vpq_ext_pattern_winbox_info *pstWinboxInfo;
};
#define USE_EXT_PATTERN_INFO_V2
struct v4l2_vpq_ext_pattern_info_v2 {
    unsigned char bOnOff;
    enum V4L2_VPQ_EXT_PATTERN_MODE eMode;
    struct v4l2_vpq_ext_pattern_gradation_info stGradInfo;
    struct v4l2_vpq_ext_pattern_winbox_info stWinboxInfo;
};

struct v4l2_ext_vpq_register_data {
    unsigned int registerAddress;
    unsigned int registerMask;
    unsigned int registerValue;
};

struct v4l2_ext_vpq_register_ctrl {
    unsigned int number;
    union {
        struct v4l2_ext_vpq_register_data *registerData;
        unsigned int compat_registerData;
        unsigned long long sizer;
    };
};

#define DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE 17
struct v4l2_ext_vpq_delta_brightness_conpensation_lut {
    unsigned short input_freq[DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
    unsigned short contrast_gain[DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
    unsigned short brightness_gain [DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
};

enum v4l2_ext_aipq_mode {
    V4L2_EXT_AIPQ_MODE_OFF = 0,
    V4L2_EXT_AIPQ_MODE_ON = 1,
    V4L2_EXT_AIPQ_MODE_DEMO_ON = 2,
};

enum v4l2_ext_aipq_scene_info
{
    V4L2_EXT_AIPQ_SCENE_STANDARD = 0,
    V4L2_EXT_AIPQ_SCENE_BUILDING = 1,
    V4L2_EXT_AIPQ_SCENE_LANDSCAPE = 2,
    V4L2_EXT_AIPQ_SCENE_NIGHT = 3,
    V4L2_EXT_AIPQ_SCENE_INFO_MAX
};

enum v4l2_ext_aipq_genre_info
{
    V4L2_EXT_AIPQ_GENRE_STANDARD = 0,
    V4L2_EXT_AIPQ_GENRE_SPORTS = 1,
    V4L2_EXT_AIPQ_GENRE_ANIMATION = 2,
    V4L2_EXT_AIPQ_GENRE_MOVIE = 3,
    V4L2_EXT_AIPQ_GENRE_INFO_MAX
};

struct v4l2_ext_vpq_degamma_regamma {
	// degamma (EOTF) : 1024 entry (15bit resolution)
	union {
		unsigned short *u16pT_degamma;
		unsigned int compat_degamma;
		unsigned long long sizer_degamma;
	};
	unsigned int degamma_size_num;
	// regamma (OETF) : 2048 entry (12bit resolution)
	union {
		unsigned short *u16pT_regamma;
		unsigned int compat_regamma;
		unsigned long long sizer_regamma;
	};
	unsigned int regamma_size_num;
};

struct v4l2_ext_vpq_frame_delay_mode {
    // delay mode : 0 -> Not use. Defend on LOW_DELAY, MEMC_DELAY
    // delay mode : 1 -> One frame Delay Mode
    // delay mode : other -> TBD
    unsigned int frame_delay_mode;
};
#endif
