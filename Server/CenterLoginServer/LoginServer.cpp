#include "LoginServer.h"
#include "Config.h"
#include "NetWorkParameterDefine.h"
#include "AccountDBSession.h"
#include "application_config.h"
#include "SimpleCryptograph.h"
#include "helper.h"
#include "CenterGameMessage.h"
#include "AccountServer.h"
#include "ColorScreen.h"
#include "LogMessage.h"
#include "GLSService.h"
#include "tstring.h"
#include "Timestamp/Timestamp.h"

#define WAITCLOSE_ALLOW_RATE 0.3f

//LoginServer* LoginServer::pApplicationInstance = NULL;
CWorkThread LoginServer::g_SqlServiceThread;
CWorkThread LoginServer::g_MainLogicThread;
//void LoginServer::TryConnectToCenterServer()
//{
//	Config& config = Config::GetInstance();
//	if( _CenterServerConnector->Connect( config.szCenterServerIP.c_str(), config.sCenterServerPort) )
//	{
//		{
//			_iCenterServerConnectorState = CS_Connectted;
//			_nCenterServerPing = HQ_TimeGetTime();
//			//���ӳɹ�
//			//_AccountServerConnector->EnableIoCompletionPort( false );
//
//			//����ServerID
//			GS2CSRegiseterGameServerInfoReq msg;            
//			msg.SetLevel(level_high); //�����������е����ȼ�
//			strncpy_s( msg.szGameServerName, config.szServerName, sizeof(msg.szGameServerName));
//			msg.btReset   = GS2CSRegiseterGameServerInfoReq::ROT_REPLACE;
//			msg.nServerId = CENTERLOGINSERVERID;
//			SendMsgToCenterServer(&msg);
//		}
//	}
//	else
//	{
//		if(!_CenterServerConnector)
//		{
//			_CenterServerConnector = Socketer_create();
//		}
//	}
//}

LoginServer::LoginServer()
{
	m_pNormalClients            =  NULL;
	m_pClientWaitClose          =  NULL;
	_pOwner                     =  NULL;	
	m_onlinenum                 =  0;
	m_psockClientListen         =  NULL;
	m_pListenServer             =  NULL;
	m_pNormalServers            =  NULL;
	m_pServerWaitClose          =  NULL;
	m_account_map.clear();
	m_mapClient.clear();
	m_bInService				= true;
}

LoginServer::~LoginServer()
{
	if( m_pNormalClients )
	{ delete m_pNormalClients; }
	if( m_pClientWaitClose )
	{ delete m_pClientWaitClose; }
	m_account_map.clear();
	m_mapClient.clear();
	if (m_pServerWaitClose)
	{
		delete m_pServerWaitClose;
	}
	if (m_pNormalServers)
	{
		delete m_pNormalServers;
	}

	_pOwner                     =  NULL;

	if( m_psockClientListen )
	{
		m_psockClientListen->Close();
		Listener_release(m_psockClientListen);
		m_psockClientListen = NULL;
	}

	if (m_pListenServer)
	{
		Listener_release(m_pListenServer);
		m_pListenServer = NULL;
	}
}


long LoginServer::Init( ConsoleApplication* pOwner )
{   
	_pOwner = pOwner; 	
	//ReqCheckAccountPool ();
	//�����ͻ��˼���
	m_psockClientListen = Listener_create();
	if ( !m_psockClientListen  )
	{ return ER_Failed; }

	if(!m_psockClientListen->Listen( theConfig.ustForClientPort,eN_LoginServer_ListenNum) )
	{ return ER_Failed; }
    //��������������
 	m_pListenServer = Listener_create();
	if ( !m_pListenServer  )
	{ return ER_Failed; }

	if(!m_pListenServer->Listen( theConfig.ustListenCenterPort,eN_LoginServer_ListenNum) )
	{ return ER_Failed; }


	m_pNormalClients   = new CStaticArray<CClientSession*>( dr_worldMaxPlayers  );
	m_pClientWaitClose = new CStaticArray<CClientSession*>( dr_worldMaxPlayers  );

	m_pNormalServers   = new CStaticArray<CServerSession*>( 20  );
	m_pServerWaitClose = new CStaticArray<CServerSession*>( 20  );

	theAccountDBSession.SetService(theConfig.UsingDB);
	// �������߼��߳�
	bool bResult = LoginServer::g_MainLogicThread.CreateThread( LoginServer::Main );
	CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

	bResult = LoginServer::g_SqlServiceThread.CreateThread( LoginServer::SqlMain );
	CHECK_RETURN( !bResult, ER_SqlServiceFail );

	return ER_Success;
}

void LoginServer::Main( void* pParam )
{
	theCenterLoginServer.RunOnce();
}

void LoginServer::SqlMain( void* pParam)
{
	//д���ݿ���־�߳�,���ֱ��ʹ�����ݿ��е��ʺ�,��Ϊ��֤�߳�

	/*theCenterLoginServer.GetSqlService().EnableOnlineQueryFlag();
	theCenterLoginServer.GetSqlService().RunOnce();
	
	MsgCenterLoginOn sql;
	while ( theCenterLoginServer.GetSqlService().GetOnlineQueryMessage(sql.sql) )
	{
		theCenterLoginServer.SendMsgToCenterServer(&sql);
	}*/
	theAccountDBSession.Run();

	theGLSService.RunOnStep();

	Sleep(1);
}

