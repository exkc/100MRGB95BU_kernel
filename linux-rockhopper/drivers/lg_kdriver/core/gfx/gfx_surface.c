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
 * GFX module control Drivers linux module
 *
 *  author      raxis.lim@lge.com
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>        /**< printk() */
#include <linux/init.h>
#include <linux/slab.h>          /**< kmalloc() */
#include <linux/vmalloc.h>       /**< kmalloc() */
#include <linux/fs.h>            /**< everything\ldots{} */
#include <linux/types.h>         /**< size_t */
#include <linux/fcntl.h>         /**< O_ACCMODE */
#include <linux/version.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>        /**< For request_region, check_region etc */
#include <asm/io.h>              /**< For ioremap_nocache */
#include <linux/workqueue.h>     /**< For working queue */
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/seq_file.h>

#include "gfx_impl.h"
#include "hma_alloc.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define MEMPOOL_MAIN_NAME   "surface"

/** default gfx memory pool ID (valid if multiple gfx memory pool exist) */
#define MEMPOOL_MAIN        0

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define ROUND32(width)          ((((width) + 31) / 32) * 32)

#define MEM_CFG_GET_BASE(id)    gMemCfgGfx.surface[(id)].base
#define MEM_CFG_GET_SIZE(id)    gMemCfgGfx.surface[(id)].size

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    char    name[HMA_POOL_LEN];
    int     alloc_cnt;
}
GFX_RGN_T;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
UINT32 GFX_AllocBuffer(UINT32 size);
void GFX_FreeBuffer(UINT32 phys_addr);
void GFX_ReportSurfaceList(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
static GFX_SURFACE_OBJ_T*   g_gfx_surf_list;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      GFX_AllocSurfaceMem(UINT32 surface_fd);
static int      GFX_FreeSurfaceMem(UINT32 surface_fd);
static BOOLEAN  GFX_CheckSurfacePhysAddr(UINT32 phys_addr);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static UINT32                   g_gfx_key_value;
static GFX_RGN_T                g_gfx_rgn[GFX_MAX_RGN_NUM];
static LX_GFX_PHYS_MEM_INFO_T   g_gfx_mem_pool_info;        /** default GFX memory pool info */

/*========================================================================================
    Implementation Group
========================================================================================*/

/** allocate surface's image memory which got from GFX_AllocSurfaceMem
 *
 * @param   int surface_fd , void *ptr
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int get_alloc_size_afbc(int w, int h)
{
    int number_block;
    int width;
    int height;
    int alloc_size;

    width = ALIGN(w, 16);
    height = ALIGN(h, 16);
    number_block = width * height / (16 * 16);
    alloc_size = width * height * 4;
    alloc_size += ALIGN(number_block * (128 / 8), (1 << 10));

    return alloc_size;
}

/** initialize GFX memory for surface
 *
 * @param   void
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int GFX_InitSurfaceMemory(void)
{
    int ret = RET_ERROR;

    phys_addr_t surf_mem_base = 0;
    int         surf_mem_size = 0;
    bool        use_pre_alloc_mem = false;

    // check if "surface" pool is already createed during kdriver initialization
    if (RET_OK == hma_pool_info(MEMPOOL_MAIN_NAME, &surf_mem_base, &surf_mem_size))
    {
        g_gfx_mem_pool_info.phys_addr   = (UINT32)surf_mem_base;
        g_gfx_mem_pool_info.length      = surf_mem_size;

        use_pre_alloc_mem = true;
    }
    else
    {
        g_gfx_mem_pool_info.phys_addr   = MEM_CFG_GET_BASE(MEMPOOL_MAIN);
        g_gfx_mem_pool_info.length      = MEM_CFG_GET_SIZE(MEMPOOL_MAIN);
    }

    g_gfx_key_value = 0;
    g_gfx_mem_pool_info.offset = 0;

    memset(g_gfx_rgn, 0x0, sizeof(GFX_RGN_T)*GFX_MAX_RGN_NUM);

    g_gfx_surf_list = (GFX_SURFACE_OBJ_T*)vzalloc(sizeof(GFX_SURFACE_OBJ_T) * GFX_MAX_SURFACE);
    GFX_CHECK_ERROR(NULL == g_gfx_surf_list, goto func_exit, "can't alloc surf_list\n");

    snprintf(g_gfx_rgn[MEMPOOL_MAIN].name, HMA_POOL_LEN, MEMPOOL_MAIN_NAME);

    if (use_pre_alloc_mem)
    {
        GFX_NOTI("use pre-allocated surface pool(%s) %dMB0x@%08x\n", g_gfx_rgn[MEMPOOL_MAIN].name,
                 g_gfx_mem_pool_info.length >> 20, g_gfx_mem_pool_info.phys_addr);
        // do nothing
    }
    else
    {
        ret = hma_pool_register_type(g_gfx_rgn[MEMPOOL_MAIN].name, (unsigned long) g_gfx_mem_pool_info.phys_addr,
                                     g_gfx_mem_pool_info.length, HMA_POOL);
        GFX_CHECK_ERROR(ret < 0, goto func_exit, "can't alloc surf_hma(main)\n");

        GFX_NOTI("alloc surface pool(%s) %dMB@0x%08x\n", g_gfx_rgn[MEMPOOL_MAIN].name, g_gfx_mem_pool_info.length >> 20,
                 g_gfx_mem_pool_info.phys_addr);
    }

    ret = RET_OK; /* all work done */
func_exit:
    return ret;
}

