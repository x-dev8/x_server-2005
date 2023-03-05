#pragma once

#include "ServerSession.h"
#include "ClientSession.h"
#include <map>
#ifdef WIN32
#include <hash_map>
using namespace stdext;
template<class _data >
class _string_hash:public hash_map<std::string, _data>
{

};
#endif

class CLoginInterface
{
public:
	CLoginInterface(void);
	~CLoginInterface(void);

	static CLoginInterface& Instance()
	{
		static CLoginInterface clif;
		return clif;
	}

	void Destry();

	bool InitLogin();

	static void StartThread();

	void RunOnce();
	void RunClient();
	void RunServer();

	Listener* GetClientListener(){return m_pListenClient;}
	Listener* GetServerListener(){return m_pListenServer;}

	unsigned long GetClientOverTime(){return m_client_overtime;}
	unsigned long GetServerOverTime(){return m_server_overtime;}

	void AcceptClientConnect();
	void RecvAllClientMsg();
	void ProcessAllClientMsg();
	void SendAllClientMsg();
	void CheckWaiteClientCloseList();

	void AcceptServerConnect();
	void RecvAllServerMsg();
	void ProcessAllServerMsg();
	void SendAllServerMsg();	
	void CheckWaiteServerCloseList();

	void SendMsgToAllServer(Msg* pMsg);
	void SendMsgToAllClient(Msg* pMsg);

	//增加到延时关闭队列中
	void AddClientWaiteList( CClientSession *client );
	void AddServerWaiteList( CServerSession *server );
	//移除客户端与账号的关联
	bool RemoveClient( const char *account );
	bool RemoveClientByAccountId( unsigned long accountid );
	bool FindClientInWaiteList( CClientSession *client );
	bool FindServerInWaiteList( CServerSession *server);

	CClientSession* FindClientSessionByAccountId(unsigned long acountid);

	////////////////////////////client////////////////////////
	void OnMsgClientLoginInfo(CClientSession* pClient,Msg* pMsg);
	
	///////////////////////////server//////////////////////////
	void OnMsgSwitchGate(Msg* pMsg);

private:
	typedef _string_hash<CClientSession*> AuthMap;
	typedef std::map<unsigned long,CClientSession*> mapClient;

	Listener* m_pListenClient;
	Listener* m_pListenServer;

	std::list<CClientSession*> m_clientlist;		//所有正常的客户端连接
	std::list<CClientSession*> m_waiteclose_clientlist;	//延时关闭的客户端连接
	unsigned long m_client_overtime;				//客户端的超时时间。硬性断开连接的时间

	std::list<CServerSession*> m_serverlist;		//所有正常的服务器连接
	std::list<CServerSession*> m_waiteclose_serverlist;	//延时关闭的服务器连接
	unsigned long m_server_overtime;				//服务器的超时时间。硬性断开连接的时间

	AuthMap m_account_map;					//玩家账号名与连接的映射
	mapClient m_mapClient;
};