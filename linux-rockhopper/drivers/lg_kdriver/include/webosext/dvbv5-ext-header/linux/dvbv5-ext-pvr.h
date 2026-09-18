/*
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 */

/** @file dvbv5-ext-pvr.h
 *
 *  LGE PVR header file.
 *
 *  @author     Hwachin Lee(hwachin.lee@lge.com)
 *  @version    0.1
 *  @date       2019.2.12
 */

#ifndef _DVBV5_EXT_PVR_H_
#define _DVBV5_EXT_PVR_H_

#include <linux/dvb/dmx.h>

/**
 * @brief Set PVR Upload Speed
 *
 * @rst
 * Functional Requirements
 *   This command is used to control the playback speed during playback.
 *
 * Responses to abnormal situations, including
 *   NA.
 *
 * Performance Requirements
 *   NA.
 *
 * Constraints
 *   NA.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_CID_SETRATE     1
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using pvr_ext_control and this control id.
 *
 *   +------------+-----------------------------------------+
 *   | pvr_ext_control example                              |
 *   +============+=========================================+
 *   | id         |      PVR_EXT_CID_SETRATE                |
 *   +------------+-----------------------------------------+
 *   | size       |      0                                  |
 *   +------------+-----------------------------------------+
 *   | value64    |      value for pvr upload control       |
 *   +------------+-----------------------------------------+
 *
 *
 *
 * The meaning of control value is like below
 *
 *   +-------------------------+---------------------------------+
 *   | value                   |  description                    |
 *   +=========================+=================================+
 *   | 0                       |   pause                         |
 *   +-------------------------+---------------------------------+
 *   | 100                     |   normal play                   |
 *   +-------------------------+---------------------------------+
 *   | 200/400/800/1600        |   2xFF/4xFF/8xFF/16xFF          |
 *   +-------------------------+---------------------------------+
 *   | -200/-400/-800/-1600    |   2xREW/4xREW/8xREW/16xREW      |
 *   +-------------------------+---------------------------------+
 *   | 50                      |   slow play                     |
 *   +-------------------------+---------------------------------+
 *
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd = open(deviceNode, O_WRONLY|O_NONBLOCK|O_CLOEXEC);
 *     struct pvr_ext_control param;
 *     param.id = PVR_EXT_CID_SETRATE;
 *     param.size = 0;
 *     param.value64 = rateValue;
 *     int ret = ioctl(fd , PVR_EXT_S_CTL , &param);
 *
 *
 * Seealso
 *   - :cpp:any:`pvr_ext_control`
 *
 * @endrst
 */
#define PVR_EXT_CID_SETRATE 1


/**
 * @brief Set PVR Reset upload
 *
 * @rst
 * Functional Requirements
 *   This command is used to reset upload buffer
 *
 * Responses to abnormal situations, including
 *   NA.
 *
 * Performance Requirements
 *   NA.
 *
 * Constraints
 *   NA.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_CID_RESET     2
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using pvr_ext_control and this control id.
 *
 *   +------------+-------------------------------+
 *   | pvr_ext_control example                    |
 *   +============+===============================+
 *   | id         |      PVR_EXT_CID_RESET        |
 *   +------------+-------------------------------+
 *   | size       |      0                        |
 *   +------------+-------------------------------+
 *   | value64    |      NA                       |
 *   +------------+-------------------------------+
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd = open(deviceNode, O_WRONLY|O_NONBLOCK|O_CLOEXEC);
 *     struct pvr_ext_control param;
 *     param.id = PVR_EXT_CID_RESET;
 *     param.size = 0;
 *     param.value64 = 0;
 *     int ret = ioctl(fd , PVR_EXT_S_CTL , &param);
 *
 *
 * Seealso
 *   - :cpp:any:`pvr_ext_control`
 *
 * @endrst
 */
#define PVR_EXT_CID_RESET 2



/**
 * @brief Set PVR certification for PVR operation
 *
 * @rst
 * Functional Requirements
 *   This command is for device certification before download.
 *   The certification value is defined as specific values which is based on the secure key.
 *   If the value is same to predefined specific value, the certification is success.
 *   After success the certification, read operation will pass data successfully.
 *   Beside that read operation should be return negative vaule.
 *
 * Responses to abnormal situations, including
 *   NA
 *
 * Performance Requirements
 *   NA
 *
 * Constraints
 *   NA
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_CID_CERT     3
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using pvr_ext_control and this control id.
 *
 *   +------------+-------------------------------+
 *   | pvr_ext_control example                    |
 *   +============+===============================+
 *   | id         |      PVR_EXT_CID_CERT         |
 *   +------------+-------------------------------+
 *   | size       |      32                       |
 *   +------------+-------------------------------+
 *   | value64    |      cert key                 |
 *   +------------+-------------------------------+
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     #define SEED_KEY_LEN 16
 *     #define CERT_KEY_LEN (SEED_KEY_LEN * 2)
 *
 *     uint8_t randTbl[CERT_KEY_LEN] =
 *     {
 *         0x6a,0xb0,0xad,0x8c,0x4e,0x69,0x40,0x2c,
 *         0x58,0x2e,0x1e,0xc0,0xf5,0xbe,0xc9,0x83,
 *         0x21,0xe1,0x07,0x46,0x5b,0xa9,0x7c,0xaa,
 *         0x9b,0x0f,0x2b,0x25,0x80,0x88,0x3e,0x6b
 *     };
 *
 *     uint8_t seedkey[SEED_KEY_LEN] = {0,};
 *     uint8_t certKey[CERT_KEY_LEN] = {0,};
 *     HAL_PVR_CRYPTO_GetSecureKey(NULL, seedkey);
 *
 *     for(int i = 0 ; i < CERT_KEY_LEN ; i++)
 *     {
 *         certKey[i] = seedkey[i % SEED_KEY_LEN] ^ randTbl[i];
 *     }
 *
 *     int fd = open(deviceNode, O_WRONLY|O_NONBLOCK|O_CLOEXEC);
 *     struct pvr_ext_control param;
 *     param.id = PVR_EXT_CID_CERT;
 *     param.size = 32;
 *     param.ptr = certKey;
 *     int ret = ioctl(fd , PVR_EXT_S_CTL , &param);
 *
 *
 * Seealso
 *   - :cpp:any:`pvr_ext_control`
 *
 * @endrst
 */
