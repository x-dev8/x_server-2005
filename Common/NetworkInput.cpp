//#include "NetworkInput.h"
//#include "../../Client/Client/Include/Cfg.h"
//#include <assert.h>
//#include "FuncPerformanceLog.h"
//#include "GameTime.h"
//#include "LogFileObjectName.h"
//
//void NotPushMessage( uint8 type, uint32 messageId, uint8 result, uint32 value )
//{
//    assert( false );
//	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "NotPushMessage %u:%u:%u", type, messageId, result );
//}
//
//void RecvMessageCallBack( const SNetResult& sNetResult )
//{
//    assert( false );
//    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Recv Net Info %d:%u:%u", sNetResult.result, sNetResult.messageType, sNetResult.messageLength );
//}
//
//void SendMessageCallBack( uint32 result, uint32 watchMsgCount )
//{
//    if ( result == 0)
//    {
//        char	szDebugInfo[200];
//        sprintf( szDebugInfo, "--->{%d}", watchMsgCount );
//        OutputDebugString( szDebugInfo );
//    }
//    else
//    {
//        assert( false );
//    }
//}
//
//CNetworkInput& GettheNetworkInput()
//{
//	static CNetworkInput s_theNetworkInput;
//	return s_theNetworkInput;
//}
//
//extern CCfg gCfg;
//
//CNetworkInput::CNetworkInput()
//{		
//	m_bConnectted = false;
//	m_pConnector = GetMeNetwork().CreateMeConnector();
//    m_pConnector->SetOutMessageEncType( msgflag_des8, true );
//	m_pConnector->SetLowLevelCast(10000);
//	m_pConnector->SetNormalLevelCast(20000);
//	m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_InQueue, -1);
//	m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_OutQueue, -1);
//    m_pConnector->EnableLzoUnCompress();	
//	m_pConnector->SetSkipInQueueWhenReset( true ); // 如果有被动的关闭 清空队列消息
//    m_pConnector->SetRecvMessageErrorCallBack( RecvMessageCallBack );
//    m_pConnector->SetSendMessageErrorCallBack( SendMessageCallBack );
//    m_pConnector->SetNotPushMessageCallBack( NotPushMessage );
//    m_pConnector->SetOutMsgWatchType( MSG_ALLOCGWID );
//    _dwThreadId = 0;
//}
//
//CNetworkInput::~CNetworkInput()
//{
//	if( m_pConnector )
//	{
//		m_pConnector->Close();
//		m_pConnector->Release();
//		m_pConnector = NULL;
//	}
//}
//
//void CNetworkInput::Reset()
//{
//	m_bConnectted = false;
//	m_pConnector->Reset();
//	m_pConnector->SetSkipInQueueWhenReset( true );
//}
//
//bool CNetworkInput::InitConnect( const char* szDstIP, unsigned short iPort )
//{
//	strncpy_s( m_szDst, sizeof(m_szDst), szDstIP, sizeof(m_szDst) - 1);
//	m_iPort = iPort;	
//    if ( m_iPort == 0)
//    { Reset(); }
//	return true;
//}
//
//bool CNetworkInput::ConnectToServer( int iConnectTimeout )
//{
//    if ( NULL == m_pConnector )
//    { m_pConnector = GetMeNetwork().CreateMeConnector(); }
//
//    if( m_pConnector->GetSocket()->ConnectAsync( m_szDst, m_iPort, iConnectTimeout ) )
//    { m_bConnectted = true; }
//    else
//    { m_bConnectted = false; } // 连接失败
//	return m_bConnectted;
//}
//
//uint32 CNetworkInput::CreateToConnectGameServerSocket()
//{
//    if( m_pConnector->GetSocket()->Create() )
//    {
//        IMeSocket* pSocket = GetMeNetwork().CreateMeSocket();
//
//        // 不能跟上次的socket一样
//        if( !m_pConnector->CheckIsDifferentSocket() )
//        {            
//            if( !pSocket->Create())
//            {
//                pSocket->Release();
//                m_pConnector->GetSocket()->Close();
//                return ER_Failed;
//            }
//            else
//            {
//                m_pConnector->GetSocket()->Close();
//                m_pConnector->SetSocket( pSocket );
//                return ER_Success;
//            }
//        }
//        return ER_Success;
//    }    
//    return ER_Failed;
//}
//
//int CNetworkInput::RecvMsg( char* sBuf )
//{
//	if ( m_bConnectted == false )
//	{ return 0; }
//
//    m_pConnector->TryRecv2();
//
//	Msg* pMsgCon = m_pConnector->GetMsg();
//	if( NULL == pMsgCon )
//	{ return 0; }
//
//	memcpy( sBuf, pMsgCon,pMsgCon->header.stLength );
////#ifdef _DEBUG
////	static char szInfo[128];
////	sprintf(szInfo, "RecvMSG[%ld]",pMsgCon->header.dwType );
////	OutputDebugStr( szInfo );
////#endif
//	return 1;
//}
//
//int CNetworkInput::SendMsg( char *sBuf,short stSize )
//{
//	return SendMsg( (Msg*)sBuf );
//}
//
//int CNetworkInput::SendMsg( Msg*pMsg )
//{
//	if( m_pConnector->IsClosed() )
//	{ return -1;}
//
//	int iret = m_pConnector->SendMsg( pMsg, IMeConnector::ECT_Normal, msgflag_des8 );
//    if( iret <=0 )
//    { return -1; }
//
//	//CheckSendReq();
//
////#ifdef _DEBUG
////	static char szInfo[128];
////	sprintf(szInfo, "SendMSG[%ld]",pMsg->header.dwType );
////	OutputDebugStr( szInfo );
////#endif
//	return iret;
//}
//
//void CNetworkInput::CheckSendReq()
//{
//    m_pConnector->TrySend2( false );
//
//    if ( _dwThreadId == 0)
//    {
//        _dwThreadId = GetCurrentThreadId();
//    }
//    else
//    {
//        uint32 currentThreadId = GetCurrentThreadId();
//        assert( _dwThreadId == currentThreadId );
//    }
//}
//
//bool CNetworkInput::IsClosed()
//{
//	if (!m_pConnector)
//	{ return true;}
//	else
//	{ return m_pConnector->IsClosed(); }
//}
//
//void CNetworkInput::Close()
//{
//	if ( m_bConnectted )
//    {   
//		m_pConnector->Close();
//        m_pConnector->SetSkipInQueueWhenReset( true ); // 客户端要复用 所以要置回来
//		m_bConnectted = false;
//	}
//}
//
//bool CNetworkInput::IsAllMsgSendOver()
//{
//	if( !m_pConnector )
//    { return true; }
//	else
//    { return m_pConnector->IsAllMsgSendOver(); }
//}
//#include "net_work/net_socket.h"

