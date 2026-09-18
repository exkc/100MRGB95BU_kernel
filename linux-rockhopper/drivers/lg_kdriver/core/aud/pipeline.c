
#include <linux/kernel.h>
#include <linux/slab.h>

#include "kaimc.h"
#include "module_list.h"
#include "pipeline.h"

#include "log.h"

logm_define (aud_pipeline, log_level_noti);
#define trace(fmt,args...)	logm_trace(aud_pipeline,fmt,##args)
#define debug(fmt,args...)	logm_debug(aud_pipeline,fmt,##args)
#define info(fmt,args...)	logm_info(aud_pipeline,fmt,##args)
#define noti(fmt,args...)	logm_noti(aud_pipeline,fmt,##args)
#define error(fmt,args...)	logm_error(aud_pipeline,fmt,##args)

struct element
{
    struct list_head list;

    unsigned int uid;
};

struct apipeline
{
    char *name;

    int preferred_proc;

    struct list_head element_list;
};

#define PIPE_NULL_CHECK(pipe, action) \
    if (pipe == NULL) \
    {\
        error ("pipe is null!!\n");\
        action;\
    }\

/* 일직선 방향의 audio signal processing pipeline 을 만든다.
 *
 * 하지만, 잘(?) 사용하면 일직선이 아닌 pipeline 도 사용할 수 있을 듯..
 */
struct apipeline *apipeline_new (char *name, ...)
{
    struct apipeline *pipe;
    va_list ap;

    pipe = kzalloc (sizeof (*pipe), GFP_KERNEL);
    if (!pipe)
    {
        error ("no mem\n");
        return NULL;
    }

    va_start (ap, name);
    pipe->name = kvasprintf (GFP_KERNEL, name, ap);
    pipe->preferred_proc = -1;
    va_end (ap);

    INIT_LIST_HEAD (&pipe->element_list);

    return pipe;
}

struct apipeline *apipeline_new2 (int preferred_proc, char *name, ...)
{
    struct apipeline *pipe;
    va_list ap;

    pipe = kzalloc (sizeof (*pipe), GFP_KERNEL);
    if (!pipe)
    {
        error ("no mem\n");
        return NULL;
    }

    va_start (ap, name);
    pipe->name = kvasprintf (GFP_KERNEL, name, ap);
    pipe->preferred_proc = preferred_proc;
    va_end (ap);

    INIT_LIST_HEAD (&pipe->element_list);

    return pipe;
}

struct apipeline *apipeline_new_uid_proc (unsigned int uid, char *name, ...)
{
    struct apipeline *pipe;
    va_list ap;

    pipe = kzalloc (sizeof (*pipe), GFP_KERNEL);
    if (!pipe)
    {
        error ("no mem\n");
        return NULL;
    }

    va_start (ap, name);
    pipe->name = kvasprintf (GFP_KERNEL, name, ap);
    pipe->preferred_proc = AUD_MODLIST_PROC (uid);
    va_end (ap);

    INIT_LIST_HEAD (&pipe->element_list);

    return pipe;
}

void apipeline_del (struct apipeline *pipe)
{
    struct element *e, *next;

    PIPE_NULL_CHECK (pipe, return);

    list_for_each_entry_safe (e, next, &pipe->element_list, list)
    {
        aimc_module_destroy (e->uid);
        list_del (&e->list);
        kfree (e);
    }

    kfree (pipe->name);
    kfree (pipe);
}

static unsigned int add (struct apipeline *pipe, unsigned int uid, bool at_tail)
{
    struct element *e;

    PIPE_NULL_CHECK (pipe, return 0);

    list_for_each_entry (e, &pipe->element_list, list)
    {
        if (e->uid == uid)
            return 0;
    }

    e = kzalloc (sizeof (*e), GFP_KERNEL);
    if (!e)
    {
        error ("%s: no mem for 0x%08x.\n", pipe->name, uid);
        return 0;
    }

    e->uid = uid;
    if (at_tail)
        list_add_tail (&e->list, &pipe->element_list);
    else
        list_add (&e->list, &pipe->element_list);

    return uid;
}

static unsigned int addfv (struct apipeline *pipe, int preferred_proc, bool at_tail,
    const char *impl_namef, va_list ap)
{
    char *name;
    unsigned int uid;

    PIPE_NULL_CHECK (pipe, return 0);

    name = kvasprintf (GFP_KERNEL, impl_namef, ap);
    if (!name)
    {
        error ("%s: no mem\n", pipe->name);
        return 0;
    }

    uid = aimc_module_create (name, preferred_proc);
    if (!uid)
    {
        if (preferred_proc < 0)
        {
            error ("can't find module %s", name);
            goto exit;
        }
        else
            uid = aimc_module_create (name, -1);
    }

    if (uid)
        add (pipe, uid, at_tail);

  exit:
    kfree (name);

    return uid;
}

/* printf(impl_namef, ...) 이름의 implement 를 instantiation 하여 pipeline 에
 * 추가한다. 추가된 instance 는 연결되지 않은 상태이며, aimc_module_connect()
 * 함수를 이용해 연결해야 한다.
 */
unsigned int apipeline_addf (struct apipeline *pipe, const char *impl_namef, ...)
{
    unsigned int uid;
    va_list ap;

    PIPE_NULL_CHECK (pipe, return 0);

    va_start (ap, impl_namef);
    uid = addfv (pipe, pipe->preferred_proc, false, impl_namef, ap);
    va_end (ap);

    return uid;
}

/* pipeline 의 제일 처음 instance 의 uid 를 return 한다.
 */
unsigned int apipeline_head (struct apipeline *pipe)
{
    struct element *e;

    PIPE_NULL_CHECK (pipe, return 0);

    if (list_empty (&pipe->element_list))
        return 0;

    e = list_first_entry (&pipe->element_list, struct element, list);
    return e->uid;
}

