/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

/** @file dvbv5-ext-ca.h
 *
 *  LGE CA Device driver header file.
 *
 *	@author		Seong Lee(seong.lee@lge.com)
 *  @version	0.1
 *  @date		2018.10.12
 *  @see		-
 */

#ifndef _DVBV5_EXT_CA_H_
#define _DVBV5_EXT_CA_H_

#include <linux/dvb/ca.h>
#include <linux/types.h>

/**
 * @brief Device file for CI / CI + 1.3 control
 *
 * @rst
 * Functional Requirements
 *   Open device file for CI / CI + 1.3 control
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     open()
 *
 * Return Value
 *   None
 *
 * Control Type
 *   None
 *
 * Example
 *   .. code-block:: cpp
 *
 *     open("/dev/dvb/adapter0/ca0", O_RDWR | O_NONBLOCK | O_CLOEXEC);
 *
 * @endrst
 */
#define DEFAULT_CA_DEV_NO "/dev/dvb/adapter0/ca0"

/**
 * @brief Device file for CI+ 1.4 control
 *
 * @b Pseudocode
 * @code
 * open("/dev/dvb/adapter0/ca1", O_RDWR | O_NONBLOCK | O_CLOEXEC);
 * @endcode
 *
 */
#define STRING_CIP0_DEV "/dev/dvb/adapter0/ca1"

/**
 * @brief Device file for CI+ 1.4 control
 *
 * @b Pseudocode
 * @code
 * open("/dev/dvb/adapter0/ca2", O_RDWR | O_NONBLOCK | O_CLOEXEC);
 * @endcode
 *
 */
#define STRING_CIP1_DEV "/dev/dvb/adapter0/ca2"

/**
 * @brief Device file for CI+ 1.4 control
 *
 * @b Pseudocode
 * @code
 * open("/dev/dvb/adapter0/ca3", O_RDWR | O_NONBLOCK | O_CLOEXEC);
 * @endcode
 *
 */
#define STRING_CIP2_DEV "/dev/dvb/adapter0/ca3"

/*CI control id define for CA_EXT_S_CTL or  CA_EXT_G_CTL*/
// CI~CI+ 1.3
/**
 * @brief Sets input type of the CI Device
 *
 * @rst
 * Functional Requirements
 *   CI control id define for CA_EXT_S_CTL or  CA_EXT_G_CTL
 *
 *   Set a input type of the CA.This Command ID set the TS path through which
 *   Signal flows from Tuner to CA or Signal flows from CI Plus 1.4 to CA.
 *
 *   - Data from Tuner: CA_EXT_SRC_TYPE_IN_DEMOD or CA_EXT_SRC_TYPE_EXT_DEMOD
 *   - Data from CI Plus 1.4 module: CA_EXT_SRC_TYPE_CIP
 *
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
 *     // Command
 *     CA_EXT_CID_INPUTSOURCE
 *
 *     // Parameter : ca_ext_control example
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_INPUTSOURCE                    |
 *     +------------+-------------------------------------------------+
 *     | size       |       size of ca_ext_source                     |
 *     +------------+-------------------------------------------------+
 *     | ptr        |       pointer of ca_ext_source                  |
 *     +------------+-------------------------------------------------+
 *
 * Return Value
 *   Return 0 if it success.
 *
 *   On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the Generic Error
 *   Codes chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int rc = 0;
 *     struct ca_ext_source config = {0,};
 *     struct ca_ext_control param ={0,};
 *
 *     config.input_port_num = 0;
 *     config.input_src_type = CA_EXT_SRC_TYPE_IN_DEMOD;
 *
 *     param.id   = CA_EXT_CID_INPUTSOURCE;
 *     param.size = sizeof(struct ca_ext_source);
 *     param.ptr  = &config;
 *
 *     rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 *
 * See also
 *   - :cpp:any:`CA_EXT_S_CTL`
 *   - :cpp:any:`CA_EXT_G_CTL`
 *   - :cpp:any:`ca_ext_source`
 *
 * @endrst
 */
#define CA_EXT_CID_INPUTSOURCE 0

/**
 * @brief Reads DA(Data Available) bit in a status register.
 * @li This will be deprecated.  This feature has been changed to use poll()
 *
 * @see
 * @li poll
 */
#define CA_EXT_CID_DA_STATUS 1

