#include <string.h>
#include "StallInfoQuery.h"



StallInfoQuery& GetStallInfoQuery()
{
	static StallInfoQuery instance;
	return instance;
}

void StallInfoQuery::AddStallInfo( uint32 nMapID, int16 nX, int16 nY, const char* szStallTitle, const char* szCharacterName, uint32 nCharacterID )
{
	SvrStallInfo info;
	info.dwMapID = nMapID;
	info.nX = nX;
	info.nY = nY;
	info.nCharacterID = nCharacterID;
	memcpy_s( info.szStallTitle, sizeof(info.szStallTitle), szStallTitle, sizeof(info.szStallTitle) );
	memcpy_s( info.szCharacterName, sizeof(info.szCharacterName), szCharacterName, sizeof(info.szCharacterName) );
	_stallInfoList.insert( make_pair( nMapID, info ) );
}

void StallInfoQuery::RemoveStallInfo( uint32 nCharacterID )
{
	ItrStallInfoContainer itr = _stallInfoList.begin();
	for ( ; itr != _stallInfoList.end(); ++itr )
	{
		if ( nCharacterID == itr->second.nCharacterID )
		{
			_stallInfoList.erase(itr);
			return;
		}
	}
}

void StallInfoQuery::GetStallInfoList( uint32 nMapID, uint8 nSearchField, char* szKeyWord, OUT std::vector<StallDefine::SStallInfo>& vecList )
{
    vecList.clear();

    if ( nSearchField != MsgStallQuery::ESF_NONE && NULL == szKeyWord )
    { return; }

	std::pair<ItrStallInfoContainer, ItrStallInfoContainer> pairData = _stallInfoList.equal_range(nMapID);
	ItrStallInfoContainer itr = pairData.first;

	switch (nSearchField)
	{
	case MsgStallQuery::ESF_NONE:
		{
			for ( ; itr != pairData.second; ++itr )
			{
				vecList.push_back( itr->second );
			}
		}
		break;
	case MsgStallQuery::ESF_StallName:
		{
			for ( ; itr != pairData.second; ++itr )
			{
				if ( strstr(itr->second.szStallTitle, szKeyWord) )
				{
					vecList.push_back( itr->second );
				}
			}
		}
		break;
	case MsgStallQuery::ESF_ChaName:
		{
			for ( ; itr != pairData.second; ++itr )
			{
				if ( strstr(itr->second.szCharacterName, szKeyWord) )
				{
					vecList.push_back( itr->second );
				}
			}
		}
		break;
	}
}
