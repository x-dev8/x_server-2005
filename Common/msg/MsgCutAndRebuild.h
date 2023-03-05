/********************************************************************
    Filename:    MsgCutAndRebuild.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MENETWORK_MSGCUTANGREBUILD_H__
#define __MENETWORK_MSGCUTANGREBUILD_H__

#pragma once

#include "MsgBase.h"
#include "FuncPerformanceLog.h"
#include "NetEventInterface.h"

#define MSGCANCUTMAXSIZE (1024*1024) // 最大的了，不能再大了

enum ERebuilderRet
{
    REBUILDERCUT_NOTENOUGHCHILD,
    REBUILDERCUT_CRITICALERROR,
    REBUILDERCUT_SUCC,
    REBUILDERCUT_SKIP,
    REBUILDERCUT_NEEDNOTCUT,
};

#define MSGTYPE_CHILDBEGIN CUT_MSG_CHILDBEGIN
#define MSGTYPE_CHILD CUT_MSG_CHILD

template <class MsgQueue>
int CutMsg( MsgQueue* pQueue, Msg* pMsg, uint8 encryptMode, int* piRealMsgSize = 0)
{
    if ( pMsg->header.stLength < MSGMAXSIZE )
    { return REBUILDERCUT_NEEDNOTCUT; }

    int iReadPos = 0;

    MsgChild      child;
    MsgChildBegin begin;

    char *szData = (char*)pMsg;
    int iDataLeft = 0;

    // 包头Id
    child.header.stID = pMsg->header.stID;
    begin.header.stID = pMsg->header.stID;

    begin.nMsgSize      = pMsg->header.stLength;
    begin.stChildMsgNum = (begin.nMsgSize + MsgChild::CHILD_BUFSIZE - 1) / MsgChild::CHILD_BUFSIZE;

    // 在这里锁定，确保插入顺序不会乱
    CSALocker locker( pQueue->GetQueue() );

    if( !pQueue->PushMsg( &begin, encryptMode ) )
    { return REBUILDERCUT_CRITICALERROR; }

    iDataLeft = begin.nMsgSize;

    for( int i=0; i<begin.stChildMsgNum; ++i )
    {
        if( iDataLeft > MsgChild::CHILD_BUFSIZE )
        { child.stBufSize = MsgChild::CHILD_BUFSIZE; }
        else
        { child.stBufSize = iDataLeft; }

        memcpy(child.szBuf,szData,child.stBufSize);

        if ( !pQueue->PushMsg( &child, encryptMode) )
        { return REBUILDERCUT_CRITICALERROR; }

        iDataLeft -= child.stBufSize;
        szData += child.stBufSize;
    }

    if( piRealMsgSize )
    {
        //实际需要发送的消息
        *piRealMsgSize = begin.stChildMsgNum * sizeof(MsgChild);
        *piRealMsgSize += sizeof(begin);
    }
    return REBUILDERCUT_SUCC;
}

template <class MsgQueue>
int CutThirdPartyMsg( MsgQueue* pQueue, MsgThirdParty* pMsg, int* piRealMsgSize = 0)
{
    if ( pMsg->length < MSGMAXSIZE)
    { return REBUILDERCUT_NEEDNOTCUT; }

    int iReadPos = 0;

    MsgThirdPartyChildBegin begin;
    MsgThirdPartyChild      child;
    
    char* szData  = (char*)pMsg;
    int iDataLeft = 0;

    //child.header.stID = pMsg->header.stID;
    //begin.header.stID = pMsg->header.stID;

    begin.nMsgSize      = pMsg->length;
    begin.stChildMsgNum = (begin.nMsgSize + MsgChild::CHILD_BUFSIZE - 1) / MsgChild::CHILD_BUFSIZE;

    // 在这里锁定，确保插入顺序不会乱
    CSALocker locker( pQueue->GetQueue() );

    if( !pQueue->PushMsgThirdParty( &begin ) )
    { return REBUILDERCUT_CRITICALERROR; }

    iDataLeft = begin.nMsgSize;
    for( int i = 0 ; i < begin.stChildMsgNum ; i ++ )
    {
        if( iDataLeft > MsgChild::CHILD_BUFSIZE )
        { child.stBufSize = MsgChild::CHILD_BUFSIZE; }
        else
        { child.stBufSize = iDataLeft; }

        memcpy(child.szBuf,szData,child.stBufSize);

        if (!pQueue->PushMsgThirdParty(&child))
        { return REBUILDERCUT_CRITICALERROR; }

        iDataLeft -= child.stBufSize;
        szData += child.stBufSize;
    }
    if( piRealMsgSize )
    {
        //实际需要发送的消息
        *piRealMsgSize = begin.stChildMsgNum * sizeof(MsgThirdPartyChild);
        *piRealMsgSize += sizeof(begin);
    }
    return REBUILDERCUT_SUCC;
}

template <class MsgQueueNolock>
int CutMsgNolock( MsgQueueNolock* pQueue, Msg* pMsg, uint8 encryptMode, int* piRealMsgSize = 0)
{
    if ( pMsg->GetLength() < MSGMAXSIZE )
    { return REBUILDERCUT_NEEDNOTCUT; }

    int iReadPos = 0;

    MsgChild      child;
    MsgChildBegin begin;

    char *szData = (char*)pMsg;
    int iDataLeft = 0;

    // 包头Id
    child.header.stID = pMsg->header.stID;
    begin.header.stID = pMsg->header.stID;

    begin.nMsgSize      = pMsg->GetLength();
    begin.stChildMsgNum = (begin.nMsgSize + MsgChild::CHILD_BUFSIZE - 1) / MsgChild::CHILD_BUFSIZE;

    if( !pQueue->PushMsg( &begin, encryptMode ) )
    { return REBUILDERCUT_CRITICALERROR; }

    iDataLeft = begin.nMsgSize;

    for( int i=0; i<begin.stChildMsgNum; ++i )
    {
        if( iDataLeft > MsgChild::CHILD_BUFSIZE )
        { child.stBufSize = MsgChild::CHILD_BUFSIZE; }
        else
        { child.stBufSize = iDataLeft; }

        memcpy(child.szBuf,szData,child.stBufSize);

        if ( !pQueue->PushMsg( &child, encryptMode) )
        { return REBUILDERCUT_CRITICALERROR; }

        iDataLeft -= child.stBufSize;
        szData += child.stBufSize;
    }

    if( piRealMsgSize )
    {
        //实际需要发送的消息
        *piRealMsgSize = begin.stChildMsgNum * sizeof(MsgChild);
        *piRealMsgSize += sizeof(begin);
    }
    return REBUILDERCUT_SUCC;
}

// 消息的地址是pMsgRebuild = (Msg*)pQueue->GetBuffer( stSize );
template<class MsgQueue>
int RebuildMsgs(MsgQueue* pQueue, Msg* pMsg)
{
    Msg* pMsgRebuild = NULL;
    char szBuf[MSGMAXSIZE];
    MsgChild*pMsgBuf = (MsgChild*)szBuf;

    MsgChildBegin* pBegin = (MsgChildBegin*)pMsg;
    int iWritePos = 0;

    if (pMsg->header.dwType == MSGTYPE_CHILDBEGIN)
    {
        int nSize = pBegin->nMsgSize;
        short stChildMsgNum = pBegin->stChildMsgNum;

        //>= stChildMsgNum +1
        if (pQueue->GetSize() > stChildMsgNum)
        {
            pMsgRebuild = (Msg*)pQueue->GetBuffer(nSize);
            if ( NULL == pMsgRebuild)
            { return REBUILDERCUT_CRITICALERROR; }

            //去掉MsgChildBegin            
            CSALocker locker(pQueue->GetQueue());

            if (!pQueue->PopMsg(szBuf))
            { return REBUILDERCUT_CRITICALERROR; }

            for( int i=0; i<stChildMsgNum; ++i )
            {                
                if( pQueue->PopMsg(szBuf) && (MSGTYPE_CHILD == pMsgBuf->header.dwType))
                {
                    if (pMsgBuf->stBufSize > 0)
                    {
                        memcpy(((char*)pMsgRebuild) + iWritePos,pMsgBuf->szBuf,pMsgBuf->stBufSize);
                        iWritePos += pMsgBuf->stBufSize;
                    }
                    else
                    { return REBUILDERCUT_CRITICALERROR; }
                }
                else
                { //error
                    return REBUILDERCUT_CRITICALERROR;
                }
            }            
            return REBUILDERCUT_SUCC;
        }
        else
        {
            //队列中消息数量不够        
            return REBUILDERCUT_NOTENOUGHCHILD;
        }
    }
    return REBUILDERCUT_SKIP;
}

// 消息的地址是pMsgRebuild = (Msg*)pQueue->GetBuffer( stSize );
template<class MsgQueueNolock>
int RebuildMsgsNolock(MsgQueueNolock* pQueue, Msg* pMsg)
{
    Msg* pMsgRebuild = NULL;
    char szBuf[MSGMAXSIZE];
    MsgChild*pMsgBuf = (MsgChild*)szBuf;

    MsgChildBegin* pBegin = (MsgChildBegin*)pMsg;
    int iWritePos = 0;

    if (pMsg->header.dwType == MSGTYPE_CHILDBEGIN)
    {
        int nSize = pBegin->nMsgSize;
        short stChildMsgNum = pBegin->stChildMsgNum;

        //>= stChildMsgNum +1
        if (pQueue->GetSize() > stChildMsgNum)
        {
            pMsgRebuild = (Msg*)pQueue->GetBuffer(nSize);
            if ( NULL == pMsgRebuild)
           { return REBUILDERCUT_CRITICALERROR; }

            if (!pQueue->PopMsg(szBuf))
            { return REBUILDERCUT_CRITICALERROR; }

            for( int i=0; i<stChildMsgNum; ++i )
            {                
                if( pQueue->PopMsg(szBuf) && (MSGTYPE_CHILD == pMsgBuf->header.dwType))
                {
                    if (pMsgBuf->stBufSize > 0)
                    {
                        memcpy(((char*)pMsgRebuild) + iWritePos,pMsgBuf->szBuf,pMsgBuf->stBufSize);
                        iWritePos += pMsgBuf->stBufSize;
                    }
                    else
                    { return REBUILDERCUT_CRITICALERROR; }
                }
                else
                { //error
                    return REBUILDERCUT_CRITICALERROR;
                }
            }            
            return REBUILDERCUT_SUCC;
        }
        else
        {
            //队列中消息数量不够        
            return REBUILDERCUT_NOTENOUGHCHILD;
        }
    }
    return REBUILDERCUT_SKIP;
}

template<class MsgQueue>
int RebuildThirdPartyMsgs(MsgQueue* pQueue, MsgThirdParty* pMsg)
{
    MsgThirdParty* pMsgRebuild = NULL;
    char szBuf[MSGMAXSIZE] = {0};
    MsgThirdPartyChild* pMsgBuf = (MsgThirdPartyChild*)szBuf;

    MsgThirdPartyChildBegin* pBegin = (MsgThirdPartyChildBegin*)pMsg;
    int iWritePos = 0;

    if ( pMsg->type == MSGTYPE_CHILDBEGIN)
    {
        uint32 nSize         = pBegin->nMsgSize;
        int16  stChildMsgNum = pBegin->stChildMsgNum;

        //>= stChildMsgNum +1
        if ( pQueue->GetSize() > stChildMsgNum)
        {
            pMsgRebuild = (MsgThirdParty*)pQueue->GetBuffer(nSize);
            if (!pMsgRebuild)
            { return REBUILDERCUT_CRITICALERROR; }

            //去掉MsgChildBegin            
            CSALocker locker(pQueue->GetQueue());

            if (!pQueue->PopMsgThirdParty( szBuf ))
            { return REBUILDERCUT_CRITICALERROR; }

            for( int i=0 ; i<stChildMsgNum ; ++i )
            {                
                if( pQueue->PopMsgThirdParty(szBuf) && (MSGTYPE_CHILD == pMsgBuf->type))
                {
                    if (pMsgBuf->stBufSize > 0)
                    {
                        memcpy(((char*)pMsgRebuild) + iWritePos,pMsgBuf->szBuf,pMsgBuf->stBufSize);
                        iWritePos += pMsgBuf->stBufSize;
                    }
                    else
                    { return REBUILDERCUT_CRITICALERROR; }
                }
                else
                { //error
                    return REBUILDERCUT_CRITICALERROR;
                }
            }            
            return REBUILDERCUT_SUCC;
        }
        else
        {
            //队列中消息数量不够        
            return REBUILDERCUT_NOTENOUGHCHILD;
        }
    }
    return REBUILDERCUT_SKIP;
}


enum enumThread
{
    THREAD_MAIN,
    THREAD_DB,
    THREAD_MAX
};

//extern char g_BufForThread[ THREAD_MAX ][ MSGCANCUTMAXSIZE ];

#endif // __MENETWORK_MSGCUTANGREBUILD_H__
