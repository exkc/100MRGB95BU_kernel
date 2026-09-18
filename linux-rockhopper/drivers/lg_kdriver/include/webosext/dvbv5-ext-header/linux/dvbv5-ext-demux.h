/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018-2019 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

/** @file dvbv5-ext-dmx.h
 *
 *  LGE System Decoder Device driver header file.
 *
 *	@author		Seong Lee(seong.lee@lge.com)
 *  @version	0.1
 *  @date		2018.5.15
 *  @see		-
 */

#ifndef _DVBV5_EXT_DEMUX_H_
#define _DVBV5_EXT_DEMUX_H_

#include <linux/dvb/dmx.h>

/* DMX control id define for DMX_EXT_S_CTL or DMX_EXT_G_CTL */

/**
 * @brief  Set the regional platform type
 *
 * @rst
 * Functional Requirements
 *   The platform type is set because different regions can be required
 *   different behavior. And, the platform type is set for demux0 only.
 *   So, other channel need to refer the platform type which is set on
 *   demux0.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_PLATFORM        0
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |    :c:macro:`DMX_EXT_CID_PLATFORM`              |
 *   +------------+-------------------------------------------------+
 *   | size       |    0                                            |
 *   +------------+-------------------------------------------------+
 *   | value64    |    Enum of :cpp:any:`dmx_platform`              |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = -1;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     struct dmx_ext_control argp;
 *
 *     argp.id = DMX_EXT_CID_PLATFORM
 *     argp.size = 0
 *     argp.value64 = DMX_PLATFORM_ATSC
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp)
 *     close(fd)
 *
 * Seealso
 *   - :cpp:any:`dmx_sct_filter_params`
 * @endrst
 */
#define DMX_EXT_CID_PLATFORM 0

/**
 * @brief Enum for Regional platform
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_platform {
 *         DMX_PLATFORM_ATSC = 0,
 *         DMX_PLATFORM_DVB,
 *         DMX_PLATFORM_ISDB, // JP
 *         DMX_PLATFORM_COMMERCIAL
 *     };
 *
 * Seealso
 *   :c:macro:`DMX_EXT_CID_PLATFORM`
 * @endrst
 */
enum dmx_platform {
    DMX_PLATFORM_ATSC = 0,
    DMX_PLATFORM_DVB,
    DMX_PLATFORM_ISDB,
    DMX_PLATFORM_COMMERCIAL
};

/**
 * @brief  Set a country type
 *
 * Set country values to ensure different behaviors in different countries.
 * And, the country type is set for demux0 only. So, other channel need to
 * refer the country type which is set on demux0.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_PLATFORM        0
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
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
 * Control Type
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_COUNTRY               |
 *   +------------+-------------------------------------------------+
 *   | size       |               0                                 |
 *   +------------+-------------------------------------------------+
 *   | value64    |      Enum of :cpp:any:`dmx_country`             |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = -1;
 *
 *     struct dmx_ext_control argp;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_COUNTRY
 *     argp.size = 0
 *     argp.value64 = DMX_COUNTRY_KR
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp)
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_sct_filter_params`
 * @endrst
 */
#define DMX_EXT_CID_COUNTRY 1

/**
 * @brief Enum for Regional platform
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_country {
 *         DMX_COUNTRY_KR = 0,   // Korea
 *         DMX_COUNTRY_US,       // USA
 *         DMX_COUNTRY_EU,       // EUROPE
 *         DMX_COUNTRY_CN,       // CHINA
 *         DMX_COUNTRY_MA,       // Asia (Center asia)
 *         DMX_COUNTRY_JP,       // Japan
 *         DMX_COUNTRY_COLUMBIA, // Columbia
 *     };
 *
 * Seealso
 *   :c:macro:`DMX_EXT_CID_COUNTRY`
 * @endrst
 */
enum dmx_country {
    DMX_COUNTRY_KR = 0,   /*Korea*/
    DMX_COUNTRY_US,       /*USA*/
    DMX_COUNTRY_EU,       /*EUROPE*/
    DMX_COUNTRY_CN,       /*CHINA*/
    DMX_COUNTRY_MA,       /*Asia (Center asia)*/
    DMX_COUNTRY_JP,       /*Japan*/
    DMX_COUNTRY_COLUMBIA, /*Columbia*/
};

/** This will be deprecated */
#define DMX_EXT_CID_MODEL_NO 2

