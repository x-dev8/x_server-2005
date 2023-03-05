#pragma once
#include <map>
#include <vector>
#include <string>
#include "DB/DataBase.h"

class FriendManager
{
public:
	struct FriendInfo
	{
		DWORD	nID;
		char	strName[16];
		DWORD		society;	//社会关系 如：夫妻、兄弟等等
	};
public:
	FriendManager(void);
	virtual ~FriendManager(void);

public:
	void LoadFriendDB(DataBase::CConnection* pConn);

	bool AddFriend(int nCharacterID, int nFriendID, std::string strFriendName, int nSociality );
	bool DelFriend(int nCharacterID, int nFriendID);
	bool DelFriend(int nCharacterID, std::string strFriendName);
	void GetFriendList(int nCharacterID, std::vector<FriendInfo>& vFriendList);
	bool updateSociety(int nCharacterID, int nFriendID, int nSociality);

	_inline bool IsLoaded() { return m_bLoadData; } 

	
private:
	bool m_bLoadData;


	std::multimap<int, FriendInfo> m_FriendMap;
	typedef std::multimap<int, FriendInfo>::iterator Itor_Of_FriendMap;

	DataBase::CConnection* m_pConn;
};
