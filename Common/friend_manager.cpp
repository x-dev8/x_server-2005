#include "friend_manager.h"
#include "FuncPerformanceLog.h"

FriendManager::FriendManager(void)
{
	m_bLoadData = false;
}

FriendManager::~FriendManager(void)
{
	m_FriendMap.clear();
}

void FriendManager::LoadFriendDB(DataBase::CConnection* pConn)
{
	m_pConn = pConn;

	std::string strSql;
	strSql = "SELECT * FROM [t_game_Friend]";
	
	DataBase::CRecordset pRec = m_pConn->Execute( strSql.c_str() );
	if( !pRec.IsOpen() )//|| pRec.IsEmpty() )
	{
		return;
	}

	FriendInfo tempInfo;
	while(!pRec.IsEOF())
	{
		tempInfo.nID = atoi(pRec.Get("FriendId"));
		const char* szName = pRec.Get("FriendName");
		if( szName == NULL )
			continue;
		strncpy(tempInfo.strName, szName, sizeof(tempInfo.strName)- 1);
		tempInfo.society = atoi(pRec.Get("Sociality"));

		m_FriendMap.insert(std::make_pair(atoi(pRec.Get("CharacterId")), tempInfo));
		pRec.MoveNext();
	}

	m_bLoadData = true;
}

bool FriendManager::AddFriend(int nCharacterID, int nFriendID, std::string strFriendName, int nSociality)
{
	char szSql[512] = {0};
	_snprintf(szSql, sizeof(szSql)-1, "INSERT INTO [t_game_Friend] (CharacterId, FriendId, FriendName, Sociality) VALUES (%d, %d, '%s', %d)",
	        nCharacterID, nFriendID, strFriendName.c_str(), nSociality);
     
	DataBase::CRecordset pRec = m_pConn->Execute( szSql );
	if( !pRec.IsOpen() )
	{
		return false;
	}
	
	FriendInfo tempInfo;
	memset(&tempInfo, 0, sizeof(FriendInfo));
	tempInfo.nID = nFriendID;
	//tempInfo.strName = strFriendName;
	strncpy(tempInfo.strName, strFriendName.c_str(), strFriendName.length());
	tempInfo.society = nSociality;
	
	m_FriendMap.insert(std::make_pair(nCharacterID, tempInfo));
	return true;
}

bool FriendManager::updateSociety(int nCharacterID, int nFriendID, int nSociality)
{
	guardfunc;
	char szSql[512] = {0};
	_snprintf(szSql, sizeof(szSql)-1, "UPDATE t_game_Friend SET \
		Sociality = %d WHERE CharacterId = %d And FriendId = %d", nSociality, nCharacterID, nFriendID );

	DataBase::CRecordset pRec = m_pConn->Execute( szSql );
	if( !pRec.IsOpen() )
	{
		return false;
	}
	
	std::pair<Itor_Of_FriendMap, Itor_Of_FriendMap> range;
	range = m_FriendMap.equal_range(nCharacterID);
	for(Itor_Of_FriendMap iter = range.first; iter != range.second; ++iter)
	{
		if(iter->second.nID == nFriendID)
		{
			iter->second.society = nSociality;
			break;
		}
	}

	return true;
	unguard;
}

bool FriendManager::DelFriend(int nCharacterID, int nFriendID)
{
	char szSql[512] = {0};
	_snprintf( szSql, sizeof(szSql)-1, "DELETE FROM [t_game_Friend] WHERE CharacterId = %d AND FriendId = %d",
		     nCharacterID, nFriendID);

	DataBase::CRecordset pRec = m_pConn->Execute( szSql );
	if( !pRec.IsOpen() )
	{
		return false;
	}

	std::pair<Itor_Of_FriendMap, Itor_Of_FriendMap> range;

	range = m_FriendMap.equal_range(nCharacterID);

	for(Itor_Of_FriendMap iter = range.first; iter != range.second; ++iter)
	{
		if(iter->second.nID == nFriendID)
		{
			m_FriendMap.erase(iter);
			break;
		}
	}
	return true;
}

bool FriendManager::DelFriend(int nCharacterID, std::string strFriendName)
{
	char szSql[512] = {0};
	_snprintf( szSql, sizeof(szSql)-1, "DELETE * FROM [t_game_Friend] WHERE CharacterId = %d, AND FriendName = '%s'",
		nCharacterID, strFriendName.c_str());

	DataBase::CRecordset pRec = m_pConn->Execute( szSql );
	if( !pRec.IsOpen() )
	{
		return false;
	}

	std::pair<Itor_Of_FriendMap, Itor_Of_FriendMap> range;

	range = m_FriendMap.equal_range(nCharacterID);

	for(Itor_Of_FriendMap iter = range.first; iter != range.second; ++iter)
	{
		if( strcmp(iter->second.strName, strFriendName.c_str()) == 0)
		{
			m_FriendMap.erase(iter);
			break;
		}
	}
	return true;
}

void FriendManager::GetFriendList(int nCharacterID, std::vector<FriendInfo>& vFriendList)
{
	std::pair<Itor_Of_FriendMap, Itor_Of_FriendMap> range;

	range = m_FriendMap.equal_range(nCharacterID);

	for(Itor_Of_FriendMap iter = range.first; iter != range.second; ++iter)
	{
		vFriendList.push_back(iter->second);
	}
}