//void LoginServer::SendMsgToCenterServer( Msg *pMsg )
//{
//	if( CS_Connectted == _iCenterServerConnectorState && _CenterServerConnector)
//	{
//		_CenterServerConnector->SendMsg( pMsg );
//	}
//}


long LoginServer::RunOnce()
{ 
	network::net_run();

	ProcessResultMySql();

	RunServer();
	RunClient();

	if (!theConfig.UsingDB)
	{
		theAccountServer.Run();
	}

	Sleep(1);
	return ER_Success;
}


CClientSession* LoginServer::GetClientByAccountName(const char *account)
{
	if (!account)
	{
		return NULL;
	}
	
	AuthMap::iterator itr = m_account_map.find(account);
	if (itr != m_account_map.end())
	{
		return itr->second;
	}
	return NULL;
}
CClientSession* LoginServer::GetClientByAccountID(unsigned long accountid)
{
	mapClient::iterator itr = m_mapClient.find(accountid);
	if (itr != m_mapClient.end())
	{
		return itr->second;
	}
	return NULL;
}


bool LoginServer::AddClientByAccountName(const char *account,const char* cMac,CClientSession* pClient)
{
	if (!account||!pClient)
	{
		return false;
	}
	CClientSession* pTemp = GetClientByAccountName(account);
	if (pTemp)
	{
		//����������͸���2���ͻ����ظ���¼,����ȫ�������뵽�ӳ�ɾ��������ȥ
		//todo:1:����pClient
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_alreadyaloginthisaccount;
		pClient->SendMsg(&msg);
		//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%s] ����ͬʱ��½��",pTemp->GetAccount());
		//todo:2:����pTemp
		//MsgAckLogin msg1;
		//msg1.stErrorCode = MsgAckLogin::ret_alreadyaloginthisaccount;
		//pTemp->SendMsg(&msg1);
		//todo:3:�����ӳ�ɾ��������ȥ
//		AddToClientWaitClose(pTemp,__FUNCTION__, __LINE__);
//		RemoveClient(account);
		AddToClientWaitClose(pClient,__FUNCTION__, __LINE__);
		
		return false;
	}	
	m_account_map.insert(std::make_pair(account,pClient));
	pClient->SetAccountName(account);
	pClient->SetMacAdress(cMac);
	return true;
}

bool LoginServer::AddClientByAccountID(unsigned long accountid,CClientSession* pClient)
{
	if (accountid == 0 || accountid == 0xffffffff)
	{
		return false;
	}
	CClientSession* pTemp = GetClientByAccountID(accountid);
	if (pTemp)
	{
		//����������͸���2���ͻ����ظ���¼,����ȫ�������뵽�ӳ�ɾ��������ȥ
		//todo:1:����pClient
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_alreadyaloginthisaccount;
		pClient->SendMsg(&msg);
		//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%s] ����ͬʱ��½��",pTemp->GetAccount());
		//todo:2:����pTemp
		/*MsgAckLogin msg1;
		msg1.stErrorCode = MsgAckLogin::ret_alreadyaloginthisaccount;
		pTemp->SendMsg(&msg1);*/
		//todo:3:�����ӳ�ɾ��������ȥ
//		AddToClientWaitClose(pTemp,__FUNCTION__, __LINE__);
//		RemoveClientByAccountId(accountid);
		AddToClientWaitClose(pClient,__FUNCTION__, __LINE__);
		
		return false;
	}	
	m_mapClient.insert(std::make_pair(accountid,pClient));
	pClient->SetAccountId(accountid);
	return true;
}

//�Ƴ��ͻ������˺ŵĹ���
bool LoginServer::RemoveClient( const char *account )
{
	assert(account);
	if( strlen(account) == 0)
		return false;
	AuthMap::iterator itr = m_account_map.find(account);
	if( itr != m_account_map.end() )
	{
		m_account_map.erase(itr);
		return true;
	}
	return false;
}
bool LoginServer::RemoveClientByAccountId( unsigned long accountid )
{
	if (accountid == 0xffffffff)
	{
		return false;
	}
	mapClient::iterator itr = m_mapClient.find(accountid);
	if (itr != m_mapClient.end())
	{
		m_mapClient.erase(itr);
		return true;
	}
	return false;
}

void LoginServer::CheckClientWaitClose( bool bWait)
{
	// ��������رյ�socket�Ƿ�ر����
	CClientSession** ppChar  = NULL;
	CClientSession*  pChar   = NULL;

	int iSize = m_pClientWaitClose->GetSize();
	int iUsed = m_pClientWaitClose->GetUsed();

	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++iLoopSize )
	{
		ppChar = (*m_pClientWaitClose)[ iLoopSize ];
		if(  NULL == ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( NULL == pChar)
		{ continue; }

		Socketer* pConnector =  pChar->GetConnecter();
		if ( NULL == pConnector )
		{ continue; }

		// �ͷż���
		if( pChar->CanClose(HQ_TimeGetTime()) || !bWait ) // �ͻ��˲��ڷ����з�״̬ ���� �ڵ���ʱ�䳬ʱ ���� ����Ҫ��
		{			
			pConnector->Close();
			// ɾ��
			m_pClientWaitClose->Free( iLoopSize );
			delete pChar;
		}
	}
}