/** This will be deprecated */
#define DMX_EXT_CID_CHIP_ID 3

/** This will be deprecated */
#define DMX_EXT_CID_DRV_VER 4

/** This will be deprecated */
#define DMX_EXT_CID_PORT_NUM 5

/** This will be deprecated */
#define DMX_EXT_CID_AFIFO 6

/**
 * @brief  Set a input type of the Demux
 *
 * This Command ID set the TS path through which Signal flows from Tuner to
 * Demux or  CAM to Demux. After setting pes or section filter, the value of the
 * struct dmx_pes_filter_param enum dmx_input is ignored, and the
 * DMX_EXT_CID_INPUTSOURCE setting value is used as the dmx_input value.
 *
 * Describes a special case.
 * If input_src_type is DMX_EXT_SRC_TYPE_USB_CI, input_port_num is 0,
 * input_port_type is DMX_EXT_PORT_TYPE_SERIAL.This setting value means
 * that TS is transmitted via PVR via USB CAM.
 *
 * If input_src_type is DMX_EXT_SRC_TYPE_MEM, it means TS will came through
 * PVR device. input_port_num is pvr port number which is same as target demux.
 * input_port_type should be DMX_EXT_PORT_TYPE_SERIAL.
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_INPUTSOURCE     7
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_INPUTSOURCE           |
 *   +------------+-------------------------------------------------+
 *   | size       |      size of struct                             |
 *   +------------+-------------------------------------------------+
 *   | ptr        |      pointer of :cpp:any:`dmx_ext_source`       |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *     struct dmx_ext_source src;
 *     int fd = -1;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *
 *     src.input_src_type= DMX_EXT_SRC_TYPE_IN_DEMOD; // Internal demod
 *     src.input_port_num = 0; // demod port is 0.
 *     src.input_port_type= DMX_EXT_PORT_TYPE_PARALLEL;
 *
 *     argp.id = DMX_EXT_CID_INPUTSOURCE;
 *     argp.size = sizeof(src);
 *     argp.ptr = &src;
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_source`
 *   - :cpp:any:`dmx_ext_control`
 *
 * @endrst
 */
#define DMX_EXT_CID_INPUTSOURCE 7

