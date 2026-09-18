/*****************************************************************************************
 * SIC R&D LAB, LG ELECTRONICS INC., SEOUL, KOREA
 * COPYRIGHT(c) 2011,2012 by LG Electronics Inc.
 *
 * All rights reserved. No part of this work covered by this copyright hereon
 * may be reproduced, stored in a retrieval system, in any form
 * or by any means, electronic, mechanical, photocopying, recording
 * or otherwise, without the prior written  permission of LG Electronics.
 ****************************************************************************************/
#include <linux/kernel.h>
#include "pqe_pm_drv.h"

int pqe_pm_register(struct pqe_pm_config* pCfg)
{
	// do nothing
	return 0;
}
EXPORT_SYMBOL(pqe_pm_register);

int pqe_pm_unregister(int pm_id)
{
	// do nothing
	return RET_OK;
}
EXPORT_SYMBOL(pqe_pm_unregister);

int pqe_pm_request_resume(int pm_id)
{
	// do nothing
	return RET_OK;
}
EXPORT_SYMBOL(pqe_pm_request_resume);

int pqe_pm_request_suspend(int pm_id)
{
	// do nothing
	return RET_OK;
}
EXPORT_SYMBOL(pqe_pm_request_suspend);

