/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  header file for linux kernel driver
 *
 *  author		
 *  version		1.0
 *  date		2023.01.14
 *  note		Additional information.
 *
 */

#ifndef _REE_KDRV_H_
#define _REE_KDRV_H_

#include "ree_kconfig.h"
#include "smc_cmd_defines.h"

/*global platform return value*/
#define TEE_SUCCESS                       0x00000000  /* the operation was successful */
#define TEE_ERROR_CORRUPT_OBJECT          0xF0100001  /* the obj is corrupt. The object handle is closed */
#define TEE_ERROR_CORRUPT_OBJECT_2        0xF0100002
#define TEE_ERROR_STORAGE_NOT_AVAILABLE   0xF0100003  /* obj is stored in a storage area which is inaccessible */
#define TEE_ERROR_STORAGE_NOT_AVAILABLE_2 0xF0100004
#define TEE_ERROR_GENERIC                 0xFFFF0000  /* non-specific cause */
#define TEE_ERROR_ACCESS_DENIED           0xFFFF0001  /* access privileges are not sufficient */
#define TEE_ERROR_CANCEL                  0xFFFF0002  /* the operation was cancelled */
#define TEE_ERROR_ACCESS_CONFLICT         0xFFFF0003  /* concurrent accesses caused conflict */
#define TEE_ERROR_EXCESS_DATA             0xFFFF0004  /* too much data for the requested operation was passed */
#define TEE_ERROR_BAD_FORMAT              0xFFFF0005  /* input data was of invalid format */
#define TEE_ERROR_BAD_PARAMETERS          0xFFFF0006  /* input parameters were invalid */
#define TEE_ERROR_BAD_STATE               0xFFFF0007  /* operation is not valid in the current state */
#define TEE_ERROR_ITEM_NOT_FOUND          0xFFFF0008  /* the requested data item is not found */
#define TEE_ERROR_NOT_IMPLEMENTED         0xFFFF0009  /* the requested op should exist but is not yet implemented */
#define TEE_ERROR_NOT_SUPPORTED           0xFFFF000A  /* the requested op is valid but is not supported in this Impl */
#define TEE_ERROR_NO_DATA                 0xFFFF000B  /* expected data was missing */
#define TEE_ERROR_OUT_OF_MEMORY           0xFFFF000C  /* system ran out of resources */
#define TEE_ERROR_BUSY                    0xFFFF000D  /* the system is busy working on something else */
#define TEE_ERROR_COMMUNICATION           0xFFFF000E  /* communication with a remote party failed */
#define TEE_ERROR_SECURITY                0xFFFF000F  /* a security fault was detected */
#define TEE_ERROR_SHORT_BUFFER            0xFFFF0010  /* the supplied buffer is too short for the generated output */
#define TEE_ERROR_EXTERNAL_CANCEL         0xFFFF0011  /* operation has been cancelled by an external event */
#define TEE_ERROR_OVERFLOW                0xFFFF300F  /* data position indicator would be greater than TEE_DATA_MAX_POSITION */
#define TEE_ERROR_TARGET_DEAD             0xFFFF3024  /* the destination TA has panicked during the operation */
#define TEE_ERROR_STORAGE_NO_SPACE        0xFFFF3041  /* insufficient storage space is available */
#define TEE_ERROR_MAC_INVALID             0xFFFF3071  /* the computed MAC doesn't correspond to the value passed in the param mac */
#define TEE_ERROR_SIGNATURE_INVALID       0xFFFF3072  /* the signature is invalid */
#define TEE_ERROR_TIME_NOT_SET            0xFFFF5000
#define TEE_ERROR_TIME_NEEDS_RESET        0xFFFF5001

/*
 * @flag_mmap_cached:
 *     Alternative of a legacy _gSeInfo.bCachedMap.
 *     To configure mmap flags per a file without relating of OS_LockMutex().
 * @minor_num:
 *     ToDo, (reserved) only written a minor number at opening device.
 */
struct ree_kdrv_file_priv_data {
	bool flag_mmap_cached;
	int minor_num;
};

int ree_ruta_kdrv_init(void);

int ruta_kdrv_get_rmt_rwsm(unsigned long arg);
int ruta_kdrv_recv(unsigned long arg);
int ruta_kdrv_send(unsigned long arg);

#endif /* _REE_KDRV_H_ */