/**
 * @brief  Control PCR Recovery function
 *
 * Starts the PCR recovery function for this channel. If there is an extra
 * routine for PCR, like interrupt enable, this function manages it. Enable /
 * Disable the PCR recovery function, Demux function. The PCR recovery operation
 * must be enabled automatically when the PCR Pid is set, and the PCR Recovery
 * function can be enabled / disabled by this function. With value64, the value
 * of 0 becomes PCR Recovery Off, and STC need to be increased  linearly
 * regardless of PCR. When PCR recovery is On, STC value should be updated by
 * PCR value. However, fd used for PCR control uses fd of PCR filter.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_PCR_ONOFF 8
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_PCR_ONOFF             |
 *   +------------+-------------------------------------------------+
 *   | size       |               0                                 |
 *   +------------+-------------------------------------------------+
 *   | value64    |          0: Pcr recovery Off, 1: On             |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = -1;
 *     struct dmx_ext_control argp;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_PCR_ONOFF;
 *     argp.size = 0;
 *     argp.value64 = 0; // 0 = PCR Recovery OFF, 1 = PCR Recovery ON
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_PCR_ONOFF 8

/**
 * @brief  Set the filter to check scramble bit for ATSC CADTV
 *
 * Starts the scramble check function for this channel. If there is an extra
 * routine for scramble, like interrupt enable, this function manages it. To
 * request new pid, LG will get a new fd for it.
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_REQUEST_SCRMB   9
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_REQUEST_SCRMB         |
 *   +------------+-------------------------------------------------+
 *   | size       |               0                                 |
 *   +------------+-------------------------------------------------+
 *   | value64    |          value of PID                           |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *
 *     int fd = -1;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *
 *     argp.id = DMX_EXT_CID_REQUEST_SCRMB;
 *     argp.size = 0
 *     argp.value64 = 0x11
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_REQUEST_SCRMB 9

/**
 * @brief  Cancel filter for checking scramble bit
 *
 * Stops scramble check. This function stops DMX_EXT_CID_REQUEST_SCRMB.Remove
 * the PID filter and scramble bit check routine generated in
 * DMX_EXT_CID_REQUEST_SCRMB.
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_CANCEL_SCRMB 10
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   This function is only called on ATSC models.
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_CANCEL_SCRMB          |
 *   +------------+-------------------------------------------------+
 *   | size       |               0                                 |
 *   +------------+-------------------------------------------------+
 *   | value64    |               0                                 |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *
 *     argp.id = DMX_EXT_CID_CANCEL_SCRMB; //cancel filter
 *     argp.size = 0
 *     argp.value64 = 0x11
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_CANCEL_SCRMB 10

/**
 * @brief  Check scrmable bit
 *
 * @rst
 * Checks scramble status. Call :c:macro:`DMX_EXT_CID_REQUEST_SCRMB` first then use this
 * function, to check the scrambled status of Scramble bit for specific PID.
 * Retrieves the Scramble status bit value updated by the PID filter generated
 * in :c:macro:`DMX_EXT_CID_REQUEST_SCRMB`.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_CHECK_SCRMB 11
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *  Wait until scramble status bit is updated, Maximum Elapsed time must be less than 1 second.
 * if scramble status bit is updated, return as soon as possible.
 *
 * Constraints
 *   This function is only called on ATSC models.
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         | :c:macro:`DMX_EXT_CID_CHECK_SCRMB`              |
 *   +------------+-------------------------------------------------+
 *   | size       | 0                                               |
 *   +------------+-------------------------------------------------+
 *   | value64    | ??                                              |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_control argp;
 *
 *     argp.id = DMX_EXT_CID_CHECK_SCRMB;
 *     argp.size = 0;
 *     argp.value64 = -1;
 *
 *     ret = ioctl(fd,DMX_EXT_G_CTL,&argp );
 *
 *     // check ret for valid excution of ioctl, then compare the argp.value64.
 *
 *     argp.value64 = 1  // scrambled
 *     argp.value64 = 0  // Not scrambled
 *     argp.value64 = -1 // Error, Driver couldn't detect the scramble value.
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_CHECK_SCRMB 11

/**
 * @brief  Set descrambler type.
 *
 * Sets descrambler type of this demux channel. Descrambler supports the
 * following five modes. (None/PVR/BCAS/CI+AES/CI+DES).Default value is
 * DMX_EXT_DSCRMB_TYPE_NONE.To use this ioctl, LG uses the fd obtained from open().
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_DSCRMB_TYPE 12
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
 *   Application can get data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_DSCRMB_TYPE           |
 *   +------------+-------------------------------------------------+
 *   | size       |               0                                 |
 *   +------------+-------------------------------------------------+
 *   | value64    |               Enum of dmx_ext_dscrmb_type       |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = - 1;
 *     struct dmx_ext_control argp;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_DSCRMB_TYPE;
 *     argp.size = 0;
 *     argp.value64 = DMX_EXT_DSCRMB_TYPE_BCAS; // Descrambler for BCAS.
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_DSCRMB_TYPE 12

/**
 * @brief  Enable or Disable PID Descramble for Japan ACAS
 *
 * Used when DMX_EXT_CID_DSCRMB_TYPE is set to DMX_EXT_DSCRMB_TYPE_BCAS.Select
 * the pid to be descrambled. LG can enable descramble action only for specific
 * pid filters. If LG send dmx_ext_dscrmb_pid variable with bEnable = 0, It
 * means kernel should disable descramble the specific pid filter.To use this
 * ioctl, LG uses the fd used in DMX_SET_PES_FILTER or DMX_SET_FILTER. If the
 * ioctl is called with fd that does not have a pid filter, it returns an
 * error.bEnable = 1 means enabling the descramble,  bEnable = 0 means disable
 * it.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_DSCRMB_PID 13
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
 *   Application can get data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_DSCRMB_PID            |
 *   +------------+-------------------------------------------------+
 *   | size       |             size of dmx_ext_dscrmb_pid          |
 *   +------------+-------------------------------------------------+
 *   | value64    |   pointer of :cpp:any:`dmx_ext_dscrmb_pid`      |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = -1;
 *
 *     struct dmx_ext_control argp;
 *     struct dmx_ext_dscrmb_pid param;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     // --> LG set the 0x1 pid with fd.
 *
 *     param.pid = 0x1;
 *     param.bEnable = 1;
 *     argp.id = DMX_EXT_CID_DSCRMB_PID;
 *     argp.size =sizeof(param);
 *     argp.ptr = &param;
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL, &argp);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_DSCRMB_PID 13

/**
 * @brief Sets the descramble key of the input type
 *
 * @rst
 * Sets the descramble key of the input type. Enter the key type for the current
 * descramble mode. To use this ioctl, LG uses the fd used in
 * DMX_EXT_CID_INPUTSOURCE or DMX_EXT_CID_PCR_ONOFF.
 *
 * The descramble key set via fd is applied to the entire channel.In special
 * case, For BCAS, only the PIDs that are enabled through DMX_EXT_CID_DSCRMB_PID
 * should be descrambled.But CBC and Syskey  is applied to the entire channel.
 * If the key configuration needs to be initialized or clear, bytes array filled
 * with zeros is passed through __u8 * key.
 *
 * Below Picture means Descrambler should check pid filter's status whether
 * bEnable is 1 or 0.
 *
 * .. image:: /dvbv5/resources/demux-descramble_key.png
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_DSCRMB_KEY 14
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_DSCRMB_KEY            |
 *   +------------+-------------------------------------------------+
 *   | size       |             bytes of buffer                     |
 *   +------------+-------------------------------------------------+
 *   | ptr        |   pointer of buffer                             |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     int fd = -1;
 *     __u8 key_buffer[size of key data];
 *
 *     struct dmx_ext_control argp;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     struct dmx_ext_dscrmb_key tmp_key;
 *
 *     tmp_key.key_type = DMX_EXT_DSCRMB_KEY_TYPE_EVEN ;
 *     tmp_key.key_size = sizeof(key_buffer);
 *     tmp_key.key = key_buffer;
 *     tmp_key.pid = common fd; // pid for DMX_EXT_CID_INPUTSOURCE
 *
 *     argp.id = DMX_EXT_CID_DSCRMB_KEY;
 *     argp.size = sizeof(key_buffer);
 *     argp.ptr = &tmp_key;
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *     close(fd);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_DSCRMB_KEY 14

/**
 * @brief ADD PID for HFR subset stream
 *
 * @rst
 * If the PID filter generated in designated destination by DMX_SET_PES_FILTER,
 * add PID to existing PID filter. This PID filter send packets of all added
 * PIDs to designated destination. If there is no PID filter for designated
 * destination, this ioctl works same as DMX_SET_PES_FILTER. This command id is
 * related with HFR,it can be changed later. No Implementation Required
 *
 * Currently this command is not used.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_ADD_PID 15
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |               DMX_EXT_CID_ADD_PID               |
 *   +------------+-------------------------------------------------+
 *   | size       |             0                                   |
 *   +------------+-------------------------------------------------+
 *   | value64    |   value of pid                                  |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     TBD
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_ADD_PID 15

/**
 * @brief Notify Demux that the ECP information has changed
 *
 * @rst
 * This command is used to tell Demux to update ECP related information. The
 * ioctl is only called, and there is no information passed by REE. Effective
 * information is managed by TEE. Therefore, communication with TEE is required.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_ECP_INFO_NOTI 16
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |             DMX_EXT_CID_ECP_INFO_NOTI           |
 *   +------------+-------------------------------------------------+
 *   | size       |             0                                   |
 *   +------------+-------------------------------------------------+
 *   | value64    |             0                                   |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *     int fd = -1;
 *
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_ECP_INFO_NOTI ;
 *     argp.size = 0;
 *     argp.value64 = 0;
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_ECP_INFO_NOTI 16
/**
 * @brief Notify Demux that number of sdt filter port
 *
 * @rst
 * This command is used to tell Demux to nofity sdt filter port.
 * Initial value should be -1, This means "do not reference value".
 *
 * For non-CI+2.0 USB, -1 will be set. And Do not use SDT port info.
 *
 * This is valid value only for CI+2.0 USB case.
 * For CI+2.0 USB case, This command is used a  SDT port
 * the port that handles SDT to the SDEC port that receives RF Signal
 * directly. The final set value is the correct value.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_SDT_PORT_INFO 17
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
 *   Application can set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |             DMX_EXT_CID_SDT_PORT_INFO           |
 *   +------------+-------------------------------------------------+
 *   | size       |             0                                   |
 *   +------------+-------------------------------------------------+
 *   | value64    |             0                                   |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *     int fd = -1;
 *
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_SDT_PORT_INFO ;
 *     argp.size = 0;
 *     argp.value64 = 2; // if sdt port is /dev/dvb/adapter0/demux2 *
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_SDT_PORT_INFO 17

/**
 * @brief Notify the demux the number of tuners
 *
 * @rst
 * This command is used for getting demux to know the number of tuners which the TV has.
 * This command will be called for below cases
 *
 *  case-1 : The TV is turned on with QSM-off
 *
 *  case-2 : The TV is turned on with AC-on
 *
 *  case-3 : The webOS service which includes the demux is respawned
 *
 *  case-4 : The webOS service which includes the demux becomes alive
 *
 * The number of tuners is set for demux0 only.
 * So, other channels need to refer to the number of tuners which is set on
 * demux0.
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_CID_NUMBER_OF_TUNERS 18
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
 *   When it successes, 0 is returned. When it fails, -1 is returned.
 *
 * Control Type
 *   Application will set data using dmx_ext_control and this control id.
 *
 *   +------------+-------------------------------------------------+
 *   | dmx_ext_control example                                      |
 *   +============+=================================================+
 *   | id         |             DMX_EXT_CID_NUMBER_OF_TUNERS        |
 *   +------------+-------------------------------------------------+
 *   | size       |             0                                   |
 *   +------------+-------------------------------------------------+
 *   | value64    |             0                                   |
 *   +------------+-------------------------------------------------+
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *     int fd = -1;
 *
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_NUMBER_OF_TUNERS ;
 *     argp.size = 0;
 *     argp.value64 = 1; // if the number of tuners is 1.
 *     //argp.value64 = 2; // if the number of tuners is 2.
 *     //argp.value64 = 3; // if the number of tuners is 3.
 *     //argp.value64 = 0; // if the TV is tunerless model.
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_NUMBER_OF_TUNERS 18

/**
 * @brief Set log level in demux driver and kernel
 *
 * Setting and getting of log print level in Demux kernel and drivers.
 * Each log levels have its own log printing rules.
 *
 * Returns the current log levels
 *
 * Demux control id define for DMX_EXT_G_CTL and DMX_EXT_S_CTL
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *     struct dmx_ext_control argp;
 *     int fd = -1;
 *
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *     argp.id = DMX_EXT_CID_LOG_LEVEL ;
 *     argp.size = 0;
 *     argp.value64 = DMX_EXT_LOG_LEVEL_INFO; // Set log level 'INFO'
 *
 *     ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | dmx_ext_control example                                      |
 *     +============+=================================================+
 *     | id         |       DMX_EXT_CID_LOG_LEVEL                     |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       Enum of dmx_ext_log_level                 |
 *     +------------+-------------------------------------------------+
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * Seealso
 *   - :cpp:any:`dmx_ext_control`
 */
