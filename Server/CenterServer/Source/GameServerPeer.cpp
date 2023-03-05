#include "GameServerPeer.h"
#include "Config.h"
#include "CenterServer.h"
#include "GameServerManager.h"

GameServerPeer::GameServerPeer() : _strName("UnknownServer"), _pNetClient(NULL), _bHaveSendAllGuildInfos( false ),_bHaveReady(false)
{
    _gameStages.clear();
    memset( &_burthenInfo, 0, sizeof(_burthenInfo));
}

void GameServerPeer::Release() 
{ 
	/*if (_pNetClient)
	{
		_pNetClient->Close();
		delete _pNetClient;
	}*/
	MES_DELETE(GameServerPeer);
}

bool GameServerPeer::IsHaveStageInfo( unsigned long nMapId, bool bIsRun )
{
    ItrGameStageInfoContainer it = _gameStages.find( nMapId );
    if ( it == _gameStages.end())
        return false;
    
    return ( it->second.bIsRun == bIsRun );   
}

long GameServerPeer::GetAllStageId( MapIdContainer& mapIds )
{   
    ItrGameStageInfoContainer it = _gameStages.begin();
    for ( ; it != _gameStages.end(); ++it )
    {
        mapIds.push_back( it->second );
    }
    return ER_Success;
}

void GameServerPeer::OnMessageUpdateMapInfo( MessageUpdateMapInfo* pMessage )
{   
    for ( int i=0; i<pMessage->szGameStageCount; ++i )
    {
        SGameStageOp* pGso = pMessage->GetStageOp( i );
        if ( !pGso )
            continue;

        if ( pGso->gameStageInfoType == SGameStageOp::GSIT_MapSetting)
        {
            switch ( pGso->op )
            {
            case SGameStageOp::OT_Update:
                AddStageInfo( pGso->gs );
                break;
            case SGameStageOp::OT_Remove:
                RemoveStageInfo( pGso->gs );
                LOG_MESSAGE( SYSTEMOBJECT,LOG_PRIORITY_INFO, "RemoveStageInfo(%d);", pGso->gs.ulStageId );
                break;
            }
        }
        else
        {
        }
    }
}

bool GameServerPeer::IsCanLogin()
{
    int currentMaxPlayerCount = _burthenInfo.nMaxPlayerCount - s_nLeaveCount; 
    if ( currentMaxPlayerCount < 0 )
    { currentMaxPlayerCount = 0; }

    return ( _burthenInfo.nCurrentPlayerCount < currentMaxPlayerCount );
}

void GameServerPeer::UpdateBurthen( const SBurthenBase& info )
{
    _burthenInfo = info;

    if ( _burthenInfo.nGateCount > 0 && !GetHaveReady() )
    {
//#ifdef __NEW_LOGIN__
//        if ( GetId() == Config::GetInstance().firstGameServerId )
//        {
//            CenterServer::GetInstance().GetSqlService().EnableService();
//        }
//#endif
        SetHaveReady( true );
    }
}


void GameServerPeer::SetStageOpen( unsigned long nMapID, bool bValue )
{
    ItrGameStageInfoContainer iter = _gameStages.find( nMapID );
    if ( iter == _gameStages.end() )
    { return; }

    iter->second.bIsRun = bValue;
}