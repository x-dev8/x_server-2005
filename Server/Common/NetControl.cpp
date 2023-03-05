#include "NetControl.h"
#include "MsgQueueProxy.h"
#include "MsgCutAndRebuild.h"
#include "ThreadBuffer.h"
#include "FuncPerformanceLog.h"
#include "g_assert.h"

void NetControl::Push2In( Msg* pMsg )
{
    int iSize = 0;
    if( pMsg->GetLength() > MSGMAXSIZE )
    {
        // 切割消息
        MeMsgQueueProxy<NetControl::const_iInSize, MsgQueueNotLock> tmpIn;
        tmpIn.Init( &m_in,0,MSGCANCUTMAXSIZE );
        switch ( CutMsgNolock(&tmpIn, pMsg, msgflag_normal, &iSize))
        {
        case REBUILDERCUT_CRITICALERROR:                        
            OnCriticalError();
            break;    
        default:
            break;
        }
    }
    else
    {
        m_in.PushMsg( pMsg );
    }
}

void NetControl::Push2InEx( Msg* pMsg )
{
    m_in.PushMsg( pMsg, msgflag_normal );
}

Msg* NetControl::GetMsg()
{
    // 只适用于主线程中角色消息,察看是否有分割消息
    Msg* pMsgRet = 0;
    Msg* pMsg = reinterpret_cast<Msg*>(GettheThreadBuffer().GetBuffer());

    if( !m_in.PeekMsg( pMsg,MSGMAXSIZE ) )
    { goto ret; }

    if( pMsg->GetType() == CUT_MSG_CHILDBEGIN )
    {
        MeMsgQueueProxy<NetControl::const_iInSize, MsgQueueNotLock> tmpIn;
        tmpIn.Init(&m_in, GettheThreadBuffer().GetBuffer(), MSGCANCUTMAXSIZE);
        switch( RebuildMsgsNolock( &tmpIn, pMsg ) )
        {
        case REBUILDERCUT_CRITICALERROR:            
            OnCriticalError();
            break;
        case REBUILDERCUT_NOTENOUGHCHILD:
            break;
        default:
            pMsgRet = pMsg;            
            break;
        }
    }
    else
    {
        if( m_in.PopMsg( pMsg,MSGMAXSIZE ) )
        {
            pMsgRet = pMsg;
        }
    }
ret:
    return pMsgRet;
}

Msg* NetControl::GetMsgEx()
{
    Msg* pMsgRet = NULL;
    Msg* pMsg = reinterpret_cast<Msg*>(GettheThreadBuffer().GetBuffer());
    if( m_in.PopMsg( pMsg, BUFFER_SIZE ) )
    {
        pMsgRet = pMsg;
    }
    return pMsgRet;
}

//////////////////////////////////////////////////////////////////////////
CItemControl::CItemControl()
{
}

//////////////////////////////////////////////////////////////////////////
NetControlEx::NetControlEx(void):
m_iErrTimeout(0),
m_iRecvRestSize(0),
m_iSendRestSize(0)
{
	m_sock = NULL;
}

NetControlEx::~NetControlEx()
{
    if( m_sock )
    {
        /*m_sock->Release();*/
		Socketer_release(m_sock);
        m_sock = NULL;
    }
}

