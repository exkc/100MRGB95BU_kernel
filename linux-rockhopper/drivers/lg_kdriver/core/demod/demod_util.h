#ifndef __DEMOD_UTIL_H__
#define __DEMOD_UTIL_H__

#if defined(DEMOD_PLATFORM)
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#ifndef DEMOD_TAG
#define DEMOD_TAG ""
#endif
#define SPRINTF								dsa_sprintf

#define	DEMOD_ERROR(format, args...)		dsa_printf(LOG_ERR, DEMOD_TAG format, ##__VA_ARGS__)
#define DEMOD_WARN(format, args...)			dsa_printf(LOG_WARN, DEMOD_TAG format, ##__VA_ARGS__)
#define	DEMOD_NOTI(format, args...)			dsa_printf(LOG_DEF, DEMOD_TAG format, ##__VA_ARGS__)
#define	DEMOD_INFO(format, args...)			dsa_printf(LOG_INFO, DEMOD_TAG format, ##__VA_ARGS__)
#define DEMOD_DEBUG(format, args...)		dsa_printf(LOG_DBG, DEMOD_TAG format, ##__VA_ARGS__)
#define	DEMOD_TRACE(format, args...)		do { } while(0)
#define DEMOD_PRINT(format, args...)		dsa_printf(LOG_DBG, DEMOD_TAG format, ##__VA_ARGS__)

#define	DEMOD_MCU_PRINT(format, args...)	dsa_printf(LOG_INFO, DEMOD_TAG format, ##__VA_ARGS__)
#define	DEMOD_MCU_DEBUG(format, args...)	dsa_printf(LOG_DBG, DEMOD_TAG format, ##__VA_ARGS__)
#define	DEMOD_MCU_ERROR(format, args...)	dsa_printf(LOG_ERR, DEMOD_TAG format, ##__VA_ARGS__)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kernel.h>
#define SPRINTF								sprintf

/*
below definitions are implemented in demod_impl.h
#define	DEMOD_ERROR(format, args...)
#define DEMOD_WARN(format, args...)
#define	DEMOD_NOTI(format, args...)
#define	DEMOD_INFO(format, args...)
#define DEMOD_DEBUG(...)
#define	DEMOD_TRACE(format, args...)
#define DEMOD_PRINT(format, args...)

#define	DEMOD_MCU_PRINT(format, args...)
#define	DEMOD_MCU_DEBUG(format, args...)
#define	DEMOD_MCU_ERROR(format, args...)
*/
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <afxmt.h>
#include <Windows.h>

#ifndef DEMOD_TAG
#define DEMOD_TAG ""
#endif

#define SPRINTF(buf, format, ...)		sprintf_s(buf, 1024, format, __VA_ARGS__)

#define DEMOD_ERROR(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x74);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define DEMOD_WARN(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x75);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define DEMOD_NOTI(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0a);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define DEMOD_INFO(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0b);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define DEMOD_DEBUG(format, ...)		do { } while(0)
#define	DEMOD_TRACE(format, ...)		do { } while(0)

#define DEMOD_PRINT(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}

#define DEMOD_MCU_PRINT(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8f);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define	DEMOD_MCU_DEBUG(format, ...)	do { } while(0)

#define DEMOD_MCU_ERROR(format, ...)	{\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x84);\
	printf(DEMOD_TAG format, __VA_ARGS__);\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);\
}
#define wmb()
#define rmb()
#define dump_stack()
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif
#else
#include <linux/kernel.h>
#define SPRINTF								sprintf

#endif

#define IDX_TO_ADDR(idx)        ((idx) << 2)
#define ADDR_TO_IDX(addr)       ((addr) >> 2)
#define LEN_TO_WORD(blen)       ((blen + 3) >> 2)
#define WORD_TO_LEN(wlen)       ((wlen) << 2)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char * DEMOD_BYTE_TO_HEXSTR_r(char * out, int outlen, char * src, int srclen);
char * DEMOD_BYTE_TO_HEXSTR(char * arr, int len);
char * DEMOD_BYTE_TO_CHARSTR_r(char * out, int outlen, char * src, int srclen);
char * DEMOD_BYTE_TO_CHARSTR(char * arr, int len);

int DEMOD_DUMP_BYTE(char * dst, unsigned char * src, int size);
int DEMOD_DUMP_WORD(char * dst, unsigned int * wsrc, int size);

#define DEMOD_DBG_LOG_MAX	(4096)
#define DEMOD_DBG_MEM_MAX	(1024)

extern char sdbglog[DEMOD_DBG_LOG_MAX];

int DEMOD_Get_Debug_Level(char * dbgbuf);
int DEMOD_Set_Debug_Level(int enable);

int DEMOD_Get_Test(char * dbgbuf);
int DEMOD_Set_Test(int enable);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif //__DEMOD_DEBUG__
