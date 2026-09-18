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

#ifndef __OS_UTIL_H__
#define __OS_UTIL_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/version.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include "base_types.h"


#ifdef INCLUDE_M16_CHIP_KDRV
#include "m16/os/linux_platform.h"
#include "m16/os/linux_irqs.h"
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
#include "m17/os/linux_platform.h"
#include "m17/os/linux_irqs.h"
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
#include "l18/os/linux_platform.h"
#include "l18/os/linux_irqs.h"
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
#include "o18/os/linux_platform.h"
#include "o18/os/linux_irqs.h"
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
#include "m19/os/linux_platform.h"
#include "m19/os/linux_irqs.h"
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
#include "o20/os/linux_platform.h"
#include "o20/os/linux_irqs.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "e60/os/linux_platform.h"
#include "e60/os/linux_irqs.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "o22/os/linux_platform.h"
#include "o22/os/linux_irqs.h"
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#include "m23/os/linux_platform.h"
#include "m23/os/linux_irqs.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "o24/os/linux_platform.h"
#include "o24/os/linux_irqs.h"
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/os/linux_platform.h"
#include "o26/os/linux_irqs.h"
#endif

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */



/////////////////////////////////////////////////////////////////////////////////////////
//  OS API
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef LX_STR_MAX
#define LX_STR_MAX              256
#endif

#define OS_API_VERSION          2   // os_util version = 2, check if new api is supported

#define OS_NO_WAIT              0
#define OS_INFINITE_WAIT        ((u32)-1)

#define OS_SEM_ATTR_DEFAULT     0

#define OS_EVENT_RECEIVE_ANY    0
#define OS_EVENT_RECEIVE_ALL    1

#define OS_TIMER_TIMEOUT        (1<<0)
#define OS_TIMER_TIMETICK       (1<<1)

struct os_sem
{
    char*                   name;
    struct semaphore        sem;            ///< semaphore structure in Linux
    wait_queue_head_t       wq;             ///< wait_queue_head structure in Linux. wait for timed wait.
};

typedef struct os_sem OS_SEM_T;

struct os_event
{
    char*                   name;
    spinlock_t              spinlock;
    wait_queue_head_t       wq;             ///< wait_queue_head structure in Linux
    volatile u32            ev;             ///< event value
};

typedef struct os_event OS_EVENT_T;

typedef void (*OS_TIMER_CALLBACK_T)(ULONG);

struct os_timer
{
    spinlock_t              spinlock;
    struct timer_list       tmr;            ///< timer_list structure in Linux
    u32                     option;         ///< timer option
    u32                     data;           ///< timer data
    ULONG                   ticks;          ///< timer tick value ( jiffies )
    OS_TIMER_CALLBACK_T     callback;       ///< timer callback function
};

typedef struct os_timer OS_TIMER_T;

struct os_file
{
    struct file* fd;  ///< pointer to linux file struct
    char*  name;
};

typedef struct os_file OS_FILE_T;

struct os_cmap
{
    ULONG phys_addr;
    void* virt_addr;
    unsigned int length;
};

typedef struct os_cmap OS_CACHE_MAP_T;

struct os_memcfg_region;

struct os_memcfg_desc
{
    const char* name;
    const char* alias;
    u32 pool_type;
};

extern int lg1k_core_logm_fd;

// simple mutex_lock wrapper
//
// os_mutex_init: wrapper of sema_init
// when initializing the driver, the mutex object should also be initialized together.
// you should call os_mutex_init once when initializing your driver.
//
// os_mutex_lock: wrapper of down_trylock or down
// when interrupt status, down_trylock() is called
// when timeout option is OS_INFINITE_WAIT, down() is called
// when timeout is set to the valid value. wait_event_interruptible_timeout() is called with down_trylock()
// if timeout happens, RET_TIMEOUT is returned.
//
// os_mutex_unlock:
// up() is called and all waiting tasks are awakened.
//
void    os_mutex_init(OS_SEM_T* pSem, const char* name);
int     os_mutex_lock(OS_SEM_T* pSem, u32 timeout);
void    os_mutex_unlock(OS_SEM_T* pSem);