/** allocate surface memory based on LX_GFX_SURFACE_SETTING_PARAM_T param
 *
 * @param   LX_GFX_SURFACE_SETTING_PARAM_T
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int GFX_AllocSurface(LX_GFX_SURFACE_SETTING_PARAM_T* surface)
{
    int i;
    int slot = -1;
    int ret  = RET_ERROR;

    /* I would like to give the special fd to the external memory based surface */
    if ((ULONG)surface->surface_setting.phys_addr) { i = 0; }
    else                                            { i = 0x80; }

    /* serach empty slot */
    for (/* nop */ ; i < GFX_MAX_SURFACE; i++)
    {
        if (!g_gfx_surf_list[i].bAlloc) { slot = i; break; }
    }

    GFX_CHECK_ERROR(slot < 0, goto func_exit, "surface pool(max %d) is full\n", GFX_MAX_SURFACE);
    GFX_PRINT("empty slot = %d\n", slot);

    surface->surface_fd                     = slot;

    g_gfx_surf_list[slot].bAlloc            = 1;
    g_gfx_surf_list[slot].pid               = (UINT32)current->tgid;
    g_gfx_surf_list[slot].tid               = (UINT32)current->pid;
    g_gfx_surf_list[slot].surf.surface_fd   = slot;
    g_gfx_surf_list[slot].surf.type         = surface->surface_setting.type;
    g_gfx_surf_list[slot].surf.pixel_format = surface->surface_setting.pixel_format;
    g_gfx_surf_list[slot].surf.width        = surface->surface_setting.width;
    g_gfx_surf_list[slot].surf.height       = surface->surface_setting.height;
    g_gfx_surf_list[slot].surf.alignment    = surface->surface_setting.alignment;

    g_gfx_surf_list[slot].cIdx              = g_gfx_key_value++;
    g_gfx_surf_list[slot].cTick             = OS_GetMsecTicks();

    GFX_NOTI("alloc surface. pid=%05d, tid=%05d\n", (UINT32)current->tgid, (UINT32)current->pid);

    /* get task name */
    get_task_comm(g_gfx_surf_list[slot].psname, current);

    GFX_TRACE("fd %d, dim %dx%d\n", slot, g_gfx_surf_list[slot].surf.width, g_gfx_surf_list[slot].surf.height);

    /* if application doesn't know stride, caculate it here based on HW limitation
     *
     * 1) basic alignment limitation is at least 4-byte
     * 2) some HW such as OSD requires 16-byte aligned stride
     * 3) 16x16 is the macro block size of MPEG
     *
     * As result, 16byte aligned stride is best choice to satify all surface usage.
     *
     * for exmaple, 32bppt surface with width 1366 produces stride value 5472 (same as 1368*4 )
     */
    if (surface->surface_setting.stride == 0)
    {
        UINT32 stride;
        UINT32 width = surface->surface_setting.width;

        switch (surface->surface_setting.pixel_format)
        {
            case LX_GFX_PIXEL_FORMAT_INDEX_0:   stride = 0; break;

            case LX_GFX_PIXEL_FORMAT_INDEX_1:   stride = ROUND32(width * 1) / 8; break;

            case LX_GFX_PIXEL_FORMAT_INDEX_2:   stride = ROUND32(width * 2) / 8; break;

            case LX_GFX_PIXEL_FORMAT_INDEX_4:   stride = ROUND32(width * 4) / 8; break;

            case LX_GFX_PIXEL_FORMAT_INDEX_8:
            case LX_GFX_PIXEL_FORMAT_ALPHA_8:   stride = ROUND32(width * 8) / 8; break;

            case LX_GFX_PIXEL_FORMAT_Y8__Cb8_444__Cr8_444 :
            case LX_GFX_PIXEL_FORMAT_Cb8_420__Cr8_420:
            case LX_GFX_PIXEL_FORMAT_Cb8_422__Cr8_422: stride = ROUND32(width * 8) / 8; break;

            case LX_GFX_PIXEL_FORMAT_CbCr_420:      /*16*/
            case LX_GFX_PIXEL_FORMAT_CbCr_422:      /*16*/
            case LX_GFX_PIXEL_FORMAT_CbCr_444:      /*16*/
            case LX_GFX_PIXEL_FORMAT_Y0Cb0Y1Cr0_422:/*16*/ stride = ROUND32(width * 16) / 8; break;

            case LX_GFX_PIXEL_FORMAT_YCbCr655:
            case LX_GFX_PIXEL_FORMAT_AYCbCr2644:
            case LX_GFX_PIXEL_FORMAT_AYCbCr4633:
            case LX_GFX_PIXEL_FORMAT_AYCbCr6433:
            case LX_GFX_PIXEL_FORMAT_RGB565:
            case LX_GFX_PIXEL_FORMAT_ARGB1555:
            case LX_GFX_PIXEL_FORMAT_ARGB4444:
            case LX_GFX_PIXEL_FORMAT_ARGB6343:  stride = ROUND32(width * 16) / 8; break;

            /* raxis.lim (2019/06/19) http://clm.lge.com/issue/browse/SCDCR-2465
             * make 64byte aligned surface for GPU to handle gfx surface.
             * it means 16-aligned-value in unit of pixel width.
             */
            case LX_GFX_PIXEL_FORMAT_ARGB8888_AFBC:
            case LX_GFX_PIXEL_FORMAT_ARGB8888_FBDC:
            case LX_GFX_PIXEL_FORMAT_AYCbCr8888:
            case LX_GFX_PIXEL_FORMAT_ARGB8888:
            default:                                stride = ALIGN(width * 4, 64); break;

        }

#if 0
        /* make 16 byte aligned stride */
        g_gfx_surf_list[slot].surf.stride = LX_CALC_ALIGNED_VALUE(stride, 4);
#else
        /* FIXME: disable 16byte align due to some side effect - HAL_GAL_DecodeImage etc */
        g_gfx_surf_list[slot].surf.stride = stride;
#endif
    }
    else
    {
        UINT32 stride;

        /* if external surface with AFBC format is created, always calculate stride
         * some app might send the wrong stride without considering AFBC type.
         */
        if (surface->surface_setting.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_AFBC)
        {
            stride = ALIGN(surface->surface_setting.width * 4, 64);
        }
        else
        {
            stride  = surface->surface_setting.stride;
        }

        g_gfx_surf_list[slot].surf.stride = stride;
    }

    /*  raxis.lim (2010/05/13)
     *  --  we need fill surface memory info even though it is from external memory
     *      since application can query surfaec memory regardless of surface type.
     *      but it is important that valid information may be only physical address or length.
     */
    if (surface->surface_setting.phys_addr)
    {
        UINT32 mem_length;

        g_gfx_surf_list[slot].surf.phys_addr = surface->surface_setting.phys_addr;
        g_gfx_surf_list[slot].mem.phys_addr = surface->surface_setting.phys_addr;
        g_gfx_surf_list[slot].mem.offset    = (UINT32)surface->surface_setting.phys_addr - (UINT32)
                                              g_gfx_mem_pool_info.phys_addr;

        /* if external surface with AFBC format is created, I can't use memory length as stride x height
         * DO NOT forget that AFBC image requires additonal memory by AFBC header.
         */
        if (surface->surface_setting.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_AFBC)
        {
            mem_length = get_alloc_size_afbc(surface->surface_setting.width, surface->surface_setting.height);
        }
        else if (surface->surface_setting.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_FBDC)
        {
            mem_length = _get_alloc_size_fbdc(surface->surface_setting.width, surface->surface_setting.height);
        }
        else
        {
            mem_length = surface->surface_setting.stride * surface->surface_setting.height;
        }

        g_gfx_surf_list[slot].mem.length = mem_length;

        ret = RET_OK;
    }
    else
    {
        ret = GFX_AllocSurfaceMem(surface->surface_fd);
    }

    GFX_CHECK_ERROR(RET_OK != ret, g_gfx_surf_list[slot].bAlloc = 0;
                    goto func_exit, "fail to alloc surf (%d)\n", surface->surface_fd);

    g_gfx_surf_list[slot].bPalette = 0;

    /* return surface_settings data */
    memcpy(&surface->surface_setting, &g_gfx_surf_list[slot].surf, sizeof(LX_GFX_SURFACE_SETTING_T));

    ret = RET_OK;