/**
 * @brief Set status-check mode in HW IO access
 *
 * CI control id define for CA_EXT_S_CTL or  CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_ERROR_MODE ;
 * argp.size = 0;
 * argp.value64 =  0 : Full check, 1 : Simple check
 *
 * ret = ioctl(fd, CA_EXT_S_CTL,&argp);
 *
 * struct ca_ext_control argp2;
 * argp2.id = CA_EXT_CID_ERROR_MODE ;
 * argp2.size = 0;
 * argp2.value64 =  0;
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp2);
 * @endcode
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set
 * appropriately. The generic error codes are described at the Generic Error
 * Codes chapter.
 *
 * @param[in] ptr pointer of ca_ext_control which as below.
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_ERROR_MODE                     |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0 : Full check, 1 : Simple check          |
 *     +------------+-------------------------------------------------+
 * @endrst
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_G_CTL
 * @li ca_ext_error_mode
 */
#define CA_EXT_CID_ERROR_MODE 2

/**
 * @brief Check the value of CAM between CI CAM and CI+ CAM
 *
 * Returns the value of CAM Capability from value64 that was the passed structure.
 *
 * CI control id define for CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_PLUS_CAPA ;
 * argp.size = 0;
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_PLUS_CAPA                      |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0 : CI CAM, 1 : CI Plus Cam               |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set
 * appropriately. The generic error codes are described at the Generic Error
 * Codes chapter.
 *
 *
 * @see
 * @li CA_EXT_G_CTL
 */
#define CA_EXT_CID_PLUS_CAPA 3

/**
 * @brief Gets the data rate on PCMICA bus for CI Plus. Gets the data rate on
 * PCMICA bus for CI Plus.It must be used only for CI Plus.
 *
 * Returns the data rate of the PCMICA bus in value64 inside the passed structure.
 *
 * CI control id define for CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_DATA_RATE ;
 * argp.size = 0;
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *

 * @return 0 if it success. On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_DATA_RATE                      |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0 : 72 Mbit/s, 1 : 96 Mbit/s              |
 *     +------------+-------------------------------------------------+
 * @endrst
 *
 * @see
 * @li CA_EXT_G_CTL
 * @li ca_ext_ciplus_datarate
 */
#define CA_EXT_CID_DATA_RATE 4

/**
 * @brief Set PCMCIA read, write speed setting.
 *
 *
 * Returns the data rate of the PCMICA bus in value64 inside the passed structure.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_PCMCIA_SPEED ;
 * argp.size = 0;
 * argp.value64 =  0
 *
 * ret = ioctl(fd, CA_EXT_S_CTL,&argp);
 *
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_PCMCIA_SPEED                   |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0: pcmcia read,write speed low            |
 *     +            +-------------------------------------------------+
 *     |            |       1: pcmcia read,write speed high           |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 * @see
 * @li CA_EXT_S_CTL
 */
#define CA_EXT_CID_PCMCIA_SPEED 5

/**
 * @brief This will be deprecated.
 */
#define CA_EXT_CID_FAST_POOL_TIME 6

/**
 * @brief Reads CI PLUS version in the CIS information.
 *
 * Reads CI PLUS version in the CIS information.
 * It must be used only for CI Plus.
 * See CI PLUS spec 1.3.1 G.3 CI Plus Compatibility Identification.
 *
 * Returns Ci plus version in value64 inside the passed structure.
 *
 * CI control id define for CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1; struct ca_ext_control argp; argp.id = CA_EXT_CID_PLUS_VERSION ;
 * argp.size = 0; argp.value64 =  0
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_PLUS_VERSION                   |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       value of CI PLUS Version                  |
 *     +------------+-------------------------------------------------+
 *
 *     If CI PLUS version is exist, It returns the CI PLUS version.
 *     If ciplus is more than 8, it return (0x1)
 *
 *     * $compatible[ciplus=1]$ -> return (0x00000001)
 *     * $compatible[ciplus=2]$ -> return (0x00000010)
 *     * $compatible[ciplus=8]$ -> return (0x10000000)
 *     * $compatible[ciplus=*2]$ -> return (0x00000011)
 *     * $compatible[ciplus=*3]$ -> return (0x00000111)
 *     * $compatible[ciplus=*8]$ -> return (0x11111111)
 *     * $compatible[ciplus=*2 ciprof=0x890a4401]$-> return (0x00000011)
 *     * $compatible[ciplus=*3 ciprof=0x890a4401]$-> return (0x00000111)
 *     * $compatible[ciplus=*8 ciprof=0x890a4401]$-> return (0x11111111)
 *     * $compatible[ciplus=*4 ciplus=-3 ciprof=0x890a4401]$-> return (0x00001011)
 *     * $compatible[ciplus=*7 ciplus=-3 ciplus=-5 ciprof=0x890a4401]$-> return (0x01101011)
 *
 *     If CI PLUS version does not exist or Something is wrong,the return value is 0.
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
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 *
 * @see
 * @li CA_EXT_G_CTL
 */
