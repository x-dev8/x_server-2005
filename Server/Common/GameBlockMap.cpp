#include "GlobalDef.h"
#include "GameBlockMap.h"


BlockMapManager& GetBlockMapManager()
{
	static BlockMapManager instance;
	return instance;
}

PlayerMoveAnalysis& GetPlayerMoveAnalysis()
{
	static PlayerMoveAnalysis instance;
	return instance;
}


BlockMapManager::~BlockMapManager()
{
	ItrBlockMapContainer itr = _blockMapContainer.begin();
	ItrBlockMapContainer endItr = _blockMapContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->second )
		{ delete itr->second; }
	}
}

long BlockMapManager::InitBlockMap( unsigned short nMapID, const std::string& strFileName )
{
	SwMap* pBlockMap = new SwMap;
	if ( NULL == pBlockMap )
	{ return ER_NewNormalFail; }

	if ( ! pBlockMap->Create( strFileName.c_str() ) )
	{
		delete pBlockMap;
		return ER_Failed;
	}

	if ( ! _blockMapContainer.insert( BlockMapContainer::value_type( nMapID, pBlockMap ) ).second )
	{
		delete pBlockMap;
		return ER_Failed;
	}

	return ER_Success;
}

bool BlockMapManager::IsPointReachable( unsigned short nMapID, float fX, float fY )
{
	ItrBlockMapContainer itr = _blockMapContainer.find( nMapID );
	if ( itr == _blockMapContainer.end() )
	{ return true; }

	return itr->second->CanReach( swVec2f( fX, fY ) );
}

bool BlockMapManager::IsLineCanMove( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd )
{
	ItrBlockMapContainer itr = _blockMapContainer.find( nMapID );
	if ( itr == _blockMapContainer.end() )
	{ return true; }

	return itr->second->CanMove( swVec2f( fXStart, fYStart ), swVec2f( fXEnd, fYEnd ) );
}

bool BlockMapManager::CanMoveByLine( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd )
{
	ItrBlockMapContainer itr = _blockMapContainer.find( nMapID );
	if ( itr == _blockMapContainer.end() )
	{ return true; }

	if ( ! itr->second->CanReach( swVec2f( fXStart, fYStart ) ) || ! itr->second->CanReach( swVec2f( fXEnd, fYEnd ) ) )
	{ return false; }

	return itr->second->CanMove( swVec2f( fXStart, fYStart ), swVec2f( fXEnd, fYEnd ) );
}

void PlayerMoveAnalysis::PlayerMoveAnalysisThreadFunc( void* pVoid )
{
	PlayerMoveAnalysis* pAnalysis = static_cast< PlayerMoveAnalysis* >( pVoid );
	if ( NULL == pAnalysis )
	{ return; }

	ReqMsgQueue tempQueue;
	{
		CSALocker lock( pAnalysis->_lockReqQueue );
		tempQueue = pAnalysis->_reqMsgQueue;
		pAnalysis->_reqMsgQueue.clear();
	}

	ItrReqMsgQueue itr = tempQueue.begin();
	ItrReqMsgQueue endItr = tempQueue.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( ! GetBlockMapManager().CanMoveByLine( itr->nMapID, itr->vOldPos.x, itr->vOldPos.y, itr->vNewPos.x, itr->vNewPos.y ) )
		{
			LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_DEBUG,
				"[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t[-]\t[%d]\t可能非法的玩家移动\t从坐标[%f,%f,%f]移动至坐标[%f,%f,%f]", itr->nAccountID, itr->szLoginName, itr->szCharName, itr->nChaDBID, itr->nMapID, /*itr->SessionKey, */itr->nID,
				 itr->vOldPos.x, itr->vOldPos.y, itr->vOldPos.z, itr->vOldPos.x, itr->vOldPos.y, itr->vOldPos.z );
		}
	}

	static const int nSleepTime = 1; //g_Cfg.m_bSleepTime;
	Sleep( nSleepTime );
}

void PlayerMoveAnalysis::AddReqAnalysisMsg( ReqAnalysisMsg& req )
{
	CSALocker lock( _lockReqQueue );
	_reqMsgQueue.push_back(req);
}
