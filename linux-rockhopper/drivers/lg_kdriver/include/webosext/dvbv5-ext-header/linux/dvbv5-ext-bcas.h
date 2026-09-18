/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2021 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

/** @file dvbv5-ext-bcas.h
 *
 *  LGE BCAS Device driver header file.
 *
 *	@author		yeonju.lee@lge.com Seong.lee@lge.com
 *  @version	0.1
 *  @date		2021.06.14
 *  @see		-
 */

#ifndef _DVBV5_EXT_BCAS_H_
#define _DVBV5_EXT_BCAS_H_

#include <linux/types.h>

/*BCAS control id define for BCAS_EXT_S_CTL or  BCAS_EXT_G_CTL*/

#define DEFAULT_BCAS_DEV_NO "/dev/dvb/adapter0/bcas0"

/**
 * @brief Initialize bcas card interface module
 *
 * @rst
 * Functional Requirements
 *   This interface is called to initialize the card interface module.
 *   It is called once at boot time and It can be called once again whenever lg mw is restarted.
 *   The BCAS module should be enabled only by the BCAS_EXT_CID_INIT. No other conditions should enable the BCAS module.
 *   This principle should be kept regardless of whether the BCAS module is
 *   located inside the Soc or outside the Soc.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define BCAS_EXT_CID_INIT 0
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
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control param;
 *     int fd;
 *
 *     param.id   = BCAS_EXT_CID_INIT;
 *     param.size = 0;
 *     param.value64= ubycardIndex; // default:0
 *     fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *
 *     ioctl(fd, BCAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_S_CTL`
 *   - :cpp:any:`bcas_ext_control`
 * @endrst
 */
#define BCAS_EXT_CID_INIT 0

/**
 * @brief Reset bcas card
 *
 * @rst
 * Functional Requirements
 *   This interface is called to reset the card
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define BCAS_EXT_CID_RESET 1
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
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control param;
 *     int fd;
 *
 *     param.id   = BCAS_EXT_CID_RESET;
 *     param.size = 0;
 *     param.value64 = 0;
 *     fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *
 *     ioctl(fd, BCAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_S_CTL`
 *   - :cpp:any:`bcas_ext_control`
 * @endrst
 */
#define BCAS_EXT_CID_RESET 1

/**
 * @brief Transmit the APDU to the BCAS card
 *
 * @rst
 * Functional Requirements
 *   This interface is used to transmit the APDU to the BCAS card. This interface
 *   supports APDU as input and APDU as response output and should be managed for
 *   error occurrence during transmission.
 *   Note: Middleware calls this interface in blocked call mode. Therefore, the
 *   driver must wait for a response from the card and return the result, and if
 *   it does not respond, it must return an error. However, the operation of BCAS
 *   module should not be blocked by the above operation.
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define BCAS_EXT_CID_TRANSFER_APDU 2
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
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control param;
 *     int fd;
 *     struct struct bcas_ext_transfer_apdu apdu_data;
 *
 *     param.id   = BCAS_EXT_CID_TRANSFER_APDU ;
 *     param.size = sizeof(apdu_data);
 *     param.ptr = &apdu_data;
 *
 *     fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *
 *     ioctl(fd, BCAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_S_CTL`
 *   - :cpp:any:`bcas_ext_control`
 *   - :cpp:any:`bcas_ext_transfer_apdu`
 * @endrst
 */
#define BCAS_EXT_CID_TRANSFER_APDU 2

/**
 * @brief Get status info of bcas.
 *
 * @rst
 * Functional Requirements
 *   This interface returns the smart card's inserted or not.
 *   In addition, the active state of the smart card was added to the return value.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define BCAS_EXT_CID_CARD_STATUS 3
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
 *   On success 0 is returned. On error -1 and the errno variable is
 *   set appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *  .. code-block:: cpp
 *
 *    struct bcas_ext_control param;
 *    int fd;
 *
 *    param.id   = BCAS_EXT_CID_CARD_STATUS ;
 *    param.size = 0;
 *
 *    fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *
 *    ioctl(fd, BCAS_EXT_G_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_G_CTL`
 *   - :cpp:any:`bcas_ext_control`
 * @endrst
 */
