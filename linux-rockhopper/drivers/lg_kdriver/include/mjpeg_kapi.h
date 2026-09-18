/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  application interface header for mjpeg device
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.04.09
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

#ifndef	_MJPEG_KAPI_H_
#define	_MJPEG_KAPI_H_

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/
//#define A0_WORKAROUND

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/
#define LX_MJPEG_MIN_VSIZE			16
#define LX_MJPEG_MIN_HSIZE			16
#define LX_MJPEG_MAX_VSIZE			(32*1024)	// 32k
#define LX_MJPEG_MAX_HSIZE			(32*1024)	// 32k

#define MIN_VSIZE		LX_MJPEG_MIN_VSIZE
#define MIN_HSIZE		LX_MJPEG_MIN_HSIZE
#define MAX_VSIZE		LX_MJPEG_MAX_VSIZE
#define MAX_HSIZE		LX_MJPEG_MAX_HSIZE

#define LX_MJPEG_MAX_INTR_DATA		12

#define	MJPEG_IOC_MAGIC		'm'

/** general memory buffer
 *
 *
 */
typedef struct
{
  UINT32 addr;  // physical address
	UINT32 length;
}
LX_MJPEG_MEM_BUF_T;

/** general memory buffer
 *
 *
 */
typedef struct
{
	union __aligned(8) {
		void *	virt_addr;				///< address of buffer ( logical )
		UINT32	compat_addr;
		UINT64	sizer;
	};
	UINT32		length __aligned(8);	///< length of buffer
}
LX_MJPEG_VMEM_BUF_T;

/** general memory buffer stream
 *
 */
typedef struct
{
	LX_MJPEG_MEM_BUF_T	mem_buf;		///< memory buffer
	UINT32 curr_offset;	///< current offset from mem_buf.addr
}
LX_MJPEG_MEM_STREAM_T;

/**
@name MJPEG IOCTL List
ioctl list for MJPEG device.

@{
@def MJPEG_IO_RESET
Reset MJPEG module.
When MJPEG device receives above IOCTL, then reset itself.

@def MJPEG_IOR_CHIP_REV_INFO
Reads chip revision information.
Just get chiop revision information. To support automatic changing behavior of device driver or middleware by this ioctl.

@def MJPEG_IOW_WRITE_UINT32
write 32bit value to MJPEG module.
detailed...[minimum two lines of comment required. one line of comment does not generated automatically]

@def MJPEG_IOW_WRITE_STRUCT
control complex parameter to MJPEG module.
control codec_type, speed, and additional parameter.
no need to use "see also", exact struct name shall be linked automatically.

*/
/*------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
------------------------------------------------------------------------------*/
#define	LX_MJPEG_IO_SW_RESET					_IO(MJPEG_IOC_MAGIC,  0 )
#define LX_MJPEG_IOR_GET_BUFFER_INFO		_IOR(MJPEG_IOC_MAGIC, 1, LX_MJPEG_MEM_BUF_T )
#define	LX_MJPEG_IOW_ENCODE_INIT			_IOW(MJPEG_IOC_MAGIC, 2, LX_MJPEG_ENC_INIT_PARAM_T )
#define LX_MJPEG_IOW_ENCODE_START			_IOW(MJPEG_IOC_MAGIC, 3, LX_MJPEG_ENC_START_PARAM_T )
#define LX_MJPEG_IOR_ENCODE_STOP			_IOR(MJPEG_IOC_MAGIC, 4, LX_MJPEG_ENC_STOP_PARAM_T )
#define	LX_MJPEG_IOW_DECODE_INIT			_IOW(MJPEG_IOC_MAGIC, 5, LX_MJPEG_DEC_INIT_PARAM_T )
#define LX_MJPEG_IOW_DECODE_START			_IOW(MJPEG_IOC_MAGIC, 6, LX_MJPEG_DEC_START_PARAM_T )
#define LX_MJPEG_IOR_DECODE_STOP			_IOR(MJPEG_IOC_MAGIC, 7, LX_MJPEG_DEC_STOP_PARAM_T )
#define LX_MJPEG_IOR_DECODE_SEQUENCE_INIT	_IOWR(MJPEG_IOC_MAGIC,8, LX_MJPEG_DEC_SEQ_PARAM_T )
#define LX_MJPEG_IOW_DECODE_PARTIAL			_IO(MJPEG_IOC_MAGIC, 9 )

