#ifndef _HUNTINGQUESTMANAGER_
#define _HUNTINGQUESTMANAGER_

#include "MeRTLibs.h"
#include "HuntingQuestConfig.h"
#include "GamePlayer.h"

class GamePlayer;

class HuntingQuestManager
{
public:
	HuntingQuestManager();
	virtual ~HuntingQuestManager();

	//void SetOwner( GamePlayer* pGamePlayer ) { pOwner = pGamePlayer;}

	bool IsIdsFull( GamePlayer* pOwner );
	bool IsIdExist( int id );
	bool IsTypeQuestAllExist( int type, GamePlayer* pOwner );

	bool IsGoldIdFull( HuntingQuestConfig::BaseVec& vecGoldQuest );
	bool IsTypeIdFull( HuntingQuestConfig::TypeVec& vecTypeQuest );

	void ReFreshQuest( GamePlayer* pOwner );

	void AddOneQuest( int Index, HuntingQuestConfig::BaseVec& vecGoldQuest, HuntingQuestConfig::TypeVec& vecTypeQuest, int nProbability, GamePlayer* pOwner );

	void CheckQuest( GamePlayer* pOwner );
	void SendQuestList( GamePlayer* pOwner );

	void AcceptQuest( int nId, GamePlayer* pOwner );
	void DoneQuest( int nId, GamePlayer* pOwner );

	void PassOneDay( GamePlayer* pOwner );

	static HuntingQuestManager& Instance()
	{
		static HuntingQuestManager s_xHuntingQuestManager;
		return s_xHuntingQuestManager;
	}

private:
	//GamePlayer* pOwner;
	std::vector< int > vecIds;
};

#define theHuntingQuestManager HuntingQuestManager::Instance()
#endif