#define os_mutex_wait(pSem, timeout)    os_mutex_lock(pSem, timeout)
#define os_mutex_post(pSem)             os_mutex_unlock(pSem)

// simple event broadcast & receiver wrapper
//
// os_event_init:
// when initializing the driver, the event object should also be initialized together.
// you should call os_event_init once when initializing your driver.
//
// os_event_send:
// set the event flag and wake up all waiting task
//
// os_event_recva:
// multiple processes can wait for a single event. when the os_event_send() function is called,
// all processes waiting for the event can be awakened. However, the fastest process that meets
// the conditions will be the recipient of the event. others goes to sleeping state again.
// if you don't wait event forever, set the appropriate timeout value.
// when timeout happen, RET_TIMEOUT is returned.
//
// os_event_clear:
// clear the current event flag
//
void    os_event_init(OS_EVENT_T* pEvnt, const char* name);
int     os_event_recv(OS_EVENT_T* pEvnt, u32 ev, u32* rEv, u32 option, u32 timeout);
void    os_event_send(OS_EVENT_T* pEvnt, u32 ev);
void    os_event_clear(OS_EVENT_T* pEvnt);

// simple time wrapper
//
// os_get_ms_tick : get mili second tick
// os_get_us_tick : get micro second tick
// os_get_ns_tick : get nano second tick
// os_get_ticks   : get sec, mili-sec, micro-sec ticks
//
// os_sleep_ms    : sleep mili second
// os_sleep_us    : sleep micro second
// os_delay_ns    : delay nano second
//
// @note os_sleep_xx is implemented with usleep_range()
//
u64  os_get_ms_tick(void);
u64  os_get_us_tick(void);
u64  os_get_ns_tick(void);
void os_get_ticks(u32* pSec, u32* pMsec, u32* pUsec);

void os_sleep_ms(u32 msec);
void os_sleep_us(u32 usec);
void os_delay_ns(u32 nsec);

// timeout/timetick timer wrapper
//
// os_timer_init:
// when initializing the driver, the timer object should also be initialized together.
// you should call os_timer_init once when initializing your driver.
//
// os_timer_start:
// when option is OS_TIMER_TIMEOUT, timer_callback function is called once and timer is stopped automatically.
// when option is OS_TIMER_TIMETICK, timer_callback function is called perodically and timer should be stopped manually.
//
// remember that timer_callback function is a software interrupt.
// so be careful not to call any function which makes current process to sleep.
//
// os_timer_stop:
// stop timer
//
void os_timer_init(OS_TIMER_T* pTimer);
void os_timer_start(OS_TIMER_T* pTimer, OS_TIMER_CALLBACK_T timer_callback, u32 option, u32 timeout, u32 data);
void os_timer_stop(OS_TIMER_T* pTimer);

// simple wrapper for kernel memory allocation.
// these functions are implemented internally using kmalloc or vmalloc.
// The reason why these simple functions are provided is to print error log in case of error.
//
// @note use vmalloc/vfree when you don't need physically contiuous memory.
//
#define os_kmalloc(size)    os_kmalloc_ex(size, __F__, __L__)
#define os_kfree(ptr)       os_kfree_ex(ptr, __F__, __L__)
#define os_vmalloc(size)    os_vmalloc_ex(size, __F__, __L__)
#define os_vfree(ptr)       os_vfree_ex(ptr, __F__, __L__)

void* os_kmalloc_ex(size_t size, const char* func, const int line);
void  os_kfree_ex(void* ptr, const char* func, const int line);
void* os_vmalloc_ex(size_t size, const char* func, const int line);
void  os_vfree_ex(void* ptr, const char* func, const int line);

char* os_strdup(const char* s, size_t max);

// register & memory read/write function
//
int os_wr_reg(u32 reg, u32 val);
int os_rd_reg(u32 reg, u32* val);
int os_wr_reg_list(u32 reg_list[], u32 val_list[], int num);
int os_rd_reg_list(u32 reg_list[], u32 val_list[], int num);
int os_wr_mem(u32 phys_addr, u32* data_list, int num_data);
int os_rd_mem(u32 phys_addr, unsigned int* data_list, int num_data);

