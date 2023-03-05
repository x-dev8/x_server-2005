#ifndef __CAMPCOUNTRYBATTLE_H__
#define __CAMPCOUNTRYBATTLE_H__

/************************************************************************
        ����ս��( ������������ս, ��������ս, ��ȸ����ս )
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

    // ��ø��������
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

    // ֪ͨ��ҵ���������
    void TellBattleDeathCount( GamePlayer* pPlayer );

    // ����ʤ���İ���
    void ProcessCalcBattleWinGuild();

    // ���Ͱ���ս������Ϣ
    void SendCampBattlePlayerCountMessage();

	//zhuxincong ���Ͱ���ս������Ϣ
	void SendCampBattlePlayerCountMessagezxc();

    // ����Ƿ�ɱ����������
    void CheckKillAllCampBattlePlayer( GamePlayer* pPlayer );

	int nRedScore;
	int nBlueScore;
};

#endif