/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2020 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

/** @file dvbv5-ext-delivery.h
 *
 *  LGE Delivery Device header file.
 *
 *  @author		Kyoung Won Seo(kyoungwon.seo@lge.com)
 *  @version	1.0
 *  @date		2020.3.27
 *  @see		-
 */

#ifndef _DVBV5_EXT_DELIVERY_H_
#define _DVBV5_EXT_DELIVERY_H_

/**
 * @brief DVBv5 DELIVERY0 device file path.
 *
 * @rst
 * Functional Requirements
 *   DVBv5 DELIVERY0 device file path.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_A "/dev/dvb/adapter0/delivery0"
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 * Seealso
 *   - :ref:`v4l-dvb-apis:dmx_fopen`
 * @endrst
 */
#define DVBV5_EXT_DEV_PATH_DELIVERY_CH_A "/dev/dvb/adapter0/delivery0"

/**
 * @brief DVBv5 DELIVERY1 device file path.
 *
 * @rst
 *
 * Defines
 *   .. code-block:: cpp
 *
 *     #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_B "/dev/dvb/adapter0/delivery1"
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_B, O_RDWR | O_CLOEXEC );
 *
 * Seealso
 *   - :ref:`v4l-dvb-apis:dmx_fopen`
 * @endrst
 */
#define DVBV5_EXT_DEV_PATH_DELIVERY_CH_B "/dev/dvb/adapter0/delivery1"

/**
 * @brief DVBv5 DELIVERY2 device file path.
 *
 * @rst
 *
 * Defines
 *   .. code-block:: cpp
 *
 *     #define DVBV5_EXT_DEV_PATH_DELIVERY_CH_C "/dev/dvb/adapter0/delivery2"
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_C, O_RDWR | O_CLOEXEC );
 *
 * Seealso
 *   - :ref:`v4l-dvb-apis:dmx_fopen`
 * @endrst
 */
#define DVBV5_EXT_DEV_PATH_DELIVERY_CH_C "/dev/dvb/adapter0/delivery2"

/**
 * @brief ioctl extension for executing Setting command.
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_S_CTRL _IOWR('a', 10, struct delivery_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = cid;
 *     param.size = sizeof(pointer);
 *     param.ptr = (void*)pointer;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_G_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 * @endrst
 */
#define DELIVERY_EXT_S_CTRL _IOWR('a', 10, struct delivery_ext_control)

/**
 * @brief ioctl extension for executing Getting command.
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_G_CTRL _IOWR('a', 11, struct delivery_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Get
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = cid;
 *
 *     ioctl(fd, DELIVERY_EXT_G_CTRL, &param);
 *
 *     //check param.size & (param.value64 | param.ptr)
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 * @endrst
 */
#define DELIVERY_EXT_G_CTRL _IOWR('a', 11, struct delivery_ext_control)

/**
 * @brief Set Delivery mode
 *
 * @rst
 * This CID is called to set whether to operate in ATSC 3.0 mode or Japan 4K
 * mode or CI+ 2.0 mode. After opening each channel, this CID is called
 * immediately. Setting Value is transferred through value64 variable. If
 * this CID is not called, the default value is DELIVERY_EXT_MODE_UNSET.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_MODE 1
 *
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_MODE                             |
 *   +-----------+----------------------------------------------------+
 *   | size      | 0                                                  |
 *   +-----------+----------------------------------------------------+
 *   | value64   | | DELIVERY_EXT_MODE_UNSET  :Mode is not set        |
 *   |           | | DELIVERY_EXT_MODE_ATSC30 :ATSC 3.0 mode          |
 *   |           | | DELIVERY_EXT_MODE_JAPAN4K:Japan 4K mode          |
 *   |           | | DELIVERY_EXT_MODE_CI20   :CI+ 2.0 mode           |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_MODE;
 *     param.size = 0;
 *     param.value64 = DELIVERY_EXT_MODE_ATSC30;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :cpp:any:`delivery_ext_mode`
 * @endrst
 */
