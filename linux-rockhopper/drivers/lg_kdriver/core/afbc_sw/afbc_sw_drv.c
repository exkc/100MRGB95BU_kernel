/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2021 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/*  ----------------------------------------------------------------------------------------
    Control Constants
    ----------------------------------------------------------------------------------------*/
#define AFBC_FILL_SINGLE_LINE

/*  ----------------------------------------------------------------------------------------
    File Inclusions
    ----------------------------------------------------------------------------------------*/
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include "afbc_sw_drv.h"
#include "debug_util.h"
#include "proc_util.h"

/*  ----------------------------------------------------------------------------------------
    Constant Definitions
    ----------------------------------------------------------------------------------------*/
// AFBC 1.0 에서는 afbc body 가 1KB align 되는 것을 권장하고 있다.
// AFBC 1.1 에서는 이런 권장/제약 사항이 없는것 같다.
// 따라서 AFBC 1.0 에 준하여 align 된 메모리를 다루도록 한다.
//
// GPU, GFX 등이 afbc header 와 afbc payload 가 연속된 메모리로 배치됨을 가정하기에,
// AFBC_PREFERRED_BODY_ALIGN_BYTE 는 afbc header 크기 얻어올때에도 고려해야 한다.
#define AFBC_PREFERRED_BODY_ALIGN_BYTE  (1<<10)

// AFRC unit block size (CB ? Coding Block) 크기는 화질과 압축률 고려하여 32Byte 로 고정한다.
// AFRC 스펙에 의거하여 각 입력 버퍼는 라인별로 4x4 pixel (64 byte) 단위로 압축이 된다.
#define AFRC_CB_SZ (32)
#define AFRC_CU_PXL_SZ (16) // 4x4 compressed unit size in pixel

/*  ----------------------------------------------------------------------------------------
    Macro Definitions
    ----------------------------------------------------------------------------------------*/
#define afbc_sw_error(format, args...)      DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define afbc_sw_warn(format, args...)       DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define afbc_sw_noti(format, args...)       DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define afbc_sw_info(format, args...)       DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define afbc_sw_debug(format, args...)      DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define afbc_sw_trace(format, args...)      DBG_PRINT(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define afbc_sw_check_code(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, afbc_sw_warn, __if_action , fmt, ##args )

#define afbc_sw_check_error(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, afbc_sw_error, __if_action , fmt, ##args )

#define INIT_CTX(ctx)   do { if (!ctx) ctx = &default_ctx; }while(0)

#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

/*  ----------------------------------------------------------------------------------------
    Type Definitions
    ----------------------------------------------------------------------------------------*/
struct afbc_header
{
    unsigned int offset;
    unsigned char bytes[12];
};

struct afbc_payload
{
    unsigned char bytes[1024];
};

struct afrc_payload
{
    unsigned char bytes[AFRC_CB_SZ];
};

struct afbc_sw_string_info
{
    int version;
    const char* fmt_str;
    const char* version_str;
};

/*  ----------------------------------------------------------------------------------------
    External Function Prototype Declarations
    ----------------------------------------------------------------------------------------*/

/*  ----------------------------------------------------------------------------------------
    External Variables
    ----------------------------------------------------------------------------------------*/

/*  ----------------------------------------------------------------------------------------
    global Variables
    ----------------------------------------------------------------------------------------*/

/*  ----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
    ----------------------------------------------------------------------------------------*/
static void afbc_sw_proc_init(void);

/*  ----------------------------------------------------------------------------------------
    Static Variables
    ----------------------------------------------------------------------------------------*/
static int g_afbc_sw_debug_fd = -1;

/*  ----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
    ----------------------------------------------------------------------------------------*/

/*  ----------------------------------------------------------------------------------------
    Static Variables
    ----------------------------------------------------------------------------------------*/
static struct afbc_ctx default_ctx =
{
    .version = AFBC_SW_VER_1_0,
};

static struct afbc_ctx afbc_1_0_ctx =
{
    .version = AFBC_SW_VER_1_0,
};

static struct afbc_ctx afbc_1_1_ctx =
{
    .version = AFBC_SW_VER_1_1,
};

#if 0
static struct afbc_ctx afrc_ctx =
{
    .version = AFBC_SW_VER_AFRC,
};
#endif

static struct afbc_sw_string_info string_table[] =
{
    { AFBC_SW_VER_1_0, "afbc", "afbc16x16" },
    { AFBC_SW_VER_1_1, "afbc", "afbc32x8" },
    { AFBC_SW_VER_AFRC, "afrc", "afrc" },
};

static struct afbc_sw_string_info invalid_info = { -1, "invalid", "invalid"};

/*  ========================================================================================
    Implementation Group
    ========================================================================================*/

