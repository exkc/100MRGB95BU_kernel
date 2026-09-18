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
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "os_util.h"
#include "base_device.h"
#include "pm_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "pm_o20common.h"

#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif

#define TS_COPY_FROM_USER(d,s,l)                                                      \
	do {                                                                                            \
		if (copy_from_user((void*)d, (void *)s, l)) {   \
			printk("ioctl: copy_from_user\n");          \
			return -EFAULT;                                                         \
		}                                                                                               \
	} while(0)

#define TS_COPY_TO_USER(d,s,l)                                                        \
	do {                                                                                            \
		if (copy_to_user((void*)d, (void *)s, l)) {     \
			printk("ioctl: copy_to_user\n");            \
			return -EFAULT;                                                         \
		}                                                                                               \
	} while(0)
#define LG1K_TEMP_PROC		"/proc/thermalinfo/soc_temperature"
#define LG1K_TEMP_GET_TEMP		_IOR ('i', 0x84, unsigned int)
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

DEFINE_MUTEX(o20_temp_mutex);
#define PSU_DATASIZE	256
static char psuinfo[PSU_DATASIZE];
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
        unsigned int  temp;
} TS_PARAM_T;
enum {
	PROC_ID_GOVERNOR,
	PROC_ID_BOOST,
	PROC_ID_MP_ENABLE,
	PROC_ID_TO_SUSPEND,
	PROC_ID_RESET_LOADMON,
	PROC_ID_GET_CURRENT_LOAD,
	PROC_ID_SAMPLING_RATE,
	PROC_ID_FREQ,
	PROC_ID_CPU_AVS,
	PROC_ID_CORE_AVS,
	PROC_ID_STATUS,
	PROC_ID_TS_ENABLE,
	PROC_ID_TS_DEBUG_ENABLE,
	PROC_ID_TS_CPU_APARAM,
	PROC_ID_TS_CPU_BPARAM,
	PROC_ID_TS_GPU_APARAM,
	PROC_ID_TS_GPU_BPARAM,
	PROC_ID_TEMPERATURE,
	PROC_ID_MAX,
};

enum {
	GOV_ID_MAX_FREQ,
	GOV_ID_MIN_FREQ,
	GOV_ID_HARD_UP_THRESHOLD,
	GOV_ID_EASY_UP_THRESHOLD,
	GOV_ID_EASY_COUNT,
	GOV_ID_FREQDOWN_COUNT,
	GOV_ID_MPD_COUNT,
	GOV_ID_MAX,
};

