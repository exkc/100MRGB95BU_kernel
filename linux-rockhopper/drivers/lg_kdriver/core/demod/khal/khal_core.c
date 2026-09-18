/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jinwoo.han (jinwoo.han@lge.com)
 *  @version	1.0
 *  @date		2017.04.13
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#define DEMOD_TAG "[KHAL.CORE] "
/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/delay.h>	/**< mdelay */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/freezer.h>

#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/delay.h>	/**< mdelay */

#ifdef KDRV_CONFIG_PM
#include <linux/platform_device.h>
#endif
#include "os_util.h"
#include "base_device.h"

#include "demod_khal.h"
#include "demod_impl.h"

//#include "ctop_regs.h"
//#include "sys_regs.h"
//#include "i2c_core.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

#define INITIAL_BLIND_SCAN_BW                   40000000	// 40MHz (this value can be modified)
#define SCALE_OF_MHZ                            1000000
#define SCALE_OF_KHZ                            1000

#define BER_SCALE                               257 		// PacketError * BER_SCALE = 65535

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern unsigned int intlog10(u32 value);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 rangeMin;
	UINT32 rangeMax;
	UINT32 center_rf;
	UINT32 seekBWHz;
} KHAL_DEMOD_DVBS_SAT_BS_CONTEXT_T;

typedef struct {
	UINT8  sequence_length;
	UINT8  sequenceBuffer[6];
	UINT8  cont_tone;
	UINT8  tone_burst;
	UINT8  burst_sel;
	UINT8  end_seq;
} KHAL_DEMOD_DiSEqC_MSG_T;

typedef enum {
	DISEQC_TONEBURST_UNMODULATED = 0,
	DISEQC_TONEBURST_MODULATED 
} KHAL_PARAM_TONE_MSG_T;

BOOLEAN gBerTrigger             = FALSE;

/*----------------------------------------------------------------------------------------
	static Variables
----------------------------------------------------------------------------------------*/

static KHAL_DEMOD_DVBS_SAT_BS_CONTEXT_T _gBlindScanContext;
static LX_DEMOD_DVBS_OPERATION_MODE_T   _gDvbsOperationMode = LX_DEMOD_DVBS_NORMAL_MODE ;

static const LX_DEMOD_SQI_CN_NORDIGP1_T KhalSqiCnNordigP1_DVB[80] = {
		/* Hierachy mode */   	  /* bsetHP */ /* RF mode  */ /* Code rate*/    /*CN ref */
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_1_2, 5100 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_2_3, 6900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_3_4, 7900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_5_6, 8900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_7_8, 9700 },

	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_DQPSK, LX_DEMOD_CODE_1_2, 5100 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_DQPSK, LX_DEMOD_CODE_2_3, 6900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_DQPSK, LX_DEMOD_CODE_3_4, 7900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_DQPSK, LX_DEMOD_CODE_5_6, 8900 },
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_DQPSK, LX_DEMOD_CODE_7_8, 9700 },

	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 10800},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 13100},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 14600},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 15600},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 16000},

	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 16500},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 18700},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 20200},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 21600},
	{LX_DEMOD_DVB_TPS_HIERACHY_NONE, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 22500},

	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 9100},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 12000},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 13600},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 15000},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 16600},

	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 10900},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 14100},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 15700},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 19400},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 20600},

	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 6800},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 9100},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 10400},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 11900},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 12700},

	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 8500},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 11000},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 12800},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 15000},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 16000},

	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 5800},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 7900},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 9100},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 10300},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 12100},

	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 8000},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 9300},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 11600},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 13000},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 12900},

	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 12500},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 14300},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 15300},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 16300},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 16900},

	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 16700},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 19100},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 20900},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 22500},
	{LX_DEMOD_DVB_TPS_HIERACHY_1, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 23700},

	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 15000},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 17200},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 18400},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 19100},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 20100},

	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 18500},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 21200},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 23600},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 24700},
	{LX_DEMOD_DVB_TPS_HIERACHY_2, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 25900},

	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 19500},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 21400},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 22500},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 23700},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_16QAM, LX_DEMOD_CODE_7_8, 24700},

	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 21900},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 24200},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 25600},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 26900},
	{LX_DEMOD_DVB_TPS_HIERACHY_4, FALSE, LX_DEMOD_64QAM, LX_DEMOD_CODE_7_8, 27800}
};

static const LX_DEMOD_SQI_CN_NORDIGP1_T KhalSqiCnNordigP1_DVBForDVBT2[24] = {
	/* Hierachy mode */ 	             /* bsetHP */ /* RF mode  */ /* Code rate*/	   /*CN ref */
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_1_2, 3500 },
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_3_5, 4700 },
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_2_3, 5600 },
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_3_4, 6600 },
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_4_5, 7200 },
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_QPSK,  LX_DEMOD_CODE_5_6, 7700 },

	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_1_2, 8700},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_5, 10100},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_2_3, 11400},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_3_4, 12500},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_4_5, 13300},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_16QAM, LX_DEMOD_CODE_5_6, 13800},

	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_1_2, 13000},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_5, 14800},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_2_3, 16200},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_3_4, 17700},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_4_5, 18700},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_64QAM, LX_DEMOD_CODE_5_6, 19400},

	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_1_2, 17000},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_3_5, 19400},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_2_3, 20800},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_3_4, 22900},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_4_5, 24300},
	{LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN, TRUE, LX_DEMOD_256QAM, LX_DEMOD_CODE_5_6, 25100}
};

static const SINT32 nordigDVBCdB1000_GBB[5] = {
      /*   16,    32,    64,   128,   256  */
	 2300,  2600,  2800, 31000, 36000
};

static UINT16  gTargetMax              = 100;
static UINT16  gTargetMin              = 0;
static UINT16  gTargetCenter		= 0;

static UINT8 _Demod_SQI_Cal (UINT8 oriQuality) {
	UINT8 signalQuality;

	gTargetCenter = oriQuality ;

	if (gTargetMax <= gTargetCenter) {
		gTargetMax = gTargetCenter+3;

		if (gTargetMax > 100) {
			gTargetMax = 100;
		}
		if (gTargetMax > 5) {
			gTargetMin = gTargetCenter -5;
		} else {
			gTargetMin = gTargetMax;
		}

		if (gTargetCenter == 100) {
			signalQuality = gTargetCenter;
		} else {
			signalQuality = gTargetMin;
		}

	} else if (gTargetMin >= gTargetCenter) {
		gTargetMin = gTargetCenter;
		signalQuality = gTargetMin;

	} else {
		gTargetMax = gTargetMin + 5;
		if (gTargetMax > 100) {
			gTargetMax = 100;
		}

		signalQuality = gTargetMin;
	}

	if (oriQuality == 0) {
		signalQuality = 0;
	}

	return signalQuality;
}

static LX_DEMOD_RF_MODE_T _Demod_ATSC3_ConvHALConst2LX_RfMode (KHAL_DEMOD_TPS_CONSTELLATION_T constellation) {
	LX_DEMOD_RF_MODE_T rfMode;

	switch (constellation)
	{
		case KHAL_DEMOD_TPS_CONST_QPSK:     rfMode = LX_DEMOD_QPSK;				break;
		case KHAL_DEMOD_TPS_CONST_DQPSK:    rfMode = LX_DEMOD_DQPSK;				break;
		case KHAL_DEMOD_TPS_CONST_PSK_8:    rfMode = LX_DEMOD_8PSK;				break;
		case KHAL_DEMOD_TPS_CONST_VSB_8:    rfMode = LX_DEMOD_VSB;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_16:   rfMode = LX_DEMOD_16QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_32:   rfMode = LX_DEMOD_32QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_64:   rfMode = LX_DEMOD_64QAM;   				break;
		case KHAL_DEMOD_TPS_CONST_QAM_128:  rfMode = LX_DEMOD_128QAM;      			break;
		case KHAL_DEMOD_TPS_CONST_QAM_256:  rfMode = LX_DEMOD_256QAM;     			break;
		case KHAL_DEMOD_TPS_CONST_QAM_4NR:  rfMode = LX_DEMOD_4QAM_NR;     			break;
		case KHAL_DEMOD_TPS_CONST_QAM_4:    rfMode = LX_DEMOD_4QAM;        			break;
		case KHAL_DEMOD_TPS_CONST_END:      rfMode = LX_DEMOD_MODE_END;    			break;
//		case KHAL_DEMOD_TPS_CONST_UNKNOWN:  rfMode = LX_DEMOD_UNKOWN_MODE; 			break;
		default:                            rfMode = LX_DEMOD_UNKOWN_MODE; 			break;
	}

	return rfMode;
}

/**
 * _DVB_LG115X_ConvTu2LX_RfMode
 * Convert constellation  to LG115x RF mode.
 *
 * @param	constellation 			[IN] TU_TPS_CONSTELLATION_T
 * @return 	LG115x RF mode - LX_DEMOD_RF_MODE_T
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
static KHAL_DEMOD_TPS_CONSTELLATION_T _Demod_DVB_ConvLX_RfMode2HALConst(LX_DEMOD_RF_MODE_T rfMode)
{
	KHAL_DEMOD_TPS_CONSTELLATION_T constellation;

	switch (rfMode) 	{
		case LX_DEMOD_QPSK:		constellation = KHAL_DEMOD_TPS_CONST_QPSK;		break;
		case LX_DEMOD_DQPSK:		constellation = KHAL_DEMOD_TPS_CONST_DQPSK;		break;
		case LX_DEMOD_8PSK:		constellation = KHAL_DEMOD_TPS_CONST_PSK_8;		break;
		case LX_DEMOD_16QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_16;		break;
		case LX_DEMOD_32QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_32;		break;
		case LX_DEMOD_64QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_64;		break;
		case LX_DEMOD_128QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_128;		break;
		case LX_DEMOD_256QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_256;		break;
//		case LX_DEMOD_1024QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_1024;		break;
//		case LX_DEMOD_4096QAM:		constellation = KHAL_DEMOD_TPS_CONST_QAM_4096;		break;
//		case LX_DEMOD_UNKOWN_MODE:	constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;		break;
		default:			constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;		break;
	}
	return constellation;
}

/**
 * _DVB_LG115X_ConvTu2LX_RfMode
 * Convert constellation  to LG115x RF mode.
 *
 * @param	constellation 			[IN] TU_TPS_CONSTELLATION_T
 * @return 	LG115x RF mode - LX_DEMOD_RF_MODE_T
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static LX_DEMOD_RF_MODE_T _Demod_DVB_ConvHALConst2LX_RfMode(KHAL_DEMOD_TPS_CONSTELLATION_T constellation)
{
	LX_DEMOD_RF_MODE_T rfMode;

	switch (constellation)
	{
		case KHAL_DEMOD_TPS_CONST_QPSK:		rfMode = LX_DEMOD_QPSK;				break;
		case KHAL_DEMOD_TPS_CONST_DQPSK:	rfMode = LX_DEMOD_DQPSK;			break;
		case KHAL_DEMOD_TPS_CONST_PSK_8:	rfMode = LX_DEMOD_8PSK;				break;
		case KHAL_DEMOD_TPS_CONST_VSB_8:	rfMode = LX_DEMOD_VSB;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_16:	rfMode = LX_DEMOD_16QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_32:	rfMode = LX_DEMOD_32QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_64:	rfMode = LX_DEMOD_64QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_128:	rfMode = LX_DEMOD_128QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_256:	rfMode = LX_DEMOD_256QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_4NR:	rfMode = LX_DEMOD_4QAM_NR;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_4:	rfMode = LX_DEMOD_4QAM;				break;
		case KHAL_DEMOD_TPS_CONST_END:		rfMode = LX_DEMOD_MODE_END;			break;
//		case KHAL_DEMOD_TPS_CONST_UNKNOWN:	rfMode = LX_DEMOD_UNKOWN_MODE;			break;
		default:				rfMode = LX_DEMOD_UNKOWN_MODE;			break;
	}

	return rfMode;
}

/**
 * _Demod_DVB_ConvLX_CodeRate2HALConst
 * Convert constellation  to LG115x RF mode.
 *
 * @param	constellation 			[IN] TU_TPS_CONSTELLATION_T
 * @return 	LG115x RF mode - LX_DEMOD_RF_MODE_T
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
static KHAL_DEMOD_TPS_CODERATE_T _Demod_DVB_ConvLX_CodeRate2HALConst(LX_DEMOD_CODERATE_T lxCodeRate)
{
	KHAL_DEMOD_TPS_CODERATE_T codeRate;

	switch (lxCodeRate)
	{
		case LX_DEMOD_CODE_1_2:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_1_2;			break;
		case LX_DEMOD_CODE_1_3:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_1_3;			break;
		case LX_DEMOD_CODE_1_4:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_1_4;			break;
		case LX_DEMOD_CODE_2_3:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_2_3;			break;
		case LX_DEMOD_CODE_3_4:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_3_4;			break;
		case LX_DEMOD_CODE_2_5:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_2_5;			break;
		case LX_DEMOD_CODE_3_5:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_3_5;			break;
		case LX_DEMOD_CODE_4_5:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_4_5;			break;
		case LX_DEMOD_CODE_5_6:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_5_6;			break;
		case LX_DEMOD_CODE_6_7:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_6_7;			break;
		case LX_DEMOD_CODE_7_8:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_7_8;			break;
		case LX_DEMOD_CODE_8_9:		codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_8_9;			break;
		case LX_DEMOD_CODE_9_10:	codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CODE_9_10;			break;
//		case LX_DEMOD_CODE_UNKNOWN:	codeRate = KHAL_DEMOD_TPS_CONST_UNKNOWN;		break;
		default:			codeRate = (KHAL_DEMOD_TPS_CODERATE_T)KHAL_DEMOD_TPS_CONST_UNKNOWN;		break;
	}
	return codeRate;
}

static LX_DEMOD_BWMODE_T _demod_convert_khal_ch_bw (KHAL_DEMOD_CHANNEL_BW_T khal_ch_bw) {
	LX_DEMOD_BWMODE_T demod_ch_bw = LX_DEMOD_BW_UNKNOWN;
	switch (khal_ch_bw) {
		case KHAL_DEMOD_CH_BW_6M:
			demod_ch_bw = LX_DEMOD_BW_6MHZ;
			break;
		case KHAL_DEMOD_CH_BW_7M:
			demod_ch_bw = LX_DEMOD_BW_7MHZ;
			break;
		case KHAL_DEMOD_CH_BW_8M:
			demod_ch_bw = LX_DEMOD_BW_8MHZ;
			break;
		default:
			demod_ch_bw = LX_DEMOD_BW_UNKNOWN;
			break;
	}
	return demod_ch_bw;
}
/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * _Demod_DVBT_ConvHALToLXSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DVBT_ConvHALToLXSpecParams (KHAL_DEMOD_DVBT_SET_PARAM_T paramStruct, LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam) {

	pDvbtConfigParam->bSetHp      = paramStruct.bProfileHP;
	pDvbtConfigParam->tuneMode    = (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL :
									(paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL : LX_DEMOD_TUNE_AUTO ;

	DEMOD_PRINT("tuneMode = 0x%02x",paramStruct.tuneMode);
	DEMOD_PRINT("eChannelBW = 0x%02x",paramStruct.eChannelBW);

	pDvbtConfigParam->channelBW = _demod_convert_khal_ch_bw(paramStruct.eChannelBW);

	switch (paramStruct.carrierMode) {
		case KHAL_DEMOD_TPS_CARR_2K:	  pDvbtConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;		break;
		case KHAL_DEMOD_TPS_CARR_8K:	  pDvbtConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;		break;
		default:			  pDvbtConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;		break;
	}

	switch (paramStruct.guardInterval)
	{
		case KHAL_DEMOD_TPS_GUARD_1_4:    pDvbtConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;		break;
		case KHAL_DEMOD_TPS_GUARD_1_8:    pDvbtConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;		break;
		case KHAL_DEMOD_TPS_GUARD_1_16:   pDvbtConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16; 		break;
		case KHAL_DEMOD_TPS_GUARD_1_32:   pDvbtConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32; 		break;
		default:                          pDvbtConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;	break;
	}

	switch (paramStruct.hierarchy)
	{
		case KHAL_DEMOD_TPS_HIERA_NONE:   pDvbtConfigParam->hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_NONE; 	break;
		case KHAL_DEMOD_TPS_HIERA_1:      pDvbtConfigParam->hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_1;		break;
		case KHAL_DEMOD_TPS_HIERA_2:      pDvbtConfigParam->hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_2;		break;
		case KHAL_DEMOD_TPS_HIERA_4:      pDvbtConfigParam->hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_4;		break;
		default:			  pDvbtConfigParam->hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN; 	break;
	}

	if (FALSE == paramStruct.bProfileHP)
	{
		switch (paramStruct.codeRate)
		{
			case KHAL_DEMOD_TPS_CODE_1_2:	pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_1_2;		break;
			case KHAL_DEMOD_TPS_CODE_2_3:	pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_2_3;		break;
			case KHAL_DEMOD_TPS_CODE_3_4:	pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_3_4;		break;
			case KHAL_DEMOD_TPS_CODE_5_6:	pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_5_6;		break;
			case KHAL_DEMOD_TPS_CODE_7_8:	pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_7_8;		break;
			default:			pDvbtConfigParam->lpCodeRate = LX_DEMOD_CODE_UNKNOWN;		break;
		}
	}
	else
	{
		switch (paramStruct.codeRate)
		{
			case KHAL_DEMOD_TPS_CODE_1_2:	pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_1_2;		break;
			case KHAL_DEMOD_TPS_CODE_2_3:	pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_2_3;		break;
			case KHAL_DEMOD_TPS_CODE_3_4:	pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_3_4;		break;
			case KHAL_DEMOD_TPS_CODE_5_6:	pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_5_6;		break;
			case KHAL_DEMOD_TPS_CODE_7_8:	pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_7_8;		break;
			default:			pDvbtConfigParam->hpCodeRate = LX_DEMOD_CODE_UNKNOWN;		break;
		}
	}

	switch (paramStruct.constellation)
	{
		case KHAL_DEMOD_TPS_CONST_QPSK: 	pDvbtConfigParam->qamMode = LX_DEMOD_QPSK;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_16:	pDvbtConfigParam->qamMode = LX_DEMOD_16QAM; 			break;
		case KHAL_DEMOD_TPS_CONST_QAM_32:	pDvbtConfigParam->qamMode = LX_DEMOD_32QAM; 			break;
		case KHAL_DEMOD_TPS_CONST_QAM_64:	pDvbtConfigParam->qamMode = LX_DEMOD_64QAM; 			break;
		case KHAL_DEMOD_TPS_CONST_QAM_128:	pDvbtConfigParam->qamMode = LX_DEMOD_128QAM;			break;
		case KHAL_DEMOD_TPS_CONST_QAM_256:	pDvbtConfigParam->qamMode = LX_DEMOD_256QAM;			break;
		default:				pDvbtConfigParam->qamMode = LX_DEMOD_UNKOWN_MODE;		break;
	}
	return RET_OK;
}


/**
 * _DVBT_LG115X_ConvLX2TuSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DVBT_ConvLX2HALSpecParams(LX_DEMOD_DVBT_CONFIG_T dvbtConfigParam,  KHAL_DEMOD_SPECDATA_DVBT_T *specDvbt )
{
	DEMOD_PRINT("eChannelBW = 0x%02x", dvbtConfigParam.channelBW);

	/* 4.6.2.9 TRANSMISSION MODE */
	if (dvbtConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_2K)
	{
		specDvbt->carrierMode = KHAL_DEMOD_TPS_CARR_2K;
	}
	else if (dvbtConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_8K)
	{
		specDvbt->carrierMode = KHAL_DEMOD_TPS_CARR_8K;
	}
	else
	{
		specDvbt->carrierMode = KHAL_DEMOD_TPS_CARR_UNKNOWN;
	}

	DEMOD_PRINT("FFTMode = 0x%02x",dvbtConfigParam.FFTMode);
	/* 4.6.2.8 GUARD INTERVALS */
	if (dvbtConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_32)
	{
		specDvbt->guardInterval = KHAL_DEMOD_TPS_GUARD_1_32;
	}
	else if (dvbtConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_16)
	{
		specDvbt->guardInterval = KHAL_DEMOD_TPS_GUARD_1_16;
	}
	else if (dvbtConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_8)
	{
		specDvbt->guardInterval = KHAL_DEMOD_TPS_GUARD_1_8;
	}
	else if (dvbtConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_4)
	{
		specDvbt->guardInterval = KHAL_DEMOD_TPS_GUARD_1_4;
	}
	else
	{
		specDvbt->guardInterval = KHAL_DEMOD_TPS_GUARD_UNKNOWN;
	}
	DEMOD_PRINT("gIMode = 0x%02x",dvbtConfigParam.gIMode);

	if (FALSE == dvbtConfigParam.bSetHp)
	{
		if (dvbtConfigParam.lpCodeRate == LX_DEMOD_CODE_1_2)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
		}
		else if (dvbtConfigParam.lpCodeRate == LX_DEMOD_CODE_2_3)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
		}
		else if (dvbtConfigParam.lpCodeRate == LX_DEMOD_CODE_3_4)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
		}
		else if (dvbtConfigParam.lpCodeRate == LX_DEMOD_CODE_5_6)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
		}
		else if (dvbtConfigParam.lpCodeRate == LX_DEMOD_CODE_7_8)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
		}
		else
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
		}
		DEMOD_PRINT("lpCodeRate = 0x%02x",dvbtConfigParam.lpCodeRate);
	}
	else
	{
		if (dvbtConfigParam.hpCodeRate == LX_DEMOD_CODE_1_2)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
		}
		else if (dvbtConfigParam.hpCodeRate == LX_DEMOD_CODE_2_3)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
		}
		else if (dvbtConfigParam.hpCodeRate == LX_DEMOD_CODE_3_4)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
		}
		else if (dvbtConfigParam.hpCodeRate == LX_DEMOD_CODE_5_6)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
		}
		else if (dvbtConfigParam.hpCodeRate == LX_DEMOD_CODE_7_8)
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
		}
		else
		{
			specDvbt->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
		}

		DEMOD_PRINT("hpCodeRate = 0x%02x",dvbtConfigParam.hpCodeRate);
	}

	DEMOD_PRINT("bSetHp = 0x%x",dvbtConfigParam.bSetHp);
	/* 4.6.2.6 HIERACHY INFORMATION */
	if (dvbtConfigParam.hierachMode == LX_DEMOD_DVB_TPS_HIERACHY_NONE)
	{
		specDvbt->hierarchy = KHAL_DEMOD_TPS_HIERA_NONE;
	}
	else if (dvbtConfigParam.hierachMode == LX_DEMOD_DVB_TPS_HIERACHY_1)
	{
		specDvbt->hierarchy = KHAL_DEMOD_TPS_HIERA_1;
	}
	else if (dvbtConfigParam.hierachMode == LX_DEMOD_DVB_TPS_HIERACHY_2)
	{
		specDvbt->hierarchy = KHAL_DEMOD_TPS_HIERA_2;
	}
	else if (dvbtConfigParam.hierachMode == LX_DEMOD_DVB_TPS_HIERACHY_4)
	{
		specDvbt->hierarchy = KHAL_DEMOD_TPS_HIERA_4;
	}
	else
	{
		specDvbt->hierarchy = KHAL_DEMOD_TPS_HIERA_UNKNOWN;
	}
	DEMOD_PRINT("hierachMode = 0x%02x",dvbtConfigParam.hierachMode);

	/* 4.6.2.5 CONSTELLATION */

	if (dvbtConfigParam.qamMode == LX_DEMOD_QPSK)
	{
		specDvbt->constellation = KHAL_DEMOD_TPS_CONST_QPSK;
	}
	else if (dvbtConfigParam.qamMode == LX_DEMOD_16QAM)
	{
		specDvbt->constellation = KHAL_DEMOD_TPS_CONST_QAM_16;
	}
	else if (dvbtConfigParam.qamMode == LX_DEMOD_64QAM)
	{
		specDvbt->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
	}
	else
	{
		specDvbt->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;
	}
	DEMOD_PRINT("qamMode = 0x%02x",dvbtConfigParam.qamMode);

	/* ETC PRIORITY */
	// specDVBT.bProfileHP	= TRUE;
	specDvbt->bProfileHP = dvbtConfigParam.bSetHp;
	DEMOD_PRINT("bSetHp = 0x%02x",dvbtConfigParam.bSetHp);

	specDvbt->bSpectrumInv = dvbtConfigParam.bSpectrumInv;
	DEMOD_PRINT("bSpectrumInv = 0x%02x",dvbtConfigParam.bSpectrumInv);

	return RET_OK;
}