// AFBC SW 동작에 필요한 중요 정보를 설정한다.
// - AFBC 버전에 따라 header, payload 포맷이 달라지므로 가장 중요한정보이다.
// - 추후 필요시 확장 하도록 한다.
struct afbc_ctx afbc_sw_init_context(unsigned int version)
{
    struct afbc_ctx ctx;

    memset(&ctx, 0x0, sizeof(ctx));
    ctx.version = version;

    return ctx;
}

// AFBC SW 설정은 시스템 초기화시에 고정적으로 설정되는 경향이 있다.
// fbdev_drv.c 에서 초기화한 afbc ctx 를 모두 동일하게 사용할 수 있도록 한다.
// 이는 afbc_sw_xxx 함수의 첫번째 인수를 모두 NULL 로 설정함으로써 의사 표시를 한다.
//
// 만약 테스트/기타 목적으로 다양한 afbc ctx 를 사용할 수 도 있다.
void afbc_sw_set_default_context(struct afbc_ctx* afbc_ctx)
{
    afbc_sw_check_error(!afbc_ctx, return, "null param\n");

    memcpy(&default_ctx, afbc_ctx, sizeof(default_ctx));

    afbc_sw_noti("afbc_sw.default_ctx.fmt=%s,version=%s\n",
                 afbc_sw_get_fbc_fmt_string(&default_ctx),
                 afbc_sw_get_version_string(&default_ctx));
}

// AFBC 버전에 따른 align 값을 획득한다.
static void afbc_sw_get_desc(struct afbc_ctx* ctx, int* x_align, int* y_align)
{
    INIT_CTX(ctx);

    if (ctx->version == AFBC_SW_VER_AFRC)
    {
        if (x_align) *x_align = AFRC_CU_PXL_SZ;

        if (y_align) *y_align = 1;
    }
    else if (ctx->version == AFBC_SW_VER_1_0)
    {
        if (x_align) *x_align = 16;

        if (y_align) *y_align = 16;
    }
    else // AFBC1.1
    {
        if (x_align) *x_align = 32;

        if (y_align) *y_align = 8;
    }
}

// AFBC 이미지의 payload 블럭 갯수를 x, y 뱡향별로 리턴한다.
//
static void afbc_sw_get_block_num(struct afbc_ctx* ctx, int w, int h, int* x_num, int* y_num)
{
    int x_align;
    int y_align;

    INIT_CTX(ctx);

    afbc_sw_get_desc(ctx, &x_align, &y_align);

    if (x_num) *x_num = ALIGN(w, x_align) / x_align;

    if (y_num) *y_num = ALIGN(h, y_align) / y_align;
}

// AFBC 이미지의 payload 블럭 갯수를 계산한다.
static int afbc_sw_get_afbc_total_block_num(struct afbc_ctx* ctx, int w, int h)
{
    int x_blk_num;
    int y_blk_num;

    INIT_CTX(ctx);

    afbc_sw_get_block_num(ctx, w, h, &x_blk_num, &y_blk_num);

    return x_blk_num * y_blk_num;
}

// AFBC header 크기를 리턴함.
//
// 1KB aligne 된 크기를 리턴함
// AFBC1.0, AFBC 1.1 에 따라 실제 크기는 틀리지만, 결국 align 된 크기를 사용하는것이 좋으므로,
// 메모리 할당 관점에서는 같은 크기가 됨
//
// (2021/12/15) http://clm.lge.com/issue/browse/SICDTV-10484
// framebuffer 를 사용하는 GPU DDK 에서 AFBC 1.1 크기로 계산된 버퍼를 넘어서 write 하는것이 목격됨
// afbc header, payload 계산할때는 최대 버퍼 크기로 처리하도록 함
//
// (2022/04/17) AFRC 는 헤더 정보가 없으므로 0 이다.
//
int afbc_sw_get_header_size(struct afbc_ctx* ctx, int w, int h)
{
    if (ctx)
    {
        if (ctx->version == AFBC_SW_VER_AFRC)
        {
            return 0;
        }
        else // AFBC
        {
            int number_block = afbc_sw_get_afbc_total_block_num(ctx, w, h);

            afbc_sw_debug("afbc%02x wxh=%dx%d => num_block=%d, header_size=%d\n",
                          ctx->version,
                          w, h,
                          number_block,
                          ALIGN(number_block * AFBC_HDR_BLK_SZ, AFBC_PREFERRED_BODY_ALIGN_BYTE));

            return ALIGN(number_block * AFBC_HDR_BLK_SZ, AFBC_PREFERRED_BODY_ALIGN_BYTE);
        }
    }
    else
    {
        int s0 = afbc_sw_get_header_size(&afbc_1_0_ctx, w, h);
        int s1 = afbc_sw_get_header_size(&afbc_1_1_ctx, w, h);
        int val = max(s0, s1);

        afbc_sw_debug("afbc1.0=%d(0x%08x), afbc1.1=%d(0x%08x) => max=%d(0x%08x)\n",
                      s0, s0, s1, s1, val, val);
        return val;
    }
}

