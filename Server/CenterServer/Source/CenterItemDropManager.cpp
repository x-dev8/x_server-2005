#include "CenterItemDropManager.h"
#include "CenterGameMessage.h"
#include "CenterServer.h"
#include "GameServerManager.h"
#include "logmgr.h"
#include "RunStatus.h"
//#include "log4cpp/log4cpp_logger.h"
#include "LogFileObjectNameEx.h"
#include "MySqlCommunication.h"

//////////////////////////////////////////////////////////////////////////////////////
// 由于不是在CenterServer做判断,所以会出现一个问题, 当A服务器传送过来的资料到CenterServer后, 
// CenterServer更新给其他服务器,但此时B服务器在收到更新消息之前就发送出更新到CenterSrever,这样就会可能
// 造成物品会多产出那么一两个.
//////////////////////////////////////////////////////////////////////////////////////
CenterItemDropManager::CenterItemDropManager() : m_bHaveSendLoadMessage( false ), m_bLoadSuccess( false ), m_bNeedSendToGameServers( false )
{
    m_mapCenterItemDropControl.clear(); 
    m_setItemDrop.clear();

    m_xUpdateTimer.StartTimer( 1, ECD_UpdateSaveTime );
}

void CenterItemDropManager::RunUpdate( uint32 nCurrentTime )
{
    StartLoadTimer();
    if ( m_xLoadTimer.DoneTimer( nCurrentTime ) )
    {
        SendLoadMessage();
        return;
    }

    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    AutoSaveToDataBase();
}

void CenterItemDropManager::StartLoadTimer()
{
    if ( m_bHaveSendLoadMessage )
    { return; }

    m_bHaveSendLoadMessage = true;
    m_xLoadTimer.StartTimer( 1, ECD_UpdateLoadTime );
}

void CenterItemDropManager::StopLoadTimer()
{
    m_xLoadTimer.StopTimer();
}
void CenterItemDropManager::SetLoadSuccess( bool bValue )
{ 
	m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadItemDropuccess);
	}
}
void CenterItemDropManager::AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
{
    if ( nItemID == InvalidLogicNumber )
    { return; }

    MapItemDropControlIter iter = m_mapCenterItemDropControl.find( nItemID );
    if ( iter == m_mapCenterItemDropControl.end() )
    {
        ItemDropControl xControl;
        xControl.dwControlCount = dwControlCount;
        xControl.dwDropCount    = dwDropCount;

        m_mapCenterItemDropControl.insert( make_pair( nItemID, xControl ) );
    }
    else
    {
        iter->second.dwControlCount = dwControlCount;
        iter->second.dwDropCount    += dwDropCount;
    }

    AddToAutoSaveSet( nItemID );
}

ItemDropControl* CenterItemDropManager::GetItemDropControl( uint16 nItemID )
{
    MapItemDropControlIter iter = m_mapCenterItemDropControl.find( nItemID );
    if ( iter  == m_mapCenterItemDropControl.end() )
    { return NULL; }

    return &( iter->second );
}

// 自动保存
void CenterItemDropManager::AutoSaveToDataBase()
{
    if ( !NeedToAutoSave() )
    { return; }

    CS2DBSaveItemDropControl xSave;
    for ( SaveItemDropIter iter =  m_setItemDrop.begin(); iter != m_setItemDrop.end(); ++iter )
    {
        ItemDropControl* pControl = GetItemDropControl( *iter );
        if ( pControl == NULL )
        { continue; }

        xSave.AddItemDropControl( *iter, pControl->dwControlCount, pControl->dwDropCount );
        if ( xSave.IsFull() )
        {
            theMysqlCommunication.PushReqMessage( &xSave, 0 );

            xSave.Reset();
        }
    }

    if ( xSave.nCount > 0 )
    {
        theMysqlCommunication.PushReqMessage( &xSave, 0 );
    }

    ClearAutoSaveSet();
}

void CenterItemDropManager::SendLoadMessage()
{
    CS2DBItemDropControlReq xReq;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

void CenterItemDropManager::SendDropControlToGameServer( unsigned int nServerID /* = 0; */ )
{
    if ( !GetLoadSuccess() )
    { return; }
    
    GameServerPeer* pGameServer = NULL;
    if ( nServerID != 0 )
    { pGameServer = theGameServerManager.GetGameServerPeer( nServerID ); }

    CS2GSItemDropControl xControl;
    
    for ( MapItemDropControlIter iter = m_mapCenterItemDropControl.begin(); iter != m_mapCenterItemDropControl.end(); ++iter )
    {
        xControl.AddItemDropControl( iter->first, iter->second.dwControlCount, iter->second.dwDropCount );
        if ( xControl.IsFull() )
        {
            if ( pGameServer == NULL )
            {
                theGameServerManager.SendMessageToGameServers( &xControl );
            }
            else
            {
                pGameServer->Send( &xControl );
            }

            xControl.Reset();
        }
    }

    if ( pGameServer == NULL )
    {
        theGameServerManager.SendMessageToGameServers( &xControl );
    }
    else
    {
        pGameServer->Send( &xControl );
    }
}