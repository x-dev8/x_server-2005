/********************************************************************
    Filename:    NpcShip.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_NPCSHIP_H__
#define __COMMON_NPCSHIP_H__

#pragma once

#include "NpcBase.h"
#include "LuaPlus/LuaPlus.h"

const uint32 gNpcShipPoolBatchSize = 5;

// 要考虑的问题
class GamePlayer;

class NpcShip : public NpcBase,
                public DNpcNormalChar,
                INHERIT_POOL_PARAM( NpcShip, gNpcShipPoolBatchSize  )
{
public:
    enum EConstDefine
    {
        EConstDefine_MaxPlayerCount = 8, // 最大转载的角色个数
    };

public:
    DECLARE_POOL_FUNC( NpcShip )

    NpcShip();
    virtual ~NpcShip();

    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ static SCharFightAttr instance; return &instance; }    
    virtual void            SetHPMax( uint32 hpMax )    { _hpMax = hpMax; }
    virtual uint32          GetHPMax()                  { return _hpMax; }
    virtual float           GetMoveSpeed()              { return _speed;  }
    virtual void            SetMoveSpeed( float fMove ) { _speed = fMove; }

    //////////////////////////////////////////////////////////////////////////
    virtual uint32 Init();
    virtual void   OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame );
    virtual void   Run( DWORD dwCostTime );

    void    SendBeCarryPlayersTo( GamePlayer* pTarget ); // 发送在大载体上的角色信息给看到他的Player
    uint32  On ( GameObjectId playerId, uint8& pos );   // 上载体
    uint32  Off( GameObjectId playerId );               // 下载体

protected:
    virtual void Prepare();
    virtual void Moving( DWORD dwCostTime );
    virtual void Stop();

    uint32 InitLuaScript();
    // LuaInit LuaMovingTimerEvent

    //////////////////////////////////////////////////////////////////////////
    void  WaitPlayerTime( uint32 time )     { _waitPlayerTime = time; } // 设置等待玩家上坐骑的时间
    void  MovingEventInterval( uint32 time ){ _movingEventInterval = time; } // 设置等待玩家上坐骑的时间
    void  CallEvent( uint8 eventType );
    void  Say( const char* pContent );                             // 呐喊

protected:
    typedef std::vector<GameObjectId> PlayerContainer;
    typedef PlayerContainer::iterator  PlayerContainerItr;

    PlayerContainer _players ; // 被装载的角色
    LuaStateOwner   _luaScript; // 创建Lua解释器

    uint32          _waitPlayerTime;  // 等待玩家时间 s
    GameTimerEx     _waitPlayerTimer; // 等待玩家的计时器
    
    uint32          _movingEventInterval; // 移动定时触发事件间隔时间
    GameTimerEx     _movingEventTimer;    // 移动定时触发事件计时器
    uint32          _movingEventCounter;  // 移动定时器触发次数
};

#endif // __COMMON_NPCSHIP_H__