enum {
	DEBUG_ID_PSU_INFO,
	DEBUG_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static pms_o20_gov_t* pm_o20_gov = NULL;
static pms_o20_func_t* pm_o20_func = NULL;
static pms_o20_test_t* pm_o20_test = NULL;
static pms_o20_avs_t* pm_o20_avs = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _PM_PrintStatus(struct seq_file *m, void* data);

OS_PROC_SEQRD_DEFINE_EX(pm_status_proc_fops, _PM_PrintStatus,NULL)

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

static OS_PROC_DESC_TABLE_T	_g_pm_o20_device_proc_table[] =
{
	{ "governor",				PROC_ID_GOVERNOR			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "boost",					PROC_ID_BOOST				, OS_PROC_FLAG_WRITE  },
	{ "mp_enable",				PROC_ID_MP_ENABLE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "to_suspend", 			PROC_ID_TO_SUSPEND			, OS_PROC_FLAG_WRITE  },
	{ "reset_loadmon",			PROC_ID_RESET_LOADMON		, OS_PROC_FLAG_WRITE  },
	{ "current_load",			PROC_ID_GET_CURRENT_LOAD	, OS_PROC_FLAG_READ	  },
	{ "sampling_rate",			PROC_ID_SAMPLING_RATE		, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "cpuavs",					PROC_ID_CPU_AVS			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "coreavs",				PROC_ID_CORE_AVS			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "frequency",              PROC_ID_FREQ				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "status",        		    PROC_ID_STATUS,     OS_PROC_FLAG_SEQRD, (void*)&pm_status_proc_fops },
	{ "ts_enable",				PROC_ID_TS_ENABLE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "ts_debug_enable",		PROC_ID_TS_DEBUG_ENABLE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "ts_cpu_aparam",			PROC_ID_TS_CPU_APARAM			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "ts_cpu_bparam",			PROC_ID_TS_CPU_BPARAM			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "ts_gpu_aparam",			PROC_ID_TS_GPU_APARAM			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "ts_gpu_bparam",			PROC_ID_TS_GPU_BPARAM			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "temperature",			PROC_ID_TEMPERATURE			, OS_PROC_FLAG_READ	  },
	{ NULL, 					PROC_ID_MAX					, 0 }
};

static OS_PROC_DESC_TABLE_T	_g_pm_o20_gov_proc_table[] =
{
	{ "max_frequency",			GOV_ID_MAX_FREQ				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "min_frequency",			GOV_ID_MIN_FREQ				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "up_threshold_hard",		GOV_ID_HARD_UP_THRESHOLD	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "up_threshold_easy",		GOV_ID_EASY_UP_THRESHOLD	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "count_easy", 			GOV_ID_EASY_COUNT			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freqdown_count",			GOV_ID_FREQDOWN_COUNT		, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_count",				GOV_ID_MPD_COUNT			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 					GOV_ID_MAX					, 0 }
};

static OS_PROC_DESC_TABLE_T	_g_pm_o20_debug_proc_table[] =
{

	{ "psuinfo",				DEBUG_ID_PSU_INFO				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 					DEBUG_ID_MAX					, 0 }
};


/*========================================================================================
	Implementation Group
========================================================================================*/

#define O20_AVS  0
extern o20_sidd_t gSidd_check_table_o20[6];
extern char * cpu_volttype_o20[6];
extern char * core_volttype_high_o20[6];
extern char * core_volttype_o20[6];
extern pms_o20_avsinto_t	o20_avs_info;


static void _PM_PrintStatus(struct seq_file *m, void* data)
{
	pms_o20_avsinto_t info ;
	memset (&info,0x0, sizeof(pms_o20_avsinto_t));

	seq_printf( m, "governor: %s\n", pm_o20_gov->get_gov_str(pm_o20_gov->get_gov()) );
	seq_printf( m, "cpu_num: %d\n", pm_o20_gov->get_cpunum());
	seq_printf( m, "load: %u %u %u %u\n", pm_o20_gov->get_load(0),pm_o20_gov->get_load(1),pm_o20_gov->get_load(2),pm_o20_gov->get_load(3)) ;
	seq_printf( m, "loadmax: %u \n", pm_o20_gov->get_load(4)) ;
	seq_printf( m, "loadavg: %u \n", pm_o20_gov->get_load(5)) ;
	seq_printf( m, "freq: %u Mhz\n", pm_o20_gov->get_max_freq()) ;
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "coreavs_type: %s \n", pm_o20_avs->get_core_avs_type_str()) ;
	pm_o20_avs->get_core_avs_type(&info);
	seq_printf( m, "coreavs_current(mA): %u\n", info.avscurrent);
	pm_o20_avs->get_cpu_avs_type(&info);
	seq_printf( m, "cpuavs_type: %s \n", pm_o20_avs->get_cpu_avs_type_str()) ;
	seq_printf( m, "cpuavs_current(mA): %u\n", info.avscurrent);
	seq_printf( m, "avs high [%u]\n", o20_avs_info.is_avshigh);
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "|o20 core avs %5s table|\n",(o20_avs_info.is_avshigh)?"HIGH":"NORMAL");
	seq_printf( m, "===========================\n"	);

	if(o20_avs_info.is_avshigh)
	{
		seq_printf( m, "|     < %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_n_min,core_volttype_high_o20[1]);
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_n_min,gSidd_check_table_o20[O20_AVS].core_sidd_f_min,core_volttype_high_o20[2] );
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_f_min,gSidd_check_table_o20[O20_AVS].core_sidd_ff_min,core_volttype_high_o20[3] );
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_ff_min,gSidd_check_table_o20[O20_AVS].core_sidd_fff_min,core_volttype_high_o20[3] );
		seq_printf( m, "|     > %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_fff_min,core_volttype_high_o20[4]);
	}
	else
	{
		seq_printf( m, "|     < %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_n_min,core_volttype_o20[1]);
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_n_min,gSidd_check_table_o20[O20_AVS].core_sidd_f_min,core_volttype_o20[2] );
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_f_min,gSidd_check_table_o20[O20_AVS].core_sidd_ff_min,core_volttype_o20[3] );
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_ff_min,gSidd_check_table_o20[O20_AVS].core_sidd_fff_min,core_volttype_o20[3] );
		seq_printf( m, "|     > %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].core_sidd_fff_min,core_volttype_o20[4]);
	}
		seq_printf( m, "===========================\n"	);
		seq_printf( m, "|  o20a0  cpu avs table |\n");
		seq_printf( m, "===========================\n"	);
		seq_printf( m, "|     < %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].cpu_sidd_n_min,cpu_volttype_o20[1]);
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].cpu_sidd_n_min,gSidd_check_table_o20[O20_AVS].cpu_sidd_f_min,cpu_volttype_o20[2] );
		seq_printf( m, "| %3d ~ %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].cpu_sidd_f_min,gSidd_check_table_o20[O20_AVS].cpu_sidd_ff_min,cpu_volttype_o20[2] );
		seq_printf( m, "|     > %3d |  %sV      |\n", gSidd_check_table_o20[O20_AVS].cpu_sidd_ff_min,cpu_volttype_o20[3]);
		seq_printf( m, "===========================\n"	);

		pm_o20_avs->get_cpu_avs_type(&info);
		seq_printf( m, "HVT_cpu   0x%4x = %d.%2d  Mhz \n",info.HVT_cpu,
			(info.HVT_cpu > 100) ? info.HVT_cpu/100 : 0 ,info.HVT_cpu % 100);
		seq_printf( m, "SVT_cpu   0x%4x = %d.%2d  Mhz \n",info.SVT_cpu,
			( info.SVT_cpu > 100) ? info.SVT_cpu/100 : 0, info.SVT_cpu % 100);
		seq_printf( m, "Nskew_cpu 0x%4x = %d.%2d  Mhz \n",info.Nskew_cpu,
			(info.Nskew_cpu > 100) ? info.Nskew_cpu/100 : 0,info.Nskew_cpu % 100);
		seq_printf( m, "Pskew_cpu 0x%4x = %d.%2d  Mhz \n",info.Pskew_cpu,
			(info.Pskew_cpu > 100) ? info.Pskew_cpu/100 : 0,info.Pskew_cpu % 100);
		seq_printf( m, "HVT_gpu   0x%4x = %d.%2d  Mhz \n",info.HVT_gpu,
			(info.HVT_gpu > 100) ? info.HVT_gpu/100 : 0,info.HVT_gpu % 100);
		seq_printf( m, "SVT_gpu   0x%4x = %d.%2d  Mhz \n",info.SVT_gpu,
			(info.SVT_gpu > 100) ? info.SVT_gpu/100 : 0,info.SVT_gpu % 100);
		seq_printf( m, "Nskew_gpu 0x%4x = %d.%2d  Mhz \n",info.Nskew_gpu,
			(info.Nskew_gpu > 100) ? info.Nskew_gpu/100 : 0,info.Nskew_gpu % 100);
		seq_printf( m, "Pskew_gpu 0x%4x = %d.%2d  Mhz \n",info.Pskew_gpu,
			(info.Pskew_gpu > 100) ? info.Pskew_gpu/100 : 0,info.Pskew_gpu % 100);
		seq_printf( m, "===========================\n"	);
		seq_printf( m,"      o20 CPU TEMP[%d]'C    \n",pm_o20_avs->get_temperature());
		seq_printf( m, "===========================\n"	);

}


