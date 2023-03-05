#include "EctypeStage.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "XmlStringLanguage.h"
#include "GameStageConfig.h"
#include "TeamManager.h"
#include "CountryConfig.h"

EctypeStage::EctypeStage() : GameStage()
{
    m_nStageLevel       = 0;
    m_nNextRefreshStage = 0;
    m_dwLastRefreshTime = 0;
    m_dwNextRefreshTime = 0;
    m_nStageKeepTime    = 0;
    m_nStageCreateTime  = HQ_TimeGetTime();
}

EctypeStage::~EctypeStage()
{

}

bool EctypeStage::Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel )
{
    if ( !GameStage::Initialize( pMapData, nStageID, nMapLevel ) )
    { return false; }

    // 副本场景的等级
    SetStageLevel( nMapLevel );

    bool bResult = InitLuaScript();
    if ( !bResult )
    { return false; }

    // 如果是时间限制副本
    if ( m_pMapData->IsLifeTimeLimitMap() )
    { SetStageKeepTime( m_pMapData->Duration * OneMinuteMicroSecond ); }

    return true;
}

void EctypeStage::RunUpdate()
{
	DECLARE_TIME_TEST
	BEGIN_TIME_TEST( "EctypeStage[1]" );
    // 检查副本有效性, 是否要销毁
    CheckStageValid();
	END_TIME_TEST_1( "EctypeStage[1]",100 );
    // 分段刷怪
	BEGIN_TIME_TEST( "EctypeStage[2]" );
    RefreshMonsterByStage();        // 定时出发脚本
	END_TIME_TEST_1( "EctypeStage[2]",100 );
    // 更新怪物lua
	BEGIN_TIME_TEST( "EctypeStage[3]" );
    UpdateLuaTimer();
	END_TIME_TEST_1( "EctypeStage[3]",100 );
    // 如果等待场景销毁

	BEGIN_TIME_TEST( "EctypeStage[4]" );
	if ( IsStageWaitingRelease() )
	{ 
		ClearPlayerLeaveTime(); 
	}
	END_TIME_TEST_1( "EctypeStage[4]",100 );
    // 更新预约列表
	BEGIN_TIME_TEST( "EctypeStage[5]" );
    UpdateReserve();
	END_TIME_TEST_1( "EctypeStage[5]",100 );
	BEGIN_TIME_TEST( "EctypeStage[6]" );
    GameStage::RunUpdate();
	END_TIME_TEST_1( "EctypeStage[6]",100 );
}

void EctypeStage::CheckStageValid()
{
    // 已经等待销毁, 不执行下面了
    if ( IsStageWaitingRelease() )
    { return; } 

    // 时间限制副本
    if ( m_nStageKeepTime > 0 )
    {
        if ( GameTime::IsPassCurrentTime( m_nStageCreateTime, m_nStageKeepTime ) )
        {
            LogMessage::LogLogicInfo( "场景[0x%x]创建周期时间到,将销毁", GetStageID() );   
            SetStageWaitRelease( true );
        }
        return;
    }

    // 没有玩家在里面, 也没有预约了
    if ( m_setPlayer.empty() && !HaveReserve() )
    {
        LogMessage::LogLogicDebug( "副本[0x%x]中已经没有玩家了", GetStageID() );    
        SetStageWaitRelease( true );
        return;
    }
}

void EctypeStage::SetStageWaitRelease( bool bRelease ,bool bNow )
{
    if ( bRelease )
	{ 
		m_xReleaseTimer.StopTimer();
		m_xReleaseTimer.StartTimer( HQ_TimeGetTime(),bNow ? 0 :StageDefine::constWaitReleaseTime ); 
	}
    else
    { 
        m_xReleaseTimer.StopTimer(); 
        if ( m_pMapData->IsLifeTimeLimitMap() )
        { 
            m_nStageCreateTime = HQ_TimeGetTime();
            SetStageKeepTime( m_pMapData->Duration * OneMinuteMicroSecond );
        }
    }
}

bool EctypeStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    // 判断是否能进
    if ( !CheckCanEnterStage( pPlayer ) )
    { 
        pPlayer->ShowInfo( false, 279, theXmlString.GetString( eClient_AddInfo_2slk_44 ) );

        MapConfig::RelivePosition* pRelivePosition = m_pMapData->GetRelivePositionByState( false );              
        if ( pRelivePosition != NULL )
        {
            pPlayer->FlyToMapReq( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction );
            LogMessage::LogLogicError( "副本地图[%d]人数满了,传送至地图[0x%x]门口", m_pMapData->Id, pRelivePosition->MapId );
        }

        return false;
    }            

    return true;
}

