#include "GameParthFinder.h"
#include "GameStage.h"
#include "GameWorld.h"
#include "ShareData.h"



ParthFinderTemplates& GetParthFinderTemplates()
{
	static ParthFinderTemplates instance;
	return instance;
}

GameParthFinder& GetGameParthFinder()
{
	static GameParthFinder instance;
	return instance;
}

ParthFinderTemplates::~ParthFinderTemplates()
{
	CSALocker lock(_lock);
	ItrParthFinderContainer itr = _parthFinders.begin();
	ItrParthFinderContainer endItr = _parthFinders.end();
	for ( ; itr != endItr; ++itr )
	{
		SwMap* pData = itr->second;
		if ( pData )
		{
			delete pData;
		}
	}
	_parthFinders.clear();
}

long ParthFinderTemplates::InitParthFinder( uint32 nMapID, const std::string& strFileName )
{
	CSALocker lock(_lock);
	SwMap* pParthFinder = new SwMap;
	if ( NULL == pParthFinder )
	{ return ER_NewNormalFail; }

	if ( ! pParthFinder->ReadInReachableData( strFileName.c_str() ) )
	{
		delete pParthFinder;
		return ER_Failed;
	}

	if ( ! _parthFinders.insert( ParthFinderContainer::value_type( nMapID, pParthFinder ) ).second )
	{
		delete pParthFinder;
		return ER_Failed;
	}

	return ER_Success;
}

SwMap* ParthFinderTemplates::GetParthFinder( uint32 nMapID )
{
	CSALocker lock(_lock);
	ItrParthFinderContainer itr = _parthFinders.find( nMapID );
	if ( itr != _parthFinders.end() )
	{
		return itr->second;
	}
	return NULL;
}

void GameParthFinder::ParthFinderThreadFunc( void* pVoid )
{
	GameParthFinder* pGameParthFinder = static_cast< GameParthFinder* >( pVoid );

	FindParthReqQueue tempQueue;
	{
		CSALocker lock( pGameParthFinder->_lockReqQueue );
		tempQueue = pGameParthFinder->_reqQueue;
		pGameParthFinder->_reqQueue.clear();
	}

	DECLARE_TIME_TEST
	BEGIN_TIME_TEST( "GameParthFinder::ParthFinderThreadFunc[0]" )

	ItrFindParthReqQueue itr = tempQueue.begin();
	ItrFindParthReqQueue endItr = tempQueue.end();
	for ( ; itr != endItr; ++itr )
	{
		AckFindParth ack;
		ack.nChaID = itr->nChaID;
		ack.targetPos = itr->targetPos;

		//查找场景的寻路器
		GameStage* pStage = theGameWorld.GetStageById( itr->nStageID );
		if ( NULL == pStage )
			continue;
		SwMap* pParthFinder = pStage->GetThreadParthFinder();
		if ( NULL == pParthFinder )
			continue;

		bool blTargetCanReach = pParthFinder->CanReach(itr->targetPos);
		if ( false == blTargetCanReach )
		{// 如果目标位置不可达,则尝试寻找一个离目标位置较近的可达点
			pParthFinder->GetReachablePosToDest( itr->startPos, itr->targetPos, &itr->targetPos );
		}

		if ( pParthFinder->CanReach(itr->startPos) && pParthFinder->CanReach(itr->targetPos) )
		{
			if ( pParthFinder->FindPath( itr->startPos, itr->targetPos, ack.findParth ) )
			{
				if ( blTargetCanReach )
				{
					ack.findParth.push_back( ack.targetPos );
					ack.nFinParthState = CharacterFindParth::FPS_AStar;
				}
				else
				{
					ack.nFinParthState = CharacterFindParth::FPS_Pos;
				}

				pGameParthFinder->AddAckFindParth(ack);
				continue;
			}
		}

		// 未能找到路径
		ack.findParth.push_back(itr->startPos);
		ack.nFinParthState = CharacterFindParth::FPS_None;

		pGameParthFinder->AddAckFindParth(ack);
	}

	END_TIME_TEST( "GameParthFinder::ParthFinderThreadFunc[0]" );

	static const int nSleepTime = 1; //g_Cfg.m_bSleepTime;
	Sleep( nSleepTime );
}

void GameParthFinder::AddFindParthReq( FindParthReq& req )
{
	CSALocker lock(_lockReqQueue);
	_reqQueue.push_back(req);
}

void GameParthFinder::AddAckFindParth( AckFindParth& ack )
{
	CSALocker lock(_lockAckQueue);
	_ackQueue.push_back(ack);
}

void GameParthFinder::Update()
{
	DECLARE_TIME_TEST
	BEGIN_TIME_TEST( "GameParthFinder[1]" );
	AckFindParthQueue tempQueue;
	{
		CSALocker lock(_lockAckQueue);
		tempQueue = _ackQueue;
		_ackQueue.clear();
	}
	END_TIME_TEST_1( "GameParthFinder[1]",100 );
	ItrAckFindParthQueue itr = tempQueue.begin();
	ItrAckFindParthQueue endItr = tempQueue.end();
	BEGIN_TIME_TEST( "GameParthFinder[2]" );
	for ( ; itr != endItr; ++itr )
	{
		//查找角色
		DECLARE_TIME_TEST
		BEGIN_TIME_TEST( "GameParthFinder[3]" );
		BaseCharacter* pChar = theRunTimeData.GetCharacterByID( itr->nChaID );
		if ( pChar && pChar->IsMonster() )
		{
			MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
			pMonster->GetCharFindParth().SetFindParth( itr->findParth, itr->nFinParthState, pMonster->GetMapID(), pMonster->GetPos() );
		}
		END_TIME_TEST_1( "GameParthFinder[3]",100 );
	}
	END_TIME_TEST_1( "GameParthFinder[2]",200 );
}