// AFBC payload, 즉 header 를 제외한 실제 데이터 크기를 리턴
// 메모리 할당 관점에서의 크기임
//
//
// (2021/12/15) http://clm.lge.com/issue/browse/SICDTV-10484
// framebuffer 를 사용하는 GPU DDK 에서 AFBC 1.1 크기로 계산된 버퍼를 넘어서 write 하는것이 목격됨
// afbc header, payload 계산할때는 최대 버퍼 크기로 처리하도록 함
//
// (2022/04/27) AFRC 의 하나의 CU 가 4x4 픽셀 즉 16x4 (=64) byte 로 표현되는데, 각 라인은 CU 는 최종
//  단위 CU 크기 32Byte 로 압축된다. 따라서 stride 는 아래 계산식으로 구할 수 있다.
//  stride = (width * 4 / 64) * CU
//
int afbc_sw_get_payload_size(struct afbc_ctx* ctx, int w, int h)
{
    int width;
    int height;
    int x_align;
    int y_align;
    int payload_size;

    if (ctx)
    {
        afbc_sw_get_desc(ctx, &x_align, &y_align);

        width  = ALIGN(w, x_align);
        height = ALIGN(h, y_align);

        afbc_sw_debug("afbc%02x wxh=%dx%d => %dx%d. payload_size=%d\n",
                      ctx->version,
                      w, h,
                      width, height,
                      width * height * 4);

        if (ctx->version == AFBC_SW_VER_AFRC)
        {
            payload_size =  width * height * AFRC_CB_SZ / AFRC_CU_PXL_SZ;
        }
        else
        {
            payload_size =  width * height * 4;
        }

        afbc_sw_debug("fbc_fmt=%s,version=%s, wxh=%dx%d, payload_size=%d(0x%04x)\n",
                      afbc_sw_get_fbc_fmt_string(ctx),
                      afbc_sw_get_version_string(ctx),
                      w, h, payload_size, payload_size);
    }
    else
    {
        int s0 = afbc_sw_get_payload_size(&afbc_1_0_ctx, w, h);
        int s1 = afbc_sw_get_payload_size(&afbc_1_1_ctx, w, h);
        payload_size = max(s0, s1);

        afbc_sw_debug("afbc1.0=%d(0x%08x), afbc1.1=%d(0x%08x) => max=%d(0x%04x)\n",
                      s0, s0, s1, s1, payload_size, payload_size);
    }

    return payload_size;
}


int afbc_sw_get_image_size(struct afbc_ctx* ctx, int w, int h)
{
    int size =  afbc_sw_get_header_size(ctx, w, h) + afbc_sw_get_payload_size(ctx, w, h);

    size = ALIGN(size, PAGE_SIZE);

    afbc_sw_debug("wxh=%dx%d => image_size=%d(0x%08x)\n", w, h, size, size);

    return size;
}

// AFBC SW 연산을 수행하기 위한 관리용 framebuffer 객체를 생성
//
// AFBC 실제 이미지 버퍼의 할당은(hma_alloc 혹은 고정 주소값) 호출하는 측에서 담당해야 한다.
// 즉 이 함수는 단지 afbc_sw_fill, afbc_sw_transform 등과 같은 동작을 하기 위한 AFBC 이미지의
// 레이아웃 및 중요 사전 변수를 미리 계산하기 위한 목적으로 제공된다.
//
// width, height 와는 서로 상이한 AFBC 이미지를 묘사해야 하는 경우, header, payload 및 fb_size 를
// 실제 버퍼 크기 만큼 사전에 입력을 해주어야 한다.
// 예를 들어 afbc_sw_transform 함수는 타겟 이미지의 width, height 크기와 무관하게 소스 이미지의
// payload 를 모두 복사하기 때문에, 당연히 width, height 보다는 더 큰 AFBC 이미지의 메모리 형태를
// 알려주어야 한다.
//
// 만약 0 이 입력되는 경우에는 입력 width, height 에 따라 자동 계산하여 사용하도록 한다.
//
struct afbc_framebuffer* afbc_sw_alloc_framebuffer(struct afbc_ctx* ctx,
        phys_addr_t paddr, int w, int h, unsigned int header_size, unsigned int payload_size, unsigned int fb_size)
{
    struct afbc_framebuffer* fb = NULL;

    INIT_CTX(ctx);

    fb = vzalloc(sizeof(struct afbc_framebuffer));

    afbc_sw_check_error(!fb,
                        goto func_error,
                        "can't alloc %d\n", (int)sizeof(struct afbc_framebuffer));

    if (!header_size) header_size = afbc_sw_get_header_size(ctx, w, h);

    if (!payload_size) payload_size = afbc_sw_get_payload_size(ctx, w, h);

    if (!fb_size) fb_size = afbc_sw_get_image_size(ctx, w, h);

    fb->paddr = paddr;
    fb->w = w;
    fb->h = h;
    fb->header_size = header_size;
    fb->payload_size = payload_size;
    fb->fb_size = fb_size;

#ifdef AFBC_SW_USE_CAHCE_OP
    OS_OpenCacheMap(&fb->cmap, (ULONG)paddr, ALIGN(fb_size, PAGE_SIZE));
#else
    fb->vaddr = (unsigned char*)vmap_phys((phys_addr_t)paddr, ALIGN(fb_size, PAGE_SIZE));

    if (!fb->vaddr)
    {
        pr_err("can't vmap 0x%08x\n", paddr);
        goto func_error;
    }

#endif

    return fb;

func_error:
    afbc_sw_free_framebuffer(ctx, fb);

    return NULL;
}

