/*****************************************************************************************
 * SIC R&D LAB, LG ELECTRONICS INC., SEOUL, KOREA
 * COPYRIGHT(c) 2011,2012 by LG Electronics Inc.
 *
 * All rights reserved. No part of this work covered by this copyright hereon
 * may be reproduced, stored in a retrieval system, in any form
 * or by any means, electronic, mechanical, photocopying, recording
 * or otherwise, without the prior written  permission of LG Electronics.
 ****************************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     <none>
 *  @version    1.0
 *  @date       2021-03-31
 *  @note       Additional information.
 */

#ifndef	_PQE_PM_IMPL_H_
#define	_PQE_PM_IMPL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define PQE_PM_NUM_MAX  32
#define	PQE_PM_MODULE	"pqepm"

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/delay.h>

#include "debug_util.h"
#include "os_util.h"
#include "pqe_pm_drv.h"

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
#define pqe_pm_error(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define pqe_pm_warn(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define pqe_pm_noti(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define pqe_pm_info(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define pqe_pm_debug(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define pqe_pm_trace(format, args...)	DBG_PRINT( g_pqe_pm_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define pqe_pm_check_noti(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, pqe_pm_noti, __if_action , fmt, ##args )

#define pqe_pm_check_error(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, pqe_pm_error, __if_action , fmt, ##args )

#define pqe_pm_assert(__checker)   \
            __CHECK_IF_ERROR( !(__checker), pqe_pm_warn, /* nop */, "assert failed. %s\n", #__checker)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void pqe_pm_init_proc(void);
void pqe_pm_cleanup_proc(void);

void pqe_pm_print_status(struct seq_file *m);
void pqe_pm_print_dbg_hw(struct seq_file *m);

#ifdef INCLUDE_O20_CHIP_KDRV
void pqe_pm_init_o20_hw_ctx(void);
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
void pqe_pm_init_o22_hw_ctx(void);
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
void pqe_pm_init_m23_hw_ctx(void);
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
void pqe_pm_init_o24_hw_ctx(void);
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
void pqe_pm_init_o26_hw_ctx(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int g_pqe_pm_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