/**
 * _Demod_DVBT2_ConvHALToLXSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt 			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam  	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DVBT2_ConvHALToLXSpecParams(KHAL_DEMOD_DVBT2_SET_PARAM_T paramStruct, LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam )
{

	pDvbt2ConfigParam->tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL : (paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL : LX_DEMOD_TUNE_AUTO ;
	pDvbt2ConfigParam->bSpectrumInv = (paramStruct.bSpectrumInv != FALSE) ? TRUE : FALSE ;

	pDvbt2ConfigParam->channelBW = _demod_convert_khal_ch_bw(paramStruct.eChannelBW);

	switch (paramStruct.carrierMode)
	{
		case KHAL_DEMOD_TPS_CARR_1K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_1K;		break;
		case KHAL_DEMOD_TPS_CARR_2K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;		break;
		case KHAL_DEMOD_TPS_CARR_4K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;		break;
		case KHAL_DEMOD_TPS_CARR_8K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;		break;
		case KHAL_DEMOD_TPS_CARR_16K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;		break;
		case KHAL_DEMOD_TPS_CARR_32K:		pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;		break;
		default:				pDvbt2ConfigParam->FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;		break;
	}

	switch (paramStruct.guardInterval)
	{
		case KHAL_DEMOD_TPS_GUARD_1_4:		pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;		break;
		case KHAL_DEMOD_TPS_GUARD_1_8:		pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;		break;
		case KHAL_DEMOD_TPS_GUARD_1_16:		pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;		break;
		case KHAL_DEMOD_TPS_GUARD_1_32:		pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;		break;
		case KHAL_DEMOD_TPS_GUARD_1_128:	pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;		break;
		case KHAL_DEMOD_TPS_GUARD_19_128:	pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;		break;
		case KHAL_DEMOD_TPS_GUARD_19_256:	pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;		break;
		default:				pDvbt2ConfigParam->gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;		break;
	}

	switch (paramStruct.codeRate)
	{
		case KHAL_DEMOD_TPS_CODE_1_2:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_1_2;			break;
		case KHAL_DEMOD_TPS_CODE_2_3:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_2_3;			break;
		case KHAL_DEMOD_TPS_CODE_3_4:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_3_4;			break;
		case KHAL_DEMOD_TPS_CODE_3_5:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_3_5;			break;
		case KHAL_DEMOD_TPS_CODE_4_5:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_4_5;			break;
		case KHAL_DEMOD_TPS_CODE_5_6:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_5_6;			break;
		case KHAL_DEMOD_TPS_CODE_7_8:		pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_7_8;			break;
		default:				pDvbt2ConfigParam->codeRate = LX_DEMOD_CODE_UNKNOWN;			break;
	}

	switch (paramStruct.constellation)
	{
		case KHAL_DEMOD_TPS_CONST_QPSK:		pDvbt2ConfigParam->qamMode = LX_DEMOD_QPSK;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_16:	pDvbt2ConfigParam->qamMode = LX_DEMOD_16QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_32:	pDvbt2ConfigParam->qamMode = LX_DEMOD_32QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_64:	pDvbt2ConfigParam->qamMode = LX_DEMOD_64QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_128:	pDvbt2ConfigParam->qamMode = LX_DEMOD_128QAM;				break;
		case KHAL_DEMOD_TPS_CONST_QAM_256:	pDvbt2ConfigParam->qamMode = LX_DEMOD_256QAM;				break;
		default:				pDvbt2ConfigParam->qamMode = LX_DEMOD_UNKOWN_MODE;			break;
	}

//	pDvbt2ConfigParam->groupID 	= paramStruct.groupID;
	pDvbt2ConfigParam->unPLP	= paramStruct.unPLP;
	DEMOD_PRINT("unPLP = %d\n",paramStruct.unPLP);

	return RET_OK;
}

/**
 * _Demod_DVBT2_ConvLX2HALSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt 			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam  	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DVBT2_ConvLX2HALSpecParams(LX_DEMOD_DVBT2_CONFIG_T dvbt2ConfigParam,  KHAL_DEMOD_SPECDATA_DVBT2_T *specDvbt2 )
{
	/* 4.6.2.9 TRANSMISSION MODE */
	if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_1K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_1K;
	}
	else if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_2K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_2K;
	}
	else if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_4K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_4K;
	}
	else if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_8K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_8K;
	}
	else if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_16K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_16K;
	}
	else if (dvbt2ConfigParam.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_32K)
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_32K;
	}
	else
	{
		specDvbt2->carrierMode = KHAL_DEMOD_TPS_CARR_UNKNOWN;
	}

	/* 4.6.2.8 GUARD INTERVALS */
	if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_4)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_1_4;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_8)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_1_8;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_16)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_1_16;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_32)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_1_32;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_128)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_1_128;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_19_128)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_19_128;
	}
	else if (dvbt2ConfigParam.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_19_256)
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_19_256;
	}
	else
	{
		specDvbt2->guardInterval = KHAL_DEMOD_TPS_GUARD_UNKNOWN;
	}

	//code rate
	if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_1_2)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_2_3)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_3_4)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_3_5)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_3_5;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_4_5)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_4_5;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_5_6)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
	}
	else if (dvbt2ConfigParam.codeRate == LX_DEMOD_CODE_7_8)
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
	}
	else
	{
		specDvbt2->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
	}

	/* 4.6.2.5 CONSTELLATION */
	if (dvbt2ConfigParam.qamMode == LX_DEMOD_QPSK)
	{
		specDvbt2->constellation = KHAL_DEMOD_TPS_CONST_QPSK;
	}
	else if (dvbt2ConfigParam.qamMode == LX_DEMOD_16QAM)
	{
		specDvbt2->constellation	= KHAL_DEMOD_TPS_CONST_QAM_16;
	}
	else if (dvbt2ConfigParam.qamMode == LX_DEMOD_32QAM)
	{
		specDvbt2->constellation	= KHAL_DEMOD_TPS_CONST_QAM_32;
	}
	else if (dvbt2ConfigParam.qamMode == LX_DEMOD_64QAM)
	{
		specDvbt2->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
	}
	else if (dvbt2ConfigParam.qamMode == LX_DEMOD_128QAM)
	{
		specDvbt2->constellation = KHAL_DEMOD_TPS_CONST_QAM_128;
	}
	else if (dvbt2ConfigParam.qamMode == LX_DEMOD_256QAM)
	{
		specDvbt2->constellation = KHAL_DEMOD_TPS_CONST_QAM_256;
	}
	else
	{
		specDvbt2->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;
	}

	specDvbt2->bSpectrumInv = dvbt2ConfigParam.bSpectrumInv;
//	specDvbt2->groupID 		= dvbt2ConfigParam.groupID;
	specDvbt2->unPLP		= dvbt2ConfigParam.unPLP;
	DEMOD_PRINT("unPLP = %d\n",dvbt2ConfigParam.unPLP);

	return RET_OK;
}

