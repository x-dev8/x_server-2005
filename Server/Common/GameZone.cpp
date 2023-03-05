#include "ShareData.h"
#include "GameZone.h"
#include "FuncPerformanceLog.h"
#include "ResourcePath.h"
#include "GamePlayer.h"

GameZone::GameZone()
{
    for ( int i = 0; i < dr_zoneMaxCoveredArea; i++ )
    { m_stCoveredArea[i] = -1; }

    m_bAreaStartup       = false;
    m_nPKMode            = 0;
    m_bPrivateShopEnable = false;
    m_pstCoveredArea     = m_stCoveredArea;
    m_stCoveredAreaCount = 0;
    m_stCoveredAreaCharCount = 0;
    m_bCoveredAreaHasPlayer  = false;
    m_nIntoAreaVMId          = -1;
    m_nLeaveAreaVMId         = -1;
    m_strZoneName.clear();
    m_strIntoAreaScript.clear();
    m_strLeaveAreaScript.clear();
    m_nMapX              = -1;
    m_nMapY              = -1;
    m_nZoneID            = -1;
    //m_bIsCanFreePK       = false;
    m_pstCoveredArea     = NULL;
    _bUpdateInOut        = false;
	m_bCanDuel = true;
}

GameZone::~GameZone()
{
}

bool GameZone::DelCharacterFromList( GameObjectId dwID )
{
    GameObjectIDSetItr it = _objectIds.find( dwID );
    if ( it != _objectIds.end() )
    {
        _objectIds.erase( it );
        return true;
    }
    return false;
}

// 添加隐藏怪到隐藏怪列表中
BOOL GameZone::AddHideMonsterToList( int nID )
{
    return m_HideMonsterIndexTable.Add( nID, FALSE );
}

// 遍历得到Id
GameObjectId GameZone::GetNextCurPlayerBId( bool bFirst )
{
    if ( bFirst )
    { _curPlayerIdItr = _curPlayerIds.begin(); }

    if ( _curPlayerIdItr != _curPlayerIds.end() )
    { 
        GameObjectId result = *_curPlayerIdItr;
        ++_curPlayerIdItr;
        return result; 
    }

    return InvalidGameObjectId;
}

// 遍历得到Id
GameObjectId GameZone::GetNextLastPlayerBId( bool bFirst )
{
    if ( bFirst )
    { _lastPlayerIdItr = _lastPlayerIds.begin(); }

    if ( _lastPlayerIdItr != _lastPlayerIds.end() )
    { 
        GameObjectId result = *_lastPlayerIdItr;
        ++_lastPlayerIdItr;
        return result; 
    }

    return InvalidGameObjectId;
}

void GameZone::ClearCurPlayerList()
{
    _curPlayerIds.clear();
}

void GameZone::AddCurPlayer2List( DWORD dwID )
{
    _curPlayerIds.insert( dwID );
}