// random function wrapper
// see get_random_u32() and get_random_u64() kernel api
u32 os_random(void);
u64 os_random64(void);

// helper function to dump binary data including register
// if output_buf is not NULL, all dump contents into output_buf
//
int os_hexdump(u32 disp_addr, void* data_ptr, unsigned int data_cnt, char* output_buf);

// same as strtok_r
char* simple_strtok(char* s, const char* delim, char** save_ptr);

// make string to 32bit hash value
u32 os_strhash(const char* s);

// scan linux /proc/cmdline and return target command option or token
// os_scan_kernel_cmdline can catch "fmt=value" or "token" string
//
// <ex1>
// catch disp=xxxx string and return xxxx
//
//  char optstr[32];
//  if (RET_OK == os_scan_kernel_cmdline("disp=%s", optstr))
//  {
//      if(!strncmp(optstr, "hdmi",4))
//      {
//          printk("HDMI detected\n");
//      }
//  }
//
// <ex2>
// check if WiressAV string in /proc/cmdline
//
//  if (RET_OK == os_scan_kernel_cmdline("WiressAV", NULL))
//  {
//      printk("WiressAV detected\n");
//  }
//
int os_scan_kernel_cmdline(const char* fmt_str, char* val_str);

// file access functions inside kernel driver
//
int os_file_open(OS_FILE_T* pFile, char* fname, int flags, mode_t mode);
int os_file_seek(OS_FILE_T* pFile, off_t offset, int whence);
int os_file_get_size(OS_FILE_T* pFile);
int os_file_write(OS_FILE_T* pFile, char* buffer, int count);
int os_file_read(OS_FILE_T* pFile, char* buffer, int count);
int os_file_close(OS_FILE_T* pFile);

// cached memory I/O wrapper for device memory region
//
// note) offset, length should be page aligned
int os_cmem_open(OS_CACHE_MAP_T* map, ULONG paddr, unsigned int length);
int os_cmem_close(OS_CACHE_MAP_T* map);
int os_cmem_inval(OS_CACHE_MAP_T* map, unsigned int offset, unsigned int length);
int os_cmem_clean(OS_CACHE_MAP_T* map, unsigned int offset, unsigned int length);

