#include "LoginInterface.h"
#include "MessageDefine.h"
#include <assert.h>
#include "config/config_file.h"
#include <process.h>
#include "MeRTLibs.h"
#include "AccountDBSession.h"
#include "CenterGameMessage.h"


CLoginInterface::CLoginInterface(void)
{
	m_pListenClient = Listener_create();
	m_pListenServer = Listener_create();

	m_client_overtime = 60000;
	m_server_overtime = 15000;

	m_clientlist.clear();
	m_waiteclose_clientlist.clear();

	m_serverlist.clear();
	m_waiteclose_serverlist.clear();
}

CLoginInterface::~CLoginInterface(void)
{
	Destry();
}
void CLoginInterface::Destry()
{
	for( std::list<CClientSession*>::iterator itr = m_clientlist.begin(); itr != m_clientlist.end(); ++itr )
	{
		assert( !(*itr)->IsInUnknowList() );
		if( !(*itr)->IsInNormalList() )
			continue;
		delete (*itr);
	}
	m_clientlist.clear();
	for( std::list<CClientSession*>::iterator itr = m_waiteclose_clientlist.begin(); itr != m_waiteclose_clientlist.end(); ++itr )
	{
		assert( !(*itr)->IsInUnknowList() );
		if( !(*itr)->IsInWaiteCloseList() )
			continue;
		delete (*itr);
	}
	m_waiteclose_clientlist.clear();
	m_account_map.clear();
	m_mapClient.clear();

	//
	for( std::list<CServerSession*>::iterator itr = m_serverlist.begin(); itr != m_serverlist.end(); ++itr )
	{
		assert( !(*itr)->IsInUnknowList() );
		if( !(*itr)->IsInNormalList() )
			continue;
		delete (*itr);
	}
	m_serverlist.clear();
	for( std::list<CServerSession*>::iterator itr = m_waiteclose_serverlist.begin(); itr != m_waiteclose_serverlist.end(); ++itr )
	{
		assert( !(*itr)->IsInUnknowList() );
		if( !(*itr)->IsInWaiteCloseList() )
			continue;
		delete (*itr);
	}
	m_waiteclose_serverlist.clear();

	//
	if (m_pListenClient)
	{
		Listener_release(m_pListenClient);
		m_pListenClient = NULL;
	}

	if (m_pListenServer)
	{
		Listener_release(m_pListenServer);
		m_pListenServer = NULL;
	}
}

bool CLoginInterface::InitLogin()
{
	if (!m_pListenClient->Listen(CConfig::Instance().GetClientPort(), 5))
	{
		printf("listner client %d error!\n", CConfig::Instance().GetClientPort());
		return false;
	}
	if (!m_pListenServer->Listen(CConfig::Instance().GetServerPort(), 5))
	{
		printf("listner server %d error!\n", CConfig::Instance().GetServerPort());
		return false;
	}
	return true;
}

//移除客户端与账号的关联
bool CLoginInterface::RemoveClient( const char *account )
{
	assert(account);
	if( !account )
		return false;
	AuthMap::iterator itr = m_account_map.find(account);
	if( itr != m_account_map.end() )
	{
		m_account_map.erase(itr);
		return true;
	}
	return false;
}
bool CLoginInterface::RemoveClientByAccountId( unsigned long accountid )
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

//用于检测重复
bool CLoginInterface::FindClientInWaiteList( CClientSession *client )
{
	assert( client );
	for( std::list<CClientSession*>::iterator itr = m_waiteclose_clientlist.begin(); itr != m_waiteclose_clientlist.end(); ++itr )
	{
		if( client == (*itr) )
			return true;
	}
	return false;
}

bool CLoginInterface::FindServerInWaiteList( CServerSession *server)
{
	assert( server );
	for( std::list<CServerSession*>::iterator itr = m_waiteclose_serverlist.begin(); itr != m_waiteclose_serverlist.end(); ++itr )
	{
		if( server == (*itr) )
			return true;
	}
	return false;
}

CClientSession* CLoginInterface::FindClientSessionByAccountId(unsigned long acountid)
{
	if (acountid == 0xffff)
	{
		return NULL;
	}
	mapClient::iterator itr = m_mapClient.find(acountid);
	if (itr == m_mapClient.end())
	{
		return NULL;
	}

	return itr->second;
}

