#ifndef __CAMPBATTLECONTROL_H__
#define __CAMPBATTLECONTROL_H__

/************************************************************************
                所有阵营战场管理
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

    // 注册一个战场管理
    void RegisterManager( CampBattleManager* xManager );

    // 获得一个战场管理
    //CampBattleManager* GetManager( unsigned char uchType );
	//获得一个战场管理，通过国家ID和战场类型
	CampBattleManager* GetManagerBytypeAndCountry( unsigned char uchType,int uchcountry = 0);

    // 初始化战场管理
    bool InitCampBattleManager();

    // 查找一个战场
	CampBattle* GetCampBattle( unsigned char uchFightCamp, unsigned int nMapID ,unsigned char countryid/* = CountryDefine::Country_Init*/);
    CampBattle* GetCampBattle( unsigned int nPlayerID );

    // 自动更新
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

    // 更新定时器
    GameTimerEx m_xUpdateTimer;
};

#endif