#define DMX_EXT_CID_LOG_LEVEL 19

/**
 * @brief Notify Demux that change the AVSYNC mode
 *
 * @rst
 * This command is used to tell Demux to change AVSYNC Mode.
 * Initial value should be 0, which means "PCR Master Mode".
 *
 * Commands & Parameters
 * .. code-block:: cpp
 *
 * #define DMX_EXT_CID_AVSYNC_MODE 20
 *
 * Responses to abnormal situations, including
 * None
 *
 * Performance Requirements
 * Function elapsed time should be less than 100ms.
 *
 * Constraints
 * None
 *
 * Return Value
 * On success 0 is returned. On error -1 and the errno variable is set
 * appropriately. The generic error codes are described at the
 * :ref:`gen_errors` chapter.
 *
 * Control Type
 * Application can set data using dmx_ext_control and this control id.
 *
 * +------------+-------------------------------------------------+
 * | dmx_ext_control example |
 * +============+========================+
 * | id | DMX_EXT_CID_AVSYNC_MODE |
 * +------------+-------------------------------------------------+
 * | size | 0 |
 * +------------+-------------------------------------------------+
 * | value64 | 0 |
 * +------------+-------------------------------------------------+
 *
 * Example
 * .. code-block:: cpp
 *
 * int ret = -1;
 * struct dmx_ext_control argp;
 * int fd = -1;
 *
 * fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 * argp.id = DMX_EXT_CID_AVSYNC_MODE ;
 * argp.size = 0;
 * argp.value64 = 1; // Audio Master Mode.
 * //argp.value64 = 0; // Default: PCR Master Mode.
 *
 * ret = ioctl(fd, DMX_EXT_S_CTL,&argp);
 *
 * Seealso
 * - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_CID_AVSYNC_MODE 20

#ifndef __user
#define __user
#endif

/**
 * @brief struct for DMX_EXT_S_CTL or  DMX_EXT_G_CTL
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_control {
 *         __u32 id;   // DMX control id
 *         __u32 size; // input parameter size, if 0 value64 is the input else ptr is the input.
 *         // union struct for memory alignment
 *         union {
 *             __s64 value64;    // if size is 0, this is the real input
 *             void __user *ptr; // if size is not 0, this is the real input
 *         };
 *     };
 *
 * Seealso
 *   :c:macro:`DMX_EXT_S_CTL`
 *   :c:macro:`DMX_EXT_G_CTL`
 * @endrst
 */