#define DELIVERY_EXT_CID_MODE 1

/**
 * @brief Set Delivery input source & port type & port number
 *
 * @rst
 * This CID is called to set the input source type, HW connection type, and
 * demod port number. Setting Value is transferred through ptr variable with
 * address of struct delivery_ext_source. If this CID is not called, the
 * default delivery_ext_source is
 * { DELIVERY_EXT_SRC_TYPE_NULL, Don't care ,DELIVERY_EXT_PORT_TYPE_DISABLE }.
 * If MW set delivery_ext_source as {DELIVERY_EXT_SRC_TYPE_NULL, Don't care,
 * DELIVERY_EXT_PORT_TYPE_DISABLE}, delivery driver should be disconnected
 * with demod.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_INPUT_SOURCE 2
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_INPUT_SOURCE                     |
 *   +-----------+----------------------------------------------------+
 *   | size      | size of struct                                     |
 *   +-----------+----------------------------------------------------+
 *   | ptr       | pointer of :cpp:any:`delivery_ext_source`          |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *     struct delivery_ext_source input_source;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     input_source.input_src_type = DELIVERY_EXT_SRC_TYPE_EXT_DEMOD;
 *     input_source.input_port_num = 1;
 *     input_source.input_port_type = DELIVERY_EXT_PORT_TYPE_PARALLEL;
 *
 *     param.id = DELIVERY_EXT_CID_INPUT_SOURCE;
 *     param.size = sizeof(struct delivery_ext_source);
 *     param.ptr = (void*)&input_source;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :cpp:any:`delivery_ext_src_type`
 *   - :cpp:any:`delivery_ext_port_type`
 *   - :cpp:any:`delivery_ext_source`
 * @endrst
 */
#define DELIVERY_EXT_CID_INPUT_SOURCE 2

/**
 * @brief Set Delivery system time
 *
 * @rst
 * This CID is called only in ATSC 3.0 mode, and it is used to calibrate the
 * incoming ATSC 3.0 wall clock based on UTC. Setting Value is transferred
 * through ptr variable with address of struct delivery_ext_system_time_info.
 * If this CID is not called, the default delivery_ext_system_time_info is
 * { 0, 0, 0, 0 }.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_SYSTEM_TIME_INFO 3
 *
 *   +-----------+-----------------------------------------------------+
 *   | delivery_ext_control example                                    |
 *   +===========+=====================================================+
 *   | id        | DELIVERY_EXT_CID_SYSTEM_TIME_INFO                   |
 *   +-----------+-----------------------------------------------------+
 *   | size      | size of struct                                      |
 *   +-----------+-----------------------------------------------------+
 *   | ptr       | pointer of :cpp:any:`delivery_ext_system_time_info` |
 *   +-----------+-----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *     struct delivery_ext_system_time_info sys_time_info;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     sys_time_info.current_utc_offset = 12;
 *     sys_time_info.ptp_prepend = 123;
 *     sys_time_info.leap59 = 1;
 *     sys_time_info.leap61 = 0;
 *
 *     param.id = DELIVERY_EXT_CID_SYSTEM_TIME_INFO;
 *     param.size = sizeof(struct delivery_ext_system_time_info);
 *     param.ptr = (void*)&sys_time_info;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :cpp:any:`delivery_ext_system_time_info`
 * @endrst
 */
#define DELIVERY_EXT_CID_SYSTEM_TIME_INFO 3

