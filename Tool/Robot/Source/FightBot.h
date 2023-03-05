#pragma once

#include "AttackBot.h"
class CFightBot : public CAttackBot
{
public:
	CFightBot();
	virtual ~CFightBot();

	virtual void PlayGame();
	virtual void InitPlayGame(UINT mapid = 0);

	virtual void PlayFight();

	virtual GameObjectId LockTarget();		//锁定人物

	virtual PlayerInfo* GetLockPlayerInfo(GameObjectId shID);

	virtual void RandReqCharInfo(GameObjectId shID);

    int GetLastMapId(){ return LastMapId;}
    void SetLastMapId(int MapId){ LastMapId = MapId;}

	int     StrToInt( char *strPlayerName );							//抽取字符串中的整数，并让字符串转整形luo.qin 3.28
	int	    GetCountry( char *strPlayerName );							//获得国家的枚举值luo.qin 3.28	
	bool	IsNotSameCountry(PlayerInfo &xpPlayer);						//通过账号分布来判断是否是敌对方....不知道现在游戏能不能创建无阵营的角色luo.qin 3.28

protected:
	
	bool IsEnemyPlayer(PlayerInfo &xpPlayer);

    int LastMapId;
};



///////////////////////////////////////////////////////
