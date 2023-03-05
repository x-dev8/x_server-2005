/********************************************************************
    Filename:     Mutex.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_MUTEX_H__
#define __UTILITY_MUTEX_H__

#pragma once

#include "MeRTLibs.h"
#include "Helper.h"

//线程锁基类
class _CCriticalSectionImp
{
public:
    virtual ~_CCriticalSectionImp(){};

//确保此类只能作为基类使用
protected:
    _CCriticalSectionImp(){};

protected:
    CRITICAL_SECTION m_csAccess;
};

class CSALocker;
class CSemiAutoIntLock : public _CCriticalSectionImp
{
public:
    CSemiAutoIntLock() 
    {
        InitializeCriticalSection(&m_csAccess);
    }
    virtual ~CSemiAutoIntLock() 
    {
        DeleteCriticalSection(&m_csAccess);
    }

protected:
    friend CSALocker;
};

//半自动线程锁 (需要锁定先需要派生自 CSemiAutoIntLock, 然后使用 CSALocker 锁定m_csAccess;)
class CSALocker
{
public:
    explicit CSALocker(CSemiAutoIntLock* plock, DWORD dwTimeOut = 0, const char* szNote = NULL) : m_pcsAccess(NULL)
    {
        if (plock != NULL)
        {
            DWORD dwStartTime = 0;

            if (dwTimeOut > 0 && szNote != NULL)
            {
                dwStartTime = HQ_TimeGetTime();
            }

            m_pcsAccess = &plock->m_csAccess;
            EnterCriticalSection(m_pcsAccess);

            if (dwTimeOut > 0 && szNote != NULL)
            {
                DWORD dwUseTime = HQ_TimeGetTime() - dwStartTime;
                if (dwUseTime > dwTimeOut)
                {
                    DebugLogout("%s 进入锁定时间 %d 毫秒，超出限定 %d 毫秒", szNote, dwUseTime, dwTimeOut);
                }
            }
        }
    }

    explicit CSALocker(CSemiAutoIntLock& lock, DWORD dwTimeOut = 0, const char* szNote = NULL) : m_pcsAccess(NULL)
    {

        DWORD dwStartTime = 0;

        if (dwTimeOut > 0 && szNote != NULL)
        {
            dwStartTime = HQ_TimeGetTime();
        }

        m_pcsAccess = &lock.m_csAccess;
        EnterCriticalSection(m_pcsAccess);

        if (dwTimeOut > 0 && szNote != NULL)
        {
            DWORD dwUseTime = HQ_TimeGetTime() - dwStartTime;
            if (dwUseTime > dwTimeOut)
            {
                DebugLogout("%s 进入锁定时间 %d 毫秒，超出限定 %d 毫秒", szNote, dwUseTime, dwTimeOut);
            }
        }
    }

    virtual ~CSALocker()
    {
        if (m_pcsAccess != NULL)
        {
            LeaveCriticalSection(m_pcsAccess);
        }
    }

private:
    LPCRITICAL_SECTION m_pcsAccess;

private:
    CSALocker();
    CSALocker(const CSALocker&);
    CSALocker& operator = (const CSALocker&);
};


//手动线程锁 (需要锁定/解锁时需要手动调用Lock和Unlock)
class CIntLock : public _CCriticalSectionImp
{
public:
    CIntLock(){ InitializeCriticalSection(&m_csAccess); }
    virtual ~CIntLock(){ DeleteCriticalSection(&m_csAccess); }

public:
    void Lock(){ EnterCriticalSection(&m_csAccess); }
    void Unlock(){ LeaveCriticalSection(&m_csAccess); }

private:
    CIntLock(const CIntLock&){ InitializeCriticalSection(&m_csAccess); } 
    CIntLock operator = (const CIntLock&) { return *this; }
};

#endif // __UTILITY_MUTEX_H__
