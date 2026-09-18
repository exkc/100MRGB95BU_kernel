/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/
/** @file
 *
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1313_pm
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/tick.h>
#include <linux/device.h>
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include <linux/regulator/consumer.h>
#include "os_util.h"

#include "gpio_core.h"

#include "pm_m19common.h"
#include "sys_regs.h"
#include "gpio_reg.h"
#include "sys_io.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef PM_DEBUG_PRINT_ENABLE
#ifdef PM_DEBUG_PRINT_ENABLE
#define PM_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define PM_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define CPU_AVS_S_MV		974800
#define CPU_AVS_N_MV		948800
#define CPU_AVS_F_MV		929300
#define CPU_AVS_FF_MV		903300

#define M19_CPU_TS_EN			(1 << 0)
#define M19_CPU_TS_RAW_INTR_EN			(1 << 24)

#define CORE_AVS_INVALID_MIN   6  /* invalid max */
#define CORE_AVS_FFF 5   /* ffast */
#define CORE_AVS_FF 4   /* ffast */
#define CORE_AVS_F 3    /* fast */
#define CORE_AVS_N 2    /* normal */
#define CORE_AVS_S 1    /* slow */
#define CORE_AVS_X 0    /* not determined */

#define CPU_AVS_INVALID_MIN   5  /* invalid max */
#define CPU_AVS_FF 4    /* ffast */
#define CPU_AVS_F 3     /* fast */
#define CPU_AVS_N 2     /* normal */
#define CPU_AVS_S 1     /* slow */
#define CPU_AVS_X 0     /* not determined */


#define CORE_SIDD_S_MIN_TH_AX  1    //mA
#define CORE_SIDD_N_MIN_TH_AX   71      //mA
#define CORE_SIDD_F_MIN_TH_AX   111     //mA

#define CPU_SIDD_S_MIN_TH_AX   1     //mA
#define CPU_SIDD_N_MIN_TH_AX    71     //mA
#define CPU_SIDD_F_MIN_TH_AX    111      //mA

#define CORE_SIDD_VALID_MIN     59 //mA
#define CORE_SIDD_VALID_MAX     1000 //mA

#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_CX     2

#define SIDD_CHECK_TABLE_NUM	5


char * cpu_volttype_high[6] = { "XXX","0.91","0.89","0.87", "0.85","XXX"};
char * cpu_vidttype_high[6] = { "GPIO 107[1] 108[1]","GPIO 107[1] 108[0]","GPIO 107[0] 108[1]","GPIO 107[0] 108[0]","GPIO 107[0] 108[0]","XXX" };


char * core_volttype_high[6] ={ "XXX","0.91","0.89","0.87", "0.85","XXX" };
char * core_vidttype_high[6] = { "GPIO 31[1] 13[1]","GPIO 31[1] 13[1]","GPIO 31[0] 13[1]","GPIO 31[1] 13[0]","GPIO 31[0] 13[0]","XXX" };

									 /* high normal low verylow voltage */
char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","XXX" };
char * cpu_volttype[6] = { "XXX","0.93","0.91","0.89", "0.87","XXX" };
char * cpu_vidttype[6] = { "GPIO 107[1] 108[1]","GPIO 107[1] 108[1]","GPIO 107[1] 108[0]","GPIO 107[0] 108[1]","GPIO 107[0] 108[0]","XXX" };

char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","XXX" };
char * core_volttype[6] ={ "XXX","0.93","0.91","0.89", "0.87","XXX" };
char * core_vidttype[6] = { "GPIO 31[1] 13[1]","GPIO 31[1] 13[1]","GPIO 31[0] 13[1]","GPIO 31[1] 13[0]","GPIO 31[0] 13[0]","XXX" };



static unsigned int m19_avsinfo = 0;
static unsigned int m19_cpu_avs = 0;
static unsigned int m19_core_avs = 0;

static UINT32 core_avs= 0, cpu_avs = 0;

