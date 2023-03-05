#ifndef __STALL_INFO_QUERY_H__
#define __STALL_INFO_QUERY_H__

#include "StallMessage.h"


#define theStallInfoQuery GetStallInfoQuery()

class StallInfoQuery
{
public:
	struct SvrStallInfo : public StallDefine::SStallInfo
	{
		uint32 nCharacterID;
	};
	typedef std::multimap<uint32, SvrStallInfo>	StallInfoContainer;
	typedef StallInfoContainer::iterator		ItrStallInfoContainer;

	//����һ����̯
	void AddStallInfo( uint32 nMapID, int16 nX, int16 nY, const char* szStallTitle, const char* szCharacterName, uint32 nCharacterID );

	//ȥ��һ����̯
	void RemoveStallInfo( uint32 nCharacterID );

	void GetStallInfoList( uint32 nMapID, uint8 nSearchField, char* szKeyWord, OUT std::vector<StallDefine::SStallInfo>& vecList );
private:
	StallInfoContainer	_stallInfoList;
};
StallInfoQuery& GetStallInfoQuery();

#endif