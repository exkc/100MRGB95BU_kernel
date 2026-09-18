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

#include "pm_o24common.h"

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

DEFINE_MUTEX(o24_temp_mutex);
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
	int  temp;
} TS_PARAM_T;
enum {
	PROC_ID_GOVERNOR,
	PROC_ID_BOOST,
	PROC_ID_MP_ENABLE,
	PROC_ID_FREQ_ENABLE,
	PROC_ID_FREQ_DEBUG_ENABLE,
	PROC_ID_DEBUG_ENABLE,
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
	PROC_ID_TEST,
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
	GOV_ID_MPD_UP_TH,
	GOV_ID_MPD_DN_TH,
	GOV_ID_MPD_UP_TH2,
	GOV_ID_MPD_DN_TH2,
	GOV_ID_FREQ_UP_TH,
	GOV_ID_FREQ_DN_TH,
	GOV_ID_FV_TIME,
	GOV_ID_HIST,
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
static pms_o24_gov_t* pm_o24_gov = NULL;
static pms_o24_func_t* pm_o24_func = NULL;
static pms_o24_test_t* pm_o24_test = NULL;
static pms_o24_avs_t* pm_o24_avs = NULL;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
static void _PM_PrintStatus(struct seq_file *m, void* data);

OS_PROC_SEQRD_DEFINE_EX(pm_status_proc_fops, _PM_PrintStatus,NULL)

	/*----------------------------------------------------------------------------------------
	  Static Variables
	  ----------------------------------------------------------------------------------------*/

	static OS_PROC_DESC_TABLE_T	_g_pm_o24_device_proc_table[] =
{
	{ "governor",				PROC_ID_GOVERNOR			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "boost",					PROC_ID_BOOST				, OS_PROC_FLAG_WRITE  },
	{ "mp_enable",				PROC_ID_MP_ENABLE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freq_enable",			PROC_ID_FREQ_ENABLE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freq_debug_enable",		PROC_ID_FREQ_DEBUG_ENABLE	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "debug_enable",		PROC_ID_DEBUG_ENABLE	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
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
	{ "test",			        PROC_ID_TEST			    , OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ NULL, 					PROC_ID_MAX					, 0 }
};

static OS_PROC_DESC_TABLE_T	_g_pm_o24_gov_proc_table[] =
{
	{ "max_frequency",			GOV_ID_MAX_FREQ				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "min_frequency",			GOV_ID_MIN_FREQ				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "up_threshold_hard",		GOV_ID_HARD_UP_THRESHOLD	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "up_threshold_easy",		GOV_ID_EASY_UP_THRESHOLD	, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "count_easy", 			GOV_ID_EASY_COUNT			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freqdown_count",			GOV_ID_FREQDOWN_COUNT		, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_count",				GOV_ID_MPD_COUNT			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_up_th",				GOV_ID_MPD_UP_TH			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_dn_th",				GOV_ID_MPD_DN_TH			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_up_th2",				GOV_ID_MPD_UP_TH2			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "mpd_dn_th2",				GOV_ID_MPD_DN_TH2			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freq_up_th",				GOV_ID_MPD_UP_TH			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "freq_dn_th",				GOV_ID_MPD_DN_TH			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "fv_time",				GOV_ID_FV_TIME			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "hist",				GOV_ID_HIST			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 					GOV_ID_MAX					, 0 }
};

static OS_PROC_DESC_TABLE_T	_g_pm_o24_debug_proc_table[] =
{

	{ "psuinfo",				DEBUG_ID_PSU_INFO				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 					DEBUG_ID_MAX					, 0 }
};


/*========================================================================================
  Implementation Group
  ========================================================================================*/

#define O24_AVS  0
extern o24_sidd_t gSidd_check_table_o24[6];
extern char * cpu_volttype_o24[6];
extern char * core_volttype_high_o24[6];
extern char * core_volttype_o24[6];
extern pms_o24_avsinto_t	o24_avs_info;


static void _PM_PrintStatus(struct seq_file *m, void* data)
{
	pms_o24_avsinto_t info ;
	memset (&info,0x0, sizeof(pms_o24_avsinto_t));

	seq_printf( m, "governor: %s\n", pm_o24_gov->get_gov_str(pm_o24_gov->get_gov()) );
	seq_printf( m, "cpu_num: %d\n", pm_o24_gov->get_cpunum());
	seq_printf( m, "load: %u %u %u %u\n", pm_o24_gov->get_load(0),pm_o24_gov->get_load(1),pm_o24_gov->get_load(2),pm_o24_gov->get_load(3)) ;
	seq_printf( m, "loadmax: %u \n", pm_o24_gov->get_load(4)) ;
	seq_printf( m, "loadavg: %u \n", pm_o24_gov->get_load(5)) ;
	seq_printf( m, "freq: %u Mhz\n", pm_o24_gov->get_max_freq()) ;
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "coreavs_type: %s \n", pm_o24_avs->get_core_avs_type_str()) ;
	pm_o24_avs->get_core_avs_type(&info);
	seq_printf( m, "coreavs_current(mA): %u\n", info.avscurrent);
	pm_o24_avs->get_cpu_avs_type(&info);
	seq_printf( m, "cpuavs_type: %s \n", pm_o24_avs->get_cpu_avs_type_str()) ;
	seq_printf( m, "cpuavs_current(mA): %u\n", info.avscurrent);
	seq_printf( m, "avs high [%u]\n", o24_avs_info.is_avshigh);
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "|o24 core avs %5s table|\n",(o24_avs_info.is_avshigh)?"HIGH":"NORMAL");
	seq_printf( m, "===========================\n"	);