#define LX_MJPEG_IOR_GET_CFG					_IOR(MJPEG_IOC_MAGIC,10, LX_MJPEG_CFG_T )
#define LX_MJPEG_IOW_DECODE_CONTINUE		_IOW(MJPEG_IOC_MAGIC, 11, LX_MJPEG_DEC_CONTINUE_PARAM_T )
#define LX_MJPEG_IOW_ENCODE_CONTINUE		_IOW(MJPEG_IOC_MAGIC, 12, LX_MJPEG_ENC_START_PARAM_T )

#define LX_MJPEG_IOW_GENERAL_CMD			_IOW(MJPEG_IOC_MAGIC, 13, LX_MJPEG_GENERAL_CMD_PARAM_T )

#define MJPEG_IOC_MAXNR				13
/** @} */

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define MROUND( number, multiple ) ((((number) / (multiple)) + (((number) % (multiple)) ? 1 : 0) ) * (multiple) )

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
/**
 * MJPEG header information.
 * useful when .
 * @see
 */
typedef struct {
	UINT8 ui8SamplingPrecision;
	UINT16 ui16Height;
	UINT16 ui16Width;
	UINT16 ui16SOF;
	UINT8  ui8NumberOfComponents;
	struct{
		UINT8 ui8ComponentID;
		UINT8 ui8HSampleFreq;
		UINT8 ui8VSampleFreq;
		UINT8 ui8QTableID;
	} stComponents[3];
} LX_MJPEG_FRAME_HEADER_T;

typedef struct {
	UINT8 ui8NumberOfComponents;
	struct{
		UINT8 ui8ComponentID;
		UINT8 ui8DC_HuffmanTableID;
		UINT8 ui8AC_HuffmanTableID;
	} stComponents[3];
	UINT8 ui8Ss;
	UINT8 ui8Se;
	UINT8 ui8Ah;
	UINT8 ui8Al;
} LX_MJPEG_SCAN_HEADER_T;

typedef struct {
	UINT8 ui8Pq;
	UINT8 ui8Tq;
	UINT8 ui8Elements[64];
} LX_MJPEG_QUANTIZATION_TABLE_T;

typedef struct {
	UINT8 ui8Tc;
	UINT8 ui8Th;
	UINT8 ui8CodeLengths[16];
	UINT8 ui8CodeValues[162];
} LX_MJPEG_HUFFMAN_TABLE_T;

typedef struct {
	LX_MJPEG_FRAME_HEADER_T			stFrameHeader;
	LX_MJPEG_SCAN_HEADER_T			stScanHeader;
	UINT16							ui16ResetInterval;
	LX_MJPEG_QUANTIZATION_TABLE_T	stQuantiztionTables[4];
	LX_MJPEG_HUFFMAN_TABLE_T		stHuffmanTables[4];
} LX_MJPEG_HEADER_T;


/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see
 */
typedef enum {
	LX_MJPEG_FORMAT_420 		= 0,
	LX_MJPEG_FORMAT_422 		= 1,
	LX_MJPEG_FORMAT_224 		= 2,
	LX_MJPEG_FORMAT_444 		= 3,
	LX_MJPEG_FORMAT_400 		= 4,

	LX_MJPEG_FORMAT_MIN 		= LX_MJPEG_FORMAT_420,
	LX_MJPEG_FORMAT_MAX 		= LX_MJPEG_FORMAT_420
} LX_MJPEG_FORMAT_T;


typedef struct
{
	int width;										   /* image width */
	int height;										   /* image height */

	LX_MJPEG_FORMAT_T img_fmt;						   /* 4:2:0, 4:2:2, 4:4:4 ..
													    * this valus can be exact
													    * when decoded succussfully */

	int hdr_size;									   /* header block size in jpeg file */
	UINT8 comp_num;									   /* number of component Y? Cb? Cr? */
	UINT8 sub_sample_h;								   /* horizotal subsample value */
	UINT8 sub_sample_v;								   /* vertical subsample value */
} LX_MJPEG_HEADER_INFO_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see
 */
typedef struct {
	UINT32		ui32AddressY;
	UINT32		ui32AddressCb;
	UINT32		ui32AddressCr;
	UINT32		ui32StrideY;
	UINT32		ui32StrideC;
	UINT32		ui32SizeY;
	UINT32		ui32SizeCb;
	UINT32		ui32SizeCr;

	BOOLEAN		bUVInterleaved;
} LX_MJPEG_IMAGE_BUF_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see
 */
typedef struct {
	LX_MJPEG_FORMAT_T			eFormat;
	UINT16						ui16Height;
	UINT16						ui16Width;
} LX_MJPEG_IMAGE_INFO_T;

