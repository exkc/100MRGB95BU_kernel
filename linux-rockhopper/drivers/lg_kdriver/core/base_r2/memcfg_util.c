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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifndef UNIT_TEST
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>

#include "os_util.h"
#include "debug_util.h"
#include "base_impl.h"
#include "hma_alloc.h"
#endif

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define DEFAULT_ALIGN 0x1000 // 16KB

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define MB(sz)      ((sz)<<20)          // MB to bytes
#define KB(sz)      ((sz)<<10)          // KB to bytes

#define __MB(sz)    ((sz)>>20)          // bytes to MB
#define __KB(sz)    ((sz)>>10)          // bytes to KB

// 추후 memcfg 주소가 64bit 로 수정되면 아래 매크로를 무력화하도록 한다.
#define conv_memcfg_addr(addr)         ((u32)(addr))

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct os_memcfg_item
{
    const char*      name;
    u32              name_hash;

    LX_MEMCFG_T*     memcfg;
    int              memcfg_num;

    struct list_head list;
};

struct os_memcfg_region
{
    const char*     name;
    u32             name_hash;
    u64             base;
    u32             size;
    struct list_head item_list;

    struct list_head list;
};

struct os_memcfg_ctx
{
    struct list_head region_list;
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

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static bool memcfg_enabled = false;
static struct os_memcfg_ctx ctx;

/*========================================================================================
    Implementation Group
========================================================================================*/
void lg1k_memcfg_frwk_init(void)
{
    INIT_LIST_HEAD(&ctx.region_list);
}

void lg1k_memcfg_frwk_cleanup(void)
{
    // do nothing
}

struct os_memcfg_region* os_memcfg_add_region(const char* name, u64 base, u32 size)
{
    struct os_memcfg_region* region;

    if (unlikely(!name))
    {
        lg1k_logm_error("null name error\n");
        return NULL;
    }

    if (unlikely(!base || !size))
    {
        lg1k_logm_error("base/size null or zero size error. base=0x%08llx, size=0x%08x\n", base, size);
        return NULL;
    }

    if (unlikely(base & DEFAULT_ALIGN || size & DEFAULT_ALIGN))
    {
        lg1k_logm_error("base/size invalid align(0x%04x) error. base=0x%08llx, size=0x%08x\n", DEFAULT_ALIGN, base, size);

        return NULL;
    }

    region = os_vmalloc(sizeof(struct os_memcfg_region));

    if (!region)
    {
        lg1k_logm_error("alloc error\n");
        return NULL;
    }


    region->name = os_strdup(name, LX_STR_MAX);
    region->name_hash = os_strhash(name);
    region->base = base;
    region->size = size;
    INIT_LIST_HEAD(&region->item_list);

    //INIT_LIST_HEAD(&region->list);
    list_add_tail(&region->list, &ctx.region_list);

    lg1k_logm_memcfg_debug("region(%s) base=0x%08llx, size=0x%08x\n", name, base, size);

