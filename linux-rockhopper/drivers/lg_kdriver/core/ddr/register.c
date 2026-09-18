
#if defined(CHIP_NAME_m23)
#include "REGISTER/register_m23.h"

volatile REG_DDRT_M0_T*      gpREG_DDRT_M0;
volatile REG_DDRC_M0_T*      gpREG_DDRC_M0;
volatile REG_DDRP_M0_T*      gpREG_DDRP_M0;
#endif

#if defined(CHIP_NAME_o24)
#include "REGISTER/register_o24.h"

volatile REG_DDRT_M0_T*      gpREG_DDRT_M0;
volatile REG_DDRC_M0_T*      gpREG_DDRC_M0;
volatile REG_DDRP_M0_T*      gpREG_DDRP_M0;

volatile REG_DPG0_M0_T*      gpREG_DPG0_M0;
volatile REG_DPG1_M0_T*      gpREG_DPG1_M0;
volatile REG_DPG2_M0_T*      gpREG_DPG2_M0;
volatile REG_DPG3_M0_T*      gpREG_DPG3_M0;

volatile REG_DDRT_M1_T*      gpREG_DDRT_M1;
volatile REG_DDRC_M1_T*      gpREG_DDRC_M1;
volatile REG_DDRP_M1_T*      gpREG_DDRP_M1;

volatile REG_DPG0_M1_T*      gpREG_DPG0_M1;
volatile REG_DPG1_M1_T*      gpREG_DPG1_M1;
volatile REG_DPG2_M1_T*      gpREG_DPG2_M1;
volatile REG_DPG3_M1_T*      gpREG_DPG3_M1;

volatile REG_MCU_T*          gpREG_MCU;
volatile REG_SYSTEM_T*       gpREG_SYSTEM;
#endif

/**
 * M23
 * volatile REG_DDRT_M0_T*      gpREG_DDRT_M0       = (volatile REG_DDRT_M0_T*)     (APB_DDRT_M0_BASE);
 * volatile REG_DDRC_M0_T*      gpREG_DDRC_M0       = (volatile REG_DDRC_M0_T*)     (APB_DDRC_M0_BASE);
 * volatile REG_DDRP_M0_T*      gpREG_DDRP_M0       = (volatile REG_DDRP_M0_T*)     (APB_DDRP_M0_BASE);
 * volatile REG_PHY_CRG_M0_T*   gpREG_PHY_CRG_M0    = (volatile REG_PHY_CRG_M0_T*)  (APB_PHY_CRG_M0_BASE);
 * volatile REG_DPG0_M0_T*      gpREG_DPG0_M0       = (volatile REG_DPG0_M0_T*)     (APB_DPG0_M0_BASE);
 * volatile REG_DPG1_M0_T*      gpREG_DPG1_M0       = (volatile REG_DPG1_M0_T*)     (APB_DPG1_M0_BASE);
 * volatile REG_DPG2_M0_T*      gpREG_DPG2_M0       = (volatile REG_DPG2_M0_T*)     (APB_DPG2_M0_BASE);
 * volatile REG_DPG3_M0_T*      gpREG_DPG3_M0       = (volatile REG_DPG3_M0_T*)     (APB_DPG3_M0_BASE);
 */


