#include "export_vsc_orbit_adapter.h"
//#include <stddef.h>
#include <linux/stddef.h>
#include <linux/export.h>
#include "base_types.h"
#include "base_device.h"
#include "de_kapi.h"

bool gDoneRegisterOrbitCB = false;
ORBIT_CALLBACK_T gOrbitCallbackFp;

void vsc_registerOrbitCB(ORBIT_CALLBACK_T *pfn)
{
    if (pfn != NULL) {
        gOrbitCallbackFp.pfnCalculateOrbitPosition = pfn->pfnCalculateOrbitPosition;
        gDoneRegisterOrbitCB                       = true;
    } else {
        gOrbitCallbackFp.pfnCalculateOrbitPosition = NULL;
        gDoneRegisterOrbitCB                       = false;
    }
}
EXPORT_SYMBOL(vsc_registerOrbitCB);

ORBIT_CALLBACK_T *vsc_getOrbitCallbackFp(void)
{
    if (gDoneRegisterOrbitCB)
        return &gOrbitCallbackFp;
    else
        return NULL;
}
EXPORT_SYMBOL(vsc_getOrbitCallbackFp);