/**
 * @brief Set/Get Delivery current time
 *
 * @rst
 * This CID is called for setting/getting ATSC 3.0/Japan 4K current time.
 * When used with DELIVERY_EXT_G_CTRL, current time should be returned, and
 * when used with DELIVERY_EXT_S_CTRL, current time should be set.
 * Setting Value is deliverred through ptr variable with address of
 * struct delivery_ext_time.
 * The unit of nsec variable is slightly different depending on the mode.
 * It is 1 / (10 ^ 9) second for ATSC 3.0 mode and 1 / (2 ^ 32) second for
 * Japan 4K mode. and, when mode is ATSC 3.0, wall_clock value should be
 * informed whether Is wall clock value delivered on current channel.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_CURRENT_TIME 4
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        | DELIVERY_EXT_CID_CURRENT_TIME                      |
 *   +-----------+----------------------------------------------------+
 *   | size      | size of struct                                     |
 *   +-----------+----------------------------------------------------+
 *   | ptr       | pointer of :cpp:any:`delivery_ext_time`            |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set & Get
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *     struct delivery_ext_time time;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     //Get current time
 *     param.id = DELIVERY_EXT_CID_CURRENT_TIME;
 *     param.size = sizeof(struct delivery_ext_time);
 *     param.ptr = (void*)&time;
 *
 *     ioctl(fd, DELIVERY_EXT_G_CTRL, &param);
 *
 *     printf("sec : %d, nsec : %d, wall clock : %d",
 *             time.sec, time.nsec, time.wall_clock);
 *
 *     //Set current time
 *     time.sec = 0;
 *     time.nsec = 0;
 *     time.wall_clock = 0;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :cpp:any:`delivery_ext_time`
 * @endrst
 */
#define DELIVERY_EXT_CID_CURRENT_TIME 4

/**
 * @brief Delivery clock recovery On/Off
 *
 * @rst
 * This CID is used to turn the clock recovery function on or off.
 * Setting Value is transferred through value64 variable. 1 means On.
 * 0 means Off. If this CID is not called, the default value is 0.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF 5
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF             |
 *   +-----------+----------------------------------------------------+
 *   | size      | 0                                                  |
 *   +-----------+----------------------------------------------------+
 *   | value64   | | 0 : Off                                          |
 *   |           | | 1 : On                                           |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF;
 *     param.size = 0;
 *     param.value64 = 1; // On : 1, Off : 0
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 * @endrst
 */
#define DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF 5

/**
 * @brief Set demod version which connected with delivery
 *
 * @rst
 * This CID is used to inform which demod is used because output format
 * can be different if demod is different. and, the demod is fixed normally
 * before bring up stage. So, Delivery driver should check demod output format
 * can be parsing properly in bring up stage.
 * Setting Value is transferred through value64 variable.
 * If this CID is not called, the default value is -1(This mean unset).
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_DEMOD_VERSION 6
 *
 *   +-----------+--------------------------------------------------------------------+
 *   | delivery_ext_control example                                                   |
 *   +-----------+--------------------------------------------------------------------+
 *   | id        |  DELIVERY_EXT_CID_DEMOD_VERSION                                    |
 *   +-----------+--------------------------------------------------------------------+
 *   | size      | 0                                                                  |
 *   +-----------+--------------------------------------------------------------------+
 *   | value64   | | 0x0000 ~ 0x0003 : LG 3307 ATSC3.0 Demod,BBP Based Output Format  |
 *   |           | |                                                                  |
 *   |           | | 0x0100 : Sony ATSC3.0 Demod, ALP format                          |
 *   |           | | 0x0101 : Sony ATSC3.0 Demod,fixed length format                  |
 *   |           | |                                                                  |
 *   |           | | 0x0200 : MTK ATSC3.0 Demod, ATSC 3.0 Frame Structure             |
 *   |           | | 0x0201 : MTK ATSC3.0 Demod, BBP Payload Based Output Format      |
 *   |           | | 0x0202 : MTK ATSC3.0 Demod, BBP Payload Based Output Format      |
 *   |           | |         with TS-188 bytes repack                                 |
 *   |           | | 0x0203 : MTK ATSC3.0 Demod, BBP Based Output Format              |
 *   +-----------+--------------------------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * modify
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_DEMOD_VERSION;
 *     param.size = 0;
 *     param.value64 = 3;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 * @endrst
 */