void EctypeStage::ProcessLeaveStage( GamePlayer* pPlayer )
{
    bool bHaveChange = false;
    for ( int i = 0; i < m_pMapData->GetStatusSize(); ++i )
    {
        MapConfig::Status* pStatus = m_pMapData->GetStatusByIndex( i );
        if ( pStatus == NULL )
        { continue; }

        if ( pPlayer->_buffManager.ClearBuffByBuffIdLevel( pStatus->Id, pStatus->Level ) )
        { bHaveChange = true; }
    }

    if ( bHaveChange )
    { pPlayer->OnBuffStatusChanged( true ); }

    pPlayer->OnLeaveStage();
}

bool EctypeStage::CheckCanEnterStage( GamePlayer* pPlayer )
{
    // 不是玩家数量限制副本
    if ( !m_pMapData->IsUnitCountLimitMap() )
    { return true; }

    // GM 可以进
    if ( pPlayer->m_nGMLevel > 0 )
    { return true; }  

    return true;
}

void EctypeStage::RefreshMonsterByStage()
{   
    if ( m_nNextRefreshStage == -1 )
    { return; }     // 结束了 下面不执行

    unsigned long dwTime = HQ_TimeGetTime();
    if ( dwTime < m_dwLastRefreshTime )
    { return; }    
    m_dwLastRefreshTime = dwTime + 5000;    // 5秒计算一次

    StageData* pStageData = theGameStageConfig.GetStageData( EctypeId2MapId( GetStageID() ) );
    if ( pStageData == NULL )
    { 
        m_nNextRefreshStage = -1;
        return; 
    }

    if ( m_dwNextRefreshTime == 0 )
    {
        StageData::StageInfo* pStageInfo = pStageData->GetStageInfo( m_nNextRefreshStage );
        if ( pStageInfo == NULL )
        { 
            LogMessage::LogLogicError( " 地图[0x%x] 第[%d]阶 无配置资料", EctypeId2MapId( GetStageID() ), m_nNextRefreshStage );
            m_nNextRefreshStage = -1;
            return; 
        }
        m_dwNextRefreshTime = dwTime + pStageInfo->GetSecond() * 1000;
    }

    if ( dwTime < m_dwNextRefreshTime )
    { return; }     // 时间还没到

    StageData::StageInfo* pStageInfo = pStageData->GetStageInfo( m_nNextRefreshStage );
    if ( pStageInfo == NULL )
    {
        LogMessage::LogLogicError( " 地图[0x%x] 第[%d]阶 无配置资料", EctypeId2MapId( GetStageID() ), m_nNextRefreshStage );
        return;
    }

    int nVMId = GetScriptMgr()->CreateVM( ST_GAMESTAGE, pStageData->GetScriptFile(), EctypeId2MapId( GetStageID() ) );
    if ( nVMId == -1 )
    {
        LogMessage::LogLogicError( "创建场景脚本失败!  脚本:%s", pStageData->GetScriptFile() );
        return;
    }

    // MD 没有系统级脚本, 只好找到一个玩家身上挂起脚本执行
    for( int i = 0 ; i < GetCharacterCount() ; ++i )
    {
        GameObjectId cPID = GetCharacterID( i );
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( cPID );
        if( pChar != NULL && pChar->IsPlayer() && pChar->GetMapID() == GetStageID() )
        {
            GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
            pPlayer->CancelCurScript( __FILE__, __FUNCTION__ );     // 先把该玩家的脚本取消掉
            if ( GetScriptMgr()->StartupVM( ST_GAMESTAGE, EctypeId2MapId( GetStageID() ), pPlayer, false, m_nNextRefreshStage ) )
            { break; }

            LogMessage::LogLogicError( "执行场景脚本失败!  脚本:%s, 第[%d]阶", pStageData->GetScriptFile(), m_nNextRefreshStage );
        }
    }

    if ( m_nNextRefreshStage == -1 )
    { // 结束了
        m_dwNextRefreshTime = 0;
        return;
    }    

    unsigned int dwRunTime = 0;
    // 获得下一次的信息 m_nNextRefreshStage 在脚本里会重新设置
    pStageInfo = pStageData->GetStageInfo( m_nNextRefreshStage );
    if ( pStageInfo == NULL )
    {
        LogMessage::LogLogicError( " 地图[0x%x] 第[%d]阶 无配置资料", EctypeId2MapId( GetStageID() ), m_nNextRefreshStage );
        return;
    }

    dwRunTime = pStageInfo->GetSecond();

    m_dwNextRefreshTime = dwTime + dwRunTime * 1000;

    for( int i = 0 ; i < GetCharacterCount() ; ++i )
    {
        GameObjectId cPID = GetCharacterID( i );
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( cPID );
        if( pChar != NULL && pChar->IsPlayer() && pChar->GetMapID() == GetStageID() )
        {
            GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
            pPlayer->ProcessSystem( pStageInfo->GetString(), GamePlayer::SystemSingle );
            pPlayer->TellGameStage( pStageData->GetStageInfoCount() - 1, m_nNextRefreshStage, dwRunTime );    // 发消息给客户端 显示时间倒计时
        }
    }
}