void afbc_sw_free_framebuffer(struct afbc_ctx* ctx, struct afbc_framebuffer* fb)
{
    INIT_CTX(ctx);

    if (fb)
    {
#ifdef AFBC_SW_USE_CAHCE_OP
        OS_CloseCacheMap(&fb->cmap);
#else

        if (fb->vaddr)
        {
            vunmap_phys((void*)fb->vaddr);
        }

#endif

        vfree(fb);
    }
}

// 단순한 단일색 (투명색, 불/반투명 검정, 흰색 등) 으로 전체 AFBC 이미지를 채움
//
// AFBC 의 실제 데이터 포맷은 알 수 없으므로, 아래 함수는 afbc enc sw 및 GPU 등의
// 출력 결과를 덤프한후 패턴조사하는 방식으로 해석하여 구현하였다.
// 따라서 모든 색이 제대로 표현될지는 보장할 수 없다.
//
// SW 복잡도 감소, 필요 메모리양 감소를 위하여 0 번 payload 만 구성한 후에,
// 모든 header 가 0 번 payload 만 바라보도록 구현되었다.
//
// (노트) fill 만 사용되는 경우 AFBC 이미지 버퍼의 크기는 hedaer + 1KB 정도면 충분하다.
// (노트) 아래 코드는 그대로 boot loader 등에 사용되어 질 수 있다.
//
// (노트) AFBC 1.0 과 다르게 1.1 의 경우 1KB payload 에 2개의 압축된 color 표현 바이트열이
// 들어가 있다.
//
// (노트) 현재 이 함수는 AFBC 1.1 에서만 검증되었다.
// AFBC 1.0 사용되는 경우 약간의 코드 분기가 필요할 듯 하다.
//
static int afbc_sw_fill_afbc(struct afbc_ctx* ctx,
                             struct afbc_framebuffer* fb, unsigned int color)
{
    int i;
    int block_num;
    int payload_offset;
    struct afbc_header* header = NULL;
    struct afbc_payload* payload = NULL;

    unsigned char a, r, g, b;
    unsigned char* header_buf_ptr;
    unsigned char* payload_buf_ptr;

    int ret = RET_ERROR;

    INIT_CTX(ctx);

    afbc_sw_check_error(!fb, return RET_ERROR, "null param\n");

    afbc_sw_debug("afbc%02x 0x%08x %d %d 0x%08x\n",
                  ctx->version,
                  (unsigned int)fb->paddr,
                  fb->w, fb->h,
                  color);

    header = vzalloc(sizeof(struct afbc_header));
    payload = vzalloc(sizeof(struct afbc_payload));

    afbc_sw_check_error(!header || !payload,
                        goto func_exit,
                        "can't alloc. header=%p, payload=%p\n", header, payload);

    block_num = afbc_sw_get_afbc_total_block_num(ctx, fb->w, fb->h);
    payload_offset = ALIGN(fb->header_size, AFBC_PREFERRED_BODY_ALIGN_BYTE);

    // header 와 payload 데이터를 준비한다.
    a = (color >> 24) & 0xff;
    r = (color >> 16) & 0xff;
    g = (color >> 8) & 0xff;
    b = (color) & 0xff;

    afbc_sw_debug("argb=%02x,%02x,%02x,%02x\n", a, r, g, b);

