#ifndef __NPCSHIPEX_H__
#define __NPCSHIPEX_H__

/********************************************************************
        NPC ������
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
        MaxPlayerCount = 8, // ���ת�صĽ�ɫ����
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

    void SendBeCarryPlayersTo( GamePlayer* pTarget );    // �����ڴ������ϵĽ�ɫ��Ϣ����������Player
    uint32 OnShip( GameObjectId playerId, uint8& pos );  // ������
    uint32 OffShip( GameObjectId playerId );             // ������

protected:
    //////////////////////////////////////////////////////////////////////////

    bool InitLuaScript();

    // ���õȴ�����������ʱ��
    void WaitPlayerTime( uint32 nValue ) { m_xTimer[ AiDefine::AiTimer_Talk ].SetSpaceTime( nValue * 1000 ); } 

     // ���õȴ�����������ʱ��
    void MovingEventInterval( uint32 nValue ) { m_xMovingEventTimer.SetSpaceTime( nValue * 1000 ); }
    void CallEvent( uint8 eventType );

    // �ź�
    void Say( const char* pContent );      

protected:
    typedef std::vector< GameObjectId > PlayerVector;
    typedef PlayerVector::iterator  PlayerVectorIter;

    PlayerVector    m_vecPlayers ;  // ��װ�صĽ�ɫ
    LuaStateOwner   m_xLuaScript;   // ����Lua������
    GameTimerEx     m_xMovingEventTimer;    // �ƶ���ʱ�����¼���ʱ��
    uint32          m_nMovingEventCounter;  // �ƶ���ʱ����������

};

#endif