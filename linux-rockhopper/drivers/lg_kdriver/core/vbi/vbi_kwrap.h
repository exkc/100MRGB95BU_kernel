 /******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file afe_kadp.h
 *
 *  application interface header for afe device
 *
 *  @author		wonsik.do (wonsik.do@lge.com)
 *  @version		1.0
 *  @date		2010-01-03
 *
 *  @addtogroup lg1150_afe
 *	@{
 */

#ifndef	_VBI_KWRAP_H_
#define	_VBI_KWRAP_H_

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include "vbi_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef enum
{
    VBI_DEBUG_PRINT_TTX = 0,            ///< print enable for TTX operations
    VBI_DEBUG_PRINT_CC,             ///< print enable for CC operations
    VBI_DEBUG_PRINT_WSS,            ///< print enable for WSS operations
    VBI_DEBUG_PRINT_VPS,            ///< print enable for VPS operations
	VBI_DEBUG_PRINT_CGMS,			///< print enable for CGMS operations
    VBI_DEBUG_PRINT_MAXNUM          ///< max number of enurmeration
} VBI_KWRAP_DEBUG_PRINT_MODE_T;

typedef enum
{
    VBI_DEBUG_MODE_CATCH_FROM_FILE, ///< mode for loading data from file, not HW slicer
    VBI_DEBUG_MODE_DUMP_TO_FILE,    ///< mode for dumping data to file
    VBI_DEBUG_MODE_ENABLE_KPRINT,   ///< mode for enabling kprint at VBI kernel driver
    VBI_DEBUG_MODE_FIX_CC_PARITY,	///< mode for enabling automatic CC parity fixer
	VBI_DEBUG_MODE_TARA_UNIT_TEST,	///< Send up unit test data to TARA MW for TTX
	VBI_DEBUG_MODE_DATA_PROFilter,   /// trigger data proFilter
	VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX,///< enable one-bit-error-correction on hamming bytes
	//VBI_DEBUG_MODE_ENABLE_AUTOMATIC_LPF, ///< mode for enabling adaptive-line-slicer/mem
    VBI_DEBUG_MODE_MAXNUM           ///< max number of enurmeration
} VBI_KWRAP_DEBUG_MODE_T;

typedef enum
{
    VBI_FILE_POINTER_NONE = 0,
    VBI_FILE_POINTER_FAILED,
    VBI_FILE_POINTER_ERROR,
    VBI_FILE_POINTER_USB1,
	VBI_FILE_POINTER_USB1_9,
    VBI_FILE_POINTER_USB2,
    VBI_FILE_POINTER_USB3,
    VBI_FILE_POINTER_NFS,
    VBI_FILE_POINTER_MAXNUM
} VBI_KWRAP_FILE_POINTER_STATUS_T;

typedef struct
{
	UINT32		error_count;
	UINT32		full_count;
	UINT32		max_count_value;
	BOOLEAN		cc_dont_count_80;
} VBI_KWRAP_DEBUG_ERROR_PROFILE_T;

typedef struct
{
    BOOLEAN     modeOnOff[VBI_DEBUG_MODE_MAXNUM];
    BOOLEAN     printMask[VBI_DEBUG_PRINT_MAXNUM];
    VBI_KWRAP_FILE_POINTER_STATUS_T    out_file_status;
    VBI_KWRAP_FILE_POINTER_STATUS_T    in_file_status;
//    FILE    *outfile;
//    FILE    *infile;
	VBI_KWRAP_DEBUG_ERROR_PROFILE_T	dataProfile;
} VBI_KWRAP_DEBUGGER_T;
/*------------------------------------------------------------------------------
	Extern Function Prototype Declaration
------------------------------------------------------------------------------*/
int vbi_kwrap_ttx_initializemodule(void);
int vbi_kwrap_ttx_enable(void);
int vbi_kwrap_ttx_close(void);
int vbi_kwrap_ttx_resetbuffer(void);
int vbi_kwrap_ttx_reset(void);
int vbi_kwrap_ttx_dbg_getdatacount(UINT8 bReset, unsigned int *data);
int vbi_kwrap_ttx_reg_init(void);
int vbi_kwrap_ttx_reset_wss(void);
int vbi_kwrap_ttx_reset_vps(void);
int vbi_kwrap_ttx_get_vps_packetstask(UINT8 **vps_packet);
int vbi_kwrap_checkvline625(void);
int vbi_kwrap_init_copyprotection_info(void);
int vbi_kwrap_copyprotection_dataflusher_task(void);
LX_VBI_CP_TYPE_T vbi_kwrap_get_copyprotection_info(UINT32 *cgms_packet);
int vbi_kwrap_ttx_get_wss_packetstask(UINT8 **wss_packet);
int vbi_kwrap_ttx_get_parameter_offset(UINT32 *parameter_offset);
int vbi_kwrap_ttx_get_ttx_packetstask(LX_TTX_PACKET_TYPE_T **ttx_packet, int packet_count);
int vbi_kwrap_ttx_enable_vps_slicer(BOOLEAN bEnable);
int vbi_kwrap_ttx_set_tt_slicer_mode(unsigned int slicer_mode);
int vbi_kwrap_cc_initializemodule(void);
int vbi_kwrap_cc_enable(void);
int vbi_kwrap_cc_disable(void);
int vbi_kwrap_cc_close(void);
int vbi_kwrap_cc_resetbuffer(void);
int vbi_kwrap_cc_reset(void);;
int vbi_kwrap_cc_reg_init(void);
int vbi_kwrap_cc_get_packet_count(UINT32 *count);
int vbi_kwrap_cc_get_cc_datatask(LX_CC_DATA_T *pCC_Data_Buffer);
int vbi_kwrap_ttx_disableinterrupt(void);
int vbi_kwrap_ttx_disable(void);
int vbi_kwrap_set_wsscopyprotectionrawfilter(int filterlength);
int vbi_kwrap_set_cgmscopyprotectionrawfilter(int filterlength);
int vbi_kwrap_set_analogcpcopyprotectionrawfilter(int filterlength);
int vbi_kwrap_resetdataprofilter(void);
int vbi_kwrap_ttx_setdebugmodekprint(int mode);
int vbi_kwrap_cc_setdebugmodekprint(int mode);
int vbi_kwrap_setlogmprintmask(int logLevel, BOOLEAN onOff);
void vbi_kwrap_dbg_initialize(void);
void vbi_kwrap_dbg_shutdown(void);
/*------------------------------------------------------------------------------
	Extern Variables
------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

