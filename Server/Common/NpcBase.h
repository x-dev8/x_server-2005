/********************************************************************
    Filename:     NpcBase.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_NPCBASECHARACTER_H__
#define __GAMESERVER_NPCBASECHARACTER_H__

#pragma once

#include "BaseCharacter.h"
#include "NpcInfo.h"

class GamePlayer;

const uint32 gNpcPoolBatchSize = 10;

class NpcBase : public BaseCharacter
{
public:
    struct RelateQuestInfo
    {
        RelateQuestInfo() : m_nVMId(-1) {}
        short stQuestId; // 任务Id
        char  chState;   // 状态
        int   m_nVMId;   // 脚本Id
        short stEnter;   // 脚本入口
    };
    
    typedef std::vector<RelateQuestInfo>       RelateQuestInfoContainer;
    typedef RelateQuestInfoContainer::iterator ItrRelateQuestInfoContainer;

    //////////////////////////////////////////////////////////////////////////
    enum EAction
    { // 基础的行为
        //////////////////////////////////////////////////////////////////////////
        EAction_Prepare     , // 开始开始准备
        EAction_Stop        , // 停止待机状态
        EAction_WillMoveNext, // 准备移动到下一点(做动作,等待)
        EAction_MoveNext    , // 马上移动到下一点(不做动作,不等待)
        EAction_StopToTalk  , // 停下来说话
        EAction_Moving      , // 移动中
        EAction_Waiting     , // 等待移动中

        //////////////////////////////////////////////////////////////////////////
        EAction_SubActionBegin = 10 , // 子类的行为
    };

public:
    NpcBase();
    virtual ~NpcBase();

    static uint8     GetObjecTypeByNpcType( uint8 npcType );

    virtual uint32   Init(){ return ER_Success; }
    virtual void     Run( DWORD dwCostTime );
    virtual bool     ProcessMsg( Msg* pMsg ){ return true; }
    virtual Msg*     FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); // 第一眼印象
    virtual void     EnterMySight( BaseCharacter* pWho );
    virtual void     ExitMySight ( BaseCharacter* pWho );
    virtual void     OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame );
    virtual void     RefreshEnmity(){}
    virtual void     OnDeath(){}
    
    void             SetMoveStep( float moveStep ){ m_fMoveStep = moveStep; } // 移动步长
    float            GetMoveStep()                { return m_fMoveStep; }

    BOOL             AddRelateQuestInfo( RelateQuestInfo* pInfo );
    int              GetRelateQuestInfoCount() { return (int)_relateQuestInfo.size(); }
    RelateQuestInfo* GetRelateQuestInfo( int n );
    RelateQuestInfo* GetRelateQuestInfoByQuestID( int nQuestID );
    void             SetNpcType( ENpcType type ) { m_enNpcType = type; }
    
    void             SetNpcID( int npcId )                      { m_nNpcId = npcId; } // nNpcId_for_storage 是Npcslk表里的字段npcID 这个函数是为了设置仓库NPC 的唯一编号，为计算不同仓库取物件费用做铺垫
    int              GetNpcID()                                 { return m_nNpcId;               }
    ENpcType         GetNpcType()                               { return m_enNpcType;            }
    void             SetNpcInfoIsConfigAddress( bool bIsConfig ){ _bIsConfigAddress = bIsConfig; }
    void             SetNpcInfo( NpcInfo::Npc* pNpc )           { _pNpcInfo = pNpc;              }
    bool             InitRoute();
    void             SetMoveState( EAction state ){ m_enMoveState = state; }
    EAction          GetMoveState()               { return m_enMoveState;  }
    void             BeginTalk();
    void             EndTalk();
    void             MoveNext();
    void             UpdateMoveStateToPlayer( BaseCharacter* pPlayer = NULL );
    void             SetLastAnimName( const char* szName );
    const char*      GetLastAnimName();
    bool             SetDisappearTime( uint32 DisappearTime );
    void             CallQuestScript( RelateQuestInfo* pInfo, GamePlayer* pPlayer, int nNpcID );
    bool             GetShow() { return m_bShow; }
    void             SetShow( bool bValue );
    void             StartShowTimer( unsigned int nStartTime, unsigned int nSpaceTime );
    void             StartHideTimer( unsigned int nStartTime, unsigned int nSpaceTime );
    bool             AreaHavePlayer() { return m_n9AreaPlayerCnt > 0; }

protected:
    SMovePos*        GetCurrentStepMovePos();

    virtual void     ProcessMoveAbout( DWORD dwCostTime );
    virtual void     ProcessSubAction( DWORD dwCostTime );

    virtual void     Prepare();
    virtual void     Moving( DWORD dwCostTime );
    virtual void     MoveWillMoveNext();
    virtual void     MoveMoveNext();    
    virtual void     MoveStopToTalk();
    virtual void     Waiting();
    virtual void     Stop();

protected:
    float                    m_fMoveStep         ; // 移动步长
    RelateQuestInfoContainer _relateQuestInfo    ; // 绑定的任务
    NpcInfo::Npc*            _pNpcInfo           ; // Npc info _bUseNpcInfoConfig==true 引用Config中数据 false 是自己维护的New出来的
    bool                     _bIsConfigAddress   ; // 是否是指向NpcInfo.h里的地址
    SRoute                   _Route              ; // Npc的路点
    ENpcType                 m_enNpcType         ; // Npc类型
    int                      m_nCurStep          ; // 当前路点步
    DWORD                    m_dwWaitingStartTime;
    EAction                  m_enMoveState       ; // 当前状态
    int                      m_nTalkCount        ; // 与之对话的累加数
    DWORD                    m_dwTalkTimeOut     ;
    int                      m_nNpcId            ; // NpcId
    std::string              m_strLastAnimName   ;
    DWORD                    m_dwLastUpdateMoveStateToPlayerTime;                
    DWORD                    m_DisappearTime     ; // 消失的时间
    GameTimerEx              _disappearTime      ; // 消失的时间控制
    uint16                   m_n9AreaPlayerCnt   ; // 进入视野的角色数
    bool                     m_bShow             ; // 是否显示
    GameTimerEx              m_xHideTimer        ; // 隐身定时器
    GameTimerEx              m_xShowTimer        ; // 显示定时器
};

//////////////////////////////////////////////////////////////////////////
// inline
inline NpcBase::RelateQuestInfo* NpcBase::GetRelateQuestInfoByQuestID( int nQuestID )
{
    ItrRelateQuestInfoContainer iter = _relateQuestInfo.begin();
    for ( ; iter != _relateQuestInfo.end(); ++iter  )
    {
        if ( iter->stQuestId == nQuestID )
        {
            return &( *iter );
        }
    }
    return NULL;
}

#endif // __GAMESERVER_NPC_H__
