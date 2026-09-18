/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
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
 *  application interface header for npu device
 *
 *  author        Hanshic Shin ( hanshic.shin@lge.com )
 *                Dongmin Kwon ( dongmin.kwon@lge.com )
 *  version       0.1 (draft)
 *  date          2022/04/21
 *
 *  @addtogroup npu
 */

#ifndef __NPU_API_H__
#define __NPU_API_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define NPU_IOC_MAGIC 'n'

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
    TENSOR_TYPE_NONE,
    TENSOR_TYPE_INT8,
    TENSOR_TYPE_INT16,
    TENSOR_TYPE_INT32,
    TENSOR_TYPE_INT64,
    TENSOR_TYPE_FLOAT16,
    TENSOR_TYPE_FLOAT32,
    TENSOR_TYPE_UINT8,
    TENSOR_TYPE_STRING,
    TENSOR_TYPE_BOOL,
    TENSOR_TYPE_COMPLEX64,
    TENSOR_TYPE_FLOAT8,
    TENSOR_TYPE_BFLOAT16,
} TENSOR_TYPE_T;

typedef enum {
    MEMORY_TYPE_NONE,                    /* not allocated by npu libraries, provided by caller */
    MEMORY_TYPE_MALLOC,                  /* memory using malloc in npu libraries */
    MEMORY_TYPE_DEVICE,                  /* mmap a device memory and provide the address to the caller */
    MEMORY_TYPE_FD,                      /* mmap from fd provided by caller */
    MEMORY_TYPE_PHYSICAL                 /* physical memory provided by caller */
} MEMORY_TYPE_T;

typedef struct {
    MEMORY_TYPE_T memory_type;
    int size;
    union {
        char* data;
        int fd;
        unsigned long physical_address;
        unsigned int compat_data;
        unsigned long long sizer_data;
    };
} TENSOR_T;

typedef struct {
    int            job_id;
    union {
        TENSOR_T* tensor;
        unsigned int compat_data;
        unsigned long long sizer_data;
    };
    int number_of_tensor;
} JOB_TENSORS_T;

/* tensor shape */
typedef struct {
    TENSOR_TYPE_T type;
    int dim_size; /* dimension size */
    union {
        int* dim; /* dimension */
        unsigned int compat_dim;
        unsigned long long sizer_dim;
    };
} TENSOR_SHAPE_T;

typedef struct {
    int number_of_shape;
    union {
        TENSOR_SHAPE_T* tensor_shape;
        unsigned int compat_shape;
        unsigned long long sizer_shape;
    };
} TENSOR_INFO_T;

typedef enum {
    NPU_BINARY_TYPE_PROGRAM,
    NPU_BINARY_TYPE_PARAMETERS,
} NPU_BINARY_TYPE_T;

typedef struct {
    NPU_BINARY_TYPE_T type;
    int size;
    union {
        char* data;
        unsigned int compat_data;
        unsigned long long sizer_data;
    };
} NPU_BINARY_T;

typedef enum {
    NPU_EXEC_MEMORY_TYPE_PROGRAM,
    NPU_EXEC_MEMORY_TYPE_PARAMETERS,
    NPU_EXEC_MEMORY_TYPE_FEATURE_BUFFER,
} NPU_EXEC_MEMORY_TYPE_T;

typedef struct {
    NPU_EXEC_MEMORY_TYPE_T  type;
    unsigned long long      physical_address;
    int size;
} NPU_EXEC_MEMORY_T;

typedef struct {
    int npu;
    int kmd;
} LATENCY_PROFILE_T;

typedef struct {
    int                 job_id;
    LATENCY_PROFILE_T   latency;
} JOB_T;

typedef struct {
    unsigned int address;
    unsigned int value;
} REGISTER_MAP_T;

typedef enum {
    STRIDE_TYPE_PROGRAM,
    STRIDE_TYPE_PARAMETER,
    STRIDE_TYPE_FEATURE,
    STRIDE_TYPE_INPUT,
    STRIDE_TYPE_OUTPUT
} STRIDE_TYPE_T;

typedef struct {
    STRIDE_TYPE_T    type;
    unsigned short value;
} STRIDE_T;

typedef struct {
    /* init registers */
    int number_of_registers;
    union {
        REGISTER_MAP_T* registers;
        unsigned int compat_registers;
        unsigned long long sizer_registers;
    };
    /* buffer strides */
    int number_of_strides;
    union {
        STRIDE_T* strides;
        unsigned int compat_strides;
        unsigned long long sizer_strides;
    };
    int number_of_input_offsets;
    union {
        unsigned int* input_offsets;
        unsigned int compat_input_offsets;
        unsigned long long sizer_input_offsets;
    };
    int number_of_output_offsets;
    union {
        unsigned int* output_offsets;
        unsigned int compat_output_offsets;
        unsigned long long sizer_output_offsets;
    };

} DNE_PRIVATE_T;

