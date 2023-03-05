#pragma once
#include <windows.h>

//ͨ���������������Ϣ��
//���ܷ��صõ��ӳ�
class CLagCounter
{
	
	enum enumConst
	{
		const_iCounterInterval = 30000
	};
	enum enumStatus
	{
		STATUS_READY						//���Է�������
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
