#include "Billboards.h"
#include "GamePlayer.h"
#include "DataChunkWriter.h"
#include "FuncPerformanceLog.h"
//
//CBillboardRow::CBillboardRow()
//{
//	guardfunc
//	szPlayerName[0] = '\0';
//	dwScore = 0;
//	unguard;
//}
//
//
//CBillboard::CBillboard()
//{
//	guardfunc
//
//	unguard;
//}
//
////-----------------------------------------------------------------------------
//// Name: SortModesCallback()
//// Desc: Callback function for sorting display modes (used by BuildDeviceList).
////-----------------------------------------------------------------------------
//static int SortBillBoardRow( const VOID* arg1, const VOID* arg2 )
//{
//	CBillboardRow* p1 = (CBillboardRow*)arg1;
//	CBillboardRow* p2 = (CBillboardRow*)arg2;
//
//	if( p1->dwScore > p2->dwScore )   return -1;
//	if( p1->dwScore < p2->dwScore )   return +1;
//
//	return 0;
//}
//
//void CBillboard::Sort( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	if( szPlayerName == NULL )
//		return;
//
//	if( Row.size() < BILLBOARDCNT )
//	{
//		CBillboardRow AddRow;
//		strncpy_s( AddRow.szPlayerName, sizeof( AddRow.szPlayerName ), szPlayerName, sizeof( AddRow.szPlayerName ) - 1 );
//		AddRow.dwScore = dwCnt;
//		Row.push_back( AddRow );
//		qsort( &Row[0], Row.size(), sizeof(CBillboardRow), SortBillBoardRow );
//	}
//	else
//	{
//		INT nIdx = BILLBOARDCNT-1;
//		if( Row[nIdx].dwScore < dwCnt )
//		{
//			strncpy_s( Row[nIdx].szPlayerName, sizeof( Row[nIdx].szPlayerName ), szPlayerName, sizeof( Row[nIdx].szPlayerName ) - 1 );
//			Row[nIdx].dwScore = dwCnt;
//			qsort( &Row[0], Row.size(), sizeof(CBillboardRow), SortBillBoardRow );
//		}
//	}
//	//if( InBillBoardCnt < BILLBOARDCNT )
//	//{
//	//	if( Row[InBillBoardCnt].dwScore >= dwCnt )
//	//	{
//	//		return;
//	//	}
//
//	//	strncpy( Row[InBillBoardCnt].szPlayerName, szPlayerName, dr_MaxNameString );
//	//	Row[InBillBoardCnt].dwScore = dwCnt;
//	//	qsort( Row, InBillBoardCnt,  )
//
//	//}
//
//
//
//	unguard;
//}
//
//
//CBillboardMgr::CBillboardMgr()
//{
//	guardfunc
//
//	unguard;
//}
//
//void CBillboardMgr::AddPlayer( GamePlayer* pPlayer )
//{
//	guardfunc
//
//	if( pPlayer == NULL )
//	{
//		return;
//	}
//
//
//
//	CONST char *szName = pPlayer->gCharInfoServer.baseinfo.aptotic.szCharacterName;
//	DWORD KillPlayerCnt = pPlayer->gCharInfoServer.baseinfo.score.KillPlayerCnt;
//	if( KillPlayerCnt != 0 )
//	{
//		ProcessKillPlayer( szName, KillPlayerCnt );
//	}
//
//	DWORD KillMonsterCnt = pPlayer->gCharInfoServer.baseinfo.score.KillMonsterCnt;
//	if( KillMonsterCnt != 0 )
//	{
//		ProcessKillMonster( szName, KillMonsterCnt );
//	}
//
//	DWORD DieCnt = pPlayer->gCharInfoServer.baseinfo.score.DieCnt;
//	if( DieCnt != 0 )
//	{
//		ProcessDie( szName, DieCnt );
//	}
//
//
//	DWORD Silver = pPlayer->gCharInfoServer.baseinfo.score.dwSilver;
//	if( Silver != 0 )
//	{
//		ProcessSilver( szName, Silver );
//	}
//	
//	INT nMoney = pPlayer->gCharInfoServer.baseinfo.score.dwLineMoneyCnt;	
//	if( nMoney != 0 )
//	{
//		ProcessMoney( szName, nMoney );
//	}
//
//	unguard;
//}
//
//void CBillboardMgr::ProcessKillPlayer( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	BillBoard[eKillPlayer].Sort( szPlayerName, dwCnt );
//	unguard;
//}
//
//void CBillboardMgr::ProcessKillMonster( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	BillBoard[eKillMonster].Sort( szPlayerName, dwCnt );
//	unguard;
//}
//
//void CBillboardMgr::ProcessDie( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	BillBoard[eDie].Sort( szPlayerName, dwCnt );
//	unguard;
//}
//
//void CBillboardMgr::ProcessMoney( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	BillBoard[eMoney].Sort( szPlayerName, dwCnt );
//	unguard;
//}
//
//void CBillboardMgr::ProcessSilver( const char* szPlayerName, DWORD dwCnt )
//{
//	guardfunc
//	BillBoard[eSilver].Sort( szPlayerName, dwCnt );
//	unguard;
//}
//
//void CBillboardMgr::Save()
//{
//	guardfunc
//
//	CDataChunkWriter Writer;
//	
//
//
//	unguard;
//}
//
//void CBillboardMgr::Load()
//{
//	guardfunc
//
//	unguard;
//}