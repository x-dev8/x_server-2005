#ifndef __CAMPGUILDBATTLE_H__
#define __CAMPGUILDBATTLE_H__

/************************************************************************
            帮派争夺战, 类似DOTA
            Filename:     CampGuildBattle.h 
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "CampBattle.h"
#include "Memory_Pool.h"
#include "MonsterBaseEx.h"
class CampGuildBattle : public CampBattle, INHERIT_POOL_PARAM( CampGuildBattle, 25 )
{
public:
    CampGuildBattle();
    virtual ~CampGuildBattle(){}

    virtual void Release();
    virtual void SendEnterCampBattleMessage();

    virtual void KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID );
	
	void SetGuildCampBattleTimeMap();
protected:
    virtual void ProcessChangeToEndStatus();

    virtual void ProcessCampBattleEnterStatus();
    virtual void ProcessCampBattleFightStatus();
    virtual void ProcessCampBattleResult( unsigned char uchFightCamp );
    virtual void ProcessChangeToFightStatus();

    void ProcessRefreshCampMonster();
    void ProcessRefreshNormalMonster();

	void ProcessBoss();

    void SendCampBattleResourceMessage();
    ////////////////////////////////////////////////////////////////////////////
    class RefreshIndex
    {
    public:
        RefreshIndex() : nRedIndex( 0 ), nBlueIndex( 0 ), nMaxRedIndex( 0 ), nMaxBlueIndex( 0 ){}

        int GetRedIndex() { return nRedIndex; }
        int GetBlueIndex() { return nBlueIndex; }
        int GetMaxRedIndex() { return nMaxRedIndex; }
        int GetMaxBlueIndex() { return nMaxBlueIndex; }

        void SetRedIndex( int nValue ) { nRedIndex = nValue; }
        void SetBlueIndex( int nValue ) { nBlueIndex = nValue; }
        void SetMaxRedIndex( int nValue ) { nMaxRedIndex = nValue; }
        void SetMaxBlueIndex( int nValue ) { nMaxBlueIndex = nValue; }
    private:
        int nRedIndex;
        int nMaxRedIndex;
        int nBlueIndex;
        int nMaxBlueIndex;
    };
    ////////////////////////////////////////////////////////////////////////////

private:
    GameTimerEx m_xRefreshTimer; // 刷怪定时器
	std::map<int,GameTimerEx> m_xNormalTimer ; // Normal怪刷新

    typedef std::map< int, RefreshIndex > RefreshIndexMap;
    typedef RefreshIndexMap::iterator RefreshIndexMapIter;
   
    RefreshIndexMap m_mapRefreshIndex; // 刷怪设定

	vector<GameObjectId> m_RedBarracks;
	MonsterBaseEx* m_RedBoss;
	vector<GameObjectId> m_BlueBarracks;
	MonsterBaseEx* m_BlueBoss;
	int m_RedBarracksDeadSum;
	int m_BlueBarracksDeadSum;
};

#endif