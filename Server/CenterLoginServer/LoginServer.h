#ifndef __CENTERSERVER_APPLICATION_H__
#define __CENTERSERVER_APPLICATION_H__

#pragma once
#include "ServerSession.h"
#include "ClientSession.h"
#include "WorkThread.h"
//#include "EventTimeTable.h"
#include "StaticArray.h"
#include "MySqlTaskDefine.h"
#include "MessageDefine.h"
#include "Mutex.h"
#include "objectpool.h"

#ifdef WIN32
#include <hash_map>
using namespace stdext;
template<class _data >
class _string_hash:public hash_map<std::string, _data>
{

};
#endif

//
#define REQ_CHECK_ACCOUNT_MAX 3000
//static poolmgr<SReqCheckAccount> &ReqCheckAccountPool ()
//{
//	static poolmgr<SReqCheckAccount> m(REQ_CHECK_ACCOUNT_MAX, "req check account pool");
//	return m;
//}
static SReqCheckAccount *CreateReqCheckAccount ()
{
	SReqCheckAccount *self = SReqCheckAccount::CreateInstance();
	if (!self)
	{		
		return NULL;
	}
	//self->SReqCheckAccount::SReqCheckAccount();
	return self;
}
static void ReleaseReqCheckAccount (SReqCheckAccount *self)
{
	if (!self)
		return;
	self->Release();
}

// ˢ��ʱ��Ϊ1����
#define LOGININFO_UPDATETIME_INTERVAL (1000 * 60)

// ��������ʱ��Ϊ10����
#define ALLOW_CONNECT_GATESERVER_TIME (1000 * 60 *10)

typedef std::list<SAckCheckAccount*>         SqlMessageContainerResultCheck;
typedef SqlMessageContainerResultCheck::iterator ItrSqlMessageContainerResultCheck;

class ConsoleApplication;
class LoginServer 
{
public:
	LoginServer();
	~LoginServer();
	// ������
	long Init( ConsoleApplication* pOwner );
	static LoginServer& GetInstance()
	{
		static LoginServer cls;
		return cls;
	}
	//SqlService&   GetSqlService() { return _serviceSql; }
	static void SqlMain( void* pParam); 
	static void Main( void* pParam );
	long RunOnce();
	void SetService(bool b){m_bInService = b;}
	bool IsInService(){return m_bInService;}

	enum enumConStatus
	{    
		CS_TryConnect, // ��������
		CS_ReConnect,  // ��������
		CS_Connectted, // ���ӳɹ�
	};

	//void SendMsgToCenterServer( Msg *pMsg );
	//void TryConnectToCenterServer();

	int            IncreaseOnlineNum( int nCount = 1);

	void           AddToClientWaitClose( CClientSession* pClient, char* szFun, int nLine );// �ر��������ӵĿͻ���
	void           CheckClientWaitClose( bool bWait = true );
	//�Ƴ��ͻ������˺ŵĹ���
	bool		   RemoveClient( const char *account );
	bool		   RemoveClientByAccountId( unsigned long accountid );
	CClientSession* GetClientByAccountName(const char *account);
	CClientSession* GetClientByAccountID(unsigned long accountid);
	bool           AddClientByAccountName(const char *account,const char* cMac,CClientSession* pClient);
	bool           AddClientByAccountID(unsigned long accountid,CClientSession* pClient);

	void           AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine );//
	void           CheckServerWaitClose( bool bWait = true );
	CClientSession* GetClientById(int id);
	bool		   CheckAccountResult(CClientSession* pClient, char* AccountName);
	////////////////////////////////////////////////////////////////////
	//client network process
	void           RunClient();
	void           ProcessAllClientMsg();      // ����ͻ�����Ϣ	
	void           SendAllClientMsg();         // �������пͻ�����Ϣ
	void           RecvAllClientMsg();         // �������пͻ�����Ϣ
	bool           AcceptNewClient();          // �µĿͻ�������
	void           CloseAllClient();

	void           OnMsgProcessAccountInfo(Msg* pMsg,CClientSession* pClient);  //��һ�δ��汾�ź��ʺ����������֤
	void		   OnMsgProcessPassWordCard(Msg* pMsg,CClientSession* pClient);
	////////////////////////////////////////////////////////////////////
	//server network process
	void           RunServer();
	bool           AcceptNewServer();
	void           ProcessAllServerMsg();
	void           SendAllServerMsg();
	void           RecvAllServerMsg();
	void           CloseAllServer();
	void           SendMsgToAllServer(Msg* pMsg);
	
	void		   OnMsgSwitchGate(Msg* pMsg);
	void		   OnMsgPing(Msg* pMsg,CServerSession* pServer);
	void		   OnMsgLoginError(Msg* pMsg);
	void           OnMsgShutdownServer(Msg* pMsg);
	void		   OnMsgBlockAccount(Msg* pMsg);
	void		   OnMsgBlockMac(Msg* pMsg);
	////////////////////////////////////////////////////////////////////
	//mysql task
	bool		   PushResult(/*const */SAckCheckAccount* pTask);
	SAckCheckAccount*	   GetResultQueryMessage( /*SAckCheckAccount& rMessage*/);
	void           ProcessResultMySql();
	void           OnResultCheckAccount(SAckCheckAccount* pTask);
	void           ReleaseReqCheckAccountPool(SReqCheckAccount* pTask);

	//tool
	int			   GetOnLoginNum(){ return m_onlinenum; }//������ڵ�½������
	////////////////////////////////////////////////////////////////////
private:	
	ConsoleApplication*  _pOwner; 
	//SqlService           _serviceSql;
	
	static CWorkThread g_SqlServiceThread;
	static CWorkThread g_MainLogicThread;  
	//unsigned int _nCenterServerPing;
	//unsigned int m_nLastPingCenter;
	//int _iCenterServerConnectorState;
	//Socketer* _CenterServerConnector;  // CenterServer���� 

	typedef _string_hash<CClientSession*> AuthMap;
	typedef std::map<unsigned long,CClientSession*> mapClient;
	
	CStaticArray<CClientSession*>* m_pNormalClients;    // �����Ŀͻ�������,�ȴ��ʺ���֤���
	CStaticArray<CClientSession*>* m_pClientWaitClose;  // �ȴ��ӳ�ɾ���ͻ�������
	AuthMap                        m_account_map;		//����˺��������ӵ�ӳ��
	mapClient                      m_mapClient;
	int                            m_onlinenum;          //��������������
	

	Listener*                      m_psockClientListen;  //�ͻ��˼���
	Listener*                      m_pListenServer;      //����������

	CStaticArray<CServerSession*>* m_pNormalServers;    // �����ķ���������
	CStaticArray<CServerSession*>* m_pServerWaitClose;  // �ȴ��ӳ�ɾ������������

	SqlMessageContainerResultCheck  _ResultQuerys;     //������ض���
	CSemiAutoIntLock				_ResultQuerysLock;

	bool                            m_bInService;      //��¼�������Ƿ���,���δ�����򲻽����¿ͻ��˵�������

//private:
//	static LoginServer* pApplicationInstance;
};

inline int LoginServer::IncreaseOnlineNum( int nCount)
{
	int iCount = m_onlinenum + nCount;
	if ( iCount < 0)
	{ iCount = 0; }
	m_onlinenum = iCount;
	return m_onlinenum;
}

#define theCenterLoginServer LoginServer::GetInstance()

#endif // __CENTERSERVER_APPLICATION_H__