/* pipeline 의 제일 마지막 instance 의 uid 를 return 한다.
 */
unsigned int apipeline_tail (struct apipeline *pipe)
{
    struct element *e;

    PIPE_NULL_CHECK (pipe, return 0);

    if (list_empty (&pipe->element_list))
        return 0;

    e = list_last_entry (&pipe->element_list, struct element, list);
    return e->uid;
}

/* pipeline 끼리 연결한다.
 */
unsigned int apipeline_connect (struct apipeline *pipe_out, int port_out, struct apipeline *pipe_in,
    int port_in)
{
    int uid_in, uid_out;

    uid_out = apipeline_tail (pipe_out);
    uid_in = apipeline_head (pipe_in);

    if (!uid_in || !uid_out)
    {
        error ("error in get uid of  out(%d) or in(%d)", uid_out, uid_in);
        return -1;
    }

    return aimc_module_connect (uid_out, port_out, uid_in, port_in);
}


/* pipeline 연결을 해제한다. ( input port 을 가진 pipeline 을 넣는다. )
 */
unsigned int apipeline_disconnect (struct apipeline *pipe, int port)
{
    int uid;

    uid = apipeline_head (pipe);

    if (!uid)
    {
        error ("error in get uid (%d)", uid);
        return -1;
    }

    return aimc_module_disconnect_input (uid, port);
}

/* pipeline 의 제일 첫 instance 에 uid 를 연결한다.
 */
unsigned int apipeline_prepend_uid_port (struct apipeline *pipe, int port_in, unsigned int uid_out,
    int port_out)
{
    unsigned int uid_in = apipeline_head (pipe);

    if (uid_in)
        aimc_module_connect (uid_out, port_out, uid_in, port_in);

    add (pipe, uid_out, false);

    return uid_out;
}

unsigned int apipeline_prepend_uid (struct apipeline *pipe, unsigned int uid_out)
{
    return apipeline_prepend_uid_port (pipe, 0, uid_out, 0);
}

unsigned int apipeline_append_uid_port (struct apipeline *pipe, int port_out, unsigned int uid_in,
    int port_in)
{
    unsigned int uid_out = apipeline_tail (pipe);

    if (uid_out)
        aimc_module_connect (uid_out, port_out, uid_in, port_in);

    add (pipe, uid_in, true);

    return uid_in;
}

unsigned int apipeline_append_uid (struct apipeline *pipe, unsigned int uid_in)
{
    return apipeline_append_uid_port (pipe, 0, uid_in, 0);
}

/* pipeline 제일 처음에 instance 하나 연결하여 추가한다.
 */
unsigned int apipeline_prependfv_port (struct apipeline *pipe, int port_in, int port_out,
    const char *impl_namef, va_list ap)
{
    unsigned int uid_out, uid_in;

    PIPE_NULL_CHECK (pipe, return 0);

    uid_in = apipeline_head (pipe);
    uid_out =
        addfv (pipe, uid_in ? AUD_MODLIST_PROC (uid_in) : pipe->preferred_proc, false, impl_namef,
        ap);

    if (uid_in)
        aimc_module_connect (uid_out, port_out, uid_in, port_in);

    return uid_out;
}

unsigned int apipeline_prependf_port (struct apipeline *pipe, int port_in, int port_out,
    const char *impl_namef, ...)
{
    unsigned int uid_out;
    va_list ap;

    va_start (ap, impl_namef);
    uid_out = apipeline_prependfv_port (pipe, port_in, port_out, impl_namef, ap);
    va_end (ap);

    return uid_out;
}

unsigned int apipeline_prependf (struct apipeline *pipe, const char *impl_namef, ...)
{
    unsigned int uid_out;
    va_list ap;

    va_start (ap, impl_namef);
    uid_out = apipeline_prependfv_port (pipe, 0, 0, impl_namef, ap);
    va_end (ap);

    return uid_out;
}

/* pipeline 제일 마지막에 instance 를 연결하여 추가한다.
 */
unsigned int apipeline_appendfv_port (struct apipeline *pipe, int port_out, int port_in,
    const char *impl_namef, va_list ap)
{
    unsigned int uid_out, uid_in;

    PIPE_NULL_CHECK (pipe, return 0);

    uid_out = apipeline_tail (pipe);
    uid_in =
        addfv (pipe, uid_out ? AUD_MODLIST_PROC (uid_out) : pipe->preferred_proc, true, impl_namef,
        ap);

    if (uid_out)
        aimc_module_connect (uid_out, port_out, uid_in, port_in);

    return uid_in;
}

unsigned int apipeline_appendf_port (struct apipeline *pipe, int port_out, int port_in,
    const char *impl_namef, ...)
{
    unsigned int uid_in;
    va_list ap;

    va_start (ap, impl_namef);
    uid_in = apipeline_appendfv_port (pipe, port_out, port_in, impl_namef, ap);
    va_end (ap);

    return uid_in;
}

unsigned int apipeline_appendf (struct apipeline *pipe, const char *impl_namef, ...)
{
    unsigned int uid_in;
    va_list ap;

    va_start (ap, impl_namef);
    uid_in = apipeline_appendfv_port (pipe, 0, 0, impl_namef, ap);
    va_end (ap);

    return uid_in;
}

/* pipeline 의 이름을 얻어 온다.
 */
const char *apipeline_get_name (struct apipeline *pipe)
{
    if (pipe)
        return (const char *) pipe->name;

    return NULL;
}

void apipeline_set_preferred_proc (struct apipeline *pipe, int proc)
{
    PIPE_NULL_CHECK (pipe, return);

    pipe->preferred_proc = proc;
}
