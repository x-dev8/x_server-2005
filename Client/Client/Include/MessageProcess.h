#pragma once
#include "Me3d\Include.h"
#include "MessageDefine.h"
// 要注意超过40k的包
#define CLIENT_BUFFER_SIZE 1024 * 40

class CMessageProcess
{
public:
	CMessageProcess(void);
	virtual ~CMessageProcess(void);

	void UpdateMsg(); //GameMain中调用 更新所有消息的函数
	void SetEnterWorldQueue( bool b ){ isEnterWorldQueue = b; }

	void GameLoginMsg(Msg* pMsg);//登陆界面消息处理
private:
	void LoginErrorProcess();//错误处理
	void ProcessMsg();//暂时先全部放一起

	void SpecialMsg(Msg* pMsg);//特殊消息处理
	
	void GameCreateMsg(Msg* pMsg);//角色创建界面消息处理
	void GameSelectMsg(Msg* pMsg);//角色选择界面消息处理
	void GameMainMsg(Msg* pMsg);//游戏主循环消息处理
	bool InGameMsg(Msg* pMsg);//游戏中消息处理

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