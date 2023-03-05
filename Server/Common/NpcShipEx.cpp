#include "NpcShipEx.h"
#include "GamePlayer.h"
#include "ShareData.h"

NpcShipEx::NpcShipEx() : m_xLuaScript( false )
{
    SetObjType( Object_NpcShip );
    m_vecPlayers.resize( MaxPlayerCount, InvalidGameObjectId );
   
    m_xMovingEventTimer.StartTimer( HQ_TimeGetTime(), 5000 );
    m_nMovingEventCounter = 0;
}

NpcShipEx::~NpcShipEx()
{
    try
    {
        m_xLuaScript->PushNil();
    }
    catch (LuaPlus::LuaException &e)
    {
        LogMessage::LogLogicError( "Npc %s AI Failed: %s", m_pNpcInfo->name.c_str(), e.GetErrorMessage() );
    }
}

void NpcShipEx::Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn  )
{
    NpcBaseEx::Initialize( pConfig, pStage, bAsyn);
    
    m_xTimer[ AiDefine::AiTimer_Talk ].StartTimer( HQ_TimeGetTime(), 1000 * 1000 );
    SetAiStatus( AiDefine::ThinkingStopToTalk );

    if ( !InitLuaScript() )
    { return; }

    try
    {
        LuaObject luaobject = m_xLuaScript->GetGlobal( "LuaInit" );
        if( luaobject.IsFunction() )
        { 
            LuaFunction<void> LuaInit( luaobject );
            LuaInit();
        }
    }
    catch ( LuaPlus::LuaException& e )
    {
        LogMessage::LogScriptError( "Npc %s LuaInit Failed: %s", m_pNpcInfo->name.c_str(), e.GetErrorMessage());
    }
}

void NpcShipEx::OnExit( Msg* pMsg, unsigned char exitType )
{
    // 所有人下大载体;
    for ( PlayerVectorIter iter = m_vecPlayers.begin(); iter != m_vecPlayers.end(); ++iter )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *iter );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        pPlayer->OffNpcShip();
    }

    m_vecPlayers.clear();

    NpcBaseEx::OnExit( pMsg, exitType );
}

void NpcShipEx::Run( DWORD dwCostTime )
{
    NpcBaseEx::Run( dwCostTime );
}

uint32 NpcShipEx::OnShip( GameObjectId playerId, uint8& pos )
{
    int8 curPos = 0;
    for ( PlayerVectorIter iter = m_vecPlayers.begin(); iter != m_vecPlayers.end(); ++iter )
    {
        if ( *iter != InvalidGameObjectId )
        {
            ++curPos;
            continue;
        }

        *iter = playerId;
        pos = curPos;
        return ER_Success;
    }

    return ER_Failed;
}

uint32 NpcShipEx::OffShip( GameObjectId playerId )
{
    for ( PlayerVectorIter iter = m_vecPlayers.begin(); iter != m_vecPlayers.end(); ++iter )
    {
        if ( playerId != *iter )
        { continue; }

        *iter = InvalidGameObjectId; 
        return ER_Success;
    }

    return ER_Failed;
}

void NpcShipEx::ProcessAiMoving( uint32 nCostTime )
{
    NpcBaseEx::ProcessAiMoving( nCostTime );

    for ( PlayerVectorIter iter = m_vecPlayers.begin(); iter != m_vecPlayers.end(); )
    {
        GameObjectId id = (*iter);
        if ( id == InvalidGameObjectId )
        { 
            ++iter;
            continue; 
        }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            iter = m_vecPlayers.erase( iter );
            continue;
        }

        pChar->SetFloatXF( GetFloatX() );
        pChar->SetFloatYF( GetFloatY() );
        pChar->SetDirX( GetDirX() );
        pChar->SetDirY( GetDirY() );

        ++iter;
    }

    if ( m_xMovingEventTimer.DoneTimer( HQ_TimeGetTime() ) )
    {
        try
        {
            LuaObject luaobject = m_xLuaScript->GetGlobal( "LuaMovingTimerEvent" );
            if( luaobject.IsFunction() )
            { 
                LuaFunction<void> LuaMovingTimerEvent( luaobject );
                LuaMovingTimerEvent( m_nMovingEventCounter++ );
            }
        }
        catch ( LuaPlus::LuaException& e )
        {
            LogMessage::LogScriptError( "Npc %s LuaInit Failed: %s", m_pNpcInfo->name.c_str(), e.GetErrorMessage() );
        }
    }
}