/////////////////////////////////////////////////////////////////////////////////////////
//  MEMCFG API
//
//
/////////////////////////////////////////////////////////////////////////////////////////
// kdriver 의 메모리 레이아웃을 담당한다.
//
// region :
// 예전에는 M0, M1 등 DDR 을 하나의 큰 메모리 덩어리로 취급하였으나,
// 최근에는 secure/non-secure 속성까지 고려하여 동일한 속성을 같은 메모리 그룹으로 처리한다.
// 즉 region 과 물리적 메모리는 아무런 연관성이 없다. 다만 편의성을 위하여 region name 에 M0, M1 등의
// 물리 메모리 위치를 사용할 뿐이다.
//
// region 은 해당 메모리 영역을 관리하는 역할이므로 base, size 정보를 모두 담고 있어야 한다.
// 만약 앞선 메모리맵에 이어 연속적으로 자동 배치 되길 원하면 base 는 0x0 으로 설정할 수도 있다
// 하지만 boot 에서 묘사된 address switch 설정과 일치해야 하므로, 자기 영역의 정보는 명확하게 입력하자.
//
// item ;
// 기존과 같은 방식으로 배열에 N 개의 LX_MEMCFG_T 형식으로 표현되는 모듈의 메모리 영역을 표현한다.
// 각 모듈의 특성에 따라 item 하나로 본인 모듈의 메모리를 모두 기술할 수도 있고, 각각의 LX_MEMCFG_T 하나를
// 하나의 item 으로 취급할 수도 있다.
// 메모리 레이아웃 작업 관점에서는 큰 차이가 없다. 다만 메모리맵 덤프 과정에서 약식 출력 요청시 각 item 별
// 대표 메모리맵 (전체 영역 표현) 을 출력하며, 상세 출력 요청시 item 의 서브 항목 까지 모두 출력해준다.
//
// 보통 모듈별 메모리는 자동 배치되길 기대하고 있기 때문에, 일반적인 경우 base 는 0x0 으로 설정한다.
// 디버깅 혹은 별도의 특수 메모리맵을 구성하는 목적 이외에는 항상 base 는 0x0 으로 설정한다.
//
// 용법:
// 각 함수의 인수에서 필요한 정보는 표햔되어 있어 상세한 기술은 하지 않겠다.
// kdriver/platform 밑의 plaform_init.c 을 참고하기 바란다.
//
// os_memcfg_add_region:
// region 정보를 등록한다.
//
// os_memcfg_add_item:
// 각 모듈별 메모리 영역 정보를 등록한다.
//
// os_memcfg_make_layout:
// region 과 item 의 모든 등록을 마무리한 이후, 이 함수를 호출하면 모든 base 값들이 계산되어 채워진다.
// 보통의 경우 각 플랫폼의 platform_init.c 에서 호출된다.
//
// os_memcfg_alloc_mpool:
// os_memcfg_desc 정보에 기술된 메모리 정보에 맞는 region, item 를 탐색하여 자동으로 CMA 혹은 HMA pool
// 생성 작업을 해준다.
// 보통의 경우 각 플랫폼의 platform_init.c 에서 호출된다.
//
// os_memcfg_dump:
// 익숙한 테이블 형태로 메모리맵 정보를 출력한다.
//
// os_memcfg_get_info:
// name 기반으로 region 혹은 item 의 메모리 정보 (base, size) 를 리턴한다.
//
struct os_memcfg_region* os_memcfg_add_region(const char* name, u64 paddr, u32 size);
int    os_memcfg_add_item(struct os_memcfg_region* region, const char* name, LX_MEMCFG_T data[], u32 size);
int    os_memcfg_make_layout(void);

int    os_memcfg_alloc_mpool(struct os_memcfg_desc* desc, int num_desc);

int    os_memcfg_get_info(const char* name, u64* paddr, u32* size);
void   os_memcfg_dump(void* s, bool detail);

// CMA 로 설정된 메모리풀의 안정성을 검증하기 위한 실험을 지원한다.
// 테스터는 force_hma_pool=a,b,c,d 형식으로 CMA 에서 HMA(NO_CMA) 로 전환할 pool name 리스트를 전달한다.
// CMA 타입의 메모리풀을 만드는 모듈에서는 check_force_hma_pool() 함수를 호출하여, 테스터의 의하여
// 강제 HMA 타입의 메모리풀 생성을 요청 받았는지 반드시 확인해야 한다.
//
bool check_force_hma_pool(const char* pool);

// map memory region for cached or non-cached access
//
void* vmap_phys(phys_addr_t addr, unsigned long size);
void* vmap_phys_cache(phys_addr_t addr, unsigned long size);
void vunmap_phys(void* addr);

/////////////////////////////////////////////////////////////////////////////////////////
//  ETC API
//
//
/////////////////////////////////////////////////////////////////////////////////////////
// return lg1k chip revision information
//
u32  lx_chip(void);
u32  lx_chip_rev(void);
u32  lx_ace(void);
u32  lx_ace_rev(void);

// board specific option for customizing the kdriver
// board paramter is parsed at platform_init.c of each platform.
// @see LX_BOARD_xxx at base_type.h
//
u32  lx_board_opt(void);

// platform information for customizing the kdriver
// platform paramter is parsed at platform_init.c of each platform.
// @see LX_CHIP_PLT_xxx at base_type.h
//
u32  lx_chip_plt(void);

// pre-defined graphic resolution for test or bringup
// if zero returns, driver should determine graphic resolution by parsing something.
u32 lx_chip_graphic_res(void);

// helper function to making linux device class supporting udev
//
// @param udev[IN] your device node allocated by cdev_add()
// @param fmt [IN] your device name
//
void    OS_CreateDeviceClass(dev_t dev, const char* fmt, ...);
void    OS_CreateDeviceClass_mode(dev_t dev, umode_t mode, const char* fmt, ...);
void    OS_DestroyDeviceClass(dev_t dev);

