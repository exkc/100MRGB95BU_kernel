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
 *  main driver implementation for micom device.
 *	micom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2017.04.13
 *  note			Additional information.
 *
 *  @addtogroup
 */


#ifndef	_UCOM_O26_COMMON_H_
#define	_UCOM_O26_COMMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "ucom_cfg.h"
#include "ucom_kapi.h"
#include "ucom_drv.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define MAILBOX(m)	((m) << 5) //64byte
#define REG(n)	((n) << 2)

//#define USE_O26_IPC_INTR 

#ifdef USE_O26_IPC_INTR
#define O26_UCOM_TIMEOUT	300 //(ms)
#else
#define O26_UCOM_TIMEOUT	25  //(ms)
#endif

extern OS_SEM_T			o26_ucom_mutex;

#define O26_KDRV_UCOM_LOCK_INIT()		OS_InitMutex(&o26_ucom_mutex, OS_SEM_ATTR_DEFAULT)
#define O26_KDRV_UCOM_LOCK()                      \
    do{                                             \
        if(OS_LockMutex(&o26_ucom_mutex) < 0)             \
        {                                           \
            KDRV_UCOM_ERROR("Mutex Lock Fail\n");   \
            return -1;                              \
        }                                           \
    }while(0)

#define O26_KDRV_UCOM_UNLOCK()                    \
    do{                                             \
        OS_UnlockMutex(&o26_ucom_mutex);                  \
    }while(0)

typedef struct
{
	void	(*init)(void);
	void	(*chipreset)(void);
	int	  (*getstatus)(void);
	int	  (*write)(LX_UCOM_PARAM_T * param);
	int	  (*read)(LX_UCOM_PARAM_T * param);

} ucom_o26_func_t;

typedef struct
{
	UINT8 init;
	UINT8 irq;
}ucom_o26_data_t;
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
ucom_proc_t* get_o26_ucom_proc(void);
ucom_o26_func_t* get_o26_ucom_func(void);
ucom_driver_t* get_o26_ucom_driver(void);

extern int o26_ucom_spi_read( UINT8 * addr,  UINT8 * data , UINT8  num );
extern int o26_ucom_spi_write( UINT8 * addr,  UINT8 * data , UINT8  num );

extern UINT32 o26_ucom_spi_read32(UINT32 addr);
extern int o26_ucom_spi_write32( UINT32 addr, UINT32 val);


extern unsigned int  o26_get_micom_disable(void);
extern void o26_set_micom_disable( unsigned int);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _UCOM_O26_COMMON_H_ */

/** @} */
