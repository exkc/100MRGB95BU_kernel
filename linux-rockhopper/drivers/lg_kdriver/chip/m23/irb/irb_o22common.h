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
 *  author		jun.kong
 *  version		1.0
 *  date			2017.04.13
 *  note			Additional information.
 *
 *  @addtogroup
 */


#ifndef	_IRB_O22_COMMON_H_
#define	_IRB_O22_COMMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "irb_cfg.h"
#include "irb_kapi.h"
#include "irb_drv.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#define O22_IRB_BASE 0xf9600000



typedef struct o22_irb_unit
{
  volatile unsigned int dr;
  volatile unsigned int dr_cr;
  volatile unsigned int dr_zero;
  volatile unsigned int dr_one;
} o22_irb_unit_t;


typedef struct o22_irb
{
  volatile unsigned int cr;
  volatile unsigned int const sr;
  volatile unsigned int icrd;
  volatile unsigned int fcrd;
  volatile unsigned int tpr;
  volatile unsigned int rpr;
  volatile unsigned int rpsr;
  unsigned int const reserved1;
  volatile unsigned int imsc;
  volatile unsigned int const ris;
  volatile unsigned int const mis;
  volatile unsigned int icr;
  unsigned int const reserved2[48];
  volatile unsigned int cpr;
  volatile unsigned int tr;
  unsigned int const reserved3[2];
  o22_irb_unit_t prot_data[31];
  o22_irb_unit_t rpt_data[2];
} o22_irb_t;

#if 0
typedef struct
{
  void (*init)(int index);
  void (*exit)(void);
  int (*status)(int prot_or_rpt);
  void (*tx)(int ptype);
} irblaster_driver_t;

irblaster_driver_t* get_irblaster_driver(void);

void irblaster_init(int index);
void irblaster_exit(void);
int irblaster_status(int prot_or_rpt);
void irblaster_tx(int ptype);
#endif




/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	volatile unsigned int	current_freq;
	volatile unsigned int	target_freq;
	volatile unsigned int	target_vol;
	volatile unsigned int	target_corevol;
	volatile unsigned int	do_dvfs;
	volatile unsigned int	core_onoff;
	volatile unsigned int	core_n;
	volatile unsigned int	do_hotplug;
	volatile unsigned int	do_avs;
}irbs_o22_work_t;




typedef struct
{
	void  			(*init)(void);
	void  			(*reinit)(void);
  	void (*exit)(void);
  	int (*status)(int prot_or_rpt);
	int				(*tx)(LX_IRB_PARAM_T *);


} irbs_o22_func_t;



/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
irbs_proc_t* get_o22_irb_proc(void);
irbs_o22_func_t* get_o22_irb_func(void);
irbs_driver_t* get_o22_irb_driver(void);

extern unsigned int  o22_get_micom_disable(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _IRB_DRV_H_ */

/** @} */