struct dmx_ext_control {
    /** DMX control id */
    __u32 id;
    /** input parameter size, if 0 value64 is the input else ptr is the input. */
    __u32 size;
    /** union struct for memory alignment*/
    union {
        /** if size is 0, this is the real input */
        __s64 value64;
        /** if size is not 0, this is the real input */
        void __user *ptr;
    };
};

/* enum for descramble type */

/**
 * @brief enum for descramble type
 *
 * This is the setting for the descriptor type.
 * BCAS, PVR, CI, and EMB that exist in the middle of the Enum are use cases
 * where the corresponding values are set. EMB stands for Embedded CAS.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_ext_dscrmb_type {
 *         DMX_EXT_DSCRMB_TYPE_NONE = 0,
 *         DMX_EXT_DSCRMB_TYPE_BCAS,
 *         DMX_EXT_DSCRMB_TYPE_CI_AES,
 *         DMX_EXT_DSCRMB_TYPE_CI_DES,
 *         DMX_EXT_DSCRMB_TYPE_PVR,
 *         DMX_EXT_DSCRMB_TYPE_CI_AES_ECP,
 *         DMX_EXT_DSCRMB_TYPE_CI_DES_ECP,
 *         DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS,
 *         DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2,
 *         DMX_EXT_DSCRMB_TYPE_EMB_CSA_V3
 *     };
 *
 * @endrst
 */
