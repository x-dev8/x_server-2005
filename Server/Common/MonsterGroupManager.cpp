#include "MonsterGroupManager.h"
#include "MonsterCreater.h"
#include "AiCharacter.h"


void MonsterGroupLogic::OnCreateMonster( GroupID groupID, AiCharacter* pOwner )
{
	if ( NULL == pOwner || groupID == MonsterGroup::InvalidGroupID )
	{ return; }

	MonsterGroup* pGroup = theMonsterGroupManager.GetGroupByID( groupID );
	if ( pGroup && pGroup->IsLeader( pOwner )  )
	{
		pGroup->InitGroup( pOwner );
		_pMonsterGroup = pGroup;
		_pOwner = pOwner;
	}
}

void MonsterGroupLogic::OnMonsterMoveToPos( D3DXVECTOR3 &posMoveTo )
{
	if ( IsGroupLeader() )
	{ _pMonsterGroup->OnLeaderMoveToPos( posMoveTo ); }
}

bool MonsterGroupLogic::CanMoveOn()
{
	if ( IsGroupLeader() )
	{ return _pMonsterGroup->IsAllMemberArrivePos(); }
	return true;
}

void MonsterGroupLogic::OnArrivePos()
{
	if ( _pMonsterGroup )
	{
		_pMonsterGroup->SetArrivePos( _pOwner );

		if ( _pMonsterGroup && _pMonsterGroup->IsLeaderDead() )
		{ _pOwner->CharacterMurder(); }  //向客户端发送怪物退出消息，客户端删除怪物模型

		if ( IsGroupLeader() )
		{
			if ( _pMonsterGroup->GetRefreshType() == MonsterGroup::refresh_immediate )
			{
				_pMonsterGroup->RefreshMember();
			}
			else
			{
				_pMonsterGroup->StartRefreshTimer();
			}
		}
	}
}

void MonsterGroupLogic::OnMemberLeaveFight()
{
	if ( _pMonsterGroup && _pMonsterGroup->IsLeaderDead() )
	{ _pOwner->CharacterMurder(); }
}

void MonsterGroupLogic::OnMonsterDie()
{
	if ( _pMonsterGroup )
	{ _pMonsterGroup->DelMember( _pOwner ); }
}

void MonsterGroupLogic::OnNewEnmityTarget( GameObjectId nTargetID )
{
	if ( _pMonsterGroup )
	{ _pMonsterGroup->MemberShareNewEnmityTarget( _pOwner, nTargetID ); }
}

void MonsterGroupLogic::OnClearTargetEnmity( GameObjectId nTargetID )
{
	if ( _pMonsterGroup )
	{ _pMonsterGroup->AllMemberClearTargetEnmity( nTargetID ); }
}

MonsterGroupManager& MonsterGroupManager::GetInstance()
{
	static MonsterGroupManager instance;
	return instance;
}

bool MonsterGroupManager::LoadConfig( char* szFileName )
{
	if ( szFileName == NULL || szFileName[ 0 ] == 0 )
	{ return false; }

	MeXmlDocument xMeXml;
	if ( !xMeXml.LoadFile( szFileName, 1 ) )
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
	if ( pRoot == NULL )
	{ return false; }

	int nValue = 0;

	MeXmlElement* pMonsterGroup = pRoot->FirstChildElement( "MonsterGroup" );
	if ( NULL == pMonsterGroup )
	{ return false; }

	MeXmlElement* pGroup = pMonsterGroup->FirstChildElement( "Group" );
	while ( NULL != pGroup )
	{
		MonsterGroup group;

		if ( pGroup->Attribute( "GroupID", &nValue ) == NULL )
		{ return false; }
		group.SetGroupID( nValue );

		if ( pGroup->Attribute( "LeaderID", &nValue ) == NULL )
		{ return false; }
		group.SetLeaderID( nValue );

		if ( pGroup->Attribute( "RefreshType", &nValue ) == NULL )
		{ return false; }
		group.SetRefreshType( nValue );

		if ( pGroup->Attribute( "RefreshTime", &nValue ) == NULL )
		{ return false; }
		group.SetRefreshTime( nValue );

		MonsterGroupContainerItr itr = _monsterGroupContainer.insert( std::make_pair( group.GetGroupID(), group ) ).first;
		if ( itr == _monsterGroupContainer.end() )
		{ return false; }

		float fValue = 0.0f;
		MeXmlElement* pMember = pGroup->FirstChildElement( "Member" );
		while ( NULL != pMember )
		{
			MonsterGroup::GroupMember member;

			if ( pMember->Attribute( "MemberID", &nValue ) == NULL )
			{ return false; }
			member.memberID = static_cast< MonsterGroup::MemberID >( nValue );

			if ( pMember->Attribute( "PosToLeaderX", &fValue ) == NULL )
			{ return false; }
			member.fPosToLeaderX = fValue;

			if ( pMember->Attribute( "PosToLeaderY", &fValue ) == NULL )
			{ return false; }
			member.fPosToLeaderY = fValue;

			itr->second.GetMemberContainer().push_back( member );

			pMember = pMember->NextSiblingElement();
		}

		pGroup = pGroup->NextSiblingElement();
	}

	return true;
}

