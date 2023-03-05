/*------------------------------------------------------------------------
Desc		: 日志系统。设计的本意是让该日志系统具有重定向功能。
Author		: zilong
Version		: 1.0
Date		: 2010-09-02
Revision	:
-------------------------------------------------------------------------*/

#pragma once
#include <tchar.h>
#include <WTypes.h>

#ifndef _LOG_OUTPUT_
#define _LOG_OUTPUT_
#endif


class CLogger;
CLogger &GetSysLogger();

#ifdef _LOG_OUTPUT_
#define Log_outputLine GetSysLogger().OutputLine
#else
#define Log_outputLine 
#endif

#ifdef _FUNCTION_SAFE_
#define SAFE_BEGIN	try{
// #define SAFE_END		}\
// 					catch(...){throw;}
#define SAFE_END		}\
					catch(...){\
								Log_outputLine(_T("File: %s, Line: %s, Function: %s"), \
													__FILE__, __LINE__, __FUNCTION__); \
								throw;}
#else
#define SAFE_BEGIN
#define SAFE_END
#endif

class IFile
{
public:
	virtual bool Write(const TCHAR *str_) = 0;
	virtual bool Read(TCHAR *buf, UINT len) = 0;
};

class CConsoleFile: public IFile
{
public:
	virtual bool Write(const TCHAR *str_);
	virtual bool Read(TCHAR *buf, UINT len);

};

class CLogger
{
public:
	void OutputLine(const TCHAR* format_, ...);

public:
	CLogger(IFile *pFile);
	~CLogger(void);

	void SetEnable(bool bEnable = true){m_enable = bEnable;}

	void LogString(const TCHAR* str_);

private:
	bool Open();
	void Close();

private:
	IFile *m_pFile;
	bool m_enable;
};