#define CA_EXT_CID_PLUS_VERSION 7

/**
 * @brief Reads Initialize Interface Request bit
 *
 * Reads IIR(Initialize Interface Request) bit in a status register for CI
 * Plus.It must be used only for CI Plus.The CICAM sets this bit to request a
 * physical interface reset. After setting the IIR bit, the CICAM shall not send
 * any other APDUs to the host.The CICAM clears the IIR bit when the host sets
 * the TS bit during the reset.
 *
 * Returns the value of the interface request initialization bit in value64 inside the passed structure.
 *
 * CI control id define for CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_PLUS_IIR_STATUS ;
 * argp.size = 0; argp.value64 =  0
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_PLUS_IIR_STATUS                |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       Initialize Interface Request bit value    |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 */
#define CA_EXT_CID_PLUS_IIR_STATUS 8

/**
 * @brief Writes a '1' to the RS bit in the Control Register
 *
 * Resets CI device(PCMCIA reset). During device initialization, and if there is
 * an error, the host needs to be able to reset the interface. This function
 * writes a '1' to the RS bit in the Control Register. The device clears out any
 * data in its data transfer buffer(s) and sets the interface so that it can
 * perform the buffer size negotiation protocol. The reset operation is
 * completed by setting the FR bit to 1. *
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_SET_RS_BIT ;
 * argp.size = 0;
 * argp.value64 =  0
 *
 * ret = ioctl(fd, CA_EXT_S_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_SET_RS_BIT                     |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
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
 *
 * @see
 * @li CA_EXT_S_CTL
 */
#define CA_EXT_CID_SET_RS_BIT 9

/**
 * @brief Get negotiated buffer size of CAM
 *
 * Getting of negotiated buffer size during module initialization. See chapter
 * A.2.2.1.1 on EUROPEAN STANDARD En50221 specification for more details on
 * buffer negotiation protocol. Due to the limit of the kernel buffer, read and
 * write to the physical layer must be supported.To do this, the application
 * must know the negotiated buffer size.
 *
 * Returns the value of the negotiated buffer size in value64 inside the passed structure.
 *
 * There exists a function whose name is dvb_ca_en50221_write_data in dvb_ca_en50221.c.
 * In side this function is a writing operation of the negotiated Buffer Size like below
 *
 * If ((status == ca->pub->write_cam_control(ca->pub, slot, CTRLIF_COMMAND, IRQEN | CMDREG_HC)) != 0)
 * goto exit;
 *
 * But the parts is wrong. It should be like below
 *
 * If ((status == ca->pub->write_cam_control(ca->pub, slot, CTRLIF_COMMAND, SW | IRQEN | CMDREG_HC)) != 0)
 * goto exit;
 *
 * For this reason, you must create another function for writing the negotiated Buffer Size
 *
 * CI control id define for CA_EXT_G_CTL
 *
 * @b Pseudocode
 * @code
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = DIL_CA_EXT_CID_GET_NEGO_BUFF ;
 * argp.size = 0;
 * argp.value64 =  0
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_GET_NEGO_BUFF                  |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       Size of Negotiated buffer                 |
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
 * @see
 * @li CA_EXT_G_CTL
 */
#define CA_EXT_CID_GET_NEGO_BUFF 10

/**
 * @brief Set log level in CA driver and kernel
 *
 * Setting and getting of log print level in Demux and CA drivers.
 * Each log levels have its own log printing rules.
 *
 * Returns the current log levels
 *
 * CI control id define for CA_EXT_G_CTL and CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 *
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_LOG_LEVEL ;
 * argp.size = 0;
 * argp.value64 = CA_EXT_LOG_LEVEL_INFO;
 *
 * ret = ioctl(fd, CA_EXT_S_CTL,&argp);
 *
 *
 * int ret = -1;
 * struct ca_ext_control argp;
 * argp.id = CA_EXT_CID_LOG_LEVEL ;
 * argp.size = 0;
 * argp.value64 = 0
 *
 * ret = ioctl(fd, CA_EXT_G_CTL,&argp);
 *
 * return argp.value64;
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_LOG_LEVEL                      |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       Enum of ca_ext_log_level                  |
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
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_G_CTL
 */
