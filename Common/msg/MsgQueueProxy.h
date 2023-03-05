/********************************************************************
    Filename:    MsgQueueProxy.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MENETWORK_MSGQUEUEPROXY_H__
#define __MENETWORK_MSGQUEUEPROXY_H__

#pragma once

#include "MeRTLibs.h"
#include "MsgQueue.h"

class CShareFlagVolatile
{ //简单互斥，同一线程也不可重入 【不是递归锁】
public:
    CShareFlagVolatile()
    {
        m_lShareFlag = 0;
    }

    void Lock()
    {
        while( m_lShareFlag != 0 )
        {
            Sleep( 1 );
        }
        InterlockedIncrement( &m_lShareFlag );
    }
    void Unlock()
    {
        if( m_lShareFlag <= 0 )
            return;
        InterlockedDecrement( &m_lShareFlag );
    }    
private:
    volatile long    m_lShareFlag;
};

class CShareFlag
{
public:
    CShareFlag()
    {        
        m_hEvent = 0;
        m_hEvent = CreateEvent( NULL,FALSE,TRUE,NULL );
    }
    ~CShareFlag()
    {
        if( m_hEvent )
            CloseHandle( m_hEvent );
    }

    void Lock()
    {
        if( m_hEvent )
            WaitForSingleObject( m_hEvent,INFINITE );        
        else
            m_volatile.Lock();
    }

    void Unlock()
    {
        if( m_hEvent )
            SetEvent( m_hEvent );
        else
            m_volatile.Unlock();
    }    
private:
    HANDLE               m_hEvent;
    CShareFlagVolatile m_volatile;
};

//////////////////////////////////////////////////////////////////////////
template <const DWORD t_dwSize, class queueType = MsgQueue>
class MeMsgQueueProxy
{
public:
    MeMsgQueueProxy()
    {
        m_pQueue   = 0;
        m_szBuf    = 0;
        m_nBufSize = 0;
    }

    unsigned int GetSize() const
    {
        if (!m_pQueue)
        { return 0; }

        return m_pQueue->GetSize();
    }

    void Init(queueType* pQueue, char* szBuf, int nBufSize)
    {
        m_pQueue   = pQueue;
        m_szBuf    = szBuf;
        m_nBufSize = nBufSize;
    }    

    void* GetBuffer(int nSize)
    {
        if (nSize <= m_nBufSize)
        { return m_szBuf; }
        return 0;
    }

    bool PopMsg(char* szBuf)
    {
        if (!m_pQueue)
        { return false; }

        return m_pQueue->PopMsg((Msg*)szBuf, MSGMAXSIZE);
    }

    bool PopMsgThirdParty(char* szBuf)
    {
        if (!m_pQueue)
        { return false; }

        return m_pQueue->PopMsgThirdParty((MsgThirdParty*)szBuf, MSGMAXSIZE);
    }

    bool PushMsg( Msg* pMsg, uint8 encryptMode )
    {
        if (!m_pQueue)
        { return false; }

        return m_pQueue->PushMsg( pMsg, encryptMode );
    }                                             
                                                  
    bool PushMsgThirdParty(MsgThirdParty* pMsg)   
    {                                             
        if (!m_pQueue)                            
            return false;                         
                                                  
        return m_pQueue->PushMsgThirdParty(pMsg); 
    }                                             
                                                  
    queueType* GetQueue() { return m_pQueue;}      

private:
    queueType* m_pQueue;
    char*      m_szBuf;
    int        m_nBufSize;
};

const DWORD const_iCWMQMsgBufSize = 500*50;
typedef MeMsgQueueProxy<const_iCWMQMsgBufSize> MessageQueueProxy;
typedef MeMsgQueueProxy<const_iCWMQMsgBufSize,MsgQueueNotLock> MessageQueueProxyEx;

#endif // __MENETWORK_MSGQUEUEPROXY_H__
