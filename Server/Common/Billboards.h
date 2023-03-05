/********************************************************************
	Filename: 	Billboards.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"

#define BILLBOARDCNT 100

class CBillboardRow
{
public:
	CBillboardRow();
public:
	char szPlayerName[dr_MaxNameString];
	DWORD dwScore;
};
	
class CBillboard
{
public:
	CBillboard();
	void Sort( const char* szPlayerName, DWORD dwCnt );
	std::vector< CBillboardRow > Row;//[BILLBOARDCNT];
	//INT InBillBoardCnt;		//在榜上的人数
};

class CBillboardMgr
{
	//KillPlayerCnt = 0;
	//KillMonsterCnt = 0;
	//DieCnt = 0;
	//dwLineMoneyCnt = 0;
	//dwSilver = 0;
	enum
	{
		eKillPlayer,
		eKillMonster,
		eDie,
		eMoney,
		eSilver,
		eMax
	};
public:
	CBillboardMgr();

	CBillboard	BillBoard[eMax];	
public:
	void Save();
	void Load();
	void AddPlayer( class GamePlayer* pPlayer );	

private:
	void ProcessKillPlayer( const char* szPlayerName, DWORD dwCnt );
	void ProcessKillMonster( const char* szPlayerName, DWORD dwCnt );
	void ProcessDie( const char* szPlayerName, DWORD dwCnt );
	void ProcessMoney( const char* szPlayerName, DWORD dwCnt );
	void ProcessSilver( const char* szPlayerName, DWORD dwCnt );

};