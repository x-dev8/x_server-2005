/********************************************************************
	Filename: 	DefWallow.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DEFWALLOW_H__
#define __GAMESERVER_DEFWALLOW_H__

#pragma once

#include "BaseCharacter.h"

class AntiAddictionSystem
{
public:    
	struct sPlayerTimeInGame
	{
		DWORD dwCharDbID;
		DWORD dwTimeInGame;
		int nTellTime;
	};

	struct sPlayerOnlineTime
	{
		DWORD dwCharDbID;
		DWORD dwTimeInGame;
	};

public:
    AntiAddictionSystem();
    ~AntiAddictionSystem();

	sPlayerTimeInGame* GetPlayerTimenGameById     ( uint32 dwDBID        );
	void               ApplyPlayerInGameServerTime( BaseCharacter* pChar );
	void               ApplyPlayerOnlineTime      ( BaseCharacter* pChar );
	void               ClearPlayerInWorldTime     ( BaseCharacter* pChar );
	bool               ClearAllPlayerInWorldTime  ();
	void               SetPlayerChangePerByDbID   ( uint32 dwCharDbID    );
	sPlayerOnlineTime* GetPlayerOnlineTimeById    ( uint32 dwDBID        );

private:
    std::vector<sPlayerTimeInGame> m_vecPlayerTimeInGame;
    std::vector<sPlayerOnlineTime> m_vecPlayerOnlineTime;
};

//AntiAddictionSystem& GetAntiAddictionSystem();

#endif  // __GAMESERVER_DEFWALLOW_H__