module_param(m19_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(m19_avsinfo, "m19_avsinfo");

module_param(m19_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(m19_cpu_avs, "m19_cpu_avs");

module_param(m19_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(m19_core_avs, "m19_core_avs");

                                                /* fast */
static unsigned int cpu_sidd_f_min_th;
                                                /* normal */
static unsigned int cpu_sidd_n_min_th;
                                                /* slow */
static unsigned int cpu_sidd_s_min_th;

                                                /* fast */
static unsigned int core_sidd_f_min_th;
                                                /* normal */
static unsigned int core_sidd_n_min_th;
                                                /* slow */
static unsigned int core_sidd_s_min_th;

pms_m19_avsinto_t	m19_avs_info;

m19_sidd_t gM19_Sidd_check_table[SIDD_CHECK_TABLE_NUM]={

        [SIDD_CHECK_TABLE_AX]={
        .cpu_sidd_f_min = CPU_SIDD_F_MIN_TH_AX,
        .cpu_sidd_n_min = CPU_SIDD_N_MIN_TH_AX,
        .cpu_sidd_s_min = CPU_SIDD_S_MIN_TH_AX,

        .core_sidd_f_min = CORE_SIDD_F_MIN_TH_AX,
        .core_sidd_n_min = CORE_SIDD_N_MIN_TH_AX,
        .core_sidd_s_min = CORE_SIDD_S_MIN_TH_AX,

		.core_sidd_valid_min = CORE_SIDD_VALID_MIN,
		.core_sidd_valid_max = CORE_SIDD_VALID_MAX
		},
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

//BEGIN GPIO_KERNEL_API


static unsigned int ts_timer_count = 0;
static unsigned int	ts_timer_count_1s = HZ / ((HZ / 100) * (20 / 10));

static void __iomem *cpu_ts_base = NULL;

static struct gpiod_lookup_table pm_gpio_table = {

        .dev_id = "pm_gpio",

        .table = {
					GPIO_LOOKUP_IDX("fd410000.gpio", 5, "13", 0, GPIO_ACTIVE_HIGH),
					GPIO_LOOKUP_IDX("fd430000.gpio", 7, "31", 0, GPIO_ACTIVE_HIGH),
		 { },

		},
};

static pms_m19_func_t* pm_m19_func = NULL;
static pms_m19_avs_t m19_pm_avs ;

static int _PM_GPIO_SetValue(UINT32 port, UINT32 val)
{
	UINT32 mask = 0, data = 0;
	mask = 1 << (2 + (port % 8));
	data = (val == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
	SYS_WRITE32(GPION_BASE(port/8) + mask, data);

	return 0;
}

static int _PM_GPIO_DevSetMode(UINT32 port, UINT32 mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);
	mask = 1 << (port % 8);
	direction = (mode == LX_GPIO_MODE_INPUT) ?
				direction & (~mask) : direction | mask;
	GPIONDIR(port/8) = direction;
	return 0;
}

//END KERNEL_API

int __pm_m19_set_vol(UINT32 core_cpu, UINT32 type)
{
	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		if (core_cpu == GPIO_AVS_CPU ){
			if( m19_avs_info.is_avshigh == 1)
			{
				switch(type){
					case CPU_AVS_S:
						//MV
						_GPIO_SetValue(GPIO_AVS_CPU0,1);
						_GPIO_SetValue(GPIO_AVS_CPU1,0);

						break;
					case CPU_AVS_N:
						//MV
						_GPIO_SetValue(GPIO_AVS_CPU1,1);
						_GPIO_SetValue(GPIO_AVS_CPU0,0);

						break;
					case CPU_AVS_F:
						//LV
						_GPIO_SetValue(GPIO_AVS_CPU0,0);
						_GPIO_SetValue(GPIO_AVS_CPU1,0);

						break;
					case CPU_AVS_FF:
						//VLV
						_GPIO_SetValue(GPIO_AVS_CPU0,0);
						_GPIO_SetValue(GPIO_AVS_CPU1,0);
						break;
					default:
						//HV
						_GPIO_SetValue(GPIO_AVS_CPU0,1);
						_GPIO_SetValue(GPIO_AVS_CPU1,1);
						break;
				}
			}
			else
			{
				switch(type){
					case CPU_AVS_S:
						//HV
						_GPIO_SetValue(GPIO_AVS_CPU0,1);
						_GPIO_SetValue(GPIO_AVS_CPU1,1);
						break;
					case CPU_AVS_N:
						//MV
						_GPIO_SetValue(GPIO_AVS_CPU0,1);
						_GPIO_SetValue(GPIO_AVS_CPU1,0);
						break;
					case CPU_AVS_F:
						//LV
						_GPIO_SetValue(GPIO_AVS_CPU1,1);
						_GPIO_SetValue(GPIO_AVS_CPU0,0);
						break;
					case CPU_AVS_FF:
						//VLV
						_GPIO_SetValue(GPIO_AVS_CPU0,0);
						_GPIO_SetValue(GPIO_AVS_CPU1,0);
						break;
					default:
						//HV
						_GPIO_SetValue(GPIO_AVS_CPU0,1);
						_GPIO_SetValue(GPIO_AVS_CPU1,1);
						break;
				}
			}
		}
		else if (core_cpu == GPIO_AVS_CORE ){

				if( m19_avs_info.is_avshigh == 1)
				{
						switch(type){
							case CORE_AVS_S:
								//HV
								_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_N:
								//MV
								_GPIO_SetValue(GPIO_AVS_CORE1,1);
								_GPIO_SetValue(GPIO_AVS_CORE0,0);
								break;
							case CORE_AVS_F:
								//LV
								_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_FF:
								//VLV
								_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_GPIO_SetValue(GPIO_AVS_CORE1,0);

								break;
							default:
								//HV
								_GPIO_SetValue(GPIO_AVS_CORE0, 1);
								_GPIO_SetValue(GPIO_AVS_CORE1, 1);
								break;
						}
				}
				else if( m19_avs_info.is_avshigh == 0)
				{
						switch(type){
							case CORE_AVS_S:
								//HV
								_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_GPIO_SetValue(GPIO_AVS_CORE1,1);
								break;
							case CORE_AVS_N:
								//MV
								_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_F:
								//LV
								_GPIO_SetValue(GPIO_AVS_CORE1,1);
								_GPIO_SetValue(GPIO_AVS_CORE0,0);
								break;
							case CORE_AVS_FF:
								//VLV
								_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_GPIO_SetValue(GPIO_AVS_CORE1,0);

								break;
							default:
								//HV
								_GPIO_SetValue(GPIO_AVS_CORE0, 1);
								_GPIO_SetValue(GPIO_AVS_CORE1, 1);
								break;
						}
				}

		}
	}
	else // GPIO_KERNEL_API
	{

		static struct regulator *regulator;

		int ret=0 ,prevMV=0;

		if (core_cpu == GPIO_AVS_CPU ){

			regulator = regulator_get(NULL, "cpu0");
			if (IS_ERR(regulator)) {
				PM_ERROR("couldn't get cpu0 regulator regulator\n");
				return 0;
			}

			prevMV = regulator_get_voltage(regulator) ;


			if( m19_avs_info.is_avshigh == 1)
			{
				switch(type){
					case CPU_AVS_S:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_N_MV,CPU_AVS_N_MV);
						break;
					case CPU_AVS_N:
						//MV
						ret = regulator_set_voltage(regulator, CPU_AVS_F_MV,CPU_AVS_F_MV);
						break;
					case CPU_AVS_F:
						//LV
						ret = regulator_set_voltage(regulator, CPU_AVS_FF_MV,CPU_AVS_FF_MV);
						break;
					case CPU_AVS_FF:
						//VLV
						ret = regulator_set_voltage(regulator, CPU_AVS_FF_MV,CPU_AVS_FF_MV);

						break;
					default:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_S_MV,CPU_AVS_S_MV);
						break;
				}

			}
			else if( m19_avs_info.is_avshigh == 0)
			{
				switch(type){
					case CPU_AVS_S:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_S_MV,CPU_AVS_S_MV);
						break;
					case CPU_AVS_N:
						//MV
						ret = regulator_set_voltage(regulator, CPU_AVS_N_MV,CPU_AVS_N_MV);
						break;
					case CPU_AVS_F:
						//LV
						ret = regulator_set_voltage(regulator, CPU_AVS_F_MV,CPU_AVS_F_MV);
						break;
					case CPU_AVS_FF:
						//VLV
						ret = regulator_set_voltage(regulator, CPU_AVS_FF_MV,CPU_AVS_FF_MV);

						break;
					default:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_S_MV,CPU_AVS_S_MV);
						break;
				}

			}
			PM_DEBUG("cpu ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(regulator) );
			regulator_put(regulator);
		}
		else if (core_cpu == GPIO_AVS_CORE ){

			/* max volt is set  when core_void0,1=[1,1] in m19p*/
			/* need to use gpio kernel api func */
			if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
			{
				if( m19_avs_info.is_avshigh == 1)
				{
						switch(type){
							case CORE_AVS_S:
								//HV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_N:
								//MV
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
								break;
							case CORE_AVS_F:
								//LV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_FF:
								//VLV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);

								break;
							default:
								//HV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0, 1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1, 1);
								break;
						}
				}
				else if( m19_avs_info.is_avshigh == 0)
				{
						switch(type){
							case CORE_AVS_S:
								//HV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,1);
								break;
							case CORE_AVS_N:
								//MV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);
								break;
							case CORE_AVS_F:
								//LV
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
								break;
							case CORE_AVS_FF:
								//VLV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);

								break;
							default:
								//HV
								_PM_GPIO_SetValue(GPIO_AVS_CORE0, 1);
								_PM_GPIO_SetValue(GPIO_AVS_CORE1, 1);
								break;
						}
				}

			}
			else
			{
				/* max volt is set  when core_void0,1=[0,0] in m19p*/
				switch(type){
					case CORE_AVS_S:
						//HV
						_PM_GPIO_SetValue(GPIO_AVS_CORE0, 1);
						_PM_GPIO_SetValue(GPIO_AVS_CORE1, 1);
						break;
					case CORE_AVS_N:
						//MV
						_PM_GPIO_SetValue(GPIO_AVS_CORE0,1);
						_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);
						break;
					case CORE_AVS_F:
						//LV
						_PM_GPIO_SetValue(GPIO_AVS_CORE1,1);
						_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
						break;
					case CORE_AVS_FF:
						//VLV
						_PM_GPIO_SetValue(GPIO_AVS_CORE0,0);
						_PM_GPIO_SetValue(GPIO_AVS_CORE1,0);
						break;
					default:
						//HV
						_PM_GPIO_SetValue(GPIO_AVS_CORE0, 1);
						_PM_GPIO_SetValue(GPIO_AVS_CORE1, 1);
						break;
				}
			}
		}
	}

	return 0;
}