#define CA_EXT_CID_LOG_LEVEL 11

// CI+ 1.4
#define CA_EXT_CID_PLUS14_BASE 100

/**
 * @brief Sets the connecting configuration between Input source to CIPLUS14.
 *
 * @rst
 * Functional Requirements
 *   InternalDemod(0~?), ExternalDemod(0~?) = Data from tuner
 *   CA_EXT_SRC_TYPE_MEM = Data from Network.
 *   CI control id define for CA_EXT_S_CTL
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
 *     // Command
 *     CA_EXT_CID_PLUS14_INPUTSOURCE
 *
 *     // Parameter
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |       CA_EXT_CID_PLUS14_INPUTSOURCE             |
 *     +------------+-------------------------------------------------+
 *     | size       |       size of ca_ext_source                     |
 *     +------------+-------------------------------------------------+
 *     | ptr        |       pointer of ca_ext_source                  |
 *     +------------+-------------------------------------------------+
 *
 * Return Value
 *   Return 0 if it success.
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the Generic Error Codes chapter.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int fd;
 *     char path[64];
 *     snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 *     fd = open(path, O_RDWR);
 *
 *
 *     struct ca_ext_control param;
 *     struct ca_ext_source config;
 *
 *
 *     param.id   = CA_EXT_CID_PLUS14_INPUTSOURCE ;
 *     param.size = sizeof(config);
 *     param.ptr  = &config;
 *
 *     config.input_src_type = CA_EXT_SRC_TYPE_MEM;
 *     config.input_port_num = 0;
 *
 *
 *     rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 *  See also
 *    - :cpp:any:`CA_EXT_S_CTL`
 *
 * @endrst
 */
#define CA_EXT_CID_PLUS14_INPUTSOURCE CA_EXT_CID_PLUS14_BASE + 1

/**
 * @brief Gets the number of PID filters
 *
 * This interface is used to obtain the number of PID filters that can be processed per channel.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 * param.id   = CA_EXT_CID_PLUS14_NUM_OF_PID_FILTER_PER_CH ;
 * param.size = 0;
 * param.value64  = 0;
 *
 * rc = ioctl(fd, CA_EXT_G_CTL, &param);
 * @endcode
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_NUM_OF_PID_FILTER_PER_CH       |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
 *     +------------+-------------------------------------------------+
 * @endrst
 *
 * @see
 * @li CA_EXT_G_CTL
 */
#define CA_EXT_CID_PLUS14_NUM_OF_PID_FILTER_PER_CH CA_EXT_CID_PLUS14_BASE + 2

/**
 * @brief adds PID on the PID SELECTOR (PID Filter) of the CIPLUS1.4-MULTIPLEXER
 *
 * This interface is used to obtain the number of PID filters that can be processed per channel.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_ADD_PID_FILTER;
 * param.size = 0
 * param.value64= 0x??;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_ADD_PID_FILTER                 |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       value of PID                              |
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
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_REMOVE_PID_FILTER
 */
#define CA_EXT_CID_PLUS14_ADD_PID_FILTER CA_EXT_CID_PLUS14_BASE + 3

/**
 * @brief Removes PID from the PID SELECTOR
 *
 * This function is only used in RF-DTV mode. This function removes PID from the
 * PID SELECTOR (PID Filter) of the CIPLUS14-MULTIPLEXERs input. The PID which
 * will be removed from the PID SELECTOR are specified in parameter.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_REMOVE_PID_FILTER;
 * param.size = 0
 * param.value64= 0x??;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_REMOVE_PID_FILTER              |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       value of PID                              |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_ADD_PID_FILTER
 */
#define CA_EXT_CID_PLUS14_REMOVE_PID_FILTER CA_EXT_CID_PLUS14_BASE + 4

/**
 * @brief Enable data transfer
 *
 * This function is used in the both cases of IP-Delivery mode and TS mode.
 * When called, parameters are ignored and enable data transfer
 *
 * Soc can detemine the channel with fd.
 * In IP-Delivery mode case, Target Channel should be CA1 or CA2 or CA3.
 * In TS mode case, It also same as IP-Delivery mode.
 * Local TS of 0x47 is always assigned to CA1.
 * Local TS of 0x48 is always assigned to CA2.
 * Local TS of 0x49 is always assigned to CA3.
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_START_SENDING_DATA;
 * param.size = 0
 * param.value64= 0;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_START_SENDING_DATA             |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
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
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_STOP_SENDING_DATA
 */
