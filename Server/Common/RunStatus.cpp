#include "RunStatus.h"
#include "ColorScreen.h"

RunStatus::RunStatus()
{
    _runstatus = RunStatusDefine::RunStatus_PrepareData;
}

void RunStatus::CheckRunStatus()
{
    for ( int i = 0; i < RunStatusDefine::LoadResourceSuccess; ++i )
    {
        if ( m_xLoadResource.GetBitValue( i ) == BitValue< unsigned long >::NoneValue )
        { return; }
    }

    _runstatus = RunStatusDefine::RunStatus_Running;

#ifdef _GAME_SERVER_
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Game_Server Status: Running ..." );
	COLOR_MESSAGE( COLOR_GREEN, "[GameServer OK] \n" );
#else
	//这个是center的
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Center_Server Status: Running ..." );
	COLOR_MESSAGE( COLOR_GREEN, "[CenterServer OK] \n" );
#endif

}

void RunStatus::SetLoadSuccess( unsigned char uchLoadType )
{
    m_xLoadResource.SetBitValue( uchLoadType );

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load Resource[ID:%d-%s] Success AllResource[%d]", uchLoadType, RunStatusDefine::g_szStatusArray[uchLoadType], RunStatusDefine::LoadResourceSuccess );

    CheckRunStatus();
}