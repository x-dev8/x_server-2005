#include "CenterSystemVarManager.h"
#include "ScriptVarMgr.h"
#include "MySqlCommunication.h"
#include "GameServerPeer.h"
#include "GameServerManager.h"
#include "RunStatus.h"

CenterSystemVarManager::CenterSystemVarManager() : bHaveSendLoadMessage( false ), bLoadSuccess( false )
{
    m_xUpdateTimer.StartTimer( 1, ECD_UpdateSaveTime );
}

CenterSystemVarManager::~CenterSystemVarManager()
{
}

void CenterSystemVarManager::StartLoadTimer()
{
    if ( bHaveSendLoadMessage )
    { return; }

    bHaveSendLoadMessage = true;
    m_xLoadTimer.StartTimer( 1, ECD_UpdateLoadTime );
}

void CenterSystemVarManager::StopLoadTimer()
{
    m_xLoadTimer.StopTimer();
}
void CenterSystemVarManager::SetLoadSuccess(bool bValue) 
{ 
	bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadSystemVarSuccess);
	}
}
SystemVar* CenterSystemVarManager::GetServerSysVar(uint32 serverId)
{
    if ( serverId == 0 )
    { return NULL;}

    sysVarMapIter iter = m_sysVarMap.find(serverId);
    if ( iter == m_sysVarMap.end() )    // 如果没有找到
    {
        SystemVar* pSystemVar = SystemVar::CreateSystemVar();
        if (pSystemVar == NULL)
        { return NULL;}

        pSystemVar->SetServerId(serverId);
        AddServerSysVar(pSystemVar);
        return pSystemVar;
    }
    return iter->second;
}

void CenterSystemVarManager::ProcessLoadSysVarData( unsigned int nCurrentTime )
{
    StartLoadTimer();
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return; }

    CS2DBLoadSystemVarReq xReq;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

void CenterSystemVarManager::RunUpdate( uint32 nCurrentTime )
{
    // 处理加载系统变量数据
    ProcessLoadSysVarData( nCurrentTime );

    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    AutoSaveToDatabase();   // 定时保存到DBServer
}

void CenterSystemVarManager::AutoSaveToDatabase()
{
    if ( !NeedToAutoSave() )
    { return;}

    CS2DBSaveSystemVarReq xSaveReq;
    for ( sysVarSetIter iterBegin = m_sysVarSet.begin(); iterBegin != m_sysVarSet.end(); ++iterBegin )
    {
        xSaveReq.xSystemVar.SetServerId(*iterBegin);
        sysVarMapIter iter = m_sysVarMap.find(*iterBegin);  // 从Map中得到当前的系统变量数组
        if ( iter == m_sysVarMap.end() )
        { continue;}

        memcpy_s( xSaveReq.xSystemVar.sysVar, sizeof(xSaveReq.xSystemVar.sysVar),  iter->second->sysVar, sizeof(xSaveReq.xSystemVar.sysVar) );
        theMysqlCommunication.PushReqMessage(&xSaveReq, 0);
    }

    ClearAutoSaveToServerSet();
}

void CenterSystemVarManager::OnGS2CSSendChangeVarReq( GS2CSSendChangeVarReq* pMsg, uint32 serverId )
{
    SystemVar* pVar = GetServerSysVar(serverId);
    if (pVar == NULL)
    { return;}

    HelperFunc::SafeNCpy( pVar->sysVar[pMsg->nIndex].szName, pMsg->szName, sizeof( pVar->sysVar[pMsg->nIndex].szName ) );
    pVar->sysVar[pMsg->nIndex].nVar = pMsg->nVar;

    AutoAddToServerSet(serverId);
}

void CenterSystemVarManager::SendSysVarToGameServer(uint32 serverId)
{
    if ( serverId == 0 )
    { return; }
    
    CS2GSSystemVar xCS2GSSystemVar;
    xCS2GSSystemVar.xSystemVar.SetServerId(serverId);

    SystemVar* pVar = GetServerSysVar(serverId);
    if (pVar == NULL)
    { return;}

    memcpy_s( xCS2GSSystemVar.xSystemVar.sysVar, sizeof(xCS2GSSystemVar.xSystemVar.sysVar), pVar->sysVar, sizeof(pVar->sysVar) );

    // 发送消息到GameServer
    GameServerPeer* pGameSeverPeer = theGameServerManager.GetGameServerPeer(serverId);
    if (pGameSeverPeer == NULL)
    { return;}

    pGameSeverPeer->Send( &xCS2GSSystemVar );
}