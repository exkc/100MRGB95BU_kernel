#ifndef _CONFIG_H
#define _CONFIG_H

#define SYS_CRIT  0x0001
#define SYS_ERR   0x0002
#define SYS_WARN  0x0004
#define SYS_INFO  0x0008
#define DDR_CRIT  0x0010
#define DDR_ERR   0x0020
#define DDR_WARN  0x0040
#define DDR_INFO  0x0080

/* ddr configuration */
struct ddr_sys {
	uint32_t start;
};

typedef enum {
	MON_OFF = 0,
	MON_ON  = 1,
} monitor_t;

struct ddr_ctrl {
	monitor_t monitor;
};

typedef enum {
	DDR_SUCCESS      = 1,
	DDR_CAP_EXCEEDED = 2,
} traffic_t;

struct ddr_status {
	traffic_t traffic;
};

struct ddr_struct {
	/* ddr system */
	struct ddr_sys sys;
	/* ddr control */
	struct ddr_ctrl ctrl;
	struct ddr_status stat;
};

/* debug configuration */
typedef struct {
	uint16_t major;
	uint16_t minor;
} version_t;

typedef struct {
	uint16_t info;
	uint16_t debug;
} log_t;

struct ddr_debug {
	version_t ver;
	log_t log;
};

/* extern config */
extern struct ddr_struct *prev;
extern struct ddr_struct *curr;
extern struct ddr_struct *next;
extern struct ddr_debug *dbg;

#endif /* _CONFIG_H */
