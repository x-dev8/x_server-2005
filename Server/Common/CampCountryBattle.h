#ifndef __CAMPCOUNTRYBATTLE_H__
#define __CAMPCOUNTRYBATTLE_H__

/************************************************************************
        国家战场( 包括国王争夺战, 青龙争夺战, 朱雀争夺战 )
        Filename:     CampCountryBattle.h 
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/

#include "CampBattle.h"
#include "Memory_Pool.h"

class CampCountryBattle : public CampBattle, INHERIT_POOL_PARAM( CampCountryBattle, 5 )
{
public:
    CampCountryBattle();
    virtual ~CampCountryBattle(){}

    virtual void Release();
    virtual void SendEnterCampBattleMessage();

    // 获得复活点索引
    virtual unsigned int GetReliveIndex( GamePlayer* pPlayer );

    virtual void ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill );

    virtual void ProcessBattlePlayerOutLine( GamePlayer* pPlayer );

    virtual void ProcessCampBattleFightStatus();
	
	int GetRedScore(){return nRedScore;}
	int GetBlueScore(){return nBlueScore;}
	void SetRedSocre(int nValue){nRedScore = nValue;}
	void SetBlueSocre(int nValue){nBlueScore = nValue;}
	
protected:
    virtual void ProcessCampBattleResult( unsigned char uchFightCamp );
    virtual void ProcessChangeToEndStatus();

    // 通知玩家的死亡次数
    void TellBattleDeathCount( GamePlayer* pPlayer );

    // 计算胜利的帮派
    void ProcessCalcBattleWinGuild();

    // 发送帮派战力的消息
    void SendCampBattlePlayerCountMessage();

	//zhuxincong 发送帮派战力的消息
	void SendCampBattlePlayerCountMessagezxc();

    // 检测是否杀光了所有人
    void CheckKillAllCampBattlePlayer( GamePlayer* pPlayer );

	int nRedScore;
	int nBlueScore;
};

#endif