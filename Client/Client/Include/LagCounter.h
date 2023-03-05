#pragma once
#include <windows.h>

//通过向服务器发送消息，
//接受返回得到延迟
class CLagCounter
{
	
	enum enumConst
	{
		const_iCounterInterval = 30000
	};
	enum enumStatus
	{
		STATUS_READY						//可以发送请求
		,STATUS_WAITACK
		,STATUS_IDLE
	};

	DWORD			m_dwLastCounterTime;
	int				m_iStatus;
	DWORD			m_dwSendReqTime;

	DWORD			m_dwLag;
public:
	CLagCounter(void);
	~CLagCounter(void);

	BOOL CanSendReq();
	//call after send req msg
	void SendReq();
	//call after recved ack-msg
	void RecvAck();
	DWORD GetLag();
};
