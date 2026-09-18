
#undef TRACE_SYSTEM
#define TRACE_SYSTEM	dmflash

#if !defined(_TRACE_DMFLASH_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_DMFLASH_H

#include <linux/kernel.h>
#include <linux/bio.h>
#include <linux/blktrace_api.h>
#include <linux/tracepoint.h>

#define RWBS_LEN	8

DECLARE_EVENT_CLASS(dmflash_lbn_rwbs,

	TP_PROTO(u64 lbn, unsigned long bi_rw, unsigned int bi_size),

	TP_ARGS(lbn, bi_rw, bi_size),

	TP_STRUCT__entry(
		__field(u64,	lbn			)
		__array(char,	rwbs,	RWBS_LEN	)
	),

	TP_fast_assign(
		__entry->lbn	= lbn;
		blk_fill_rwbs(__entry->rwbs, bi_rw, bi_size);
	),

	TP_printk("lbn: %llu, rwbs: %s", __entry->lbn, __entry->rwbs)
);

DEFINE_EVENT(dmflash_lbn_rwbs, dmflash_flash_map_enter,

	TP_PROTO(u64 lbn, unsigned long bi_rw, unsigned int bi_size),

	TP_ARGS(lbn, bi_rw, bi_size)
);

DECLARE_EVENT_CLASS(dmflash_lbn,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn),

	TP_STRUCT__entry(
		__field(u64,	lbn	)
	),

	TP_fast_assign(
		__entry->lbn	= lbn;
	),

	TP_printk("lbn: %llu", __entry->lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_hash_digest_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_hash_insert_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_hash_insert_end,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_compress_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_decompress_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_read_on_buffer_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_read_on_buffer_end,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_read_on_disk_start,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

DEFINE_EVENT(dmflash_lbn, dmflash_read_on_disk_end,

	TP_PROTO(u64 lbn),

	TP_ARGS(lbn)
);

/* FIXME: HASH_LEN is defined temporarily for sha256 only */
#define HASH_LEN	32

DECLARE_EVENT_CLASS(dmflash_lbn_digest,

	TP_PROTO(u64 lbn, unsigned char *hash_val, unsigned int hash_len),

	TP_ARGS(lbn, hash_val, hash_len),

	TP_STRUCT__entry(
		__field(u64,		lbn			)
		__array(unsigned char,	hash_val, HASH_LEN	)
		__field(unsigned int,	hash_len		)
	),

	TP_fast_assign(
		__entry->lbn		= lbn;
		memcpy(__entry->hash_val, hash_val, hash_len);
		__entry->hash_len	= hash_len;
	),

	TP_printk("lbn: %llu, hash_val: %s",
		__entry->lbn,
		__print_hex(__entry->hash_val, __entry->hash_len))
);

DEFINE_EVENT(dmflash_lbn_digest, dmflash_hash_digest_end,

	TP_PROTO(u64 lbn, unsigned char *hash_val, unsigned int hash_len),

	TP_ARGS(lbn, hash_val, hash_len)
);

DECLARE_EVENT_CLASS(dmflash_lbn_compress,

	TP_PROTO(u64 lbn, unsigned int comp_len),

	TP_ARGS(lbn, comp_len),

	TP_STRUCT__entry(
		__field(u64,		lbn		)
		__field(unsigned int,	comp_len	)
	),

	TP_fast_assign(
		__entry->lbn		= lbn;
		__entry->comp_len	= comp_len;
	),

	TP_printk("lbn: %llu, comp_len: %u",
		__entry->lbn,
		__entry->comp_len)
);

DEFINE_EVENT(dmflash_lbn_compress, dmflash_compress_end,

	TP_PROTO(u64 lbn, unsigned int comp_len),

	TP_ARGS(lbn, comp_len)
);

DECLARE_EVENT_CLASS(dmflash_lbn_decompress,

	TP_PROTO(u64 lbn, u16 psg_size, unsigned int decomp_len),

	TP_ARGS(lbn, psg_size, decomp_len),

	TP_STRUCT__entry(
		__field(u64,		lbn		)
		__field(u16,		psg_size	)
		__field(unsigned int,	decomp_len	)
	),

	TP_fast_assign(
		__entry->lbn		= lbn;
		__entry->psg_size	= psg_size;
		__entry->decomp_len	= decomp_len;
	),

	TP_printk("lbn: %llu, psg_size: %hu, decomp_len: %u",
		__entry->lbn,
		__entry->psg_size,
		__entry->decomp_len)
);

DEFINE_EVENT(dmflash_lbn_decompress, dmflash_decompress_end,

	TP_PROTO(u64 lbn, u16 psg_size, unsigned int decomp_len),

	TP_ARGS(lbn, psg_size, decomp_len)
);

DECLARE_EVENT_CLASS(dmflash_lbn_psg,

	TP_PROTO(u64 lbn, u64 psg_start, u16 psg_size),

	TP_ARGS(lbn, psg_start, psg_size),

	TP_STRUCT__entry(
		__field(u64,	lbn		)
		__field(u64,	psg_start	)
		__field(u16,	psg_size	)
	),

	TP_fast_assign(
		__entry->lbn		= lbn;
		__entry->psg_start	= psg_start;
		__entry->psg_size	= psg_size;
	),

	TP_printk("lbn: %llu, psg_start: %llu, psg_size: %hu",
		__entry->lbn,
		__entry->psg_start,
		__entry->psg_size)
);

DEFINE_EVENT(dmflash_lbn_psg, dmflash_write_start,

	TP_PROTO(u64 lbn, u64 psg_start, u16 psg_size),

	TP_ARGS(lbn, psg_start, psg_size)
);

DECLARE_EVENT_CLASS(dmflash_psg,

	TP_PROTO(u64 psg_start, u16 psg_size),

	TP_ARGS(psg_start, psg_size),

	TP_STRUCT__entry(
		__field(u64,	psg_start	)
		__field(u16,	psg_size	)
	),

	TP_fast_assign(
		__entry->psg_start	= psg_start;
		__entry->psg_size	= psg_size;
	),

	TP_printk("psg_start: %llu, psg_size: %hu",
		__entry->psg_start,
		__entry->psg_size)
);

DEFINE_EVENT(dmflash_psg, dmflash_write_end,

	TP_PROTO(u64 psg_start, u16 psg_size),

	TP_ARGS(psg_start, psg_size)
);

DECLARE_EVENT_CLASS(dmflash_bio,

	TP_PROTO(struct bio *bio),

	TP_ARGS(bio),

	TP_STRUCT__entry(
		__field(dev_t,		dev			)
		__field(sector_t,	sector			)
		__field(unsigned int,	byte_size		)
		__array(char,		rwbs,	RWBS_LEN	)
	),

	TP_fast_assign(
		__entry->dev		= bio->bi_bdev->bd_dev;
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->byte_size	= bio->bi_iter.bi_size;
		blk_fill_rwbs(__entry->rwbs, bio->bi_rw, bio->bi_iter.bi_size);
	),

	TP_printk("%d,%d %s %llu + %u",
		MAJOR(__entry->dev), MINOR(__entry->dev),
		__entry->rwbs,
		(unsigned long long)__entry->sector,
		DIV_ROUND_UP(__entry->byte_size, 512))
);

DEFINE_EVENT(dmflash_bio, dmflash_wb_enter,

	TP_PROTO(struct bio *bio),

	TP_ARGS(bio)
);

DEFINE_EVENT(dmflash_bio, dmflash_write_make_request,

	TP_PROTO(struct bio *bio),

	TP_ARGS(bio)
);

DECLARE_EVENT_CLASS(dmflash_bio_plugging,

	TP_PROTO(unsigned int req_type, unsigned int nr_sector),

	TP_ARGS(req_type, nr_sector),

	TP_STRUCT__entry(
		__field(unsigned int,	req_type		)
		__field(unsigned int,	nr_sector		)
	),

	TP_fast_assign(
		__entry->req_type	= req_type;
		__entry->nr_sector	= nr_sector;
	),

	TP_printk("%u %u", __entry->req_type, __entry->nr_sector)
);

DEFINE_EVENT(dmflash_bio_plugging, dmflash_plug,

	TP_PROTO(unsigned int req_type, unsigned int nr_pending_sector),

	TP_ARGS(req_type, nr_pending_sector)
);

DEFINE_EVENT(dmflash_bio_plugging, dmflash_unplug,

	TP_PROTO(unsigned int req_type, unsigned int nr_sector),

	TP_ARGS(req_type, nr_sector)
);

#endif

#include <trace/define_trace.h>
