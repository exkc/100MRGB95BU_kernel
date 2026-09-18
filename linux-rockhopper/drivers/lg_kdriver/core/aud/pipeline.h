#ifndef _APIPELINE_H_
#define _APIPELINE_H_

#include <linux/kernel.h>

struct apipeline;

struct apipeline *apipeline_new (char *name, ...);
struct apipeline *apipeline_new2 (int preferred_proc, char *name, ...);
struct apipeline *apipeline_new_uid_proc (unsigned int uid, char *name, ...);
void apipeline_del (struct apipeline *pipe);

unsigned int apipeline_addf (struct apipeline *pipe, const char *impl_namef, ...);

unsigned int apipeline_head (struct apipeline *pipe);
unsigned int apipeline_tail (struct apipeline *pipe);

unsigned int apipeline_connect (struct apipeline *pipe_out, int port_out, struct apipeline *pipe_in, int port_in);
unsigned int apipeline_disconnect (struct apipeline *pipe, int port);

unsigned int apipeline_prepend_uid_port (struct apipeline *pipe, int port_in, unsigned int uid_out, int port_out);
unsigned int apipeline_prepend_uid (struct apipeline *pipe, unsigned int uid_out);

unsigned int apipeline_append_uid_port (struct apipeline *pipe, int port_out, unsigned int uid_in, int port_in);
unsigned int apipeline_append_uid (struct apipeline *pipe, unsigned int uid_in);

unsigned int apipeline_prependfv_port (struct apipeline *pipe, int port_in, int port_out, const char *impl_namef, va_list ap);
unsigned int apipeline_prependf_port (struct apipeline *pipe, int port_in, int port_out, const char *impl_namef, ...);
unsigned int apipeline_prependf (struct apipeline *pipe, const char *impl_namef, ...);

unsigned int apipeline_appendfv_port (struct apipeline *pipe, int port_out, int port_in, const char *impl_namef, va_list ap);
unsigned int apipeline_appendf_port (struct apipeline *pipe, int port_out, int port_in, const char *impl_namef, ...);
unsigned int apipeline_appendf (struct apipeline *pipe, const char *impl_namef, ...);
const char *apipeline_get_name (struct apipeline *pipe);
void apipeline_set_preferred_proc (struct apipeline *pipe, int proc);
#endif