static int lg1k_temp_get_temp(int sensor)
{
	int temp=0;
	#if 0
	int temp =0 ,tempa = 0;
	unsigned int rawts = 0;


	if(lg1k_tempbase != NULL)
	{
		rawts = readl((void *)((uintptr_t)lg1k_tempbase + (uintptr_t)0x0) );

		tempa = (aparam * rawts) / 100000;
		temp = tempa - bparam;
	}
	#endif

	temp = pm_o20_avs->get_temperature();

	return temp;
}
/*
 * Procfs interface
 */
static int
lg1k_temp_ioctl_unlocked(struct file *fp, unsigned int cmd, unsigned long arg)
{
	int val = 0;
	TS_PARAM_T param;

	switch (cmd) {

	case LG1K_TEMP_GET_TEMP:
		TS_COPY_FROM_USER(&param, arg, sizeof(TS_PARAM_T));
		val = lg1k_temp_get_temp(0);
		param.temp = val;
		TS_COPY_TO_USER(arg, &param, sizeof(TS_PARAM_T));
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
static long lg1k_temp_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	long ret;

	mutex_lock(&o20_temp_mutex);
	ret = lg1k_temp_ioctl_unlocked(fp, cmd, arg);
	mutex_unlock(&o20_temp_mutex);

	return ret;
}
#ifdef CONFIG_COMPAT
static long TS_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;


	TS_PARAM_T arg_buf;
	ret = copy_from_user((void *)&arg_buf, (void __user *)arg,
			sizeof(TS_PARAM_T));
	if (ret)
	{
		printk(" error copy from user \n");
		return -EINVAL;
	}


	ret = copy_to_user((void __user *)arg, (void *)&arg_buf,
			sizeof(TS_PARAM_T));
	if (ret)
	{
		printk(" error copy to user \n");
		return -EINVAL;
	}


	ret = lg1k_temp_ioctl(file, cmd, arg);

	return ret;
}
#endif
static int temp_open(struct inode *inode, struct file *file);
static struct file_operations proc_temp_fops =
{
	.open = temp_open,
	//.read = temp_read,
	.read = seq_read,
	.llseek = seq_lseek,
	//.write = temp_write,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= TS_CompatIoctl,
#endif
	.release = single_release,
};
static int temp_proc_op(struct seq_file *m, void *data)
{


	seq_printf( m,"%d\n",pm_o20_avs->get_temperature());

	return 0;

}
static int temp_open(struct inode *inode, struct file *file)
{
        return single_open(file, temp_proc_op, NULL);
}
/**
 * read_proc implementation of pm device
 *
*/
static int	o20_read_debug_proc(UINT32 procId, char* buffer )
{
	int ret = 0 ;

	switch( procId ) {
		case DEBUG_ID_PSU_INFO:
			memcpy(buffer, psuinfo, PSU_DATASIZE);
			ret = snprintf( buffer, PSU_DATASIZE, "%s\n", psuinfo);
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}
static int	o20_read_gov_proc(UINT32 procId, char* buffer )
{

	int	ret = 0 ;

	switch( procId ) {
		case GOV_ID_MAX_FREQ:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_max_freq() * 1000);
			break;
		case GOV_ID_MIN_FREQ:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_min_freq() * 1000);
			break;
		case GOV_ID_HARD_UP_THRESHOLD:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_hard_up_threshold() );
			break;
		case GOV_ID_EASY_UP_THRESHOLD:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_easy_up_threshold() );
			break;
		case GOV_ID_EASY_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_easy_count());
			break;
		case GOV_ID_FREQDOWN_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_freqdown_count());
			break;
		case GOV_ID_MPD_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_mpd_count());
			break;
		default:
			ret = -1;
			break;
	}

	return ret;

}