    return region;
}
EXPORT_SYMBOL(os_memcfg_add_region);


int os_memcfg_add_item(struct os_memcfg_region* region, const char* name, LX_MEMCFG_T memcfg[], u32 size)
{
    struct os_memcfg_item* item;

    if (unlikely(!region))
    {
        lg1k_logm_error("null region error\n");
        return RET_ERROR;
    }

    if (unlikely(!name))
    {
        lg1k_logm_error("null name error\n");
        return RET_ERROR;
    }

    if (unlikely(!memcfg))
    {
        lg1k_logm_error("base null error\n");
        return RET_ERROR;
    }

    item = os_vmalloc(sizeof(struct os_memcfg_item));

    if (!item)
    {
        lg1k_logm_error("alloc error\n");
        return RET_ERROR;
    }


    item->name = os_strdup(name, LX_STR_MAX);
    item->name_hash = os_strhash(name);
    item->memcfg = memcfg;
    item->memcfg_num = size / sizeof(LX_MEMCFG_T);

    //INIT_LIST_HEAD(&item->list);
    list_add_tail(&item->list, &region->item_list);

    lg1k_logm_memcfg_debug("item(%s) #item=%d\n", name, item->memcfg_num);

    return RET_OK;
}
EXPORT_SYMBOL(os_memcfg_add_item);

int os_memcfg_get_info(const char* name, u64* paddr, u32* size)
{
    struct os_memcfg_region* region;
    struct os_memcfg_item* item;
    u32 name_hash;

    if (!name || !paddr || !size)
    {
        //lg1k_logm_error("null parameter\n");
        return RET_ERROR;
    }

    name_hash = os_strhash(name);

    list_for_each_entry(region, &ctx.region_list, list)
    {
        if (region->name_hash == name_hash)
        {
            *paddr = region->base;
            *size = region->size;
            return RET_OK;
        }

        list_for_each_entry(item, &region->item_list, list)
        {
            if (item->name_hash == name_hash)
            {
                LX_MEMCFG_T* memcfg = item->memcfg;
                int memcfg_num = item->memcfg_num;

                u64 item_base = memcfg[0].base;
                u64 item_end  = memcfg[memcfg_num - 1].base + memcfg[memcfg_num - 1].size;

                *paddr = item_base;
                *size  = item_end - item_base;

                return RET_OK;
            }
        }
    }

    return RET_ERROR;
}
EXPORT_SYMBOL(os_memcfg_get_info);

#define ANSI_RED_FG "\033[1;31m"
#define ANSI_RESET  "\033[0m"

// add_item 로 입력된 데이터를 바탕으로 맵을 만듦
// 에러 갯수 만큼을 리턴함. 0 이면 에러 없음. 만약 2이면 에러 2개 발생한것
int os_memcfg_make_layout(void)
{
    int err = 0;
    u64 curr_addr = 0x0;

    struct os_memcfg_region* region;
    struct os_memcfg_item* item;

    memcfg_enabled = true;

    // 첫번째 region 으로 curr_addr 초기화한다.
    // 모든 region 이 고유의 영역을 가지고 있어야 하므로, 이 과정은 보험용이다.
    // 가령 하나의 region 을 가상으로 여러개로 나누고, 이에 대한 메모리 설정을 요청 하는 경우
    // 적어도 유의미한 curr_addr 는 있어야 한다.
    {
        struct os_memcfg_region* first_rgn = list_first_entry(&ctx.region_list, struct os_memcfg_region, list);

        lg1k_logm_memcfg_debug("first_rgn base=0x%08llx, size=0x%08x\n", first_rgn->base, first_rgn->size);

        // 에러 #0
        // region 의 주소는 0 이 아니어야 한다. 최소한 첫번째 regioon 은 base 정보가 있어야 한다.
        // 첫번째 region 의 base 가 0 이라면 메모리 레이아웃이 의미가 없다.
        // 최대한 커널 경고를 통해, 오류가 발생했음을 리포트 한다.
        if (!first_rgn->base)
        {
            lg1k_logm_error("%s[errori(%d) case0]%s can't layout memory\n", ANSI_RED_FG, err, ANSI_RESET);
            lg1k_logm_error("  (reason) region(%s) base=0x00000000\n", first_rgn->name);
            lg1k_logm_error("  (severity) critical\n");
            lg1k_logm_error("  (fix) can't fix !!! initialization fail !!!\n");

            ++err;

            WARN_ON(1);
        }

        curr_addr = first_rgn->base;
    }

    lg1k_logm_noti("<!> starting memcfg with curr_addr=0x%08llx\n", curr_addr);

    list_for_each_entry(region, &ctx.region_list, list)
    {
        u64 region_base = region->base;
        u64 region_end = region->base + region->size;
        const char* region_name = region->name;

        if (!region_base)
        {
            lg1k_logm_warn("region(%s) has no base address\n", region->name);

            region_base = curr_addr;
        }

        // 에러 #0
        // region 메모리 설정 이상으로, 이전 영역과 겹친 경우
        if (region_base < curr_addr)
        {
            lg1k_logm_error("%s[error(%d) case0]%s invalid region base error\n", ANSI_RED_FG, err, ANSI_RESET);
            lg1k_logm_error("  (reason) region(%s) base=0x%08llx < curr_addr=0x%08llx \n",
                            region->name, region_base, curr_addr);
            lg1k_logm_error("  (severity) critical\n");
            lg1k_logm_error("  (fix) can't fix !!! \n");

            ++err;
        }

        // 에러 #1
        // region 은 의미있는 영역 정보를 가지고 있어야 한다.
        if (region->size == 0)
        {
            lg1k_logm_error("%s[error(%d) case1]%s zero region size\n", ANSI_RED_FG, err, ANSI_RESET);
            lg1k_logm_error("  (reason) region(%s) size=0x00000000\n", region->name);
            lg1k_logm_error("  (severity) critical\n");
            lg1k_logm_error("  (fix) can't fix !!! all items belongs to the region will be set zero-size\n");

            ++err;
        }

        // 각 그룹의 주소값으로 초기화하고, 메모리 레이웃을 진행한다.
        curr_addr = region_base;

        lg1k_logm_memcfg_debug("region(%s) memcfg start. base=0x%08llx~0x%08llx, size=0x%08x(%dKB)\n",
                               region->name, region_base, region_end, region->size, __KB(region->size));

        list_for_each_entry(item, &region->item_list, list)
        {
            int i;
            LX_MEMCFG_T* memcfg = item->memcfg;
            int memcfg_num = item->memcfg_num;

            const char* item_name = item->name;
            u64 item_base = 0;
            u32 item_size = 0;

            for (i = 0; i < memcfg_num; i++)
            {
                u64 sub_end;
                u64 sub_base = memcfg[i].base;
                u32 sub_size = memcfg[i].size;
                const char* sub_name = memcfg[i].name;

                lg1k_logm_memcfg_debug("-- item(%s:%s) memcfg start. base=0x%08llx, size=0x%08x(%dKB)\n",
                                       item_name, sub_name, sub_base, sub_size, __KB(sub_size));

                // 만약 sub base 가 고정된 주소값을 가지고 있는 경우
                // 영역 내부에 위치하고 있는지, align 은 맞는지 체크한다.
                if (sub_base)
                {
                    // 에러 #2
                    // curr_addr 바깥에 위치하는지 체크한다. ( region 의 바깥 여부를 포함한다 )
                    // 앞선 블럭과 영역 겹침도 체크된다.
#if 0
                    if (sub_base < region_base)
#else
                    if (sub_base < curr_addr)
#endif
                    {
                        lg1k_logm_error("%s[error(%d) case2]%s wrong base address\n", ANSI_RED_FG, err, ANSI_RESET);
                        lg1k_logm_error("  (reason) item(%s:%s, sz=0x%08x) base=0x%08llx < curr_addr=0x%08llx\n",
                                        item_name, sub_name, sub_size, sub_base, region_base);
                        lg1k_logm_error("  (severity) major\n");
                        lg1k_logm_error("  (fix) set new base=0x%08llx\n", curr_addr);

                        sub_base = curr_addr;
                        ++err;
                    }

                    // 에러 #3
                    // 주소값에 대한 align 체크
                    if (sub_base % DEFAULT_ALIGN)
                    {
                        lg1k_logm_error("%s[error(%d) case3]%s invalid base align\n", ANSI_RED_FG, err, ANSI_RESET);
                        lg1k_logm_error("  (reason) item(%s:%s, sz=0x%08x) base=0x%08llx violates align=0x%04x\n",
                                        item_name, sub_name, sub_size, sub_base, DEFAULT_ALIGN);
                        lg1k_logm_error("  (severity) minor\n");
                        lg1k_logm_error("  (fix) set new base=0x%08llx\n", (ALIGN(sub_base, DEFAULT_ALIGN)));

                        sub_base = ALIGN(sub_base, DEFAULT_ALIGN);
                        ++err;
                    }
                }
                else
                {
                    sub_base = curr_addr;
                }

                // 에러 #4
                // size 값의 align 체크
                // 기존 정책에 따라 size align 을 강제화 하진 않도록 한다. 다만 warning 은 찍자.
                if (sub_size % DEFAULT_ALIGN)
                {
                    lg1k_logm_warn("%s[error(%d) case4]%s invalid size align\n", ANSI_RED_FG, err, ANSI_RESET);
                    lg1k_logm_warn("  (reason) item(%s:%s, sz=0x%08x) size violates default_align=0x%04x\n",
                                   item_name, sub_name, sub_size, DEFAULT_ALIGN);
                    lg1k_logm_warn("  (severity) minor\n");
                    lg1k_logm_warn("  (fix) do nothing, keep current size\n");
#if 0
                    sub_size = ALIGN(sub_size, DEFAULT_ALIGN);
                    ++err;
#endif
                }

                sub_end = sub_base + sub_size;

                // 에러 #5
                // 계산된 sub 영역이 region 을 벗어나는지 체크
                // region 의 끝을 넘지 않도록 수정 조치한다.
                if (region_end < sub_end)
                {
                    lg1k_logm_error("%s[error(%d) case5]%s wrong end address\n", ANSI_RED_FG, err, ANSI_RESET);
                    lg1k_logm_error("  (reason) item(%s:%s, sz=0x%08x) end=0x%08llx > region(%s) end=0x%08llx\n",
                                    item_name, sub_name, sub_size, sub_end, region_name, region_end);
                    lg1k_logm_error("  (severity) major\n");
                    lg1k_logm_error("  (fix) set new end=0x%08llx by -0x%08llx\n", region_end, sub_end - region_end);

                    sub_size -= (sub_end - region_end);
                    sub_end = region_end;

                    ++err;
                }

                // 현재 subent 의 base 정보를 업데이트/기록한다.
                // item 의 base 와 size 정보를 업데이트/트래킹 한다.
                memcfg[i].base = conv_memcfg_addr(sub_base);

                lg1k_logm_memcfg_debug("-- item(%s:%s) memcfg completed. base=0x%08llx, size=0x%08x(%dKB)\n",
                                       item_name, sub_name, sub_base, sub_size, __KB(sub_size));

                if (!item_base) item_base = sub_base;

                memcfg[i].base = conv_memcfg_addr(sub_base);
                memcfg[i].size = sub_size;

                item_size += sub_size;

                // curr_addr 업데이트 하고 다음 처리 준비
                curr_addr = ALIGN(sub_base + sub_size, DEFAULT_ALIGN);
                lg1k_logm_memcfg_debug("-- curr_addr moved to 0x%08llx\n", curr_addr);
            }

            // item 의 최종 위치/크기를 기록함
            // item->base = item_base;
            // item->size = item_size;

            lg1k_logm_memcfg_debug("- item(%s) memcfg completed. base=0x%08llx, size=0x%08x(%dKB)\n",
                                   item_name, item_base, item_size, __KB(item_size));
        }

        //lg1k_logm_memcfg_debug("region(%s) memcfg completed. base=0x%08llx~0x%08llx, size=0x%08x(%dKB)\n",
        //                      region->name, region_base, region_end, region->size, __KB(region->size));

        // region 메모리 설정 완료, 다음 region 메모리 설정 준비
        curr_addr = region_end;

        lg1k_logm_memcfg_debug("- region (%s) memcfg completed. curr_addr moved to 0x%08llx\n",
                               region_name, curr_addr);
    }


    lg1k_logm_noti("<!> memcfg %s... error_count=%d\n", (!err) ? "completed" : "faled", err);

    return err;
}
EXPORT_SYMBOL(os_memcfg_make_layout);

#ifdef UNIT_TEST
int os_memcfg_alloc_mpool(struct os_memcfg_desc* desc, int num_desc)
{
    return RET_OK;
}

#else
int os_memcfg_alloc_mpool(struct os_memcfg_desc* desc, int num_desc)
{
    int i;

    lg1k_logm_noti("memory pool registeration...\n");

    if (!desc || !num_desc)
    {
        return RET_ERROR;
    }

    for (i = 0; i < num_desc; i++)
    {
        int ret;
        u64 base;
        u32 size;
        const char* name = desc[i].name;
        const char* alias = desc[i].alias;
        u32 pool_type = desc[i].pool_type;

        if (!name)
        {
            continue;
        }

        ret = os_memcfg_get_info(name, &base, &size);

        if (ret != RET_OK)
        {
            continue;
        }

        /* check if CMA on/off test is enabled or not */
        if (pool_type == CMA_POOL)
        {
            if (alias && check_force_hma_pool(alias))
            {
                lg1k_logm_noti("<!> mpool(%s)'s alias(%s) is force set to HMA_POOL\n", name, alias);
                pool_type = HMA_POOL;
            }
            else if (check_force_hma_pool(name))
            {
                lg1k_logm_noti("<!> mpool(%s) is force set to HMA_POOL\n", name);
                pool_type = HMA_POOL;
            }
        }

        switch (pool_type)
        {
            case HMA_POOL:
            {
                /* if memory region is set to NO_CMA, try to pre-alloc device region from kernel */
                if (base && size)
                {
                    ret = hma_pool_register_type(name, base, size, CMA_POOL);

                    if (ret == 0)
                    {
                        lg1k_logm_noti("(x) CMA(%-15s %3dM@0x%08llx) HMA\n", name, size >> 20, base);
                        hma_alloc(name, size, 1 << 12);
                    }
                    else
                    {
                        lg1k_logm_noti("(?) CMA(%-15s %3dM@0x%08llx) register error\n", name, size >> 20, base);
                    }
                }
                else
                {
                    lg1k_logm_noti("(x) CMA(%-15s %3dM@0x%08llx) ignored\n", name, size >> 20, base);
                }
            }
            break;

            case CMA_POOL:
            {
                /* do nothing. each device will create its own CMA allocator */
                lg1k_logm_noti("(o) CMA(%-15s %3dM@0x%08llx) CMA\n", name, size >> 20, base);
            }
            break;

            default:
            {
                /* do nothing. this is BSP dedicated area */
                lg1k_logm_noti("(/) CMA(%-15s %3dM@0x%08llx) skip\n", name, size >> 20, base);
            }
            break;
        }

        // make user memory pool
        if (desc[i].alias)
        {
            ret = hma_pool_register_type(desc[i].alias, base, size, pool_type);

            if (!ret)
            {
                lg1k_logm_noti("cma(%16s), %3dM@0x%08llx, %s pool\n",
                               desc[i].alias, size >> 20, base, (pool_type == CMA_POOL) ? "CMA" : "HMA");
            }
            else
            {
                lg1k_logm_error("cannot register pool(%s)\n", desc[i].alias);
            }
        }
    }

    return RET_OK;
}
#endif
EXPORT_SYMBOL(os_memcfg_alloc_mpool);

#ifdef UNIT_TEST
#undef STR_ALLOC
#endif

static void dump(struct seq_file* s, const char* fmt, ...)
{
#ifdef STR_ALLOC
    char* str;
#else
    char str[257];
#endif
    va_list ap;

    va_start(ap, fmt);
#ifdef STR_ALLOC
    str = kvasprintf(GFP_KERNEL, fmt, ap);

    if (!str) return;

#else
    vsnprintf(str, 256, fmt, ap);
#endif
    va_end(ap);

    if (s)
    {
        seq_printf(s, str);
    }
    else
    {
        lg1k_logm_noti(str);
    }

#ifdef STR_ALLOC
    kfree(str);
#endif
}

static __attribute__((unused)) const char* marker0 = "└─";// termiated list/item
static __attribute__((unused)) const char* marker1 = "├─";// continuous list/item
static __attribute__((unused)) const char* marker2 = "│"; // continuous list

// 메모리 레이아웃 상태를 출력/덤프함. base logm 을 사용함.
void os_memcfg_dump(void* s, bool detail)
{
    struct os_memcfg_region* region;
    struct os_memcfg_item* item;

    if (!memcfg_enabled) return;

    dump(s, "NAME                BASE       ~ END        [SIZE(hex),  SIZE(MB/KB)]\n");

    list_for_each_entry(region, &ctx.region_list, list)
    {
        dump(s, "=====================================================================\n");
        dump(s, "%-19s 0x%08llx ~ 0x%08llx [0x%08x,%4dMB %03dKB]\n",
             region->name, region->base, region->base + region->size,
             region->size, __MB(region->size), __KB(region->size & 0xfffff));
        dump(s, "=====================================================================\n");

        list_for_each_entry(item, &region->item_list, list)
        {
            int i;
            LX_MEMCFG_T* memcfg = item->memcfg;
            int memcfg_num = item->memcfg_num;
            u64 item_base;
            u32 item_size;

            bool list_terminated = false;

            if (item == list_last_entry(&region->item_list, struct os_memcfg_item, list))
            {
                list_terminated = true;
            }

            if (RET_OK != os_memcfg_get_info(item->name, &item_base, &item_size))
            {
                item_base = 0xffffffff;
                item_size = 0xffffffff;
            }

            dump(s, "%-19s 0x%08llx ~ 0x%08llx [0x%08x,%4dMB %03dKB]\n",
                 item->name,
                 item_base, item_base + item_size,
                 item_size, __MB(item_size), __KB(item_size & 0xfffff));

            if (!detail) continue;

            for (i = 0; i < memcfg_num; i++)
            {
                u64 sub_base = memcfg[i].base;
                u32 sub_size = memcfg[i].size;
                const char* sub_name = memcfg[i].name;

                dump(s, "%s%-17s 0x%08llx ~ 0x%08llx [0x%08x,%4dMB %03dKB]\n",
                     (i < memcfg_num - 1) ? marker1 : marker0,
                     sub_name, sub_base,
                     sub_base + sub_size,
                     sub_size, __MB(sub_size), __KB(sub_size & 0xfffff));
            }
        }

        dump(s, "\n");
    }
}

EXPORT_SYMBOL(os_memcfg_dump);


// 디버깅 목적으로 cma pool 임에도 강제로 hma pool 이 될 수 있도록, 결과를 리턴한다.
// 실제 cma pool 이 기본 속성인 pool 을 다루는, 담당 모듈에서 이 함수를 직접 호출해 주어야 한다.
// hma pool 로 판정된 모듈의 경우에는 기본 속성과 무관하게 무조건 hma pool 로 만들어줘야 한다.
bool check_force_hma_pool(const char* pool)
{
#ifdef __KERNEL__
    char* tok, *sav_tok;
    char delim[] = ",";
    char pool_list[256];

    int ret;

    if (!pool) return false;

    ret = os_scan_kernel_cmdline("force_hma_pool=%s", pool_list);

    if (ret == RET_OK)
    {
        //printk("pool_list=%s, pool=%s\n", pool_list, pool);

        for (tok = simple_strtok(pool_list, delim, &sav_tok); tok; tok = simple_strtok(NULL, delim, &sav_tok))
        {
            int sz0 = strlen(tok);
            int sz1 = strlen(pool);

            if (sz0 == sz1 && !strncmp(tok, pool, sz0))
            {
                return true;
            }
        }
    }

#endif
    return false;
}

EXPORT_SYMBOL(check_force_hma_pool);