void NetControlEx::PushBuf2Msg( char*sBuf,int iSize )
{
    short stMsgSize;
    char  sMsgBuf[ MSGMAXSIZE ];
    int   iNeed;
    Msg*  pMsg;
    if( iSize <= 0 )
    { return; }

    //if( m_in.GetSize() > const_iMaxQueueMsgNum )
    //{
    //    OnCriticalError();
    //    return ;
    //}

    if( m_iRecvRestSize < sizeof( short ) )
    {
        if( m_iRecvRestSize + iSize < sizeof( short ) )
        {
            memcpy( m_sRecvRest+m_iRecvRestSize,sBuf, min(iSize, sizeof(m_sRecvRest)-m_iRecvRestSize) );
            m_iRecvRestSize += iSize;
            return;
        }
        else
        {
            iNeed = sizeof( short ) - m_iRecvRestSize;
            if( iSize > iNeed )
            {
                //先凑足short
                memcpy( m_sRecvRest+m_iRecvRestSize,sBuf, min(iNeed, sizeof(m_sRecvRest)-m_iRecvRestSize));
                sBuf += iNeed;
                iSize -= iNeed;

                m_iRecvRestSize += iNeed;
            }
            else
            {
                memcpy( m_sRecvRest+m_iRecvRestSize,sBuf, min(iSize, sizeof(m_sRecvRest)-m_iRecvRestSize) );
                m_iRecvRestSize += iSize;
                return;
            }
        }
    }

    stMsgSize = *(short*)m_sRecvRest;
    if( stMsgSize < 0 || stMsgSize > MSGMAXSIZE )
    {
        //失败
        G_ASSERT_NORET( false );
        //致命错误
        AddErrorTimeout( const_iErrTimeout );
        return;
    }

    if( m_iRecvRestSize + iSize >= stMsgSize )
    {
        //有完整的包,先组成完整的包
        memcpy( sMsgBuf,m_sRecvRest, min(m_iRecvRestSize, sizeof(sMsgBuf)) );
        iNeed = stMsgSize - m_iRecvRestSize;
        memcpy( sMsgBuf+m_iRecvRestSize,sBuf, min(iNeed, sizeof(sMsgBuf)-m_iRecvRestSize) );
        //处理包
        pMsg = (Msg*)sMsgBuf;
        //保存到接收队列
        //DATAREPORT( "Recved packet",1 );

#ifdef LOG_ALL_MSG
        LogMsg( this, pMsg );
#endif // LOG_ALL_MSG

        Push2In( pMsg );
        //
        m_iRecvRestSize = 0;
        if( iSize > iNeed )
            PushBuf2Msg( sBuf+iNeed,iSize-iNeed );
    }
    else
    {
        if( m_iRecvRestSize + iSize < MSGMAXSIZE )
        {
            memcpy( m_sRecvRest+m_iRecvRestSize,sBuf, min(iSize, sizeof(m_sRecvRest)-m_iRecvRestSize) );
            m_iRecvRestSize += iSize;
        }
        else
        {
            //
            G_ASSERT_NORET( false );
        }
    }
}

void NetControlEx::RecvMsg()
{
//    char sRecvBuf[ MSGMAXSIZE ];        
//    int iError;
//recv_again:
//    int iRecv = m_sock->Recv( sRecvBuf,MSGMAXSIZE,0 );
//    if( 0 == iRecv )
//    {
//        //被关闭了
//        OnConnectError();
//    }
//    else
//        if( -1 == iRecv )
//        {
//            iError = WSAGetLastError();
//            switch( iError )
//            {
//            case WSAECONNRESET:
//                OnConnectError();
//                break;
//            case WSAEWOULDBLOCK:
//                //do nothing...
//                break;
//            default:
//                AddErrorTimeout();
//                break;
//            }
//        }
//        else
//        {
//            m_iErrTimeout = 0;
//            //DATAREPORT( "Recved bytes",iRecv );
//            PushBuf2Msg( sRecvBuf,iRecv );        
//        }
//        if( MSGMAXSIZE == iRecv )
//        { goto recv_again; }
}

void NetControlEx::AddErrorTimeout( int iData ) 
{
    m_iErrTimeout += iData;
    if( m_iErrTimeout >= const_iErrTimeout )
    {
        //关闭
        OnConnectError();
    }
}

void NetControlEx::SendMsg( Msg*pMsg )
{   
    bool bRet = true;
    if( pMsg->header.stLength < MSGMAXSIZE )
    {
        bRet = m_out.PushMsg( pMsg );
    }
    else
    {    
        MeMsgQueueProxy<NetControl::const_iOutSize> tmpOut;
        tmpOut.Init(&m_out, GettheThreadBuffer().GetBuffer(), MSGCANCUTMAXSIZE);
        //gCharacterProxyOut.Init( &m_out,g_BufForThread[THREAD_MAIN],MSGCANCUTMAXSIZE );
        switch( CutMsg( &tmpOut, pMsg, msgflag_normal ) )
        {
        case REBUILDERCUT_CRITICALERROR:            
            OnCriticalError();
            bRet = false;
            break;    
        default:
            bRet = true;
        }
    }    
    if( !bRet )
    {
        OnCriticalError();
    }

    if( m_out.GetSize() > const_iMaxQueueMsgNum )
    {
        //输出队列不能无休止的增加，当
        OnCriticalError();
        return;
    }
#ifdef LOG_ALL_MSG
    LogMsg( this, pMsg );
#endif // LOG_ALL_MSG
}