static int	o20_read_proc(UINT32 procId, char* buffer )
{
	int	ret = 0 ;
	pms_o20_avsinto_t info;

	switch( procId ) {
		case PROC_ID_GOVERNOR:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_gov());
			break;
		case PROC_ID_MP_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_mp_enable());
			break;
		case PROC_ID_TS_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_ts_enable());
			break;
		case PROC_ID_TS_DEBUG_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o20_avs->get_ts_debug_enable());
			break;
		case PROC_ID_TS_CPU_APARAM:
			ret = sprintf( buffer, "%u\n", pm_o20_avs->get_cpu_ts_aparam());
			break;
		case PROC_ID_TS_CPU_BPARAM:
			ret = sprintf( buffer, "%u\n", pm_o20_avs->get_cpu_ts_bparam());
			break;
		case PROC_ID_TS_GPU_APARAM:
			ret = sprintf( buffer, "%u\n", pm_o20_avs->get_gpu_ts_aparam());
			break;
		case PROC_ID_TS_GPU_BPARAM:
			ret = sprintf( buffer, "%u\n", pm_o20_avs->get_gpu_ts_bparam());
			break;
		case PROC_ID_TEMPERATURE:
			ret = sprintf( buffer, "%d\n", pm_o20_avs->get_temperature());
			break;
		case PROC_ID_GET_CURRENT_LOAD:
			ret = sprintf( buffer, "%u\n", pm_o20_gov->get_load(LOAD_MAX));
			break;
		case PROC_ID_SAMPLING_RATE:
			ret = sprintf( buffer, "%u ms\n", pm_o20_func->get_sampling_rate());
			break;
		case PROC_ID_FREQ:
			ret = sprintf( buffer, "%u\n",pm_o20_func->getfreq() * 1000);
			break;
		case PROC_ID_CPU_AVS:
			pm_o20_avs->get_cpu_avs_type(&info);
			ret = snprintf( buffer,48,"cpuavs_type:%u %s cpuavs_current(mA):%u\n",info.avstype,pm_o20_avs->get_cpu_avs_type_str(),info.avscurrent);
			break;
		case PROC_ID_CORE_AVS:
			pm_o20_avs->get_core_avs_type(&info);
			ret = snprintf( buffer,48,"coreavs_type:%u %s coreavs_current(mA):%u\n",info.avstype,pm_o20_avs->get_core_avs_type_str(),info.avscurrent);
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