/**
 * MJPEG operation mode enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_OPERATION_NORMAL	= 0,
	LX_MJPEG_OPERATION_PARTIAL	= 1,
} LX_MJPEG_OPERATION_T;

/**
 * MJPEG rotation degree enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_ROTATE_0			= 0,
	LX_MJPEG_ROTATE_90			= 1,
	LX_MJPEG_ROTATE_180			= 2,
	LX_MJPEG_ROTATE_270			= 3
} LX_MJPEG_ROTATION_T;

/**
 * MJPEG mirroring enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_MIRROR_NONE		= 0x00,
	LX_MJPEG_MIRROR_HORIZONTAL	= 0x01,
	LX_MJPEG_MIRROR_VERTICAL	= 0x02
} LX_MJPEG_MIRRORING_T;

/**
 * MJPEG scale enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_SCALE_NONE			= 0,
	LX_MJPEG_SCALE_1_2			= 1,
	LX_MJPEG_SCALE_1_4			= 2,
	LX_MJPEG_SCALE_1_8			= 3
} LX_MJPEG_SCALING_T;

/**
 * MJPEG encoding quality enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_QUALITY_LOW		= 0,
	LX_MJPEG_QUALITY_MID_LOW	= 1,
	LX_MJPEG_QUALITY_MID_HIGH	= 2,
	LX_MJPEG_QUALITY_HIGH		= 3,
	LX_MJPEG_QUALITY_USE_VALUE	= 4,	// using quality value
} LX_MJPEG_QUALITY_T;

/**
 * MJPEG decoding capability enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_DECODE_CAPS_NONE			= 0,
	LX_MJPEG_DECODE_CAPS_CNM			= 1,
	LX_MJPEG_DECODE_CAPS_LG				= 2,
} LX_MJPEG_DECODE_CAPS_T;

/**
 * MJPEG encoding capability enumeration.
 *
 * @see
 */
typedef enum {
	LX_MJPEG_ENCODE_CAPS_HW		= 0,
	LX_MJPEG_ENCODE_CAPS_SW		= 1,
} LX_MJPEG_ENCODE_CAPS_T;

/**
 * MJPEG encoding capability enumeration.
 *
 * @see
 */
typedef enum
{
	LX_MJPEG_STATUS_DONE		= 0x1 << 0,			// 0x0001 : 1
	LX_MJPEG_STATUS_ERROR	= 0x1 << 1,			// 0x0002 : 2
	LX_MJPEG_STATUS_BBC		= 0x1 << 2,			// 0x0004 : 4
	LX_MJPEG_STATUS_OVER		= 0x1 << 3,			// 0x0008 : 8
	LX_MJPEG_STATUS_BUFFER0	= 0x1 << 4, 		// 0x0010 : 16
	LX_MJPEG_STATUS_BUFFER1	= 0x1 << 5,			// 0x0020 : 32

} LX_MJPEG_STATUS_T;

/**
 * MJPEG General Command enum.
 *
 * @see LX_MJPEG_GENERAL_CMD_PARAM_T
 */
typedef enum
{
	LX_MJPEG_CMD_SW_RESET,
	LX_MJPEG_CMD_USE_QUEUE,
	LX_MJPEG_CMD_DECODE_INIT,
	LX_MJPEG_CMD_DECODE_START,
	LX_MJPEG_CMD_DECODE_CONTINUE,
	LX_MJPEG_CMD_DECODE_STOP,
	LX_MJPEG_CMD_DECODE_CLEAR_DPB,
	LX_MJPEG_CMD_DECODE_GET_CURRENT_COORD,
	LX_MJPEG_CMD_STOP_READ,
	LX_MJPEG_CMD_CLEAR_INTR,
	LX_MJPEG_CMD_DECODE_COPY_CACHE_DATA,

} LX_MJPEG_COMMAND_T;

typedef enum
{
	MJPEG_SAMPLE_NONE = 0x0,
	MJPEG_SAMPLE_420 = 0xA,
	MJPEG_SAMPLE_H422 = 0x9,
	MJPEG_SAMPLE_V422 = 0x6,
	MJPEG_SAMPLE_444 = 0x5,
	MJPEG_SAMPLE_400 = 0x1,
} SAMPLE_FACTOR_T;

enum {
	SOI_MARKER		= 0xFFD8,			// Start of image
	EOI_MARKER		= 0xFFD9,			// End of image

	JFIF_CODE		= 0xFFE0,			// Application
	EXIF_CODE		= 0xFFE1,

	DRI_MARKER		= 0xFFDD,			// Define restart interval
	RST_MARKER		= 0x000D,			// 0xD0 ~0xD7

	DQT_MARKER		= 0xFFDB,			// Define quantization table(s)
	DHT_MARKER		= 0xFFC4,			// Define Huffman table(s)

