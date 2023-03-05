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

// Ҫ���ǵ�����
class GamePlayer;

class NpcShip : public NpcBase,
                public DNpcNormalChar,
                INHERIT_POOL_PARAM( NpcShip, gNpcShipPoolBatchSize  )
{
public:
    enum EConstDefine
    {
        EConstDefine_MaxPlayerCount = 8, // ���ת�صĽ�ɫ����
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

    void    SendBeCarryPlayersTo( GamePlayer* pTarget ); // �����ڴ������ϵĽ�ɫ��Ϣ����������Player
    uint32  On ( GameObjectId playerId, uint8& pos );   // ������
    uint32  Off( GameObjectId playerId );               // ������

protected:
    virtual void Prepare();
    virtual void Moving( DWORD dwCostTime );
    virtual void Stop();

    uint32 InitLuaScript();
    // LuaInit LuaMovingTimerEvent

    //////////////////////////////////////////////////////////////////////////
    void  WaitPlayerTime( uint32 time )     { _waitPlayerTime = time; } // ���õȴ�����������ʱ��
    void  MovingEventInterval( uint32 time ){ _movingEventInterval = time; } // ���õȴ�����������ʱ��
    void  CallEvent( uint8 eventType );
    void  Say( const char* pContent );                             // �ź�

protected:
    typedef std::vector<GameObjectId> PlayerContainer;
    typedef PlayerContainer::iterator  PlayerContainerItr;

    PlayerContainer _players ; // ��װ�صĽ�ɫ
    LuaStateOwner   _luaScript; // ����Lua������

    uint32          _waitPlayerTime;  // �ȴ����ʱ�� s
    GameTimerEx     _waitPlayerTimer; // �ȴ���ҵļ�ʱ��
    
    uint32          _movingEventInterval; // �ƶ���ʱ�����¼����ʱ��
    GameTimerEx     _movingEventTimer;    // �ƶ���ʱ�����¼���ʱ��
    uint32          _movingEventCounter;  // �ƶ���ʱ����������
};

#endif // __COMMON_NPCSHIP_H__