void LoginServer::AddToClientWaitClose( CClientSession* pClient, char* szFun, int nLine )
{
	if ( !pClient||!pClient->IsInNormalList())
	{ return; }

	IncreaseOnlineNum( -1 );

	if ( InvalidGameObjectId != pClient->GetId())
	{
		m_pNormalClients->Free(pClient->GetId());
	}
	RemoveClient(pClient->GetAccount());
	RemoveClientByAccountId(pClient->GetAccountId());
	// ���뵽�ȴ�����
	GameObjectId iID = m_pClientWaitClose->Malloc();
	if( InvalidGameObjectId == iID )
	{	
		delete pClient;
	}
	else
	{
		*(*m_pClientWaitClose)[ iID ] = pClient;
		pClient->SetCloseTime(HQ_TimeGetTime());
		pClient->SetId(iID);
		pClient->SetInWaiteList();
	}
	return;
}

bool LoginServer::AcceptNewClient()
{
//#ifdef _DEBUG
//    LogMessage::LogLogicInfo( "OneAcceptNewClient--", m_iOnlineNum, theCfg.playerMaxOnlineCount );
//#endif
    //������������
    //if( GetOnlineNum() >= theCfg.playerMaxOnlineCount )
    //{
    //    LogMessage::LogSystemInfo( "GateServer Accept���� [%d] �Ѿ��ﵽ����[%d]", m_iOnlineNum, theCfg.playerMaxOnlineCount );
    //    LogMessage::LogLogicError( "GateServer Accept���� [%d] �Ѿ��ﵽ����[%d]", m_iOnlineNum, theCfg.playerMaxOnlineCount );
    //    return false;
    //}

    // �ӳ����ٶ��й���
    float fUsed = (float)(m_pClientWaitClose->GetUsed()) / m_pClientWaitClose->GetSize();
    if( fUsed > WAITCLOSE_ALLOW_RATE )
    {
        /*LogMessage::LogSystemInfo( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );
        LogMessage::LogLogicError( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );*/
        return false;
    }

    Socketer* pSocket = NULL;
	pSocket = m_psockClientListen->Accept();
    if ( !pSocket )
    {        
        /*LogMessage::LogSystemError( "AcceptNewClient->CreateMeSocket Fail" );*/
        return false;
    }

    // �����������IP�����������������Ͽ�
    //in_addr addr;
    std::string strIP;
	char chip[20];
	pSocket->GetIP(chip,20);
	strIP = chip;

    GameObjectId iID = m_pNormalClients->Malloc();
    if ( InvalidGameObjectId == iID )
    {
        //LogMessage::LogLogicError("AcceptNewClient->MallocLoopID Fail");
        if ( pSocket )
        {
            pSocket->Close();
			Socketer_release(pSocket);
        }
        return false;
    }
    *(*m_pNormalClients)[iID] = NULL;

    CClientSession* pClient = new CClientSession;
    if( !pClient )
    {
        /*LogMessage::LogLogicError( "AcceptNewClient->new GamePlayer Fail" );*/
        if ( pSocket )
        {
            pSocket->Close();
			Socketer_release(pSocket);
        }

        if( InvalidGameObjectId != iID)
        {
            m_pNormalClients->Free(iID);
        }
		delete pClient;
        return false;
    }
    // ����CClientSession��
	pSocket->UseDecrypt();
	//pSocket->UseEncrypt();
	//pSocket->UseCompress();
    pClient->SetConnecter( pSocket);    
    pClient->SetConnect(HQ_TimeGetTime());

    *(*m_pNormalClients)[ iID ] = pClient;
	pClient->SetId(iID);
	pClient->SetInNormalList();

    IncreaseOnlineNum();
    return true;
}

void LoginServer::RecvAllClientMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CClientSession**ppChar = NULL,*pChar = NULL;

	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalClients->GetSize();
	iUsed = m_pNormalClients->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalClients->IsUsed(iLoopSize))
		{ continue; }

		ppChar = (*m_pNormalClients)[iLoopSize];
		if( !ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( !pChar )
		{ continue; }

		Socketer* pConnector = pChar->GetConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckRecv();
	}
}

//�������пͻ�����Ϣ
void LoginServer::SendAllClientMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CClientSession**ppChar = NULL,*pChar = NULL;
	
	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalClients->GetSize();
	iUsed = m_pNormalClients->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalClients->IsUsed(iLoopSize))
		{ continue; }

		ppChar = (*m_pNormalClients)[iLoopSize];
		if( !ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( !pChar )
		{ continue; }

		Socketer* pConnector = pChar->GetConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckSend();
	}

	//�ȴ�ɾ����Ҳ��Ҫ���͵�
	iSize = 0;
	iUsed = 0;
	iSize = m_pClientWaitClose->GetSize();
	iUsed = m_pClientWaitClose->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pClientWaitClose->IsUsed(iLoopSize))
		{ continue; }

		ppChar = (*m_pClientWaitClose)[iLoopSize];
		if( !ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( !pChar )
		{ continue; }

		Socketer* pConnector = pChar->GetConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckSend();
	}
}

