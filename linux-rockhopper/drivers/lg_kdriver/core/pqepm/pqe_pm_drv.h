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

#ifndef	_PQE_PM_DRV_H_
#define	_PQE_PM_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define	PQE_PM_NAME_MAX			32

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

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
enum
{
	PQE_PM_DEVICE_SUSPEND_PREPARE = 0,
	PQE_PM_DEVICE_SUSPEND,
	PQE_PM_DEVICE_SUSPEND_COMPLETED,

	PQE_PM_DEVICE_RESUME_PREPARE,
	PQE_PM_DEVICE_RESUME,
	PQE_PM_DEVICE_RESUME_COMPLETED,

	PQE_PM_DEVICE_ACTION_MAX,
};

enum
{
	PQE_PM_HW_FW_SUSPEND = 0,
	PQE_PM_HW_CG_ON,
	PQE_PM_HW_CG_OFF,
	PQE_PM_HW_FW_RESUME,

	PQE_PM_HW_ACTION_MAX,
};

enum
{
	PQE_PM_OPT_NONE = 0x0,
	PQE_PM_OPT_MONITOR = 0x1000,
};

struct pqe_pm_config {
    char name[PQE_PM_NAME_MAX];
	unsigned int opt;
    int order;

    int id;//read only
	int (*callback)(int);
};

void pqe_pm_register_hw_handler(int(*handler)(int));
void pqe_pm_register_enable(int* enable);

int pqe_pm_register(struct pqe_pm_config* cfg);
int pqe_pm_unregister(int pm_id);

int pqe_pm_request_resume(int pm_id);
int pqe_pm_request_suspend(int pm_id);

void pqe_pm_dbg_set_mask(int type, int data);

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void	pqe_pm_preinit(void);
extern int 	pqe_pm_initialize(void);
extern void	pqe_pm_cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