#define PVR_EXT_CID_CERT 3


/**
 * @brief Set PVR packet length
 *
 * @rst
 * Functional Requirements
 *   Set pvr packet length with passed value. The value should be one of 188 and 192.
 *   Default packet length should be 192
 *
 * Responses to abnormal situations, including
 *   NA
 *
 * Performance Requirements
 *   NA
 *
 * Constraints
 *   This function for test or debug. It will not be included on TV product.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_CID_SET_PKTLEN     3
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using pvr_ext_control and this control id.
 *
 *   +------------+-------------------------------+
 *   | pvr_ext_control example                    |
 *   +============+===============================+
 *   | id         |      PVR_EXT_CID_SET_PKTLEN   |
 *   +------------+-------------------------------+
 *   | size       |      0                        |
 *   +------------+-------------------------------+
 *   | value64    |      188 or 192               |
 *   +------------+-------------------------------+
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd = open(deviceNode, O_WRONLY|O_NONBLOCK|O_CLOEXEC);
 *     struct pvr_ext_control param;
 *     param.id = PVR_EXT_CID_SET_PKTLEN;
 *     param.size = 0;
 *     param.value64 = 188;
 *     int ret = ioctl(fd , PVR_EXT_S_CTL , &param);
 *
 *
 * Seealso
 *   - :cpp:any:`pvr_ext_control`
 *
 * @endrst
 */
#define PVR_EXT_CID_SET_PKTLEN 4

#ifndef __user
#define __user
#endif

/**
 * @brief struct for PVR_EXT_S_CTL or  PVR_EXT_G_CTL
 *
 * @rst
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     struct pvr_ext_control {
 *         __u32 id;   // PVR control id
 *         __u32 size; // input parameter size, if 0 value64 is the input else ptr is the input.
 *         // union struct for memory alignment
 *         union {
 *             __s64 value64;    // if size is 0, this is the real input
 *             void __user *ptr; // if size is not 0, this is the real input
 *         };
 *     };
 *
 * Seealso
 *   :c:macro:`PVR_EXT_S_CTL`
 *   :c:macro:`PVR_EXT_G_CTL`
 * @endrst
 */
struct pvr_ext_control {
    /** PVR control id */
    __u32 id;
    /** input parameter size, if 0 value64 is the input else ptr is the input. */
    __u32 size;
    /** union struct for memory alignment */
    union {
        /** if size is 0, this is the real input */
        __s64 value64;
        /** if size is not 0, this is the real input */
        void __user *ptr;
    };
};



/*set parameter to PVR , 0 can be changed. */
/**
 * @brief Set parameter to PVR
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_S_CTL _IOW('o', 0, struct pvr_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using pvr_ext_control and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct pvr_ext_control param;
 *     int fd;
 *
 *     param.id   = PVR_EXT_CID_RESET ;
 *     param.size = 0;
 *     param.value64= 0;
 *
 *     fd = open("/dev/dvb/adapter0/dvr0",O_WRONLY|O_NONBLOCK|O_CLOEXEC);
 *     ioctl(fd, PVR_EXT_S_CTL, &param);
 *
 * Seealso
 *   - :c:macro:`PVR_EXT_G_CTL`
 *   - :cpp:any:`pvr_ext_control`
 * @endrst
 */
#define PVR_EXT_S_CTL _IOW('p', 0, struct pvr_ext_control)


/* Get parameter from PVR , 1 can be changed. */
/**
 * @brief Get parameter from PVR
 *
 * @rst
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define PVR_EXT_G_CTL _IOWR('p', 1, struct pvr_ext_control)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable will be set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using pvr_ext_control and this control id.
 *   This function is not used currently.
 *
 * Example
 *   .. code-block:: cpp
 *
 *         int ret = 0;
 *         struct pvr_ext_control argp;
 *         argp.id = PVR_EXT_CID_XXXX;
 *         ret = ioctl(fd, PVR_EXT_G_CTL,&argp);
 *
 * Seealso
 *   - :c:macro:`PVR_EXT_S_CTL`
 *   - :cpp:any:`pvr_ext_control`
 * @endrst
 */
#define PVR_EXT_G_CTL _IOWR('p', 1, struct pvr_ext_control)

#endif /* _DVBV5_EXT_PVR_H_ */