void GameZone::UpdateLastPlayerList()
{
    // 不需要更新
    if ( !_bUpdateInOut )
    { return; }

    bool bChange = false;

    // 对比上次玩家列表,如没发现则说明玩家刚进入区域
    GameObjectId objectId = InvalidLogicNumber;
    for ( uint32 currentIndex = 0; (objectId = GetNextCurPlayerBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        // 没有找到表示进入
        if ( _lastPlayerIds.find( objectId ) != _lastPlayerIds.end() )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
        if( !pChar || !pChar->IsPlayer() )
        { continue; }

        PlayerEnterZone( (GamePlayer*)pChar );

        bChange = true;
    }

    // 对比当前玩家列表,如没发现则说明玩家刚离开区域
    objectId = InvalidLogicNumber;
    for ( uint32 currentIndex = 0; (objectId = GetNextLastPlayerBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        // 找到就跳过 没找到表示离开了
        if ( _curPlayerIds.find( objectId ) != _curPlayerIds.end())
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );//找到玩家 让玩家离开队列
        if (!pChar)
        { 
			//直接移除集合里的ID
			_lastPlayerIds.erase(objectId);
			continue; 
		}
		else if( !pChar->IsPlayer())
			continue;

        PlayerLeaveZone((GamePlayer*)pChar);
        bChange = true;
    }

    if ( bChange )
    { _lastPlayerIds = _curPlayerIds; }
}

void GameZone::SetIntoAreaScript(const char* sz)
{
    if ( sz == NULL || stricmp("NULL",sz) == 0||stricmp("NA",sz) == 0 )
    { return; }

    m_strIntoAreaScript = sz;

    if( !m_strIntoAreaScript.empty() )
    { _bUpdateInOut = true;}
}

void GameZone::SetLeaveAreaScript( const char* sz )
{
    if (sz == NULL || stricmp("NULL", sz) == 0|| stricmp("NA" , sz) == 0)
    { return; }

    m_strLeaveAreaScript = sz;
    if (!m_strLeaveAreaScript.empty())
    { _bUpdateInOut = true; }
}

bool GameZone::PlayerEnterZone( GamePlayer* pGamePlayer )
{
    if ( NULL == pGamePlayer )
    { return false; }

    pGamePlayer->SetCurZoneID( m_nZoneID );

    if ( m_strIntoAreaScript.size() > 0 )
    { // 运行进入区块脚本
        if ( m_nIntoAreaVMId == -1 )
        {            
            std::string strScriptPath = SCRIPT_ROOTDIRECTORY;
            strScriptPath += m_strIntoAreaScript;
            m_nIntoAreaVMId = GetScriptMgr()->CreateVM( ST_INTO_AREA, strScriptPath.c_str(), -1 );
        }

        if ( m_nIntoAreaVMId != -1 )
        {
            GetScriptMgr()->StartupVM( ST_INTO_AREA, m_nIntoAreaVMId, pGamePlayer );
            pGamePlayer->DebugLog( "StartupVM(%s)", m_strIntoAreaScript.c_str() );
        }
        else
        { pGamePlayer->Log( "Error:Call into area script [%s] is failed.", m_strIntoAreaScript.c_str() ); }
    }

    //if( m_bPKDisable )
    //{ pGamePlayer->SetInPKDisableZone( TRUE/*, m_nZoneID*/ ); }

    //if ( m_bIsCanFreePK )
    //{ pGamePlayer->SetInFreePKZone(true); }
    return true;
}

bool GameZone::PlayerLeaveZone( GamePlayer* pGamePlayer )
{
    if ( NULL == pGamePlayer)
    { return false; }

    if ( pGamePlayer->GetCurZoneID() == m_nZoneID )
    { pGamePlayer->SetCurZoneID( -1 ); }

    if ( m_strLeaveAreaScript.size() > 0 )
    {
        if ( m_nLeaveAreaVMId == -1 )
        {            
            std::string strScriptPath = SCRIPT_ROOTDIRECTORY;
            strScriptPath += m_strLeaveAreaScript;
            m_nLeaveAreaVMId = GetScriptMgr()->CreateVM( ST_LEAVE_AREA, strScriptPath.c_str(), -1 );
        }

        if ( m_nLeaveAreaVMId != -1 )
        { 
            GetScriptMgr()->StartupVM( ST_LEAVE_AREA, m_nLeaveAreaVMId, pGamePlayer ); 
            pGamePlayer->DebugLog( "StartupVM(%s)", m_strLeaveAreaScript.c_str() );
        }
        else
        { pGamePlayer->Log( "Error:Call leave area script [%s] is failed.", m_strLeaveAreaScript.c_str() ); }
    }

    //if( m_bPKDisable )
    //{ pGamePlayer->SetInPKDisableZone( FALSE/*, m_nZoneID*/ ); }

    //if (m_bIsCanFreePK)
    //{ pGamePlayer->SetInFreePKZone(false); }
    return true;
}