#define DELIVERY_EXT_CID_DEMOD_VERSION 6

/**
 * @brief Make to start event occurrence
 *
 * @rst
 * This CID is used to make to start event occurrence.
 * If this CID is called when in DELIVERY_EXT_MODE_UNSET state,
 * DELIVERY_EXT_CID_START should be failed. Value is transferred through
 * value64 variable, The default value is DELIVERY_EXT_EVENT_UNSET.
 * When DELIVERY_EXT_EVENT_DATA_DUMP is transferred, the event which inform
 * baseband frame/TLV/TS packet is ready to read should be start to occur.
 * When delivery driver get baseband packet on ATSC 3.0 mode, if 'error mode'
 * bit is set & 'error indication' bit is set, the baseband packet should be
 * dropped.
 * When DELIVERY_EXT_EVENT_WALL_CLOCK is transferred, the event which inform
 * wall clock comes in should be start to occur.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_START 7
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_START                            |
 *   +-----------+----------------------------------------------------+
 *   | size      | 0                                                  |
 *   +-----------+----------------------------------------------------+
 *   | value64   | | DELIVERY_EXT_EVENT_DATA_DUMP                     |
 *   |           | | DELIVERY_EXT_EVENT_WALL_CLOCK                    |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_MODE;
 *     param.size = 0;
 *     param.value64 = DELIVERY_EXT_MODE_ATSC30;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 *     param.id = DELIVERY_EXT_CID_START;
 *     param.size = 0;
 *     param.value64 = DELIVERY_EXT_EVENT_DATA_DUMP;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :cpp:any:`delivery_ext_event`
 * @endrst
 */
#define DELIVERY_EXT_CID_START 7

/**
 * @brief Make to stop event occurrence
 *
 * @rst
 * This CID is used to make to stop event occurrence.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_STOP 8
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_STOP                             |
 *   +-----------+----------------------------------------------------+
 *   | size      | 0                                                  |
 *   +-----------+----------------------------------------------------+
 *   | value64   | | DELIVERY_EXT_EVENT_DATA_DUMP                     |
 *   |           | | DELIVERY_EXT_EVENT_WALL_CLOCK                    |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_MODE;
 *     param.size = 0;
 *     param.value64 = DELIVERY_EXT_MODE_ATSC30;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 *     param.id = DELIVERY_EXT_CID_START;
 *     param.size = 0;
 *     param.value64 = DELIVERY_EXT_EVENT_DATA_DUMP;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 *     param.id = DELIVERY_EXT_CID_STOP;
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 * @endrst
 */
#define DELIVERY_EXT_CID_STOP 8

/**
 * @brief Modify input wall clock by adding specific pattern
 *
 * @rst
 * This CID is used to set abnormal wall clock pattern for verifying Delivery
 * driver ATSC3.0 wall clock recovery.
 * The abnormal wall clock pattern is set in such a way that the ptr variable
 * is passed the address of an array of N x size of int. and, The unit of the
 * int value is msec. Delivery wall clock recovery should be performed by using
 * wall clock which is added on N 'wall clock' values that come in after
 * 'clock recovery on' for N int values delivered when
 * 'DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK' CID is set.
 * 'DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK' CID will be called before
 * 'DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF' On. If
 * 'DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF' is called with Off setting after
 * 'DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK' setting, abnormal wall clock
 * pattern setting should be expired.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK 9
 *
 *   +-----------+----------------------------------------------------+
 *   | delivery_ext_control example                                   |
 *   +===========+====================================================+
 *   | id        |  DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK           |
 *   +-----------+----------------------------------------------------+
 *   | size      | n * sizeof(int)                                    |
 *   +-----------+----------------------------------------------------+
 *   | ptr       | pointer of int array                               |
 *   +-----------+----------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Set
 *
 * Example
 *   .. code-block:: cpp
 *
 *     #define TEST_NUM 40
 *
 *     int fd;
 *     struct delivery_ext_control param;
 *     int test_pattern_array[TEST_NUM];
 *
 *     fd = open(DVBV5_EXT_DEV_PATH_DELIVERY_CH_A, O_RDWR | O_CLOEXEC );
 *
 *     param.id = DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK;
 *     param.size = TEST_NUM * sizeof(int);
 *     param.ptr = (void*)&test_pattern_array[0];
 *
 *     for(i=0 ; i<TEST_NUM ; i++) {
 *       test_pattern_array[i] = test_pattern_case1[i];
 *     }
 *
 *     ioctl(fd, DELIVERY_EXT_S_CTRL, &param);
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :cpp:any:`delivery_ext_control`
 *   - :c:macro:`DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF`
 * @endrst
 */