/**
 * write_proc implementation of pm device
 *
*/

static int o20_write_debug_proc( UINT32 procId, char* command )
{
	int ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case DEBUG_ID_PSU_INFO:
			memcpy(psuinfo,command,PSU_DATASIZE);
			break;
		default:
			ret = -1;
			break;
	}

	return strlen(command);
}
static int o20_write_gov_proc( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;
	int ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case GOV_ID_MAX_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
			if( input_value < pm_o20_gov->get_min_freq()) {
				printk("input frequency is lower then min frequency\n");
				break;
			}
			pm_o20_gov->set_max_freq(input_value / 1000);
			break;
		case GOV_ID_MIN_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
			if( input_value < pm_o20_gov->get_max_freq()) {
				printk("input frequency is higher then max frequency\n");
				break;
			}
			pm_o20_gov->set_min_freq(input_value / 1000);
			break;
		case GOV_ID_HARD_UP_THRESHOLD:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_gov->set_hard_up_threshold(input_value);
			break;
		case GOV_ID_EASY_UP_THRESHOLD:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_gov->set_easy_up_threshold(input_value);
			break;
		case GOV_ID_EASY_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_gov->set_easy_count(input_value);
			break;
		case GOV_ID_FREQDOWN_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_gov->set_freqdown_count(input_value);
			break;
		case GOV_ID_MPD_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_gov->set_mpd_count(input_value);
			break;
		default:
			ret = -1;
			break;
	}

	return strlen(command);

}

