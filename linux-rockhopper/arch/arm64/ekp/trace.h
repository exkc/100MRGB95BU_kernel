/* SPDX-License-Identifier: GPL-2.0 */
#if !defined(_TRACE_ARM64_EKP_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_ARM64_EKP_H

#include <linux/tracepoint.h>

#undef TRACE_SYSTEM
#define TRACE_SYSTEM ekp

#define ekp_cmd_symbolic(cmd)	\
	__print_symbolic(cmd,	\
		{ EKP_INIT, "EKP_INIT" }, \
		{ EKP_POST_INIT, "EKP_POST_INIT" }, \
		{ EKP_START, "EKP_START" }, \
		{ EKP_SET_PGD, "EKP_SET_PGD" }, \
		{ EKP_SET_P4D, "EKP_SET_P4D" }, \
		{ EKP_SET_PUD, "EKP_SET_PUD" }, \
		{ EKP_SET_PMD, "EKP_SET_PMD" }, \
		{ EKP_SET_PTE, "EKP_SET_PTE" }, \
		{ EKP_CRED_INIT, "EKP_CRED_INIT" }, \
		{ EKP_LKMP_PREPARE, "EKP_LKMP_PREPARE" }, \
		{ EKP_LKMP_ENABLE, "EKP_LKMP_ENABLE" }, \
		{ EKP_LKMP_AFTER_INIT, "EKP_LKMP_AFTER_INIT" }, \
		{ EKP_LKMP_DISABLE, "EKP_LKMP_DISABLE" }, \
		{ EKP_LKMP_DISABLE_INIT, "EKP_LKMP_DISABLE_INIT" }, \
		{ EKP_LKMP_DISABLE_CORE, "EKP_LKMP_DISABLE_CORE" }, \
		{ EKP_SET_ROMEM, "EKP_SET_ROMEM" }, \
		{ EKP_CLEAR_ROMEM, "EKP_CLEAR_ROMEM" }, \
		{ EKP_SLAB_SET_FP, "EKP_SLAB_SET_FP" }, \
		{ EKP_DBG_PUTS, "EKP_DBG_PUTS" }, \
		{ EKP_KEXEC_PREPARE, "EKP_KEXEC_PREPARE" }, \
		{ EKP_ARCH_CMPXCHG, "EKP_ARCH_CMPXCHG" }, \
		{ EKP_ARCH_XCHG, "EKP_ARCH_XCHG" }, \
		{ EKP_HIBERNATION, "EKP_HIBERNATION" }, \
		{ EKP_SUSPEND, "EKP_SUSPEND" })


TRACE_EVENT(ekp_cmd,

	TP_PROTO(unsigned long cmd, unsigned long arg1, unsigned long arg2,
		 unsigned long arg3, unsigned long arg4, unsigned long arg5,
		 unsigned long arg6, unsigned long r0, unsigned long r1,
		 unsigned long r2, unsigned long r3),

	TP_ARGS(cmd, arg1, arg2, arg3, arg4, arg5, arg6, r0, r1, r2, r3),

	TP_STRUCT__entry(
		__field(unsigned long,	cmd)
		__field(unsigned long,	arg1)
		__field(unsigned long,	arg2)
		__field(unsigned long,	arg3)
		__field(unsigned long,	arg4)
		__field(unsigned long,	arg5)
		__field(unsigned long,	arg6)
		__field(unsigned long,	r0)
		__field(unsigned long,	r1)
		__field(unsigned long,	r2)
		__field(unsigned long,	r3)
	),

	TP_fast_assign(
		__entry->cmd	= cmd;
		__entry->arg1	= arg1;
		__entry->arg2	= arg2;
		__entry->arg3	= arg3;
		__entry->arg4	= arg4;
		__entry->arg5	= arg5;
		__entry->arg6	= arg6;
		__entry->r0	= r0;
		__entry->r1	= r1;
		__entry->r2	= r2;
		__entry->r3	= r3;
	),

	TP_printk("%s: 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx / 0x%lx 0x%lx 0x%lx 0x%lx",
		  ekp_cmd_symbolic(__entry->cmd),
		  __entry->arg1, __entry->arg2, __entry->arg3,
		  __entry->arg4, __entry->arg5, __entry->arg6,
		  __entry->r0, __entry->r1, __entry->r2, __entry->r3)
);

TRACE_EVENT(ekp_perf_end,

	TP_PROTO(int id, u64 begin, u64 end, u64 delta),

	TP_ARGS(id, begin, end, delta),

	TP_STRUCT__entry(
		__field(int, id)
		__field(u64, begin)
		__field(u64, end)
		__field(u64, delta)
	),

	TP_fast_assign(
		__entry->id = id;
		__entry->begin = begin;
		__entry->end = end;
		__entry->delta = delta;
	),

	TP_printk("id=%d begin=%llu end=%llu delta=%llu",
		  __entry->id, __entry->begin, __entry->end, __entry->delta)
);

#endif /* _TRACE_ARM64_EKP_H */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .

#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE trace

/* This part must be outside protection */
#include <trace/define_trace.h>