enum dmx_ext_dscrmb_type {
    DMX_EXT_DSCRMB_TYPE_NONE = 0,
    DMX_EXT_DSCRMB_TYPE_BCAS,
    DMX_EXT_DSCRMB_TYPE_CI_AES,
    DMX_EXT_DSCRMB_TYPE_CI_DES,
    DMX_EXT_DSCRMB_TYPE_PVR,
    DMX_EXT_DSCRMB_TYPE_CI_AES_ECP,
    DMX_EXT_DSCRMB_TYPE_CI_DES_ECP,
    DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS,
    DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2,
    DMX_EXT_DSCRMB_TYPE_EMB_CSA_V3
};

/* struct for descramble pid */

/**
 * @brief struct for descramble pid
 *
 * Descrambler Key is applied to the entire channel and is a structure used to
 * apply descramble of specific PID. Default value is 0 which means Disable.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_dscrmb_pid {
 *         __u32 pid;
 *         __u32 bEnable;
 *     };
 *
 * @endrst
 */
struct dmx_ext_dscrmb_pid {
    __u32 pid;
    __u32 bEnable;
};

/* This will be deprecated */
struct dmx_ext_dscrmb_filter {
    enum dmx_ts_pes pes_type;
    __u16 pid;
};

/* This will be deprecated */
struct dmx_ext_dscramb_read_pids {
    __u32 number_of_pids;
    __u16 array_of_pids[32];
};

/* enum for descramble key type */

/**
 * @brief enum for descramble key type
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_ext_dscrmb_key_type {
 *         DMX_EXT_DSCRMB_KEY_TYPE_EVEN = 0,
 *         DMX_EXT_DSCRMB_KEY_TYPE_ODD,
 *         DMX_EXT_DSCRMB_KEY_TYPE_EVEN_ODD, // not used, Same as EVEN+ODD
 *         DMX_EXT_DSCRMB_KEY_TYPE_EVENIV,
 *         DMX_EXT_DSCRMB_KEY_TYPE_ODDIV,
 *         DMX_EXT_DSCRMB_KEY_TYPE_CBC,
 *         DMX_EXT_DSCRMB_KEY_TYPE_SYSKEY,
 *         DMX_EXT_DSCRMB_KEY_TYPE_PVRKEY
 *     };
 *
 * @endrst
 */
