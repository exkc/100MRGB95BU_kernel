#ifndef _REGISTER_O24
#define _REGISTER_O24

typedef unsigned int UINT32; /* REGISTER */

#include "O24/O24_REG_DDRT_M0.h"
#include "O24/O24_REG_DDRC_M0.h"
#include "O24/O24_REG_DDRP_M0.h"
#include "O24/O24_REG_PHY_CRG_M0.h"
#include "O24/O24_REG_DPG0_M0.h"
#include "O24/O24_REG_DPG1_M0.h"
#include "O24/O24_REG_DPG2_M0.h"
#include "O24/O24_REG_DPG3_M0.h"
#include "O24/O24_REG_DDRT_M1.h"
#include "O24/O24_REG_DDRC_M1.h"
#include "O24/O24_REG_DDRP_M1.h"
#include "O24/O24_REG_PHY_CRG_M1.h"
#include "O24/O24_REG_DPG0_M1.h"
#include "O24/O24_REG_DPG1_M1.h"
#include "O24/O24_REG_DPG2_M1.h"
#include "O24/O24_REG_DPG3_M1.h"
#include "O24/O24_REG_DDRT_M2.h"
#include "O24/O24_REG_DDRC_M2.h"
#include "O24/O24_REG_DDRP_M2.h"
#include "O24/O24_REG_PHY_CRG_M2.h"
#include "O24/O24_REG_DPG0_M2.h"
#include "O24/O24_REG_DPG1_M2.h"
#include "O24/O24_REG_DPG2_M2.h"
#include "O24/O24_REG_DPG3_M2.h"
#include "O24/O24_REG_WDOG.h"
#include "O24/O24_REG_GPIO.h"
#include "O24/O24_REG_MCU.h"
#include "O24/O24_REG_SYSTEM.h"

#define APB_DDRT_M0_BASE     ( 0xC4D07100 )
#define APB_DDRC_M0_BASE     ( 0xC4D00000 )
#define APB_DDRP_M0_BASE     ( 0xC4D08000 )
#define APB_PHY_CRG_M0_BASE  ( 0xC4D0F000 )
#define APB_DPG0_M0_BASE     ( 0xC4D04100 )
#define APB_DPG1_M0_BASE     ( 0xC4D04300 )
#define APB_DPG2_M0_BASE     ( 0xC4D04500 )
#define APB_DPG3_M0_BASE     ( 0xC4D04700 )
#define APB_DDRT_M1_BASE     ( 0xC4907100 )
#define APB_DDRC_M1_BASE     ( 0xC4900000 )
#define APB_DDRP_M1_BASE     ( 0xC4908000 )
#define APB_PHY_CRG_M1_BASE  ( 0xC490F000 )
#define APB_DPG0_M1_BASE     ( 0xC4904100 )
#define APB_DPG1_M1_BASE     ( 0xC4904300 )
#define APB_DPG2_M1_BASE     ( 0xC4904500 )
#define APB_DPG3_M1_BASE     ( 0xC4904700 )
#define APB_DDRT_M2_BASE     ( 0xC4507100 )
#define APB_DDRC_M2_BASE     ( 0xC4500000 )
#define APB_DDRP_M2_BASE     ( 0xC4508000 )
#define APB_PHY_CRG_M2_BASE  ( 0xC450F000 )
#define APB_DPG0_M2_BASE     ( 0xC4504100 )
#define APB_DPG1_M2_BASE     ( 0xC4504300 )
#define APB_DPG2_M2_BASE     ( 0xC4504500 )
#define APB_DPG3_M2_BASE     ( 0xC4504700 )
#define APB_WDOG_BASE        ( 0xF40C0000 )
#define APB_GPIO_BASE        ( 0xF40C2000 )
#define APB_MCU_BASE         ( 0xF40CE000 )
#define APB_SYSTEM_BASE      ( 0xF40CF000 )

extern volatile REG_DDRT_M0_T*       gpREG_DDRT_M0;
extern volatile REG_DDRC_M0_T*       gpREG_DDRC_M0;
extern volatile REG_DDRP_M0_T*       gpREG_DDRP_M0;
/*
 * extern volatile REG_PHY_CRG_M0_T*    gpREG_PHY_CRG_M0;
 */
extern volatile REG_DPG0_M0_T*       gpREG_DPG0_M0;
extern volatile REG_DPG1_M0_T*       gpREG_DPG1_M0;
extern volatile REG_DPG2_M0_T*       gpREG_DPG2_M0;
extern volatile REG_DPG3_M0_T*       gpREG_DPG3_M0;

extern volatile REG_DDRT_M1_T*       gpREG_DDRT_M1;
extern volatile REG_DDRC_M1_T*       gpREG_DDRC_M1;
extern volatile REG_DDRP_M1_T*       gpREG_DDRP_M1;
/*
 * extern volatile REG_PHY_CRG_M1_T*    gpREG_PHY_CRG_M1;
 */
extern volatile REG_DPG0_M1_T*       gpREG_DPG0_M1;
extern volatile REG_DPG1_M1_T*       gpREG_DPG1_M1;
extern volatile REG_DPG2_M1_T*       gpREG_DPG2_M1;
extern volatile REG_DPG3_M1_T*       gpREG_DPG3_M1;

/*
 * extern volatile REG_DDRT_M2_T*       gpREG_DDRT_M2;
 * extern volatile REG_DDRC_M2_T*       gpREG_DDRC_M2;
 * extern volatile REG_DDRP_M2_T*       gpREG_DDRP_M2;
 * extern volatile REG_PHY_CRG_M2_T*    gpREG_PHY_CRG_M2;
 * extern volatile REG_DPG0_M2_T*       gpREG_DPG0_M2;
 * extern volatile REG_DPG1_M2_T*       gpREG_DPG1_M2;
 * extern volatile REG_DPG2_M2_T*       gpREG_DPG2_M2;
 * extern volatile REG_DPG3_M2_T*       gpREG_DPG3_M2;
 */
/*
 * extern volatile REG_WDOG_T*          gpREG_WDOG;
 * extern volatile REG_GPIO_T*          gpREG_GPIO;
 */
extern volatile REG_MCU_T*           gpREG_MCU;
extern volatile REG_SYSTEM_T*        gpREG_SYSTEM;

//
#define REG_RD(addr)        (*(const volatile unsigned int __force *) (addr))
#define REG_WR(addr,b)      (*(volatile unsigned int __force *) (addr) = (b))
#define REG_ARD(addr)       REG_RD(&(addr))
#define REG_AWR(addr,b)     REG_WR(&(addr),(b))

#endif /* _REGISTER_O24 */