#define DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK 9

/**
 * @brief enum for DELIVERY_EXT_CID_MODE
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     enum delivery_ext_mode {
 *         DELIVERY_EXT_MODE_UNSET,   //Mode is not set.
 *         DELIVERY_EXT_MODE_ATSC30,  //ATSC3.0 mode
 *         DELIVERY_EXT_MODE_JAPAN4K, //Japan 4K mode
 *         DELIVERY_EXT_MODE_CI20,    //CI+ 2.0 mode
 *         DELIVERY_EXT_MODE_MAX
 *     };
 *
 * Seealso
 *   :c:macro:`DELIVERY_EXT_CID_MODE`
 * @endrst
 */
enum delivery_ext_mode {
    DELIVERY_EXT_MODE_UNSET,
    DELIVERY_EXT_MODE_ATSC30,
    DELIVERY_EXT_MODE_JAPAN4K,
    DELIVERY_EXT_MODE_CI20,
    DELIVERY_EXT_MODE_MAX
};

/**
 * @brief enum for DELIVERY_EXT_CID_INPUT_SOURCE
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     enum delivery_ext_src_type {
 *         DELIVERY_EXT_SRC_TYPE_NULL,      //Source type is not set
 *         DELIVERY_EXT_SRC_TYPE_IN_DEMOD,  //Internal Demod
 *         DELIVERY_EXT_SRC_TYPE_EXT_DEMOD, //Extener Demod
 *         DELIVERY_EXT_SRC_TYPE_MEM,       //Memory
 *         DELIVERY_EXT_SRC_TYPE_MAX
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_INPUT_SOURCE`
 * @endrst
 */
enum delivery_ext_src_type {
    DELIVERY_EXT_SRC_TYPE_NULL,
    DELIVERY_EXT_SRC_TYPE_IN_DEMOD,
    DELIVERY_EXT_SRC_TYPE_EXT_DEMOD,
    DELIVERY_EXT_SRC_TYPE_MEM,
    DELIVERY_EXT_SRC_TYPE_MAX
};

/**
 * @brief enum for DELIVERY_EXT_CID_INPUT_SOURCE
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     enum delivery_ext_port_type {
 *         // Disable current Delivery channel
 *         DELIVERY_EXT_PORT_TYPE_DISABLE,
 *         // Enable current Delivery channel as serial type
 *         DELIVERY_EXT_PORT_TYPE_SERIAL,
 *         // Enable current Delivery channel as parallel type
 *         DELIVERY_EXT_PORT_TYPE_PARALLEL,
 *         DELIVERY_EXT_PORT_TYPE_MAX
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_INPUT_SOURCE`
 * @endrst
 */
enum delivery_ext_port_type {
    DELIVERY_EXT_PORT_TYPE_DISABLE,
    DELIVERY_EXT_PORT_TYPE_SERIAL,
    DELIVERY_EXT_PORT_TYPE_PARALLEL,
    DELIVERY_EXT_PORT_TYPE_MAX
};