/**
 * _Demod_DTMB_ConvHALToLXSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt 			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam  	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DTMB_ConvHALToLXSpecParams(KHAL_DEMOD_DTMB_SET_PARAM_T paramStruct, LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam )
{
	pDtmbConfigParam->tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL :
									(paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL : LX_DEMOD_TUNE_AUTO ;
	pDtmbConfigParam->bM720	= (paramStruct.bM720 == TRUE)?TRUE:FALSE;

	pDtmbConfigParam->channelBW	= _demod_convert_khal_ch_bw(paramStruct.eChannelBW);

	switch (paramStruct.carrierMode)
	{
		case KHAL_DEMOD_TPS_CARR_SC:		pDtmbConfigParam->carrierMode = LX_DEMOD_CARRIER_SINGLE;	break;
		case KHAL_DEMOD_TPS_CARR_MC:		pDtmbConfigParam->carrierMode = LX_DEMOD_CARRIER_MULTI;		break;
		default:				pDtmbConfigParam->carrierMode = LX_DEMOD_CARRIER_UNKNOWN;	break;
	}

	switch (paramStruct.guardInterval)
	{
		case KHAL_DEMOD_TPS_GUARD_420_C:	pDtmbConfigParam->pnMode= LX_DEMOD_TPS_GUARD_420_C;		break;
		case KHAL_DEMOD_TPS_GUARD_420_V:	pDtmbConfigParam->pnMode= LX_DEMOD_TPS_GUARD_420_V;		break;
		case KHAL_DEMOD_TPS_GUARD_595:		pDtmbConfigParam->pnMode= LX_DEMOD_TPS_GUARD_595;		break;
		case KHAL_DEMOD_TPS_GUARD_945_C:	pDtmbConfigParam->pnMode= LX_DEMOD_TPS_GUARD_945_C;		break;
		case KHAL_DEMOD_TPS_GUARD_945_V:	pDtmbConfigParam->pnMode= LX_DEMOD_TPS_GUARD_945_V;		break;
		default:				pDtmbConfigParam->pnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;	break;
	}

	switch (paramStruct.codeRate)
	{
		case KHAL_DEMOD_TPS_CODE_2_5:		pDtmbConfigParam->codeRate = LX_DEMOD_CODE_2_5;			break;
		case KHAL_DEMOD_TPS_CODE_3_5:		pDtmbConfigParam->codeRate = LX_DEMOD_CODE_3_5;			break;
		case KHAL_DEMOD_TPS_CODE_4_5:		pDtmbConfigParam->codeRate = LX_DEMOD_CODE_4_5;			break;
		default:				pDtmbConfigParam->codeRate = LX_DEMOD_CODE_UNKNOWN;		break;
	}

	switch (paramStruct.constellation)
	{
		case KHAL_DEMOD_TPS_CONST_QAM_4NR:	pDtmbConfigParam->constellation = LX_DEMOD_4QAM_NR; 		break;
		case KHAL_DEMOD_TPS_CONST_QAM_4:	pDtmbConfigParam->constellation = LX_DEMOD_4QAM;		break;
		case KHAL_DEMOD_TPS_CONST_QAM_16:	pDtmbConfigParam->constellation = LX_DEMOD_16QAM;		break;
		case KHAL_DEMOD_TPS_CONST_QAM_32:	pDtmbConfigParam->constellation = LX_DEMOD_32QAM;		break;
		case KHAL_DEMOD_TPS_CONST_QAM_64:	pDtmbConfigParam->constellation = LX_DEMOD_64QAM;		break;
		default:				pDtmbConfigParam->constellation = LX_DEMOD_UNKOWN_MODE;		break;
	}

	return RET_OK;

}

/**
 * _Demod_DTMB_ConvLX2HALSpecParams
 * Convert common FFT mode to LG1150 GBB FFT mode for DVB-T.
 *
 * @param	specDvbt 			[IN] TU_SPECDATA_DVBT_T
 * @param	pDvbtConfigParam  	[OUT] LX_DEMOD_DVBT_CONFIG_T
 * @return if Succeeded - OK else-NOT_OK
 * @see 	_DEMOD_DVB_DVBT_ConvSpecParams
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/

static int _Demod_DTMB_ConvLX2HALSpecParams(LX_DEMOD_DTMB_CONFIG_T dtmbConfigParam,  KHAL_DEMOD_SPECDATA_DTMB_T *specDtmb )
{

	specDtmb->bM720 = (specDtmb->bM720) ? TRUE : FALSE;

//	if (dtmbConfigParam.bM720 == TRUE)	specDtmb->bM720 = TRUE;
//	else		specDtmb->bM720 = FALSE;

	switch (dtmbConfigParam.carrierMode)
	{
		case LX_DEMOD_CARRIER_SINGLE:		specDtmb->carrierMode = KHAL_DEMOD_TPS_CARR_SC;			break;
		case LX_DEMOD_CARRIER_MULTI:		specDtmb->carrierMode = KHAL_DEMOD_TPS_CARR_MC;			break;
		default: 				specDtmb->carrierMode = KHAL_DEMOD_TPS_CARR_UNKNOWN;		break;
	}

	switch (dtmbConfigParam.pnMode)
	{
		case LX_DEMOD_TPS_GUARD_420_C:		specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_420_C;		break;
		case LX_DEMOD_TPS_GUARD_420_V:		specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_420_V;		break;
		case LX_DEMOD_TPS_GUARD_595:		specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_595;		break;
		case LX_DEMOD_TPS_GUARD_945_C:		specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_945_C;		break;
		case LX_DEMOD_TPS_GUARD_945_V:		specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_945_V;		break;
		default: 				specDtmb->guardInterval = KHAL_DEMOD_TPS_GUARD_UNKNOWN;		break;
	}

	switch (dtmbConfigParam.codeRate)
	{
		case LX_DEMOD_CODE_2_5:			specDtmb->codeRate = KHAL_DEMOD_TPS_CODE_2_5;			break;
		case LX_DEMOD_CODE_3_5:			specDtmb->codeRate = KHAL_DEMOD_TPS_CODE_3_5;			break;
		case LX_DEMOD_CODE_4_5:			specDtmb->codeRate = KHAL_DEMOD_TPS_CODE_4_5;			break;
		default: 				specDtmb->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;		break;
	}

	switch (dtmbConfigParam.constellation)
	{
		case LX_DEMOD_4QAM_NR:			specDtmb->constellation = KHAL_DEMOD_TPS_CONST_QAM_4NR;			break;
		case LX_DEMOD_4QAM:				specDtmb->constellation = KHAL_DEMOD_TPS_CONST_QAM_4;			break;
		case LX_DEMOD_16QAM:			specDtmb->constellation = KHAL_DEMOD_TPS_CONST_QAM_16;			break;
		case LX_DEMOD_32QAM:			specDtmb->constellation = KHAL_DEMOD_TPS_CONST_QAM_32;			break;
		case LX_DEMOD_64QAM:			specDtmb->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;			break;
		default: 				specDtmb->constellation 	= KHAL_DEMOD_TPS_CONST_UNKNOWN;			break;
	}


	return RET_OK;
}

static int _DEMOD_DVB_DVBS_send_diseqc_sequence(KHAL_DEMOD_DiSEqC_MSG_T * sendingDiseqcMsg)
{
	LX_DEMOD_DVBS_DiSEqC_MSG_T diseqcMsg;
	UINT8 i;

	DEMOD_PRINT("Start");

	memset(&diseqcMsg, 0x0, sizeof(LX_DEMOD_DVBS_DiSEqC_MSG_T));

	diseqcMsg.sequence_length = sendingDiseqcMsg->sequence_length;
	diseqcMsg.end_seq = sendingDiseqcMsg->end_seq;

	for(i=0;i < sendingDiseqcMsg->sequence_length;i++)
	{
		diseqcMsg.sequenceBuffer[i] = *(sendingDiseqcMsg->sequenceBuffer + i);
		DEMOD_PRINT("sequenceBuffer[%d] = %d\n",i,diseqcMsg.sequenceBuffer[i]);

	}
	diseqcMsg.cont_tone 	= (sendingDiseqcMsg->cont_tone == 1) ? LX_DEMOD_DISEQC_TONE_CONTINUOUS : LX_DEMOD_DISEQC_TONE_DISCRETE ;
	diseqcMsg.tone_burst 	= (sendingDiseqcMsg->tone_burst == 1) ? LX_DEMOD_DISEQC_TONE_BURST_ON : LX_DEMOD_DISEQC_TONE_BURST_OFF;
	diseqcMsg.burst_sel 	= (sendingDiseqcMsg->burst_sel == 1) ? LX_DEMOD_DISEQC_TONEBURST_MODULATED : LX_DEMOD_DISEQC_TONEBURST_UNMODULATED ;

	if (RET_OK != DEMOD_DVBS_Set_DiseqcToneMessageCtrl(&diseqcMsg))
	{
		DEMOD_PRINT("FAIL, DEMOD_DVBS_Set_DiseqcToneMessageCtrl()\n");

		return RET_ERROR;
	}

	return RET_OK;
}

static UINT32 _DEMOD_DVB_DVBT_GetSnr(LX_DEMOD_SIGNAL_CTX_T* sigStatus, LX_DEMOD_GIMODE_T giMode)
{
	UINT32 		cSnr,constPwrTemp,constPwr;
	UINT16		mse;
	UINT32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	mse	= sigStatus->m.mse;
	constPwr = sigStatus->m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}

	if (lx_chip() > LX_CHIP_E60) // for LX_CHIP_O22 
	{
		constPwrTemp =  24192; //for O22 scale
	}
	else
	{
		constPwrTemp =  3024;
	}
	
	if (constPwr == 1)
	{
		calcValue =  (UINT32)constPwrTemp / ((UINT32) mse);
		DEMOD_PRINT("calcValue = %d \n",calcValue);

		if (calcValue == 0)
		{
			DEMOD_PRINT("Over mse value (mse = %d)	\n",mse);

			calcValue = 1;
		}

		temp_snr 	= intlog10(calcValue);
		temp_snr 	= temp_snr * 100;
		cSnr 		= (UINT32)(temp_snr >> 24);

		if (cSnr > 340)
		{
			cSnr = cSnr + 10;
		}
		else
		{
			cSnr = cSnr + 20;
		}
	}
	else
	{
		calcValue 	=  (UINT32)constPwr / ((UINT32)(mse * 4));

		if (calcValue == 0)
		{
			DEMOD_PRINT("Over mse value (mse = %d)	\n" ,mse);

			calcValue = 1;
		}

		temp_snr 	= intlog10(calcValue);
		temp_snr 	= temp_snr * 100;
		cSnr 		= (UINT32)(temp_snr >> 24);
		DEMOD_PRINT("mse = %d, constPwr = %d,(original cSnr = %u)\n",mse,constPwr,cSnr);

		if (LX_DEMOD_DVBT_ISDBT_GIMODE_1_4 == giMode)
		{
			cSnr = cSnr + 60;
		}
		else
		{
			cSnr = cSnr + 65;
		}
	}
	return cSnr;
}

static UINT32 _DEMOD_DVB_DVBT2_GetSnr(LX_DEMOD_SIGNAL_CTX_T* sigStatus, LX_DEMOD_GIMODE_T giMode)
{
	UINT32   	cSnr, constPwr;
	UINT16 		mse;
	UINT32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	mse = sigStatus->m.mse;

	if (mse == 0)
	{
		mse = 1;
	}


	if (lx_chip() > LX_CHIP_E60) // for LX_CHIP_O22
	{
		constPwr =  24192; //for O22 scale
	}
	else
	{
		constPwr =  3024; //for other chips scale
	}

	calcValue =  (UINT32)constPwr / ((UINT32) mse);

	if (calcValue == 0)
	{
		DEMOD_PRINT("Over mse value (mse = %d)  \n" ,mse);

		calcValue = 1;
	}

	temp_snr 	= intlog10(calcValue);
	temp_snr 	= temp_snr * 100;
	cSnr		= (UINT32)(temp_snr >> 24);

	DEMOD_PRINT("Original cSnr = %d \n",cSnr);



	if (lx_chip() == LX_CHIP_M19)
	{
		DEMOD_PRINT("INCLUDE_M19_CHIP_KDRV \n");
		if (giMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_128)
		{
			if ( cSnr > 210)
			{
				cSnr += 10;
			}
			else if ( cSnr > 190 )
			{
				cSnr += 7;
			}
			else
			{
				cSnr += 3;
			}
		}
		else
		{
			if ( cSnr > 197 )
			{
				cSnr += 2;
			}
			else if (cSnr >= 190)
			{
				cSnr +=3;
			}
			else
			{
				cSnr +=1;
			}
		}
	}
	else if (lx_chip() == LX_CHIP_O20 || lx_chip() == LX_CHIP_E60 )  // supported LX_CHIP_O20 and LX_CHIP_E60
	{
		DEMOD_PRINT("INCLUDE_O20_CHIP_KDRV or INCLUDE_E60_CHIP_KDRV\n");
		if (giMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_128)
		{
			if ( cSnr > 210)
			{
				cSnr += 10;
			}
			else
			{
				cSnr += 7;
			}
		}
		else
		{
			if ( cSnr > 197 )
			{
				cSnr += 2;
			}
			else if (cSnr >= 190)
			{
				cSnr +=3;
			}
			else
			{
				cSnr +=1;
			}
		}
	}
	else if (lx_chip() >= LX_CHIP_O22 )  // supported LX_CHIP_O22
	{
		DEMOD_PRINT("INCLUDE_O22_CHIP_KDRV\n");
		if (giMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_128)
		{
			if ( cSnr > 210)
			{
				cSnr += 10;
			}
			else
			{
				cSnr += 7;
			}
		}
		else if (giMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_8)
		{
			if ( cSnr >= 230)
			{
				cSnr += 2;
			}
			else if ( cSnr < 220)
			{
				cSnr -= 1;
			}
			
		}
		else
		{
			if ( cSnr > 197 )
			{
				cSnr += 2;
			}
			else if (cSnr >= 190)
			{
				cSnr +=3;
			}
			else
			{
				cSnr +=1;
			}
		}
	}
	else
	{
		DEMOD_PRINT("SNR original value \n");
	}

	return cSnr;
}

static UINT32 _DEMOD_DVB_DVBC_GetSnr(LX_DEMOD_SIGNAL_CTX_T* sigStatus)
{
	UINT32			cSnr;
	UINT16 			mse;
	UINT32			constPwr;
	UINT32 			calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	mse 	= sigStatus->m.mse;
	constPwr 	= sigStatus->m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}
	if (constPwr == 1)
	{
		calcValue =  (UINT32)65536 / ((UINT32) mse);
		if (calcValue == 0)
		{
			DEMOD_PRINT("Over mse value (mse = %d)	\n" ,mse);

			calcValue = 1;
		}
		temp_snr 	= intlog10(calcValue);
		temp_snr 	= temp_snr * 100;
		cSnr 		= (UINT32)(temp_snr >> 24);
		DEMOD_PRINT("mse = %d, (original cSnr = %d) \n" ,mse,cSnr);
		if (cSnr > 340)
		{
			cSnr = cSnr + 10;
		}
		else
		{
			cSnr = cSnr + 20;
		}

		DEMOD_PRINT("Adjusted cSnr = %d \n" ,cSnr);

	}
	else
	{
		calcValue =  (UINT32)constPwr / ((UINT32)(mse * 4));
		if (calcValue == 0)
		{
			DEMOD_PRINT("Over mse value (mse = %d)	\n" ,mse);

			calcValue = 1;
		}
		temp_snr 	= intlog10(calcValue);
		temp_snr 	= temp_snr * 100;
		cSnr 		= (UINT32)(temp_snr >> 24);
		DEMOD_PRINT("mse = %d, constPwr = %d,(original cSnr = %d) \n",mse,constPwr,cSnr);

		if (LX_DEMOD_QPSK == sigStatus->rfMode)
		{
			if (cSnr > 200)
			{
				cSnr = cSnr + 90;
			}
			else if ((cSnr <= 200) && (cSnr > 5 ))
			{
				cSnr = cSnr + 80;
			}
			else if (cSnr <= 5)
			{
				cSnr = 0;
			}
		}
		else
		{
			if (cSnr > 200)
			{
				cSnr = cSnr + 80;
			}
			else if ((cSnr <= 200) && (cSnr > 132 ))
			{
				cSnr = cSnr + 70;
			}
			else if ((cSnr <= 132) && (cSnr > 121 ))
			{
				cSnr = cSnr + 70;
			}
			else if ((cSnr <= 121) && (cSnr > 113 ))
			{
				cSnr = cSnr + 60;
			}
			else if (cSnr <= 113)
			{
				cSnr = cSnr + 60;
			}
		}
		DEMOD_PRINT("DVBC adjusted cSnr = %d\n",cSnr);
	}
	return cSnr;
}


static UINT32 _DEMOD_DVB_DVBS_GetSnr(LX_DEMOD_SIGNAL_CTX_T* sigStatus)
{
	UINT32		cSnr;
	UINT16 		mse;
	UINT32		constPwr;
	UINT32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	mse 	= sigStatus->m.mse;
	constPwr 	= sigStatus->m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}
	if (constPwr == 0)
	{
		DEMOD_PRINT("Fail to get the constPwr value(constPwr = %d) \n",constPwr);
		constPwr = 1024;
	}


	calcValue 	=  (UINT32)constPwr / ((UINT32)(mse * 4));
	if (calcValue == 0)
	{
		calcValue = 1;
	}
	DEMOD_PRINT("calcValue = %d , constPwr = %d , mse = %d \n",calcValue, constPwr, mse);
	temp_snr 	= intlog10(calcValue);
	temp_snr 	= temp_snr * 100;
	cSnr 		= (UINT32)(temp_snr >> 24);
	DEMOD_PRINT("mse = %d, constPwr = %d (original pSNR = %d) \n",mse,constPwr,cSnr);

	if (cSnr > 130)
	{
		cSnr = cSnr + 90;
	}
	else
	{
		cSnr = cSnr + 80;
	}
	DEMOD_PRINT("adjusted cSnr = %d \n",cSnr);


	return cSnr;
}

static UINT32 _DEMOD_DVB_DTMB_GetSnr(LX_DEMOD_SIGNAL_CTX_T* sigStatus)
{
	UINT32		cSnr;
	UINT16		mse;
	UINT32		constPwr;
	UINT32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	mse 	= sigStatus->m.mse;
	constPwr = sigStatus->m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}

	if (constPwr == 0)
	{
		DEMOD_PRINT("Fail to get the constPwr value(constPwr = %d) \n",constPwr);
		constPwr = 65536;
	}

	calcValue =  (UINT32)constPwr / ((UINT32)(mse * 4));
	DEMOD_PRINT("calcValue = %d \n",calcValue);

	if (calcValue==0)
	{
		cSnr = 0;
		DEMOD_PRINT("check dtmb mse value [%d]\n", mse);
	}
	else
	{
		temp_snr 	= intlog10(calcValue);
		temp_snr 	= temp_snr * 100;
		cSnr 		= (UINT32)(temp_snr >> 24);
	}

	DEMOD_PRINT("mse = %d, constPwr = %d (original pSNR = %d) \n",mse,constPwr,cSnr);
	if (cSnr > 340)
	{
		cSnr = cSnr + 10;
	}
	else
	{
		cSnr = cSnr + 20;
	}
	DEMOD_PRINT("adjusted pSnr = %d \n",cSnr);

	return cSnr;
}

static KHAL_RETURN_VALUE_T _KHAL_DEMOD_TunePostJob(BOOLEAN *pFinished)
{
	BOOLEAN			notifiedStatus;
	LX_DEMOD_LOCK_STATE_T	demodLock = LX_DEMOD_UNKOWN_STATE;

	if (RET_OK != KHAL_Get_DEMOD_NotifiedStatus(&notifiedStatus))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_NotifiedStatus()\n");
		return KHAL_NOK;
	}

	if (TRUE == notifiedStatus)
	{
		if (RET_OK != KHAL_Get_DEMOD_NotifiedLock(&demodLock))	/*	fecLock status */
		{
			DEMOD_NOTI("fail, KHAL_Get_DEMOD_NotifiedLock()\n");
			return KHAL_NOK;
		}

		if (LX_DEMOD_LOCKED == demodLock )
		{
			*pFinished	= TRUE;
			printk("POST JOB: tune post job lock ok\n");
		}
		else
		{
			*pFinished	= TRUE;
			printk("POST JOB: tune post job not lock ok\n");
		}
	}
	else
	{
		*pFinished = FALSE;
	}

	return KHAL_OK;

}

static KHAL_RETURN_VALUE_T _KHAL_DEMOD_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	LX_DEMOD_LOCK_STATE_T	demodLock = LX_DEMOD_UNKOWN_STATE;

	if (RET_OK != KHAL_Get_DEMOD_NotifiedLock(&demodLock))	/*	fecLock status */
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_NotifiedLock()\n");
		return KHAL_NOK;
	}

	if (LX_DEMOD_LOCKED == demodLock)
	{
		*pLockState = KHAL_DEMOD_LOCK_OK;
		DEMOD_PRINT("CheckLock: LOCK\n");
	}
	else
	{
		*pLockState = KHAL_DEMOD_LOCK_FAIL;
		DEMOD_PRINT("CheckLock: UNLOCK\n");
	}

	return KHAL_OK;
}

static KHAL_RETURN_VALUE_T _KHAL_DEMOD_GetSpecialData(LX_DEMOD_CONFIG_T * pChannelParams)
{
	/* Check Specia Data with the specified parameters. */
	LX_DEMOD_LOCK_STATE_T	demodLock = LX_DEMOD_UNKOWN_STATE;
	BOOLEAN			notifiedStatus;

	if (pChannelParams == NULL) return KHAL_NOK;

	if (KHAL_OK != KHAL_Get_DEMOD_NotifiedStatus(&notifiedStatus))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_NotifiedStatus()\n");
		return KHAL_NOK;
	}
	else
	{
		if (TRUE == notifiedStatus)
		{
			if (RET_OK != KHAL_Get_DEMOD_NotifiedLock(&demodLock))	/*	fecLock status */
			{
				DEMOD_WARN("fail, KHAL_Get_DEMOD_NotifiedLock()\n");
				return KHAL_NOK;
			}
		}
		else
		{
			return	KHAL_NOK;
		}
	}

	if (LX_DEMOD_LOCKED != demodLock)
	{
		DEMOD_PRINT("CheckLock: UNLOCK \n");
		return KHAL_NOK;
	}

	if (KHAL_OK != KHAL_Get_DEMOD_ChannelPara(pChannelParams))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_ChannelPara()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}