void LoginServer::CloseAllClient()
{
	/*LogMessage::LogSystemInfo("GateServer�ر����пͻ���");*/

	int iLoopUsed,iLoopSize;
	int iUsed,iSize;

	CClientSession**ppChar = NULL,*pChar = NULL;

	iSize = m_pNormalClients->GetSize();
	iUsed = m_pNormalClients->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++ iLoopSize )
	{
		ppChar = (*m_pNormalClients)[ iLoopSize ];
		if( !ppChar )
			continue;
		iLoopUsed ++;

		pChar = *ppChar;
		AddToClientWaitClose( pChar, __FUNCTION__, __LINE__ );
	}
	m_onlinenum = 0;
}

CClientSession* LoginServer::GetClientById(int id)
{
	if (id < 0||!m_pNormalClients->IsUsed(id))	
	{
		return NULL;
	}
	return *((*m_pNormalClients)[id]);
}

bool LoginServer::CheckAccountResult(CClientSession* pClient, char* AccountName)
{
	if (!pClient||!AccountName)
	{
		return false;
	}
	if (strcmp(pClient->GetAccount(),AccountName) == 0)
	{
		return true;
	}
	return false;
}

void LoginServer::ProcessAllClientMsg()
{
#define PROCESS_ONE_CLIENT_MSG_NUM 3

	short i;
	CClientSession** ppChar = NULL, *pChar = NULL;
	int iSize = m_pNormalClients->GetSize();
	int iUsed = m_pNormalClients->GetUsed();
	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if ( !m_pNormalClients->IsUsed(iLoopSize) )
		{ continue; }

		ppChar = (*m_pNormalClients)[iLoopSize];
		if( !ppChar )
		{ continue; }

		++iLoopUsed;

		pChar = *ppChar;
		if( !pChar )
		{ continue; }

		//30S��ʱ
		if (pChar->IsOverTime(HQ_TimeGetTime(),30000))
		{
			AddToClientWaitClose( pChar, __FUNCTION__, __LINE__);
			continue;
		}

		Socketer* pConnector = pChar->GetConnecter();
		if ( !pConnector )
		{ continue; }

		// �Ƿ��Ѿ�����
		if (pConnector->IsClose())
		{
			AddToClientWaitClose( pChar, __FUNCTION__, __LINE__);
			continue;
		}
		Msg *pMsg;
		i = 0;
		while( pMsg = pConnector->GetMsg())
		{
			++i;
			switch( pMsg->GetType() )
			{
			case MSG_LOGIN_ACCOUNTINFO:
				{
					OnMsgProcessAccountInfo(pMsg,pChar);
				}
				break;
			case MSG_PASSWORDCARDACK:
				{
					OnMsgProcessPassWordCard(pMsg,pChar);
				}
				break;
			default:
				break;
			}
			if (PROCESS_ONE_CLIENT_MSG_NUM <= i)
				break;
		}
	}
}

void LoginServer::AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine )
{
	if ( !pServer||!pServer->IsInNormalList())
	{ return; }

	if ( InvalidGameObjectId != pServer->GetId())
	{
		m_pNormalServers->Free(pServer->GetId());
	}

	// ���뵽�ȴ�����
	GameObjectId iID = m_pServerWaitClose->Malloc();
	if( InvalidGameObjectId == iID )
	{	
		delete pServer;
	}
	else
	{
		*(*m_pServerWaitClose)[ iID ] = pServer;
		pServer->SetCloseTime(HQ_TimeGetTime());
		pServer->SetId(iID);
		pServer->SetInWaiteList();
	}
	return;
}
void LoginServer::CheckServerWaitClose( bool bWait )
{
	// ��������رյ�socket�Ƿ�ر����
	CServerSession** ppServer  = NULL;
	CServerSession*  pServer   = NULL;

	int iSize = m_pServerWaitClose->GetSize();
	int iUsed = m_pServerWaitClose->GetUsed();

	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++iLoopSize )
	{
		ppServer = (*m_pServerWaitClose)[ iLoopSize ];
		if(  NULL == ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( NULL == pServer)
		{ continue; }

		Socketer* pConnector =  pServer->GetIConnecter();
		if ( NULL == pConnector )
		{ continue; }

		// �ͷż���
		if( pServer->CanClose(HQ_TimeGetTime()) || !bWait )
		{
			pConnector->Close();
			// ɾ��
			m_pServerWaitClose->Free( iLoopSize );
			delete pServer;
		}
	}
}

void LoginServer::RunClient()
{
	//////////////////////////////////////////////////////////////////////////
	//BEGIN_TIME_TEST( "client accept" )    
	int iAccept = 0;
	const int iAcceptMax = 10;    
	while(m_psockClientListen->CanAccept() && iAccept < iAcceptMax&& IsInService())
	{ //���ܿͻ��˵�����
		if ( !AcceptNewClient())
		{   
			break;
		}
		iAccept ++;
	}
	//END_TIME_TEST( "client accept" )
	//////////////////////////////////////////////////////////////////////////
	//BEGIN_TIME_TEST( "client resv" )
	RecvAllClientMsg(); // ���տͻ�����Ϣ������Ϣ
	//END_TIME_TEST( "client resv" )
	//////////////////////////////////////////////////////////////////////////
	//BEGIN_TIME_TEST( "client process" )    
	ProcessAllClientMsg(); // ת���ͻ�����Ϣ��GameServer
	//END_TIME_TEST( "client process" )
	//////////////////////////////////////////////////////////////////////////	
	CheckClientWaitClose();
	//////////////////////////////////////////////////////////////////////////
	//BEGIN_TIME_TEST( "client send" )
	SendAllClientMsg(); // ���Ϳͻ�����Ϣ������Ϣ
	//END_TIME_TEST( "client send" )
	//////////////////////////////////////////////////////////////////////////
}