int pm_m19_check_sidd_valid( UINT32 core_sidd,  UINT32 cpu_sidd, m19_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_sidd > core_sidd_valid_max || core_sidd < core_sidd_valid_min) {
		__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
		__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S );

		if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
			if(m19_avs_info.is_avshigh)
				PM_ERROR("M19 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x]\n",cpu_volttype_high[CPU_AVS_S],core_volttype_high[CORE_AVS_S],lx_chip_rev());
			else
				PM_ERROR("M19 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x]\n",cpu_volttype[CPU_AVS_S],core_volttype[CORE_AVS_S],lx_chip_rev());
		else
			PM_ERROR("M19 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x]\n",cpu_volttype[CPU_AVS_S],core_volttype[CORE_AVS_S],lx_chip_rev());
		return -1;
	}

	return 0;
}

int pm_m19_get_cpu_avs(pms_m19_avsinto_t * info)
{
	info->avstype = cpu_avs;

	if(m19_avsinfo)
	{
		if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
		{
			info->avscurrent =   (m19_avsinfo >> 13) & 0x1fff;
		}
		else
			info->avscurrent =   (m19_avsinfo >> 12) & 0xfff;
	}else
	{
		info->avscurrent = 0;
	}

	return (int)cpu_avs;
}
unsigned char * pm_m19_get_cpu_avs_str(void)
{
	//return cpu_avstype[cpu_avs];
	/* cpu avs fallow core avs */

	return core_avstype[core_avs];
}