	SOF_MARKER		= 0xFFC0,			// Start of frame : Baseline DCT
	SOF_MARKER_PDCT_HD	= 0xFFC2,			// Start of frame : Progressive DCT
	SOS_MARKER		= 0xFFDA			// Start of scan
};

/**
 * MJPEG option parameter.
 *
 * @see
 */
typedef struct {
	LX_MJPEG_ROTATION_T		eRotation;
	LX_MJPEG_MIRRORING_T	eMirroring;
	LX_MJPEG_SCALING_T		eScaleHorizontal;	// Deocder only
	LX_MJPEG_SCALING_T		eScaleVertical;		// Decoder only
	LX_MJPEG_OPERATION_T	eOperation;			// Decoder only
	BOOLEAN					bQuality;			// Encoder only
	UINT32					nQuality;			// Encoder only 0-100 (0:low quality, 100:hight quality)
} LX_MJPEG_OPTION_T;

#if 0
/**
 * MJPEG option parameter.
 *
 * @see
 */
typedef struct {
	LX_MJPEG_ROTATION_T		eRotation;
	LX_MJPEG_MIRRORING_T	eMirroring;
	LX_MJPEG_SCALING_T		eScaleHorizontal;
	LX_MJPEG_SCALING_T		eScaleVertical;
	LX_MJPEG_OPERATION_T	eOperation;
} LX_MJPEG_DECODE_OPTION_T;

/**
 * MJPEG option parameter.
 *
 * @see
 */
typedef struct {
	LX_MJPEG_SCALING_T		eScaleHorizontal;
	LX_MJPEG_SCALING_T		eScaleVertical;
	LX_MJPEG_QUALITY_T		eQuality;			// 0-4	(4: use nQuality, 3:high 0:low)
	UINT32					nQuality;			// 0-100 (0:low quality, 100:hight quality)
} LX_MJPEG_ENCODE_OPTION_T;
#endif

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOW_ENCODE_INIT
 */
typedef struct
{
	LX_MJPEG_IMAGE_INFO_T		stImageInfo;		/** information of image */
	LX_MJPEG_IMAGE_BUF_T		stImageBuf;			/** information of data buffer of image */
	LX_MJPEG_OPTION_T			stOption;
} LX_MJPEG_ENC_INIT_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_ENCODE_START
 */
typedef struct
{
	LX_MJPEG_MEM_BUF_T		stDataBuffer;				/** information of data buffer */
} LX_MJPEG_ENC_START_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_ENCODE_STATUS
 */
typedef struct
{
	LX_MJPEG_HEADER_T	stHeader;					/** jpeg header information */
	UINT32				ui32Length;					/** length written in kernel driver */
} LX_MJPEG_ENC_STOP_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOW_DECODE_INIT
 */
typedef struct
{
	LX_MJPEG_HEADER_T			stHeader;			/** jpeg header information */
	LX_MJPEG_IMAGE_BUF_T		stImageBuf;			/** output buffer to hold decoded data */
	LX_MJPEG_IMAGE_BUF_T		stImageVirtBuf;		/** Virtual Address of output buffer to hold decoded data */
	LX_MJPEG_OPTION_T			stOption;
} LX_MJPEG_DEC_INIT_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_START
 */
typedef struct
{
	LX_MJPEG_MEM_BUF_T	stDataBuffer;					/** information of data buffer */
	UINT32			ui32DataLength;					/** length of data */
	BOOLEAN			bEndOfStream;					/** end of stream */
	BOOLEAN			bSkipCheck;
} LX_MJPEG_DEC_START_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_START
 */
typedef struct
{
	LX_MJPEG_MEM_BUF_T	stDataBuffer;					/** information of data buffer */
	UINT32			ui32DataLength;				/** length of data */
	BOOLEAN			bEndOfStream;					/** end of stream */
	BOOLEAN			bSkipCheck;
} LX_MJPEG_DEC_CONTINUE_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_START
 */
typedef struct
{
	LX_MJPEG_STATUS_T	eMjpegStatus;				/** information of data buffer */
	UINT32				ui32Data;					/** length of data */
} LX_MJPEG_DEC_GET_STATUS_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_STATUS
 */
typedef struct
{
	LX_MJPEG_IMAGE_INFO_T	stImageInfo;			/** information of decoded data */
} LX_MJPEG_DEC_STOP_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_START
 */
typedef struct
{
	LX_MJPEG_VMEM_BUF_T		stDataBuffer;				/** information of data buffer */

	LX_MJPEG_HEADER_T	stHeader;					/** jpeg header information */
	UINT32				ui32Length;					/** decoded header length in kernel driver */
} LX_MJPEG_DEC_SEQ_PARAM_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see MJPEG_IOR_DECODE_STATUS
 */
