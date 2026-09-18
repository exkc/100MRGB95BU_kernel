#include "export_vsc_adapter.h"
//#include <stddef.h>
#include <linux/stddef.h>
#include <linux/export.h>
#include "base_types.h"
#include "base_device.h"
#include "de_kapi.h"

BOOLEAN gDoneRegisterAspectratioCB = FALSE;
ASPECTRATIO_CALLBACK_T gAspectratioCallbackFp;

void vsc_registerAspectratioCB(ASPECTRATIO_CALLBACK_T *pfn)
{
	if(pfn != NULL)
	{
		gAspectratioCallbackFp.pfnAspectratiodrvCalculate = pfn->pfnAspectratiodrvCalculate;
		gAspectratioCallbackFp.pfnOrbitdrvMoveConvert     = pfn->pfnOrbitdrvMoveConvert;
		gAspectratioCallbackFp.pfnOrbitdrvWindowConvert   = pfn->pfnOrbitdrvWindowConvert;
		gDoneRegisterAspectratioCB = TRUE;
	}
	else // if (pfn == NULL)
	{
		gAspectratioCallbackFp.pfnAspectratiodrvCalculate = NULL;
		gAspectratioCallbackFp.pfnOrbitdrvMoveConvert     = NULL;
		gAspectratioCallbackFp.pfnOrbitdrvWindowConvert   = NULL;
		gDoneRegisterAspectratioCB = TRUE;
	}
}
EXPORT_SYMBOL(vsc_registerAspectratioCB);

ASPECTRATIO_CALLBACK_T *vsc_getAspectratioCallbackFp(void)
{
	if (gDoneRegisterAspectratioCB)
		return &gAspectratioCallbackFp;
	else
		return NULL;
}
EXPORT_SYMBOL(vsc_getAspectratioCallbackFp);