#define CA_EXT_CID_PLUS14_START_SENDING_DATA CA_EXT_CID_PLUS14_BASE + 5

/**
 * @brief Disable data transfer
 *
 * This function is used both cases of IP-Delivery mode and TS(RF-DTV) mode.
 *
 * 1 In IP-Delivery mode, The operating principle is like below. In this mode,
 * this function stops the delivery of IP-Data from the uploading Memory buffer
 * to CIPLUS14-Multiplxers input in Host-IP-Delivery Mode and
 * CICIAM-IP-Delivery Mode. When this function is called, a processor or an
 * Micom which were independently dedicated for the delivery of IP-Data from the
 * uploading Memory buffer to CIPLUS14-Multiplexers Input stops. By calling
 * this function, No IP-DATA of the selected ciMuxInputCh will be delivered to
 * CIPLUS14-Multiplexers input and then No IP-Data of the through ciMuxInputCh
 * will be delivered to CICAM.  When user stops a CIPLUS14-related-action, this
 * function is called one time. If this function is called, while read and write
 * are periodically called, the uploading buffer will become full within some
 * time.
 *
 * 2 In TS (RF-DTV) mode, The operating principle is like below. Transport-Data
 * comes from Tuner. In TS mode, the Transport-Data is delivered to
 * Multiplexers input. This function stops to pass the Transport-Data to the
 * Multiplexers input. By calling this function, those Transport-Data was cut
 * from the Transport-stream from SOC to CAM.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_STOP_SENDING_DATA;
 * param.size = 0
 * param.value64= 0;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 * soc can detemine the channel with fd.
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_STOP_SENDING_DATA              |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_START_SENDING_DATA
 */
#define CA_EXT_CID_PLUS14_STOP_SENDING_DATA CA_EXT_CID_PLUS14_BASE + 6

/**
 * @brief Selects CICAM-Delivery-Mode or Host-delivery-Mode
 *
 * For IP-Delivery Mode, there are two kinds of Mode. The one is the CICAM-Mode
 * and the other is the Host-Delivery-Mode.
 *
 * In CICAM-Mode, after IP-Data is
 * processed by CICAM, the IP-Data from CICAM is delivered to Soc, In the Soc,
 * the IP-data will be directly delivered to SDECs input like the normal DTV
 * case.
 *
 * In Host-Delivery-Mode, after IP-Data is processed by CICAM, the
 * IP-Data from CICAM is delivered to Soc, In the Soc, the IP-data is delivered
 * to a Memory Buffer not to the SDECs input like CICAM-Mode case. In the
 * memory buffer, the IP-data will be further processed by LGE-mw and then
 * delivered to Gstreamer for displaying
 *
 * This function selects which path will be selected between CICAM-Delivery-Mode and Host-delivery-Mode.
 *
 * @li ``CICAM-Delivery-Mode mode``: When value64 == 0 is selected, the IP-data from CICAM is delivered to
 * SDECs input like the normal DTV case. We call this mode as
 * CICAM-Delivery-Mode mode.
 *
 * @li ``HOST-Delivery-Mode`` When value64 == 1 is selected, the IP-data from CICAM is delivered to
 * a download memory buffer. We call this mode as HOST-Delivery-Mode.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_DOWNLOAD_MODE;
 * param.size = 0
 * param.value64= 0;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 * soc can detemine the channel with fd.
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_DOWNLOAD_MODE                  |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |0:IP-data is delivered to Demux(HW)              |
 *     +            +-------------------------------------------------+
 *     |            |1:the IP-data delivered to a memory buffer(SW)   |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 */
#define CA_EXT_CID_PLUS14_DOWNLOAD_MODE CA_EXT_CID_PLUS14_BASE + 7

