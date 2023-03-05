//获得精确的时间函数，毫秒 AND 微妙

#ifndef _H_CROSSLIB_MY_H_
#define _H_CROSSLIB_MY_H_

#ifdef __cplusplus
extern "C"{
#endif

//#include "../configtype.h"

#ifdef _MSC_VER
	signed __int64 high_millisecond_();
	signed __int64 high_microsecond_();
#else
	int64_t high_millisecond_();
	int64_t high_microsecond_();
#endif

/* get current millisecond time */
#define get_millisecond() high_millisecond_()

/* get current microsecond time */
#define get_microsecond() high_microsecond_()

/* sleep some millisecond */
void delay_delay (unsigned long millisecond);

#ifdef __cplusplus
}
#endif
#endif

