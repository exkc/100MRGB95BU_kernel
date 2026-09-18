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
 *  main driver implementation for irb device.
 *	irb device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1210_irb
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "os_util.h"
#include "base_device.h"
#include "irb_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "irb_o24common.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/

#define PSU_DATASIZE	256
/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
enum {
    PROC_ID_TX,
    PROC_ID_GOVERNOR,
    PROC_ID_BOOST,
    PROC_ID_MP_ENABLE,
    PROC_ID_TO_SUSPEND,
    PROC_ID_RESET_LOADMON,
    PROC_ID_GET_CURRENT_LOAD,
    PROC_ID_SAMPLING_RATE,
    PROC_ID_FREQ,
    PROC_ID_CPU_AVS,
    PROC_ID_CORE_AVS,
    PROC_ID_STATUS,
    PROC_ID_TS_ENABLE,
    PROC_ID_TS_DEBUG_ENABLE,
    PROC_ID_TS_CPU_APARAM,
    PROC_ID_TS_CPU_BPARAM,
    PROC_ID_TS_GPU_APARAM,
    PROC_ID_TS_GPU_BPARAM,
    PROC_ID_TEMPERATURE,
    PROC_ID_MAX,
};

enum {
    GOV_ID_MAX_FREQ,
    GOV_ID_MIN_FREQ,
    GOV_ID_HARD_UP_THRESHOLD,
    GOV_ID_EASY_UP_THRESHOLD,
    GOV_ID_EASY_COUNT,
    GOV_ID_FREQDOWN_COUNT,
    GOV_ID_MPD_COUNT,
    GOV_ID_MAX,
};

enum {
    DEBUG_ID_PSU_INFO,
    DEBUG_ID_MAX,
};

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
static irbs_o24_func_t* irb_o24_func = NULL;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
static void _IRB_PrintStatus(struct seq_file *m, void* data);
void o24_irb_proc_init (void);
void o24_irb_proc_cleanup (void);

OS_PROC_SEQRD_DEFINE_EX(irb_status_proc_fops, _IRB_PrintStatus,NULL)

    /*----------------------------------------------------------------------------------------
      Static Variables
      ----------------------------------------------------------------------------------------*/

    static OS_PROC_DESC_TABLE_T	_g_irb_o24_device_proc_table[] =
{
    { "tx",				PROC_ID_TX			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
    { "temperature",			PROC_ID_TEMPERATURE			, OS_PROC_FLAG_READ	  },
    { NULL, 					PROC_ID_MAX					, 0 }
};


/*========================================================================================
  Implementation Group
  ========================================================================================*/



static void _IRB_PrintStatus(struct seq_file *m, void* data)
{

}


/**
 * read_proc implementation of irb device
 *
 */

static int	o24_read_proc(UINT32 procId, char* buffer )
{
    int	ret = 0 ;

    switch( procId ) {
	case PROC_ID_SAMPLING_RATE:
	    break;
	default:
	    ret = -1;
	    break;
    }

    return ret;
}

/**
 * write_proc implementation of irb device
 *
 */


static int o24_write_proc( UINT32 procId, char* command )
{
    unsigned int vendor;
    unsigned int opt;
    unsigned int key ;
    unsigned int input_n;
    irbs_o24_work_t irbs_work;
    int ret = 0;

    memset(&irbs_work, 0x0, sizeof(irbs_work));

    /* TODO: add your proc_write implementation */
    switch( procId )
    {
	case PROC_ID_TX:

	    input_n = sscanf(command,"%x %x %x \n", &vendor,&opt,&key);
	    break;
	default:
	    ret = -1;
	    break;
    }

    return strlen(command);
}


/**
 * initialize proc utility for irb device
 *
 * @see IRB_Init
 */
void o24_irb_proc_init (void)
{
    irb_o24_func = get_o24_irb_func();


    OS_PROC_CreateEntryEx ( IRB_MODULE, _g_irb_o24_device_proc_table,
	    o24_read_proc,
	    o24_write_proc );
}

/**
 * cleanup proc utility for irb device
 *
 * @see IRB_Cleanup
 */
void o24_irb_proc_cleanup (void)
{
    OS_PROC_RemoveEntry( IRB_MODULE );
}

static irbs_proc_t o24_irb_proc_func =
{
    .init = o24_irb_proc_init,
    .cleanup = o24_irb_proc_cleanup,
};

irbs_proc_t* get_o24_irb_proc(void)
{
    return &o24_irb_proc_func;
}