/**
 * @brief Enable Reciving data from CI-CAM
 *
 * This function is used both cases of IP-Delivery mode and TS mode. *
 * When called, parameters are ignored and enable data transfer
 *
 * In IP-Delivery mode, The operating principle is like below. IP-Delivery mode
 * has two modes. The fist is the Host-IP-Delivery Mode and the second is the
 * CICAM mode. In Host-IP-Delivery Mode, IP-Data is delivered from CICAM to Soc.
 * In the Soc, the IP-Data need to be firstly saved on a Memory Buffer when the
 * IP-Data firstly arrives on Soc(hereafter, these memories will be called
 * download buffer). This is for balancing the timing-difference and some
 * data-processing. This action sequence is called Downloading. And then, a
 * Data-Processing SW module inside the Soc reads the IP-Data from the download
 * memory buffer so that he can control the read-timing and the amounts of read
 * IP-Data as he wishes regardless of CICAM outputs throughput. This function
 * starts to pass the Transport-Data from the DEMUXs output to the downloading
 * memory buffer.
 *
 * In TS mode, The operating principle is like below. In this mode, after
 * CICAMs data processing, the Transport-Data comes back from CAM to Soc.
 * Inside the Soc, the Transport Data pass through a DEMUX. And then the
 * Transport Data is delivered from the DEMUXs output to the input of SDEC.
 * This function starts to pass the Transport-Data from the DEMUXs output to
 * the downloading memory buffer.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_START_RECEIVING_DATA;
 * param.size = 0
 * param.value64= 0;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 * soc can detemine the channel with fd.
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_START_RECEIVING_DATA           |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA
 */
#define CA_EXT_CID_PLUS14_START_RECEIVING_DATA CA_EXT_CID_PLUS14_BASE + 8

/**
 * @brief Disable Reciving data from CI-CAM
 *
 * This function is used both cases of IP-Delivery mode and TS mode. *
 * When called, parameters are ignored and enable data transfer
 *
 * 1 In IP-Delivery mode, The operating principle is like below. IP-Delivery
 * mode has two modes. The fist is the Host-IP-Delivery Mode and the second is
 * the CICAM mode. In Host-IP-Delivery Mode, IP-Data is delivered from CICAM to
 * Soc. In the Soc, the IP-Data need to be firstly saved on a downloading Memory
 * Buffer when the IP-Data firstly arrives on Soc. This is for balancing the
 * timing-difference and some data-processing. This action sequence is called
 * Downloading. And then, a Data-Processing module inside the Soc reads the
 * IP-Data from the download memory buffer so that he can control the
 * read-timing and the amounts of read IP-Data as he wishes. This function stops
 * the delivery of IP-Data from the CICAM to download memory buffer in soc. If
 * this function is called without stopping of calling
 * read(), the
 * download buffer memory can be full within some time.
 *
 * 2 In TS mode, The operating principle is like below. In this mode, after
 * CICAMs data processing, the Transport-Data comes back from CAM to Soc.
 * Inside the Soc, the Transport Data pass through a DEMUX. And then the
 * Transport Data is delivered from the DEMUXs output to the input of SDEC.
 * This function stops to pass the Transport-Data from the DEMUXs output to the
 * input of the SDEC.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA;
 * param.size = 0
 * param.value64= 0;
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 * soc can detemine the channel with fd.
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA            |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0                                         |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_START_RECEIVING_DATA
 */
#define CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA CA_EXT_CID_PLUS14_BASE + 9

/**
 * @brief Get CI CAM input bitrate
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 24.
 */
#define CA_EXT_CID_PLUS14_CICAM_IN_BITRATE CA_EXT_CID_PLUS14_BASE + 10

/**
 * @brief Get CI CAM output bitrate
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 24.
 */
#define CA_EXT_CID_PLUS14_CICAM_OUT_BITRATE CA_EXT_CID_PLUS14_BASE + 11

/**
 * @brief Bypass input to output directly
 *
 *
 * Bypass the input of cam to the output to verify Read / Write function. This
 * supports the mock up environment. Data written to a specific fd must be
 * readable again. Default is 0, 0 is bypass disable, 1 is bypass enable.
 *
 * CI control id define for CA_EXT_S_CTL
 *
 * @b Pseudocode
 * @code
 * int fd;
 * char path[64];
 * snprintf(path, sizeof(path), "/dev/dvb/adapter0/ca%d", 1);  // ca1
 * fd = open(path, O_RDWR);
 *
 * struct ca_ext_control param;
 *
 * param.id   = CA_EXT_CID_CTS_IO_BYPASS_MODE;
 * param.size = 0
 * param.value64= 1; //Enable
 *
 * rc = ioctl(fd, CA_EXT_S_CTL, &param);
 *
 * soc can detemine the channel with fd.
 * @endcode
 *
 * @rst
 *     +------------+-------------------------------------------------+
 *     | ca_ext_control example                                       |
 *     +============+=================================================+
 *     | id         |CA_EXT_CID_CTS_IO_BYPASS_MODE                    |
 *     +------------+-------------------------------------------------+
 *     | size       |       0                                         |
 *     +------------+-------------------------------------------------+
 *     | value64    |       0: Disable 1: Enable                      |
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
 *
 * @endrst
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 * @see
 * @li CA_EXT_S_CTL
 * @li CA_EXT_CID_PLUS14_START_RECEIVING_DATA
 */
