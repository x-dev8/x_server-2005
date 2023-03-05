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

// 刷新时间为1分钟
#define LOGININFO_UPDATETIME_INTERVAL (1000 * 60)

// 允许连接时间为10分钟
#define ALLOW_CONNECT_GATESERVER_TIME (1000 * 60 *10)

typedef std::list<SAckCheckAccount*>         SqlMessageContainerResultCheck;
typedef SqlMessageContainerResultCheck::iterator ItrSqlMessageContainerResultCheck;

class ConsoleApplication;
class LoginServer 
{
public:
	LoginServer();
	~LoginServer();
	// 主流程
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
		CS_TryConnect, // 尝试连接
		CS_ReConnect,  // 重新连接
		CS_Connectted, // 连接成功
	};

	//void SendMsgToCenterServer( Msg *pMsg );
	//void TryConnectToCenterServer();

	int            IncreaseOnlineNum( int nCount = 1);

	void           AddToClientWaitClose( CClientSession* pClient, char* szFun, int nLine );// 关闭正常连接的客户端
	void           CheckClientWaitClose( bool bWait = true );
	//移除客户端与账号的关联
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
	void           ProcessAllClientMsg();      // 处理客户端消息	
	void           SendAllClientMsg();         // 发送所有客户端消息
	void           RecvAllClientMsg();         // 发送所有客户端消息
	bool           AcceptNewClient();          // 新的客户端连接
	void           CloseAllClient();

	void           OnMsgProcessAccountInfo(Msg* pMsg,CClientSession* pClient);  //第一次带版本号和帐号密码过来验证
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
	int			   GetOnLoginNum(){ return m_onlinenum; }//获得正在登陆的人数
	////////////////////////////////////////////////////////////////////
private:	
	ConsoleApplication*  _pOwner; 
	//SqlService           _serviceSql;
	
	static CWorkThread g_SqlServiceThread;
	static CWorkThread g_MainLogicThread;  
	//unsigned int _nCenterServerPing;
	//unsigned int m_nLastPingCenter;
	//int _iCenterServerConnectorState;
	//Socketer* _CenterServerConnector;  // CenterServer连接 

	typedef _string_hash<CClientSession*> AuthMap;
	typedef std::map<unsigned long,CClientSession*> mapClient;
	
	CStaticArray<CClientSession*>* m_pNormalClients;    // 正常的客户端连接,等待帐号认证结果
	CStaticArray<CClientSession*>* m_pClientWaitClose;  // 等待延迟删除客户端连接
	AuthMap                        m_account_map;		//玩家账号名与连接的映射
	mapClient                      m_mapClient;
	int                            m_onlinenum;          //正常的连接数量
	

	Listener*                      m_psockClientListen;  //客户端监听
	Listener*                      m_pListenServer;      //服务器监听

	CStaticArray<CServerSession*>* m_pNormalServers;    // 正常的服务器连接
	CStaticArray<CServerSession*>* m_pServerWaitClose;  // 等待延迟删除服务器连接

	SqlMessageContainerResultCheck  _ResultQuerys;     //结果返回队列
	CSemiAutoIntLock				_ResultQuerysLock;

	bool                            m_bInService;      //登录服务器是否开启,如果未开启则不接受新客户端的新连接

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