	if(o24_avs_info.is_avshigh)
	{
		seq_printf( m, "|    <= %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].core_sidd_f_min,core_volttype_high_o24[1] );
		seq_printf( m, "|     > %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].core_sidd_f_min,core_volttype_high_o24[3]);
	}
	else
	{
		seq_printf( m, "| 	 <= %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].core_sidd_f_min,core_volttype_o24[1] );
		seq_printf( m, "|     > %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].core_sidd_f_min,core_volttype_o24[3]);
	}
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "|  o24a0  cpu avs table |\n");
	seq_printf( m, "===========================\n"	);
	seq_printf( m, "|    <= %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].cpu_sidd_f_min,cpu_volttype_o24[1]);
	seq_printf( m, "| %3d ~ %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].cpu_sidd_f_min,gSidd_check_table_o24[O24_AVS].cpu_sidd_ff_min,cpu_volttype_o24[3] );
	seq_printf( m, "|     > %3d |  %smV      |\n", gSidd_check_table_o24[O24_AVS].cpu_sidd_ff_min,cpu_volttype_o24[4]);
	seq_printf( m, "===========================\n"	);

	pm_o24_avs->get_cpu_avs_type(&info);
	seq_printf( m, "===========================\n"	);
	seq_printf( m,"      o24 CPU TEMP[%d]'C    \n",pm_o24_avs->get_temperature());
	seq_printf( m, "===========================\n"	);

}

static int get_cpusidd(struct seq_file *m, void* v)
{
	unsigned int cpusidd = 0;
	pms_o24_avsinto_t info;

	pm_o24_avs->get_cpu_avs_type(&info);

	if( info.avscurrent > 0)
		cpusidd = info.avscurrent;
	else
		cpusidd = 0;

	seq_printf( m,"%d\n",cpusidd);
	return 0;
}

static int cpusidd_open(struct inode * inode, struct file *file)
{
	return single_open(file, get_cpusidd,NULL);
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
static const struct proc_ops proc_cpusidd_fops =
{
	.proc_open = cpusidd_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations proc_cpusidd_fops =
{
	.open = cpusidd_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

static int get_coresidd(struct seq_file *m, void* v)
{
	unsigned int coresidd = 0;

	pms_o24_avsinto_t info;
	pm_o24_avs->get_core_avs_type(&info);

	if( info.avscurrent > 0)
		coresidd = info.avscurrent;
	else
		coresidd = 0;

	seq_printf( m,"%d\n",coresidd);
	return 0;
}

static int coresidd_open(struct inode * inode, struct file *file)
{
	return single_open(file, get_coresidd,NULL);
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
static const struct proc_ops proc_coresidd_fops =
{
	.proc_open = coresidd_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations proc_coresidd_fops =
{
	.open = coresidd_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

static int temp_open(struct inode *inode, struct file *file);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
static const struct proc_ops proc_temp_fops =
{
	.proc_open = temp_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations proc_temp_fops =
{
	.open = temp_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

static int temp_proc_op(struct seq_file *m, void *data)
{

	seq_printf( m,"%d\n",pm_o24_avs->get_temperature());

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
static int	o24_read_debug_proc(UINT32 procId, char* buffer )
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
static int	o24_read_gov_proc(UINT32 procId, char* buffer )
{

	int	ret = 0 ;

	switch( procId ) {
		case GOV_ID_MAX_FREQ:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_max_freq());
			break;
		case GOV_ID_MIN_FREQ:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_min_freq());
			break;
		case GOV_ID_HARD_UP_THRESHOLD:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_hard_up_threshold() );
			break;
		case GOV_ID_EASY_UP_THRESHOLD:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_easy_up_threshold() );
			break;
		case GOV_ID_EASY_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_easy_count());
			break;
		case GOV_ID_FREQDOWN_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_freqdown_count());
			break;
		case GOV_ID_MPD_COUNT:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mpd_count());
			break;
		case GOV_ID_MPD_UP_TH:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mpd_up_threshold());
			break;
		case GOV_ID_MPD_DN_TH:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mpd_dn_threshold());
			break;
		case GOV_ID_MPD_UP_TH2:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mpd_up_threshold2());
			break;
		case GOV_ID_MPD_DN_TH2:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mpd_dn_threshold2());
			break;
		case GOV_ID_FREQ_UP_TH:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_freq_up_threshold());
			break;
		case GOV_ID_FREQ_DN_TH:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_freq_dn_threshold());
			break;
		case GOV_ID_FV_TIME:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_fv_time());
			break;
		case GOV_ID_HIST:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_hist());
			break;
		default:
			ret = -1;
			break;
	}

	return ret;

}