    // opaque red/blue case study
    //
    // 00000000  40 fa 01 00 05 00 00 00  00 00 05 00 00 00 00 00  |@...............|
    // ...
    // 0001fa40  ff ef ff 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
    // 0001fa50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
    // ...
    // 0001fc40  ff ef ff 00 00 00 00 00  00 00 00 00 00 00 00 00  |................| (+512B)
    // 0001fc50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................| (+512B)
    // ...
    // ...
    //
    if (a == 0xff)
    {
        header->bytes[0] = 0x5;
        header->bytes[6] = 0x5;

        payload->bytes[0] = 0xff;
        payload->bytes[1] = 0xef;
        payload->bytes[2] = b;
        payload->bytes[3] = g;
        payload->bytes[4] = r;

        payload->bytes[512 + 0] = 0xff;
        payload->bytes[512 + 1] = 0xef;
        payload->bytes[512 + 2] = b;
        payload->bytes[512 + 3] = g;
        payload->bytes[512 + 4] = r;
    }
    // transparent red/blue case study
    //
    // 00000000  40 fa 01 00 06 00 00 00  00 00 06 00 00 00 00 00  |@...............|
    // ...
    // 0001fa40  ff ff ff 00 00 7f 00 00  00 00 00 00 00 00 00 00  |................|
    // 0001fa50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
    // ...
    // 0001fc40  ff ff ff 00 00 7f 00 00  00 00 00 00 00 00 00 00  |................| (+512B)
    // 0001fc50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................| (+512B)
    // ...
    // ...
    else
    {
        header->bytes[0] = 0x6;
        header->bytes[6] = 0x6;

        payload->bytes[0] = 0xff;
        payload->bytes[1] = 0xff;
        payload->bytes[2] = b;
        payload->bytes[3] = g;
        payload->bytes[4] = r;
        payload->bytes[5] = a;

        payload->bytes[6] = 0xff;
        payload->bytes[7] = 0xff;
        payload->bytes[8] = b;
        payload->bytes[9] = g;
        payload->bytes[10] = r;
        payload->bytes[11] = a;

        payload->bytes[512 + 0] = 0xff;
        payload->bytes[512 + 1] = 0xff;
        payload->bytes[512 + 2] = b;
        payload->bytes[512 + 3] = g;
        payload->bytes[512 + 4] = r;
        payload->bytes[512 + 5] = a;

        payload->bytes[512 + 6] = 0xff;
        payload->bytes[512 + 7] = 0xff;
        payload->bytes[512 + 8] = b;
        payload->bytes[512 + 9] = g;
        payload->bytes[512 + 10] = r;
        payload->bytes[512 + 11] = a;
    }

#ifdef AFBC_SW_USE_CAHCE_OP
    header_buf_ptr = (unsigned char*)fb->cmap.virt_addr;
    payload_buf_ptr = header_buf_ptr + payload_offset;
#else
    header_buf_ptr = (unsigned char*)fb->vaddr;
    payload_buf_ptr = header_buf_ptr + payload_offset;
#endif

    // abfc image 전체를 한번 깨끗하게 정리해 주어야 한다.
    // 이 함수를 memory clear 목적으로도 사용한다.
    memset(header_buf_ptr, 0x0, fb->fb_size);

    // 1개의 payload 만 복사하고, 모든 header 가 이를 가르키도록 조치한다.
#ifdef AFBC_FILL_SINGLE_LINE
    memcpy(payload_buf_ptr, payload, sizeof(struct afbc_payload));
#else

    for (i = 0; i < block_num; i++)
    {
        memcpy(payload_buf_ptr, payload, sizeof(struct afbc_payload));
        payload_buf_ptr += sizeof(struct afbc_payload);
    }

#endif

    // N 개의 header 를 복사/생성한다.
    for (i = 0; i < block_num; i++)
    {
#ifdef AFBC_FILL_SINGLE_LINE
        header->offset = payload_offset; /* use fixed payload offset */
#else
        header->offset = payload_offset + i * sizeof(struct afbc_payload);
#endif
        memcpy(header_buf_ptr, header, sizeof(struct afbc_header));

        header_buf_ptr += sizeof(struct afbc_header);
    }

#ifdef AFBC_SW_USE_CAHCE_OP
    OS_CleanCacheMap(&fb->cmap, 0x0, ALIGN(fb->header_size + fb->payload_size, PAGE_SIZE));
#endif

    ret = RET_OK;

func_exit:

    if (header) vfree(header);

    if (payload) vfree(payload);

    return ret;
}

// 가장 대표적인 color 에 대한 payload 데이터를 사용하여 fill() 함수를 구현하도록 한다.
// CU 크기인 32Byte 중 아래 데이터외 부분은 모두 0x00 이다.
static const unsigned char afrc_payload_data[][AFRC_CB_SZ] =
{
    {0xdf, 0xfd, 0xca, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, }, // black
    {0xdf, 0xfd, 0xca, 0x02, 0xe6, 0x9f, 0x7f, 0x01, 0x00, 0x00, }, // red
    {0xdf, 0xfd, 0xca, 0xfc, 0x03, 0x00, 0xff, 0x01, 0x00, 0x00, }, // green
    {0xdf, 0xfd, 0xca, 0x02, 0x26, 0xa0, 0x7f, 0x01, 0x00, 0x00, }, // blue
    {0xcf, 0xfd, 0xca, 0x04, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, }, // clear
};

