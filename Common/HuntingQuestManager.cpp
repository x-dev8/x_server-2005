#include "HuntingQuestManager.h"
#include "GlobalDef.h"
#include "QuestDefine.h"
#include "QuestManager.h"
#include "GamePlayer.h"
#include "GameServer.h"

HuntingQuestManager::HuntingQuestManager()
{
	//pOwner = 0;
	vecIds.resize( MaxCount_Show, 0 );
}

HuntingQuestManager::~HuntingQuestManager()
{
	vecIds.clear();
}

bool HuntingQuestManager::IsIdsFull( GamePlayer* pOwner )
{
	if ( !pOwner )
		return true;

	int nCount = 0;
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 )
			nCount++;
	}

	return nCount >= MaxCount_Show;
}

bool HuntingQuestManager::IsIdExist( int id )
{
	for (std::vector< int >::iterator it = vecIds.begin(); it != vecIds.end(); it++ )
	{
		if ( *it == id || !theQuestManager.IsQuestIdValid( id ) )
			return true;
	}

	return false;
}

bool HuntingQuestManager::IsGoldIdFull( HuntingQuestConfig::BaseVec& vecGoldQuest )
{
	for ( HuntingQuestConfig::BaseVec::iterator iter = vecGoldQuest.begin(); iter != vecGoldQuest.end(); iter++ )
	{
		if ( !IsIdExist( (*iter).nId ) )
			return false;
	}

	return true;
}

bool HuntingQuestManager::IsTypeIdFull( HuntingQuestConfig::TypeVec& vecTypeQuest )
{
	for ( HuntingQuestConfig::TypeVec::iterator iter = vecTypeQuest.begin(); iter != vecTypeQuest.end(); iter++ )
	{
		for ( HuntingQuestConfig::BaseVec::iterator it = (*iter).begin(); it != (*iter).end(); it++ )
		{
			if ( !IsIdExist( (*it).nId ) )
				return false;
		}
	}

	return true;
}

bool HuntingQuestManager::IsTypeQuestAllExist( int type, GamePlayer* pOwner )
{
	if ( !pOwner )
		return true;

	HuntingQuestConfig::TypeVec& vecTypeQuest = theHuntingQuestConfig.GetLevelTypeQuest( pOwner->GetLevel(), pOwner->GetCountryId() );
	if ( vecTypeQuest.size() <= 0 )
		return true;

	if ( type < 0 || type >= vecTypeQuest.size() )
		return true;

	for ( HuntingQuestConfig::BaseVec::iterator iter = vecTypeQuest[type].begin(); iter != vecTypeQuest[type].end(); iter++ )
	{
		if ( !IsIdExist( (*iter).nId ) )
			return false;
	}

	return true;
}

