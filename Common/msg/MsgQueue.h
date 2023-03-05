/********************************************************************
    Filename:     MsgQueue.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MENETWORK_MSGQUEUE_H__
#define __MENETWORK_MSGQUEUE_H__

#pragma once

#include "MsgBase.h"
#include "Mutex.h"
#include "Memory_Pool.h"
//#include "EncDec.h"

typedef std::list<unsigned char*> MsgContainer;
typedef MsgContainer::iterator    ItrMsgContainer;

//class MsgPool
//{
//public:
////	MsgPool()
////	{
////
////	}
////	~MsgPool()
////	{
////		s_theMsgMemAllocator.DestroyMemPool();
////	}
////public:
//    static Common::TAllocator<unsigned char, MSGMAXSIZE, 200> s_theMsgMemAllocator;
//};

class MsgQueue : public CSemiAutoIntLock
{
public:    
    MsgQueue();
    ~MsgQueue();

    uint32 GetSize() { return m_iSize; }

    bool PushMsg( Msg* pMsg, uint8 encryptMode = msgflag_normal ); // ѹ����Ϸ��Ϣ
    bool PopMsg ( Msg* pMsg, uint32 stSize);                       // �������ڵ�MSGMaxSize��buffer
    bool PeekMsg( Msg* pMsg, uint32 stSize);                       // �������ڵ�MSGMaxSize��buffer
    //bool PopQueue( MsgContainer& list, bool add );

    //bool PushMsgThirdParty( MsgThirdParty* pMsg );               // ѹ���������Ϣ    
    //bool PopMsgThirdParty ( MsgThirdParty* pMsg, uint32 stSize); // �������ڵ�MSGMaxSize��buffer
    //bool PeekMsgThirdParty( MsgThirdParty* pMsg, uint32 stSize); // �������ڵ�MSGMaxSize��buffer

    void Clear();

protected:
    MsgContainer m_listAdditional;
    volatile uint32 m_iSize;
	/*MsgPool msgpool;*/
	static Common::TAllocator<unsigned char, MSGMAXSIZE, 200> s_theMsgMemAllocator;
};

class MsgQueueNotLock
{
public:    
    MsgQueueNotLock();
    ~MsgQueueNotLock();

    uint32 GetSize() { return m_iSize; }
    bool PushMsg( Msg* pMsg, uint8 encryptMode = msgflag_normal ); // ѹ����Ϸ��Ϣ

    bool PeekMsg( Msg* pMsg, uint32 stSize); // �������ڵ�MSGMaxSize��buffer
    bool PopMsg ( Msg* pMsg, uint32 stSize); // �������ڵ�MSGMaxSize��buffer
    //MsgQueueNotLock& operator =( MsgQueue& queue );
    //MsgQueueNotLock& operator +=( MsgQueue& queue );
    void Clear();

protected:
    MsgContainer m_listAdditional;
    volatile uint32 m_iSize;
	/*MsgPool msgpool;*/
	static Common::TAllocator<unsigned char, MSGMAXSIZE, 200> s_theMsgMemAllocator;
};

#endif // __MENETWORK_MSGQUEUE_H__