enum dmx_ext_dscrmb_key_type {
    DMX_EXT_DSCRMB_KEY_TYPE_EVEN = 0,
    DMX_EXT_DSCRMB_KEY_TYPE_ODD,
    DMX_EXT_DSCRMB_KEY_TYPE_EVEN_ODD,
    DMX_EXT_DSCRMB_KEY_TYPE_EVENIV,
    DMX_EXT_DSCRMB_KEY_TYPE_ODDIV,
    DMX_EXT_DSCRMB_KEY_TYPE_CBC,
    DMX_EXT_DSCRMB_KEY_TYPE_SYSKEY,
    DMX_EXT_DSCRMB_KEY_TYPE_PVRKEY
};

/* struct for scramble key */

/**
 * @brief struct for scramble key
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_dscrmb_key {
 *         enum dmx_ext_dscrmb_key_type key_type;
 *         __u32 key_size;
 *         union {
 *             __u8 *key;
 *             __s64 reserved;
 *         };
 *     };
 *
 * @endrst
 */
struct dmx_ext_dscrmb_key {
    enum dmx_ext_dscrmb_key_type key_type;
    __u32 key_size;
    union {
        __u8 *key;
        __s64 reserved;
    };
};

/* enum for input src type */

/**
 * @brief enum for input src type
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_src_type {
 *         DMX_EXT_SRC_TYPE_IN_DEMOD,
 *         DMX_EXT_SRC_TYPE_EXT_DEMOD,
 *         DMX_EXT_SRC_TYPE_CI,
 *         DMX_EXT_SRC_TYPE_CIP,
 *         DMX_EXT_SRC_TYPE_MEM,
 *         DMX_EXT_SRC_TYPE_NULL,
 *         DMX_EXT_SRC_TYPE_USB_CI,
 *         DMX_EXT_SRC_TYPE_IPTV
 *     };
 *
 * @endrst
 */
enum dmx_src_type {
    DMX_EXT_SRC_TYPE_IN_DEMOD,
    DMX_EXT_SRC_TYPE_EXT_DEMOD,
    DMX_EXT_SRC_TYPE_CI,
    DMX_EXT_SRC_TYPE_CIP,
    DMX_EXT_SRC_TYPE_MEM,
    DMX_EXT_SRC_TYPE_NULL,
    DMX_EXT_SRC_TYPE_USB_CI,
    DMX_EXT_SRC_TYPE_IPTV
};

/* enum for hw connection type */

/**
 * @brief enum for hw connection type
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum dmx_ext_port_type {
 *         DMX_EXT_PORT_TYPE_SERIAL,
 *         DMX_EXT_PORT_TYPE_PARALLEL,
 *         DMX_EXT_PORT_TYPE_MEM, // Not use right now
 *         DMX_EXT_PORT_TYPE_NONE // Mean nothing. Default
 *     };
 *
 * @endrst
 */
enum dmx_ext_port_type {
    DMX_EXT_PORT_TYPE_SERIAL,
    DMX_EXT_PORT_TYPE_PARALLEL,
    DMX_EXT_PORT_TYPE_MEM, // Not use right now
    DMX_EXT_PORT_TYPE_NONE // Mean nothing. Default
};

/**
 * @brief struct for dmx set input config
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_source {
 *         enum dmx_src_type input_src_type;
 *         __u32 input_port_num;
 *         enum dmx_ext_port_type input_port_type;
 *     };
 *
 * @endrst
 */
struct dmx_ext_source {
    /** specific src type */
    enum dmx_src_type input_src_type;
    /** number of input */
    __u32 input_port_num;
    /** HW connection type of input port */
    enum dmx_ext_port_type input_port_type;
};

/**
 * @brief Demux Driver Log Level
 *
 * @rst
 * .. c:type:: dmx_ext_log_level
 * @endrst
 *
 * @code
 * enum dmx_ext_log_level {
 *   DMX_EXT_LOG_LEVEL_NONE = 0,
 *   DMX_EXT_LOG_LEVEL_ALERT = 1,
 *   DMX_EXT_LOG_LEVEL_CRIT = 2,
 *   DMX_EXT_LOG_LEVEL_ERROR = 3,
 *   DMX_EXT_LOG_LEVEL_WARNING = 4,
 *   DMX_EXT_LOG_LEVEL_NOTICE = 5,
 *   DMX_EXT_LOG_LEVEL_INFO = 6,
 *   DMX_EXT_LOG_LEVEL_DEBUG = 7,
 *   DMX_EXT_LOG_LEVEL_DEBUG1 = 8,
 *   DMX_EXT_LOG_LEVEL_DEBUG2 = 9
 * };
 * @endcode
 *
 */
