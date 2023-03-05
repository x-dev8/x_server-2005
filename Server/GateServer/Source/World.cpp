#include "World.h"
//#include "MeConnector.h"
#include "BaseCharacter.h"
#include "GateServer.h"
#include "MapConfig.h"
#include "Config.h"

CGateWorld::CGateWorld()
{
}

CGateWorld::~CGateWorld()
{
    for ( ItGateStageContainer it=m_mapStage.begin(); it!=m_mapStage.end(); ++it )
    {
        CGateStage* pStage = it->second;
        if ( pStage )
        { delete pStage; }
    }
    m_mapStage.clear();
}

bool CGateWorld::InitStages()
{ // 读入所有场所并且初始化
    for( int i=0; i< theMapConfig.MapDataCount(); ++i)
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex( i );
        if ( NULL == pMapData)
        { continue; }

        if ( !theCfg.IsMapRun(pMapData->Id) )
        { continue; }

        if ( pMapData->IsEctypeMap() )
        { continue; }

        uint32 result = CreateStage( pMapData->Id, pMapData->Id );

        if ( RESULT_FAILED( result ))
        { 
            LogMessage::LogLogicInfo( "CreateStage fail[0x%x:0x%x] [%u]", pMapData->Id, pMapData->Id, result ); 
            return false;
        }
    }
    return true;
}

uint32 CGateWorld::CreateStage( DWORD dwMapId, DWORD dwEctypeId )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwMapId );
    if ( NULL == pMapData )
    { return 1; }

    CGateStage* pGateStage = new CGateStage;
    if ( NULL == pGateStage )
    { return 2; }

    pGateStage->SetMapCfgId( dwMapId );
    pGateStage->SetStageId( dwEctypeId );

    int nMapWidth  = ChunckToTile( pMapData->Column ); // pMap->stLandSizeX*More_nMapSize;
    int nMapHeight = ChunckToTile( pMapData->Row);     // pMap->stLandSizeY*More_nMapSize;

    if( !pGateStage->InitStage( nMapWidth, nMapHeight ) )
    { 
        delete pGateStage;
        return 3;
    }

    if ( !AddGateStage( pGateStage) )
    {
        delete pGateStage;
        return 4;
    }
    return 0;
}

bool CGateWorld::ReleaseStage( DWORD dwEctypeId )
{
    LogMessage::LogLogicInfo( "ReleaseStage Malloc[0x%x]", dwEctypeId );

    ItGateStageContainer it = m_mapStage.find( dwEctypeId );
    if ( it == m_mapStage.end() )
    { return false; }

    CGateStage* pStage = it->second;
    delete pStage;
    m_mapStage.erase( it );
    return true;
}

CGateStage* CGateWorld::GetStageById( DWORD dwMapId )
{
    ItGateStageContainer it = m_mapStage.find( dwMapId );
    if ( it == m_mapStage.end() )
    { return NULL; }
    return it->second;
}

bool CGateWorld::AddGateStage( CGateStage* pStage )
{
    // ToLog( pStage );
    DWORD dwMapId = pStage->GetStageId();
    if ( GetStageById( dwMapId ) )
    { return false; }
    m_mapStage[dwMapId] = pStage;
    return true;
}

int CGateWorld::AddToTile( GameObjectId stID,DWORD dwStageID,short stTileID )
{
    CGateStage* pStage = GetStageById( dwStageID );
    if ( !pStage )
    { return -1; }

    return pStage->AddToTile( stID, stTileID );
}

void CGateWorld::RemoveFromTile( GameObjectId stID, DWORD dwStageID, short stTileID )
{
    CGateStage* pStage = GetStageById( dwStageID );
    if ( !pStage )
    { return; }

    pStage->RemoveFromTile( stID, stTileID );
}

void CGateWorld::SendMsgToView( GameObjectId stID, Msg* pMsg,bool bExceptMe )
{
    BaseCharacter *pChar = GettheGateServer().GetChar( stID );
    if( !pChar )
    { return; }

    DWORD dwMapID = pChar->GetStageID();
    CGateStage* pStage = GetStageById( dwMapID );
    if ( !pStage )
    { 
		if ( !bExceptMe )
		{
			if( pChar->IsPlayer() )
			{
				GamePlayer* pClient = (GamePlayer *)pChar;
				pClient->SendMsg( pMsg );
			}
		}
		return; 
	}

    pStage->SendMsgToView( stID, pChar->GetCurrentTileId(), pMsg, bExceptMe );
}

void CGateWorld::SendMsgToRegion( GameObjectId id, Msg *pMsg )
{
    BaseCharacter *pChar = GettheGateServer().GetChar( id );
    if( !pChar )
    { return; }

    DWORD dwMapID = pChar->GetStageID();
    CGateStage* pStage = GetStageById( dwMapID );

    if ( !pStage )
    { return; }

    pStage->SendMsgToRegion( id, pChar->GetCurrentTileId(), pMsg );
}

void CGateWorld::SendMsgToArea( DWORD dwMapId, int nX, int nY, Msg *pMsg )
{
    CGateStage* pStage = GetStageById( dwMapId );
    if ( pStage )
    {
        pStage->SendMsgToArea( pMsg, nX, nY );
    }
    else
    {
        DWORD dwLandId = (dwMapId&0x0000ffff);
        ItGateStageContainer it=m_mapStage.begin();
        for ( ; it!=m_mapStage.end(); ++it )
        {
            CGateStage* pStage = it->second;
            if ( pStage->GetMapCfgId() == dwLandId )
            {
                pStage->SendMsgToArea( pMsg, nX, nY );
            }
        }
    }
}

void CGateWorld::SendMsgToStage( DWORD dwMapId, Msg *pMsg )
{
    CGateStage* pStage = GetStageById( dwMapId );
    if ( pStage )
    {
        pStage->SendMsgToStage( pMsg );
    }
    else
    {
        DWORD dwLandId = (dwMapId&0x0000ffff);
        ItGateStageContainer it =m_mapStage.begin();
        for ( ; it!=m_mapStage.end(); ++it )
        {
            CGateStage* pStage = it->second;
            if ( pStage->GetMapCfgId() == dwLandId )
            {
                pStage->SendMsgToStage( pMsg );
            }
        }
    }
}

void CGateWorld::SendMsgToWorld( Msg *pMsg )
{
    ItGateStageContainer it = m_mapStage.begin();
    for ( ; it!=m_mapStage.end(); ++it )
    {
        CGateStage* pStage = it->second;
        pStage->SendMsgToStage( pMsg );
    }
}

void CGateWorld::SendMsgToCountry( Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID )
{
    ItGateStageContainer it = m_mapStage.begin();
    for ( ; it!=m_mapStage.end(); ++it )
    {
        CGateStage* pStage = it->second;
        pStage->SendCountryMsgToStage( pMsg, country, ustLevel, stExceptID );
    }
}

void CGateWorld::ShowAllPlayerPos()
{

}