bool LoginServer::AcceptNewServer()
{
	// �ӳ����ٶ��й���
	float fUsed = (float)(m_pServerWaitClose->GetUsed()) / m_pServerWaitClose->GetSize();
	if( fUsed > WAITCLOSE_ALLOW_RATE )
	{
		/*LogMessage::LogSystemInfo( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );
		LogMessage::LogLogicError( "�ӳ����ٶ��й��� Rate[%f:%f]", fUsed, WAITCLOSE_ALLOW_RATE );*/
		return false;
	}

	Socketer* pSocket = NULL;
	pSocket = m_pListenServer->Accept();
	if ( !pSocket )
	{        
		/*LogMessage::LogSystemError( "AcceptNewServer->CreateMeSocket Fail" );*/
		return false;
	}

	// �����������IP�����������������Ͽ�
	//in_addr addr;
	std::string strIP;
	char chip[20];
	pSocket->GetIP(chip,20);
	strIP = chip;
	/////////////////////////////////////////////
	GameObjectId iID = m_pNormalServers->Malloc();
	if ( InvalidGameObjectId == iID )
	{
		/*LogMessage::LogLogicError("AcceptNewClient->MallocLoopID Fail");*/
		if ( pSocket )
		{
			pSocket->Close();
			Socketer_release(pSocket);
		}
		return false;
	}
	*(*m_pNormalServers)[iID] = NULL;

	CServerSession* pServer = new CServerSession;
	if( !pServer )
	{
		/*LogMessage::LogLogicError( "AcceptNewClient->new GamePlayer Fail" );*/
		if ( pSocket )
		{
			pSocket->Close();
			Socketer_release(pSocket);
		}

		if( InvalidGameObjectId != iID)
		{
			m_pNormalServers->Free(iID);
		}
		delete pServer;
		return false;
	}
	// ����
	pServer->SetIConnecter(pSocket);
	pServer->SetConnect(HQ_TimeGetTime());

	*(*m_pNormalServers)[ iID ] = pServer;
	pServer->SetId(iID);
	pServer->SetInNormalList();

	return true;
}

void LoginServer::ProcessAllServerMsg()
{
#define PROCESS_ONE_SERVER_MSG_NUM 50

	short i;
	CServerSession** ppServer = NULL, *pServer = NULL;
	int iSize = m_pNormalServers->GetSize();
	int iUsed = m_pNormalServers->GetUsed();
	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if ( !m_pNormalServers->IsUsed(iLoopSize) )
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }	

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }

		// �Ƿ��Ѿ�����
		if (pConnector->IsClose())
		{			
			AddToServerWaitClose( pServer, __FUNCTION__, __LINE__);
			continue;
		}
		Msg *pMsg;
		i = 0;
		while( pMsg = pConnector->GetMsg())
		{
			switch(pMsg->GetType())
			{
			case S2S_SWITCHGATE:
				OnMsgSwitchGate(pMsg);
				break;
			case MSG_PINGSERVER:
				OnMsgPing(pMsg,pServer);
				break;
			case CS2LS_LOGIN_ERROR:
				OnMsgLoginError(pMsg);
				break;
			case S2S_SHUTDOWNSERVER:
				OnMsgShutdownServer(pMsg);
				break;
			case S2S_BlockAccount:
				OnMsgBlockAccount(pMsg);
				break;
			case S2S_BlockMacAddress:
				OnMsgBlockMac(pMsg);
				break;
			default:
				break;
			}
			++i;
			if (PROCESS_ONE_SERVER_MSG_NUM <= i)
				break;
		}
	}
}

void LoginServer::SendAllServerMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CServerSession**ppServer = NULL,*pServer = NULL;

	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalServers->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckSend();
	}
}

void LoginServer::RecvAllServerMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CServerSession**ppServer = NULL,*pServer = NULL;

	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalServers->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckRecv();
	}
}

void LoginServer::CloseAllServer()
{
	/*LogMessage::LogSystemInfo("GateServer�ر����з�����");*/

	int iLoopUsed,iLoopSize;
	int iUsed,iSize;

	CServerSession**ppServer = NULL,*pServer = NULL;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++ iLoopSize )
	{
		ppServer = (*m_pNormalServers)[ iLoopSize ];
		if( !ppServer )
			continue;
		iLoopUsed ++;

		pServer = *ppServer;
		AddToServerWaitClose( pServer, __FUNCTION__, __LINE__ );
	}
}

void LoginServer::RunServer()
{
	int acceptnum = 0;
	const int acceptmax = 5;
	while( m_pListenServer->CanAccept() && acceptnum < acceptmax )
	{
		AcceptNewServer();
		acceptnum++;
	}

	RecvAllServerMsg();
	ProcessAllServerMsg();
	CheckServerWaitClose();
	SendAllServerMsg();
}