func_exit:

    if (ret != RET_OK)
    {
        /* raxis.lim (2012/11/12) print memory pool info for debug */
        LX_GFX_MEM_STAT_T   gfx_mem_stat;
        int                 surface_cnt = 0;

        (void)GFX_GetSurfaceMemoryStat(&gfx_mem_stat);
        printk("gfx memory pool info = base %x, size %d KB, total_alloc %d KB, total_free %d KB\n",
               gfx_mem_stat.surface_mem_base, gfx_mem_stat.surface_mem_length >> 10,
               gfx_mem_stat.surface_mem_alloc_size >> 10, gfx_mem_stat.surface_mem_free_size >> 10);

        for (i = 0; i < GFX_MAX_SURFACE; i++)
        {
            if (g_gfx_surf_list[i].bAlloc) surface_cnt++;
        }

        printk("total %d surface(s) allocated\n", surface_cnt);
    }

    return ret;
}

static BOOLEAN  GFX_CheckSurfacePhysAddr(UINT32 phys_addr)
{
    BOOLEAN result = FALSE;

    result = (phys_addr >= (UINT32)g_gfx_mem_pool_info.phys_addr &&
              phys_addr < (UINT32)g_gfx_mem_pool_info.phys_addr + g_gfx_mem_pool_info.length) ? TRUE : FALSE;

    return result;
}

