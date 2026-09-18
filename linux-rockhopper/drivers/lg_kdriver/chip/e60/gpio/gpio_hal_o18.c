/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		jun.kong
 *  @version	1.0
 *  @date		2016-05-02
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include "gpio_drv.h"
#include "gpio_kapi.h"
#include "gpio_reg.h"
#include "gpio_core.h"

#include <linux/irq.h>
#include <linux/interrupt.h>

#ifdef INCLUDE_O18_CHIP_KDRV
#include "../../chip/o18/os/linux_irqs.h"
#endif	//#ifdef INCLUDE_O18_CHIP_KDRV
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_O18_CHIP_KDRV
#if defined (CHIP_NAME_o18)
UINT32 		gpio_intr_num_o18[GPIO_IRQ_NUM_NR] = {
#else
UINT32 		gpio_intr_num_o18[GPIO_IRQ_NUM_NR_18] = {
#endif

O18_IRQ_GPIO0,
O18_IRQ_GPIO1,
O18_IRQ_GPIO2,
O18_IRQ_GPIO3,
O18_IRQ_GPIO4,
O18_IRQ_GPIO5,
O18_IRQ_GPIO6,
O18_IRQ_GPIO7,
O18_IRQ_GPIO8,
O18_IRQ_GPIO9,
O18_IRQ_GPIO10,
O18_IRQ_GPIO11,
O18_IRQ_GPIO12,
O18_IRQ_GPIO13,
O18_IRQ_GPIO14,
O18_IRQ_GPIO15,
O18_IRQ_GPIO16,
O18_IRQ_GPIO17};
extern GPIO_INTR_INFO_T gpio_isr_info[GPIO_PIN_MAX];


/*========================================================================================
	Implementation Group
========================================================================================*/

int abnormal_intr_cnt = 0;

 void _GPIO_ISR_GPIO_O18( unsigned int ui32IRQNum, unsigned int IntData )
{
	UINT32	gpio_array_n;
	LX_GPIO_INFO_T  intrinfo;
	UINT32	ui32Status = 0,ui32Status0 = 0;
	UINT8	ucGpio = 0, realGpio = 0;
	ULONG 	flags = 0;
	//GPIO_ERROR("_GPIO_ISR_GPIO0Hdr [%d] \n", ui32IRQNum);

	LX_GPIO_VALUE_T value =LX_GPIO_VALUE_INVALID ;

	if (ui32IRQNum >= O18_IRQ_GPIO0 && ui32IRQNum <=O18_IRQ_GPIO17)
		gpio_array_n = ui32IRQNum-O18_IRQ_GPIO0;
	else
	{
		GPIO_ERROR("this intr is not a gpio intr\n");
		return;
	}

	ui32Status0 = GPIONMIS(gpio_array_n);

	GPIO_DEBUG("MIS [%x]gpio_array_n[%d] \n", GPIONMIS(gpio_array_n),gpio_array_n);
	GPIO_DEBUG("RIS [%x] \n", GPIONRIS(gpio_array_n));
	GPIO_DEBUG("MIS [%x]\n", GPIONMIS(gpio_array_n));

	/* Clear the interrupt */


	if(ui32Status0 != 0)
	{
		ui32Status =ui32Status0;
		gpio_array_n = gpio_array_n;
		//GPIONIC(gpio_array_n) =ui32Status;
	}

	GPIONIC(gpio_array_n) =ui32Status;

	for ( ucGpio = 0; ucGpio <= GPIO_NUM_IN_ARRAY; ++ucGpio )
	{
		if ( 0 == ui32Status ) break;

		/* Check for gpio interrupt */
		if ( ui32Status & ( 1 << ucGpio ) )
		{
			/* Check if the handler mask for the gpio is enabled */
			if ( GPIONIE(gpio_array_n) & ( 1 << ucGpio ) )
			{
				/* invoked the registered callback routine */
				realGpio = ucGpio + 8*(gpio_array_n);

				if (gpio_isr_info[realGpio].cb_enable)
				{
					_GPIO_GetValue(realGpio, &value );
					GPIO_DEBUG("_GPIO_ISR_GPIO_O18 		pin[%d] value[%d]\n",realGpio, value);
					spin_lock_irqsave(&gpioPoll_lock, flags);
					gpio_intr_pin = realGpio + 1;
					gpio_intr_pin_value = value;
					spin_unlock_irqrestore(&gpioPoll_lock, flags);

					if(gpio_intr_pin)
					{
						wake_up_interruptible_all(gGPIOPollWaitQueueT[realGpio/GPIO_NUM_IN_INT_ARRAY]);
					}
				}

				if (gpio_isr_info[realGpio].count_enable )
				{
					int cktime = 0, measure = 0;
					/* start */
					if (gpio_isr_info[realGpio].intr_count == gpio_isr_info[realGpio].start_count)
					{
						cktime = (int)(ktime_to_us(ktime_get()));
						gpio_isr_info[realGpio].start 	 = (int)cktime;
						gpio_isr_info[realGpio].measured = (int)cktime;
					}
					else if (gpio_isr_info[realGpio].intr_count  == LAST_SAMPLE)
					{
						cktime = (int)(ktime_to_us(ktime_get()));
						measure = (int)( cktime - (int)gpio_isr_info[realGpio].measured );


						if(measure < VALID_DURATION_MIN )
						{
							abnormal_intr_cnt++;
							if(abnormal_intr_cnt > DURATATION_RETRY_CNT )
							{
								GPIO_INFO("gpioabnormal measured[%d] abnormacnt[%d]\n",measure,abnormal_intr_cnt );
								gpio_isr_info[realGpio].dur = (int)( (int)cktime  - (int)gpio_isr_info[realGpio].start);
								_GPIO_SetIntrAction(realGpio, NULL, COUNT_DISABLE, &intrinfo);
								abnormal_intr_cnt = 0;
							}
							gpio_isr_info[realGpio].intr_count  += 1;
						}
						else
						{
							gpio_isr_info[realGpio].dur = (int)( (int)cktime - (int)gpio_isr_info[realGpio].start);
							abnormal_intr_cnt = 0;
							_GPIO_SetIntrAction(realGpio, NULL, COUNT_DISABLE, &intrinfo);
						}
					}
					else if (gpio_isr_info[realGpio].intr_count > gpio_isr_info[realGpio].start_count)
					{
					}
					else
					{
					    cktime = (int)(ktime_to_us(ktime_get()));
						measure  = (int)( cktime - (int)gpio_isr_info[realGpio].measured );
						gpio_isr_info[realGpio].measured = (int)cktime;
						if(measure  < VALID_DURATION_MIN )
						{
							 abnormal_intr_cnt++;
							 gpio_isr_info[realGpio].intr_count  += 1;
						}
						else
						{
						  abnormal_intr_cnt = 0;
						}
					}

					if(   gpio_isr_info[realGpio].intr_count > 0)
					   gpio_isr_info[realGpio].intr_count--;
					GPIO_INFO("realGpio [%d] intrcnt [%d] start_count[%d]\n ",realGpio, gpio_isr_info[realGpio].intr_count,gpio_isr_info[realGpio].start_count);

				}
			}

			/* Clear the serviced status */
			ui32Status ^= ( 1 << ucGpio );
			//GPIONIC(gpio_array_n) =ui32Status;
		}
	}
}
#endif



