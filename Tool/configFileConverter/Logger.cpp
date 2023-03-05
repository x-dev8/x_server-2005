#include "stdafx.h"
#include <wtypes.h>
#include <iostream>

#include "Logger.h"


//日志文件名
const TCHAR LOG_FILE_NAME[] = _T("LogFile.txt");

CLogger &GetSysLogger()
{
	static CLogger instance(new CConsoleFile);
	return instance;
}

CLogger::CLogger(IFile *pFile):
m_pFile(pFile),
m_enable(false)
{
	Open();
}

CLogger::~CLogger(void)
{
	Close();
}

bool CLogger::Open()
{
	SetEnable(true);

	return true;
}

void CLogger::Close()
{
	if(m_pFile)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
}

void CLogger::OutputLine(const TCHAR* format_, ...)
{
	if(!m_enable)
		return;

	TCHAR szMsg[1024 * 2];
	va_list ap;
	va_start(ap, format_);
	szMsg[_vsntprintf(szMsg, sizeof(szMsg) - 1, format_, ap)] = 0;
	va_end(ap);
	size_t len = _tcslen(szMsg);
	szMsg[len] = _T('\n');
	szMsg[len + 1] = 0;
	
	LogString(szMsg);
}

void CLogger::LogString(const TCHAR* str_)
{
	if(!m_enable/* || NULL == m_pFile*/)
		return;

	m_pFile->Write(str_);
}

bool CConsoleFile::Write(const TCHAR *str_)
{
	std::cout << str_;
	return true;
}

bool CConsoleFile::Read(TCHAR *buf, UINT len)
{
	return false;
}