void HuntingQuestManager::AddOneQuest( int Index, HuntingQuestConfig::BaseVec& vecGoldQuest, HuntingQuestConfig::TypeVec& vecTypeQuest, int nProbability, GamePlayer* pOwner )
{
	if ( !pOwner )
		return;
	if ( Index < 0 || Index >= vecIds.size() )
		return;
	if ( vecGoldQuest.size() <= 0 || vecTypeQuest.size() <= 0 )
		return;

	if ( pOwner->IsQuestActive( vecIds[Index] ) )
		return;

	int nType = theRand.rand16() % vecGoldQuest.size();

	int nRandNum = theRand.rand32() % RAND_THOUSAND;
	if ( nProbability >= nRandNum )
	{
		while ( IsIdExist( vecGoldQuest[nType].nId ) && !IsGoldIdFull( vecGoldQuest ) )
		{
			nType = theRand.rand16() % vecGoldQuest.size();
		}

		if ( IsGoldIdFull( vecGoldQuest ) && !IsTypeIdFull( vecTypeQuest ) )
		{
			while ( IsTypeQuestAllExist( nType, pOwner ) )
			{
				nType = theRand.rand16() % vecGoldQuest.size();
			}

			if ( nType >= 0 && nType < vecTypeQuest.size() && vecTypeQuest[nType].size() > 0 )
			{
				int nQuality = theRand.rand16() % vecTypeQuest[nType].size();

				while( IsIdExist( vecTypeQuest[nType][nQuality].nId ) )
				{
					nQuality = theRand.rand16() % vecTypeQuest[nType].size();
				}

				vecIds[Index] = vecTypeQuest[nType][nQuality].nId;
			}
		}
		else
		{
			if ( !IsGoldIdFull( vecGoldQuest ) )
				vecIds[Index] = vecGoldQuest[nType].nId;
		}
	}
	else
	{
		if ( IsTypeIdFull( vecTypeQuest ) )
			return;

		while ( IsTypeQuestAllExist( nType, pOwner ) )
		{
			nType = theRand.rand16() % vecGoldQuest.size();
		}

		if ( nType >= 0 && nType < vecTypeQuest.size() && vecTypeQuest[nType].size() > 0 )
		{
			int nQuality = theRand.rand16() % vecTypeQuest[nType].size();

			while( IsIdExist( vecTypeQuest[nType][nQuality].nId ) )
			{
				nQuality = theRand.rand16() % vecTypeQuest[nType].size();
			}

			vecIds[Index] = vecTypeQuest[nType][nQuality].nId;
		}
	}
}

void HuntingQuestManager::ReFreshQuest( GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	int nCount = 0;
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 )
		{
			if ( pOwner->IsQuestActive( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] ) )
				vecIds[nCount] = pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i];
			else
				vecIds[nCount] = 0;

			nCount++;
		}

		if ( nCount == MaxCount_Show )
			break;
	}

	HuntingQuestConfig::BaseVec& vecGoldQuest = theHuntingQuestConfig.GetLevelGoldQuest( pOwner->GetLevel(), pOwner->GetCountryId() );
	if ( vecGoldQuest.size() <= 0 )
		return;

	HuntingQuestConfig::TypeVec& vecTypeQuest = theHuntingQuestConfig.GetLevelTypeQuest( pOwner->GetLevel(), pOwner->GetCountryId() );
	if ( vecTypeQuest.size() <= 0 )
		return;

	int typeQuestCount = 0;
	for ( HuntingQuestConfig::TypeVec::iterator iter = vecTypeQuest.begin(); iter != vecTypeQuest.end(); iter++ )
	{
		typeQuestCount += (*iter).size();
	}

	int nProbability = (int) theHuntingQuestConfig.GetGoldProbability() * 10;

	int nSize = vecIds.size() <= typeQuestCount ? vecIds.size() : typeQuestCount;
	for (int i = 0; i < /*vecIds.size()*/nSize; i++ )
	{
		AddOneQuest( i, vecGoldQuest, vecTypeQuest, nProbability, pOwner );
	}

	//std::sort( vecIds.begin(), vecIds.end(), HuntingQuestManager::SortByLevel );
	//std::sort( vecIds.begin(), vecIds.end(), HuntingQuestManager::SortByAccept );

	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] = 0;
	}

	int j = 0;
	for (std::vector< int >::iterator it = vecIds.begin(); it != vecIds.end() && j < More_nHuntingNum; it++, j++ )
	{
		pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[j] = *it;
	}
}