int pm_m19_get_core_avs(pms_m19_avsinto_t * info)
{
	info->avstype = core_avs;

	if(m19_avsinfo)
	{
		if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
		{
			info->avscurrent =  m19_avsinfo & 0x1fff;
		}
		else
			info->avscurrent =  m19_avsinfo & 0xfff;
	}else
	{
		info->avscurrent = 0;
	}

	return (int)core_avs;
}
unsigned char *pm_m19_get_core_avs_str(void)
{
		return core_avstype[core_avs];
}

int pm_m19_set_avs(void)
{
	int ret = -1;
	UINT32 core_sidd = 0, cpu_sidd = 0;
	UINT32 mask = 0, value = 0;

	if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
	{
		if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
		{
			GPIO_DevSetPinMux(GPIO_AVS_CPU0, 1);
			GPIO_DevSetPinMux(GPIO_AVS_CPU1, 1);

			_GPIO_SetMode(GPIO_AVS_CORE0, 1);
			_GPIO_SetMode(GPIO_AVS_CORE1, 1);
			_GPIO_SetMode(GPIO_AVS_CPU0, 1);
			_GPIO_SetMode(GPIO_AVS_CPU1, 1);
		}
		else // GPIO_KERNEL_API
		{
			/* pinmux enable for gpio107 108 */
			value = CTOP_CTRL_M19Ax_READ(CTOP_DPE,0x138);
			mask = 3 << 3;
			value |= mask;
			CTOP_CTRL_M19Ax_WRITE(CTOP_DPE,0x138,value);

			_GPIO_SetMode(GPIO_AVS_CORE0, 1);
			_GPIO_SetMode(GPIO_AVS_CORE1, 1);

			/* GPIO_AVS_CPU0,1's direction is handelded by kernel regulator API */
		}

		/* do avs using m19_core_avs,m19_cpu_avs of bootargs */
		if((m19_core_avs > 0) && (m19_core_avs < CORE_AVS_INVALID_MIN) && (m19_cpu_avs > 0) && (m19_cpu_avs < CPU_AVS_INVALID_MIN))
		{
			/* store avs info to suspend resume */
			cpu_avs = m19_cpu_avs;
			core_avs = m19_core_avs;

			__pm_m19_set_vol(GPIO_AVS_CPU,m19_cpu_avs);
			__pm_m19_set_vol(GPIO_AVS_CORE,m19_core_avs);
			if(m19_avs_info.is_avshigh)
			{
				printk("M19 AVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
					cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype_high[cpu_avs],cpu_vidttype_high[cpu_avs],
					core_volttype_high[core_avs],core_vidttype_high[core_avs],lx_chip_rev());
			}
			else
			{
				printk("M19 AVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
					cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype[cpu_avs],cpu_vidttype[cpu_avs],
					core_volttype[core_avs],core_vidttype[core_avs],lx_chip_rev());
			}


			return 0;
		}
		/* do avs using kdriver avs param */
		else if(m19_avsinfo)
		{
			/*  correct AVS info case:  */
			core_sidd = m19_avsinfo & 0x1fff;
			cpu_sidd  = (m19_avsinfo >> 13) & 0x1fff;
			printk("M19 AVS avs info valid m19_avsinfo[%x] \n",m19_avsinfo);

			if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
			{
				core_sidd_s_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_s_min;
				core_sidd_n_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_n_min;
				core_sidd_f_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_f_min;

				cpu_sidd_s_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min;
				cpu_sidd_n_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
				cpu_sidd_f_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			}
			else{
				__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
				__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
				if(m19_avs_info.is_avshigh)
				{
					printk("M19 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n",
						lx_chip_rev(),cpu_volttype_high[CPU_AVS_S],cpu_vidttype_high[CPU_AVS_S],
						core_volttype_high[CORE_AVS_S],core_vidttype_high[CORE_AVS_S]);
				}
				else
				{
					printk("M19 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n",
						lx_chip_rev(),cpu_volttype[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],
						core_volttype[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				}

				return -1;
			}

			if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
			{
				ret = pm_m19_check_sidd_valid(core_sidd, cpu_sidd, &gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
				return ret;
			}

			/* core voltage table is different from cpu voltage table */
			if( core_sidd >= core_sidd_f_min_th){
					core_avs =	CORE_AVS_F;
			}
			else if( core_sidd >= core_sidd_n_min_th){
					core_avs =	CORE_AVS_N;
			}
			else if( core_sidd >= core_sidd_s_min_th){
					core_avs =	CORE_AVS_S;
			}
			else{
					core_avs =	CORE_AVS_S;
			}

			/* caution: consider core sidd for determining cpu avs */
			/* avs 3 level table is adapted in m19c0 */
			if( core_sidd >= cpu_sidd_f_min_th){
					cpu_avs =  CPU_AVS_F;
			}
			else if( core_sidd >= cpu_sidd_n_min_th){
					cpu_avs =  CPU_AVS_N;
			}
			else if( core_sidd >= cpu_sidd_s_min_th){
					cpu_avs =  CPU_AVS_S;
			}
			else{
					cpu_avs =  CPU_AVS_S;
			}

			__pm_m19_set_vol(GPIO_AVS_CORE,core_avs );
			__pm_m19_set_vol(GPIO_AVS_CPU,cpu_avs );

			if(m19_avs_info.is_avshigh)
			{
				printk("M19 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
					cpu_sidd_s_min_th,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd,cpu_avstype[cpu_avs],
					core_sidd_s_min_th,core_sidd_n_min_th,core_sidd_f_min_th,core_sidd,core_avstype[core_avs],
					cpu_volttype_high[cpu_avs],cpu_vidttype_high[cpu_avs],core_volttype_high[core_avs],core_vidttype_high[core_avs],lx_chip_rev());
			}
			else
			{
				printk("M19 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
					cpu_sidd_s_min_th,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd,cpu_avstype[cpu_avs],
					core_sidd_s_min_th,core_sidd_n_min_th,core_sidd_f_min_th,core_sidd,core_avstype[core_avs],
					cpu_volttype[cpu_avs],cpu_vidttype[cpu_avs],core_volttype[core_avs],core_vidttype[core_avs],lx_chip_rev());
			}

			return 0;

		}
		/* skip avs */
		else{
			__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
			/* crc fail or brank case :  default HV(Slow chip condition)  */
			if(m19_avs_info.is_avshigh)
			{
				printk("M19 AVS avs info is not valid, skipped! m19_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
				,m19_avsinfo,cpu_volttype_high[CPU_AVS_S],core_volttype_high[CORE_AVS_S],lx_chip_rev() );
			}
			else
			{
				printk("M19 AVS avs info is not valid, skipped! m19_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
				,m19_avsinfo,cpu_volttype[CPU_AVS_S],core_volttype[CORE_AVS_S],lx_chip_rev() );
			}
			return -1;
	     }


	}
	else
	{
		if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
		{
			GPIO_DevSetPinMux(GPIO_AVS_CPU0, 1);
			GPIO_DevSetPinMux(GPIO_AVS_CPU1, 1);

			_GPIO_SetMode(GPIO_AVS_CORE0, 1);
			_GPIO_SetMode(GPIO_AVS_CORE1, 1);
			_GPIO_SetMode(GPIO_AVS_CPU0, 1);
			_GPIO_SetMode(GPIO_AVS_CPU1, 1);
		}
		else // GPIO_KERNEL_API
		{
			/* pinmux enable for gpio107 108 */
			value = CTOP_CTRL_M19Ax_READ(CTOP_DPE,0x138);
			mask = 3 << 3;
			value |= mask;
			CTOP_CTRL_M19Ax_WRITE(CTOP_DPE,0x138,value);

			_PM_GPIO_DevSetMode(GPIO_AVS_CORE0, 1);
			_PM_GPIO_DevSetMode(GPIO_AVS_CORE1, 1);

			/* GPIO_AVS_CPU0,1's direction is handelded by kernel regulator API */
		}

		__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
		__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
		printk("M19 AVS skipped m19_avsinfo[%x] \n",m19_avsinfo);
		return 0;

		/* do avs using m19_core_avs,m19_cpu_avs of bootargs */
		if((m19_core_avs > 0) && (m19_core_avs < CORE_AVS_INVALID_MIN) && (m19_cpu_avs > 0) && (m19_cpu_avs < CPU_AVS_INVALID_MIN))
		{
			/* store avs info to suspend resume */
			cpu_avs = m19_cpu_avs;
			core_avs = m19_core_avs;

			__pm_m19_set_vol(GPIO_AVS_CPU,m19_cpu_avs);
			__pm_m19_set_vol(GPIO_AVS_CORE,m19_core_avs);

			printk("M19 AVS Boot cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n"
			,cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype[cpu_avs],cpu_vidttype[cpu_avs],core_volttype[core_avs],core_vidttype[core_avs],lx_chip_rev());

			return 0;
		}
		/* do avs using kdriver avs param */
		else if(m19_avsinfo)
		{
			/*  correct AVS info case:  */
			core_sidd = m19_avsinfo & 0xfff;
			cpu_sidd  = (m19_avsinfo >> 12) & 0xfff;
			printk("M19 AVS avs info valid m19_avsinfo[%x] \n",m19_avsinfo);

			#if 0  //disable M19 AVS
			if (lx_chip_rev() >= LX_CHIP_REV(M19,A0) && lx_chip_rev() < LX_CHIP_REV(M19,B0)){
				core_sidd_ff_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
				core_sidd_f_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
				core_sidd_n_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

				cpu_sidd_ff_min_th =  gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
				cpu_sidd_f_min_th =  gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
				cpu_sidd_n_min_th = gM19_Sidd_check_table[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
			}
			else
			#endif
			{
				__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
				__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
				printk("M19 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
				,lx_chip_rev(),cpu_volttype[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				return -1;
			}

		}
		/* skip avs */
		else{
			__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
			/* crc fail or brank case :  default HV(Slow chip condition)  */
			printk("M19 AVS avs info is not valid, skipped! m19_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
			,m19_avsinfo,cpu_volttype[CPU_AVS_S],core_volttype[CORE_AVS_S],lx_chip_rev() );
			return -1;
	     }
	}
}

int pm_m19_set_avs_force(UINT32 core_cpu, UINT32 type)
{
	if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
	{
		if (core_cpu == GPIO_AVS_CPU ){
			cpu_avs = type;
		}
		else if (core_cpu == GPIO_AVS_CORE ){
			core_avs = type;
		}
		__pm_m19_set_vol(core_cpu,type);

		PM_NOTI("M19 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n",cpu_avstype[cpu_avs],cpu_volttype[cpu_avs],
			cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype[core_avs],core_vidttype[core_avs]  );
	}
	else
	{
		if (core_cpu == GPIO_AVS_CPU ){
			cpu_avs = type;
		}
		else if (core_cpu == GPIO_AVS_CORE ){
			core_avs = type;
		}
		__pm_m19_set_vol(core_cpu,type);

		PM_NOTI("M19 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n",cpu_avstype[cpu_avs],cpu_volttype[cpu_avs],
			cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype[core_avs],core_vidttype[core_avs]  );
	}
	return 0;

}
int pm_m19_set_avs_in_resume(void)
{
	UINT32 core_sidd = 0, cpu_sidd = 0;
	UINT32 mask = 0, value = 0;

	if(lx_chip_rev() >= LX_CHIP_REV(M19,A0))
	{
		if((core_avs > 0) && (core_avs < CORE_AVS_INVALID_MIN) && (cpu_avs > 0) && (cpu_avs < CPU_AVS_INVALID_MIN))
		{
			if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
			{
				GPIO_DevSetPinMux(GPIO_AVS_CPU0, 1);
				GPIO_DevSetPinMux(GPIO_AVS_CPU1, 1);

				_GPIO_SetMode(GPIO_AVS_CORE0, 1);
				_GPIO_SetMode(GPIO_AVS_CORE1, 1);
				_GPIO_SetMode(GPIO_AVS_CPU0, 1);
				_GPIO_SetMode(GPIO_AVS_CPU1, 1);
			}
			else // GPIO_KERNEL_API
			{
				/* pinmux enable for gpio107 108 */
				value = CTOP_CTRL_M19Ax_READ(CTOP_DPE,0x138);
				mask = 3 << 3;
				value |= mask;
				CTOP_CTRL_M19Ax_WRITE(CTOP_DPE,0x138,value);

				_PM_GPIO_DevSetMode(GPIO_AVS_CORE0, 1);
				_PM_GPIO_DevSetMode(GPIO_AVS_CORE1, 1);

				/* GPIO_AVS_CPU0,1's direction is handelded by kernel regulator API */
			}

			if(m19_avsinfo)
			{
				/*	correct AVS info case:	*/
				core_sidd = m19_avsinfo & 0x1fff;
				cpu_sidd  = (m19_avsinfo >> 13) & 0x1fff;
			}
			__pm_m19_set_vol(GPIO_AVS_CPU,cpu_avs);
			__pm_m19_set_vol(GPIO_AVS_CORE,core_avs);
			if(m19_avs_info.is_avshigh)
			{
				PM_NOTI("M19 AVSRESUME cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n",
					cpu_sidd_s_min_th,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd,cpu_avstype[cpu_avs],
					core_sidd_s_min_th,core_sidd_n_min_th,core_sidd_f_min_th,core_sidd,core_avstype[core_avs],
					cpu_volttype_high[cpu_avs],cpu_vidttype_high[cpu_avs],core_volttype_high[core_avs],core_vidttype_high[core_avs],lx_chip_rev() );
			}
			else
			{
				PM_NOTI("M19 AVSRESUME cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n",
					cpu_sidd_s_min_th,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd,cpu_avstype[cpu_avs],
					core_sidd_s_min_th,core_sidd_n_min_th,core_sidd_f_min_th,core_sidd,core_avstype[core_avs],
					cpu_volttype[cpu_avs],cpu_vidttype[cpu_avs],core_volttype[core_avs],core_vidttype[core_avs],lx_chip_rev() );

			}

		}
	}
	else
	{
		if((core_avs > 0) && (core_avs < CORE_AVS_INVALID_MIN) && (cpu_avs > 0) && (cpu_avs < CPU_AVS_INVALID_MIN))
		{
			if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
			{
				GPIO_DevSetPinMux(GPIO_AVS_CPU0, 1);
				GPIO_DevSetPinMux(GPIO_AVS_CPU1, 1);

				_GPIO_SetMode(GPIO_AVS_CORE0, 1);
				_GPIO_SetMode(GPIO_AVS_CORE1, 1);
				_GPIO_SetMode(GPIO_AVS_CPU0, 1);
				_GPIO_SetMode(GPIO_AVS_CPU1, 1);
			}
			else // GPIO_KERNEL_API
			{
				/* pinmux enable for gpio107 108 */
				value = CTOP_CTRL_M19Ax_READ(CTOP_DPE,0x138);
				mask = 3 << 3;
				value |= mask;
				CTOP_CTRL_M19Ax_WRITE(CTOP_DPE,0x138,value);

				_PM_GPIO_DevSetMode(GPIO_AVS_CORE0, 1);
				_PM_GPIO_DevSetMode(GPIO_AVS_CORE1, 1);

				/* GPIO_AVS_CPU0,1's direction is handelded by kernel regulator API */
			}

			__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
			printk("M19 AVS skipped in resume m19_avsinfo[%x] \n",m19_avsinfo);
			return 0;

		}
	}
	return 0;


}

int pm_m19_check_n_set(void)
{
	LX_GPIO_VALUE_T val1,val2;
	UINT32 reset = 0;
	UINT32 core_sidd = 0, cpu_sidd = 0;

	if( (core_avs > 0) && (core_avs < CORE_AVS_INVALID_MIN) && (cpu_avs > 0) && (cpu_avs < CPU_AVS_INVALID_MIN))
	{
		if(m19_avsinfo)
		{
			/*	correct AVS info case:	*/
			core_sidd = m19_avsinfo & 0xfff;
			cpu_sidd  = (m19_avsinfo >> 12) & 0xfff;
		}

		switch(cpu_avs){
			case CPU_AVS_S:
				GPIO_DevGetValue(GPIO_AVS_CPU0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CPU1,&val2);
				if(val1 != 1 || val2 != 1)
				{
					__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
					reset = 1;
				}
				break;
			case CPU_AVS_N:
				GPIO_DevGetValue(GPIO_AVS_CPU0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CPU1,&val2);
				if(val1 != 1 || val2 != 0)
				{
					__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_N);
					reset = 1;
				}
				break;
			case CPU_AVS_F:
				GPIO_DevGetValue(GPIO_AVS_CPU0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CPU1,&val2);
				if(val1 != 0 || val2 != 1)
				{
					__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_F);
					reset = 1;
				}
				break;
			case CPU_AVS_FF:
				GPIO_DevGetValue(GPIO_AVS_CPU0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CPU1,&val2);
				if(val1 != 0 || val2 != 0)
				{
					__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_FF);
					reset = 1;
				}
				break;
			default:
				GPIO_DevGetValue(GPIO_AVS_CPU0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CPU1,&val2);
				if(val1 != 1 || val2 != 1)
				{
					__pm_m19_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
					reset = 1;
				}
				break;
		}

		switch(core_avs){
			case CORE_AVS_S:

				GPIO_DevGetValue(GPIO_AVS_CORE0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CORE1,&val2);
				if(val1 != 0 || val2 != 0)
				{
					__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
					reset = 1;
				}
				break;
			case CORE_AVS_N:
				GPIO_DevGetValue(GPIO_AVS_CORE0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CORE1,&val2);
				if(val1 != 0 || val2 != 1)
				{
					__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_N);
					reset = 1;
				}
				break;
			case CORE_AVS_F:
				GPIO_DevGetValue(GPIO_AVS_CORE0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CORE1,&val2);
				if(val1 != 1 || val2 != 0)
				{
					__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_F);
					reset = 1;
				}
				break;
			case CORE_AVS_FF:
				GPIO_DevGetValue(GPIO_AVS_CORE0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CORE1,&val2);
				if(val1 != 1 || val2 != 1)
				{
					__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_FF);
					reset = 1;
				}
				break;
			default:
				GPIO_DevGetValue(GPIO_AVS_CORE0,&val1);
				GPIO_DevGetValue(GPIO_AVS_CORE1,&val2);
				if(val1 != 0 || val2 != 0)
				{
					__pm_m19_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
					reset = 1;
				}
				break;
		}

		if(reset)
		{
			printk("M19 AVSRESET cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n"
			,cpu_sidd_s_min_th,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd,cpu_avstype[cpu_avs],core_sidd_s_min_th,core_sidd_n_min_th,core_sidd_f_min_th
			,core_sidd,core_avstype[core_avs],cpu_volttype[cpu_avs],cpu_vidttype[cpu_avs],core_volttype[core_avs],core_vidttype[core_avs],lx_chip_rev() );
		}
		else
			printk("M19 AVSRESETNO\n");


	}


	return 0;
}


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int m19_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	switch (cmd)
	{
		default:
			ret = -1;
			break;
	}

    return ret;
}