/** free allocated surface memory which got from GFX_AllocSurface
 *
 * @param   int surface_fd
 * @return  int 0 : OK , -1 : NOT OK
 */
int GFX_FreeSurface(UINT32 surface_fd)
{
    ULONG phys_addr;
    int ret = RET_ERROR;

    GFX_NOTI("destroy surface. pid=%05d, tid=%05d\n", (UINT32)current->tgid, (UINT32)current->pid);

    /* check error condition */
    GFX_CHECK_ERROR(surface_fd >= GFX_MAX_SURFACE,          goto func_exit, "invalid fd 0x%x(%d)\n", surface_fd,
                    surface_fd);
    GFX_CHECK_ERROR(!g_gfx_surf_list[surface_fd].bAlloc,    goto func_exit, "not allocated fd 0x%x(%d)\n", surface_fd,
                    surface_fd);

    phys_addr = (UINT32)g_gfx_surf_list[surface_fd].surf.phys_addr;

    /* since surface is allocated with the external memory, we should check phys_addr range */
    if (g_gfx_surf_list[surface_fd].surf.type == LX_GFX_SURFACE_TYPE_MEM_BUFFER && GFX_CheckSurfacePhysAddr(phys_addr))
    {
        GFX_FreeSurfaceMem(surface_fd);
    }

    /*  raxis.lim (2010/07/01)
     *  -- palettte memory should be free when paleltte data is available.
     *  -- bPalette variable seems not enough to free palette data.
     */
    if (NULL != g_gfx_surf_list[surface_fd].pal)
    {
        OS_Free(g_gfx_surf_list[surface_fd].pal);
    }

    memset(&g_gfx_surf_list[surface_fd], 0x0, sizeof(GFX_SURFACE_OBJ_T));

    ret = RET_OK; /* all work done */
func_exit:
    return ret;
}


/** free all surfaces created by specific process
 *
 * @param   pid
 */
