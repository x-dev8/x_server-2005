#pragma once

#include<string>  
#include<cstdarg>  
#include<windows.h>
#include "logmgr.h"
//#include "log4cpp/log4cpp_logger.h"

// #ifdef _DEBUG
// #define MeSprintf_s sprintf_s
// #else
// #define MeSprintf_s MeSprintf
// #endif

#define MeSprintf_s MeSprintf
//算缓冲区长度
#define BufferSize(buffer,type)  sizeof(buffer)/sizeof(type) - 1

//失败处理函数，可以用于输入Log或者其他处理
typedef bool (*MeAssertFailProcFuncPtr)(
	const char* pcExpression,
	const char* pcFile,
	const char* pcFunction,
	const int iLine);

//失败处理之后如何记录相关信息
class MeAssertFail
{
public:
	static bool DefaultAssertFail(
		const char* pcExpression,
		const char* pcFile,
		const char* pcFunction,
		const int iLine);

	static bool SimpleAssertFail(
		const char* pcExpression,
		const char* pcFile,
		const char* pcFunction,
		const int iLine);

	static MeAssertFailProcFuncPtr ms_pfnNiAssertFailProc;
};


#define MEASSERTINLINE(boolean_expresion) \
	((boolean_expresion) ? true : \
	MeAssertFail::ms_pfnNiAssertFailProc( \
#boolean_expresion, __FILE__, __FUNCTION__, __LINE__))


#define MEASSERT(boolean_expresion) ((void)MEASSERTINLINE(boolean_expresion));


int MeSprintf(char* pcDest, size_t stDestSize, const char* pcFormat, ...);
int MeVsprintf(char* pcDest, size_t stDestSize, const char* pcFormat,
			   va_list kArgs);
int MeVsnprintf(char* pcDest, size_t stDestSize, size_t stCount,
				const char* pcFormat, va_list kArgs);

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define ME_TRUNCATE _TRUNCATE
#else //#if defined(_MSC_VER) && _MSC_VER >= 1400
#define ME_TRUNCATE ((size_t)-1)
#endif //#if defined(_MSC_VER) && _MSC_VER >= 1400


std::string   safeFormat(const   char*   fmt,  ...);