int m19_check_ts(void)
{
	int cpu_temp = 0, cpu_tempa = 0;
	unsigned int cpu_rawts = 0;



	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s)
	{

		/* OS_RdReg call ioremap which is restricted in soft isr */
		if(cpu_ts_base != NULL)
		{
			cpu_rawts = readl((void *)((uintptr_t)cpu_ts_base + (uintptr_t)0x14) );
		}

		if( cpu_rawts != 0 &&
			m19_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = (m19_avs_info.cpu_ts_aparam * cpu_rawts) / 10000;
			cpu_temp = cpu_tempa - m19_avs_info.cpu_ts_bparam ;

			m19_avs_info.temperature = cpu_temp;

			if( m19_avs_info.ts_debug_enable )
			{
				PM_NOTI("------------------------------\n");
				PM_NOTI("M19 [%s] TEMP[%d]'C  RAW[%d]\n",m19_pm_avs.get_core_avs_type_str(), cpu_temp,cpu_rawts);
			}
			if(cpu_temp > m19_avs_info.avshigh_th)
			{
				if(m19_avs_info.is_avshigh == 0)
				{
					m19_avs_info.avshigh_count++;

					if(m19_avs_info.avshigh_count > 5 )
					{
						m19_avs_info.is_avshigh = 1;
						m19_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("M19 SET AVS HIGH: CPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						pm_m19_set_avs();
						return 1 ;
					}
				}
			}

		}
		else if (m19_avs_info.cpu_ts_aparam == 0)
		{
			switch(core_avs)
			{
				case 0:
					break;
				case CORE_AVS_S:
					m19_avs_info.cpu_ts_aparam =m19_avs_info.cpu_ts_s_aparam;
					m19_avs_info.cpu_ts_bparam =m19_avs_info.cpu_ts_s_bparam;
					break;
				case CORE_AVS_N:
					m19_avs_info.cpu_ts_aparam =m19_avs_info.cpu_ts_n_aparam;
					m19_avs_info.cpu_ts_bparam =m19_avs_info.cpu_ts_n_bparam;
					break;
				case CORE_AVS_F:
					m19_avs_info.cpu_ts_aparam =m19_avs_info.cpu_ts_f_aparam;
					m19_avs_info.cpu_ts_bparam =m19_avs_info.cpu_ts_f_bparam;
					break;
				case CORE_AVS_FF:
					m19_avs_info.cpu_ts_aparam =m19_avs_info.cpu_ts_f_aparam;
					m19_avs_info.cpu_ts_bparam =m19_avs_info.cpu_ts_f_bparam;
					break;
				default:
					break;
			}

		}
		ts_timer_count = 0;
	}
	return 0 ;
}