void GFX_FreeProcessSurface(UINT32 pid)
{
    int i;
    int num_of_freed = 0;

    GFX_NOTI("+ do surface cleanup for pid %d\n", pid);

    for (i = 0 ; i < GFX_MAX_SURFACE; i++)
    {
        if (g_gfx_surf_list[i].bAlloc && g_gfx_surf_list[i].pid == pid)
        {
            //GFX_NOTI("+ destroy surface fd=0x%02x size=%dx%d\n", i,  g_gfx_surf_list[i].surf.width, g_gfx_surf_list[i].surf.height);
            GFX_CHECK_ERROR(RET_OK != GFX_FreeSurface(i), /* do nothing */, "surface fd 0x%d(%d) can't be freed\n", i, i);
            num_of_freed++;
        }
    }

    if (num_of_freed > 0)
    {
        GFX_WARN("%d surface(s) with pid %d freed automatically\n", num_of_freed, (int)pid);
    }
}

void GFX_DetatchProcessSurface(UINT32 surface_fd)
{
    if (surface_fd < GFX_MAX_SURFACE)
    {
        if (g_gfx_surf_list[surface_fd].bAlloc)
        {
            GFX_WARN("surface(0x%x) detatched from %05d:%05d(%s)\n",
                     surface_fd,
                     g_gfx_surf_list[surface_fd].pid,
                     g_gfx_surf_list[surface_fd].tid,
                     g_gfx_surf_list[surface_fd].psname);

            g_gfx_surf_list[surface_fd].pid = -9999;
            g_gfx_surf_list[surface_fd].tid = -9999;
            snprintf(g_gfx_surf_list[surface_fd].psname, TASK_COMM_LEN, "----");
        }
    }
}

int GFX_QuerySurface(LX_GFX_SURFACE_QUERY_PARAM_T*  param)
{
    LX_GFX_SURFACE_SETTING_T*   ret_settings = NULL;
    int ret = RET_ERROR;

    switch (param->query_type)
    {
        case LX_GFX_SURFACE_QUERY_TYPE_SURFACE_FD:
        {
            int fd = param->query_data.surface_fd;

            GFX_CHECK_ERROR(fd < 0, goto func_exit, "invalid fd 0x%x(%d)\n", fd, fd);
            GFX_CHECK_ERROR(fd >= GFX_MAX_SURFACE,  goto func_exit, "invalid fd 0x%x(%d)\n", fd, fd);
            GFX_CHECK_ERROR(!g_gfx_surf_list[fd].bAlloc, goto func_exit, "non-allocated fd 0x%x(%d)\n", fd, fd);

            ret_settings = &(g_gfx_surf_list[fd].surf);
        }
        break;

        case LX_GFX_SURFACE_QUERY_TYPE_SURFACE_OFFSET:
        case LX_GFX_SURFACE_QUERY_TYPE_SURFACE_PHYS_ADDR:
        {
            int i;
            ULONG phys_addr = (param->query_type == LX_GFX_SURFACE_QUERY_TYPE_SURFACE_PHYS_ADDR) ?
                              param->query_data.surface_phys_addr :
                              param->query_data.surface_offset + g_gfx_mem_pool_info.phys_addr;

            for (i = 0; i < GFX_MAX_SURFACE; i++)
            {
                if (g_gfx_surf_list[i].bAlloc && (UINT32)g_gfx_surf_list[i].surf.phys_addr == phys_addr)
                {
                    ret_settings = &(g_gfx_surf_list[i].surf); break;
                }
            }
        }
        break;

        default:
            GFX_ERROR("uknown query type\n"); goto func_exit;
    }

    GFX_CHECK_CODE(NULL == ret_settings, goto func_exit, "sourface not found. type=%d value=0x%x\n", param->query_type,
                   param->query_data.value);
    memcpy(&param->surface_setting, ret_settings, sizeof(LX_GFX_SURFACE_SETTING_T));

    ret = RET_OK;
func_exit:
    return ret;
}

/** simplfied form of GFX_QuerySurface
 *
 *
 */
int      GFX_GetSurfaceInfo(int surface_fd, LX_GFX_SURFACE_SETTING_T* surface_info)
{
    int ret;
    LX_GFX_SURFACE_QUERY_PARAM_T query_param;

    memset(&query_param, 0x0, sizeof(LX_GFX_SURFACE_QUERY_PARAM_T));

    query_param.query_type = LX_GFX_SURFACE_QUERY_TYPE_SURFACE_FD;
    query_param.query_data.surface_fd = surface_fd;

    ret = GFX_QuerySurface(&query_param);
    GFX_CHECK_CODE(RET_OK != ret, return ret, "invalid surface fd 0x%x \n", surface_fd);

    memcpy(surface_info, &query_param.surface_setting, sizeof(LX_GFX_SURFACE_SETTING_T));

    return ret;
}

