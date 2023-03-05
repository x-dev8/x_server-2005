#pragma once

#include "network.h"
#include "AccountServerMsg.h"
#include "md5.h"

using namespace network;
class CAccountServer
{
public:
	enum ecs
	{
		ecs_tryconnect = 0,
		ecs_connected,
		ecs_max,
	};
public:
	CAccountServer(void);
	~CAccountServer(void);

	static CAccountServer& Instance()
	{
		static CAccountServer cas;
		return cas;
	}

	bool IsInService(){return _service;}

	string GetMsgMd5Sign(void* _input0,int _length0,void* _input1,int _length1);

	void Run();
	void ProcessAccountServerMsg();
	char TryConnectAccountServer();
	void ReciveAccountMsg();
	void SendAccountMsg();

	bool SendMsgToAccountServer(Msg* pMsg);

	void OnMsgCheckSucc(Msg* pMsg);
	void OnMsgCheckFail(Msg* pMsg);
	void OnMsgReqAuth(Msg* pMsg);
	void OnMsgBlockAccount(Msg* pMsg);
	void OnMsgPwdCardReq(Msg* pMsg);
	
	bool IsNeedReConnect();
	bool IsConnected(){return connect_state == ecs_connected;}
private:
	Socketer*		 m_socketer;
	char             connect_state;
	unsigned long    ping_time;        //����ping��ʱ��
	unsigned long    check_ping_time;  //���һ�μ��PINGͨ����ʱ��
	bool             _service;         //�����Ƿ���,��Ҫ��֤������
	unsigned long    connect_time;     //�������ӵ�ʱ��.�Ӹ���ʱ,���û�ɹ�,3S����һ��
};

#define theAccountServer CAccountServer::Instance()