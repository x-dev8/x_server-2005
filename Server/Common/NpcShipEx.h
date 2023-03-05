#ifndef __NPCSHIPEX_H__
#define __NPCSHIPEX_H__

/********************************************************************
        NPC 大载体
        Filename:    NpcShipEx.h
        MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "NpcBaseEx.h"
#include "LuaPlus/LuaPlus.h"

class NpcShipEx : public NpcBaseEx, INHERIT_POOL_PARAM( NpcShipEx, 5 )
{
public:
    enum EConstDefine
    {
        MaxPlayerCount = 8, // 最大转载的角色个数
    };

    DECLARE_POOL_FUNC( NpcShipEx )

    NpcShipEx();
    virtual ~NpcShipEx();

    //////////////////////////////////////////////////////////////////////////////////
    virtual void Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn = false );

    virtual void OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame );
    
    virtual void Run( DWORD dwCostTime );

    virtual void ProcessAiMoving( uint32 nCostTime );

    virtual void ProcessArriveRoute();
    //////////////////////////////////////////////////////////////////////

    void SendBeCarryPlayersTo( GamePlayer* pTarget );    // 发送在大载体上的角色信息给看到他的Player
    uint32 OnShip( GameObjectId playerId, uint8& pos );  // 上载体
    uint32 OffShip( GameObjectId playerId );             // 下载体

protected:
    //////////////////////////////////////////////////////////////////////////

    bool InitLuaScript();

    // 设置等待玩家上坐骑的时间
    void WaitPlayerTime( uint32 nValue ) { m_xTimer[ AiDefine::AiTimer_Talk ].SetSpaceTime( nValue * 1000 ); } 

     // 设置等待玩家上坐骑的时间
    void MovingEventInterval( uint32 nValue ) { m_xMovingEventTimer.SetSpaceTime( nValue * 1000 ); }
    void CallEvent( uint8 eventType );

    // 呐喊
    void Say( const char* pContent );      

protected:
    typedef std::vector< GameObjectId > PlayerVector;
    typedef PlayerVector::iterator  PlayerVectorIter;

    PlayerVector    m_vecPlayers ;  // 被装载的角色
    LuaStateOwner   m_xLuaScript;   // 创建Lua解释器
    GameTimerEx     m_xMovingEventTimer;    // 移动定时触发事件计时器
    uint32          m_nMovingEventCounter;  // 移动定时器触发次数

};

#endif