GFX_SURFACE_OBJ_T* GFX_GetSurfaceObject(UINT32 fd)
{
#if 1

    if (fd >= GFX_MAX_SURFACE) return NULL;

    if (!g_gfx_surf_list[fd].bAlloc) return NULL;

#else
    GFX_CHECK_CODE(fd >= GFX_MAX_SURFACE, return NULL, "invalid fd 0x%x(%d)\n", fd, fd);
    GFX_CHECK_CODE(!g_gfx_surf_list[fd].bAlloc, return NULL, "non-allocated fd 0x%x(%d)\n", fd, fd);
#endif

    return &g_gfx_surf_list[fd];
}

/** free allocated surface's image memory which got from GFX_FreeSurfaceMem
 *
 * @param   int surface_fd
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int GFX_FreeSurfaceMem(UINT32 surface_fd)
{
    int ret = RET_OK;

    UINT32  phys_addr = (UINT32)g_gfx_surf_list[surface_fd].surf.phys_addr;

    /* surfcae address is already checked before calling this function !! */
    hma_free(g_gfx_rgn[MEMPOOL_MAIN].name, (unsigned long)phys_addr);

    g_gfx_rgn[MEMPOOL_MAIN].alloc_cnt--;

    return ret;
}

static int GFX_AllocSurfaceMem(UINT32 surface_fd)
{
    int     mem_length;
    phys_addr_t ptr = (phys_addr_t)NULL;
    int     ret = RET_ERROR;

    if (g_gfx_surf_list[surface_fd].surf.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_AFBC)
    {
        int w = g_gfx_surf_list[surface_fd].surf.width;
        int h = g_gfx_surf_list[surface_fd].surf.height;
        mem_length = get_alloc_size_afbc(w, h);
    }
    else if (g_gfx_surf_list[surface_fd].surf.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_FBDC)
    {
        int w = g_gfx_surf_list[surface_fd].surf.width;
        int h = g_gfx_surf_list[surface_fd].surf.height;
        mem_length = _get_alloc_size_fbdc(w, h);
    }
    else
    {
        mem_length = g_gfx_surf_list[surface_fd].surf.height * g_gfx_surf_list[surface_fd].surf.stride;
        mem_length = LX_CALC_ALIGNED_VALUE(mem_length, 12 /* 4K */);
    }

    ptr = hma_alloc(g_gfx_rgn[MEMPOOL_MAIN].name, mem_length, PAGE_SIZE);
    GFX_CHECK_ERROR((phys_addr_t)NULL == ptr, goto func_exit, "out of surfmem. can't alloc %d KB\n", mem_length >> 10);

    g_gfx_rgn[MEMPOOL_MAIN].alloc_cnt++;

    g_gfx_surf_list[surface_fd].surf.phys_addr  = (UINT32)ptr;
    g_gfx_surf_list[surface_fd].mem.phys_addr   = (UINT32)ptr;
    g_gfx_surf_list[surface_fd].mem.length      = mem_length;
    g_gfx_surf_list[surface_fd].mem.offset      = (UINT32)ptr - (UINT32)g_gfx_mem_pool_info.phys_addr;

    ret = RET_OK;   /* all work done */
func_exit:
    return ret;
}

/** get surface's image memory inform
 *
 * @param   LX_GFX_SURFACE_MEM_INFO_PARAM_T *mem
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int GFX_GetSurfaceMemory(LX_GFX_SURFACE_MEM_INFO_PARAM_T* mem_info)
{
    GFX_CHECK_ERROR(mem_info->surface_fd >= GFX_MAX_SURFACE, return RET_ERROR, "invaild surface fd\n");

    memcpy(&mem_info->surface_mem, &(g_gfx_surf_list[mem_info->surface_fd].mem), sizeof(LX_GFX_PHYS_MEM_INFO_T));

    GFX_TRACE("fd:0x%x(%d), phys_addr:0x%x, offset:%d, length:%d\n",
              mem_info->surface_fd, mem_info->surface_fd,
              mem_info->surface_mem.phys_addr, mem_info->surface_mem.offset, mem_info->surface_mem.length);

    return RET_OK;
}


/** mmap the surface's image physical memory to virtual memory for using user level
 *
 * @param   struct vm_area_struct *vma
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int GFX_SurfaceMmap(struct file* file, struct vm_area_struct* vma)
{
    ULONG   phy_start;
    ULONG   phy_end;
    ULONG   off = vma->vm_pgoff << PAGE_SHIFT;
    ULONG   size = vma->vm_end - vma->vm_start;
    ULONG   end = PAGE_ALIGN(off + size);

    GFX_FILE_CTX_T* dev_ctx = file->private_data;

    /* check size is page aligned */
    if (size & (PAGE_SIZE - 1)) return -EINVAL;

    phy_start = g_gfx_mem_pool_info.phys_addr & PAGE_MASK;