static int	o24_read_proc(UINT32 procId, char* buffer )
{
	int	ret = 0 ;
	pms_o24_avsinto_t info;

	switch( procId ) {
		case PROC_ID_GOVERNOR:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_gov());
			break;
		case PROC_ID_MP_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_mp_enable());
			break;
		case PROC_ID_FREQ_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_freq_enable());
			break;
		case PROC_ID_FREQ_DEBUG_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_freq_debug_enable());
			break;
		case PROC_ID_DEBUG_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_debug_enable());
			break;
		case PROC_ID_TS_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_ts_enable());
			break;
		case PROC_ID_TS_DEBUG_ENABLE:
			ret = sprintf( buffer, "%u\n", pm_o24_avs->get_ts_debug_enable());
			break;
		case PROC_ID_TS_CPU_APARAM:
			ret = sprintf( buffer, "%u\n", pm_o24_avs->get_cpu_ts_aparam());
			break;
		case PROC_ID_TS_CPU_BPARAM:
			ret = sprintf( buffer, "%u\n", pm_o24_avs->get_cpu_ts_bparam());
			break;
		case PROC_ID_TS_GPU_APARAM:
			ret = sprintf( buffer, "%u\n", pm_o24_avs->get_gpu_ts_aparam());
			break;
		case PROC_ID_TS_GPU_BPARAM:
			ret = sprintf( buffer, "%u\n", pm_o24_avs->get_gpu_ts_bparam());
			break;
		case PROC_ID_TEMPERATURE:
			ret = sprintf( buffer, "%d\n", pm_o24_avs->get_temperature());
			break;
		case PROC_ID_GET_CURRENT_LOAD:
			ret = sprintf( buffer, "%u\n", pm_o24_gov->get_load(LOAD_MAX));
			break;
		case PROC_ID_SAMPLING_RATE:
			ret = sprintf( buffer, "%u ms\n", pm_o24_func->get_sampling_rate());
			break;
		case PROC_ID_FREQ:
			ret = sprintf( buffer, "%u\n",pm_o24_func->getfreq());
			break;
		case PROC_ID_CPU_AVS:
			pm_o24_avs->get_cpu_avs_type(&info);
			ret = snprintf( buffer,48,"cpuavs_type:%u %s cpuavs_current(mA):%u\n",info.avstype,pm_o24_avs->get_cpu_avs_type_str(),info.avscurrent);
			break;
		case PROC_ID_CORE_AVS:
			pm_o24_avs->get_core_avs_type(&info);
			ret = snprintf( buffer,48,"coreavs_type:%u %s coreavs_current(mA):%u\n",info.avstype,pm_o24_avs->get_core_avs_type_str(),info.avscurrent);
			break;
		case PROC_ID_TEST:
			ret = snprintf( buffer,48, "%u\n", pm_o24_test->get_testmode());
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