static int afbc_sw_fill_afrc(struct afbc_ctx* ctx,
                             struct afbc_framebuffer* fb, unsigned int color)
{
    unsigned char afrc_payload[AFRC_CB_SZ];

    INIT_CTX(ctx);

    memset(afrc_payload, 0x0, AFRC_CB_SZ);

    switch (color)
    {
        case 0xff000000:  memcpy(afrc_payload, afrc_payload_data[0], AFRC_CB_SZ); break;

        case 0xffff0000:  memcpy(afrc_payload, afrc_payload_data[1], AFRC_CB_SZ); break;

        case 0xff00f000:  memcpy(afrc_payload, afrc_payload_data[2], AFRC_CB_SZ); break;

        case 0xff0000ff:  memcpy(afrc_payload, afrc_payload_data[3], AFRC_CB_SZ); break;

        default:          memcpy(afrc_payload, afrc_payload_data[4], AFRC_CB_SZ); break;
    }

    // not implemented yet

    return RET_OK;
}

int afbc_sw_fill(struct afbc_ctx* ctx,
                 struct afbc_framebuffer* fb, unsigned int color)
{
    INIT_CTX(ctx);

    if (ctx->version == AFBC_SW_VER_AFRC)
    {
        return afbc_sw_fill_afrc(ctx, fb, color);
    }
    else
    {
        return afbc_sw_fill_afbc(ctx, fb, color);
    }
}

// src_fb 내용을 dst_fb 에 복사한다.
//
// 어떠한 가공도 하지 않고, 단순히 메모리 전체를 복사할 뿐이다.
//
// (노트) 추후 일부 영역만 잘라내서 복사하는 부분을 지원할 수 있겠다.
//
int afbc_sw_blit(struct afbc_ctx* ctx,
                 struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb)
{
    INIT_CTX(ctx);

    if (src_fb->fb_size != dst_fb->fb_size)
    {
        afbc_sw_error("fb_size different %d != %d\n", src_fb->fb_size, dst_fb->fb_size);
        return RET_ERROR;
    }

    OS_InvalCacheMap(&src_fb->cmap, 0x0, src_fb->fb_size);

    memcpy(dst_fb->cmap.virt_addr, src_fb->cmap.virt_addr, src_fb->fb_size);

    OS_CleanCacheMap(&dst_fb->cmap, 0x0, dst_fb->fb_size);

    return RET_OK;
}

