/********************************************************************
    Filename:    Exception.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_EXCEPTION_H__
#define __UTILITY_EXCEPTION_H__

#include "tstring.h"

using Common::_tstring;

namespace Common
{
    class CException
    {
    public:
        CException();
        virtual ~CException();

        CException(int nCode, _tstring strMsg);
        CException(const CException& exception);
        const CException& operator = (const CException& exception);

        CException(int nCode, const TCHAR* pszFormat, ...);

    public:
        void SetMsg(_tstring strMsg);
        void SetCode(int nCode);

        const _tstring& GetMsg() const;
        int GetCode() const;

    protected:
        _tstring m_strMsg;          //异常文字描述信息
        int m_nCode;                //异常编号
    };
};

#endif // __UTILITY_EXCEPTION_H__