static int o24_write_debug_proc( UINT32 procId, char* command )
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
static int o24_write_gov_proc( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;
	int ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case GOV_ID_MAX_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
			if( input_value < pm_o24_gov->get_min_freq()) {
				printk("input frequency is lower then min frequency\n");
				break;
			}
			pm_o24_gov->set_max_freq(input_value);
			break;
		case GOV_ID_MIN_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
			if( input_value < pm_o24_gov->get_max_freq()) {
				printk("input frequency is higher then max frequency\n");
				break;
			}
			pm_o24_gov->set_min_freq(input_value);
			break;
		case GOV_ID_HARD_UP_THRESHOLD:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_hard_up_threshold(input_value);
			break;
		case GOV_ID_EASY_UP_THRESHOLD:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_easy_up_threshold(input_value);
			break;
		case GOV_ID_EASY_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_easy_count(input_value);
			break;
		case GOV_ID_FREQDOWN_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_freqdown_count(input_value);
			break;
		case GOV_ID_MPD_COUNT:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_mpd_count(input_value);
			break;
		case GOV_ID_MPD_UP_TH:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_mpd_up_threshold(input_value);
			break;
		case GOV_ID_MPD_DN_TH:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_mpd_dn_threshold(input_value);
			break;
		case GOV_ID_MPD_UP_TH2:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_mpd_up_threshold2(input_value);
			break;
		case GOV_ID_MPD_DN_TH2:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_mpd_dn_threshold2(input_value);
			break;
		case GOV_ID_FREQ_UP_TH:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_freq_up_threshold(input_value);
			break;
		case GOV_ID_FREQ_DN_TH:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_freq_dn_threshold(input_value);
			break;
		case GOV_ID_FV_TIME:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_fv_time(input_value);
			break;
		case GOV_ID_HIST:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_gov->set_hist(input_value);
			break;
		default:
			ret = -1;
			break;
	}

	return strlen(command);

}