bool LoginServer::PushResult(/*const*/ SAckCheckAccount* pTask)
{
	if (!pTask)
	{
		return false;
	}
	CSALocker lock(&_ResultQuerysLock);
	_ResultQuerys.push_back(pTask);
	return true;
}

SAckCheckAccount* LoginServer::GetResultQueryMessage( /*SAckCheckAccount& rMessage*/ )
{
	CSALocker lock(&_ResultQuerysLock);
	if ( _ResultQuerys.empty())
	{ return NULL;}

	SAckCheckAccount* rMessage = _ResultQuerys.front();
	_ResultQuerys.pop_front();
	return rMessage;
}


void LoginServer::ProcessResultMySql()
{
	SqlMessageContainerResultCheck  sqlMessages;
	{
		CSALocker lock(&_ResultQuerysLock);
		if ( _ResultQuerys.empty() )
		{ return; }
		sqlMessages = _ResultQuerys;
		_ResultQuerys.clear();
	}

	ItrSqlMessageContainerResultCheck it = sqlMessages.begin();
	for ( ; it != sqlMessages.end(); ++it)
	{
		SAckCheckAccount* sqlMessage = *it;
		switch(sqlMessage->task_type)
		{
		case eAck_Check_Account:
			OnResultCheckAccount(sqlMessage);
			break;
		default:
			break;
		}
	}
}