typedef struct
{
	UINT16 x;
	UINT16 y;
} LX_MJPEG_DEC_GET_CUR_COORD_T;

/**
 * MJPEG ioctl parameter.
 * useful when complex parameter should be passed to MJPEG kernel driver.
 * @see LX_MJPEG_IOW_GENERAL_CMD
 */
typedef struct
{
	LX_MJPEG_COMMAND_T command;
	union
	{
		BOOLEAN							use_queue;
		LX_MJPEG_DEC_INIT_PARAM_T		dec_init;
		LX_MJPEG_DEC_START_PARAM_T 		dec_start;
		LX_MJPEG_DEC_CONTINUE_PARAM_T	dec_continue;
		LX_MJPEG_DEC_STOP_PARAM_T		dec_stop;
		LX_MJPEG_DEC_GET_CUR_COORD_T	dec_coord;
	} param;
} LX_MJPEG_GENERAL_CMD_PARAM_T;

/** MJPEG cfg
 *
 *
 */
typedef struct
{
	UINT16			max_decode_width;			/** maximum decodable width (default: 8k) */
	UINT16			max_decode_height;			/** maximum decodable width (default: 8k) */

	UINT32			decode_caps;
	UINT32			encode_caps;

	UINT32			resvd[6];
} LX_MJPEG_CFG_T;

typedef enum
{
	LX_MJPEG_RESULT_DONE		= 0x1 << 1,			// 0x0002 : 2
	LX_MJPEG_RESULT_ERROR	= 0x1 << 2,			// 0x0004 : 4
	LX_MJPEG_RESULT_BBC		= 0x1 << 3,			// 0x0008 : 8
	LX_MJPEG_RESULT_OVER		= 0x1 << 4,			// 0x0010 : 16
	LX_MJPEG_RESULT_BUFFER0	= 0x1 << 5, 		// 0x0020 : 32
	LX_MJPEG_RESULT_BUFFER1	= 0x1 << 6,
	LX_MJPEG_RESULT_BUFFER2	= 0x1 << 7,
	LX_MJPEG_RESULT_BUFFER3	= 0x1 << 8,
	LX_MJPEG_RESULT_STREAM_ERROR = 0x1 << 9,
	LX_MJPEG_RESULT_TIMEOUT = 0x1 << 10,
	LX_MJPEG_RESULT_BUFFERS	= LX_MJPEG_RESULT_BUFFER0 | LX_MJPEG_RESULT_BUFFER1 | LX_MJPEG_RESULT_BUFFER2 | LX_MJPEG_RESULT_BUFFER3,

	LX_MJPEG_RESULT_BUFFER0_AND_BBC = 0x1 << 12,
	LX_MJPEG_RESULT_STOP 	= 0x1 << 20,
} LX_MJPEG_RESULT_T;

typedef enum
{
	MJPEG_EVENT_DONE	= 0x1 << 1,				// 0x0002 : 2
	MJPEG_EVENT_ERROR	= 0x1 << 2,				// 0x0004 : 4
	MJPEG_EVENT_BBC 	= 0x1 << 3,				// 0x0008 : 8
	MJPEG_EVENT_OVER	= 0x1 << 4,				// 0x0010 : 16
	MJPEG_EVENT_BUFFER0 = 0x1 << 5,			// 0x0020 : 32
	MJPEG_EVENT_BUFFER1 = 0x1 << 6,
	MJPEG_EVENT_BUFFER2 = 0x1 << 7,
	MJPEG_EVENT_BUFFER3 = 0x1 << 8,
	MJPEG_EVENT_STREAM_ERROR = 0x1 << 9,
	MJPEG_EVENT_TIMEOUT = 0x1 << 10,
	MJPEG_EVENT_DC_ERROR = 0x1 << 11,

	MJPEG_EVENT_BUFFER	= MJPEG_EVENT_BUFFER0 | MJPEG_EVENT_BUFFER1 | MJPEG_EVENT_BUFFER2 | MJPEG_EVENT_BUFFER3,
	MJPEG_EVENT_DECODE	= MJPEG_EVENT_DONE | MJPEG_EVENT_ERROR | MJPEG_EVENT_ERROR | MJPEG_EVENT_BUFFER,
} LX_MJPEG_EVENT_T;

/*------------------------------------------------------------------------------
	Extern Function Prototype Declaration
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Extern Variables
------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _MJPEG_KAPI_H_ */

/** @} */
