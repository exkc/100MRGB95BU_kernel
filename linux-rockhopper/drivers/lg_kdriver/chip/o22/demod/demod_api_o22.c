/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
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


/*  @file
 *
 *	demod api for chip
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-13
 *	@note
 */

#define DEMOD_TAG "[CHIP.API] "

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>		/* printk() */
#include <linux/types.h>		/* size_t */

#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "DBB_DEMOD_L2_Common_API.h"

#include "demod_common_o22.h"
#include "demod_ipc_o22.h"

int DEMOD_O22_API_Suspend (void) {
	LX_DEMOD_L2_Context * frontend = NULL;

	frontend = DEMOD_O22_GetContext();

	DEMOD_INFO("set fw_type invalid to entering suspend\n");

	frontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;

	return RET_OK;
}

int DEMOD_O22_API_Status(char * pDbglog, int * pDbgidx) {

	LX_DEMOD_L2_Context * frontend = NULL;

	frontend = DEMOD_O22_GetContext();

	*pDbgidx = DEMOD_L1_API_Status(frontend->demod, pDbglog);

	return RET_OK;
}

int DEMOD_O22_API_Dump(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();
	int retc = NO_DEMOD_ERROR;

	//*pDbgidx = DEMOD_L1_API_Dump(frontend->demod, pDbglog);

	if (!frontend->demod_init_done) {
		DEMOD_WARN("not yet demod_init_done\n");
	} else {
		/* Call the demod global status function */
		retc = DEMOD_L1_GET_DD_Status (frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		}

		switch (frontend->demod->rsp->dd_status.reply_operMod) {
		case DEMOD_MODULATION_VSB:
			retc = DEMOD_L1_GET_DD_VSB_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_VSB_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			}
			break;

		case DEMOD_MODULATION_QAM:
			retc = DEMOD_L1_GET_DD_QAM_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_QAM_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			}
			break;

		case DEMOD_MODULATION_ATSC3:
			retc = DEMOD_L1_GET_DD_ATSC3_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_ATSC3_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			}

			retc = DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR ("DEMOD_L1_GET_DD_ATSC3_PLP_Info  error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			}
			break;

		case DEMOD_MODULATION_ISDBT:
			retc = DEMOD_L1_GET_DD_ISDBT_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_ISDBT_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			retc = DEMOD_L1_GET_DD_ISDBT_TMCC_Info(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_ISDBT_TMCC_Info() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBT :
			retc = DEMOD_L1_GET_DD_DVBT_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBT_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBT2 :
			retc = DEMOD_L1_GET_DD_DVBT2_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBT2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBC :
			retc = DEMOD_L1_GET_DD_DVBC_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBC_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBC2 :
			retc = DEMOD_L1_GET_DD_DVBC2_Status(frontend->demod );
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBC2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBS :
			retc = DEMOD_L1_GET_DD_DVBS_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBS_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		case DEMOD_MODULATION_DVBS2:
			retc = DEMOD_L1_GET_DD_DVBS2_Status(frontend->demod);
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DVBS2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		case DEMOD_MODULATION_DTMB :
			retc = DEMOD_L1_GET_DD_DTMB_Status(frontend->demod );
			if(NO_DEMOD_ERROR != retc) {
				DEMOD_ERROR("FAIL, DEMOD_L1_GET_DD_DTMB_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			break;

		default :
			DEMOD_ERROR("invalid operMod : 0x%02x\n", frontend->demod->rsp->dd_status.reply_operMod);
		}
	}

	DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_STATUS_CODE, pDbglog, pDbgidx);

	switch (frontend->demod->rsp->dd_status.reply_operMod)
	{
		case DEMOD_MODULATION_VSB :
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_VSB_STATUS_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_ATSC3:
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_ATSC3_STATUS_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_ATSC3_PLP_ID_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_ATSC3_PLP_INFO_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_QAM:
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_QAM_STATUS_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_ISDBT:
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_ISDBT_STATUS_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_ISDBT_TMCC_INFO_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_DVBT:
			//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_PROP_DVBT_HIERARCHY_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_DVBT_STATUS_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_DVBT2:
			//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_PROP_DVBT2_MODE_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_DVBT2_STATUS_CODE, pDbglog, pDbgidx);
			break;

			case DEMOD_MODULATION_DVBC:
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_DVBC_STATUS_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_DVBS:
			//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_PROP_DVBS_OPMSEL_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_DVBS_STATUS_CODE, pDbglog, pDbgidx);
			break;

		case DEMOD_MODULATION_DVBS2:
			//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_PROP_DVBS_OPMSEL_CODE, pDbglog, pDbgidx);
			DEMOD_L1_CommandDump(frontend->demod->rsp, DEMOD_CMD_DVBS2_STATUS_CODE, pDbglog, pDbgidx);
			break;

		default:
			break;
	}
	
	return RET_OK;
}