void LoginServer::OnResultCheckAccount(SAckCheckAccount* pTask)
{
	if (!pTask)
	{
		return;
	}
	/*SAckCheckAccount* pAck = (SAckCheckAccount*)pTask;
	if (!pAck)
	{
		return;
	}*/
	switch(pTask->result)
	{
	case eCheckResult_succ:
		{
			CClientSession* pClient = GetClientByAccountName(pTask->account_name);
			if (!pClient)
			{
				break;
			}
			/*pClient->SetAccountId(pTask->account_id);*/
			if (!AddClientByAccountID(pTask->account_id,pClient))
			{
				break;
			}
			//todo:���ͳɹ�Э���CENTER SERVER,�������Ժ��ٸ�client����
			pClient->SetSessionKey(HelperFunc::CreateID());
			MsgLoginInfo msg;
			msg.nAccountID = pClient->GetAccountId();
			strncpy_s( msg.szIP,       sizeof(msg.szIP ),    pClient->GetIP(),        sizeof(msg.szIP)-1)       ;
			strncpy_s( msg.szMac,       sizeof(msg.szMac ),    pClient->GetMacAdress(),        sizeof(msg.szMac)-1)       ;
			strncpy_s( msg.szAccount,       sizeof(msg.szAccount ),    pClient->GetAccount(),        sizeof(msg.szAccount)-1)       ;
			msg.isWallow = pTask->addictedstate;
			msg.SessionKey = pClient->GetSessionKey();
			SendMsgToAllServer(&msg);
			//printf("1,keylogin:send login info to center server:%d\n",HQ_TimeGetTime());
		}
		break;
	case eCheckResult_error_account:
	case eCheckResult_error_pwd:
	case eCheckResult_fail:
		{
			//todo:���ʹ���Э��
			CClientSession* pClient = GetClientByAccountName(pTask->account_name);
			if (pClient)
			{
				MsgAckLogin msg;
				msg.stErrorCode = MsgAckLogin::error_invaliduserorpass;
				pClient->SendMsg(&msg);
			}
		}
		break;
	}

	theAccountDBSession.ReleaseAckCheckAccountPool(pTask);
}
void LoginServer::OnMsgProcessPassWordCard(Msg* pMsg,CClientSession* pClient)
{
	if (!pMsg||!pClient)
	{
		return;
	}
	MsgPassWordCardAck* pAck = (MsgPassWordCardAck*)pMsg;
	if (!pAck)
	{
		return;
	}
	//���͵���Ӫȥ
	MsgPwdCardAck msg;
	msg.header.stID = pClient->GetId();
	pClient->GetPwdCardData(msg.content.PwdCardSerialNumber,msg.content.crA,msg.content.crB,msg.content.crC);
	strcpy_s(msg.content.account_name,17,pClient->GetAccount());
	strcpy_s(msg.content.A,PwdCardLength,pAck->A);
	strcpy_s(msg.content.B,PwdCardLength,pAck->B);
	strcpy_s(msg.content.C,PwdCardLength,pAck->C);
	strncpy_s( msg.sign,sizeof(msg.sign),
		theAccountServer.GetMsgMd5Sign((void*)&(msg.content),sizeof(MsgPwdCardAck::SContent),(void*)theConfig.strKey.c_str(),16).c_str(),
		sizeof(msg.sign)-1);
	theAccountServer.SendMsgToAccountServer(&msg);
	return;
}
void LoginServer::OnMsgProcessAccountInfo(Msg* pMsg,CClientSession* pClient)
{
	if (!pMsg||!pClient)
	{
		return;
	}
	MsgLoginAccountInfo* pAccountInfo = (MsgLoginAccountInfo*)pMsg;
	if (!pAccountInfo)
	{
		return;
	}
//1,���ȼ��汾���Ƿ�ƥ��
	if (0 != strcmp(thApplication.GetFullVersion(),pAccountInfo->szFullVersion))
	{
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::error_invalidversion;
		pClient->SendMsg(&msg);
		return;
	}

//2,�ΰ汾��ƥ��
	if (VERSION_SECOND != pAccountInfo->nSecondVersion)
	{
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::error_invalidversion;
		pClient->SendMsg(&msg);
		return;
	}

//3,�����ʺ�����,������client����֤���õ��ʺ���
	static char account_name[20];
	static char pwds[20];
	
	memset(pwds,0,20);
	if (pAccountInfo->isEncryp)
	{
		if (!theSimpleCtyp.Decode(pAccountInfo->szAccount,32/*strlen(pAccountInfo->szAccount)*/,account_name)
			||!theSimpleCtyp.Decode(pAccountInfo->szPwds,32/*strlen(pAccountInfo->szPwds)*/,pwds))
		{
			MsgAckLogin msg;
			msg.stErrorCode = MsgAckLogin::ret_loginfail;
			pClient->SendMsg(&msg);
			return;
		}
	}
	else
	{
		return;
	}
//4,����˺�����û
	static int32 blocktime = 0;
	blocktime = theGLSService.CheckBlockAccount(account_name);
	if (blocktime > 0)
	{
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_blocked;
		msg.blocktime = blocktime;
		pClient->SendMsg(&msg);
		return;
	}
//5,���Mac����û
	static char scMac[MAC_LENGTH] ;
	memset(scMac,0,MAC_LENGTH);
	if (!theSimpleCtyp.Decode(pAccountInfo->szMac,32,scMac))
	{
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_loginfail;
		pClient->SendMsg(&msg);
		return;
	}

	// ���ڿͻ������ϸ��͵�����...����ļ�������ͨ��˵���ͻ����޸�������� ֱ�ӷ��
	bool bWrong = false;
	std::vector<std::string> vecMac = Common::_tstring::split(std::string(scMac),"-");
	if (vecMac.size() == 6)
	{
		for (int nn = 0; nn < 6; ++nn)//�������
		{
			if (bWrong) break;

			if (vecMac[nn].size()!=2){ bWrong = true; break; }
			for (int mm = 0; mm<2; ++mm)//���16����
			{
				if(!isxdigit(vecMac[nn].at(mm))){ bWrong = true; break; }
			}
		}
	}
	if (bWrong)
	{
		// ������˺�
		GLSService::SBlockInfo* pBlockInfo = new GLSService::SBlockInfo;
		pBlockInfo->begintime = theTimestamp.GetTimestamp();
		pBlockInfo->blocktime = 60*60*24;//24Сʱ
		pBlockInfo->guid = -1; //���ﻹ��֪�������˺�id ��-1
		strncpy_s( pBlockInfo->name, sizeof( pBlockInfo->name ), account_name, sizeof(pBlockInfo->name) - 1 );
		theGLSService.AddNewBlockInfoPublic(pBlockInfo);

		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_loginfail;
		pClient->SendMsg(&msg);
		return;
	}

	blocktime = theGLSService.CheckBlockUserMac(scMac);
	if (blocktime > 0)
	{
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_blocked;
		msg.blocktime = blocktime;
		pClient->SendMsg(&msg);
		return;
	}
	// ��Ӽ�¼
	if (!AddClientByAccountName(account_name,scMac,pClient))
	{
		return;
	}
	//6,����֤������ӵ�SQL������ƽ̨�Խӵ���֤������
	if (theConfig.UsingDB)
	{
		//��������������,Ӧ��SQL�Ƕ��̲߳���
		SReqCheckAccount* req = CreateReqCheckAccount();
		if (!req)
		{
			return;
		}
		//memcpy(req->account_name,account_name,16);
		//memcpy(req->passwords,pwds,14);
		strncpy_s( req->account_name,sizeof(req->account_name),account_name,sizeof(req->account_name)-1);
		strncpy_s( req->passwords,sizeof(req->passwords),pwds,sizeof(req->passwords)-1);
		theAccountDBSession.PushTask(req);
	}
	else
	{
		if (theAccountServer.IsInService())
		{
			MsgCheckAccount msg;
			msg.header.stID = pClient->GetId();
			memcpy(msg.content.account_name,account_name,17);
			memcpy(msg.content.pwds,pwds,14);
			/*strncpy_s( msg.content.account_name,sizeof(msg.content.account_name),account_name,sizeof(msg.content.account_name)-1);
			strncpy_s( msg.content.pwds,sizeof(msg.content.pwds),pwds,sizeof(msg.content.pwds)-1);*/
			/*		memcpy(msg.content.account_name,account_name,16);
			memcpy(msg.content.pwds,pwds,14);	*/	
			strncpy_s( msg.sign,sizeof(msg.sign),
				theAccountServer.GetMsgMd5Sign((void*)&(msg.content),sizeof(MsgCheckAccount::SContent),(void*)theConfig.strKey.c_str(),16).c_str(),
				sizeof(msg.sign)-1);		
			theAccountServer.SendMsgToAccountServer(&msg);

			//LogMessage::LogSystemError("account[%s] malloc[%d]", account_name,pClient->GetId());
		}
		else
		{
			MsgAckLogin msg;
			msg.stErrorCode = MsgAckLogin::ret_noservice;
			pClient->SendMsg(&msg);
		}
	}
}

