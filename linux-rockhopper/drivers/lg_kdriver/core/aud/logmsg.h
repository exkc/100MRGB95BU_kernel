#ifndef _LOGMSG_H_
#define _LOGMSG_H_

extern void (*aud_log_print) (int proc_num, unsigned int ts, const char *string);
extern void aud_log_default (int proc_num, unsigned int ts, const char *string);

#endif