static int o24_write_proc( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;
	unsigned int temp;
	pms_o24_work_t pms_work;
	int ret = 0;

	memset(&pms_work, 0x0, sizeof(pms_work));

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_GOVERNOR:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value <= 10)
			{
				pm_o24_test->set_testmode(0);

				pm_o24_gov->set_gov(input_value);
				pm_o24_gov->set_startup_timer(0);

				if (input_value == 0)
				{
					pm_o24_func->set_max_performance();
					if(!(lx_board_opt() & LX_BOARD_OPT_SLT))
					{
						pm_o24_func->setfreq(1200);
					}
				}
			}
			break;
		case PROC_ID_BOOST:
			pm_o24_gov->boost();
			break;
		case PROC_ID_MP_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_gov->set_mp_enable(input_value);
			break;
		case PROC_ID_FREQ_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_gov->set_freq_enable(input_value);
			break;
		case PROC_ID_FREQ_DEBUG_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_gov->set_freq_debug_enable(input_value);
			break;
		case PROC_ID_DEBUG_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_gov->set_debug_enable(input_value);
			break;
		case PROC_ID_TS_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_gov->set_ts_enable(input_value);
			break;
		case PROC_ID_TS_DEBUG_ENABLE:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value != 0)
				input_value = 1;
			pm_o24_avs->set_ts_debug_enable(input_value);
			break;

		case PROC_ID_TS_CPU_APARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_cpu_ts_aparam(input_value);
			break;
		case PROC_ID_TS_CPU_BPARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_cpu_ts_bparam(input_value);
			break;
		case PROC_ID_TS_GPU_APARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_gpu_ts_aparam(input_value);
			break;
		case PROC_ID_TS_GPU_BPARAM:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_gpu_ts_bparam(input_value);
			break;
		case PROC_ID_TO_SUSPEND:
			input_n = sscanf(command,"%u\n", &input_value);
			if (input_value == 1)
			{
				temp = pm_o24_gov->get_gov() | PMS_GOV_TOSUSPEND_FLAG;
				pm_o24_gov->set_gov(temp);
				pm_o24_gov->set_startup_timer(0);
				pm_o24_func->set_max_performance();
			}
			break;
		case PROC_ID_RESET_LOADMON:
			pm_o24_gov->reset_load_monitor();
			break;
		case PROC_ID_SAMPLING_RATE:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_func->set_sampling_rate(input_value);
			break;
		case PROC_ID_FREQ:
			input_n = sscanf(command,"%u\n", &input_value);
#if 1
			pms_work.target_freq = input_value;
			pms_work.do_dvfs = 1;
			pm_o24_func->run_clk(&pms_work);
#else

			pm_o24_func->setfreq(input_value);
#endif
			break;

		case PROC_ID_CPU_AVS:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_avs_force(GPIO_AVS_CPU, input_value);
			break;
		case PROC_ID_CORE_AVS:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_avs->set_avs_force(GPIO_AVS_CORE, input_value);
			break;
		case PROC_ID_TEST:
			input_n = sscanf(command,"%u\n", &input_value);
			pm_o24_test->set_testmode(input_value);
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
void o24_proc_init (void)
{
	struct proc_dir_entry *pde = NULL;
	pm_o24_func = get_o24_pm_func();
	pm_o24_gov = get_o24_pm_gov();
	pm_o24_test = get_o24_pm_test();
	pm_o24_avs = get_o24_pm_avs();


	OS_PROC_CreateEntryEx ( PM_MODULE, _g_pm_o24_device_proc_table,
			o24_read_proc,
			o24_write_proc );
	OS_PROC_CreateEntryEx ( PM_GOV_MODULE, _g_pm_o24_gov_proc_table,
			o24_read_gov_proc,
			o24_write_gov_proc );
	OS_PROC_CreateEntryEx ( PM_DEBUG_MODULE, _g_pm_o24_debug_proc_table,
			o24_read_debug_proc,
			o24_write_debug_proc );

	pde = proc_mkdir("thermalinfo", NULL);

	if(pde != NULL)
	{
		proc_create ("soc_temperature", 0, pde, &proc_temp_fops);
		/* iddq_core: core sidd   iddq_cpu:cpu sidd */
		proc_create ("iddq_core", 0, pde, &proc_coresidd_fops);
		proc_create ("iddq_scpu", 0, pde, &proc_cpusidd_fops);
		return;
	}
	else{
		printk("check tempdir\n");
		return;
	}
}

/**
 * cleanup proc utility for pm device
 *
 * @see PM_Cleanup
 */
void o24_proc_cleanup (void)
{
	OS_PROC_RemoveEntry( PM_MODULE );
	OS_PROC_RemoveEntry( PM_GOV_MODULE );
	OS_PROC_RemoveEntry( PM_DEBUG_MODULE );
}

static pms_proc_t o24_proc_func =
{
	.init = o24_proc_init,
	.cleanup = o24_proc_cleanup,
};

pms_proc_t* get_o24_pm_proc(void)
{
	return &o24_proc_func;
}