static KHAL_RETURN_VALUE_T _KHAL_DEMOD_ChangeTransSystem(LX_DEMOD_INIT_PARAM_T * pMediaChageParams)
{
	UINT32	curr_t, elapsed_t;
	curr_t = (UINT32)jiffies_to_msecs(jiffies);

	do {
		if (FALSE == KHAL_DEMOD_Ioremap())
		{
			DEMOD_NOTI("wait ioremap...\n");
			elapsed_t = (UINT32)jiffies_to_msecs(jiffies) - curr_t;
			if ( elapsed_t >= 100 )
			{
				DEMOD_WARN("ioremap is fail, elapesd %d ms\n", elapsed_t);
				break;
			}
			usleep_range(1000,3000);	/* 1ms ~ 10ms */
		}
		else
		{
			DEMOD_NOTI("check ioremap is done\n");
		}
	} while (TRUE != KHAL_DEMOD_Ioremap());

	do {
		if (FALSE == KHAL_DEMOD_FWdn())
		{
			DEMOD_NOTI("wait fwdn...");
			elapsed_t = (UINT32)jiffies_to_msecs(jiffies) - curr_t;
			if ( elapsed_t >= 300 )
			{
				DEMOD_NOTI("fwdn is fail, elapesd %d ms\n", elapsed_t);
				break;
			}
			usleep_range(10000,11000);	/* 1ms ~ 10ms */
		}
		else
		{
			DEMOD_NOTI("check fwdn is done\n");
		}
	} while (TRUE != KHAL_DEMOD_FWdn());

	if (KHAL_OK != KHAL_DEMOD_MediaChange(pMediaChageParams))
	{
		DEMOD_WARN("fail, KHAL_DEMOD_MediaChange()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}

///////////////////////////////////////////VQI///////////////////////////////////////////////////////////
KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_Initialize(void)
{
	unsigned int elapsedTime = jiffies_to_msecs(jiffies);
	KHAL_DEMOD_PanamaOn(FALSE);

	if (KHAL_OK != DEMOD_ResetHW())
	{
		DEMOD_WARN("fail, DEMOD_ResetHW()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS DEMOD_ResetHW()\n");

	usleep_range(20000,23000);	/* 3ms ~ 10ms */

	if (KHAL_OK != KHAL_DEMOD_Init())
	{
		DEMOD_NOTI("fail KHAL_DEMOD_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS KHAL_DEMOD_Init()\n");

	if (KHAL_OK != DEMOD_I2C_open(7,0xB2))
	{
		DEMOD_NOTI("fail DEMOD_I2C_open()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("SUCCESS DEMOD_I2C_open()\n");

	if (KHAL_OK != DEMOD_ATSC_SW_Init())
	{
		DEMOD_NOTI("fail DEMOD_ATSC_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_ATSC_SW_Init()\n");

	if (KHAL_OK != DEMOD_FW_Initialize())
	{
		DEMOD_NOTI("fail DEMOD_FW_Initialize()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_FW_Initialize()\n");

	DEMOD_NOTI("elapsed %d ms\n", jiffies_to_msecs(jiffies) - elapsedTime);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_Initialize);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ChangeTransSystem(KHAL_DEMOD_TRANS_SYSTEM_T transSystem)
{
	LX_DEMOD_INIT_PARAM_T 	mediaChageParams;

	if (transSystem == KHAL_DEMOD_TRANS_SYS_ISDBT)   // brazil or japen ISDBT
	{
		mediaChageParams.operMode 	= LX_DEMOD_ISDBT;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_QAM_NO_OPERATION_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq 		= LX_DEMOD_IF_FREQ_05_000_KHZ;
		DEMOD_NOTI("Transmedia is ISDBT\n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_VSB)
	{
		mediaChageParams.operMode 	= LX_DEMOD_ATSC;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_QAM_NO_OPERATION_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq 		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("Transmedia is VSB\n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_QAM)
	{
		mediaChageParams.operMode	= LX_DEMOD_QAM;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_VSB_NO_OPERATION;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("Transmedia is QAM \n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_ALWAYSREADY)
	{
		mediaChageParams.operMode	= LX_DEMOD_ALWAYSREADY;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_VSB_NO_OPERATION;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("Transmedia is LX_DEMOD_ALWAYSREADY \n");
	}
	else
	{
		mediaChageParams.operMode	= LX_DEMOD_DIGITAL_Sleep;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_VSB_NO_OPERATION;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;
	
		DEMOD_NOTI("TransSystem = 0x%02x\n",transSystem);
	}

	return _KHAL_DEMOD_ChangeTransSystem(&mediaChageParams);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ChangeTransSystem);

#if 1
KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_CheckSignalStatus(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	/*Check signal state with the specified parameters*/
	UINT32		cSnr = 0;
	UINT16		mse;
	UINT32		constPwr;
	u32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	LX_DEMOD_SIGNAL_CTX_T sigCtx;


	DEMOD_PRINT("Start \n");

	if (NULL == pSignalState)
	{
		DEMOD_PRINT("FAIL, pSignalState is NULL\n");
		return KHAL_NOK;
	}

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_PRINT("FAIL, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (sigCtx.bSignalValid == FALSE )
	{
		cSnr = 0xffffffff;
		DEMOD_PRINT("The Signal is NOT LOCKED. next time ......try\n");
	}

	mse 	= sigCtx.m.mse;
	constPwr = sigCtx.m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}

	switch (sigCtx.operMode)
	{
		case LX_DEMOD_QAM: {
		#if 1
				calcValue =  (u32)constPwr / ((u32)(mse));
				if (calcValue==0)
				{
					cSnr = 0;
					DEMOD_NOTI("check LX_DEMOD_QAM mse value ... mse[%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 10;
					cSnr = (u32)(temp_snr >> 24);
				}
		#endif
				if (sigCtx.rfMode == LX_DEMOD_64QAM) {
					DEMOD_PRINT("64QAM constPwr[%d] mse[%d] cSnr = %d \n", constPwr, mse,cSnr);
				}
				else	// 256 QAM
				{
					DEMOD_PRINT("256QAM  cSnr = %d \n",cSnr);
				}
				DEMOD_PRINT("QAM adjusted pSnr = %d\n" ,cSnr);
			}
			break;

		case LX_DEMOD_ATSC: {
				calcValue =  (u32)constPwr / ((u32)(mse*4));
				if (calcValue == 0)
				{
					cSnr = 0;
					DEMOD_NOTI("check LX_DEMOD_ATSC(vsb) mse value ... mse[%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 100;
					cSnr = (u32)(temp_snr >> 24);
				}
				DEMOD_PRINT("VSB cSnr = %d\n",cSnr);

				if (cSnr <= 116)			cSnr = (cSnr / 10) + 4;
				else if (cSnr <= 120)		cSnr = (cSnr / 10) + 5;
				else if (cSnr <= 124)		cSnr = (cSnr / 10) + 6;
				else if (cSnr <= 140)		cSnr = (cSnr / 10) + 7;
				else if (cSnr >= 250)		cSnr = (cSnr / 10) + 15;
				else				cSnr = (cSnr / 10) + 8;

				DEMOD_PRINT("VSB adjusted pSnr = %d \n",cSnr);

			}
			break;

		case LX_DEMOD_ISDBT:
			{
			#if 1

				calcValue =  (u32)constPwr / ((u32)(mse));
				if (calcValue==0)
				{
					cSnr = 0;
					DEMOD_NOTI("check LX_DEMOD_ISDBT mse value ... mse[%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 10;
					cSnr = (u32)(temp_snr >> 24);
		}
			#endif

			DEMOD_PRINT("ISDBT mse = %d, constPwr = %d,(original cSnrR = %d) \n",mse,constPwr,cSnr);

			}
			break;

		default:
				break;

	}

	pSignalState->bSignalValid	= sigCtx.bSignalValid;
	pSignalState->packetError	= sigCtx.packetError;
	pSignalState->unBER 		= sigCtx.ber;
	pSignalState->unAGC 		= sigCtx.agc;
	pSignalState->unSNR 		= cSnr;	// check later
	pSignalState->quality		= 0;	// check later

	DEMOD_PRINT("Packet Error[%d] \n", pSignalState->packetError);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_CheckSignalStatus);

#endif



KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetPacketError(UINT32 *pPacketError)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}
	*pPacketError = sigCtx.packetError;

	DEMOD_PRINT("PacketError: %u\n", *pPacketError);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetPacketError);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetBER(UINT32 *pBER)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}
	*pBER = sigCtx.ber;

	DEMOD_PRINT("BER: %u\n", *pBER);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetBER);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetAGC(UINT32 *pAGC)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}
	*pAGC = sigCtx.agc;

	DEMOD_PRINT("AGC: %u\n", *pAGC);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetAGC);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetSNR (UINT32 *pSNR)
{
	UINT16		mse;
	UINT32		constPwr;
	u32		 calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (sigCtx.bSignalValid == FALSE )
	{
		*pSNR = 0xffffffff;
		DEMOD_NOTI("The Signal is NOT LOCKED. next time ......try \n");
		return KHAL_NOK;
	}

	mse = sigCtx.m.mse;
	constPwr = sigCtx.m.constPwr;

	if (mse == 0)
	{
		mse = 1;
	}

	//*pSNR = 0;
	DEMOD_PRINT("check KHAL SNR[%d]\n", *pSNR);

	switch (sigCtx.operMode)
	{
		case LX_DEMOD_QAM:
			{
				calcValue =  (u32)constPwr / ((u32)(mse));
				if (calcValue==0)
				{
					*pSNR = 0;
					DEMOD_NOTI("check mse value [%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 10;
					*pSNR = (u32)(temp_snr >> 24);
				}

				DEMOD_PRINT("bMse = %d, constPwr = %d,(original pSNR = %d) \n",mse,constPwr,*pSNR);
			}
			break;

		case LX_DEMOD_ATSC:
			{

				calcValue =  (u32)constPwr / ((u32)(mse*4));
				if (calcValue==0)
				{
					*pSNR = 0;
					DEMOD_NOTI("check mse value [%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 100;
					*pSNR = (u32)(temp_snr >> 24);
				}

				if (*pSNR <=116)
				{
					*pSNR = (*pSNR /10) + 3;

				}
				else if ( *pSNR<=120)
				{
					*pSNR = (*pSNR /10) + 4;
				}
				else if ( *pSNR<=124)
				{
					*pSNR = (*pSNR /10) + 5;
				}
				else if ( *pSNR<=140)
				{
					*pSNR = (*pSNR /10) + 6;
				}
				else
				{
					*pSNR = (*pSNR /10) + 7;
				}
				DEMOD_PRINT("VSB adjusted pSnr = %d \n",*pSNR);
			}
			break;

		case LX_DEMOD_ISDBT:
			{
				calcValue =  (u32)constPwr / ((u32)(mse));
				if (calcValue==0)
				{
					*pSNR = 0;
					DEMOD_NOTI("check mse value [%d]\n", mse);
				}
				else
				{
					temp_snr = intlog10(calcValue);
					temp_snr = temp_snr * 10;
					*pSNR = (u32)(temp_snr >> 24);
				}

			}
			break;

		default:
			break;

	}


	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetSNR);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetSQI(UINT8 *pSQI)
{
	/*Gets SQI.*/

	UINT32	ber;
	UINT16	ubc;
	UINT8 	quality = 0;
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_PRINT("FAIL, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	// ======== BER base  ============
	ber = sigCtx.ber;
	ubc = sigCtx.packetError;

	// LOCKED
	if (sigCtx.bSignalValid == TRUE)
	{
		 ber = ber/100;		// e-5

		if (0 == ubc)
		{
			if (ber <= 20)			// 100 ~ 90	2.0x10e-4
				quality = (int)((200 - ber) >> 1);

			else if (ber <= 260)		// 90 ~ 30	26.0x10e-4
				quality = (int)( 90 - ((ber - 20) >> 2));

			else if (ber <= 340)		// 30 ~ 20
				quality = (int)( 30 - ((ber - 260) >> 3));

			else
				quality = 20;

		}

		else if (ubc < 10)
		{
			quality = 20 - ubc / 2;		// 20 ~ 15
		}

		else if (ubc < 30)
		{
			quality = 12 - ((ubc - 10) / 4);		// 15 ~ 10
		}

		else if (ubc < 70)
		{
			quality = 10 - ((ubc - 30) / 10);		// 10 ~ 6
		}

		else if (ubc < 326)
		{
			quality = 5 - ((ubc - 56) / 64);		// 6 ~ 2
		}
		else
		{
			quality = 1;
		}
	}
	else
	{
		quality = 0;
	}

	*pSQI = quality;

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetSQI);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_GetFWVersion(UINT32 *pFWVersion)
{
	if (KHAL_OK != DEMOD_Get_FW_PartInfo(pFWVersion))
	{
		DEMOD_WARN("fail, DEMOD_Get_FW_PartInfo()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_GetFWVersion);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_CheckFrequencyOffset(SINT32 *pFreqOffset)
{
	if (KHAL_OK != DEMOD_Get_CarrierFreqOffset(pFreqOffset))
	{
		DEMOD_WARN("fail, DEMOD_Get_CarrierFreqOffset() \n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_CheckFrequencyOffset);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ControlTSMode( BOOLEAN bIsSerial)
{
	if (KHAL_OK != DEMOD_Serial_Control(bIsSerial))
	{
		DEMOD_WARN("fail, DEMOD_Serial_Control()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ControlTSMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ControlOutput(BOOLEAN bEnableOutput)
{
	if (KHAL_OK != DEMOD_TPOutCLKEnable(bEnableOutput))
	{
		DEMOD_WARN("fail, DEMOD_TPOutCLKEnable()\n");
		return KHAL_NOK;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ControlOutput);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_Set_Frame_resynchronizaiton(BOOLEAN bEnable)
{
	if (KHAL_OK != DEMOD_Set_Frame_resynchronizaiton(bEnable))
	{
		DEMOD_WARN("fail, DEMOD_Set_Frame_resynchronizaiton()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_Set_Frame_resynchronizaiton);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ATSC_SetDemod(KHAL_DEMOD_ATSC_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	/* Set registers of VSB mode */
	if (paramStruct.transSystem == KHAL_DEMOD_TRANS_SYS_VSB)
	{
		configParams.operMode		= LX_DEMOD_ATSC;
		configParams.vsb.bSpectrumInv	= FALSE;
		configParams.vsb.channelBW	= LX_DEMOD_BW_6MHZ;
		configParams.vsb.tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL : LX_DEMOD_TUNE_AUTO ;

		DEMOD_PRINT("Set Decoder for VSB\n");

	}/* Set registers of QAM mode */
	else
	{
		configParams.operMode		= LX_DEMOD_QAM;
		configParams.qam.bSpectrumInv	= paramStruct.bSpectrumInv;
		configParams.qam.channelBW	= LX_DEMOD_BW_6MHZ;
		configParams.qam.qamMode	= (paramStruct.constellation == KHAL_DEMOD_TPS_CONST_QAM_64) ? LX_DEMOD_64QAM : LX_DEMOD_256QAM;
		configParams.qam.tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL : LX_DEMOD_TUNE_AUTO ;

		DEMOD_PRINT("Set Decoder for QAM \n");
	}

	if (KHAL_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_WARN("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ATSC_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_SetDemod(KHAL_DEMOD_ISDBT_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	configParams.operMode			= LX_DEMOD_ISDBT;
	configParams.isdbt.bSpectrumInv 	= FALSE;
	configParams.isdbt.channelBW		= LX_DEMOD_BW_6MHZ;
	configParams.isdbt.FFTMode		= LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
	configParams.isdbt.gIMode		= LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
	configParams.isdbt.tuneMode 		= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL : LX_DEMOD_TUNE_AUTO;

	if (KHAL_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_WARN("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_TunePostJob);

BOOLEAN KHAL_DEMOD_VQI_ISDBT_GetEmergencyAlertFlagStatus(void)
{
	/*return emegency flag status;*/
	BOOLEAN bEalarm;

	if (KHAL_OK != DEMOD_ISDBT_GetEmergencyAlertFlagStatus(&bEalarm))
	{
		DEMOD_WARN("fail, DEMOD_ISDBT_GetEmergencyAlertFlagStatus()\n");
		return KHAL_NOK;
	}

	return bEalarm;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_GetEmergencyAlertFlagStatus);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_CheckSpecialData(KHAL_DEMOD_SPECDATA_ISDBT_T *pSpecData)
{
	/* Check Specia Data with the specified parameters. */
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	/* 4.6.2.9 TRANSMISSION MODE */
	if (channelParams.isdbt.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_2K)			pSpecData->carrierMode = KHAL_DEMOD_TPS_CARR_2K;
	else if (channelParams.isdbt.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_4K)		pSpecData->carrierMode = KHAL_DEMOD_TPS_CARR_4K;
	else if (channelParams.isdbt.FFTMode == LX_DEMOD_DVBT_ISDBT_FFT_8K)		pSpecData->carrierMode = KHAL_DEMOD_TPS_CARR_8K;
	else										pSpecData->carrierMode = KHAL_DEMOD_TPS_CARR_UNKNOWN;

	/* 4.6.2.8 GUARD INTERVALS */
	if (channelParams.isdbt.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_32)		pSpecData->guardInterval = KHAL_DEMOD_TPS_GUARD_1_32;
	else if (channelParams.isdbt.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_16)		pSpecData->guardInterval = KHAL_DEMOD_TPS_GUARD_1_16;
	else if (channelParams.isdbt.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_8)		pSpecData->guardInterval = KHAL_DEMOD_TPS_GUARD_1_8;
	else if (channelParams.isdbt.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_1_4)		pSpecData->guardInterval = KHAL_DEMOD_TPS_GUARD_1_4;
	else										pSpecData->guardInterval = KHAL_DEMOD_TPS_GUARD_UNKNOWN;

	if (channelParams.isdbt.tmcc.layerASegmentNum>channelParams.isdbt.tmcc.layerBSegmentNum)
	{
		if (channelParams.isdbt.tmcc.layerASegmentNum>channelParams.isdbt.tmcc.layerCSegmentNum)
		{
			//A
			if (channelParams.isdbt.tmcc.layerAQamMode== LX_DEMOD_QPSK)		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QPSK;
			else if (channelParams.isdbt.tmcc.layerAQamMode == LX_DEMOD_16QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_16;
			else if (channelParams.isdbt.tmcc.layerAQamMode == LX_DEMOD_64QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
			else									pSpecData->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;

			if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_1_2)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_2_3)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_3_4)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_3_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_5;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_4_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_4_5;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_5_6)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
			else if (channelParams.isdbt.tmcc.layerACodeRate == LX_DEMOD_CODE_7_8)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
			else									pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
		}
		else
		{
			//C
			if (channelParams.isdbt.tmcc.layerCQamMode== LX_DEMOD_QPSK)		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QPSK;
			else if (channelParams.isdbt.tmcc.layerCQamMode == LX_DEMOD_16QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_16;
			else if (channelParams.isdbt.tmcc.layerCQamMode == LX_DEMOD_64QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
			else									pSpecData->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;

			if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_1_2)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_2_3)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_3_4)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_3_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_5;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_4_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_4_5;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_5_6)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
			else if (channelParams.isdbt.tmcc.layerCCodeRate == LX_DEMOD_CODE_7_8)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
			else									pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
		}
	}
	else
	{
		if (channelParams.isdbt.tmcc.layerBSegmentNum>channelParams.isdbt.tmcc.layerCSegmentNum)
		{
		 	//B
			if (channelParams.isdbt.tmcc.layerBQamMode== LX_DEMOD_QPSK)		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QPSK;
			else if (channelParams.isdbt.tmcc.layerBQamMode == LX_DEMOD_16QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_16;
			else if (channelParams.isdbt.tmcc.layerBQamMode == LX_DEMOD_64QAM)	pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
			else									pSpecData->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;

			if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_1_2)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_1_2;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_2_3)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_2_3;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_3_4)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_4;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_3_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_3_5;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_4_5)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_4_5;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_5_6)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_5_6;
			else if (channelParams.isdbt.tmcc.layerBCodeRate == LX_DEMOD_CODE_7_8)	pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_7_8;
			else									pSpecData->codeRate = KHAL_DEMOD_TPS_CODE_UNKNOWN;
		}
	}

	/* ETC PRIORITY */
	pSpecData->bSpectrumInv = channelParams.isdbt.bSpectrumInv;

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_CheckFrequencyOffset(SINT32 *pFreqOffset)
{
	if (KHAL_OK != DEMOD_Get_CarrierFreqOffset(pFreqOffset))
	{
		DEMOD_WARN("fail, DEMOD_Get_CarrierFreqOffset()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_CheckFrequencyOffset);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_CheckSignalStatus(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	UINT32		cSnr;
	UINT16		mse;
	UINT32		constPwr;
	u32 		calcValue;
	UINT64 		temp_snr = 0x0000000000000000L;

	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (NULL == pSignalState)
	{
		DEMOD_WARN("fail, pSignalState is NULL\n");
		return KHAL_NOK;
	}

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (sigCtx.bSignalValid == FALSE )
	{
//		cSnr = 0xffffffff;
		DEMOD_PRINT("The Signal is NOT LOCKED. next time ......try \n");

	}

	mse = sigCtx.m.mse;
	constPwr = sigCtx.m.constPwr;

	if (mse == 0)
	{
//		DEMOD_PRINT("Fail to get the MSE value(mse = %d) \n",mse);
		mse = 1;
	}

	calcValue =  (u32)constPwr / ((u32)(mse));
	if (calcValue==0)
	{
		cSnr = 0;
		DEMOD_PRINT("check mse value [%d] \n", mse);
	}
	else
	{
		temp_snr = intlog10(calcValue);
		temp_snr = temp_snr * 10;
		cSnr = (u32)(temp_snr >> 24);
	}

	cSnr += 1;

	DEMOD_PRINT("mse = %d, constPwr = %d,(original cSnrR = %d) \n",mse,constPwr,cSnr);

	pSignalState->bSignalValid 	= sigCtx.bSignalValid;
	pSignalState->packetError 	= sigCtx.packetError;

	pSignalState->unBER		= sigCtx.ber;
	pSignalState->unAGC		= sigCtx.agc;
	pSignalState->unSNR		= cSnr;	// check later
	pSignalState->quality		= 0;	// check later
	DEMOD_PRINT("Packet Error = [%d]\n", pSignalState->packetError );

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_CheckSignalStatus);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_ControlOutput(BOOLEAN bEnableOutput)
{
	if (KHAL_OK != DEMOD_TPOutCLKEnable(bEnableOutput))
	{
		DEMOD_WARN("fail, DEMOD_TPOutCLKEnable()\n");
		return KHAL_NOK;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_ControlOutput);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_Initialize(void)
{
	unsigned int elapsedTime = jiffies_to_msecs(jiffies);
	KHAL_DEMOD_PanamaOn(FALSE);	

	if (KHAL_OK != DEMOD_ResetHW())
	{
		DEMOD_WARN("fail, DEMOD_ResetHW()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS DEMOD_ResetHW()\n");
	usleep_range(20000,23000);	/* 3ms ~ 10ms */

	if (KHAL_OK != KHAL_DEMOD_Init())
	{
		DEMOD_WARN("fail, KHAL_DEMOD_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS KHAL_DEMOD_Init()\n");

	if (KHAL_OK != DEMOD_I2C_open(7,0xB2))
	{
		DEMOD_WARN("fail, DEMOD_I2C_open()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("SUCCESS DEMOD_I2C_open()\n");


	if (KHAL_OK != DEMOD_ATSC_SW_Init())
	{
		DEMOD_WARN("fail, DEMOD_ATSC_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_ATSC_SW_Init()\n");

	if (KHAL_OK != DEMOD_FW_Initialize())
	{
		DEMOD_WARN("fail, DEMOD_FW_Initialize()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_FW_Initialize()\n");

	DEMOD_NOTI("elapsed %d ms\n", jiffies_to_msecs(jiffies) - elapsedTime);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_Initialize);


KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_ChangeTransSystem (KHAL_DEMOD_TRANS_SYSTEM_T transSystem)
{
	LX_DEMOD_INIT_PARAM_T 	mediaChageParams;

	if (transSystem == KHAL_DEMOD_TRANS_SYS_ISDBT)   // brazil or japen ISDBT
	{
		mediaChageParams.operMode 	= LX_DEMOD_ISDBT;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_QAM_NO_OPERATION_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq 		= LX_DEMOD_IF_FREQ_05_000_KHZ;

		DEMOD_NOTI("Transmedia is ISDBT\n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_ALWAYSREADY)   // brazil or japen ISDBT
	{
		mediaChageParams.operMode 	= LX_DEMOD_ALWAYSREADY;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_VSB_NO_OPERATION;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("Transmedia is ISDBT\n");
	}
	else
	{
		mediaChageParams.operMode	= LX_DEMOD_DIGITAL_Sleep;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_VSB_NO_OPERATION;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;
		
		DEMOD_NOTI("TransSystem is Unknown (0x%02x)\n",transSystem);
	}

	return _KHAL_DEMOD_ChangeTransSystem(&mediaChageParams);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_ChangeTransSystem);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_ISDBT_ControlTSMode (BOOLEAN bIsSerial)
{
	DEMOD_PRINT("bIsSerial = %d \n", bIsSerial);

	if (KHAL_OK != DEMOD_Serial_Control(bIsSerial))
	{
		DEMOD_PRINT("FAIL, DEMOD_Serial_Control()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_ISDBT_ControlTSMode );

KHAL_RETURN_VALUE_T KHAL_DEMOD_ISDBT_DebugMenu(void)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ISDBT_DebugMenu);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_VSB_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_VSB_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_VSB_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_VSB_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_QAM_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_QAM_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_QAM_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_QAM_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_QAM_CheckSpecialData(KHAL_DEMOD_SPECDATA_QAM_T *pSpecData)
{
	/* Check Specia Data with the specified parameters. */
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	pSpecData->bSpectrumInv = channelParams.qam.bSpectrumInv;

	if (LX_DEMOD_256QAM == channelParams.qam.qamMode)
	{
		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_256;
		DEMOD_PRINT("Constellation = KHAL_DEMOD_TPS_CONST_QAM_256\n");
	}
	else if (LX_DEMOD_64QAM == channelParams.qam.qamMode)
	{
		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_QAM_64;
		DEMOD_PRINT("Constellation = KHAL_DEMOD_TPS_CONST_QAM_64\n");
	}
	else
	{
		pSpecData->constellation = KHAL_DEMOD_TPS_CONST_UNKNOWN;
		DEMOD_PRINT("Constellation = UNKNOWN \n");
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_QAM_CheckSpecialData);

#if 1
KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DebugMenu (void)
{
	DEMOD_INFO("N/A\n");
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DebugMenu);
#endif


KHAL_RETURN_VALUE_T KHAL_DEMOD_SetI2C(void *client)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_SetI2C);

///////////////////////////////////////////DVB///////////////////////////////////////////////////////////

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_Initialize(void)
{
	unsigned int elapsedTime = jiffies_to_msecs(jiffies);
	KHAL_DEMOD_PanamaOn(FALSE);

	if (KHAL_OK != DEMOD_ResetHW())
	{
		DEMOD_WARN("fail, DEMOD_ResetHW()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS DEMOD_ResetHW()\n");
	usleep_range(20000,23000);	/* 3ms ~ 10ms */

	if (KHAL_OK != KHAL_DEMOD_Init())
	{
		DEMOD_WARN("fail, KHAL_DEMOD_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS KHAL_DEMOD_Init()\n");

	if (KHAL_OK != DEMOD_I2C_open(7,0xB2))
	{
		DEMOD_WARN("fail, DEMOD_I2C_open()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("SUCCESS DEMOD_I2C_open()\n");

	if (KHAL_OK != DEMOD_DVB_SW_Init())
	{
		DEMOD_WARN("fail, DEMOD_DVB_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_DVB_SW_Init()\n");

	if (KHAL_OK != DEMOD_FW_Initialize())
	{
		DEMOD_WARN("fail, DEMOD_FW_Initialize()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_FW_Initialize()\n");

	DEMOD_NOTI("elapsed %d ms\n", jiffies_to_msecs(jiffies) - elapsedTime);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_Initialize);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_ChangeTransMedia(KHAL_DEMOD_TRANS_SYSTEM_T transSystem)
{
	UINT32 			ifFrq = LX_DEMOD_IF_FREQ_05_000_KHZ;  //TU_IF_FREQ_04_560_KHZ;
	LX_DEMOD_INIT_PARAM_T 	mediaChageParams;

	if (transSystem == KHAL_DEMOD_TRANS_SYS_DVBT || transSystem == KHAL_DEMOD_TRANS_SYS_DVBT2 )
	{
		mediaChageParams.operMode 	= LX_DEMOD_DVBT;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_DVBC_NO_OPERATION_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_8MHZ;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is DVB-T or DVB-T2 \n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_DVBC)
	{
		mediaChageParams.operMode 	= LX_DEMOD_DVBC;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_DVBT_NO_OPERATION;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is DVB-C \n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_DVBS || transSystem == KHAL_DEMOD_TRANS_SYS_DVBS2)
	{
		mediaChageParams.operMode 	= LX_DEMOD_DVBS;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_DVBS_NO_OPERATION_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_DVBS_NO_OPERATION;
		mediaChageParams.ifFrq 		= 0;

		DEMOD_NOTI("TransSystem is DVB-S or DVB-S2 \n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_ALWAYSREADY)
	{
		mediaChageParams.operMode 	= LX_DEMOD_ALWAYSREADY;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_DVBT_NO_OPERATION;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is LX_DEMOD_ALWAYSREADY \n");
	}
	else
	{
		mediaChageParams.operMode 	= LX_DEMOD_DIGITAL_Sleep;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_DVBT_NO_OPERATION;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is UNKNOWN (0x%02x)\n", transSystem);
	}

	return _KHAL_DEMOD_ChangeTransSystem(&mediaChageParams);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_ChangeTransMedia);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_CheckFrequencyOffset(SINT32 *pFreqOffset)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pFreqOffset = sigCtx.offsetFrq_Hz;

	DEMOD_PRINT("Frequency Offset = %d\n", *pFreqOffset);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_CheckFrequencyOffset);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_GetPacketError(UINT32 *pPacketError)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pPacketError = sigCtx.packetError ;

	DEMOD_PRINT("Packet Error = %d \n",*pPacketError);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_GetPacketError);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_OperMode(KHAL_DEMOD_TRANS_SYSTEM_T *pOperMode)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	switch (sigCtx.operMode)
	{
		case LX_DEMOD_DVBT:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBT;
				DEMOD_PRINT("Operation mode = %s \n", "DVBT");
			}
			break;
		case LX_DEMOD_DVBT2:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBT2;
				DEMOD_PRINT("Operation mode = %s\n", "DVBT2");
			}
			break;
		case LX_DEMOD_DVBC:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBC;
				DEMOD_PRINT("Operation mode = %s\n", "DVBC");
			}
			break;
		case LX_DEMOD_DVBC2:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBC2;
				DEMOD_PRINT("Operation mode = %s\n", "DVBC2");
			}
			break;
		case LX_DEMOD_DVBS:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBS;
				DEMOD_PRINT("Operation mode = %s\n", "DVBS");
			}
			break;
		case LX_DEMOD_DVBS2:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_DVBS2;
				DEMOD_PRINT("Operation mode = %s\n", "DVBS2");
			}
			break;
		default:
			{
				*pOperMode = KHAL_DEMOD_TRANS_SYS_UNKNOWN;
				DEMOD_PRINT("Invalid operation mode\n");
			}
			break;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_OperMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_ControlTSMode( BOOLEAN bIsSerial)
{
	DEMOD_PRINT("bIsSerial = %d\n", bIsSerial);
	// not yet
	if (KHAL_OK != DEMOD_Serial_Control(bIsSerial))
	{
		DEMOD_NOTI("fail, DEMOD_Serial_Control ()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_ControlTSMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_ControlOutput(BOOLEAN bEnableOutput)
{
	if (RET_OK != DEMOD_TPOutCLKEnable(bEnableOutput))
	{
		DEMOD_NOTI("fail, DEMOD_TPOutCLKEnable ()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_ControlOutput);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_GetCellID(UINT16 *pCellID)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pCellID = sigCtx.cellID;

	DEMOD_PRINT("Cell ID = 0x%x\n", *pCellID);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_GetCellID);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DebugMenu(void)
{
	DEMOD_INFO("N/A\n");
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DebugMenu);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_SetCountryGrp(KHAL_DEMOD_COUNTRY_GRP_T halCountryGrp)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[0];

	DEMOD_NOTI("Received Country Group Code is 0x%x \n", halCountryGrp);

	if (halCountryGrp == KHAL_DEMOD_COUNTRY_GRP_EU)
	{
		pDemodInfo->bCountryGrpEU = TRUE;
	}
	else
	{
		pDemodInfo->bCountryGrpEU = FALSE;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_SetCountryGrp);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_GetTsClkRate(UINT32 *pTsClkRate)
{
	UINT32 demodTsClkRate;
	if (RET_OK != DEMOD_GetTsClkRate(&demodTsClkRate))
	{
		DEMOD_NOTI("fail, DEMOD_TPOutCLKEnable ()\n");
		return KHAL_NOK;
	}

	*pTsClkRate = demodTsClkRate;

	DEMOD_NOTI("demodTsClkRate = %d , *pTsClkRate = %d \n", demodTsClkRate, *pTsClkRate);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_GetTsClkRate);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT_SetDemod(KHAL_DEMOD_DVBT_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T 		configParams;

	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));
	configParams.operMode	= LX_DEMOD_DVBT;

	_Demod_DVBT_ConvHALToLXSpecParams(paramStruct,&configParams.dvbt);

	if (RET_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_NOTI("fail, KHAL_DEMOD_ChannelChange ()\n");
		return KHAL_NOK;
	}

	gBerTrigger = TRUE;
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);/*set Demodulatro lock state to *pLockState */
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT_CheckSpecialData(KHAL_DEMOD_SPECDATA_DVBT_T *pSpecData)
{
	/* Check Specia Data with the specified parameters. */
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	_Demod_DVBT_ConvLX2HALSpecParams(channelParams.dvbt,pSpecData);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT_GetSignalState(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	UINT8 				i;
	SINT32 				berSQI = 1;
	SINT32 				cnRel;
	SINT32 				tempQual = 0;
	UINT32 				cn_nordig_p1 = 0;
	UINT8 				signalQuality;
	UINT32 				unSNR;
	LX_DEMOD_CONFIG_T 		channelParams;
	LX_DEMOD_DVBT_CONFIG_T 		dvbtParams;
	LX_DEMOD_SIGNAL_CTX_T 		sigStatus;
	UINT32				temp_ber;
	UINT64				temp_snr = 0x0000000000000000L;
	UINT32				divBer;

	if (NULL == pSignalState)
	{
		DEMOD_NOTI("fail, pSnr or pBer or pQuality is NULL\n");
		return KHAL_NOK;
	}

	if (gBerTrigger == TRUE)
	{
		usleep_range(700000,701000);	/* 700ms ~ 701ms */

		gBerTrigger 	= FALSE;
		DEMOD_NOTI("DVB-T BerTrigger for All\n");
	}

	if (RET_OK != KHAL_Get_DEMOD_Sigstatus(&sigStatus))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_Sigstatus ()\n");
		return KHAL_NOK;
	}

	DEMOD_PRINT("CellID = 0x%x , FrequencyOffset = %d\n", sigStatus.cellID, sigStatus.offsetFrq_Hz);

	if (FALSE == sigStatus.bSignalValid )
	{
		DEMOD_NOTI("[KHAL DVB] sigStatus.bSignalValid is FALSE\n");
		return KHAL_NOK;
	}
	if (RET_OK != KHAL_Get_DEMOD_ChannelPara(&channelParams))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_ChannelPara ()\n");
		return KHAL_NOK;
	}

	if (LX_DEMOD_DVBT == sigStatus.operMode)
	{
		memcpy(&dvbtParams, &(channelParams.dvbt), sizeof(LX_DEMOD_DVBT_CONFIG_T));

		for(i = 0; i < sizeof(KhalSqiCnNordigP1_DVB)/ sizeof(LX_DEMOD_SQI_CN_NORDIGP1_T); i++)
		{
			if ( (dvbtParams.hierachMode == KhalSqiCnNordigP1_DVB[i].hierachMode) && (dvbtParams.bSetHp == KhalSqiCnNordigP1_DVB[i].bSetHp) &&
				  (dvbtParams.qamMode == KhalSqiCnNordigP1_DVB[i].constel) && (dvbtParams.hpCodeRate == KhalSqiCnNordigP1_DVB[i].code_rate))
			{
				cn_nordig_p1 = KhalSqiCnNordigP1_DVB[i].cn_ref;
				break;
			}
		}
		DEMOD_PRINT("OPER MODE :LX_DEMOD_DVBT\n");
	}
	else
	{
		DEMOD_PRINT("OPER MODE is Invalid\n");
		return KHAL_NOK;
	}

	unSNR 	= _DEMOD_DVB_DVBT_GetSnr(&sigStatus, channelParams.dvbt.gIMode);

	cnRel 	= (SINT32)((unSNR * 100) - cn_nordig_p1);

	divBer = sigStatus.ber >> 1;
	
	if ( divBer == 0 )			// PostVit BER > 1e-7
	{
		berSQI = 100;
	}
	else  if ( divBer > 10000 ) // PostVit BER > 1e-3
	{
		berSQI = 0 ;
	}
	else
	{
		temp_snr = intlog10((u32)(divBer));
		temp_ber = (u32)(temp_snr >> 24);
//		berSQI = (SINT32)(100*1000 - (20 * 1000 * (temp_ber)-(40*1000))) ;
		berSQI = (SINT32)(100*1000 - (20 * 1000 * temp_ber)) ;

		berSQI = berSQI / 1000;
	}

	if (cnRel > (3* 1000) )
	{
		signalQuality 	= berSQI;
	}
	else  if ( cnRel < (-7 * 1000) )
	{
		signalQuality 	= 0;
	}
	else
	{
		tempQual 	= ((cnRel - (3*1000))/10)+ (1* 1000);
		signalQuality 	= (UINT8)((tempQual * berSQI)/ 1000) ;
	}

	pSignalState->bSignalValid 	= sigStatus.bSignalValid;
	pSignalState->unSNR 		= unSNR/10;
	pSignalState->unBER 		= sigStatus.ber;
	pSignalState->unAGC 		= sigStatus.agc;
	pSignalState->packetError 	= sigStatus.packetError;
	pSignalState->quality 		= _Demod_SQI_Cal(signalQuality);

	DEMOD_PRINT("PacketError = %d , BER = %d , SignalQuality = %d\n",pSignalState->packetError , pSignalState->unBER, pSignalState->quality);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT_GetSignalState);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT2_SetDemod(KHAL_DEMOD_DVBT2_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	configParams.operMode	= LX_DEMOD_DVBT2;

	if (RET_OK != _Demod_DVBT2_ConvHALToLXSpecParams(paramStruct,&configParams.dvbt2))
	{
		DEMOD_NOTI("fail, _Demod_DVBT2_ConvHALToLXSpecParams ()\n");
		return KHAL_NOK;
	}

	if (RET_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_NOTI("fail, KHAL_DEMOD_ChannelChange ()\n");
		return KHAL_NOK;
	}

	gBerTrigger = TRUE;

	DEMOD_PRINT("DEMOD_DVB_Tune: SUCCESS - DVB-T2\n");

	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT2_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT2_ChangePLP(UINT8 unPLP)
{
	LX_DEMOD_DVBT2_CONFIG_T dvbt2ConfigParam;
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[0];

	DEMOD_PRINT("Received PLP ID : 0x%02x \n", unPLP);

	dvbt2ConfigParam.unPLP = unPLP;
	if (RET_OK != DEMOD_DVBT2_Set_PartialConfig(&dvbt2ConfigParam))
	{
		DEMOD_NOTI("fail, DEMOD_DVBT2_Set_PartialConfig()\n");
		return KHAL_NOK;
	}
	pDemodInfo->getCfgParam.dvbt2.unPLP = unPLP;

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT2_ChangePLP);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT2_CheckSpecialData(KHAL_DEMOD_SPECDATA_DVBT2_T *pSpecData)
{
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	if (RET_OK != _Demod_DVBT2_ConvLX2HALSpecParams(channelParams.dvbt2,pSpecData))
	{
		DEMOD_NOTI("fail, _Demod_DVBT2_ConvLX2HALSpecParams()\n");
		return KHAL_NOK;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT2_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT2_GetSignalState(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	UINT8 				i;
	SINT32 				berSQI = 1;
	SINT32 				cnRel;
	SINT32 				tempQual = 0;
	UINT32 				cn_nordig_p1 = 0;
	UINT8 				signalQuality;
	UINT32 				unSNR;
	LX_DEMOD_CONFIG_T		channelParams;
	LX_DEMOD_DVBT2_CONFIG_T 	dvbt2Params;
	LX_DEMOD_SIGNAL_CTX_T 		sigStatus;

	if (NULL == pSignalState)
	{
		DEMOD_PRINT("FAIL, pSnr or pBer or pQuality is NULL\n");
		return KHAL_NOK;
	}

	if (gBerTrigger == TRUE)
	{
		usleep_range(700000,701000);	/* 700ms ~ 701ms */

		gBerTrigger 	= FALSE;
		DEMOD_NOTI("DVB-T2 BerTrigger for All\n");
	}

	if (RET_OK != KHAL_Get_DEMOD_Sigstatus(&sigStatus))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	DEMOD_PRINT("CellID = 0x%x , FrequencyOffset = %d\n", sigStatus.cellID, sigStatus.offsetFrq_Hz);

	if (FALSE == sigStatus.bSignalValid )
	{
		DEMOD_PRINT("FAIL, sigStatus.bSignalValid is FALSE\n");
		return KHAL_NOK;
	}

	if (RET_OK != KHAL_Get_DEMOD_ChannelPara(&channelParams))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_ChannelPara()\n");
		return KHAL_NOK;
	}

	if (LX_DEMOD_DVBT2 == sigStatus.operMode)
	{
		memcpy(&dvbt2Params, &(channelParams.dvbt2), sizeof(LX_DEMOD_DVBT2_CONFIG_T));

		for(i = 0; i < sizeof(KhalSqiCnNordigP1_DVBForDVBT2)/ sizeof(LX_DEMOD_SQI_CN_NORDIGP1_T); i++)
		{
			if ( (dvbt2Params.qamMode == KhalSqiCnNordigP1_DVBForDVBT2[i].constel) && (dvbt2Params.codeRate == KhalSqiCnNordigP1_DVBForDVBT2[i].code_rate))
			{
				cn_nordig_p1 = KhalSqiCnNordigP1_DVBForDVBT2[i].cn_ref;
				break;
			}
		}
	}
	else
	{
		DEMOD_PRINT("OPER MODE is Invalid\n");
		return KHAL_NOK;

	}

	unSNR 	= _DEMOD_DVB_DVBT2_GetSnr(&sigStatus, channelParams.dvbt2.gIMode);
	cnRel 	= (SINT32)((unSNR * 100) - cn_nordig_p1);

	if (lx_chip() >= LX_CHIP_O22 && channelParams.dvbt2.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_19_256)
	{
			 DEMOD_PRINT("[KHAL DVB] O22 and GI Mode check\n");
			 if (sigStatus.ber < 10)
			 {
					 sigStatus.ber = 0 ;
			 }
	}

	if ( sigStatus.ber == 0 )			// PostVit BER > 1e-7
	{
		berSQI = 100/6;
	}
	else  if ( sigStatus.ber > 10000 )	// PostVit BER > 1e-4
	{
		berSQI = 0 ;
	}
	else
	{
		berSQI = 100/15;
	}

	if (cnRel > (3* 1000) )
	{
		signalQuality = 100;
	}
	else  if ( cnRel < (-3 * 1000) )
	{
		signalQuality = 0;
	}
	else
	{
		tempQual = cnRel + (3*1000);
		signalQuality = (UINT8)((tempQual * berSQI) / 1000) ;
	}

	pSignalState->bSignalValid 	= sigStatus.bSignalValid;
	pSignalState->unSNR 		= unSNR/10;
	pSignalState->unBER 		= sigStatus.ber;
	pSignalState->unAGC 		= sigStatus.agc;
	pSignalState->packetError 	= sigStatus.packetError;
	pSignalState->quality 		= _Demod_SQI_Cal(signalQuality);

	DEMOD_PRINT("PacketError = %d , BER = %d ,SignalQuality = %d \n",pSignalState->packetError ,sigStatus.ber, pSignalState->quality);

	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT2_GetSignalState);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBT2_GetMultiPLPInfo(KHAL_MULTI_TS_INFO_T *pPlpInfo)
{
	UINT8 					count;
	LX_DEMOD_DVBT2_MULTI_PLP_INFO_T 	paramMultiPlpInfo;

	if (RET_OK != DEMOD_DVBT2_Get_multiPLP_ID(&paramMultiPlpInfo))
	{
		DEMOD_NOTI("fail, DEMOD_DVBT2_Get_multiPLP_ID()\n");
		return KHAL_NOK;
	}

	pPlpInfo->PLPCount = paramMultiPlpInfo.plpDatacount;
	DEMOD_PRINT("pPlpInfo->PLPCount = 0x%x\n", pPlpInfo->PLPCount);

	for (count = 0; count < pPlpInfo->PLPCount; count++)
	{
		pPlpInfo->paPLPID[count] = paramMultiPlpInfo.plpDataID[count];
		DEMOD_PRINT("multiTS[%d] = 0x%02x\n", count, pPlpInfo->paPLPID[count]);
	}

	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBT2_GetMultiPLPInfo);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBC_SetDemod(KHAL_DEMOD_DVBC_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	DEMOD_PRINT("Received TuneMode = 0x%02x",paramStruct.tuneMode);

	configParams.operMode		= LX_DEMOD_DVBC;
	configParams.dvbc.bSpectrumInv	= paramStruct.bSpectrumInv;
	configParams.dvbc.channelBW 	= LX_DEMOD_BW_8MHZ;
	configParams.dvbc.qamMode	= _Demod_DVB_ConvHALConst2LX_RfMode(paramStruct.constellation);
	configParams.dvbc.symbolRate	= paramStruct.symbolRate;
	configParams.dvbc.frequency 	= paramStruct.frequency;
	configParams.dvbc.tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL :
					  (paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL :
					  (paramStruct.tuneMode == KHAL_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA) ? LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA : LX_DEMOD_TUNE_AUTO ;

	if (RET_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_NOTI("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}

	gBerTrigger = TRUE;
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBC_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBC_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBC_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBC_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBC_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBC_CheckSpecialData(KHAL_DEMOD_SPECDATA_DVBC_T *pSpecData)
{
	/* Check Specia Data with the specified parameters. */
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	pSpecData->bSpectrumInv		= channelParams.dvbc.bSpectrumInv;
	pSpecData->symbolRate 		= channelParams.dvbc.symbolRate;
	pSpecData->constellation 	= _Demod_DVB_ConvLX_RfMode2HALConst(channelParams.dvbc.qamMode);

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBC_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBC_GetSignalState(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	SINT32				berSQI;
	SINT32				cnRel;
	SINT32				cn;
	SINT32 				tempQual = 0;
	UINT32 				unSNR;
	UINT8				signalQuality;
	LX_DEMOD_CONFIG_T		channelParams;
	LX_DEMOD_DVBC_CONFIG_T 		dvbcParams;
	LX_DEMOD_SIGNAL_CTX_T 		sigStatus;
	UINT32				temp_ber;
	UINT64				temp_snr = 0x0000000000000000L;

	if (NULL == pSignalState)
	{
		DEMOD_PRINT("FAIL, pSnr or pBer or pQuality is NULL\n");
		return KHAL_NOK;
	}

	if (lx_chip() == LX_CHIP_M19)
	{		
		if (gBerTrigger == TRUE)
		{
	//		usleep_range(1000000,1001000);	/* 300ms ~ 310ms */
			usleep_range(700000,701000);	/* 700ms ~ 701ms */
			gBerTrigger 	= FALSE;
			DEMOD_PRINT("DVB-C BerTrigger\n");
		}
	}
	else
	{
		DEMOD_PRINT("SKIP DVB-C BerTrigger without M19\n");
	}

	if (RET_OK != KHAL_Get_DEMOD_Sigstatus(&sigStatus ))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (FALSE == sigStatus.bSignalValid )
	{
		DEMOD_PRINT("sigStatus.bSignalValid is FALSE\n");
		return KHAL_NOK;
	}

	if (LX_DEMOD_DVBC != sigStatus.operMode)
	{
		DEMOD_PRINT("OPER MODE may not be mismatched\n");
		return KHAL_NOK;
	}

	if (RET_OK != KHAL_Get_DEMOD_ChannelPara(&channelParams))
	{
		DEMOD_NOTI("fail, KHAL_Get_DEMOD_ChannelPara()\n");
		return KHAL_NOK;
	}

	memcpy(&dvbcParams, &(channelParams.dvbc), sizeof(LX_DEMOD_DVBC_CONFIG_T));

	if ((LX_DEMOD_QPSK == dvbcParams.qamMode) || (LX_DEMOD_UNKOWN_MODE == dvbcParams.qamMode))
	{
		DEMOD_PRINT("FAIL, Invalid dvbcParams.qamMode\n");
		return KHAL_NOK;
	}

	unSNR 	= _DEMOD_DVB_DVBC_GetSnr(&sigStatus);
	cn 	= (SINT32)(unSNR * 100);

	if (sigStatus.ber == 0 )			// PostVit BER < 1e-7
	{
		berSQI = 100 ;
	}
	else  if ( sigStatus.ber > 45000 )		// PostVit BER < 2e-4
	{
		berSQI = 0 ;
	}
	else		// PostVit BER < 2e-3
	{
		temp_snr = intlog10((u32)sigStatus.ber);
		temp_ber = (u32)(temp_snr >> 24);
		berSQI = (SINT32)(100*1000 - ( 20 * 1000 * temp_ber- (40 * 1000))) ;
		berSQI = berSQI / 1000;
	}

	cnRel = cn - nordigDVBCdB1000_GBB[dvbcParams.qamMode];

	if (cnRel > (3* 1000) )
	{
		signalQuality = berSQI;
	}
	else  if ( cnRel < (-7 * 1000) )
	{
		signalQuality = 0 ;
	}
	else
	{
		tempQual 	= ((cnRel - (3*1000))/10)+ (1* 1000);
		signalQuality 	= (UINT8)((tempQual * berSQI)/ 1000) ;
	}

	pSignalState->bSignalValid 	= sigStatus.bSignalValid;
	pSignalState->unSNR 		= unSNR/10;
	pSignalState->unBER		= sigStatus.ber;
	pSignalState->unAGC 		= sigStatus.agc;
	pSignalState->packetError 	= sigStatus.packetError;
	pSignalState->quality 		= _Demod_SQI_Cal(signalQuality); //(gScaleInfoSqi.sum)/TU_SCALE_ARRAY_SIZE ;

	DEMOD_PRINT("PacketError = %d , SignalQuality = %d  , BER = %d\n",pSignalState->packetError , pSignalState->quality, pSignalState->unBER);
	return KHAL_OK;

}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBC_GetSignalState);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_SetDemod(KHAL_DEMOD_DVBS_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	if (paramStruct.transSystem == KHAL_DEMOD_TRANS_SYS_DVBS)
	{
		configParams.operMode			= LX_DEMOD_DVBS;
		configParams.dvbs.constellation 	= LX_DEMOD_QPSK;
		configParams.dvbs.codeRate		= (LX_DEMOD_CODERATE_T)(paramStruct.codeRate);
		configParams.dvbs.symbolRate 		= paramStruct.symbolRate;
		configParams.dvbs.frequency		= paramStruct.freqKHz;
		configParams.dvbs.operatingMode		= (paramStruct.bIsBlind_search == FALSE) ? LX_DEMOD_DVBS_NORMAL_MODE : _gDvbsOperationMode;
		configParams.dvbs.tuneMode		= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL :
							  (paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL : LX_DEMOD_TUNE_AUTO ;

		DEMOD_PRINT("DVB-S tuneMode = 0x%02x \n", configParams.dvbs.tuneMode);
		DEMOD_PRINT("DVB-S frequency = %d \n", configParams.dvbs.frequency);
		DEMOD_PRINT("DVB-S symbol  = %d \n", configParams.dvbs.symbolRate);
	}
	else if (paramStruct.transSystem == KHAL_DEMOD_TRANS_SYS_DVBS2)
	{
		configParams.operMode			= LX_DEMOD_DVBS2;
		configParams.dvbs2.symbolRate 		= paramStruct.symbolRate;
		configParams.dvbs2.frequency		= paramStruct.freqKHz;
		configParams.dvbs2.operatingMode	= (paramStruct.bIsBlind_search == FALSE) ? LX_DEMOD_DVBS_NORMAL_MODE : _gDvbsOperationMode;
		configParams.dvbs2.tuneMode		= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL :
							  (paramStruct.tuneMode == KHAL_DEMOD_TUNE_MANUAL) ? LX_DEMOD_TUNE_MANUAL : LX_DEMOD_TUNE_AUTO ;

		DEMOD_PRINT("DVB-S2 tuneMode = 0x%02x\n", configParams.dvbs2.tuneMode);
		DEMOD_PRINT("DVB-S2 frequency = %d \n", configParams.dvbs2.frequency);
		DEMOD_PRINT("DVB-S2 symbol  = %d\n", configParams.dvbs2.symbolRate);
	}
	else
	{
		DEMOD_PRINT("FAIL, Unknown TransSystem : 0x%02x\n", paramStruct.transSystem);
		return KHAL_NOK;
	}

	if (paramStruct.bIsBlind_search == FALSE)
	{
		DEMOD_PRINT("bIsBlind_search	= %s \n", (paramStruct.bIsBlind_search == FALSE)?"FALSE":"TRUE");

		if (RET_OK != DEMOD_DVBSX_BlindScan_End())
		{
			DEMOD_PRINT("FAIL, DEMOD_DVBSX_BlindScan_End()\n");
		}
	}

	if (RET_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_NOTI("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_CheckSpecialData(KHAL_DEMOD_SPECDATA_DVBS_T *pSpecData)
{
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	if (channelParams.operMode == LX_DEMOD_DVBS)
	{
		pSpecData->bIsDVBS2 		= FALSE;
		pSpecData->bSpectrumInv 	= channelParams.dvbs.bSpectrumInv;
		pSpecData->symbolRate		= channelParams.dvbs.symbolRate;
		pSpecData->constellation	= _Demod_DVB_ConvLX_RfMode2HALConst(channelParams.dvbs.constellation);
		pSpecData->codeRate 		= _Demod_DVB_ConvLX_CodeRate2HALConst(channelParams.dvbs.codeRate);

		DEMOD_PRINT("Symbol Rate = %d \n",channelParams.dvbs.symbolRate);
		DEMOD_PRINT("Code Rate = 0x%02x \n",channelParams.dvbs.codeRate);
		DEMOD_PRINT("Constellation = 0x%02x \n", channelParams.dvbs.constellation);
		DEMOD_PRINT("Oper Mode = LX_DEMOD_DVBS \n");
	}
	else if (channelParams.operMode == LX_DEMOD_DVBS2)
	{
		pSpecData->bIsDVBS2 		= TRUE;
		pSpecData->bSpectrumInv 	= channelParams.dvbs2.bSpectrumInv;
		pSpecData->symbolRate		= channelParams.dvbs2.symbolRate;
		pSpecData->constellation	= _Demod_DVB_ConvLX_RfMode2HALConst(channelParams.dvbs2.constellation);
		pSpecData->codeRate 		= _Demod_DVB_ConvLX_CodeRate2HALConst(channelParams.dvbs2.codeRate);

		DEMOD_PRINT("Symbol Rate = %d \n",channelParams.dvbs2.symbolRate);
		DEMOD_PRINT("Code Rate = 0x%02x \n",channelParams.dvbs2.codeRate);
		DEMOD_PRINT("Constellation = 0x%02x \n", channelParams.dvbs2.constellation);
		DEMOD_PRINT("Oper Mode = LX_DEMOD_DVBS2 \n");
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_GetSignalState(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	SINT32 				berSQI = 1;
	SINT32 				cnRel;
	SINT32 				tempQual = 0;
	UINT32 				cn_nordig_p1 = 0;
	UINT8 				signalQuality;
	UINT32 				unSNR;
	LX_DEMOD_CONFIG_T 		channelParams;
	LX_DEMOD_DVBS2_CONFIG_T 	dvbs2Params;
	LX_DEMOD_SIGNAL_CTX_T 		sigStatus;

	UINT32				temp_ber;
	UINT64				temp_snr = 0x0000000000000000L;

	UINT32 cNnordig[2] = {
			/*  QPSK, 8PSK  */
			    9700, 8900
	};

	if (NULL == pSignalState)
	{
		DEMOD_PRINT("pSnr or pBer or pQuality is NULL \n");
		return RET_ERROR;
	}

	if (RET_OK != KHAL_Get_DEMOD_Sigstatus(&sigStatus))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return RET_ERROR;
	}
	if (FALSE == sigStatus.bSignalValid )
	{
		DEMOD_PRINT("sigStatus.bSignalValid is FALSE\n");
		return RET_OK;
	}

	if (LX_DEMOD_DVBS == sigStatus.operMode)
	{
		cn_nordig_p1 = cNnordig[0];
		DEMOD_PRINT("OPER MODE : LX_DEMOD_DVBS\n");
	}
	else if (LX_DEMOD_DVBS2 == sigStatus.operMode)
	{
		if (RET_OK != KHAL_Get_DEMOD_ChannelPara(&channelParams))
		{
			DEMOD_WARN("fail, KHAL_Get_DEMOD_ChannelPara()\n");
			return RET_ERROR;
		}

		memcpy(&dvbs2Params, &(channelParams.dvbs2), sizeof(LX_DEMOD_DVBS2_CONFIG_T));

		if (dvbs2Params.constellation == LX_DEMOD_8PSK)
		{
				cn_nordig_p1 = cNnordig[1];
		}
		else
		{
				cn_nordig_p1 = cNnordig[0];
		}
	}
	else
	{
		DEMOD_PRINT("OPER MODE is Invalid\n");
		return RET_ERROR;
	}

	unSNR 	= _DEMOD_DVB_DVBS_GetSnr(&sigStatus);
	cnRel 	= (SINT32)((unSNR * 100) - cn_nordig_p1);

	DEMOD_PRINT("sigStatus.ber = %d  \n",sigStatus.ber);

	if ( sigStatus.ber == 0 )			// PostVit BER > 1e-7
	{
		berSQI = 100;
	}
//	else  if ( sigStatus.ber > 10000 )	// PostVit BER > 1e-3
//	{
//		berSQI = 0 ;
//	}
	else
	{
		temp_snr 	= intlog10((u32)sigStatus.ber);
		temp_ber 	= (u32)(temp_snr >> 24);
		berSQI 		= (SINT32)(100*1000 - (20 * 1000 * (temp_ber)-(40*1000))) ;
		berSQI 		= berSQI / 1000;
	}
//	DEMOD_PRINT("berSQI = %d  \n",berSQI);

//	if (LX_DEMOD_DVBS2 == sigStatus.operMode)
//	{
//		berSQI = 100;
//	}

//	DEMOD_PRINT("cnRel = %d  cn_nordig_p1 = %d \n",sigStatus.operMode,cn_nordig_p1);
//	DEMOD_PRINT("sigStatus.operMode = %d  \n",sigStatus.operMode);
//	DEMOD_PRINT("berSQI = %d  \n",berSQI);

	if (cnRel > (3* 1000) )
	{
		signalQuality = berSQI;
	}
	else  if ( cnRel < (-7 * 1000) )
	{
		signalQuality = 0 ;
	}
	else
	{
		tempQual 	= ((cnRel - (3*1000))/10)+ (1* 1000);
		signalQuality 	= (UINT8)((tempQual * berSQI)/ 1000) ;
//		DEMOD_PRINT("tempQual = %d \n",tempQual);
	}

//	DEMOD_PRINT("signalQuality = %d \n",signalQuality);

//	if (sigStatus.packetError == 255) signalQuality = 0;

	pSignalState->bSignalValid 	= sigStatus.bSignalValid;
	pSignalState->unSNR 		= unSNR/10;
	pSignalState->unBER 		= sigStatus.ber;
	pSignalState->unAGC 		= sigStatus.agc;
	pSignalState->packetError 	= sigStatus.packetError;
	pSignalState->quality 		= _Demod_SQI_Cal(signalQuality);//(gScaleInfoSqi.sum)/TU_SCALE_ARRAY_SIZE ;

	DEMOD_PRINT("PacketError = %d , SignalQuality = %d \n",pSignalState->packetError , pSignalState->quality);
//	DEMOD_PRINT("pSignalState->unSNR = %d \n",pSignalState->unSNR);

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_GetSignalState);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_GetFWVersion(UINT32 *pFWVersion)
{
	if (RET_OK != DEMOD_Get_FW_PartInfo(pFWVersion))
	{
		DEMOD_WARN("fail, DEMOD_Get_FW_PartInfo()\n");
		return KHAL_NOK;
	}

	DEMOD_PRINT("FWVersion: 0x%x\n", *pFWVersion);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_GetFWVersion);

KHAL_RETURN_VALUE_T KHAL_DEMOD_PAL_GetFWVersion(UINT32 *pFWVersion)
{
	int status = KHAL_OK;
	return status;
}
EXPORT_SYMBOL(KHAL_DEMOD_PAL_GetFWVersion);

KHAL_RETURN_VALUE_T KHAL_DEMOD_NTSC_GetFWVersion(UINT32 *pFWVersion)
{
	int status = KHAL_OK;
	return status;
}
EXPORT_SYMBOL(KHAL_DEMOD_NTSC_GetFWVersion);


KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_Send_Diseqc(UINT8 *pCmd, UINT8 u8CmdSize)
{
	/*Execute Diseqc Cmd */
	UINT8 i;

	LX_DEMOD_DVBS_DiSEqC_MSG_T diseqcMsg;
	memset(&diseqcMsg, 0x0, sizeof(LX_DEMOD_DVBS_DiSEqC_MSG_T));

	diseqcMsg.sequence_length 		= u8CmdSize;
	diseqcMsg.end_seq 			= 0xFF;

	for(i=0;i < u8CmdSize;i++)
	{
		diseqcMsg.sequenceBuffer[i] = *(pCmd + i);
		DEMOD_PRINT("diseqcMsg.sequenceBuffer[%d] = 0x%x\n",i,diseqcMsg.sequenceBuffer[i]);
	}
	//input default value
	diseqcMsg.cont_tone 	= LX_DEMOD_DISEQC_TONE_DISCRETE ;
	diseqcMsg.tone_burst 	= LX_DEMOD_DISEQC_TONE_BURST_OFF;
	diseqcMsg.burst_sel 	= LX_DEMOD_DISEQC_TONEBURST_UNMODULATED;

	if (RET_OK != DEMOD_DVBS_Set_DiseqcToneMessageCtrl(&diseqcMsg))
	{
		DEMOD_WARN("fail, DEMOD_DVBS_Set_DiseqcToneMessageCtrl()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_Send_Diseqc);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_22Khz_Tone(BOOLEAN b22kon)
{
	/* Set 22khz on or off */
	KHAL_DEMOD_DiSEqC_MSG_T	sendingDiseqcMsg;
	memset(&sendingDiseqcMsg, 0x0, sizeof(KHAL_DEMOD_DiSEqC_MSG_T));

	sendingDiseqcMsg.sequence_length 	= 0;
	sendingDiseqcMsg.sequenceBuffer[0] 	= 0;
	sendingDiseqcMsg.cont_tone		= (b22kon == TRUE) ? 1 : 0;
	sendingDiseqcMsg.tone_burst		= 0;
	sendingDiseqcMsg.burst_sel		= 0;

	if (RET_OK != _DEMOD_DVB_DVBS_send_diseqc_sequence(&sendingDiseqcMsg))
	{
		DEMOD_WARN("fail, _DEMOD_DVB_DVBS_send_diseqc_sequence()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_22Khz_Tone);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_ToneMode (KHAL_DEMOD_DVBS_22KHZ_MODE_T mode)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_ToneMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_Send_Tone_Burst(BOOLEAN bTone1)
{
	/* Set toneburst modulated/unmodulated. */
	KHAL_DEMOD_DiSEqC_MSG_T	sendingDiseqcMsg;
	memset(&sendingDiseqcMsg, 0x0, sizeof(KHAL_DEMOD_DiSEqC_MSG_T));

	sendingDiseqcMsg.sequence_length 	= 0;
	sendingDiseqcMsg.sequenceBuffer[0] 	= 0;
	sendingDiseqcMsg.cont_tone		= 0;
	sendingDiseqcMsg.tone_burst		= 1;
	sendingDiseqcMsg.burst_sel		= (bTone1 == DISEQC_TONEBURST_UNMODULATED) ? LX_DEMOD_DISEQC_TONEBURST_UNMODULATED : LX_DEMOD_DISEQC_TONEBURST_MODULATED;

	if (RET_OK != _DEMOD_DVB_DVBS_send_diseqc_sequence(&sendingDiseqcMsg))
	{
		DEMOD_WARN("fail, _DEMOD_DVB_DVBS_send_diseqc_sequence()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_Send_Tone_Burst);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_Init(UINT32 StartFreqMhz, UINT32 EndFreqMhz)
{
	/* Initialize for blind scan */
	LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T initFreq;

	DEMOD_PRINT("StartFreqMhz : %d \n",StartFreqMhz );

	//BS DB Initialization
	_gBlindScanContext.rangeMin 		= StartFreqMhz; // Hz
	_gBlindScanContext.rangeMax 		= EndFreqMhz*SCALE_OF_MHZ; // Hz
	_gBlindScanContext.center_rf 		= StartFreqMhz; //Hz
	_gBlindScanContext.seekBWHz 		= INITIAL_BLIND_SCAN_BW ;
	_gDvbsOperationMode 			= LX_DEMOD_DVBS_BLIND_SCAN_MODE ;
	initFreq.startFreqKhz 			= StartFreqMhz*SCALE_OF_KHZ;
	initFreq.endFreqKhz 			= EndFreqMhz*SCALE_OF_KHZ;

	DEMOD_PRINT("initFreq.startFreqKhz : %d \n",initFreq.startFreqKhz );

	if (RET_OK != DEMOD_DVBSX_BlindScan_Init(&initFreq))
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_BlindScan_Init()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_Init);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_GetTunerFreq(UINT32 *TunerCenterFreqMhz, UINT32 *TunerCutOffFreqKhz)
{
	/*
	*TunerCenterFreqMhz = demodCenterFreq;
	*TunerCutOffFreqKhz = demodCutOffFreq;
	*/
	LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T freqInfo;

	if (RET_OK != DEMOD_DVBSX_GetTunerFreq(&freqInfo))
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_GetTunerFreq()\n");
		return KHAL_NOK;
	}

	*TunerCenterFreqMhz 		= freqInfo.TunerCenterFreqKhz /SCALE_OF_KHZ; //Bliend Scan between 950 Mhz to 2.4(or 1.74)Ghz
	*TunerCutOffFreqKhz 		= freqInfo.TunerCutOffFreqKhz; // BW is 40Mhz in normal case
	_gBlindScanContext.center_rf 	= freqInfo.TunerCenterFreqKhz * SCALE_OF_KHZ;
	_gBlindScanContext.seekBWHz 	= freqInfo.TunerCutOffFreqKhz * SCALE_OF_KHZ;

	DEMOD_PRINT("Received values : TunerCenterFreqKhz = %d TunerCutOffFreqKhz = %d\n",freqInfo.TunerCenterFreqKhz, freqInfo.TunerCutOffFreqKhz);
	DEMOD_PRINT("Return values : TunerCenterFreqMhz = %d TunerCutOffFreqKhz = %d\n",*TunerCenterFreqMhz, *TunerCutOffFreqKhz);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_GetTunerFreq);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_NextFreq(BOOLEAN *bBlindScanEnd)
{
	/* *bBlindScanEnd= bExistDemodNextFreq; */
	*bBlindScanEnd = FALSE;

	if (RET_OK != DEMOD_DVBSX_Get_Nextfreq_Status(bBlindScanEnd))
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_Get_Nextfreq_Status()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("NextFreq value : %d\n", *bBlindScanEnd);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_NextFreq);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_GetStatus(UINT8 *Status, BOOLEAN *bBlindScanLock)
{
	*bBlindScanLock = FALSE;

	if (RET_OK != DEMOD_DVBSX_SymbolRate_Detect())
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_SymbolRate_Detect()\n");
		return KHAL_NOK;
	}

	if (RET_OK != DEMOD_DVBSX_BlindLock_Loop())
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_BlindLock_Loop()\n");
		return KHAL_NOK;
	}
	else
	{
		*bBlindScanLock = TRUE;
		DEMOD_NOTI("SUCCESS DEMOD_DVBSX_BlindLock_Loop() \n");
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_GetStatus);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_End(void)
{
	_gBlindScanContext.rangeMin 		= 0;
	_gBlindScanContext.rangeMax 		= 0;
	_gBlindScanContext.center_rf 		= 0;
	_gBlindScanContext.seekBWHz		= 0;
	_gDvbsOperationMode 			= LX_DEMOD_DVBS_NORMAL_MODE ;

	if (RET_OK != DEMOD_DVBSX_BlindScan_End())
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_BlindScan_End()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_End);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DVB_DVBS_BlindScan_GetFoundTP(UINT32 *FreqMhz, UINT32 *SymbolRateKhz)
{
	LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T offsetInfo;
	BOOLEAN bStatus = TRUE;

	if (RET_OK != DEMOD_DVBSX_Get_OffsetFreq(&offsetInfo))
	{
		DEMOD_WARN("fail, DEMOD_DVBSX_Get_OffsetFreq()\n");
		bStatus = FALSE;
	}

	if (bStatus == TRUE)
	{
		*FreqMhz 		= offsetInfo.FreqMhz/SCALE_OF_KHZ;
		*SymbolRateKhz 	= offsetInfo.SymbolRateKhz;

		DEMOD_PRINT("FreqMhz = %d , SymbolRateKhz = %d \n", *FreqMhz,*SymbolRateKhz);
	}
	else
	{
		DEMOD_PRINT("FAIL, Operation Mode isn't DVBS or DVBS2\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DVB_DVBS_BlindScan_GetFoundTP);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_Initialize(void)
{
	unsigned int elapsedTime = jiffies_to_msecs(jiffies);

	if (KHAL_OK != DEMOD_ResetHW())
	{
		DEMOD_WARN("fail, DEMOD_ResetHW()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS DEMOD_ResetHW()\n");
	usleep_range(20000,23000);	/* 3ms ~ 10ms */

	if (KHAL_OK != KHAL_DEMOD_Init())
	{
		DEMOD_WARN("fail, KHAL_DEMOD_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS KHAL_DEMOD_Init()\n");

	if (KHAL_OK != DEMOD_I2C_open(7,0xB2))
	{
		DEMOD_WARN("fail, DEMOD_I2C_open()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("SUCCESS DEMOD_I2C_open()\n");

	if (KHAL_OK != DEMOD_DTMB_SW_Init())
	{
		DEMOD_WARN("fail, DEMOD_DTMB_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_DTMB_SW_Init()\n");

	if (KHAL_OK != DEMOD_FW_Initialize())
	{
		DEMOD_WARN("fail, DEMOD_FW_Initialize()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_FW_Initialize()\n");

	DEMOD_NOTI("elapsed %d ms\n", jiffies_to_msecs(jiffies) - elapsedTime);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_Initialize);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_ChangeTransSystem(KHAL_DEMOD_TRANS_SYSTEM_T transSystem)
{
	UINT32 			ifFrq = LX_DEMOD_IF_FREQ_05_000_KHZ;  //TU_IF_FREQ_04_560_KHZ;
	LX_DEMOD_INIT_PARAM_T 	mediaChageParams;

	if (transSystem == KHAL_DEMOD_TRANS_SYS_DTMB)
	{
		mediaChageParams.operMode 	= LX_DEMOD_DTMB;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FIXED_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_8MHZ;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is DTMB \n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_ALWAYSREADY)
	{
		mediaChageParams.operMode 	= LX_DEMOD_ALWAYSREADY;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FIXED_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_8MHZ;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is LX_DEMOD_ALWAYSREADY \n");
	}
	else
	{
		mediaChageParams.operMode 	= LX_DEMOD_DIGITAL_Sleep;
		mediaChageParams.symbr 		= LX_DEMOD_SYMR_FULL_SCAN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_DVBT_NO_OPERATION;
		mediaChageParams.ifFrq 		= ifFrq;

		DEMOD_NOTI("TransSystem is UNKNOWN (0x%02x)\n", transSystem);
	}

	return _KHAL_DEMOD_ChangeTransSystem(&mediaChageParams);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_ChangeTransSystem);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_SetDemod(KHAL_DEMOD_DTMB_SET_PARAM_T paramStruct)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	configParams.operMode	= LX_DEMOD_DTMB;
	_Demod_DTMB_ConvHALToLXSpecParams(paramStruct, &configParams.dtmb);

	if (RET_OK != KHAL_DEMOD_ChannelChange(&configParams)) //DEMOD_ChannelChange
	{
		DEMOD_WARN("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_SetDemod);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_CheckSpecialData(KHAL_DEMOD_SPECDATA_DTMB_T *pSpecDTMB)
{
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData");
		return KHAL_NOK;
	}

	_Demod_DTMB_ConvLX2HALSpecParams(channelParams.dtmb,pSpecDTMB);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_CheckSignalStatus(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	UINT32 				unSNR ;
	UINT32 				scaleSNR;
	UINT8 				signalQuality;
	LX_DEMOD_CONFIG_T 		channelParams;
	LX_DEMOD_DTMB_CONFIG_T 		dtmbParams;
	LX_DEMOD_SIGNAL_CTX_T 		sigStatus;

	if (NULL == pSignalState)
	{
		DEMOD_PRINT("pSnr or pBer or pQuality is NULL\n");
		return KHAL_NOK;
	}

	if (RET_OK != KHAL_Get_DEMOD_Sigstatus(&sigStatus))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (FALSE == sigStatus.bSignalValid )
	{
		DEMOD_PRINT("sigStatus.bSignalValid is FALSE\n");
		return KHAL_NOK;
	}

	if (RET_OK != KHAL_Get_DEMOD_ChannelPara(&channelParams))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_ChannelPara()\n");
		return KHAL_NOK;
	}

	if (LX_DEMOD_DTMB == sigStatus.operMode)
	{
		memcpy(&dtmbParams, &(channelParams.dtmb), sizeof(LX_DEMOD_DTMB_CONFIG_T));
		DEMOD_PRINT("OPER MODE :LX_DEMOD_DTMB\n");
	}
	else
	{
		DEMOD_PRINT("OPER MODE is Invalid\n");
		return KHAL_NOK;
	}

	unSNR 			= _DEMOD_DVB_DTMB_GetSnr(&sigStatus);
	scaleSNR 		= unSNR/10;

	if (scaleSNR >= 26)
	{
		signalQuality = 100;
	}
	else if (scaleSNR >=12 && scaleSNR < 26)
	{
		signalQuality = 99 - (26-scaleSNR)*(7);
	}
	else
	{
		signalQuality = 1;
	}

	if (sigStatus.packetError > 250)
	{
		signalQuality = 0;
	}


	pSignalState->bSignalValid 	= sigStatus.bSignalValid;
//	pSignalState->unBER 		= sigStatus.ber;
	pSignalState->unBER 		= sigStatus.packetError * BER_SCALE;
	pSignalState->unSNR 		= scaleSNR;
	pSignalState->unAGC 		= sigStatus.agc;
	pSignalState->packetError 	= sigStatus.packetError;
	pSignalState->quality = 	_Demod_SQI_Cal(signalQuality);//(gScaleInfoSqi.sum)/TU_SCALE_ARRAY_SIZE ;

	DEMOD_PRINT("PacketError = %d SignalQuality = %d  BER = %d \n",pSignalState->packetError , pSignalState->quality, pSignalState->unBER);

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_CheckSignalStatus);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_CheckFrequencyOffset(SINT32 *pFreqOffset)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pFreqOffset = sigCtx.offsetFrq_Hz;

	DEMOD_PRINT("Frequency Offset = %d\n", *pFreqOffset);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_CheckFrequencyOffset);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_ControlTSMode(BOOLEAN bIsSerial)
{
	DEMOD_PRINT("bIsSerial = %d\n", bIsSerial);

	if (RET_OK != DEMOD_Serial_Control(bIsSerial))
	{
		DEMOD_WARN("fail, DEMOD_Serial_Control()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_ControlTSMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_ControlOutput(BOOLEAN bEnableOutput)
{
	if (RET_OK != DEMOD_TPOutCLKEnable(bEnableOutput))
	{
		DEMOD_WARN("fail, DEMOD_TPOutCLKEnable()\n");
		return KHAL_NOK;
	}
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_ControlOutput);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DTMB_GetFWVersion(UINT32 *pFWVersion)
{
	if (RET_OK != DEMOD_Get_FW_PartInfo(pFWVersion))
	{
		DEMOD_WARN("fail, DEMOD_Get_FW_PartInfo()\n");
		return KHAL_NOK;
	}

	DEMOD_PRINT("FWVersion : 0x%x\n", *pFWVersion);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DTMB_GetFWVersion);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_GetSQI(UINT8 *pSQI)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pSQI = 0; // TBD

	DEMOD_PRINT("SQI : %d\n", *pSQI);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_GetSQI);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_GetPacketError(UINT32 *pPacketError)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pPacketError = sigCtx.packetError;

	DEMOD_PRINT("PacketError : %d\n",*pPacketError);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_GetPacketError);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_GetBER(UINT32 *pBER)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pBER = sigCtx.ber;

	DEMOD_PRINT("BER : %d\n",*pBER);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_GetBER);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_GetAGC(UINT32 *pAGC)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;
	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pAGC = sigCtx.agc;

	DEMOD_PRINT("AGC : %d\n",*pAGC);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_GetAGC);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_GetSNR(UINT32 *pSNR)
{
	//TBD
	*pSNR = 0;
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_GetSNR);

KHAL_RETURN_VALUE_T KHAL_DEMOD_DTMB_DebugMenu(void)
{
	//TBD
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_DTMB_DebugMenu);

KHAL_RETURN_VALUE_T KHAL_DEMOD_VQI_DVB_ISDBT_Initialize(void)
{
	unsigned int elapsedTime = jiffies_to_msecs(jiffies);
	KHAL_DEMOD_PanamaOn(TRUE);

	if (KHAL_OK != DEMOD_ResetHW())
	{
		DEMOD_WARN("fail, DEMOD_ResetHW()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS DEMOD_ResetHW()\n");
	usleep_range(20000,23000);	/* 3ms ~ 10ms */

	if (KHAL_OK != KHAL_DEMOD_Init())
	{
		DEMOD_WARN("fail, KHAL_DEMOD_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_INFO("SUCCESS KHAL_DEMOD_Init()\n");

	if (KHAL_OK != DEMOD_I2C_open(7,0xB2))
	{
		DEMOD_WARN("fail, DEMOD_I2C_open()\n");
		return KHAL_NOK;
	}
	DEMOD_PRINT("SUCCESS DEMOD_I2C_open()\n");

	if (KHAL_OK != DEMOD_ATSC_SW_Init())
	{
		DEMOD_WARN("fail, DEMOD_ATSC_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_ATSC_SW_Init()\n");

	if (KHAL_OK != DEMOD_DVB_SW_Init())
	{
		DEMOD_WARN("fail, DEMOD_DVB_SW_Init()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_DVB_SW_Init()\n");

	if (KHAL_OK != DEMOD_FW_Initialize())
	{
		DEMOD_WARN("fail, DEMOD_FW_Initialize()\n");
		return KHAL_NOK;
	}
	DEMOD_NOTI("SUCCESS DEMOD_FW_Initialize()\n");

	DEMOD_NOTI("elapsed %d ms\n", jiffies_to_msecs(jiffies) - elapsedTime);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_VQI_DVB_ISDBT_Initialize);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_Initialize(void)
{
	KHAL_DEMOD_PanamaOn(FALSE);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_Initialize);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_TunePostJob(BOOLEAN *pFinished)
{
	return _KHAL_DEMOD_TunePostJob(pFinished);
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_TunePostJob);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_CheckLock(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return _KHAL_DEMOD_CheckLock(pLockState);
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_CheckLock);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_CheckSpecialData(KHAL_DEMOD_SPECDATA_ATSC3_T *pSpecATSC3)
{
	LX_DEMOD_CONFIG_T channelParams;

	if (KHAL_OK != _KHAL_DEMOD_GetSpecialData(&channelParams)) {
		DEMOD_WARN("fail, _KHAL_DEMOD_GetSpecialData\n");
		return KHAL_NOK;
	}
	
	if (NULL == pSpecATSC3)
	{
		DEMOD_NOTI("fail, pSpecATSC3 is NULL\n");
		return KHAL_NOK;
	}

	switch (channelParams.atsc3.FFTMode)
	{
		case LX_DEMOD_DVBT_ISDBT_FFT_8K: 	pSpecATSC3->carrierMode = KHAL_DEMOD_TPS_CARR_8K;  		break;
		case LX_DEMOD_DVBT_ISDBT_FFT_16K: 	pSpecATSC3->carrierMode = KHAL_DEMOD_TPS_CARR_16K; 		break;
		case LX_DEMOD_DVBT_ISDBT_FFT_32K: 	pSpecATSC3->carrierMode = KHAL_DEMOD_TPS_CARR_32K; 		break;
		default:				pSpecATSC3->carrierMode = KHAL_DEMOD_TPS_CARR_UNKNOWN;		break;
	}
	switch (channelParams.atsc3.gIMode)
	{
		case LX_DEMOD_GUARD_ATSC3_1_192:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_1_192; 		break;
		case LX_DEMOD_GUARD_ATSC3_2_384:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_2_384; 		break;
		case LX_DEMOD_GUARD_ATSC3_3_512:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_3_512; 		break;
		case LX_DEMOD_GUARD_ATSC3_4_768:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_4_768; 		break;
		case LX_DEMOD_GUARD_ATSC3_5_1024:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_5_1024; 		break;
		case LX_DEMOD_GUARD_ATSC3_6_1536:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_6_1536; 		break;
		case LX_DEMOD_GUARD_ATSC3_7_2048:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_7_2048; 		break;
		case LX_DEMOD_GUARD_ATSC3_8_2432:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_8_2432; 		break;
		case LX_DEMOD_GUARD_ATSC3_9_3072:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_9_3072; 		break;
		case LX_DEMOD_GUARD_ATSC3_10_368:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_10_3648;		break;
		case LX_DEMOD_GUARD_ATSC3_11_4096:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_11_4096;		break;
		case LX_DEMOD_GUARD_ATSC3_12_4864:	pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_12_4864;		break;
		default:				pSpecATSC3->guardInterval = KHAL_DEMOD_TPS_GUARD_ATSC3_UNKNOWN;		break;
	}

	switch (channelParams.atsc3.codeRate)
	{
		case LX_DEMOD_ATSC3_CODE_2_15:  	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_2_15;		break;
		case LX_DEMOD_ATSC3_CODE_3_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_3_15;		break;
		case LX_DEMOD_ATSC3_CODE_4_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_4_15;		break;
		case LX_DEMOD_ATSC3_CODE_5_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_5_15;		break;
		case LX_DEMOD_ATSC3_CODE_6_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_6_15;		break;
		case LX_DEMOD_ATSC3_CODE_7_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_7_15;		break;
		case LX_DEMOD_ATSC3_CODE_8_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_8_15;		break;
		case LX_DEMOD_ATSC3_CODE_9_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_9_15;		break;
		case LX_DEMOD_ATSC3_CODE_10_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_10_15;		break;
		case LX_DEMOD_ATSC3_CODE_11_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_11_15;		break;
		case LX_DEMOD_ATSC3_CODE_12_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_12_15;		break;
		case LX_DEMOD_ATSC3_CODE_13_15:	 	pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_13_15;		break;
		default:	 			pSpecATSC3->codeRate = KHAL_DEMOD_TPS_CODE_ATSC3_UNKNOWN;	break;
	}

	DEMOD_PRINT("SpecialData: %u, %u, %u\n", channelParams.atsc3.FFTMode, channelParams.atsc3.gIMode, channelParams.atsc3.codeRate);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_CheckSpecialData);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_CheckFrequencyOffset(SINT32 *pFreqOffset)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pFreqOffset		= sigCtx.offsetFrq_Hz;

	DEMOD_PRINT("FreqOffset: %u\n", *pFreqOffset);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_CheckFrequencyOffset);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetFWVersion(UINT32 *pFWVersion)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetFWVersion);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetSQI(UINT8 *pSQI)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetSQI);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetPacketError(UINT32 *pPacketError)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pPacketError		= sigCtx.packetError;

	DEMOD_PRINT("PacketError: %u\n", *pPacketError);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetPacketError);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetBER(UINT32 *pBER)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pBER		= sigCtx.ber;

	DEMOD_PRINT("BER: %u\n", *pBER);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetBER);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetAGC(UINT32 *pAGC)
{
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pAGC		= sigCtx.agc;

	DEMOD_PRINT("AGC: %u\n", *pAGC);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetAGC);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_GetSNR(UINT32 *pSNR)
{

	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	*pSNR = sigCtx.unSNR;

	DEMOD_PRINT("SNR : %d\n",*pSNR);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_GetSNR);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_ControlOutput(BOOLEAN bEnableOutput)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_ControlOutput);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_ControlTSMode( BOOLEAN bIsSerial)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_ControlTSMode);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_ChangeTransSystem(KHAL_DEMOD_TRANS_SYSTEM_T transSystem)
{
	LX_DEMOD_INIT_PARAM_T	mediaChageParams;

	if (transSystem == KHAL_DEMOD_TRANS_SYS_ATSC3)	// brazil or japen ISDBT
	{
		mediaChageParams.operMode	= LX_DEMOD_ATSC3;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_UNKOWN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("Transmedia is ATSC3\n");
	}
	else if (transSystem == KHAL_DEMOD_TRANS_SYS_ALWAYSREADY)
	{
		mediaChageParams.operMode	= LX_DEMOD_ALWAYSREADY;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_UNKOWN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;
		
		DEMOD_NOTI("Transmedia is LX_DEMOD_ALWAYSREADY\n");
	}
	else
	{
		mediaChageParams.operMode	= LX_DEMOD_DIGITAL_Sleep;
		mediaChageParams.symbr		= LX_DEMOD_SYMR_UNKOWN_MODE;
		mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
		mediaChageParams.ifFrq		= LX_DEMOD_IF_FREQ_06_000_KHZ;

		DEMOD_NOTI("TransSystem is UNKNOWN (0x%02x)\n", transSystem);
	}

	return _KHAL_DEMOD_ChangeTransSystem(&mediaChageParams);
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_ChangeTransSystem);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_CheckSignalStatus(KHAL_DEMOD_SIGNAL_STATE_T *pSignalState)
{
	/*Check signal state with the specified parameters*/
	LX_DEMOD_SIGNAL_CTX_T sigCtx;

	if (NULL == pSignalState)
	{
		DEMOD_WARN("fail, pSignalState is NULL\n");
		return KHAL_NOK;
	}

	if (KHAL_OK != KHAL_Get_DEMOD_Sigstatus(&sigCtx))
	{
		DEMOD_WARN("fail, KHAL_Get_DEMOD_Sigstatus()\n");
		return KHAL_NOK;
	}

	if (sigCtx.bSignalValid == FALSE)
	{
//		cSnr = 0xffffffff;
		DEMOD_NOTI("The Signal is NOT LOCKED. next time ......try \n");
		return KHAL_OK;

	}

	pSignalState->bSignalValid	= sigCtx.bSignalValid;
	pSignalState->packetError	= sigCtx.packetError;
	pSignalState->unBER 		= sigCtx.ber;
	pSignalState->unAGC 		= sigCtx.agc;
	pSignalState->unSNR 		= sigCtx.unSNR;
	pSignalState->quality		= sigCtx.sigQ;	// check later

	DEMOD_PRINT("Packet Error = [%d]\n", pSignalState->packetError);
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_CheckSignalStatus);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_Monitor(KHAL_DEMOD_LOCK_STATE_T *pLockState)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_Monitor);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_Probe(UINT8 portI2C)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_Probe);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_DebugMenu (void)
{
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_DebugMenu);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_Get_MPLP_Info(KHAL_DEMOD_ATSC3_MULTI_PLP_ID_T *pPlpParams, KHAL_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel)
{
	UINT8	count;
	LX_DEMOD_ATSC3_MULTI_PLP_ID_T multiplpinfo;
	
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[0];

	if (RET_OK != DEMOD_ATSC3_Get_MPLP_Info(&multiplpinfo, (LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T)plpSel))
	{
		DEMOD_NOTI("fail, DEMOD_ATSC3_Get_MPLP_Info()\n");
		return KHAL_NOK;
	}

	pPlpParams->total_plpCount = multiplpinfo.plpTotalCount;
	pPlpParams->selected_plpCount = multiplpinfo.plpDatacount;

	for (count = 0; count < multiplpinfo.plpDatacount; count++)
	{
		pPlpParams->plpID[count] = multiplpinfo.plpDataID[count];
		DEMOD_PRINT("plpID[%d] = 0x%02x\n", count, pPlpParams->plpID[count]);
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_Get_MPLP_Info);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_PLP_Select(UINT8 plp0_id, UINT8 plp1_id, UINT8 plp2_id, UINT8 plp3_id)
{
	LX_DEMOD_ATSC3_CONFIG_T atsc3ConfigParam;
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[0];

	DEMOD_PRINT("ATSC3 config plpData[] = {0x%x, 0x%x, 0x%x, 0x%x}\n", plp0_id, plp1_id, plp2_id, plp3_id);

	atsc3ConfigParam.plpData[0] = plp0_id;
	atsc3ConfigParam.plpData[1] = plp1_id;
	atsc3ConfigParam.plpData[2] = plp2_id;
	atsc3ConfigParam.plpData[3] = plp3_id;

	if (RET_OK != DEMOD_ATSC3_Set_PLP(&atsc3ConfigParam))
	{
		DEMOD_NOTI("fail, DEMOD_DVBT2_Set_PartialConfig()\n");
		return KHAL_NOK;
	}

	pDemodInfo->getCfgParam.atsc3.plpData[0] = plp0_id;
	pDemodInfo->getCfgParam.atsc3.plpData[1] = plp1_id;
	pDemodInfo->getCfgParam.atsc3.plpData[2] = plp2_id;
	pDemodInfo->getCfgParam.atsc3.plpData[3] = plp3_id;
	
	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_PLP_Select);

KHAL_RETURN_VALUE_T KHAL_DEMOD_ATSC3_SetDemodExpand(KHAL_DEMOD_ATSC3_SET_PARAM_T paramStruct, UINT8 plp0_id, UINT8 plp1_id, UINT8 plp2_id, UINT8 plp3_id)
{
	LX_DEMOD_CONFIG_T configParams;
	memset(&configParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	DEMOD_PRINT("Set Decoder for ATSC3, tuneMode 0x%02x, transSystem 0x%02x\n",
						paramStruct.tuneMode, paramStruct.transSystem);

	/* Set registers of VSB mode */
	if (paramStruct.transSystem == KHAL_DEMOD_TRANS_SYS_ATSC3)
	{
		configParams.operMode		= LX_DEMOD_ATSC3;
		configParams.atsc3.bSpectrumInv	= paramStruct.bSpectrumInv;;
		configParams.atsc3.tuneMode	= (paramStruct.tuneMode == KHAL_DEMOD_TUNE_NORMAL) ? LX_DEMOD_TUNE_NORMAL : LX_DEMOD_TUNE_AUTO;
		configParams.atsc3.plpData[0]	= plp0_id;
		configParams.atsc3.plpData[1]	= plp1_id;
		configParams.atsc3.plpData[2]	= plp2_id;
		configParams.atsc3.plpData[3]	= plp3_id;
		configParams.atsc3.constellation = (LX_DEMOD_ATSC3_CONSTELLATION_T)_Demod_ATSC3_ConvHALConst2LX_RfMode(paramStruct.constellation);

		#if 0
		switch (_Demod_ATSC3_ConvHALConst2LX_RfMode(paramStruct.constellation))
		{
			case LX_DEMOD_QPSK:
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QPSK;
				break;
			case LX_DEMOD_DQPSK:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_DQPSK;				
				break;
			case LX_DEMOD_8PSK:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_PSK_8; 			
				break;
			case LX_DEMOD_16QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_16;				
				break;
			case LX_DEMOD_32QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_32;				
				break;
			case LX_DEMOD_64QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_64;				
				break;
			case LX_DEMOD_128QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_128;				
				break;
			case LX_DEMOD_256QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_256;				
				break;
			case LX_DEMOD_4QAM_NR:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_1024;				
				break;
			case LX_DEMOD_4QAM:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_QAM_4096;				
				break;			
			case LX_DEMOD_MODE_END:	
				configParams.atsc3.constellation = LX_DEMOD_CONST_ATSC3_END;				
				break;						
			default:							
				configParams.atsc3.constellation = LX_DEMOD_UNKOWN_MODE;			
				break;
		}
		#endif
			

		DEMOD_PRINT("tuneMode 0x%02x, transSystem 0x%02x, BW 0x%x, constel 0x%02x, plpData[] = {0x%x, 0x%x, 0x%x, 0x%x}\n",
			paramStruct.tuneMode, paramStruct.transSystem, paramStruct.eChannelBW, paramStruct.constellation,
			configParams.atsc3.plpData[0], configParams.atsc3.plpData[1], configParams.atsc3.plpData[2], configParams.atsc3.plpData[3]);
	}
	else
	{
		DEMOD_NOTI("fail Set Decoder, invalid transsystem\n");
	}


	if (KHAL_OK != KHAL_DEMOD_ChannelChange(&configParams))
	{
		DEMOD_WARN("fail, KHAL_DEMOD_ChannelChange()\n");
		return KHAL_NOK;
	}

	return KHAL_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ATSC3_SetDemodExpand);