#define BCAS_EXT_CID_CARD_STATUS 3

// clang-format on

#ifndef __user
#define __user
#endif

/**
 * @brief enum for BCAS_EXT_CID_CARD_STATUS
 *
 *
 * @rst
 *
 * If a smartcard is inserted, the return value is 1. (BCAS_EXT_CARD_STATUS_INSERTED)
 * If a smartcard is not inserted, the return value is 0. (BCAS_EXT_CARD_STATUS_NOT_INSERTED)
 * If a smartcard is active status, the return value is 2. (BCAS_EXT_CARD_STATUS_ACTIVED)
 *
 * Definition
 *   .. code-block:: cpp
 *
 *     enum bcas_ext_card_status {
 *         BCAS_EXT_CARD_STATUS_NOT_INSERTED = 0,
 *         BCAS_EXT_CARD_STATUS_INSERTED     = 1,
 *         BCAS_EXT_CARD_STATUS_ACTIVED      = 2,
 *     };
 *
 * Seealso
 *   :c:macro:`BCAS_EXT_CID_CARD_STATUS`
 * @endrst
 */
enum bcas_ext_card_status {
    BCAS_EXT_CARD_STATUS_NOT_INSERTED = 0,
    BCAS_EXT_CARD_STATUS_INSERTED     = 1,
    BCAS_EXT_CARD_STATUS_ACTIVED      = 2,
};

/* BCAS strutp for Transfer APDU */

/**
 * @brief struct for Transfer APDU
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_transfer_apdu {
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
 *   - :c:macro:`BCAS_EXT_CID_TRANSFER_APDU`
 * @endrst
 */
struct bcas_ext_transfer_apdu {
    /** (in) The length of command APDU to be transferred */
    __u32 command_apdu_len;

    /** (in) The max length of resonse APDU */
    __u32 max_response_apdu_len;

    union {
        /** (in) Holds the buffer with command APDU to be sent to the card */
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

/**
 * @brief struct for BCAS_EXT_S_CTL or  BCAS_EXT_G_CTL
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control {
 *       __u32 id; //BCAS control id
 *       __u32 size; //input parameter size, if 0 value64 is the input else ptr is the input.
 *       //union struct for memory alignment
 *       union {
 *         __s64 value64; //if size is 0, this is the real input
 *         void __user *ptr; //if size is not 0, this is the real input
 *       };
 *     };
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_G_CTL`
 *   - :c:macro:`BCAS_EXT_S_CTL`
 * @endrst
 */
struct bcas_ext_control {
    /** BCAS control id */
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
 * @brief Set parameter from BCAS
 *
 * @rst
 * Functional Requirements
 *   Set parameter from BCAS
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
 *     #define BCAS_EXT_S_CTL _IOW('o', 0, struct bcas_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control param;
 *     int fd;
 *
 *     param.id   = BCAS_EXT_CID_INIT ;
 *     param.size = 0;
 *     param.value64= 0;
 *
 *     fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *     ioctl(fd, BCAS_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_S_CTL`
 *   - :cpp:any:`bcas_ext_control`
 * @endrst
 */
#define BCAS_EXT_S_CTL _IOW('o', 0, struct bcas_ext_control)

/**
 * @brief Get parameter from BCAS
 *
 * @rst
 * Functional Requirements
 *   Get parameter from BCAS
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
 *     #define BCAS_EXT_G_CTL _IOWR('o', 1, struct bcas_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using bcas_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct bcas_ext_control param;
 *     int fd;
 *
 *     param.id   = BCAS_EXT_CID_CARD_STATUS ;
 *     param.size = 0;
 *
 *     fd = open("/dev/dvb/adapter0/bcas0",O_RDWR);
 *
 *     ioctl(fd, BCAS_EXT_G_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`BCAS_EXT_G_CTL`
 *   - :cpp:any:`bcas_ext_control`
 * @endrst
 */
#define BCAS_EXT_G_CTL _IOWR('o', 1, struct bcas_ext_control)

#endif /* _DVBV5_EXT_BCAS_H_ */