void CLoginInterface::AddClientWaiteList( CClientSession *client )
{
	assert(client);
	if( !client )
		return;
	if( client->IsInWaiteCloseList() )
		return;
	assert(!RemoveClient(client->GetAccount()));
	assert( !client->IsInWaiteCloseList() );
	RemoveClientByAccountId(client->GetAccountId());
	client->SetInWaiteList();
	assert( !FindClientInWaiteList(client) );

	client->SetAccount();
	client->SetCloseTime(timeGetTime());
	m_waiteclose_clientlist.push_back(client);
}

void CLoginInterface::AddServerWaiteList( CServerSession *server )
{
	assert(server);
	if( !server )
		return;
	if( server->IsInWaiteCloseList() )
		return;
	assert( !server->IsInWaiteCloseList() );
	server->SetInWaiteList();
	assert( !FindServerInWaiteList(server) );
	server->SetCloseTime(timeGetTime());
	m_waiteclose_serverlist.push_back(server);
}


static void thiread_ran( void *data )
{
	assert(data);
	CLoginInterface *account_con = (CLoginInterface*)data;
	unsigned long delay;
	while(1)
	{
		account_con->RunOnce();
		Sleep(1);
		/*g_currenttime = GetMillisecond();
		account_con->RunStep();
		delay = GetMillisecond() - g_currenttime;
		if(delay < EnumConstant::enum_login_server_delay_run_time)
			delay_delay(EnumConstant::enum_login_server_delay_run_time - delay);*/
	}
	account_con->Destry();
}

void CLoginInterface::StartThread()
{
	//开启逻辑线程
	_beginthread( thiread_ran, 0, &CLoginInterface::Instance() );
}

void CLoginInterface::RunOnce()
{
	net_run();

	if (!CAccountDBSession::Instance()._CheckState())
	{
		if (CAccountDBSession::Instance().GetWorkState() != CAccountDBSession::SS_Connected)
		{
			CAccountDBSession::Instance()._TryConnectToSqlDb();
			return;
		}
	}

	RunClient();
	RunServer();
}

void CLoginInterface::RunClient()
{
	int acceptnum = 0;
	const int acceptmax = 50;
	while( GetClientListener()->CanAccept() && acceptnum < acceptmax )
	{
		AcceptClientConnect();
		acceptnum++;
	}

	RecvAllClientMsg();
	ProcessAllClientMsg();
	CheckWaiteClientCloseList();
	SendAllClientMsg();
}

void CLoginInterface::AcceptClientConnect()
{
	Socketer* socke = GetClientListener()->Accept();
	if( !socke )
		return;
	CClientSession* pclient = new CClientSession;
	if( !pclient )
	{
		assert( false && "new CClientSession; return NULL! error!" );
		Socketer_release(socke);
		return;
	}
	pclient->SetConnecter(socke);
	char ip[64] = {0};
	pclient->GetConnecter()->GetIP(ip, sizeof(ip));
	pclient->SetConnect(timeGetTime());
	assert( pclient->GetConnecter() != NULL );
	pclient->SetInNormalList();
	m_clientlist.push_back( pclient );
}

void CLoginInterface::RecvAllClientMsg()
{
	for (std::list<CClientSession*>::iterator itr = m_clientlist.begin(); itr !=  m_clientlist.end(); ++itr)
	{
		(*itr)->GetConnecter()->CheckRecv();
	}
}

void CLoginInterface::ProcessAllClientMsg()
{
#define LOGIN_EVERY_ONE_FRAME_PROCESS_MSG_NUM 3
	short i;
	std::list<CClientSession*>::iterator tempitr;
	for( std::list<CClientSession*>::iterator itr = m_clientlist.begin(); itr != m_clientlist.end(); )
	{
		tempitr = itr;
		++itr;
		if( !(*tempitr)->IsInNormalList() )
		{
			m_clientlist.erase(tempitr);
			continue;
		}
		if( (*tempitr)->GetConnecter()->IsClose() )
		{
			if( RemoveClient( (*tempitr)->GetAccount() ) )
			{				
			}
			RemoveClientByAccountId((*tempitr)->GetAccountId());
			AddClientWaiteList( (*tempitr) );
			m_clientlist.erase(tempitr);
			continue;
		}
		if ((*tempitr)->IsOverTime(timeGetTime(), GetClientOverTime()))
		{
			if( RemoveClient( (*tempitr)->GetAccount() ) )
			{				
			}
			RemoveClientByAccountId((*tempitr)->GetAccountId());
			AddClientWaiteList( (*tempitr) );
			m_clientlist.erase(tempitr);
			continue;
		}
		Msg *pMsg;
		i = 0;
		while( pMsg = (*tempitr)->GetConnecter()->GetMsg() )
		{
			++i;
			switch( pMsg->GetType() )
			{
			case MSG_PING:
				{
					MsgPingMsg msgPing;
					(*tempitr)->SendMsg(&msgPing);
					(*tempitr)->SetConnect(timeGetTime());
				}
				break;
			case MSG_LOGININFO:
				{
					OnMsgClientLoginInfo((*tempitr),pMsg);
				}
				break;
			}
			if (LOGIN_EVERY_ONE_FRAME_PROCESS_MSG_NUM <= i)
				break;
		}
	}
}