void EctypeStage::RecordPlayerDeath( GamePlayer *pPlayer )
{
    DeathCountMapIter iter = m_mapPlayerDeath.find( pPlayer->GetDBCharacterID() );
    if ( iter == m_mapPlayerDeath.end() )
    {
        iter = m_mapPlayerDeath.insert( std::make_pair( pPlayer->GetDBCharacterID(), 0 ) ).first;
        if ( iter == m_mapPlayerDeath.end() )
        { return; }
    }

    iter->second += NUMERIC_ONE; 
}

uint16 EctypeStage::GetPlayerDeathCount( GamePlayer *pPlayer )
{
    DeathCountMapIter iter = m_mapPlayerDeath.find( pPlayer->GetDBCharacterID() );
    if ( iter == m_mapPlayerDeath.end() )
    { return 0; }

    return iter->second;
}

GameStage::eEctypeKickType EctypeStage::WhyKickOutPlayer( GamePlayer* pPlayer )
{
    if ( IsStageWaitingRelease() )
    { return eEctypeKickType_release; }

    return eEctypeKickType_no;
}

void EctypeStage::CheckKickOutPlayer( BaseCharacter* pChar )
{
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if( GetStageID() != pPlayer->GetMapID() )
    { return; }

    // 判断是否要剔除副本
    eEctypeKickType nString = WhyKickOutPlayer( pPlayer );
    if ( nString == eEctypeKickType_no )
    { return; }

    PlayerLeaveTimeIter iter = m_mapPlayerLeaveTime.find( pPlayer->GetDBCharacterID() ); 
    if ( iter != m_mapPlayerLeaveTime.end())
    {
		//10秒以后飞
		if (HQ_TimeGetTime() - iter->second < StageDefine::constKickOutUserTime)
		{
			return;
		}
		const MapConfig::RelivePosition* pRelivePosition = NULL;
		pRelivePosition = pPlayer->GetSpecRelivePosition(m_pMapData);
		if (!pRelivePosition)
		{
			pRelivePosition = pPlayer->GetRelivePosition(m_pMapData);
			if ( pRelivePosition == NULL )
			{ return; }
		}
		if ( pRelivePosition != NULL )
		{
			pPlayer->FlyToMapReq( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction );
		}
		else
		{
			const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pPlayer->GetCountry() );
			if ( pSetting != NULL )
			{
				pPlayer->FlyToMapReq( pSetting->GetMapID(), pSetting->GetPosX(), pSetting->GetPosY(), 0.f );
			}
		}

		return; 
	}

    MsgTellLeaveEctype xTell;
	switch(nString)
	{
	case eEctypeKickType_noTeam:
		xTell.nStringID = eClient_AddInfo_2slk_73;
		break;
	case eEctypeKickType_noguild:
		xTell.nStringID = eClient_AddInfo_2slk_74;
		break;
	default:
		xTell.nStringID = eClient_AddInfo_2slk_72;
		break;
	}
    pPlayer->SendMessageToClient( &xTell );

	pPlayer->Log(theXmlString.GetString(eServerLog_FuBenExit), pPlayer->GetAccountID(), pPlayer->GetCharName(), m_pMapData->MapName.c_str(), GetStageID() );

	m_mapPlayerLeaveTime.insert( std::make_pair( pPlayer->GetDBCharacterID(), HQ_TimeGetTime() ) );            // 记录飞的时间	
}