#include "networkinput.h"
//#include "../../client/client/cfg.h"
#include "Cfg.h"
#include "FuncPerformanceLog.h"
//#include "MsgDef.h"
#include "MessageDefine.h"
//#include "log.h"


CNetworkInput& GettheNetworkInput()
{
	static CNetworkInput s_theNetworkInput;
	return s_theNetworkInput;
}
extern CCfg gCfg;
CNetworkInput::CNetworkInput()
{
	guardfunc;
	memset(m_szDst, 0, sizeof(m_szDst));
	m_iPort = 0;
	m_bConnectted = false;
	m_pConnector = network::Socketer_create();
	//m_pConnector->UseDecrypt();
	m_pConnector->UseEncrypt();
	//m_pConnector->UseUncompress();	
	unguard;
}

CNetworkInput::~CNetworkInput(void)
{
	guardfunc;
	Destroy();
	m_bConnectted = false;
	unguard;
}
void CNetworkInput::Destroy ()
{
	guardfunc;
	if( m_pConnector )
	{
		network::Socketer_release(m_pConnector);
		m_pConnector = NULL;
	}
	unguard;
}

bool CNetworkInput::InitConnect( const char *szDstIP,int iPort )
{
	guardfunc;
	m_bConnectted = false;
	m_pConnector->Close();
	strcpy( m_szDst,szDstIP );
	m_iPort = iPort;	
	return true;
	unguard;
}

bool CNetworkInput::ConnectToServer (bool islogin)
{
	guardfunc;
	//尝试连接15秒，连接不上就提示“创建连接失败”
	int iConnectTimeout = 15000;
	DWORD current = HQ_TimeGetTime();
	if (m_pConnector&&m_pConnector->IsClose())
	{
		network::Socketer_release(m_pConnector);
		m_pConnector = NULL;
		m_pConnector = network::Socketer_create();
		//m_pConnector->UseDecrypt();
		m_pConnector->UseEncrypt();
		//m_pConnector->UseUncompress();
	}
	while (1)
	{
		if( m_pConnector && m_pConnector->Connect(m_szDst,m_iPort) )
		{
			m_bConnectted = true;
			break;
		}
		else
			m_bConnectted = false;
		if (HQ_TimeGetTime() - current >= iConnectTimeout)
			break;
		Sleep(10);
	}
	return m_bConnectted;
	unguard;
}

int CNetworkInput::SendMsg( Msg* pMsg ,long msg_length)
{
	guardfunc;
	//if(pMsg->GetType() != MSG_PING )
	//{
	//	int n =0;
	//	n++;
	//	//		Clog::Instance().WriteLog("send message type:%d, lenght:%d", pMsg->GetType(), pMsg->GetLength());
	//}
	if (!m_pConnector||m_pConnector->IsClose())
	{
		return -1;
	}
	bool iret = m_pConnector->SendMsg( pMsg,0,0);
	if (!iret)
	{
		return -1;
	}
	return iret;
	unguard;
}
Msg *CNetworkInput::GetMsg ()
{
	if (!m_pConnector)
	{
		return NULL;
	}
	return m_pConnector->GetMsg();
}

bool CNetworkInput::IsClosed(void)
{
	guardfunc;
	if (!m_pConnector)
	{
		return true;
	}
	else
		return m_pConnector->IsClose();
	unguard;
}

void CNetworkInput::Close()
{
	guardfunc;
	if (m_pConnector)
	{
		m_pConnector->Close();		
	}
	m_bConnectted = false;
	unguard;
}
void CNetworkInput::CheckSendReq()
{
	guardfunc;
	if (m_pConnector)
	{
		m_pConnector->CheckSend();
	}
	unguard;
}

void CNetworkInput::CheckRevReq()
{
	if (m_pConnector)
	{
		m_pConnector->CheckRecv();
	}
}
//--------------------------------------------------------------------------
//	End.
//--------------------------------------------------------------------------