void CLoginInterface::SendAllClientMsg()
{
	for (std::list<CClientSession*>::iterator itr = m_clientlist.begin(); itr != m_clientlist.end(); ++itr)
	{
		(*itr)->GetConnecter()->CheckSend();
	}
	for (std::list<CClientSession*>::iterator itr = m_waiteclose_clientlist.begin(); itr != m_waiteclose_clientlist.end(); ++itr)
	{
		(*itr)->GetConnecter()->CheckSend();
	}
}

void CLoginInterface::CheckWaiteClientCloseList()
{
	CClientSession *temp;
	while(1)
	{
		if(m_waiteclose_clientlist.empty())
			return;
		temp = m_waiteclose_clientlist.front();
		if( !temp->IsInWaiteCloseList() )
		{
			m_waiteclose_clientlist.pop_front();
			continue;
		}
		if( !temp->CanClose(timeGetTime()) )
			return;

		m_waiteclose_clientlist.pop_front();
		delete temp;
	}
}

void CLoginInterface::RunServer()
{
	int acceptnum = 0;
	const int acceptmax = 5;
	while( GetServerListener()->CanAccept() && acceptnum < acceptmax )
	{
		AcceptServerConnect();
		acceptnum++;
	}

	RecvAllServerMsg();
	ProcessAllServerMsg();
	CheckWaiteServerCloseList();
	SendAllServerMsg();
}

void CLoginInterface::AcceptServerConnect()
{
	Socketer* socke = GetServerListener()->Accept();
	if( !socke )
		return;
	CServerSession* pserver = new CServerSession;
	if( !pserver )
	{
		assert( false && "new CServerSession; return NULL! error!" );
		Socketer_release(socke);
		return;
	}
	pserver->SetIConnecter(socke);
	char ip[64] = {0};
	pserver->GetIConnecter()->GetIP(ip, sizeof(ip));
	pserver->SetConnect(timeGetTime());
	assert( pserver->GetIConnecter() != NULL );
	pserver->SetInNormalList();
	m_serverlist.push_back( pserver );
}

void CLoginInterface::RecvAllServerMsg()
{
	for (std::list<CServerSession*>::iterator itr = m_serverlist.begin(); itr !=  m_serverlist.end(); ++itr)
	{
		(*itr)->GetIConnecter()->CheckRecv();
	}
}

void CLoginInterface::ProcessAllServerMsg()
{
#define LOGIN_EVERY_ONE_FRAME_PROCESS_MSG_NUM 3
	short i;
	std::list<CServerSession*>::iterator tempitr;
	for( std::list<CServerSession*>::iterator itr = m_serverlist.begin(); itr != m_serverlist.end(); )
	{
		tempitr = itr;
		++itr;
		if( !(*tempitr)->IsInNormalList() )
		{
			m_serverlist.erase(tempitr);
			continue;
		}
		if( (*tempitr)->GetIConnecter()->IsClose() )
		{
			AddServerWaiteList( (*tempitr) );
			m_serverlist.erase(tempitr);
			continue;
		}
		if ((*tempitr)->IsOverTime(timeGetTime(), GetServerOverTime()))
		{
			AddServerWaiteList( (*tempitr) );
			m_serverlist.erase(tempitr);
			continue;
		}
		Msg *pMsg;
		i = 0;
		while( pMsg = (*tempitr)->GetIConnecter()->GetMsg() )
		{
			++i;
			switch( pMsg->GetType() )
			{
			case MSG_PING:
				{
					MsgPingMsg msgPing;
					(*tempitr)->SendMsg(&msgPing);
					(*tempitr)->SetConnect(timeGetTime());
				}
				break;
			case S2S_SWITCHGATE:
				OnMsgSwitchGate(pMsg);
				break;
			}
			if (LOGIN_EVERY_ONE_FRAME_PROCESS_MSG_NUM <= i)
				break;
		}
	}
}