void HuntingQuestManager::CheckQuest( GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	for (std::vector< int >::iterator it = vecIds.begin(); it != vecIds.end(); it++ )
	{
		 *it = 0;
	}

	int nCount = 0;
	for ( int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 )
		{
			vecIds[nCount] =  pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i];
			nCount++;
		}

		if ( nCount == MaxCount_Show )
			break;
	}

	HuntingQuestConfig::BaseVec& vecGoldQuest = theHuntingQuestConfig.GetLevelGoldQuest( pOwner->GetLevel(), pOwner->GetCountryId() );
	if ( vecGoldQuest.size() <= 0 )
		return;

	HuntingQuestConfig::TypeVec& vecTypeQuest = theHuntingQuestConfig.GetLevelTypeQuest( pOwner->GetLevel(), pOwner->GetCountryId() );
	if ( vecTypeQuest.size() <= 0 )
		return;

	int nProbability = (int) theHuntingQuestConfig.GetGoldProbability() * 10;

	int typeQuestCount = 0;
	for ( HuntingQuestConfig::TypeVec::iterator iter = vecTypeQuest.begin(); iter != vecTypeQuest.end(); iter++ )
	{
		typeQuestCount += (*iter).size();
	}

	int nSize = vecIds.size() <= typeQuestCount ? vecIds.size() : typeQuestCount;
	for (int i = 0; i < /*vecIds.size()*/nSize; i++ )
	{
		if ( vecIds[i] == 0 )
			AddOneQuest( i, vecGoldQuest, vecTypeQuest, nProbability, pOwner );
	}

	//std::sort( vecIds.begin(), vecIds.end(), HuntingQuestManager::SortByLevel );
	//std::sort( vecIds.begin(), vecIds.end(), HuntingQuestManager::SortByAccept );

	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] = 0;
	}

	int j = 0;
	for (std::vector< int >::iterator it = vecIds.begin(); it != vecIds.end() && j < More_nHuntingNum; it++, j++ )
	{
		pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[j] = *it;
	}
}

void HuntingQuestManager::SendQuestList( GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	MsgHuntingQuestList msg;

	CheckQuest( pOwner );

	int nCount = 0;
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 )
		{
			msg.nIds[nCount] =  pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i];
			nCount++;
		}

		if ( nCount == MaxCount_Show )
			break;
	}

	msg.dwTime = pOwner->gCharInfoServer.otherdata.sHunting.dFreeRefreshTime;
	msg.nCount = pOwner->gCharInfoServer.otherdata.sHunting.nCount;

	DWORD dwCurTime = HQ_TimeGetTime();
	DWORD leftTime = 0;

	if ( dwCurTime >= msg.dwTime )
		leftTime = ( dwCurTime - msg.dwTime ) / 1000;
	else
		leftTime = ( msg.dwTime - dwCurTime ) / 1000;

	if ( leftTime < theHuntingQuestConfig.GetFreshTime() )
		msg.nLeftTime = theHuntingQuestConfig.GetFreshTime() - leftTime;

	GettheServer().SendMsgToSingle( &msg, pOwner );
}

void HuntingQuestManager::AcceptQuest( int nId, GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	bool bIdExist = false;
	for ( int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 
			&& pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] == nId )
		{
			bIdExist = true;
		}
	}

	if ( !bIdExist )
		return;

	if ( !theQuestManager.IsQuestIdValid( nId ) )
		return;

	//添加任务 调用脚本
	CScriptMgr::JoinQuestScript( pOwner, nId );
}

void HuntingQuestManager::DoneQuest( int nId, GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	bool bIdExist = false;
	for ( int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 
			&& pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] == nId )
		{
			pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] = 0;
			bIdExist = true;
		}
	}

	if ( !bIdExist )
		return;

	SendQuestList( pOwner );
}

void HuntingQuestManager::PassOneDay( GamePlayer* pOwner )
{
	if ( !pOwner )
		return;

	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		/*if ( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] > 0 &&
			pOwner->IsQuestActive( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] ) )
		{
			pOwner->Script_CancelQuest( pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] );
		}*/

		pOwner->gCharInfoServer.otherdata.sHunting.nCurRandIds[i] = 0;
	}

	pOwner->gCharInfoServer.otherdata.sHunting.nCount = 0;
	pOwner->gCharInfoServer.otherdata.sHunting.dFreeRefreshTime = 0;

	SendQuestList( pOwner );
}