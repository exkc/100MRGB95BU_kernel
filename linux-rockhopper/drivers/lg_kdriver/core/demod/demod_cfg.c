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
 *  main configuration file for demod device
 *	demod device will teach you how to make device driver with new platform.
 *
 *  author		jeongpil.yun (jeongpil.yun@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#define DEMOD_TAG "[CORE.CFG] "

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_impl.h"
#include "hma_alloc.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
DEMOD_MEM_CFG_T gMemCfgDEMOD =
{
		.memory_name	= "demod_isdbt",		/* ISDB-T running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_ISDBT =
{
		.memory_name	= "demod_isdbt",		/* ISDB-T running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_TDI =
{
		.memory_name	= "demod_tdi",			/* DVBT2 running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_DJB =
{
		.memory_name	= "demod_djb",			/* DVBT2/S2 running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_RISIC =
{
		.memory_name	= "demod_risic",		/* risic running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_FW =
{
		.memory_name	= "demod_fw",			/* demod FW running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_DTMB =
{
		.memory_name	= "demod_dtmb",			/* DTMB running memory */
};

DEMOD_MEM_CFG_T gMemCfgDEMOD_ATSC3 =
{
		.memory_name	= "demod_atsc3",		/* ATSC3.0 FW running memory */
};


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

extern BOOLEAN		gPanama;



/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
void    DEMOD_SetupMemMap (void)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18:
		{
			gMemCfgDEMOD.memory_size		= 12582912;	// 12MB, ISDB-T
			gMemCfgDEMOD_DVB_TDI.memory_size	= 5670000;	// about 5MB, DVB_TDI
			gMemCfgDEMOD_DVB_DJB.memory_size	= 1160000;	// about 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 4000000;	// about 4MB, DTMB
			gMemCfgDEMOD_FW.memory_size		= 98304;	// 96KB, DTMB
		}
		break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19:
		{
			gMemCfgDEMOD.memory_size		= 12582912;	// 12MB, ISDB-T
			gMemCfgDEMOD_DVB_TDI.memory_size	= 5670000;	// DVB_TDI
			gMemCfgDEMOD_DVB_DJB.memory_size	= 1160000;	// DVB_DJB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 512000;	// DVB_RISIC
			gMemCfgDEMOD_FW.memory_size		= 98304;	// 96KB, DTMB
		}
		break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		case LX_CHIP_O20:
		{
			gMemCfgDEMOD.memory_size		= 0x00C00000;	// 12MB, ISDB-T
			gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00580000;	// 5.5MB, DVB_TDI
			gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
			gMemCfgDEMOD_FW.memory_size		= 0x00080000;	// 512KB, FW
		}
		break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		case LX_CHIP_E60:
		{
			gMemCfgDEMOD.memory_size		= 0x00C00000;	// 12MB, ISDB-T
			gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00580000;	// 5.5MB, DVB_TDI
			gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
			gMemCfgDEMOD_FW.memory_size		= 0x00080000;	// 512KB, FW
		}
		break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22:
		{
			gMemCfgDEMOD_ISDBT.memory_size		= 0x00C00000;	// ISDB-T, 12MB
			gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00680000;	// DVB_TDI, 6.5MB
			gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
			gMemCfgDEMOD_ATSC3.memory_size		= 0x01400000;	// 20MB, ATSC3.0
			gMemCfgDEMOD_FW.memory_size		= 0x00080000;	// 512KB, FW

			gMemCfgDEMOD.memory_name = "demod";
			gMemCfgDEMOD.memory_size = 0;
		}
		break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		case LX_CHIP_M23:
		{
			gMemCfgDEMOD_ISDBT.memory_size		= 0x00C00000;	// ISDB-T, 12MB
			gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00680000;	// DVB_TDI, 6.5MB
			gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
//			gMemCfgDEMOD_ATSC3.memory_size		= 0x01400000;	// 20MB, ATSC3.0
			gMemCfgDEMOD_ATSC3.memory_size		= 0x01700000;	// 23MB, ATSC3.0
			gMemCfgDEMOD_FW.memory_size 		= 0x00080000;	// 512KB, FW

			gMemCfgDEMOD.memory_name = "demod";
			gMemCfgDEMOD.memory_size = 0;
		}
		break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV //!//
		case LX_CHIP_O24:
		{
			gMemCfgDEMOD_ISDBT.memory_size		= 0x00C00000;	// ISDB-T, 12MB
			gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00680000;	// DVB_TDI, 6.5MB
			gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
			gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
			gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
			gMemCfgDEMOD_ATSC3.memory_size		= 0x01400000;	// 20MB, ATSC3.0
//			gMemCfgDEMOD_ATSC3.memory_size		= 0x01700000;	// 23MB, ATSC3.0
			gMemCfgDEMOD_FW.memory_size 		= 0x00080000;	// 512KB, FW

			gMemCfgDEMOD.memory_name = "demod";
			gMemCfgDEMOD.memory_size = 0;
		}
		break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV // chungiii
				
				case LX_CHIP_O26:
				{
					gMemCfgDEMOD_ISDBT.memory_size		= 0x00C00000;	// ISDB-T, 12MB
					gMemCfgDEMOD_DVB_TDI.memory_size	= 0x00680000;	// DVB_TDI, 6.5MB
					gMemCfgDEMOD_DVB_DJB.memory_size	= 0x00100000;	// 1MB, DVB_DJB
					gMemCfgDEMOD_DTMB.memory_size		= 0x00400000;	// 4MB, DTMB
					gMemCfgDEMOD_DVB_RISIC.memory_size	= 0x00080000;	// 512KB, DVB_RISIC
					gMemCfgDEMOD_ATSC3.memory_size		= 0x01400000;	// 20MB, ATSC3.0
		//			gMemCfgDEMOD_ATSC3.memory_size		= 0x01700000;	// 23MB, ATSC3.0
					gMemCfgDEMOD_FW.memory_size 		= 0x00080000;	// 512KB, FW
		
					gMemCfgDEMOD.memory_name = "demod";
					gMemCfgDEMOD.memory_size = 0;
				}
				break;
#endif


		default:
		{
			gMemCfgDEMOD.memory_size 		 = 0x00C00000; /* 12 MB for ISDB-T de-interleaving */
			gMemCfgDEMOD_DVB_TDI.memory_size = 0;
			gMemCfgDEMOD_DVB_DJB.memory_size = 0;
		}
		break;
	}
}