void CLoginInterface::SendAllServerMsg()
{
	for (std::list<CServerSession*>::iterator itr = m_serverlist.begin(); itr != m_serverlist.end(); ++itr)
	{
		(*itr)->GetIConnecter()->CheckSend();
	}
	for (std::list<CServerSession*>::iterator itr = m_waiteclose_serverlist.begin(); itr != m_waiteclose_serverlist.end(); ++itr)
	{
		(*itr)->GetIConnecter()->CheckSend();
	}
}

void CLoginInterface::CheckWaiteServerCloseList()
{
	CServerSession *temp;
	while(1)
	{
		if(m_waiteclose_serverlist.empty())
			return;
		temp = m_waiteclose_serverlist.front();
		if( !temp->IsInWaiteCloseList() )
		{
			m_waiteclose_serverlist.pop_front();
			continue;
		}
		if( !temp->CanClose(timeGetTime()) )
			return;

		m_waiteclose_serverlist.pop_front();
		delete temp;
	}
}


void CLoginInterface::OnMsgClientLoginInfo(CClientSession* pClient,Msg* pMsg)
{
	if (!pClient||!pMsg)
	{
		return;
	}

	MsgLoginInfo* pLogin = (MsgLoginInfo*)pMsg;
	if (!pLogin)
	{
		return;
	}
	
	unsigned long accountid = CAccountDBSession::Instance().CheckAccount(pLogin->szAccount,pLogin->Password);
	if (accountid == 0xffffffff)
	{//帐号鉴证错误
		MsgAckLogin msg;
		msg.stErrorCode = MsgAckLogin::ret_loginfail;
		pClient->SendMsg(&msg);
	}
	else
	{//done,要跟其他服务器通讯，然后告之客户端
		pLogin->nAccountID = accountid;
		pClient->SetAccount(pLogin->szAccount,accountid);
		m_account_map.insert(std::make_pair(pClient->GetAccount(),pClient));
		m_mapClient.insert(std::make_pair(pClient->GetAccountId(),pClient));
		SendMsgToAllServer(pMsg);
	}
}

void CLoginInterface::SendMsgToAllServer(Msg* pMsg)
{
	for (std::list<CServerSession*>::iterator itr = m_serverlist.begin(); itr != m_serverlist.end(); ++itr)
	{
		(*itr)->SendMsg(pMsg);
	}
	for (std::list<CServerSession*>::iterator itr = m_waiteclose_serverlist.begin(); itr != m_waiteclose_serverlist.end(); ++itr)
	{
		(*itr)->SendMsg(pMsg);
	}
}

void CLoginInterface::SendMsgToAllClient(Msg* pMsg)
{
	for (std::list<CClientSession*>::iterator itr = m_clientlist.begin(); itr != m_clientlist.end(); ++itr)
	{
		(*itr)->SendMsg(pMsg);
	}
	for (std::list<CClientSession*>::iterator itr = m_waiteclose_clientlist.begin(); itr != m_waiteclose_clientlist.end(); ++itr)
	{
		(*itr)->SendMsg(pMsg);
	}
}

void CLoginInterface::OnMsgSwitchGate(Msg* pMsg)
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

	CClientSession* pClient = FindClientSessionByAccountId(pMessage->nAccountId);
	if (pClient)
	{

		MsgAckLogin msg1;
		msg1.stErrorCode = MsgAckLogin::ret_succ;
		msg1.dwAccountID = pMessage->nAccountId;
		/*msg.dwSessionKey = pMessage->nAccountId;*/
		pClient->SendMsg(&msg1);

		MsgSwitchGate msg;
		msg.nResult = pMessage->nResult;
		msg.uGatePort = pMessage->uGatePort;
		memcpy(msg.szGateIP,pMessage->szGateIP,60*sizeof(char));
		memcpy(msg.szChannelName,pMessage->szChannelName,MAX_NAME_STRING*sizeof(char));
		msg.nServerType = pMessage->nServerType;
		pClient->SendMsg(&msg);
	}
}