#include "NpcCreater.h"
#include "GameStage.h"
#include "NpcBaseEx.h"
#include "ShareData.h"

void NpcCreater::CreateNpc( GameStage* pStage )
{
    for ( NpcInfo::NpcsIter it = theNpcInfo.npcs_.begin(); it != theNpcInfo.npcs_.end(); ++it )
    {
        NpcInfo::Npc* pNpcInfo = &it->second;
        if ( pNpcInfo->mapId != pStage->GetMapData()->Id )
        { continue; }

        if ( pNpcInfo->type == eNT_ScriptNpc ) // 脚本NPC不会自动建立，通过脚本来创建
        { continue; }

        CreateNpc( pStage, pNpcInfo, false );
    }
}

void NpcCreater::AsynCreateNpc( GameStage* pStage,GameWorld::SSynStageInfo* pSyn)
{
	if (!pSyn)
	{
		return;
	}
	for ( NpcInfo::NpcsIter it = theNpcInfo.npcs_.begin(); it != theNpcInfo.npcs_.end(); ++it )
	{
		NpcInfo::Npc* pNpcInfo = &it->second;
		if ( pNpcInfo->mapId != pStage->GetMapData()->Id )
		{ continue; }

		if ( pNpcInfo->type == eNT_ScriptNpc ) // 脚本NPC不会自动建立，通过脚本来创建
		{ continue; }

		AsynCreateNpc( pStage, pNpcInfo, false,pSyn );
	}
}

void NpcCreater::CreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig, DWORD OnlineTime /* = 0 */ )
{
    GameObjectId nNpcId = theRunTimeData.CreateObject( theRunTimeData.GetObjecTypeByNpcType( pNpcInfo->type ) );
    NpcBaseEx* pNpcOject = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcId );
    if ( NULL == pNpcOject )
    {
        LogMessage::LogSystemError( "Get NpcObject[%u] Error!", nNpcId);
        return;
    }

    pNpcOject->Initialize( pNpcInfo, pStage );
    pNpcOject->SetDisappear( OnlineTime );
    pNpcOject->SetNewConfig( bNewConfig );

    if( !theGameWorld.OnAddCharacter( nNpcId, __FILE__, __LINE__ ) )
    {
        LogMessage::LogSystemError( "CreateNpcHero theGameWorld.OnAddCharacter( %d ) error", nNpcId );
        theGameWorld.OnDelCharacter( nNpcId );
        theRunTimeData.ReleaseObject( nNpcId, __FILE__, __LINE__ );
        return;
    }
}

void NpcCreater::AsynCreateNpc( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bNewConfig,GameWorld::SSynStageInfo* pSyn,DWORD OnlineTime)
{
	if (!pSyn)
	{
		return;
	}
	GameObjectId nNpcId = theRunTimeData.CreateObject( theRunTimeData.GetObjecTypeByNpcType( pNpcInfo->type ) );
	NpcBaseEx* pNpcOject = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcId );
	if ( NULL == pNpcOject )
	{
		LogMessage::LogSystemError( "AsynCreateNpc Get NpcObject[%u] Error!", nNpcId);
		return;
	}

	pNpcOject->Initialize( pNpcInfo, pStage ,true);
	pNpcOject->SetDisappear( OnlineTime );
	pNpcOject->SetNewConfig( bNewConfig );

	pSyn->_vecSynStageNpc.push_back(nNpcId);
	//if( !theGameWorld.OnAddCharacter( nNpcId, __FILE__, __LINE__ ) )
	//{
	//	LogMessage::LogSystemError( "AsynCreateNpc theGameWorld.OnAddCharacter( %d ) error", nNpcId );
	//	theGameWorld.OnDelCharacter( nNpcId );
	//	theRunTimeData.ReleaseObject( nNpcId );
	//	return;
	//}
}