#define CA_EXT_CID_CTS_IO_BYPASS_MODE CA_EXT_CID_PLUS14_BASE + 12

// CA_CI_MODULE
/**
 * @brief  Invalid CA Device status case
 *
 *
 * The CA_GET_SLOT_INFO is an Linux Standard API which informs a CA
 * Device status to the userspace. A new feature is added to this API
 * so that it returns CA_CI_EXT_MODULE_INVALID when the CAM does not
 * response to TV.The CA_CI_EXT_MODULE_INVALID is defined as 128 in
 * the ca_ext.h
 *
 *
 * @return 0 if it success.
 * On error -1 and the errno variable is set appropriately. The generic error
 * codes are described at the Generic Error Codes chapter.
 *
 *
 * @see
 * @li CA_GET_SLOT_INFO
 */
#define CA_EXT_CI_MODULE_INVALID 128

// clang-format on

#ifndef __user
#define __user
#endif

/**
 * @brief Input source type to CAM
 *
 * @rst
 * .. c:type:: ca_src_type
 * @endrst
 *
 * @code
 * enum ca_src_type {
 *   CA_EXT_SRC_TYPE_IN_DEMOD,  // Internal Demod
 *   CA_EXT_SRC_TYPE_EXT_DEMOD, // External demod
 *   CA_EXT_SRC_TYPE_CIP,       // CI Plus 1.4 (CIP ~ CI)
 *   CA_EXT_SRC_TYPE_MEM,       // Data stream via Network
 *   CA_EXT_SRC_TYPE_NULL
 * };
 * @endcode
 */

enum ca_src_type {
    /** SoC internal demod */
    CA_EXT_SRC_TYPE_IN_DEMOD, // Internal Demod
    /** External demod */
    CA_EXT_SRC_TYPE_EXT_DEMOD, // External demod
    /** Ci plus 1.4 input */
    CA_EXT_SRC_TYPE_CIP, // CI Plus 1.4 (CIP ~ CI)
    /** Data stream via Network */
    CA_EXT_SRC_TYPE_MEM, // Data stream via Network
    CA_EXT_SRC_TYPE_NULL
};

/**
 * @brief Data rate from CAM.
 * This will be deprecated.
 *
 * @rst
 * .. c:type:: ca_ext_ciplus_datarate
 * @endrst
 *
 * @code
 * enum ca_ext_ciplus_datarate {
 *   CA_EXT_CIPLUS_DATARATE_72 = 0,
 *   CA_EXT_CIPLUS_DATARATE_96,
 *};
 * @endcode
 */
enum ca_ext_ciplus_datarate {
    /** 72 Mbit/s */
    CA_EXT_CIPLUS_DATARATE_72 = 0,
    /** 96 Mbit/s */
    CA_EXT_CIPLUS_DATARATE_96,
};

/**
 * @brief Data error check mode.
 * This will be deprecated.
 *
 * @rst
 * .. c:type:: ca_ext_error_mode
 * @endrst
 *
 * @code
 * enum ca_ext_error_mode {
 *   CA_EXT_CI_ERROR_CHECK_MODE_FULL   = 0,
 *   CA_EXT_CI_ERROR_CHECK_MODE_SIMPLE = 1,
 *   CA_EXT_CI_ERROR_CHECK_MODE_MAX
 * };
 * @endcode
 *
 */
enum ca_ext_error_mode {
    /** Error is checked at each data processing step. */
    CA_EXT_CI_ERROR_CHECK_MODE_FULL = 0,
    /** Check for data errors in an optimized way to improve performance. */
    CA_EXT_CI_ERROR_CHECK_MODE_SIMPLE = 1,
    CA_EXT_CI_ERROR_CHECK_MODE_MAX
};

/**
 * @brief PCMCIA io speed
 *
 * @rst
 * .. c:type:: ca_ext_pcmcia_speed
 * @endrst
 *
 * @code
 * enum ca_ext_pcmcia_speed {
 *    CA_EXT_PMCICA_SPEED_LOW = 0,
 *    CA_EXT_PMCICA_SPEED_HIGH
 * };
 * @endcode
 */