enum dmx_ext_log_level {
    DMX_EXT_LOG_LEVEL_NONE = 0,
    DMX_EXT_LOG_LEVEL_ALERT = 1,
    DMX_EXT_LOG_LEVEL_CRIT = 2,
    DMX_EXT_LOG_LEVEL_ERROR = 3,
    DMX_EXT_LOG_LEVEL_WARNING = 4,
    DMX_EXT_LOG_LEVEL_NOTICE = 5,
    DMX_EXT_LOG_LEVEL_INFO = 6,
    DMX_EXT_LOG_LEVEL_DEBUG0 = 7,
    DMX_EXT_LOG_LEVEL_DEBUG1 = 8,
    DMX_EXT_LOG_LEVEL_DEBUG2 = 9
};

/*set parameter to DEMUX , 53 can be changed. */
/**
 * @brief Set parameter from Demux
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_S_CTL _IOW('o', 0, struct dmx_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using dmx_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_control param;
 *     int fd;
 *
 *     param.id   = DMX_EXT_CID_INIT ;
 *     param.size = 0;
 *     param.value64= 0;
 *
 *     fd = open("/dev/dvb/adapter0/demux0",O_RDWR);
 *     ioctl(fd, DMX_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`DMX_EXT_G_CTL`
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_S_CTL _IOW('o', 53, struct dmx_ext_control)

/* Get parameter from DEMUX , 54 can be changed. */
/**
 * @brief Get parameter from Demux
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_EXT_G_CTL _IOW('o', 0, struct dmx_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using dmx_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *         int ret = 0;
 *         struct dmx_ext_control argp;
 *         argp.id = DMX_EXT_CID_PLATFORM;
 *         ret = ioctl(fd, DMX_EXT_G_CTL,&argp);
 *
 * Seealso
 *   - :c:macro:`DMX_EXT_S_CTL`
 *   - :cpp:any:`dmx_ext_control`
 * @endrst
 */
#define DMX_EXT_G_CTL _IOWR('o', 54, struct dmx_ext_control)

/**
 * @brief  Register TEMI(Timed external media information) filter
 *
 * @rst
 * Add :c:macro:`DMX_SET_TEMI_FILTER` referring to
 * :c:func:`v4l-dvb-apis:DMX_SET_FILTER`. The new filter configuration is set by
 * getting a new fd. If fd is closed, the filter is also closed.TS has TEMI
 * information and detects it using PID and timeline_id.Set the pid in
 * dmx_sct_filter_params and the timeline_id in filter.filter [0].The data to be
 * returned in the Read mode has N TEMI data types. One TEMI data is configured
 * in the form of  PTS (8 bytes, little endian) + temi_timeline_descriptor (N
 * bytes to Max 54 bytes).
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define DMX_SET_TEMI_FILTER _IOW('o', 99, struct dmx_sct_filter_params)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can register filter using dmx_sct_filter_params and this ioctl.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct dmx_ext_control argp;
 *     struct
 *     int fd = -1;
 *     struct dmx_sct_filter_params params;
 *     fd = open("/dev/dvb/adapter0/demux0", O_RDWR | O_NONBLOCK);
 *
 *     params.pid     = 0xf0; // TEMI PID is f0
 *     params.timeout = 0;
 *     params.flags   = DMX_IMMEDIATE_START;
 *     params.flags |= DMX_CHECK_CRC;
 *     memset(&params.filter, 0, sizeof(dmx_filter));
 *
 *
 *     params.filter.filter[0] = 0; // Time line id is 0
 *     params.filter.mask[0] = 0xff; // Masking 0xff
 *     rc = ioctl(fd, DMX_SET_BUFFER_SIZE, PAT_BUFFERSIZE); // 4K will be enough for TEMI
 *
 *     rc = ioctl(fd, DMX_SET_TEMI_FILTER , &params); // SET TEMI Filter
 *
 *     rc = ioctl(fd, DMX_START);
 *     rd_size = read(fd, buf, MAX_DEMUX_READ); // READ TEMI data
 *     close(fd);
 *
 * Seealso
 *   - :c:type:`v4l-dvb-apis:dmx_sct_filter_params`
 * @endrst
 */
#define DMX_SET_TEMI_FILTER _IOW('o', 99, struct dmx_sct_filter_params)

#endif /* _DVBV5_EXT_DEMUX_H_ */
