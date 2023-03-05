#ifndef __CAMPBATTLECONTROL_H__
#define __CAMPBATTLECONTROL_H__

/************************************************************************
                ������Ӫս������
                Filename:     CampBattleControl.h 
                MaintenanceMan Mail: lori227@live.cn

************************************************************************/
#include <vector>
#include "Singleton.h"
#include "CampGuildBattleManager.h"
#include "CampCountryBattleManager.h"
#include "GameTimer.h"

#define theCampBattleControl CampBattleControl::Instance()

class CampBattleControl : public ISingletion< CampBattleControl >
{
public:
    CampBattleControl();
    ~CampBattleControl(){};

    // ע��һ��ս������
    void RegisterManager( CampBattleManager* xManager );

    // ���һ��ս������
    //CampBattleManager* GetManager( unsigned char uchType );
	//���һ��ս������ͨ������ID��ս������
	CampBattleManager* GetManagerBytypeAndCountry( unsigned char uchType,int uchcountry = 0);

    // ��ʼ��ս������
    bool InitCampBattleManager();

    // ����һ��ս��
	CampBattle* GetCampBattle( unsigned char uchFightCamp, unsigned int nMapID ,unsigned char countryid/* = CountryDefine::Country_Init*/);
    CampBattle* GetCampBattle( unsigned int nPlayerID );

    // �Զ�����
    void RunUpdate( unsigned int nCurrentTime );

protected:
    bool RegisterGuildBattleManger();
    bool RegisterKingBattleManger();
    bool RegisterDragonBattleManger();
    bool RegisterRosefinchBattleManger();
	bool RegisterGuildUnionBattleManger();
private:
    typedef std::vector< CampBattleManager* > CampBattleManagerVector;
    typedef CampBattleManagerVector::iterator CampBattleManagerVectorIter;

    CampBattleManagerVector m_vecManager;

    // ���¶�ʱ��
    GameTimerEx m_xUpdateTimer;
};

#endif