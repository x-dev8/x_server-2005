#include "Exception.h"
#include <stdarg.h>

using Common::CException;

CException::CException()
{
}

CException::~CException()
{
}

CException::CException(int nCode, _tstring strMsg):m_nCode(nCode)
{
    m_strMsg = strMsg;
}

CException::CException(const CException& exception):m_nCode(exception.GetCode())
{
    m_strMsg = exception.GetMsg();
}

const CException& CException::operator = (const CException& exception)
{
    m_nCode = exception.GetCode();
    m_strMsg = exception.GetMsg();
    return *this;
}

CException::CException(int nCode, const TCHAR* pszFormat, ...):m_nCode(nCode)
{
	va_list args;
	va_start(args, pszFormat);

#ifdef _UNICODE
    unsigned int nLength = _vscwprintf(pszFormat, args);
    m_strMsg.resize(nLength);
    _vsnwprintf_s(const_cast<wchar_t*>(m_strMsg.c_str()), _TRUNCATE, m_strMsg.length(), pszFormat, args);
#else
    unsigned int nLength = _vscprintf(pszFormat, args);
    m_strMsg.resize(nLength);
	_vsnprintf_s(const_cast<char*>(m_strMsg.c_str()), _TRUNCATE, m_strMsg.length(), pszFormat, args);
#endif

	va_end(args);	
}

void CException::SetMsg(_tstring strMsg)
{
    m_strMsg = strMsg;
}

void CException::SetCode(int nCode)
{
    m_nCode = nCode;
}

const _tstring& CException::GetMsg() const
{
    return m_strMsg;
}

int CException::GetCode() const
{
    return m_nCode;
}