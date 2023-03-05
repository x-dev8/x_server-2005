#include "ServerVarInterface.h"
#include "ShareData.h"
#include "FamilyDefine.h"
#include "GamePlayer.h"


bool CServerVarInterface::IsHaveFamily()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return false; }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->GetFamilyID() != FamilyDefine::InitFamilyID;
}
bool CServerVarInterface::IsFamilyMaster()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return false; }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

	GameFamily* pFamily = pPlayer->GetFamily();
	if( pFamily == NULL )
	{ return false; }

	return pFamily->IsFamilyLeader(pPlayer->GetDBCharacterID());
}

bool CServerVarInterface::IsExistFamily()
{
	return theGameFamilyManager.IsExistFamily();
}