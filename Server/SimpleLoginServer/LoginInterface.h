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

	//���ӵ���ʱ�رն�����
	void AddClientWaiteList( CClientSession *client );
	void AddServerWaiteList( CServerSession *server );
	//�Ƴ��ͻ������˺ŵĹ���
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

	std::list<CClientSession*> m_clientlist;		//���������Ŀͻ�������
	std::list<CClientSession*> m_waiteclose_clientlist;	//��ʱ�رյĿͻ�������
	unsigned long m_client_overtime;				//�ͻ��˵ĳ�ʱʱ�䡣Ӳ�ԶϿ����ӵ�ʱ��

	std::list<CServerSession*> m_serverlist;		//���������ķ���������
	std::list<CServerSession*> m_waiteclose_serverlist;	//��ʱ�رյķ���������
	unsigned long m_server_overtime;				//�������ĳ�ʱʱ�䡣Ӳ�ԶϿ����ӵ�ʱ��

	AuthMap m_account_map;					//����˺��������ӵ�ӳ��
	mapClient m_mapClient;
};