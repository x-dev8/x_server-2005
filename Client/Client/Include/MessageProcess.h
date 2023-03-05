#pragma once
#include "Me3d\Include.h"
#include "MessageDefine.h"
// Ҫע�ⳬ��40k�İ�
#define CLIENT_BUFFER_SIZE 1024 * 40

class CMessageProcess
{
public:
	CMessageProcess(void);
	virtual ~CMessageProcess(void);

	void UpdateMsg(); //GameMain�е��� ����������Ϣ�ĺ���
	void SetEnterWorldQueue( bool b ){ isEnterWorldQueue = b; }

	void GameLoginMsg(Msg* pMsg);//��½������Ϣ����
private:
	void LoginErrorProcess();//������
	void ProcessMsg();//��ʱ��ȫ����һ��

	void SpecialMsg(Msg* pMsg);//������Ϣ����
	
	void GameCreateMsg(Msg* pMsg);//��ɫ����������Ϣ����
	void GameSelectMsg(Msg* pMsg);//��ɫѡ�������Ϣ����
	void GameMainMsg(Msg* pMsg);//��Ϸ��ѭ����Ϣ����
	bool InGameMsg(Msg* pMsg);//��Ϸ����Ϣ����

	void GetNowTime(struct tm& nowtime);

private:
	bool isDisconnected;

	/*char szBuf[CLIENT_BUFFER_SIZE];*/

	bool isReadyEnterGame;
	bool isEnterWorld;
	bool isEnterWorldQueue;

	DWORD dwEnterWorldQueueStartTime;
	DWORD dwStartTime;

	MsgAckEnterWorld ackEnterWorld;
};

extern CMessageProcess g_MessageProcess;