static int	DEMOD_HmaAlloc( DEMOD_MEM_CFG_T* mem )
{
	/* memory allocation already succeeded !! */
	if(0x0 != mem->memory_base) return RET_OK;

	/* DO not allocate zero-sized memory */
	if(0x0 == mem->memory_size) return RET_OK;

	mem->memory_base = hma_alloc("te_shared", mem->memory_size, PAGE_SIZE);

	if(mem->memory_base)
	{
		DEMOD_WARN("++ demod alloc ok (%s %dKB@0x%08x))\n", mem->memory_name, mem->memory_size>>10, mem->memory_base);
		return RET_OK;
	}
	else
	{
		DEMOD_ERROR("++ demod alloc error (%s %d KB)\n", mem->memory_name, mem->memory_size>>10);
		return RET_ERROR;
	}
}

extern int DEMOD_FW_ReInit(int mode);
static BOOLEAN	_demod_mem_alloc_ok = FALSE;

void	DEMOD_UnregisterMemMap( void )
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(lx_chip() == LX_CHIP_M23)
	{
		if((TRUE == _demod_mem_alloc_ok) && (0 != gMemCfgDEMOD.memory_base)) {
			DEMOD_NOTI("demod mem free all, 0x%08x, %dKB\n", gMemCfgDEMOD.memory_base, gMemCfgDEMOD.memory_size);
			hma_free("te_shared", gMemCfgDEMOD.memory_base);

			gMemCfgDEMOD.memory_base = 0;
			gMemCfgDEMOD_ISDBT.memory_base = 0;
			gMemCfgDEMOD_DVB_TDI.memory_base = 0;
			gMemCfgDEMOD_DVB_DJB.memory_base = 0;
			gMemCfgDEMOD_DTMB.memory_base = 0;
			gMemCfgDEMOD_DVB_RISIC.memory_base = 0;
			gMemCfgDEMOD_ATSC3.memory_base = 0;

			_demod_mem_alloc_ok = FALSE;
			pDemodDev->mem_alloc = FALSE;

			DEMOD_FW_ReInit(10);	// M23: clear base addr
		}
	}
	else if(lx_chip() == LX_CHIP_O24) //!//
	{
		if((TRUE == _demod_mem_alloc_ok) && (0 != gMemCfgDEMOD.memory_base)) {
			DEMOD_NOTI("demod mem free all, 0x%08x, %dKB\n", gMemCfgDEMOD.memory_base, gMemCfgDEMOD.memory_size);
			hma_free("te_shared", gMemCfgDEMOD.memory_base);

			gMemCfgDEMOD.memory_base = 0;
			gMemCfgDEMOD_ISDBT.memory_base = 0;
			gMemCfgDEMOD_DVB_TDI.memory_base = 0;
			gMemCfgDEMOD_DVB_DJB.memory_base = 0;
			gMemCfgDEMOD_DTMB.memory_base = 0;
			gMemCfgDEMOD_DVB_RISIC.memory_base = 0;
			gMemCfgDEMOD_ATSC3.memory_base = 0;

			_demod_mem_alloc_ok = FALSE;
			pDemodDev->mem_alloc = FALSE;
		}
	}
	else if(lx_chip() == LX_CHIP_O26) //chungiii
	{
		if((TRUE == _demod_mem_alloc_ok) && (0 != gMemCfgDEMOD.memory_base)) {
			DEMOD_NOTI("demod mem free all, 0x%08x, %dKB\n", gMemCfgDEMOD.memory_base, gMemCfgDEMOD.memory_size);
			hma_free("te_shared", gMemCfgDEMOD.memory_base);

			gMemCfgDEMOD.memory_base = 0;
			gMemCfgDEMOD_ISDBT.memory_base = 0;
			gMemCfgDEMOD_DVB_TDI.memory_base = 0;
			gMemCfgDEMOD_DVB_DJB.memory_base = 0;
			gMemCfgDEMOD_DTMB.memory_base = 0;
			gMemCfgDEMOD_DVB_RISIC.memory_base = 0;
			gMemCfgDEMOD_ATSC3.memory_base = 0;

			_demod_mem_alloc_ok = FALSE;
			pDemodDev->mem_alloc = FALSE;
		}
	}
		
}


