#include "LogicWork.h"
#include "RankManager.h"
#include "ServerStatus.h"

CWorkThread CLogicWork::g_MainLogicThread;

CLogicWork::CLogicWork(void)
{
}

CLogicWork::~CLogicWork(void)
{
}

void CLogicWork::Main( void* pParam)
{
	theRankManager.Run();
	theServerStatusManager.Run();
	Sleep(1);
}

bool CLogicWork::Init()
{
	bool bResult = CLogicWork::g_MainLogicThread.CreateThread( CLogicWork::Main );
	CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

	return ER_Success;
}