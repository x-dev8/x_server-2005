#include "Common.h"

std::string   safeFormat(const   char*   fmt,   ...)  
{  
	va_list   argptr;  
	va_start(argptr,   fmt);  
	int   bufsize   =   _vsnprintf(NULL,   0,   fmt,   argptr)   +   2;  
	char*   buf   =   new   char[bufsize];  
	_vsnprintf(buf,   bufsize,   fmt,   argptr);  
	std::string   s(buf);  
	delete[]   buf;      
	va_end(argptr);    
	return   s;  
}

MeAssertFailProcFuncPtr MeAssertFail::ms_pfnNiAssertFailProc = 
MeAssertFail::DefaultAssertFail;

bool MeAssertFail::DefaultAssertFail(
		const char* pcExpression,
		const char* pcFile,
		const char* pcFunction,
		const int iLine)
{
	char* pcCaption = "Assert Failed";
	char acString[512];
	MeSprintf(
		acString, 
		sizeof(acString), 
		"\n"
		"Assert Failed: %s\n\n"
		"File: %s\n"
		"Line: %d\n"
		"Function: %s\n",
		pcExpression,
		pcFile,
		iLine,
		pcFunction);

	//LOG_MESSAGE("Error.log",LOG_PRIORITY_ERROR,"Error Login:[%s]",acString);

	return false;

	/*
	fprintf(stderr, acString);

	int iButtonResult = MessageBox(
		NULL, 
		acString, 
		pcCaption, 
		MB_ABORTRETRYIGNORE);

	switch(iButtonResult)
	{
	case IDABORT:
		exit(EXIT_FAILURE);
	default:
	case IDRETRY:
		//NIDEBUGBREAK();
		return false;

	case IDIGNORE:
		return false;
	}
	*/
	
}

bool MeAssertFail::SimpleAssertFail(const char* pcExpression,const char* pcFile,
		                            const char* pcFunction,const int iLine)
{
	char acString[1024];
	MeSprintf(acString, 1024, "*** Assertion Failure***\n"
		"%s(%d) : Expression \"%s\"\n", pcFile, iLine, pcExpression);
	::OutputDebugString(acString);

	return false;
}

inline int MeSprintf(char* pcDest, size_t stDestSize, const char* pcFormat, ...)
{
	MEASSERT(pcFormat);

	va_list kArgs;
	va_start(kArgs, pcFormat);
	int iRet = MeVsprintf(pcDest, stDestSize, pcFormat, kArgs);
	va_end(kArgs);

	MEASSERT(iRet != -1); //当缓冲区越界的时候，输出错误日志
	//LOG_MESSAGE("Error.log",LOG_PRIORITY_ERROR,"缓冲区溢出:[%s]",acString);

	return iRet;
}

inline int MeVsprintf(char* pcDest, size_t stDestSize, const char* pcFormat,
			   va_list kArgs)
{
	return MeVsnprintf(pcDest, stDestSize, ME_TRUNCATE, pcFormat, kArgs);
}


inline int MeVsnprintf(char* pcDest, size_t stDestSize, size_t stCount,
					   const char* pcFormat, va_list kArgs)
{
	if (stDestSize == 0)
	{
		return 0;
	}

	MEASSERT(pcDest);
	MEASSERT(stCount < stDestSize || stCount == ME_TRUNCATE);
	MEASSERT(pcFormat);

	// Ensure that input buffer is cleared out.
	pcDest[0] = '\0';

	bool bTruncate = (stCount == ME_TRUNCATE);

#if _MSC_VER >= 1400
	int iRet = vsnprintf_s(pcDest, stDestSize, stCount, pcFormat, kArgs);
#else   // _MSC_VER >= 1400
	if (bTruncate)
	{
		stCount = stDestSize - 1;
	}
	int iRet = _vsnprintf(pcDest, stCount, pcFormat, kArgs);
#endif  // _MSC_VER >= 1400

	if (iRet == -1 && !bTruncate)
	{
		iRet = (int)stCount;
	}

#if _MSC_VER < 1400
	// Ensure that the string ends in a null character.
	if (iRet == -1)
	{
		pcDest[stDestSize - 1] = '\0';
	}
	else
	{
		pcDest[iRet] = '\0';
	}
#endif  // #if _MSC_VER < 1400

	return iRet;
}
