#ifndef __MONSTER_GROUP_MANAGER_H__
#define __MONSTER_GROUP_MANAGER_H__

#include "GameTimer.h"
#include "Dxsdk/d3dx9math.h"


class AiCharacter;

// 一个怪物分组
class MonsterGroup
{
public:
	typedef unsigned short GroupID;
	typedef unsigned int MemberID;
	struct GroupMember
	{
		GroupMember() { pMonster = NULL; blArrivePos = true; }

		MemberID memberID;
		float fPosToLeaderX;
		float fPosToLeaderY;
		AiCharacter* pMonster;
		bool blArrivePos;
	};
	typedef std::vector< GroupMember >	MemberContainer;
	typedef MemberContainer::iterator	MemberContainerItr;

	enum EConstDefine
	{
		InvalidGroupID = 0,

		refresh_immediate = 0,
		refresh_normal,
	};

	GroupID GetGroupID() { return _groupID; }
	void SetGroupID( GroupID groupID ) { _groupID = groupID; }
	MemberID GetLeaderID() { return _leader.memberID; }
	void SetLeaderID( MemberID leaderID ) { _leader.memberID = leaderID; }
	unsigned int GetRefreshTime() { return _refreshTime; }
	void SetRefreshTime( unsigned int nRefreshTime ) { _refreshTime = nRefreshTime; }
	char GetRefreshType() { return _refreshType; }
	void SetRefreshType( char nRefreshType ) { _refreshType = nRefreshType; }
	MemberContainer& GetMemberContainer() { return _memberContainer; }

	bool InitGroup( AiCharacter* pLeader );
	void DelMember( AiCharacter* pMonster );
	bool IsLeader( AiCharacter* pMonster );
	void OnLeaderMoveToPos( D3DXVECTOR3 &posMoveTo );
	void SetArrivePos( AiCharacter* pMonster );
	bool IsAllMemberArrivePos();
	bool SetAndCheckAllMemberArrivePos( AiCharacter* pMonster );
	void RefreshMember();
	void MemberShareNewEnmityTarget( AiCharacter *pMonster, GameObjectId nTargetID );
	void AllMemberClearTargetEnmity( GameObjectId nTargetID );
	void StartRefreshTimer();
	bool IsRefreshTimerDone();
	bool IsLeaderDead() { return _leader.pMonster == NULL; }

	static D3DXVECTOR3 CalcPos( D3DXVECTOR3 &pos, float fDirX, float fDirY, float fPosToLeaderX, float fPosToLeaderY );

private:
	GroupID _groupID;
	GroupMember _leader;
	MemberContainer _memberContainer;
	unsigned int _refreshTime;
	char _refreshType;
	GameTimerEx _refreshTimer;
};

// 放在角色里用来封装分组逻辑的模块
class MonsterGroupLogic
{
public:
	typedef MonsterGroup::GroupID	GroupID;

	MonsterGroupLogic() { _pOwner = NULL; _pMonsterGroup = NULL; }
	void SetOwner( AiCharacter* pOwner ) { _pOwner = pOwner; }
	void SetGroup( MonsterGroup* pGroup ) { _pMonsterGroup = pGroup; }
	void OnCreateMonster( GroupID groupID, AiCharacter* pOwner );
	bool IsGroupLeader() { return _pMonsterGroup && _pMonsterGroup->IsLeader( _pOwner ); }
	bool CanMoveOn();
	void OnArrivePos();
	void OnMonsterMoveToPos( D3DXVECTOR3 &posMoveTo );
	void OnMemberLeaveFight();
	void OnNewEnmityTarget( GameObjectId nTargetID );
	void OnMonsterDie();
	void OnClearTargetEnmity( GameObjectId nTargetID );

private:
	AiCharacter* _pOwner;
	MonsterGroup* _pMonsterGroup;
};

// 分组管理器
class MonsterGroupManager
{
public:
	typedef MonsterGroup::GroupID	GroupID;
	typedef std::map< GroupID, MonsterGroup >	MonsterGroupContainer;
	typedef MonsterGroupContainer::iterator		MonsterGroupContainerItr;

public:
	static MonsterGroupManager& GetInstance();
	bool LoadConfig( char* szFileName );
	MonsterGroup* GetGroupByID( GroupID groupID );
	void Update();

private:
	MonsterGroupContainer _monsterGroupContainer;
};
#define theMonsterGroupManager MonsterGroupManager::GetInstance()

#endif