void NpcShipEx::ProcessArriveRoute()
{
    NpcBaseEx::ProcessArriveRoute();

    if ( !NeedMoveToNextRoute() )
    {
        m_xTimer[ AiDefine::AiTimer_Talk ].StopTimer();
        m_xMovingEventTimer.StopTimer();
        m_nMovingEventCounter = 0;
    }
}

bool NpcShipEx::InitLuaScript()
{
    try
    {
        LuaObject metaTableObj;
        metaTableObj = m_xLuaScript->GetGlobals().CreateTable( "MultiObjectMetaTable" );
        metaTableObj.SetObject("__index", metaTableObj );
        metaTableObj.RegisterObjectDirect( "WaitPlayerTime",      (NpcShipEx*)0, &NpcShipEx::WaitPlayerTime      );
        metaTableObj.RegisterObjectDirect( "MovingEventInterval", (NpcShipEx*)0, &NpcShipEx::MovingEventInterval );
        metaTableObj.RegisterObjectDirect( "Say",                 (NpcShipEx*)0, &NpcShipEx::Say                 );
        metaTableObj.RegisterObjectDirect( "CallEvent",           (NpcShipEx*)0, &NpcShipEx::CallEvent           );

        LuaObject CAICharacterCoreObj = m_xLuaScript->BoxPointer( this );
        CAICharacterCoreObj.SetMetaTable( metaTableObj );
        m_xLuaScript->GetGlobals().SetObject( "Npc", CAICharacterCoreObj );

        std::string strFilePath;
        strFilePath += SCRIPT_ROOTDIRECTORY;
        strFilePath += m_pNpcInfo->actionScript;
        if( LUA_ERRFILE == m_xLuaScript->LoadFile( strFilePath.c_str() ) )
        { 
            LogMessage::LogSystemError( "Npc %s InitLuaScript(%s) Failed", m_pNpcInfo->name.c_str(), strFilePath.c_str() );
            return ER_Failed; 
        }
        m_xLuaScript->Call( 0, 0 );
    }
    catch (LuaPlus::LuaException &e)
    {
        LogMessage::LogScriptError( "Npc %s AI script failed:%s", GetCharName(), e.GetErrorMessage() );
        return false;
    }

    return true;
}

void NpcShipEx::SendBeCarryPlayersTo( GamePlayer* pTarget )
{
    char szMsgBuff[1024] = {0};

    for ( PlayerVectorIter iter = m_vecPlayers.begin(); iter != m_vecPlayers.end(); ++iter)
    {
        GameObjectId id = (*iter);
        if ( id == InvalidGameObjectId )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            *iter = InvalidGameObjectId;
            continue;
        }

        GettheServer().SendMsgToSingle( pChar->FirstSightOnMe( szMsgBuff, sizeof(szMsgBuff)), pTarget );
    }
}

void NpcShipEx::CallEvent( uint8 eventType )
{
    switch ( eventType )
    {
    case 1:
        break;
    }
}

void NpcShipEx::Say( const char* pContent )
{
    if ( !HaveAreaPlayer() )
    { return; }

    MsgChat msgChat;
    msgChat.header.stID = GetID();
    HelperFunc::SafeNCpy( msgChat.chatHeader.szSpeakName, GetCharName(), sizeof( msgChat.chatHeader.szSpeakName ) );
    msgChat.SetString( pContent );
    GettheServer().SendMsgToView( &msgChat, GetID(), true );
}