// 가령 1024x4320 T/B 이미지를 1920x2160 S/S (960x2160 L/R 로 구성) 이미지로 변환한다.
//
// <제약사항>
// 1. src_fb 와 dst_fb 은 같은 크기의 메모리 크기를 가져야 한다.
//    src_fb 의 payload 구조 전체를 dst_fb 로 복사해야 하기 때문이다.
//    이는 호출하는 쪽에서 보장해 주어야 한다.
//
// 2. AFBC payload 는 SW 에서 재성성할 수 수준의 복잡도를 넘어서기 때문에, 아래 함수는 실제
//    payload 는 그대로 유지한다.
//    header 의 내용도 그대로 유지하며, block 내에서의 위치만 조작한다.
//
// AFBC_TRANSFORM_TB_TO_SS 의 실제 구현 내용은 http://clm.lge.com/issue/browse/SICDTV-10314 참조
//
// 3. src_fb 의 width 는 dst_fb 의 width/2 보다 같거나 커야 한다.
//    src_fb 의 height 는 dst_fb 의 height * 2 와 같아야 한다.
//
static int afbc_sw_transform_tb2ss_afbc(struct afbc_ctx* ctx,
                                        struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb)
{
    UINT64 tk[2];

    int src_x_off;
    int src_x_off_blk_num;

    int src_x_blk_num;
    int src_y_blk_num;
    int dst_x_blk_num;
    int dst_y_blk_num;

    int src_fb_blk_num;

    void* src_fb_vaddr;
    void* dst_fb_vaddr;

    INIT_CTX(ctx);

    afbc_sw_check_error(src_fb->fb_size != dst_fb->fb_size,
                        return RET_ERROR,
                        "fb_size different %d != %d\n", src_fb->fb_size, dst_fb->fb_size);

    afbc_sw_check_error(src_fb->h != dst_fb->h * 2,
                        return RET_ERROR,
                        "not supported height %d != %d*2\n", src_fb->h, dst_fb->h);

    afbc_sw_check_error(src_fb->w < dst_fb->w / 2,
                        return RET_ERROR,
                        "not supported width %d < %d/2\n", src_fb->w, dst_fb->w);

    tk[0] = OS_GetUsecTicks();

    // src_fb 의 width 가 dst_fb

    // dst_surf 는 L/R 을 담고 있기 때문에 dst_surf.w/2 기준으로 offset 을 계산하자.
    src_x_off = (src_fb->w - (dst_fb->w / 2)) / 2;
    afbc_sw_get_block_num(ctx, src_x_off, 0, &src_x_off_blk_num, NULL);

    afbc_sw_get_block_num(ctx, src_fb->w, src_fb->h, &src_x_blk_num, &src_y_blk_num);
    afbc_sw_get_block_num(ctx, dst_fb->w, dst_fb->h, &dst_x_blk_num, &dst_y_blk_num);

    src_fb_blk_num = afbc_sw_get_afbc_total_block_num(ctx, src_fb->w, src_fb->h);

#ifdef AFBC_SW_USE_CAHCE_OP
    OS_InvalCacheMap(&src_fb->cmap, 0x0, src_fb->fb_size);

    src_fb_vaddr = src_fb->cmap.virt_addr;
    dst_fb_vaddr = dst_fb->cmap.virt_addr;
#else
    src_fb_vaddr = src_fb->vaddr;
    dst_fb_vaddr = dst_fb->vaddr;
#endif

    // src_fb 의 내용을 dst_fb 에 전체 복사한다.
    // payload 데이터의 위치, 내용을 통째로 복사하는 것이 핵심이다.
    memcpy(dst_fb_vaddr, src_fb_vaddr, src_fb->fb_size);

    // 이제 복사된 dst_cmap.virt_addr 를 대상으로 header 를 선택적으로 복사한다.
    {
        int i;

        unsigned char* dst_hdr;
        unsigned char* src0_hdr;
        unsigned char* src1_hdr;

        int src_line_bytes;
        int dst_line_bytes;

        src0_hdr = (unsigned char*)src_fb_vaddr + (src_x_off_blk_num * AFBC_HDR_BLK_SZ);
        src1_hdr = src0_hdr;
        src1_hdr += (src_fb_blk_num / 2) * AFBC_HDR_BLK_SZ;

        dst_hdr  = (unsigned char*)dst_fb_vaddr;

        src_line_bytes = src_x_blk_num * AFBC_HDR_BLK_SZ; // (32)*16B
        dst_line_bytes = (dst_x_blk_num / 2) * AFBC_HDR_BLK_SZ; // (60/2) * 16B

        for (i = 0; i < dst_y_blk_num; i++) /* 270 */
        {
            memcpy(dst_hdr, src0_hdr, dst_line_bytes);
            dst_hdr += dst_line_bytes;

            memcpy(dst_hdr, src1_hdr, dst_line_bytes);
            dst_hdr += dst_line_bytes;

            src0_hdr += src_line_bytes;
            src1_hdr += src_line_bytes;
        }
    }

#ifdef AFBC_SW_USE_CAHCE_OP
    OS_CleanCacheMap(&dst_fb->cmap, 0x0, dst_fb->fb_size);
#endif

    tk[1] = OS_GetUsecTicks();

    afbc_sw_debug("0x%08llx %dx%d -> 0x%08llx %dx%d, tick=%dus\n",
                  src_fb->paddr, src_fb->w, src_fb->h,
                  dst_fb->paddr, dst_fb->w, dst_fb->h,
                  (int)(tk[1] - tk[0]));

    return RET_OK;
}

static int afbc_sw_transform_tb2ss_afrc(struct afbc_ctx* ctx,
                                        struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb)
{
    // not implemented yet

    return RET_OK;
}

int afbc_sw_transform(struct afbc_ctx* ctx,
                      struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb, enum afbc_sw_transform_opt opt)
{
    int ret;

    INIT_CTX(ctx);

    switch (opt)
    {
        case AFBC_TRANSFORM_TB_TO_SS:
            if (ctx->version == AFBC_SW_VER_AFRC)
            {
                ret = afbc_sw_transform_tb2ss_afrc(ctx, src_fb, dst_fb);
            }
            else
            {
                ret = afbc_sw_transform_tb2ss_afbc(ctx, src_fb, dst_fb);
            }

            break;

        default:
            ret = RET_NOT_SUPPORTED;
            break;
    }

    return ret;
}

const char* afbc_sw_get_fbc_fmt_string(struct afbc_ctx* ctx)
{
    int i;
    int ntable = NELEMENTS(string_table);

    if (!ctx)
    {
        ctx = &default_ctx;
    }

    for (i = 0; i < ntable; i++)
    {
        if (ctx->version == string_table[i].version) return string_table[i].fmt_str;
    }

    return invalid_info.fmt_str;
}