void EctypeStage::ClearPlayerLeaveTime()
{
    uint32 nCurrentTime = HQ_TimeGetTime();
    for ( PlayerLeaveTimeIter iter = m_mapPlayerLeaveTime.begin(); iter != m_mapPlayerLeaveTime.end(); )
    {
        if ( GameTime::IsPassCurrentTime( nCurrentTime, iter->second, 20000 ) )        // 25秒 清除
        {
            iter = m_mapPlayerLeaveTime.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}


uint32 EctypeStage::InitLuaScript()
{
    std::string strFilePath = m_pMapData->GetMapScriptFile();
    if ( strFilePath.empty() )
    { return true; }

    try
    {
        LuaObject metaTableObj;
        metaTableObj = _luaScript->GetGlobals().CreateTable("MultiObjectMetaTable");
        metaTableObj.SetObject("__index", metaTableObj );
        metaTableObj.RegisterObjectDirect( "LuaStartTimer", (EctypeStage*)0, &EctypeStage::LuaStartTimer );
        metaTableObj.RegisterObjectDirect( "LuaStopTimer" , (EctypeStage*)0, &EctypeStage::LuaStopTimer );

        LuaObject CAICharacterCoreObj = _luaScript->BoxPointer(this);
        CAICharacterCoreObj.SetMetaTable(metaTableObj);
        _luaScript->GetGlobals().SetObject( "GameStage", CAICharacterCoreObj );

        std::string strFilePath = STAGEROOTDIRECTORY;
        strFilePath += "\\";
        strFilePath += m_pMapData->GetMapScriptFile();
        if( LUA_ERRFILE==_luaScript->LoadFile( strFilePath.c_str() ) )
        { 
            LogMessage::LogSystemError( "GameStage %s InitLuaScript(%s) Failed", m_pMapData->MapName.c_str(),strFilePath.c_str() );
            return false; 
        }
        _luaScript->Call( 0, 0 );
    }
    catch (LuaPlus::LuaException &e)
    {
        LogMessage::LogScriptError( "GameStage %s Load script failed:%s", m_pMapData->MapName.c_str(), e.GetErrorMessage() );
        return false;
    }

    // 调用初始化
    try
    {
        LuaObject luaobject = _luaScript->GetGlobal("LuaInit");
        if(luaobject.IsFunction())
        { 
            LuaFunction<void> LuaInit(luaobject);
            LuaInit();
        }
    }
    catch ( LuaPlus::LuaException& e )
    {
        LogMessage::LogScriptError( "GameStage %s LuaInit Failed: %s", m_pMapData->MapName.c_str(), e.GetErrorMessage());
    }

    _bHaveScript = true;
    return true;
}

void EctypeStage::LuaStartTimer( uint8 id, uint32 interval )
{
    if ( id >= StageDefine::ETimerType_Max )
    { return; }

    _timers[id].StartTimer( id, interval );
}

void EctypeStage::LuaStopTimer( uint8 id )
{
    if ( id >= StageDefine::ETimerType_Max )
    { return; }

    _timers[id].StopTimer();
}

void EctypeStage::UpdateLuaTimer()
{
    if ( !_bHaveScript )
    { return; }

    for ( uint8 i = StageDefine::ETimerType_1; i < StageDefine::ETimerType_Max; ++i )
    {
        if ( !_timers[i].IsStart() || !_timers[i].DoneTimer( HQ_TimeGetTime() ))
        { continue; }

        try
        {
            LuaObject luaobject = _luaScript->GetGlobal("LuaOnTimer");
            if(luaobject.IsFunction())
            { 
                LuaFunction<void> LuaOnTimer(luaobject);
                LuaOnTimer( i );
            }
        }
        catch ( LuaPlus::LuaException& e )
        {
            LogMessage::LogScriptError( "GameStage %s LuaOnTimer Failed: %s", m_pMapData->MapName.c_str(), e.GetErrorMessage());
        }
    }
}

void EctypeStage::UpdateReserve()
{
    uint32 nCurrentTime = HQ_TimeGetTime();
    for ( ReserveMapIter iter = m_mapReserve.begin(); iter != m_mapReserve.end(); )
    {
        if ( GameTime::IsPassCurrentTime( nCurrentTime, iter->second, StageDefine::constMaxReserveTime ) )
        {
            iter = m_mapReserve.erase( iter );
            continue;
        }

        ++iter;
    }
}