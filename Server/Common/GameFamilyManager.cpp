#include "FamilyManager.h"
#include "GamePlayer.h"


template<>
void FamilyManager< GameFamily >::SendAllFamiliesToClient( unsigned int nID )
{
	GamePlayer* pPlayer = GameFamily::GetPlayer( nID );
	if ( pPlayer == NULL )
	{ return; }

	MsgAllFamilyInfoList infoList;

	FamilyDefine::FamilySimpleInfo info;
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		info.SetFamilyID( itr->second->GetFamilyID() );
		info.SetFamilyName( itr->second->GetFamilyName() );
		info.SetLevel( itr->second->GetFamilyLevel() );
		info.SetMemberCount( itr->second->GetMemberCount() );
		info.SetProsperity( itr->second->GetProsperity() );

		if ( infoList.AddFamily(info) == false )
		{
			infoList.bEnd = false;
			pPlayer->SendMessageToClient( &infoList );

			infoList.Reset();
			infoList.AddFamily(info);
		}
	}

	if ( infoList.nFamilyCount > 0 )
	{
		pPlayer->SendMessageToClient( &infoList );
	}
}

template<>
bool FamilyManager< GameFamily >::IsExistFamily()
{
	return !( _familyContainer.empty() );
}
