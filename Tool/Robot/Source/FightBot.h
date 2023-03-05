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

	virtual GameObjectId LockTarget();		//��������

	virtual PlayerInfo* GetLockPlayerInfo(GameObjectId shID);

	virtual void RandReqCharInfo(GameObjectId shID);

    int GetLastMapId(){ return LastMapId;}
    void SetLastMapId(int MapId){ LastMapId = MapId;}

	int     StrToInt( char *strPlayerName );							//��ȡ�ַ����е������������ַ���ת����luo.qin 3.28
	int	    GetCountry( char *strPlayerName );							//��ù��ҵ�ö��ֵluo.qin 3.28	
	bool	IsNotSameCountry(PlayerInfo &xpPlayer);						//ͨ���˺ŷֲ����ж��Ƿ��ǵжԷ�....��֪��������Ϸ�ܲ��ܴ�������Ӫ�Ľ�ɫluo.qin 3.28

protected:
	
	bool IsEnemyPlayer(PlayerInfo &xpPlayer);

    int LastMapId;
};



///////////////////////////////////////////////////////