/////////////////////////////////////////////////////////////////////////////////////////
//  for legacy interface
//  DO NOT use the below function. Use OS_XXX macroes instead of these functions.
//
//
/////////////////////////////////////////////////////////////////////////////////////////
int OS_OpenCacheMap(OS_CACHE_MAP_T* pMap, ULONG phys_addr, u32 length);
int OS_CloseCacheMap(OS_CACHE_MAP_T* pMap);
int OS_InvalCacheMap(OS_CACHE_MAP_T* pMap, u32 off, u32 length);
int OS_CleanCacheMap(OS_CACHE_MAP_T* pMap, u32 off, u32 length);

#define OS_Malloc(size)             OS_KMalloc(size)
#define OS_Free(ptr)                OS_KFree(ptr)
#define OS_KMalloc(size)            OS_KMalloc_Tag(size, " ", __F__, __L__)
#define OS_KFree(ptr)               OS_KFree_Tag(ptr, " ", __F__, __L__)
void*   OS_KMalloc_Tag(size_t size, const char* szFile, const char* szFunc, const int nLine);
void    OS_KFree_Tag(void* ptr, const char* szFile, const char* szFunc, const int nLine);

int     OS_WrReg(u32 reg, u32 val);
int     OS_RdReg(u32 reg, u32* val);
int     OS_WrRegList(u32 reg_list[], u32 val_list[], int num);
int     OS_RdRegList(u32 reg_list[], u32 val_list[], int num);
int     OS_WrData(u32 phys_addr, u32* data_list, int num);
int     OS_RdData(u32 phys_addr, unsigned int* data_list, int num);

int     OS_OpenFile(OS_FILE_T* pFile, char* fname, int flags, mode_t mode);
int     OS_SeekFile(OS_FILE_T* pFile, off_t offset, int whence);
int     OS_SizeOfFile(OS_FILE_T* pFile);
int     OS_WriteFile(OS_FILE_T* pFile, char* buffer, int count);
int     OS_ReadFile(OS_FILE_T* pFile, char* buffer, int count);
int     OS_CloseFile(OS_FILE_T* pFile);

void    OS_InitTimer(OS_TIMER_T* pTimer);
void    OS_StopTimer(OS_TIMER_T* pTimer);
void    OS_StartTimer(OS_TIMER_T* pTimer, OS_TIMER_CALLBACK_T timer_callback, u32 option, u32 timeout,
                      u32 data);

int     OS_ScanKernelCmdline(const char* fmt_str, char* val_str);
int     OS_ScanKernelCmdlineToken(const char* token);

u64     OS_GetMsecTicks(void);
u64     OS_GetUsecTicks(void);
u64     OS_GetNsecTicks(void);
void    OS_GetCurrentTicks(u32* pSec, u32* pMsec, u32* pUsec);

int     OS_MsecSleep(u32 msec);
void    OS_UsecDelay(u32 usec);
void    OS_NsecDelay(u32 nsec);

void    OS_InitEvent(OS_EVENT_T* pEvnt);
int     OS_RecvEvent(OS_EVENT_T* pEvnt, u32 ev, u32* rEv, u32 option, u32 timeout);
void    OS_SendEvent(OS_EVENT_T* pEvnt, u32 ev);
void    OS_ClearEvent(OS_EVENT_T* pEvnt);

#define OS_WaitMutex(pSem)  OS_LockMutex(pSem)
#define OS_PostMutex(pSem)  OS_UnlockMutex(pSem)
#define OS_LockMutex(pSem)  OS_LockMutexEx(pSem,OS_INFINITE_WAIT)

void    OS_InitMutex(OS_SEM_T* pSem, u32 attr);
int __must_check OS_LockMutexEx(OS_SEM_T* pSem, u32 timeout);
void    OS_UnlockMutex(OS_SEM_T* pSem);


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __OS_UTIL_H__ */

/** @} */