#if 0
    phy_end   = PAGE_ALIGN(phy_start + mem_size);

    if (phy_start <= offset && end <= phy_end) goto allowed;

    return -EINVAL;
#else
    PARAM_UNUSED(phy_end);
    PARAM_UNUSED(end);
#endif

    if (!dev_ctx->cached_mmap)
    {
        /* raxis.lim (2018/07/11) SDMSTG-488
         * pgprot_noncached -> pgprot_writecombine
         * change pgprot function to support non-aligned access to mmapped memory
         */
        vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
    }

    off +=  phy_start;
    vma->vm_pgoff = off >> PAGE_SHIFT;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
    vm_flags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))
    vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
#else
    vma->vm_flags |= VM_RESERVED;
#endif

    if (remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT, size, vma->vm_page_prot))
        return -EAGAIN;

    return 0;
}

/** save the pallete date to surface
 *
 */
int GFX_SetSurfacePalette(int surface_fd, int size, UINT32* data)
{
    int ret = RET_ERROR;

    GFX_CHECK_ERROR(g_gfx_surf_list[surface_fd].surf.width == 0 || g_gfx_surf_list[surface_fd].surf.height == 0,
                    goto func_exit, "invalid palette op on free surface. fd 0x%x(%d)\n", surface_fd, surface_fd);

    /*  raxis.lim (2010/07/01) -- bug fix
     *  --  the real palette memory is allocated when it is set for the first time.
     *  --  We know the maximum palette size is 256 for 8bpp surface, so it is very normal
     *      to allocate the maximum 256 palette entries.
     */
    if (!g_gfx_surf_list[surface_fd].pal)
    {
        g_gfx_surf_list[surface_fd].pal = (UINT32*)OS_Malloc(sizeof(UINT32) * 256);
    }

    GFX_CHECK_ERROR(NULL == g_gfx_surf_list[surface_fd].pal, goto func_exit, "can't alloc surf_palette\n");

    memcpy((void*)g_gfx_surf_list[surface_fd].pal, (void*)data, sizeof(UINT32)*size);

    /*  raxis.lim (2010/07/01) -- bug fix
     *  -- PalSize should be number of palette entry not byte size of palette data
     *  -- bPalDownload field should be removed ( GFX should always download palette when blit time )
     */
    g_gfx_surf_list[surface_fd].bPalette    = 1;
    g_gfx_surf_list[surface_fd].bPalDownload = 0;
    g_gfx_surf_list[surface_fd].PalSize     = size;

    GFX_PRINT("fd 0x%x(%d), palsz %d, datap %p\n",
              surface_fd, surface_fd, g_gfx_surf_list[surface_fd].PalSize, g_gfx_surf_list[surface_fd].pal);

    ret = RET_OK;   /* all work done */
func_exit:
    return ret;
}

/** get the pallete date from surface
 *
 */
int GFX_GetSurfacePalette(int surface_fd, int size, UINT32* data)
{
    if ((g_gfx_surf_list[surface_fd].surf.width == 0) || (g_gfx_surf_list[surface_fd].surf.height == 0)
            || (g_gfx_surf_list[surface_fd].pal == NULL))
    {
        GFX_ERROR("ERROR : tried to save palette data on free surface [%d]\n", surface_fd);
        return RET_ERROR;
    }

    memcpy((void*)data, (void*)g_gfx_surf_list[surface_fd].pal, sizeof(UINT32)*size);

    GFX_PRINT("fd 0x%x(%d), palSize %d, palData %p\n",
              surface_fd, surface_fd, g_gfx_surf_list[surface_fd].PalSize, g_gfx_surf_list[surface_fd].pal);

    return RET_OK;
}

/** get memory statistics for GFX surface memory
 *  this function is used in IOCTL for debug, and in gfx proc.
 *  application can use this information to monitor memroy usage.
 *
 *  @param  pMemStat [IN] pointer to LX_GFX_MEM_STAT_T ( surface memory info )
 *  @return RET_OK
 *
 */