typedef struct {
    /* init registers */
    int number_of_registers;
    union {
        REGISTER_MAP_T* registers;
        unsigned int compat_registers;
        unsigned long long sizer_registers;
    };
    /* buffer strides */
    int number_of_strides;
    union {
        STRIDE_T* strides;
        unsigned int compat_strides;
        unsigned long long sizer_strides;
    };
    int number_of_input_offsets;
    union {
        unsigned int* input_offsets;
        unsigned int compat_input_offsets;
        unsigned long long sizer_input_offsets;
    };
    int number_of_output_offsets;
    union {
        unsigned int* output_offsets;
        unsigned int compat_output_offsets;
        unsigned long long sizer_output_offsets;
    };

} LNX_PRIVATE_T;

typedef enum {
    NPU_PRIVATE_NONE,
    NPU_PRIVATE_LNE,
    NPU_PRIVATE_DNE,
    NPU_PRIVATE_LNX,
    NPU_PRIVATE_MIN = NPU_PRIVATE_NONE,
    NPU_PRIVATE_MAX = NPU_PRIVATE_LNX,
} NPU_PRIVATE_T;

typedef enum {
    NPU_USER_PROCESS_NONE,
    NPU_USER_PROCESS_AIPQ,
    NPU_USER_PROCESS_NNHAL,
    NPU_USER_PROCESS_DELEGATE,                          // offline-nnhal
    NPU_USER_PROCESS_MIN = NPU_USER_PROCESS_NONE,
    NPU_USER_PROCESS_MAX = NPU_USER_PROCESS_DELEGATE,
} NPU_USER_PROCESS_T;

typedef struct {
    NPU_PRIVATE_T type;
    int         size;
    union {
        char* data;
        void* dne_private;
        void* lne_private;
        void* lnx_private;
        unsigned int compat_data;
        unsigned long long sizer_data;
    };
} PRIVATE_DATA_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
#define NPU_IOCTL_RESET                   _IO(NPU_IOC_MAGIC,  0)
#define NPU_IOCTL_LOAD_BINARY             _IOW(NPU_IOC_MAGIC, 1, NPU_BINARY_T)
#define NPU_IOCTL_SET_INPUT_TENSOR_INFO   _IOW(NPU_IOC_MAGIC, 2, TENSOR_INFO_T)         /* NPU HW tensor info */
#define NPU_IOCTL_SET_OUTPUT_TENSOR_INFO  _IOW(NPU_IOC_MAGIC, 3, TENSOR_INFO_T)         /* NPU HW tensor info */
#define NPU_IOCTL_SET_FEATURE_BUFFER_SIZE _IOW(NPU_IOC_MAGIC, 4, int)
#define NPU_IOCTL_SET_PRIVATE_DATA        _IOW(NPU_IOC_MAGIC, 5, PRIVATE_DATA_T)
#define NPU_IOCTL_REQUEST_JOB             _IOW(NPU_IOC_MAGIC, 6, JOB_T)
#define NPU_IOCTL_CANCEL_JOB              _IOW(NPU_IOC_MAGIC, 7, JOB_T)
#define NPU_IOCTL_GET_JOB_RESULT          _IOR(NPU_IOC_MAGIC, 8, JOB_T)
#define NPU_IOCTL_CANCEL_ALL_JOBS         _IO(NPU_IOC_MAGIC,  9)
#define NPU_IOCTL_SET_PERIOD              _IOW(NPU_IOC_MAGIC, 10, int)
#define NPU_IOCTL_SET_JOB_INPUT_TENSORS   _IOW(NPU_IOC_MAGIC, 11, JOB_TENSORS_T)
#define NPU_IOCTL_SET_JOB_OUTPUT_TENSORS  _IOW(NPU_IOC_MAGIC, 12, JOB_TENSORS_T)
#define NPU_IOCTL_SET_AFFINITY            _IOW(NPU_IOC_MAGIC, 13, int)
#define NPU_IOCTL_SET_USER_PROCESS_TYPE   _IOW(NPU_IOC_MAGIC, 14, NPU_USER_PROCESS_T)
#define NPU_IOCTL_SET_EXEC_MEMORY         _IOW(NPU_IOC_MAGIC, 15, NPU_EXEC_MEMORY_T)
#define NPU_IOCTL_ENABLE_PROTECTED_MODE   _IOW(NPU_IOC_MAGIC, 16, bool)
#define NPU_IOCTL_MAX_NR                  (16)

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __NPU_KADPI_H__

/** @} */