/**
 * O24
 * volatile REG_DDRT_M0_T*      gpREG_DDRT_M0       = (volatile REG_DDRT_M0_T*)     (APB_DDRT_M0_BASE);
 * volatile REG_DDRC_M0_T*      gpREG_DDRC_M0       = (volatile REG_DDRC_M0_T*)     (APB_DDRC_M0_BASE);
 * volatile REG_DDRP_M0_T*      gpREG_DDRP_M0       = (volatile REG_DDRP_M0_T*)     (APB_DDRP_M0_BASE);
 * volatile REG_PHY_CRG_M0_T*   gpREG_PHY_CRG_M0    = (volatile REG_PHY_CRG_M0_T*)  (APB_PHY_CRG_M0_BASE);
 * volatile REG_DPG0_M0_T*      gpREG_DPG0_M0       = (volatile REG_DPG0_M0_T*)     (APB_DPG0_M0_BASE);
 * volatile REG_DPG1_M0_T*      gpREG_DPG1_M0       = (volatile REG_DPG1_M0_T*)     (APB_DPG1_M0_BASE);
 * volatile REG_DPG2_M0_T*      gpREG_DPG2_M0       = (volatile REG_DPG2_M0_T*)     (APB_DPG2_M0_BASE);
 * volatile REG_DPG3_M0_T*      gpREG_DPG3_M0       = (volatile REG_DPG3_M0_T*)     (APB_DPG3_M0_BASE);
 * volatile REG_DDRT_M1_T*      gpREG_DDRT_M1       = (volatile REG_DDRT_M1_T*)     (APB_DDRT_M1_BASE);
 * volatile REG_DDRC_M1_T*      gpREG_DDRC_M1       = (volatile REG_DDRC_M1_T*)     (APB_DDRC_M1_BASE);
 * volatile REG_DDRP_M1_T*      gpREG_DDRP_M1       = (volatile REG_DDRP_M1_T*)     (APB_DDRP_M1_BASE);
 * volatile REG_PHY_CRG_M1_T*   gpREG_PHY_CRG_M1    = (volatile REG_PHY_CRG_M1_T*)  (APB_PHY_CRG_M1_BASE);
 * volatile REG_DPG0_M1_T*      gpREG_DPG0_M1       = (volatile REG_DPG0_M1_T*)     (APB_DPG0_M1_BASE);
 * volatile REG_DPG1_M1_T*      gpREG_DPG1_M1       = (volatile REG_DPG1_M1_T*)     (APB_DPG1_M1_BASE);
 * volatile REG_DPG2_M1_T*      gpREG_DPG2_M1       = (volatile REG_DPG2_M1_T*)     (APB_DPG2_M1_BASE);
 * volatile REG_DPG3_M1_T*      gpREG_DPG3_M1       = (volatile REG_DPG3_M1_T*)     (APB_DPG3_M1_BASE);
 * volatile REG_DDRT_M2_T*      gpREG_DDRT_M2       = (volatile REG_DDRT_M2_T*)     (APB_DDRT_M2_BASE);
 * volatile REG_DDRC_M2_T*      gpREG_DDRC_M2       = (volatile REG_DDRC_M2_T*)     (APB_DDRC_M2_BASE);
 * volatile REG_DDRP_M2_T*      gpREG_DDRP_M2       = (volatile REG_DDRP_M2_T*)     (APB_DDRP_M2_BASE);
 * volatile REG_PHY_CRG_M2_T*   gpREG_PHY_CRG_M2    = (volatile REG_PHY_CRG_M2_T*)  (APB_PHY_CRG_M2_BASE);
 * volatile REG_DPG0_M2_T*      gpREG_DPG0_M2       = (volatile REG_DPG0_M2_T*)     (APB_DPG0_M2_BASE);
 * volatile REG_DPG1_M2_T*      gpREG_DPG1_M2       = (volatile REG_DPG1_M2_T*)     (APB_DPG1_M2_BASE);
 * volatile REG_DPG2_M2_T*      gpREG_DPG2_M2       = (volatile REG_DPG2_M2_T*)     (APB_DPG2_M2_BASE);
 * volatile REG_DPG3_M2_T*      gpREG_DPG3_M2       = (volatile REG_DPG3_M2_T*)     (APB_DPG3_M2_BASE);
 * volatile REG_WDOG_T*         gpREG_WDOG          = (volatile REG_WDOG_T*)        (APB_WDOG_BASE);
 * volatile REG_GPIO_T*         gpREG_GPIO          = (volatile REG_GPIO_T*)        (APB_GPIO_BASE);
 * volatile REG_MCU_T*          gpREG_MCU           = (volatile REG_MCU_T*)         (APB_MCU_BASE);
 * volatile REG_SYSTEM_T*       gpREG_SYSTEM        = (volatile REG_SYSTEM_T*)      (APB_SYSTEM_BASE);
 */