void	DEMOD_RegisterMemMap( char* mode )
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	static const char * str_dvb = "dvb";
	static const char * str_isdbt = "isdbt";
	static const char * str_dtmb = "dtmb";
	static const char * str_atsc3 = "atsc3";

	DEMOD_CHECK_ERROR(NULL==mode, return, "<!> NULL mode, check codes\n");

	DEMOD_NOTI("%s, %s\n", mode, (_demod_mem_alloc_ok ? "already, skip" : "try alloc"));

	/* memory allocation already succeeded !! */
	if(_demod_mem_alloc_ok) return;

	if(lx_chip() == LX_CHIP_M19)
	{
		if(!strncmp(mode,"dvb",4))
		{
			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DTMB), 		goto func_exit, "register failed\n");
			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_TDI), 		goto func_exit, "register failed\n");
			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_DJB), 		goto func_exit, "register failed\n");
			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_RISIC),		goto func_exit, "register failed\n");
			_demod_mem_alloc_ok = TRUE;
		}
		else if(!strncmp(mode,"isdbt",5))
		{
			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 			goto func_exit, "register failed\n");
			_demod_mem_alloc_ok = TRUE;
		}
	}
	else if(lx_chip() == LX_CHIP_O20)
	{
		 if(gPanama==TRUE)
		{
			if((!strncmp(mode,"dvb",4)) || (!strncmp(mode,"isdbt",7)))
			{
				//DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc_Shared(&gMemCfgDEMOD), goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");

				gMemCfgDEMOD_DVB_TDI.memory_base	= gMemCfgDEMOD.memory_base;
				gMemCfgDEMOD_DVB_DJB.memory_base	= gMemCfgDEMOD_DVB_TDI.memory_base + 0x00580000;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= gMemCfgDEMOD_DVB_DJB.memory_base + 0x00100000;

				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_TDI.base[0x%x],gMemCfgDEMOD_DVB_TDI.size[%d]\n",gMemCfgDEMOD_DVB_TDI.memory_base , gMemCfgDEMOD_DVB_TDI.memory_size);
				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_DJB.base[0x%x],gMemCfgDEMOD_DVB_DJB.size[%d]\n",gMemCfgDEMOD_DVB_DJB.memory_base , gMemCfgDEMOD_DVB_DJB.memory_size);
				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_RISIC.base[0x%x],gMemCfgDEMOD_DVB_RISIC.size[%d]\n",gMemCfgDEMOD_DVB_RISIC.memory_base , gMemCfgDEMOD_DVB_RISIC.memory_size);
				DEMOD_WARN("[panama] ISDBT gMemCfgDEMOD.base[0x%x],gMemCfgDEMOD.size[%d]\n",gMemCfgDEMOD.memory_base , gMemCfgDEMOD.memory_size);
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{
			if(!strncmp(mode,"dvb",4))
			{
	//			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DTMB), 	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_TDI),	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_DJB),	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_RISIC),	goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;

				DEMOD_WARN("gMemCfgDEMOD_DVB_TDI.base[0x%x],gMemCfgDEMOD_DVB_TDI.size[%d] \n",gMemCfgDEMOD_DVB_TDI.memory_base , gMemCfgDEMOD_DVB_TDI.memory_size);
				DEMOD_WARN("gMemCfgDEMOD_DVB_DJB.base[0x%x],gMemCfgDEMOD_DVB_DJB.size[%d] \n",gMemCfgDEMOD_DVB_DJB.memory_base , gMemCfgDEMOD_DVB_DJB.memory_size);
				DEMOD_WARN("gMemCfgDEMOD_DVB_RISIC.base[0x%x],gMemCfgDEMOD_DVB_RISIC.size[%d] \n",gMemCfgDEMOD_DVB_RISIC.memory_base , gMemCfgDEMOD_DVB_RISIC.memory_size);
			}
			else if(!strncmp(mode,"isdbt",5))
			{
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;
				DEMOD_WARN("gMemCfgDEMOD.base[0x%x],gMemCfgDEMOD.size[%d]\n",gMemCfgDEMOD.memory_base , gMemCfgDEMOD.memory_size);
			}
			else if(!strncmp(mode,"dtmb",4))
			{
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DTMB), 	goto func_exit, "register failed\n");
	//			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_TDI),	goto func_exit, "register failed\n");
	//			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_DJB),	goto func_exit, "register failed\n");
	//			DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_RISIC),	goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;
			}
		}
	}
	else if(lx_chip() == LX_CHIP_E60)
	{
		 if(gPanama==TRUE)
		{
			if((!strncmp(mode,"dvb",4)) || (!strncmp(mode,"isdbt",7)))
			{
				//DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc_Shared(&gMemCfgDEMOD), 	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");

				gMemCfgDEMOD_DVB_TDI.memory_base	= gMemCfgDEMOD.memory_base;
				gMemCfgDEMOD_DVB_DJB.memory_base	= gMemCfgDEMOD_DVB_TDI.memory_base + 0x00580000;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= gMemCfgDEMOD_DVB_DJB.memory_base + 0x00100000;

				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_TDI.base[0x%x],gMemCfgDEMOD_DVB_TDI.size[%d]\n",gMemCfgDEMOD_DVB_TDI.memory_base , gMemCfgDEMOD_DVB_TDI.memory_size);
				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_DJB.base[0x%x],gMemCfgDEMOD_DVB_DJB.size[%d]\n",gMemCfgDEMOD_DVB_DJB.memory_base , gMemCfgDEMOD_DVB_DJB.memory_size);
				DEMOD_WARN("[panama] gMemCfgDEMOD_DVB_RISIC.base[0x%x],gMemCfgDEMOD_DVB_RISIC.size[%d]\n",gMemCfgDEMOD_DVB_RISIC.memory_base , gMemCfgDEMOD_DVB_RISIC.memory_size);

				DEMOD_WARN("[panama] ISDBT gMemCfgDEMOD.base[0x%x],gMemCfgDEMOD.size[%d]\n",gMemCfgDEMOD.memory_base , gMemCfgDEMOD.memory_size);
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{

			if(!strncmp(mode,"dvb",4))
			{
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_TDI), 	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_DJB), 	goto func_exit, "register failed\n");
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DVB_RISIC),	goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode,"isdbt",5))
			{
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode,"dtmb",4))
			{
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD_DTMB), 	goto func_exit, "register failed\n");
				_demod_mem_alloc_ok = TRUE;
			}
		}
	}
	else if(lx_chip() == LX_CHIP_O22)
	{
		UINT32 memory_base = 0;

		if(gPanama==TRUE)
		{
			if((!strncmp(mode, str_dvb, strlen(str_dvb))) || (!strncmp(mode, str_isdbt, strlen(str_isdbt))))
			{
				UINT32 DVB_memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				gMemCfgDEMOD.memory_size = (gMemCfgDEMOD_ISDBT.memory_size > DVB_memory_size) ? gMemCfgDEMOD_ISDBT.memory_size : DVB_memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;

				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{
			if(!strncmp(mode, str_dvb, strlen(str_dvb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_isdbt, strlen(str_isdbt)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ISDBT.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_dtmb, strlen(str_dtmb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DTMB.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DTMB.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_atsc3, strlen(str_atsc3)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ATSC3.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ATSC3.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
		}

		if (TRUE == _demod_mem_alloc_ok) {
			if (gMemCfgDEMOD_ATSC3.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ATSC3     base 0x%08x, size %u\n", gMemCfgDEMOD_ATSC3.memory_base, gMemCfgDEMOD_ATSC3.memory_size);
			if (gMemCfgDEMOD_ISDBT.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ISDBT     base 0x%08x, size %u\n", gMemCfgDEMOD_ISDBT.memory_base, gMemCfgDEMOD_ISDBT.memory_size);
			if (gMemCfgDEMOD_DTMB.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DTMB      base 0x%08x, size %u\n", gMemCfgDEMOD_DTMB.memory_base, gMemCfgDEMOD_DTMB.memory_size);

			if (gMemCfgDEMOD_DVB_TDI.memory_base) {
				DEMOD_INFO("gMemCfgDEMOD_DVB_TDI   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_TDI.memory_base, gMemCfgDEMOD_DVB_TDI.memory_size);
				DEMOD_INFO("gMemCfgDEMOD_DVB_DJB   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_DJB.memory_base, gMemCfgDEMOD_DVB_DJB.memory_size);
				DEMOD_INFO("gMemCfgDEMOD_DVB_RISIC base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_RISIC.memory_base, gMemCfgDEMOD_DVB_RISIC.memory_size);
			}

			DEMOD_NOTI("mem alloc success, %s, panama %s, 0x%08x, %dKB\n", mode, (TRUE == gPanama) ? "on" : "off", gMemCfgDEMOD.memory_base, gMemCfgDEMOD.memory_size);
		}
		/* add your code if new chip supports memory share */
	}
	else if(lx_chip() == LX_CHIP_M23)
	{
		UINT32 memory_base = 0;

		if(gPanama==TRUE)
		{
			// dvb + isdbt
			if((!strncmp(mode, str_dvb, strlen(str_dvb))) || (!strncmp(mode, str_isdbt, strlen(str_isdbt))))
			{
				UINT32 DVB_memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				gMemCfgDEMOD.memory_size = (gMemCfgDEMOD_ISDBT.memory_size > DVB_memory_size) ? gMemCfgDEMOD_ISDBT.memory_size : DVB_memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;

				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{
			if(!strncmp(mode, str_dvb, strlen(str_dvb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_dtmb, strlen(str_dtmb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DTMB.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DTMB.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_atsc3, strlen(str_atsc3)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ATSC3.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ATSC3.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
		}

		if (TRUE == _demod_mem_alloc_ok) {
			if (gMemCfgDEMOD_ATSC3.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ATSC3	   base 0x%08x, size %u\n", gMemCfgDEMOD_ATSC3.memory_base, gMemCfgDEMOD_ATSC3.memory_size);
			if (gMemCfgDEMOD_ISDBT.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ISDBT	   base 0x%08x, size %u\n", gMemCfgDEMOD_ISDBT.memory_base, gMemCfgDEMOD_ISDBT.memory_size);
			if (gMemCfgDEMOD_DTMB.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DTMB	   base 0x%08x, size %u\n", gMemCfgDEMOD_DTMB.memory_base, gMemCfgDEMOD_DTMB.memory_size);

			if (gMemCfgDEMOD_DVB_TDI.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_TDI   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_TDI.memory_base, gMemCfgDEMOD_DVB_TDI.memory_size);
			if (gMemCfgDEMOD_DVB_DJB.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_DJB   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_DJB.memory_base, gMemCfgDEMOD_DVB_DJB.memory_size);
			if (gMemCfgDEMOD_DVB_RISIC.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_RISIC base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_RISIC.memory_base, gMemCfgDEMOD_DVB_RISIC.memory_size);

			DEMOD_FW_ReInit(9);	// M23: set base addr
		}
		/* add your code if new chip supports memory share */
	}
	else if(lx_chip() == LX_CHIP_O24) //!//
	{
		UINT32 memory_base = 0;

		if(gPanama==TRUE)
		{
			// dvb + isdbt
			if((!strncmp(mode, str_dvb, strlen(str_dvb))) || (!strncmp(mode, str_isdbt, strlen(str_isdbt))))
			{
				UINT32 DVB_memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				gMemCfgDEMOD.memory_size = (gMemCfgDEMOD_ISDBT.memory_size > DVB_memory_size) ? gMemCfgDEMOD_ISDBT.memory_size : DVB_memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;

				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{
			if(!strncmp(mode, str_dvb, strlen(str_dvb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_dtmb, strlen(str_dtmb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DTMB.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DTMB.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_atsc3, strlen(str_atsc3)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ATSC3.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ATSC3.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_isdbt, strlen(str_isdbt)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ISDBT.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}

		}

		if (TRUE == _demod_mem_alloc_ok) {
			if (gMemCfgDEMOD_ATSC3.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ATSC3	   base 0x%08x, size %u\n", gMemCfgDEMOD_ATSC3.memory_base, gMemCfgDEMOD_ATSC3.memory_size);
			if (gMemCfgDEMOD_ISDBT.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_ISDBT	   base 0x%08x, size %u\n", gMemCfgDEMOD_ISDBT.memory_base, gMemCfgDEMOD_ISDBT.memory_size);
			if (gMemCfgDEMOD_DTMB.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DTMB	   base 0x%08x, size %u\n", gMemCfgDEMOD_DTMB.memory_base, gMemCfgDEMOD_DTMB.memory_size);

			if (gMemCfgDEMOD_DVB_TDI.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_TDI   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_TDI.memory_base, gMemCfgDEMOD_DVB_TDI.memory_size);
			if (gMemCfgDEMOD_DVB_DJB.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_DJB   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_DJB.memory_base, gMemCfgDEMOD_DVB_DJB.memory_size);
			if (gMemCfgDEMOD_DVB_RISIC.memory_base)
				DEMOD_INFO("gMemCfgDEMOD_DVB_RISIC base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_RISIC.memory_base, gMemCfgDEMOD_DVB_RISIC.memory_size);
		}
		/* add your code if new chip supports memory share */
	}
	else if(lx_chip() == LX_CHIP_O26) //chungiii 
	{
		UINT32 memory_base = 0;

		if(gPanama==TRUE)
		{
			// dvb + isdbt
			if((!strncmp(mode, str_dvb, strlen(str_dvb))) || (!strncmp(mode, str_isdbt, strlen(str_isdbt))))
			{
				UINT32 DVB_memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				gMemCfgDEMOD.memory_size = (gMemCfgDEMOD_ISDBT.memory_size > DVB_memory_size) ? gMemCfgDEMOD_ISDBT.memory_size : DVB_memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;

				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
		}
		else
		{
			if(!strncmp(mode, str_dvb, strlen(str_dvb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DVB_TDI.memory_size + gMemCfgDEMOD_DVB_DJB.memory_size + gMemCfgDEMOD_DVB_RISIC.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DVB_TDI.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_TDI.memory_size;
				gMemCfgDEMOD_DVB_DJB.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_DJB.memory_size;
				gMemCfgDEMOD_DVB_RISIC.memory_base	= memory_base;		memory_base += gMemCfgDEMOD_DVB_RISIC.memory_size;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_dtmb, strlen(str_dtmb)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_DTMB.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_DTMB.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_atsc3, strlen(str_atsc3)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ATSC3.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ATSC3.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}
			else if(!strncmp(mode, str_isdbt, strlen(str_isdbt)))
			{
				gMemCfgDEMOD.memory_size = gMemCfgDEMOD_ISDBT.memory_size;
				DEMOD_CHECK_ERROR(RET_OK != DEMOD_HmaAlloc(&gMemCfgDEMOD), 		goto func_exit, "register failed\n");
				memory_base = gMemCfgDEMOD.memory_base;

				// set for each standard
				gMemCfgDEMOD_ISDBT.memory_base		= memory_base;
				_demod_mem_alloc_ok = TRUE;
			}

		}

		if (TRUE == _demod_mem_alloc_ok) {
			if (gMemCfgDEMOD_ATSC3.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_ATSC3	   base 0x%08x, size %u\n", gMemCfgDEMOD_ATSC3.memory_base, gMemCfgDEMOD_ATSC3.memory_size);
			if (gMemCfgDEMOD_ISDBT.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_ISDBT	   base 0x%08x, size %u\n", gMemCfgDEMOD_ISDBT.memory_base, gMemCfgDEMOD_ISDBT.memory_size);
			if (gMemCfgDEMOD_DTMB.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_DTMB	   base 0x%08x, size %u\n", gMemCfgDEMOD_DTMB.memory_base, gMemCfgDEMOD_DTMB.memory_size);

			if (gMemCfgDEMOD_DVB_TDI.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_DVB_TDI   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_TDI.memory_base, gMemCfgDEMOD_DVB_TDI.memory_size);
			if (gMemCfgDEMOD_DVB_DJB.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_DVB_DJB   base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_DJB.memory_base, gMemCfgDEMOD_DVB_DJB.memory_size);
			if (gMemCfgDEMOD_DVB_RISIC.memory_base)
				DEMOD_NOTI("gMemCfgDEMOD_DVB_RISIC base 0x%08x, size %u\n", gMemCfgDEMOD_DVB_RISIC.memory_base, gMemCfgDEMOD_DVB_RISIC.memory_size);
		}
		/* add your code if new chip supports memory share */
	}

	if (TRUE == _demod_mem_alloc_ok) {
		pDemodDev->mem_alloc = _demod_mem_alloc_ok;
		DEMOD_NOTI("<!> demod mem alloc %s, %s, panama %s, 0x%08x, %dKB\n", (_demod_mem_alloc_ok)? "ok":"failed", mode, (TRUE == gPanama) ? "on" : "off", gMemCfgDEMOD.memory_base, gMemCfgDEMOD.memory_size);
		return;
	}
	else
	{
		if((gPanama==TRUE) && (!strncmp(mode, str_atsc3, strlen(str_atsc3))))
		{
			DEMOD_NOTI("<!> demod mem alloc skip!! %s, %s, panama %s\n", (_demod_mem_alloc_ok)? "ok":"failed", mode, (TRUE == gPanama) ? "on" : "off");
			return;
		}
	}


func_exit:
	//panic("demod mem alloc failed (%s)\n", mode);
	DEMOD_WARN("<!> demod(%s) memory register (%s)\n", mode, (_demod_mem_alloc_ok)? "ok":"failed");
}

/** @} */


