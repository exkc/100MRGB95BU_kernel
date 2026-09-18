/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

/** @file dvbv5-ext-acas.h
 *
 *  LGE ACAS Device driver header file.
 *
 *	@author		yeonju.lee@lge.com Seong.lee@lge.com
 *  @version	0.1
 *  @date		2019.02.22
 *  @see		-
 */

#ifndef _DVBV5_EXT_ACAS_H_
#define _DVBV5_EXT_ACAS_H_ 

#include <linux/types.h>

/*ACAS control id define for ACAS_EXT_S_CTL or  ACAS_EXT_G_CTL*/

#define DEFAULT_ACAS_DEV_NO "/dev/dvb/adapter0/acas0"

/**
 * @brief Initialize acas chip interface module
 *
 * @rst
 * Functional Requirements
 *   This interface is called to initialize the chip interface module. It is called once at boot time and is not called at a later time.
 *   The ACAS module should be enabled only by the ACAS_EXT_CID_INIT. No other conditions should enable the ACAS module.
 *   This principle should be kept regardless of whether the ACS module is
 *   located inside the Soc or outside the Soc.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_CID_INIT 0
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
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control param;
 *     int fd;
 *
 *     param.id   = ACAS_EXT_CID_INIT;
 *     param.size = 0;
 *     param.value64= ubyChipIndex; // default:0
 *     fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *
 *     ioctl(fd, ACAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_S_CTL`
 *   - :cpp:any:`acas_ext_control`
 * @endrst
 */
#define ACAS_EXT_CID_INIT 0

/**
 * @brief Reset acas chip
 *
 * @rst
 * Functional Requirements
 *   This interface is called to reset the chip.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_CID_RESET 1
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
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control param;
 *     int fd;
 *
 *     param.id   = ACAS_EXT_CID_RESET;
 *     param.size = 0;
 *     param.value64 = 0;
 *     fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *
 *     ioctl(fd, ACAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_S_CTL`
 *   - :cpp:any:`acas_ext_control`
 * @endrst
 */
#define ACAS_EXT_CID_RESET 1

/**
 * @brief Transmit the APDU to the ACAS chip
 *
 * @rst
 * Functional Requirements
 *   This interface is used to transmit the APDU to the ACAS chip. This interface
 *   supports APDU as input and APDU as response output and should be managed for
 *   error occurrence during transmission.
 *   Note: Middleware calls this interface in blocked call mode. Therefore, the
 *   driver must wait for a response from the card and return the result, and if
 *   it does not respond, it must return an error. However, the operation of ACAS
 *   module should not be blocked by the above operation.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_CID_TRANSFER_APDU 2
 *
 * Responses to abnormal situations, including
 *   Even if communication fails, it should be returned within 1 second.
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
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control param;
 *     int fd;
 *     struct struct acas_ext_transfer_apdu apdu_data;
 *
 *     param.id   = ACAS_EXT_CID_TRANSFER_APDU ;
 *     param.size = sizeof(apdu_data);
 *     param.ptr = &apdu_data;
 *
 *     fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *
 *     ioctl(fd, ACAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_S_CTL`
 *   - :cpp:any:`acas_ext_control`
 *   - :cpp:any:`acas_ext_transfer_apdu`
 * @endrst
 */
#define ACAS_EXT_CID_TRANSFER_APDU 2

/**
 * @brief Read waiting time for reset from ACAS chip.
 *
 * @rst
 * Functional Requirements
 *   The waiting time returned from ACAS chip when call reset. API should wait
 *   then try reset again. This time is delivered at T2 field in ATR packet
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_CID_GET_RESET_TIME 3
 *
 * Responses to abnormal situations, including
 *   Function elapsed time should be less than 1000ms.
 *
 * Performance Requirements
 *   Return As soon as possible when Reset wait time is updated
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is
 *   set appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *  .. code-block:: cpp
 *
 *    struct acas_ext_control param;
 *    int fd;
 *
 *    param.id   = ACAS_EXT_CID_GET_RESET_TIME ;
 *    param.size = 0;
 *
 *    fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *
 *    ioctl(fd, ACAS_EXT_G_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_G_CTL`
 *   - :cpp:any:`acas_ext_control`
 * @endrst
 */
