#include "NetworkInput.h"
#include <assert.h>
#include "FuncPerformanceLog.h"
#include "GameTime.h"

/*
INetworkNode& GettheNetworkInput(){
	static INetworkNode s_theNetworkInput;
	return s_theNetworkInput;
}*/

void NotPushMessage( uint8 type, uint32 messageId, uint8 result, uint32 value )
{
	assert( false );
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "NotPushMessage %u:%u:%u", type, messageId, result );
}

void SendMessageCallBack( uint32 result, uint32 watchMsgCount )
{
	if ( result == 0)
	{
		char	szDebugInfo[200];
		sprintf( szDebugInfo, "--->{%d}", watchMsgCount );
		OutputDebugString( szDebugInfo );
	}
	else
	{
		assert( false );
	}
}

INetworkNode::INetworkNode()
{		
	m_bConnectted = false;
	m_sock=Listener_create(); 
	m_pConnector = Socketer_create();
	//m_pConnector->UseDecrypt();
	m_pConnector->UseEncrypt();
	//m_pConnector->UseUncompress();
	s_time_record=0;
	_currentState = e_state_no_confirm;
	_lastState    = _currentState;
	//m_pConnector = GetMeNetwork().CreateMeConnector();
	//   m_pConnector->SetOutMessageEncType( msgflag_des8, true );
	//m_pConnector->SetLowLevelCast(10000);
	//m_pConnector->SetNormalLevelCast(20000);
	//m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_InQueue, -1);
	//m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_OutQueue, -1);
	//   m_pConnector->EnableLzoUnCompress();	
	//m_pConnector->SetSkipInQueueWhenReset( true ); // 如果有被动的关闭 清空队列消息
	//   m_pConnector->SetRecvMessageErrorCallBack( RecvMessageCallBack );
	//   m_pConnector->SetSendMessageErrorCallBack( SendMessageCallBack );
	//   m_pConnector->SetNotPushMessageCallBack( NotPushMessage );
	//   m_pConnector->SetOutMsgWatchType( MSG_ALLOCGWID );
	_dwThreadId = 0;
}

INetworkNode::~INetworkNode(void)
{
	Close();
	m_pConnector->Close();
	if( m_pConnector ){
		//	m_pConnector->Close();
		//	m_pConnector->Release();
		m_pConnector = NULL;
	}
}

void INetworkNode::Reset(void)
{
	m_bConnectted = false;
}

BOOL INetworkNode::InitConnect( const char *szDstIP,int iPort )
{
	strcpy( m_szDst,szDstIP );
	m_iPort = iPort;
	
	m_pConnector->Close();	
	if ( m_iPort == 0)
	{ Reset(); }
	return TRUE;
}






bool INetworkNode::ConnectToServer()
{
/*
	if ( !m_pConnector )
	{
		m_pConnector = Socketer_create();
		return false;
	}

	if( m_pConnector->Connect( m_szDst, m_iPort ) )
	{
		m_bConnectted = true;
	}
	else
	{ // 连接失败
		m_bConnectted = false;
	}
	return m_bConnectted;*/

	//尝试连接15秒，连接不上就提示“创建连接失败”
	int iConnectTimeout = 15000;
	DWORD current = HQ_TimeGetTime();
	if (m_pConnector->IsClose())
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
}


// int INetworkNode::SendMsg( Msg*pMsg )
// {
// 	if(IsClosed()){ return -1;}
// 	int iret = m_pConnector->SendMsg( pMsg);//, IMeConnector::ECT_Normal, msgflag_des8 );
// 	if( iret <=0 )
// 	{ return -1; }
// 	return iret;
// }




bool INetworkNode::IsClosed(void)
{
	if (!m_pConnector)
	{ return m_pConnector->IsClose();}
	return true;
}

void INetworkNode::Close()
{
	if ( m_bConnectted == true )
	{   
		m_pConnector->Close();
		//m_pConnector->SetSkipInQueueWhenReset( true ); // 客户端要复用 所以要置回来
		m_bConnectted = false;
	}
}

void INetworkNode::Update()
{
	if(m_pConnector){
		m_pConnector->CheckSend();
		m_pConnector->CheckRecv();
	}

	if(GetBotState()==e_state_no_confirm){
		try_comfirm_account();
		return ;
	}

	if( m_bConnectted)
	{
		if( GetConnector() != NULL && GetConnector()->IsClose() )
		{
			m_bConnectted = FALSE;
			OnDisconnectFromServer();
		}
		ProcessMsgs();
	}
}
