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

#ifdef INCLUDE_M17_CHIP_KDRV
#include "../../chip/m17/os/linux_irqs.h"
#endif	//#ifdef INCLUDE_M17_CHIP_KDRV
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
#ifdef INCLUDE_M17_CHIP_KDRV
UINT32 		gpio_intr_num_m17[GPIO_IRQ_NUM_NR] = {M17_IRQ_GPIO0_2,M17_IRQ_GPIO3_5,M17_IRQ_GPIO6_8,M17_IRQ_GPIO9_11,M17_IRQ_GPIO12_14,M17_IRQ_GPIO15_17};
extern GPIO_INTR_INFO_T gpio_isr_info[GPIO_PIN_MAX];


/*========================================================================================
	Implementation Group
========================================================================================*/

 void _GPIO_ISR_GPIO_M17( unsigned int ui32IRQNum, unsigned int IntData )
{
	UINT32	gpio_array_n;
	LX_GPIO_INFO_T  intrinfo;
	UINT32	ui32Status = 0,ui32Status0 = 0,ui32Status1 = 0,ui32Status2 =0;
	UINT8	ucGpio = 0, realGpio = 0;
	ULONG 	flags = 0;
	//GPIO_ERROR("_GPIO_ISR_GPIO0Hdr [%d] \n", ui32IRQNum);

	LX_GPIO_VALUE_T value =LX_GPIO_VALUE_INVALID ;

	if (ui32IRQNum >= M17_IRQ_GPIO0_2 && ui32IRQNum <=M17_IRQ_GPIO15_17)
		gpio_array_n = ui32IRQNum-M17_IRQ_GPIO0_2;
	else
	{
		GPIO_ERROR("this intr is not a gpio intr\n");
		return;
	}


	switch( ui32IRQNum )
	{
		case M17_IRQ_GPIO0_2 :
			gpio_array_n = 0;
			break;
		case M17_IRQ_GPIO3_5 :
			gpio_array_n = 3;
			break;
		case M17_IRQ_GPIO6_8 :
			gpio_array_n = 6;
			break;
		case M17_IRQ_GPIO9_11 :
			gpio_array_n = 9;
			break;
		case M17_IRQ_GPIO12_14 :
			gpio_array_n = 12;
			break;
		case M17_IRQ_GPIO15_17 :
			gpio_array_n = 15;
			break;
		default:
			GPIO_ERROR("check gpio array num\n");
			break;

	}

	ui32Status0 = GPIONMIS(gpio_array_n);
	ui32Status1 = GPIONMIS(gpio_array_n + 1);
	ui32Status2 = GPIONMIS(gpio_array_n + 2);

	GPIO_DEBUG("MIS [%x][%x][%x]gpio_array_n[%d] \n", GPIONMIS(gpio_array_n),GPIONMIS(gpio_array_n + 1),GPIONMIS(gpio_array_n + 2),gpio_array_n);
	GPIO_DEBUG("RIS [%x][%x][%x][%x][%x][%x][%x][%x] \n", GPIONRIS(0),GPIONRIS(1),GPIONRIS(2),GPIONRIS(3),GPIONRIS(4),GPIONRIS(5),GPIONRIS(6),GPIONRIS(7));
	GPIO_DEBUG("MIS [%x][%x][%x][%x][%x][%x][%x][%x] \n", GPIONMIS(0),GPIONMIS(1),GPIONMIS(2),GPIONMIS(3),GPIONMIS(4),GPIONMIS(5),GPIONMIS(6),GPIONMIS(7));


	/* Clear the interrupt */


	if(ui32Status0 != 0)
	{
		ui32Status =ui32Status0;
		gpio_array_n = gpio_array_n;
		//GPIONIC(gpio_array_n) =ui32Status;

	}
	else if(ui32Status1 != 0)
	{
		ui32Status =ui32Status1;
		gpio_array_n = gpio_array_n +1 ;

	}
	else if(ui32Status2 != 0)
	{
		ui32Status =ui32Status2;
		gpio_array_n = gpio_array_n + 2;

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
					GPIO_DEBUG("_GPIO_ISR_GPIO_M17 		pin[%d] value[%d]\n",realGpio, value);
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
					if (gpio_isr_info[realGpio].intr_count == gpio_isr_info[realGpio].start_count)
					{
					       gpio_isr_info[realGpio].start = (int)(ktime_to_us(ktime_get()));
					}
					else if (gpio_isr_info[realGpio].intr_count  == LAST_SAMPLE)
					{
					   int cktime = (int)(ktime_to_us(ktime_get()));

					   gpio_isr_info[realGpio].dur = (int)( cktime - (int)gpio_isr_info[realGpio].start );
					   //disable interrupt
					_GPIO_SetIntrAction(realGpio, NULL, COUNT_DISABLE, &intrinfo);
					}
					else
					{
					  ;
					}

					if(   gpio_isr_info[realGpio].intr_count > 0)
					   gpio_isr_info[realGpio].intr_count--;
					GPIO_DEBUG("realGpio [%d] intrcnt [%d] start_count[%d]\n ",realGpio, gpio_isr_info[realGpio].intr_count,gpio_isr_info[realGpio].start_count);

				}
			}

			/* Clear the serviced status */
			ui32Status ^= ( 1 << ucGpio );
			//GPIONIC(gpio_array_n) =ui32Status;
		}
	}
}
#endif