#define ACAS_EXT_CID_GET_RESET_TIME 3

// clang-format on

#ifndef __user
#define __user
#endif

/* ACAS strutp for Transfer APDU */

/**
 * @brief struct for Transfer APDU
 *
 * @rst
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     struct acas_ext_transfer_apdu {
 *       __u32 command_apdu_len;
 *       __u32 max_response_apdu_len;
 *       union {
 *       __u8 *command_apdu;
 *       __u64 reserved1;
 *       };
 *       union {
 *       __u8 *response_apdu;
 *       __u64 reserved2;
 *       };
 *       union {
 *       __u32 *response_apdu_len;
 *       __u64 reserved3;
 *       };
 *     };
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_CID_TRANSFER_APDU`
 * @endrst
 */
struct acas_ext_transfer_apdu {
    /** (in) The length of command APDU to be transferred */
    __u32 command_apdu_len;

    /** (in) The max length of resonse APDU */
    __u32 max_response_apdu_len;

    union {
        /** (in) Holds the buffer with command APDU to be sent to the chip */
        __u8 *command_apdu;
        __u64 reserved1;
    };

    union {
        /** (out) Holds the buffer to receive the response APDU */
        __u8 *response_apdu;
        __u64 reserved2;
    };

    union {
        /** (out) Holds the length of response APDU receive */
        __u32 *response_apdu_len;
        __u64 reserved3;
    };
};

/* ACAS strutp for Transfer APDU */

struct acas_ext_reset_time {
    __u32 chip_index;
    __u32 reset_time;
};

/**
 * @brief struct for ACAS_EXT_S_CTL or  ACAS_EXT_G_CTL
 *
 * @rst
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control {
 *       __u32 id; //ACAS control id
 *       __u32 size; //input parameter size, if 0 value64 is the input else ptr is the input.
 *       //union struct for memory alignment
 *       union {
 *         __s64 value64; //if size is 0, this is the real input
 *         void __user *ptr; //if size is not 0, this is the real input
 *       };
 *     };
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_G_CTL`
 *   - :c:macro:`ACAS_EXT_S_CTL`
 * @endrst
 */
struct acas_ext_control {
    /** ACAS control id */
    __u32 id;

    /** input parameter size, if 0 value64 is the input else ptr is the input */
    __u32 size;

    /** union struct for memory alignment */
    union {
        /** if size is 0, this is the real input */
        __s64 value64;

        /** if size is not 0, this is the real input */
        void __user *ptr;
    };
};

/**
 * @brief Set parameter from ACAS
 *
 * @rst
 * Functional Requirements
 *   Set parameter from ACAS
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
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_S_CTL _IOW('o', 0, struct acas_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control param;
 *     int fd;
 *
 *     param.id   = ACAS_EXT_CID_INIT ;
 *     param.size = 0;
 *     param.value64= 0;
 *
 *     fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *     ioctl(fd, ACAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_S_CTL`
 *   - :cpp:any:`acas_ext_control`
 * @endrst
 */
#define ACAS_EXT_S_CTL _IOW('o', 0, struct acas_ext_control) // 62 -> or ??

/**
 * @brief Get parameter from ACAS
 *
 * @rst
 * Functional Requirements
 *   Get parameter from ACAS
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
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define ACAS_EXT_G_CTL _IOWR('o', 1, struct acas_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using acas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct acas_ext_control param;
 *     int fd;
 *
 *     param.id   = ACAS_EXT_CID_GET_RESET_TIME ;
 *     param.size = 0;
 *
 *     fd = open("/dev/dvb/adapter0/acas0",O_RDWR);
 *
 *     ioctl(fd, ACAS_EXT_G_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`ACAS_EXT_G_CTL`
 *   - :cpp:any:`acas_ext_control`
 * @endrst
 */
#define ACAS_EXT_G_CTL _IOWR('o', 1, struct acas_ext_control) // 63 -> or ??

#endif /* _DVBV5_EXT_ACAS_H_ */
