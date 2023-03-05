//反外挂机制
#pragma once
#ifdef NPGUARD
#include "CSAuthMessage.h"
#include "NP/ggsrv30.h"
extern class GamePlayer;
class CSAuthManager
{
public:
	CSAuthManager();
	~CSAuthManager();
	static bool InitAllCSAuthManager();//初始化反外函数 GameServer初始化的时候
	static void CloseAllCSAuthManager();//关闭反怪物机制 GameServer关闭的时候
	bool InitPlayerCSAuth(GamePlayer* pPlayer);//当GamePlayer创建的时候
	void ClosePlayerCSAuth();
	void OnUpdate(GamePlayer* pPlayer);//更新函数 放在玩家的Run函数中 3分钟调用次
	bool SendCheckMsgToClient(GamePlayer* pPlayer);
	bool ReviceCheckMsgByClient(MsgCheckCSAuthAck* pMsg,GamePlayer* pPlayer);
private:
	CCSAuth3 csa;//反外挂的类 每个GamePlayer都有个 
	unsigned int m_NextUpdateTime;
};
#endif