void LoginServer::SendMsgToAllServer(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}

	CServerSession** ppServer = NULL, *pServer = NULL;
	int iSize = m_pNormalServers->GetSize();
	int iUsed = m_pNormalServers->GetUsed();
	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if ( !m_pNormalServers->IsUsed(iLoopSize) )
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }	

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }

		// �Ƿ��Ѿ�����
		if (pConnector->IsClose())
		{			
			AddToServerWaitClose( pServer, __FUNCTION__, __LINE__);
			continue;
		}
		pConnector->SendMsg(pMsg);
	}
}

void LoginServer::OnMsgSwitchGate(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}

	S2SSwitchGate* pMessage = (S2SSwitchGate*)pMsg;
	if (!pMessage)
	{
		return;
	}

	CClientSession* pClient = GetClientByAccountID(pMessage->nAccountId);
	if (pClient)
	{

		MsgAckLogin msg1;
		msg1.stErrorCode = MsgAckLogin::ret_succ;
		msg1.dwAccountID = pMessage->nAccountId;
		msg1.SessionKey = pClient->GetSessionKey();
		pClient->SendMsg(&msg1);

		MsgSwitchGate msg;
		msg.nResult = pMessage->nResult;
		msg.uGatePort = pMessage->uGatePort;
		memcpy(msg.szGateIP,pMessage->szGateIP,60*sizeof(char));
		memcpy(msg.szChannelName,pMessage->szChannelName,MAX_NAME_STRING*sizeof(char));
		msg.nServerType = pMessage->nServerType;
		pClient->SendMsg(&msg);
		//printf("8,keylogin:send to client switch gate:%d\n",HQ_TimeGetTime());
	}
}

void LoginServer::OnMsgLoginError(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	MsgLoginError* pError = (MsgLoginError*)pMsg;
	if (!pError)
	{
		return;
	}
	CClientSession* pClient = GetClientByAccountID(pError->uAccountId);
	if (pClient)
	{
		MsgAckLogin msg;
		if (pError->chErrorType == eLE_AccountInGame)
		{
			msg.stErrorCode = MsgAckLogin::ret_alreadyaloginthisaccount;
		}
		else if (pError->chErrorType == eLE_AccountServerFullLoad)
		{
			msg.stErrorCode = MsgAckLogin::ret_FullLoad;
		}
		else if (pError->chErrorType == eLE_AccountOverOneMac)
		{
			msg.stErrorCode = MsgAckLogin::ret_FullMac;
		}
		pClient->SendMsg(&msg);
	}
}

void LoginServer::OnMsgPing(Msg* pMsg,CServerSession* pServer)
{
	if (!pMsg||!pServer)
	{
		return;
	}
	pServer->SetConnect(HQ_TimeGetTime());
	pServer->SendMsg(pMsg);

	//printf("pingmsg:2,login server resv and send to center:%d\n",HQ_TimeGetTime());
}

void LoginServer::ReleaseReqCheckAccountPool(SReqCheckAccount* pTask)
{
	if (!pTask)
	{
		return;
	}
	CSALocker lock(&_ResultQuerysLock);
	ReleaseReqCheckAccount(pTask);
}

void LoginServer::OnMsgShutdownServer(Msg* pMsg)
{
	S2SShutdownServer* pShut = (S2SShutdownServer*)pMsg;
	if (!pShut)
	{
		return;
	}
	if ( ST_CenterServer != pShut->serverType)
	{ return; }
	SetService(false);
	COLOR_MESSAGE( COLOR_RED, "[����ֹͣ] \n" );
}

void LoginServer::OnMsgBlockAccount(Msg* pMsg)
{
	MsgS2SBlockAccount* pBlock = (MsgS2SBlockAccount*)pMsg;
	if (!pBlock)
	{
		return;
	}
	GLSService::SBlockInfo* pBlockInfo = new GLSService::SBlockInfo;
	pBlockInfo->begintime = theTimestamp.GetTimestamp();
	pBlockInfo->blocktime = pBlock->blocktime;
	pBlockInfo->guid = pBlock->guid;
	strncpy_s( pBlockInfo->name, sizeof( pBlockInfo->name ), pBlock->name, sizeof(pBlockInfo->name) - 1 );
	theGLSService.AddNewBlockInfoPublic(pBlockInfo);
}

void LoginServer::OnMsgBlockMac(Msg* pMsg)
{
	MsgS2SBlockMac* pBlock = (MsgS2SBlockMac*)pMsg;
	if (!pBlock)
	{
		return;
	}
	GLSService::SBlockInfoMac* pBlockInfoMac = new GLSService::SBlockInfoMac;
	pBlockInfoMac->begintime = theTimestamp.GetTimestamp();
	pBlockInfoMac->blocktime = pBlock->blocktime;
	strncpy_s( pBlockInfoMac->cMac, sizeof( pBlockInfoMac->cMac ), pBlock->scMac, sizeof(pBlockInfoMac->cMac) - 1 );
	theGLSService.AddNewBlockInfoMacPublic(pBlockInfoMac);
}

