#ifndef _REGISTER_M23
#define _REGISTER_M23

typedef unsigned int UINT32; /* REGISTER */

#include "M23/M23_REG_DDRT_M0.h"
#include "M23/M23_REG_DDRC_M0.h"
#include "M23/M23_REG_DDRP_M0.h"
#include "M23/M23_REG_PHY_CRG_M0.h"
#include "M23/M23_REG_DPG0_M0.h"
#include "M23/M23_REG_DPG1_M0.h"
#include "M23/M23_REG_DPG2_M0.h"
#include "M23/M23_REG_DPG3_M0.h"

#define APB_DDRT_M0_BASE     ( 0xC4F47100 )
#define APB_DDRC_M0_BASE     ( 0xC4F40000 )
#define APB_DDRP_M0_BASE     ( 0xC4F48000 )
#define APB_PHY_CRG_M0_BASE  ( 0xC4F4F000 )
#define APB_DPG0_M0_BASE     ( 0xC4F44100 )
#define APB_DPG1_M0_BASE     ( 0xC4F44300 )
#define APB_DPG2_M0_BASE     ( 0xC4F44500 )
#define APB_DPG3_M0_BASE     ( 0xC4F44700 )

extern volatile REG_DDRT_M0_T*       gpREG_DDRT_M0;
extern volatile REG_DDRC_M0_T*       gpREG_DDRC_M0;
extern volatile REG_DDRP_M0_T*       gpREG_DDRP_M0;
/*
 * extern volatile REG_PHY_CRG_M0_T*    gpREG_PHY_CRG_M0;
 * extern volatile REG_DPG0_M0_T*       gpREG_DPG0_M0;
 * extern volatile REG_DPG1_M0_T*       gpREG_DPG1_M0;
 * extern volatile REG_DPG2_M0_T*       gpREG_DPG2_M0;
 * extern volatile REG_DPG3_M0_T*       gpREG_DPG3_M0;
 */

//
#define REG_RD(addr)        (*(const volatile unsigned int __force *) (addr))
#define REG_WR(addr,b)      (*(volatile unsigned int __force *) (addr) = (b))
#define REG_ARD(addr)       REG_RD(&(addr))
#define REG_AWR(addr,b)     REG_WR(&(addr),(b))

#endif /* _REGISTER_M23 */