static int m19_pm_set_cpu_ts_aparam(unsigned int value)
{
	m19_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int m19_pm_set_cpu_ts_bparam(unsigned int value)
{
	m19_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int m19_pm_get_cpu_ts_aparam(void)
{
	return m19_avs_info.cpu_ts_aparam;
}

static unsigned int m19_pm_get_cpu_ts_bparam(void)
{
	return m19_avs_info.cpu_ts_bparam;
}

static int m19_pm_set_gpu_ts_aparam(unsigned int value)
{
	m19_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int m19_pm_set_gpu_ts_bparam(unsigned int value)
{
	m19_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int m19_pm_get_gpu_ts_aparam(void)
{
	return m19_avs_info.gpu_ts_aparam;
}

static unsigned int m19_pm_get_gpu_ts_bparam(void)
{
	return m19_avs_info.gpu_ts_bparam;
}

static int m19_pm_set_ts_debug_enable(unsigned int value)
{
	m19_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int m19_pm_get_ts_debug_enable(void)
{
	return m19_avs_info.ts_debug_enable;
}

static unsigned int m19_pm_get_temperature(void)
{
	return m19_avs_info.temperature;
}

void m19_AvsReInit(void)
{
	/* need to enable after ts test */

	unsigned int val;
	if(cpu_ts_base == NULL)		cpu_ts_base = ioremap( 0xc9a04000, 0x18);
	val =  M19_CPU_TS_EN;
	writel(val, cpu_ts_base);
}

void m19_AvsInit(void)
{
	unsigned int val;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		/* do nothing */
	}
	else
	{
		/* need to be declared in kernel */
		gpiod_add_lookup_table(&pm_gpio_table);
	}

	pm_m19_func = get_m19_pm_func();


	if(cpu_ts_base == NULL)
	{
		cpu_ts_base = ioremap( 0xc9a04000, 0x18);
	}
	val = M19_CPU_TS_EN;
	writel(val, cpu_ts_base);

	/* cpu_ts_aparam, cpu_ts_bparam, gpu_ts_aparam, gpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -352(cpu_ts_bparam)  + 157(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */

	/* choose different temp regression parameter in regard to chip characteristic known by core SIDD range */
	m19_avs_info.cpu_ts_aparam = 0;
	m19_avs_info.cpu_ts_bparam = 0;

	m19_avs_info.cpu_ts_f_aparam = 140;
	m19_avs_info.cpu_ts_f_bparam = 309;
	m19_avs_info.cpu_ts_n_aparam = 157;
	m19_avs_info.cpu_ts_n_bparam = 352;
	m19_avs_info.cpu_ts_s_aparam = 162;
	m19_avs_info.cpu_ts_s_bparam = 373;

	/* avs table is changed when gpu temp reach 80'c */
	m19_avs_info.avshigh_th = 80;
	m19_avs_info.is_avshigh = 0;
	m19_avs_info.avshigh_count = 0;

	m19_avs_info.ts_debug_enable = 0;
	//pm_m19_set_avs();
}

static pms_m19_avs_t m19_pm_avs =
{
	.init = m19_AvsInit,
	.reinit = m19_AvsReInit,
	.set_avs = pm_m19_set_avs,
	.get_cpu_avs_type = pm_m19_get_cpu_avs,
	.get_cpu_avs_type_str = pm_m19_get_cpu_avs_str,
	.get_core_avs_type = pm_m19_get_core_avs,
	.get_core_avs_type_str = pm_m19_get_core_avs_str,
	.set_avs_in_resume = pm_m19_set_avs_in_resume,
	.set_avs_force = pm_m19_set_avs_force,
	.check_n_set = pm_m19_check_n_set,
	.ioctl = m19_pm_ioctl_avs,
	.check_ts = m19_check_ts,
	.get_cpu_ts_aparam = m19_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = m19_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = m19_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = m19_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = m19_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = m19_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = m19_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = m19_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = m19_pm_get_ts_debug_enable,
	.set_ts_debug_enable = m19_pm_set_ts_debug_enable,
	.get_temperature = m19_pm_get_temperature,
};

pms_m19_avs_t* get_m19_pm_avs(void)
{
	return &m19_pm_avs;
}