bool NetControlEx::SendRest()
{
    //int iSend;
    //int iError;
    //if( m_iSendRestSize > 0 )
    //{

    //    BEGINFUNCPERLOG( "socket send" );
    //    iSend = m_sock->Send( m_sSendRest+m_iSendRestStart,m_iSendRestSize,0 );
    //    ENDFUNCPERLOG( "socket send" );

    //    if( iSend <= 0 )
    //    {            
    //        iError = WSAGetLastError();
    //        if( WSAEWOULDBLOCK != iError )
    //            AddErrorTimeout();
    //        return false;
    //    }

    //    //DATAREPORT("Send bytes",iSend );
    //    if( iSend < m_iSendRestSize )
    //    {
    //        //剩余数据还没有发送完
    //        m_iSendRestStart += iSend;
    //        m_iSendRestSize -= iSend;
    //        return false;
    //    }
    //    m_iSendRestStart = 0;
    //    m_iSendRestSize = 0;
    //}
    //剩余数据全部发送完毕，可以发送下一个数据包
    return true;
}

void NetControlEx::TrySendAllMsg()
{
    //Msg*pMsg = (Msg*)m_sSendRest;        

    //const int iHalfMsgSize = MSGMAXSIZE / 2;
    ////如果有足够的消息准备发送
    //if( m_iSendRestSize > iHalfMsgSize )
    //{    
    //    if( !SendRest() )
    //        return;
    //}
    //else
    //{
    //    //将buf中的剩余数据前移
    //    memcpy( m_sSendRest,m_sSendRest+m_iSendRestStart, min(m_iSendRestSize, sizeof(m_sSendRest)) );
    //    m_iSendRestStart = 0;
    //}

    //while( 1 )
    //{        
    //    int iWritePos = m_iSendRestSize;
    //    int iSizeRest;
    //    iSizeRest = MSGMAXSIZE;
    //    iSizeRest -= iWritePos;        
    //    int iMsgLen;
    //    while( ( iSizeRest > 64 ) 
    //        && ( m_out.GetSize() > 0 ) )
    //    {
    //        pMsg = (Msg*)(m_sSendRest + iWritePos );

    //        BEGINFUNCPERLOG( "pop msg" );
    //        bool bPopRet = m_out.PopMsg( pMsg,iSizeRest );
    //        ENDFUNCPERLOG( "pop msg" );
    //        if( !bPopRet )
    //            break;
    //        iMsgLen = pMsg->header.stLength;
    //        m_iSendRestSize += iMsgLen;
    //        iWritePos += iMsgLen;
    //        iSizeRest -= iMsgLen;
    //    };
    //    if( m_iSendRestSize <= 0 )
    //        break;
    //    if( !SendRest() )
    //        break;
    //}

    //while( m_out.PopMsg( pMsg,MSGMAXSIZE ) )
    //{
    //    m_iSendRestSize  = pMsg->GetLength();
    //    m_iSendRestStart = 0;
    //    if( !SendRest() )
    //        return;
    //}
}

void NetControlEx::OnConnectError()
{
    //在输入队列加入一个
    MsgExit msg;
    msg.header.stID = GetID();
    Push2In( &msg );
    //m_sock->Close();
}

void NetControlEx::GetPeerName( char *szName,int iLen )
{
    //sockaddr_in addr;
    //memset(&addr, 0, sizeof(addr));
    //int iSize;
    ////m_sock
    //iSize = sizeof( addr );
    //if( -1 != getpeername( m_sock->GetSockfd(),(sockaddr*)&addr,&iSize ) )
    //{
    //    _snprintf( szName, 20, inet_ntoa(addr.sin_addr));
    //    /*_snprintf( szName, sizeof(szName)-1, "%d.%d.%d.%d",addr.sin_addr.S_un.S_un_b .s_b1, 
    //    addr.sin_addr.S_un.S_un_b .s_b2, 
    //    addr.sin_addr.S_un.S_un_b .s_b3, 
    //    addr.sin_addr.S_un.S_un_b .s_b4 );*/
    //}
    //else
    //{
    //    _snprintf( szName, sizeof(szName)-1, "Invalid addr" );
    //}
}