MonsterGroup* MonsterGroupManager::GetGroupByID( GroupID groupID )
{
	MonsterGroupContainerItr itr = _monsterGroupContainer.find( groupID );
	if ( itr == _monsterGroupContainer.end() )
	{ return NULL; }
	return &itr->second;
}

void MonsterGroupManager::Update()
{
	MonsterGroupContainerItr itr = _monsterGroupContainer.begin();
	for ( ; itr != _monsterGroupContainer.end(); ++itr )
	{
		if ( itr->second.IsRefreshTimerDone() )
		{ itr->second.RefreshMember(); }
	}
}

bool MonsterGroup::InitGroup( AiCharacter* pLeader )
{
	if ( NULL == pLeader )
	{ return false; }
	_leader.pMonster = pLeader;

	RefreshMember();
	return true;
}

void MonsterGroup::DelMember( AiCharacter* pMonster )
{
	if ( IsLeader(pMonster) )
	{
		_leader.pMonster = NULL;
	} 
	else
	{
		MemberContainerItr itr = _memberContainer.begin();
		for ( ; itr != _memberContainer.end(); ++itr )
		{
			if ( itr->pMonster == pMonster )
			{
				itr->pMonster = NULL;
				itr->blArrivePos = true;
			}
		}
	}
}

bool MonsterGroup::IsLeader( AiCharacter* pMonster )
{
	if ( NULL == pMonster )
	{ return false; }
	return pMonster->GetMonsterID() == GetLeaderID();
}

void MonsterGroup::OnLeaderMoveToPos( D3DXVECTOR3 &posMoveTo )
{
	MemberContainerItr itr = _memberContainer.begin();
	for ( ; itr != _memberContainer.end(); ++itr )
	{
		if ( itr->pMonster )
		{
			D3DXVECTOR3 distanceLeader( posMoveTo.x - _leader.pMonster->GetPos().x, posMoveTo.y - _leader.pMonster->GetPos().y, 0 ) ;
			float fDistanceLeader = D3DXVec3Length( &distanceLeader );
			if ( abs( fDistanceLeader - 0.0f ) < 0.1f )
			{ return; }
			D3DXVECTOR3 dir;
			D3DXVec3Normalize( &dir, &distanceLeader );
			D3DXVECTOR3 pos( CalcPos( posMoveTo, dir.x, dir.y,	itr->fPosToLeaderX, itr->fPosToLeaderY ) );
			D3DXVECTOR3 distanceSelf( pos.x - itr->pMonster->GetPos().x, pos.y - itr->pMonster->GetPos().y, 0 );
			float fDistanceSelf = D3DXVec3Length( &distanceSelf );
			if ( abs(fDistanceSelf) < 0.1f )
			{ return; }
			itr->pMonster->SetMoveTargetPoint( pos.x, pos.y, _leader.pMonster->GetPos().z );
			itr->pMonster->SetBornPoint( pos.x, pos.y, _leader.pMonster->GetPos().z );
			itr->pMonster->SetMoveSpeed( fDistanceSelf * _leader.pMonster->GetMoveSpeed() / fDistanceLeader );
			//itr->blArrivePos = false;
		}
	}
}

