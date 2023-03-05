#include "StorageMgr.h"
#include "NpcBaseCharacter.h"
#include "ShareData.h"
#include "GameWorld.h"

CStorageMgr::CStorageMgr(void)
{
	nNpcID = 0;
}

CStorageMgr::~CStorageMgr(void)
{
}
CStorageMgr* GetStorageMgr()
{
	static CStorageMgr s;
	return &s;
}
/*
@param:nStorageNpcId is the  Npcid from the slk of npc
@return :the map of the city
*/
int CStorageMgr::GetCityInfo(int nStorageNpcId)
{
	NpcBaseCharacter* pNpcChar = (NpcBaseCharacter*)theRunTimeData.GetCharacterByID( nStorageNpcId );
	if( !pNpcChar||!pNpcChar->IsNpc() )
		return 0;
	//×ª»»
	DWORD dwMapId = EctypeId2MapId( pNpcChar->GetMapID() ); 
	return dwMapId;
}
/*
@param:nStorageNpcId is the  Npcid from the slk of npc
@return : theNpcName 
*/
const char* CStorageMgr::GetNpcName(int nStorageNpcId)
{
	NpcBaseCharacter* pNpcChar = (NpcBaseCharacter*)theRunTimeData.GetCharacterByID( nStorageNpcId );
	if( !pNpcChar||!pNpcChar->IsNpc() )
		return "";
	//×ª»»
	return pNpcChar->GetPlayerName();
}