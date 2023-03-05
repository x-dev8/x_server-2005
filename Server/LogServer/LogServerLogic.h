#pragma once

#include "WorkThread.h"
#include "network.h"
#include "ServerSession.h"
#include "StaticArray.h"
#include "Mutex.h"
#include "LogMessager.h"

class LogServerLogic
{
public:
	LogServerLogic(void);
	~LogServerLogic(void);

	static LogServerLogic& Instance()
	{
		static LogServerLogic lslc;
		return lslc;
	}

	bool	Init();
	void	Run();

	static void MySqlMain( void* pParam); 
	static void Main( void* pParam );

	//
	void    RunServer();
	bool    AcceptNewServer();
	void	ProcessAllServerMsg();
	void	SendAllServerMsg();
	void	RecvAllServerMsg();
	void	CloseAllServer();
	void	SendMsgToAllServer(Msg* pMsg);
	void	AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine );
	void    CheckServerWaitClose( bool bWait = true);
	//
	void	DoTestLogMessage();
private:
	Listener*		m_pListenServer;      //����������
	CStaticArray<CServerSession*>* m_pNormalServers;    // �����ķ���������
	CStaticArray<CServerSession*>* m_pServerWaitClose;  // �ȴ��ӳ�ɾ������������

	static CWorkThread g_SqlServiceThread;
	static CWorkThread g_MainLogicThread;
};

#define theLogServerLogic LogServerLogic::Instance()