D3DXVECTOR3 MonsterGroup::CalcPos( D3DXVECTOR3 &pos, float fDirX, float fDirY, float fPosToLeaderX, float fPosToLeaderY )
{
	D3DXVECTOR3 frontDir( fDirX, fDirY, 0 );
	D3DXVECTOR3 rightDir( fDirY, - fDirX, 0 );
	return pos + frontDir * fPosToLeaderY + rightDir * fPosToLeaderX;
}

void MonsterGroup::RefreshMember()
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->pMonster )
		{
			itr->pMonster->GetMonsterGroupLogic().SetOwner( NULL );
			itr->pMonster->GetMonsterGroupLogic().SetGroup( NULL );
			itr->pMonster->CharacterMurder();
		}

		MonsterCreateData xCreateData;
		xCreateData.SetMonsterID( itr->memberID );
		xCreateData.SetCount( 1 );
		xCreateData.SetRadius( 0.0f );
		xCreateData.SetBodySize( 1.0f );
		D3DXVECTOR3 pos( MonsterGroup::CalcPos( _leader.pMonster->GetPos(), _leader.pMonster->GetDirX(), _leader.pMonster->GetDirY(), itr->fPosToLeaderX, itr->fPosToLeaderY ) );
		xCreateData.SetPostionX( pos.x );
		xCreateData.SetPostionY( pos.y );
		xCreateData.SetDirX( _leader.pMonster->GetDirX() );
		xCreateData.SetDirY( _leader.pMonster->GetDirY() );
		xCreateData.SetMapID( _leader.pMonster->GetMapID() );

		MonsterBaseEx* pMonster = MonsterCreater::CreateNormalMonster( xCreateData );
		if ( NULL == pMonster )
		{ continue;	}

		pMonster->SetAiStatus( AiDefine::ThinkingDoNothing );
		pMonster->SetBornPoint( pos.x, pos.y, 0 );
		itr->pMonster = pMonster;
		itr->blArrivePos = true;
		pMonster->GetMonsterGroupLogic().SetOwner( pMonster );
		pMonster->GetMonsterGroupLogic().SetGroup( this );
	}
}

bool MonsterGroup::IsAllMemberArrivePos()
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->blArrivePos == false )
		{ return false; }
	}
	return true;
}

void MonsterGroup::SetArrivePos( AiCharacter* pMonster )
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->pMonster == pMonster )
		{
			itr->blArrivePos = true;
			itr->pMonster->SetBornPoint( itr->pMonster->GetFloatX(), itr->pMonster->GetFloatY(), 0 );
		}
	}
}

bool MonsterGroup::SetAndCheckAllMemberArrivePos( AiCharacter* pMonster )
{
	bool blAllMemberArrivePos = true;
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->pMonster == pMonster )
		{ itr->blArrivePos = true; }
		blAllMemberArrivePos = itr->blArrivePos;
	}
	return blAllMemberArrivePos;
}

void MonsterGroup::MemberShareNewEnmityTarget( AiCharacter *pMonster, GameObjectId nTargetID )
{
	if ( ! IsLeader(pMonster) && ! IsLeaderDead() )
	{ _leader.pMonster->SetEnmity( nTargetID, _leader.pMonster->GetViewEnmity() ); }

	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->pMonster == pMonster || itr->pMonster == NULL )
		{ continue; }
		itr->pMonster->SetEnmity( nTargetID, itr->pMonster->GetViewEnmity() );
	}
}

void MonsterGroup::StartRefreshTimer()
{
	_refreshTimer.StartTimer( HQ_TimeGetTime(), _refreshTime );
}

bool MonsterGroup::IsRefreshTimerDone()
{
	return _refreshTimer.DoneTimer();
}

void MonsterGroup::AllMemberClearTargetEnmity( GameObjectId nTargetID )
{
	if ( ! IsLeaderDead() )
	{
		EnmityData *pEnmity = _leader.pMonster->GetEnmity( nTargetID );
		if ( pEnmity )
		{
			pEnmity->ClearEnmity();
			_leader.pMonster->ProcessClearEnmityResult( nTargetID );
		}
	}

	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->pMonster == NULL )
		{ continue; }
		EnmityData *pEnmity = itr->pMonster->GetEnmity( nTargetID );
		if ( pEnmity )
		{
			pEnmity->ClearEnmity();
			itr->pMonster->ProcessClearEnmityResult( nTargetID );
		}
	}
}
