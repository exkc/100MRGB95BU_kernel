
#define _GNU_SOURCE
#include <sys/ioctl.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <mali_kbase_ioctl.h>
#include <mali_base_kernel.h>
#include <mali_base_common_kernel.h>

#define fatal(...)		_fatal(__func__, __LINE__, __VA_ARGS__)
void _fatal (const char *func, int line, const char *fmt, ...)
{
    va_list ap;

    (void)fprintf (stderr, "%s.%d: ", func, line);

    va_start (ap, fmt);
    (void)vfprintf (stderr, fmt, ap);
    va_end (ap);

    (void)fprintf (stderr, "error %s(%d)\n", strerror (errno), errno);

    exit (1);
}

char *read_a_line (FILE * s)
{
	char *buf = NULL;
	unsigned int len = 4;
	int cur = 0;

	do
	{
		char *p;

		if (len < UINT_MAX - 4)
			len += 4;
		p = (char*)realloc (buf, len);
		if (!p)
			fatal("no mem. len %u\n", len);
		buf = p;

		p = fgets (buf + cur, len - cur, s);
		if (!p)
		{
			if (cur == 0)
			{
				free (buf);
				return NULL;
			}
			return buf;
		}

		//debug("got line \"%s\"\n", buf);

		cur += strlen (buf + cur);
		if (cur > 0 && (buf[cur - 1] == '\n' || buf[cur - 1] == '\r'))
		{
			do
			{
				buf[cur - 1] = 0;
				cur--;
			}
			while (cur > 0 && (buf[cur - 1] == '\n' || buf[cur - 1] == '\r'));

			return buf;
		}
	}
	while (1);
}

// not thread safe
char *line_file(const char *fname)
{
	static FILE *fd;
	static char *last;

	if (last)
	{
		free((void*)last);
		last = NULL;
	}

	if (fname)
	{
		if (fd)
			fclose(fd);

		fd = fopen(fname, "r");
		if (!fd)
			return NULL;
	}

	if (fd)
		last = read_a_line(fd);
	return last;
}

char *line_filef(const char *namef, ...)
{
	char *line;
	if (namef)
	{
		va_list ap;

		va_start(ap, namef);

		char *filename = NULL;
		int ret;
		ret = vasprintf(&filename, namef, ap);
		assert(ret > 0);

		va_end(ap);

		line = line_file(filename);
		free(filename);
	}
	else
		line = line_file(NULL);

	return line;
}

char *line_self(const char *fname)
{
	if (fname)
		return line_filef("/proc/self/%s", fname);
	else
		return line_file(NULL);
}

char *line_self_starts(const char *fname, const char *starts)
{
	size_t len = strlen(starts);
	for (char *l=line_self(fname); l; l=line_self(NULL))
		if (!strncmp(l, starts, len))
		{
			// skip starts string and space
			l += len;
			while(*l == ' ' || *l == '\t')
				l ++;
			return l;
		}
	return NULL;
}

int open_mali(void)
{
	int ret;

	int fd = open("/dev/mali0", O_RDWR);;
	assert(fd >= 0);

	struct kbase_ioctl_version_check version_check;
	memset(&version_check, 0, sizeof(version_check));

	ret = ioctl(fd, KBASE_IOCTL_VERSION_CHECK, &version_check);
	if (ret < 0)
		printf("VERSION_CHECK failed. %s\n", strerror(errno));
	assert(ret >= 0);
	printf("version %d.%d\n", version_check.major, version_check.minor);

	struct kbase_ioctl_set_flags flags;
	memset(&flags, 0, sizeof(flags));

	ret = ioctl(fd, KBASE_IOCTL_SET_FLAGS, &flags);
	if (ret < 0)
		printf("SET_FLAGS failed. %s\n", strerror(errno));
	assert(ret >= 0);

	printf("gpu kernel initialized\n");
	return fd;
}

int alloc(int fd, int pages)
{
	int ret;

	union kbase_ioctl_mem_alloc alloc;
	memset(&alloc, 0, sizeof(alloc));
	alloc.in.va_pages = pages;
	alloc.in.commit_pages = pages;
	alloc.in.flags = BASE_MEM_PROT_GPU_RD | BASE_MEM_PROT_CPU_WR;

	ret = ioctl(fd, KBASE_IOCTL_MEM_ALLOC, &alloc);
	if (ret < 0)
		printf("ALLOC failed. %s\n", strerror(errno));
	assert(ret >= 0);

	printf("gpu memory allocated. %d pages\n", pages);
	printf("flags  0x%016llx\n", alloc.out.flags);
	printf("gpu_va 0x%016llx\n", alloc.out.gpu_va);

	return 0;
}

int main(int argc, char **argv)
{
	int pid = (int)getpid();

	printf("pid %d\n", pid);
	printf("RssFile: %s\n", line_self_starts("status", "RssFile:"));
	printf("RssAnon: %s\n", line_self_starts("status", "RssAnon:"));
	printf("\n");

	int fd = open_mali();

	printf("RssFile: %s\n", line_self_starts("status", "RssFile:"));
	printf("RssAnon: %s\n", line_self_starts("status", "RssAnon:"));
	printf("gpu: %s\n", line_filef("/proc/gpu/%d", pid));
	printf("\n");

	alloc(fd, 1024);

	printf("RssFile: %s\n", line_self_starts("status", "RssFile:"));
	printf("RssAnon: %s\n", line_self_starts("status", "RssAnon:"));
	printf("gpu: %s\n", line_filef("/proc/gpu/%d", pid));

	return 0;
}