enum ca_ext_pcmcia_speed {
    /** Pcmcia read,write speed low. */
    CA_EXT_PMCICA_SPEED_LOW = 0,
    /** Pcmcia read,write speed high. */
    CA_EXT_PMCICA_SPEED_HIGH
};

/*enum for hw connection type */
enum ca_ext_port_type { CA_EXT_PORT_TYPE_SERIAL, CA_EXT_PORT_TYPE_PARALLEL };

/**
 * @brief CA Driver Log Level
 *
 * @rst
 * .. c:type:: ca_ext_log_level
 * @endrst
 *
 * @code
 * enum ca_ext_log_level {
 *   CA_EXT_LOG_LEVEL_NONE = 0,
 *   CA_EXT_LOG_LEVEL_ALERT = 1,
 *   CA_EXT_LOG_LEVEL_CRIT = 2,
 *   CA_EXT_LOG_LEVEL_ERROR = 3,
 *   CA_EXT_LOG_LEVEL_WARNING = 4,
 *   CA_EXT_LOG_LEVEL_NOTICE = 5,
 *   CA_EXT_LOG_LEVEL_INFO = 6,
 *   CA_EXT_LOG_LEVEL_DEBUG0 = 7,
 *   CA_EXT_LOG_LEVEL_DEBUG1 = 8,
 *   CA_EXT_LOG_LEVEL_DEBUG2 = 9
 * };
 * @endcode
 *
 */
enum ca_ext_log_level {
    CA_EXT_LOG_LEVEL_NONE = 0,
    CA_EXT_LOG_LEVEL_ALERT = 1,
    CA_EXT_LOG_LEVEL_CRIT = 2,
    CA_EXT_LOG_LEVEL_ERROR = 3,
    CA_EXT_LOG_LEVEL_WARNING = 4,
    CA_EXT_LOG_LEVEL_NOTICE = 5,
    CA_EXT_LOG_LEVEL_INFO = 6,
    CA_EXT_LOG_LEVEL_DEBUG0 = 7,
    CA_EXT_LOG_LEVEL_DEBUG1 = 8,
    CA_EXT_LOG_LEVEL_DEBUG2 = 9
};

/**
 * @brief Struct for input source information
 *
 * @rst
 * .. c:type:: ca_ext_source
 * @endrst
 * @code
 * struct ca_ext_source {
 *     enum ca_src_type input_src_type; // input_src_type - specific src type
 *     __u32 input_port_num;            // Port number of input
 * };
 * @endcode
 */
struct ca_ext_source {
    /** Input source type to CAM */
    enum ca_src_type input_src_type; // input_src_type - specific src type
    /** Device port number */
    __u32 input_port_num; // Port number of input
};

/**
 * @brief Specifies CA Extended ioctl parameters. CI struct for CA_EXT_S_CTL or CA_EXT_G_CTL.
 * @rst
 * .. c:type:: ca_ext_control
 * @endrst
 *
 * @code
 * struct ca_ext_control {
 *   __u32 id;
 *   __u32 size;
 *   union {
 *       __s64 value64;
 *       void __user *ptr;
 *   };
 *  };
 * @endcode
 *
*/
struct ca_ext_control {

    /** CI control id*/
    __u32 id;
    /**
     * If this is 0, value64 is chosen and the data of value64 can be set or get.
     * If this is not 0, ptr is chosen and the data of multiyple bytes can be set or get.
     */
    __u32 size;

    /** Use union struct for memory alignment*/
    union {
        /** This is the int64 data value.*/
        __s64 value64;
        /** This is data address of "size" bytes. */
        void __user *ptr;
    };
};

/**
 * @brief Set parameter to CI
 * set parameter to CI , 60 can be changed.
 *
 * @code
 * #define CA_EXT_S_CTL _IOW('o', 60, struct ca_ext_control)
 * @endcode
 *
 * @see ca_ext_control
 */
#define CA_EXT_S_CTL _IOW('o', 60, struct ca_ext_control)

/**
 * @brief Get parameter from CI
 * get parameter from CI , 61 can be changed.
 * @code
 * #define CA_EXT_G_CTL _IOWR('o', 61, struct ca_ext_control)
 * @endcode
 *
 * @see ca_ext_control
 */
#define CA_EXT_G_CTL _IOWR('o', 61, struct ca_ext_control)

#endif /* _DVBV5_EXT_CA_H_ */
