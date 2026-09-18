#ifndef _PROC_H
#define _PROC_H

struct ddr_info {
	const char *size;
	const char *clock;
};

extern int ddr_cmd(char *);
extern int get_ddr_info(struct ddr_info *dev);
extern unsigned int strtoui(char *);

extern int init_ddr_proc(void);
extern void cleanup_ddr_proc(void);

#endif /* _PROC_H */