static int o20_write_proc( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;
	unsigned int temp;
	pms_o20_work_t pms_work;
	int ret = 0;

	memset(&pms_work, 0x0, sizeof(pms_work));

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_GOVERNOR:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value <= 10)
			{
				pm_o20_test->set_testmode(0);

				pm_o20_gov->set_gov(input_value);
				pm_o20_gov->set_startup_timer(0);

				if (input_value == 0 || input_value == 6) /* 0:disable  6:disable + dft setting */
					pm_o20_func->set_max_performance();
				if( input_value == 6)
					pm_o20_func->setfreq(CPU_DFTFREQ);
				else if( input_value == 1)
					pm_o20_func->setfreq(CPU_NORMALFREQ);
			}
			break;
		case PROC_ID_BOOST:
			pm_o20_gov->boost();
			break;
		case PROC_ID_MP_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o20_gov->set_mp_enable(input_value);
			break;
		case PROC_ID_TS_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o20_gov->set_ts_enable(input_value);
			break;
		case PROC_ID_TS_DEBUG_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o20_avs->set_ts_debug_enable(input_value);
			break;

		case PROC_ID_TS_CPU_APARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_cpu_ts_aparam(input_value);
			break;
		case PROC_ID_TS_CPU_BPARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_cpu_ts_bparam(input_value);
			break;
		case PROC_ID_TS_GPU_APARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_gpu_ts_aparam(input_value);
			break;
		case PROC_ID_TS_GPU_BPARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_gpu_ts_bparam(input_value);
			break;
		case PROC_ID_TO_SUSPEND:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value == 1)
			{
				temp = pm_o20_gov->get_gov() | PMS_GOV_TOSUSPEND_FLAG;
				pm_o20_gov->set_gov(temp);
				pm_o20_gov->set_startup_timer(0);
				pm_o20_func->set_max_performance();
			}
			break;
		case PROC_ID_RESET_LOADMON:
			pm_o20_gov->reset_load_monitor();
			break;
		case PROC_ID_SAMPLING_RATE:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_func->set_sampling_rate(input_value);
			break;
		case PROC_ID_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value > (pm_o20_func->getfreq() * 1000))
			{
				pms_work.target_freq = input_value/1000;
				pms_work.do_dvfs = 1;
				pm_o20_func->run(pms_work);
			} else if (input_value < (pm_o20_func->getfreq() * 1000)) {
				pms_work.target_freq = input_value/1000;
				pms_work.do_dvfs = 2;
				pm_o20_func->run(pms_work);
			}
			break;

		case PROC_ID_CPU_AVS:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_avs_force(GPIO_AVS_CPU, input_value);
			break;

			break;
		case PROC_ID_CORE_AVS:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o20_avs->set_avs_force(GPIO_AVS_CORE, input_value);

			break;
		default:
			ret = -1;
			break;
	}

	return strlen(command);
}


/**
 * initialize proc utility for pm device
 *
 * @see PM_Init
*/
void o20_proc_init (void)
{
	struct proc_dir_entry *pde;
	pm_o20_func = get_o20_pm_func();
	pm_o20_gov = get_o20_pm_gov();
	pm_o20_test = get_o20_pm_test();
	pm_o20_avs = get_o20_pm_avs();


	OS_PROC_CreateEntryEx ( PM_MODULE, _g_pm_o20_device_proc_table,
										o20_read_proc,
										o20_write_proc );
	OS_PROC_CreateEntryEx ( PM_GOV_MODULE, _g_pm_o20_gov_proc_table,
										o20_read_gov_proc,
										o20_write_gov_proc );
	OS_PROC_CreateEntryEx ( PM_DEBUG_MODULE, _g_pm_o20_debug_proc_table,
										o20_read_debug_proc,
										o20_write_debug_proc );
    pde = proc_mkdir("thermalinfo", NULL);
	if(!pde)
		printk("check tempdir\n");
	proc_create ("soc_temperature", 0, pde, &proc_temp_fops);
}

/**
 * cleanup proc utility for pm device
 *
 * @see PM_Cleanup
*/
void o20_proc_cleanup (void)
{
	OS_PROC_RemoveEntry( PM_MODULE );
	OS_PROC_RemoveEntry( PM_GOV_MODULE );
	OS_PROC_RemoveEntry( PM_DEBUG_MODULE );
}

static pms_proc_t o20_proc_func =
{
	.init = o20_proc_init,
	.cleanup = o20_proc_cleanup,
};

pms_proc_t* get_o20_pm_proc(void)
{
	return &o20_proc_func;
}

