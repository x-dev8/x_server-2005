#include "NpcShip.h"
#include "GamePlayer.h"
#include "ShareData.h"

NpcShip::NpcShip() : _luaScript( false )
{
    SetObjType( Object_NpcShip );
    _players.resize( EConstDefine_MaxPlayerCount, InvalidGameObjectId );
    _waitPlayerTime = 1000; // 默认一秒
    _movingEventInterval = 5000; // 5秒
    _movingEventCounter  = 0;
}

NpcShip::~NpcShip()
{
    try
    {
        _luaScript->PushNil();
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Npc %s AI Failed: %s", _pNpcInfo->name.c_str(), e.GetErrorMessage());
    }
}

uint32 NpcShip::Init()
{
    uint32 result = InitLuaScript();
    if ( result != ER_Success )
    { return ER_Failed; }

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
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Npc %s LuaInit Failed: %s", _pNpcInfo->name.c_str(), e.GetErrorMessage());
    }
    return ER_Success;
}

void NpcShip::OnExit( Msg* pMsg, unsigned char exitType )
{
    // 所有人下大载体
    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if ( pChar == NULL || !pChar->IsPlayer())
        { continue; }

        GamePlayer* pGamePlayer = (GamePlayer*)pChar;

        pGamePlayer->OffNpcShip();
    }
    
    _players.clear();

    NpcBase::OnExit( pMsg, exitType );
}

void NpcShip::Run( DWORD dwCostTime )
{
    NpcBase::Run(dwCostTime);
}

uint32 NpcShip::On( GameObjectId playerId, uint8& pos )
{
    int8 curPos = 0;
    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        if ( *it != InvalidGameObjectId )
        {
            ++curPos;
            continue;
        }
        
        *it = playerId;
        pos = curPos;
        return ER_Success;
    }

    return ER_Failed;
}

uint32 NpcShip::Off( GameObjectId playerId )
{
    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        if ( playerId != *it )
        { continue; }

        *it = InvalidGameObjectId; 
        return ER_Success;
    }

    return ER_Failed;
}

void NpcShip::Prepare()
{
    _waitPlayerTimer.StartTimer( HQ_TimeGetTime(), _waitPlayerTime * 1000 );
    if ( _waitPlayerTimer.DoneTimer())
    {
        SetMoveState( EAction_WillMoveNext );
    }
}

void NpcShip::Moving( DWORD dwCostTime )
{
    NpcBase::Moving( dwCostTime );

    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end();  )
    {
        GameObjectId id = (*it);
        if ( id == InvalidGameObjectId )
        { 
            ++it;
            continue; 
        }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            it = _players.erase( it );
            continue;
        }

        pChar->SetFloatXF( GetFloatX() );
        pChar->SetFloatYF( GetFloatY() );
        pChar->SetDirX( GetDirX() );
        pChar->SetDirY( GetDirY() );

        ++it;
    }

    _movingEventTimer.StartTimer( HQ_TimeGetTime() , _movingEventInterval );
    if ( _movingEventTimer.DoneTimer( HQ_TimeGetTime()))
    {
        try
        {
            LuaObject luaobject = _luaScript->GetGlobal("LuaMovingTimerEvent");
            if(luaobject.IsFunction())
            { 
                LuaFunction<void> LuaMovingTimerEvent(luaobject);
                LuaMovingTimerEvent( _movingEventCounter++ );
            }
        }
        catch ( LuaPlus::LuaException& e )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Npc %s LuaInit Failed: %s", _pNpcInfo->name.c_str(), e.GetErrorMessage());
        }
    }
}

void NpcShip::Stop()
{
    _waitPlayerTimer.StopTimer();
    _movingEventTimer.StopTimer();
    _movingEventCounter = 0;
}

uint32 NpcShip::InitLuaScript()
{
    try
    {
        LuaObject metaTableObj;
        metaTableObj = _luaScript->GetGlobals().CreateTable("MultiObjectMetaTable");
        metaTableObj.SetObject("__index", metaTableObj );
        metaTableObj.RegisterObjectDirect( "WaitPlayerTime",      (NpcShip*)0, &NpcShip::WaitPlayerTime      );
        metaTableObj.RegisterObjectDirect( "MovingEventInterval", (NpcShip*)0, &NpcShip::MovingEventInterval );
        metaTableObj.RegisterObjectDirect( "Say",                 (NpcShip*)0, &NpcShip::Say                 );
        metaTableObj.RegisterObjectDirect( "CallEvent",           (NpcShip*)0, &NpcShip::CallEvent           );

        LuaObject CAICharacterCoreObj = _luaScript->BoxPointer(this);
        CAICharacterCoreObj.SetMetaTable(metaTableObj);
        _luaScript->GetGlobals().SetObject( "Npc", CAICharacterCoreObj );

        std::string strFilePath;
        strFilePath += SCRIPT_ROOTDIRECTORY;
        strFilePath += _pNpcInfo->actionScript;
        if( LUA_ERRFILE==_luaScript->LoadFile( strFilePath.c_str() ) )
        { 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Npc %s InitLuaScript(%s) Failed", _pNpcInfo->name.c_str(),strFilePath.c_str() );
            return ER_Failed; 
        }
        _luaScript->Call( 0, 0 );
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Npc %s AI script failed:%s", GetCharName(), e.GetErrorMessage() );
        return ER_Failed;
    }

    return ER_Success;
}

void NpcShip::SendBeCarryPlayersTo( GamePlayer* pTarget )
{
    char szMsgBuff[1024] = {0};

    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        GameObjectId id = (*it);
        if ( id == InvalidGameObjectId )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            *it = InvalidGameObjectId;
            continue;
        }

        GettheServer().SendMsgToSingle( pChar->FirstSightOnMe( szMsgBuff, sizeof(szMsgBuff)), pTarget );
    }
}

void NpcShip::CallEvent( uint8 eventType )
{
    switch ( eventType )
    {
    case 1:
    	break;
    }
}

void NpcShip::Say( const char* pContent )
{
    if ( !AreaHavePlayer() )
    { return; }

    MsgChat msgChat;
    msgChat.header.stID = GetID();
    HelperFunc::SafeNCpy( msgChat.chatHeader.szSpeakName, GetCharName(), sizeof( msgChat.chatHeader.szSpeakName ) );
    msgChat.SetString( pContent );
    GettheServer().SendMsgToView( &msgChat, GetID(), true );
}