const char* afbc_sw_get_version_string(struct afbc_ctx* ctx)
{
    int i;
    int ntable = NELEMENTS(string_table);

    if (!ctx)
    {
        ctx = &default_ctx;
    }

    for (i = 0; i < ntable; i++)
    {
        if (ctx->version == string_table[i].version) return string_table[i].version_str;
    }

    return invalid_info.version_str;
}

void afbc_sw_preinit(void)
{
    /* do nothing */
}

int afbc_sw_init(void)
{
    g_afbc_sw_debug_fd = DBG_OPEN("afbc_sw");

    if (g_afbc_sw_debug_fd < 0)
    {
        pr_err("[afbc_sw] can't open debug handle\n");
    }
    else
    {
        OS_DEBUG_EnableModule(g_afbc_sw_debug_fd);
        OS_DEBUG_EnableModuleByIndex(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED);
        OS_DEBUG_EnableModuleByIndex(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW);
        OS_DEBUG_EnableModuleByIndex(g_afbc_sw_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE);
    }

    afbc_sw_proc_init();

    return RET_OK;
}

void afbc_sw_cleanup(void)
{
    /* do nothing */
}

/*  ========================================================================================
    Implementation Group (proc & test)
    ========================================================================================*/
enum
{
    PROC_ID_CTX,
    PROC_ID_INFO,
    PROC_ID_OP_FILL,
    PROC_ID_MAX,
};

static OS_PROC_DESC_TABLE_T _g_gfx_device_proc_table[] =
{
    { "ctx", PROC_ID_INFO, OS_PROC_FLAG_READ },
    { "info", PROC_ID_INFO, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "op_fill", PROC_ID_OP_FILL,  OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { NULL, PROC_ID_MAX, 0 }
};

static struct afbc_ctx debug_ctx;
static int debug_img_w = 1920;
static int debug_img_h = 1080;

static int  afbc_sw_proc_read_func(unsigned int procId, char* buffer)
{
    int ret = 0;

    switch (procId)
    {
        case PROC_ID_CTX:
        {
            ret = snprintf(buffer, 256, "ctx.version=%s\n",
                           (debug_ctx.version == AFBC_SW_VER_1_0) ? "1.0" : "1.1");
        }
        break;

        case PROC_ID_OP_FILL:
        {
            ret = snprintf(buffer, 256, "<usage> paddr width height color afbc_ver\n");
        }
        break;

        case PROC_ID_INFO:
        {
            int header_size = afbc_sw_get_header_size(&debug_ctx, debug_img_w, debug_img_h);
            int payload_size = afbc_sw_get_payload_size(&debug_ctx, debug_img_w, debug_img_h);

            ret = snprintf(buffer, 256, "afbc%s %4dx%d hdr:%d img:%d\n",
                           (debug_ctx.version == AFBC_SW_VER_1_0) ? "1.0" : "1.1",
                           debug_img_w, debug_img_h,
                           header_size, header_size + payload_size);
        }
        break;

        default:
        {
            ret = snprintf(buffer, 256, "n/a\n");
        }
        break;
    }

    return ret;
}

static int afbc_sw_proc_write_func(unsigned int procId, char* command)
{
    switch (procId)
    {
        case PROC_ID_INFO:
        {
            unsigned int version;
            unsigned int width;
            unsigned int height;
            sscanf(command, " %x %d %d", &version, &debug_img_w, &debug_img_h);

            debug_img_w = width;
            debug_img_h = height;
            debug_ctx = afbc_sw_init_context((version == 0x10) ? AFBC_SW_VER_1_0 : AFBC_SW_VER_1_1);
        }
        break;

        case PROC_ID_OP_FILL:
        {
            unsigned int version;
            unsigned int paddr;
            unsigned int width;
            unsigned int height;
            unsigned int color;

            struct afbc_ctx ctx;
            struct afbc_framebuffer* fb;

            sscanf(command, "%x %d %d %x %x", &paddr, &width, &height, &color, &version);

            ctx = afbc_sw_init_context((version == 0x10) ? AFBC_SW_VER_1_0 : AFBC_SW_VER_1_1);

            fb = afbc_sw_alloc_framebuffer(&ctx, paddr, width, height, 0, 0, 0);

            if (fb)
            {
                afbc_sw_fill(&ctx, fb, color);
                afbc_sw_free_framebuffer(&ctx, fb);
            }
        }
        break;
    }

    return strlen(command);
}

void afbc_sw_proc_init(void)
{
    OS_PROC_CreateEntryEx("afbc_sw", _g_gfx_device_proc_table,
                          afbc_sw_proc_read_func,
                          afbc_sw_proc_write_func);

}