/**
 * @brief enum for event registration
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     enum delivery_ext_event {
 *         DELIVERY_EXT_EVENT_UNSET,
 *         //The event which inform baseband frame/TLV/TS packet is
 *         //ready to read
 *         DELIVERY_EXT_EVENT_DATA_DUMP,
 *         //The event which inform wall clock comes in
 *         DELIVERY_EXT_EVENT_WALL_CLOCK,
 *         DELIVERY_EXT_EVENT_MAX
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_START`
 * @endrst
 */
enum delivery_ext_event {
    DELIVERY_EXT_EVENT_UNSET,
    DELIVERY_EXT_EVENT_DATA_DUMP,
    DELIVERY_EXT_EVENT_WALL_CLOCK,
    DELIVERY_EXT_EVENT_MAX
};

/**
 * @brief struct for DELIVERY_EXT_S_CTL or DELIVERY_EXT_G_CTL
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     struct delivery_ext_control {
 *         // Delivery control id
 *         __u32 id;
 *         // Parameter size, if size is 0, value64 is used
 *         //if size is not 0, ptr is used
 *         __u32 size;
 *
 *         //union struct for memory alignment
 *         union {
 *             // if size is 0, value64 is used
 *             __s64 value64;
 *             // if size is not 0, ptr is used
 *             void __user *ptr;
 *         };
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_S_CTRL`
 *   - :c:macro:`DELIVERY_EXT_G_CTRL`
 * @endrst
 */
struct delivery_ext_control {
    __u32 id;
    __u32 size;

    union {
        __s64 value64;
        void *ptr;
    };
};

/**
 * @brief structure for DELIVERY_EXT_CID_INPUT_SOURCE
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     struct delivery_ext_source {
 *         // Input source type
 *         enum delivery_ext_src_type input_src_type;
 *         // Port number of input
 *         __u32 input_port_num;
 *         // HW connection type of input port
 *         enum delivery_ext_port_type input_port_type;
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_INPUT_SOURCE`
 * @endrst
 */
struct delivery_ext_source {
    enum delivery_ext_src_type input_src_type;
    __u32 input_port_num;
    enum delivery_ext_port_type input_port_type;
};

/**
 * @brief structure for DELIVERY_EXT_CID_SYSTEM_TIME_INFO
 *
 * @rst
 * Definition
 *      Data which read from TTAK.KO-07.0127/R2 ATSC3.0 spec SystemTime Element
 *
 *   .. code-block:: cpp
 *
 *     struct delivery_ext_system_time_info {
 *         __u32 current_utc_offset; //SystemTime currentUtcOffset
 *         __u32 ptp_prepend;        //SystemTime ptpPrepend
 *         __u32 leap59;             //SystemTime leap59
 *         __u32 leap61;             //SystemTime leap61
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_SYSTEM_TIME_INFO`
 * @endrst
 */
struct delivery_ext_system_time_info {
    __u32 current_utc_offset;
    __u32 ptp_prepend;
    __u32 leap59;
    __u32 leap61;
};

/**
 * @brief structure for DELIVERY_EXT_CID_CURRENT_TIME
 *
 * @rst
 * Definition
 *   .. code-block:: cpp
 *
 *     struct delivery_ext_time {
 *         // Time value
 *         // (unit : second)
 *         __u32 sec;
 *         // Sub Time value
 *         // (unit : 1 / (10^9) second(ATSC 3.0 mode)
 *         //  or 1 / (2^32) second(Japen 4K mode))
 *         __u32 nsec;
 *         // Whether Is wall clock value delivered on current channel
 *         // ( 1 : Yes, 0 : No )
 *         __u32 wall_clock;
 *     };
 *
 * Seealso
 *   - :c:macro:`DELIVERY_EXT_CID_CURRENT_TIME`
 * @endrst
 */
struct delivery_ext_time {
    __u32 sec;
    __u32 nsec;
    __u32 wall_clock;
};

#endif /* _DVBV5_EXT_DELIVERY_H_ */