int GFX_GetSurfaceMemoryStat(LX_GFX_MEM_STAT_T* pMemStat)
{
    int i;
    int val;
    int surf_cnt = 0;

    pMemStat->surface_max_num       = GFX_MAX_SURFACE;
    pMemStat->surface_mem_base      = g_gfx_mem_pool_info.phys_addr;
    pMemStat->surface_mem_length    = g_gfx_mem_pool_info.length;

    hma_pool_status(g_gfx_rgn[MEMPOOL_MAIN].name, hma_pool_status_free_size, &val);
    pMemStat->surface_mem_free_size = val;
    pMemStat->surface_mem_alloc_size = pMemStat->surface_mem_length - pMemStat->surface_mem_free_size;

    /* surface count should include both internal surface and external surface */
    for (i = 0; i < GFX_MAX_SURFACE; i++)
    {
        if (g_gfx_surf_list[i].bAlloc) surf_cnt++;
    }

    pMemStat->surface_alloc_num = surf_cnt;

    return RET_OK;
}

/** allocate dynamic buffer from GFX surface memory
 *
 *  @note buffer allocation may fail when too-big-sized buffer requested. so app should check if return address is NULL or NULL
 *
 *  @param size [IN] buffer size in byte
 *  @return physical address if success, 0x0 if failed
 */
UINT32          GFX_AllocBuffer(UINT32 size)
{
    phys_addr_t ptr;

    if (size == 0) size = (1 << PAGE_SHIFT);

    //  GFX_LockDevice();
    ptr = hma_alloc(g_gfx_rgn[MEMPOOL_MAIN].name, size, PAGE_SIZE);

    if (ptr)  g_gfx_rgn[MEMPOOL_MAIN].alloc_cnt++;

    GFX_CHECK_ERROR((phys_addr_t)NULL == ptr, /* nop */, "out of surf region ? sz %d\n", size);

    //  GFX_UnlockDevice();
    return (UINT32)ptr;
}

/** free dynamic buffer
 *
 *  @param phys_addr [IN] physical address
 */
void            GFX_FreeBuffer(UINT32 phys_addr)
{
    //  GFX_LockDevice();
    GFX_CHECK_ERROR(0x0 == phys_addr, return, "null param\n");

    GFX_CHECK_ERROR(!GFX_CheckSurfacePhysAddr(phys_addr), return, "invalid phys_addr 0x%08x\n", phys_addr);

    g_gfx_rgn[MEMPOOL_MAIN].alloc_cnt--;
    hma_free(g_gfx_rgn[MEMPOOL_MAIN].name, phys_addr);

    //  GFX_UnlockDevice();
}

int     GFX_GetSurfaceFdList(int* surf_list, int max_surf, int* num_surf)
{
    int i;
    int j;

    GFX_CHECK_ERROR(NULL == surf_list || NULL == num_surf, return RET_ERROR, "null param\n");

    for (i = 0, j = 0; i < GFX_MAX_SURFACE && j < max_surf; i++)
    {
        if (g_gfx_surf_list[i].bAlloc)
        {
            surf_list[j++] = i;
        }
    }

    *num_surf = j;
    return RET_OK;
}


void GFX_ReportSurfaceList(struct seq_file* m)
{
    int i;
    int surface_cnt = 0;

    for (i = 0; i < GFX_MAX_SURFACE; i++)
    {
        GFX_SURFACE_OBJ_T*  surface = &g_gfx_surf_list[i];

        if (surface->bAlloc)
        {
            surface_cnt++;
            seq_printf(m, "%3x(%04d) %d,%3d,%4d,%08x, %d,%04x, %4dx%-4d, %d,%4d, %d, 0x%8x,0x%08x,%8d, %05d:%05d(%s)\n",
                       i, i,
                       surface->bPalette, surface->PalSize, surface->cIdx, surface->cTick,
                       surface->surf.type, surface->surf.pixel_format,
                       surface->surf.width, surface->surf.height,
                       surface->surf.alignment, surface->surf.stride,
                       (surface->pal) ? 1 : 0,
                       surface->mem.phys_addr, surface->mem.offset, surface->mem.length,
                       surface->pid, surface->tid, surface->psname);
        }
    }

    seq_printf(m, "<!> total %d surfaces created\n", surface_cnt);
}

/** @} */
