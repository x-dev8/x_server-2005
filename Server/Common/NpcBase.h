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
        short stQuestId; // ����Id
        char  chState;   // ״̬
        int   m_nVMId;   // �ű�Id
        short stEnter;   // �ű����
    };
    
    typedef std::vector<RelateQuestInfo>       RelateQuestInfoContainer;
    typedef RelateQuestInfoContainer::iterator ItrRelateQuestInfoContainer;

    //////////////////////////////////////////////////////////////////////////
    enum EAction
    { // ��������Ϊ
        //////////////////////////////////////////////////////////////////////////
        EAction_Prepare     , // ��ʼ��ʼ׼��
        EAction_Stop        , // ֹͣ����״̬
        EAction_WillMoveNext, // ׼���ƶ�����һ��(������,�ȴ�)
        EAction_MoveNext    , // �����ƶ�����һ��(��������,���ȴ�)
        EAction_StopToTalk  , // ͣ����˵��
        EAction_Moving      , // �ƶ���
        EAction_Waiting     , // �ȴ��ƶ���

        //////////////////////////////////////////////////////////////////////////
        EAction_SubActionBegin = 10 , // �������Ϊ
    };

public:
    NpcBase();
    virtual ~NpcBase();

    static uint8     GetObjecTypeByNpcType( uint8 npcType );

    virtual uint32   Init(){ return ER_Success; }
    virtual void     Run( DWORD dwCostTime );
    virtual bool     ProcessMsg( Msg* pMsg ){ return true; }
    virtual Msg*     FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); // ��һ��ӡ��
    virtual void     EnterMySight( BaseCharacter* pWho );
    virtual void     ExitMySight ( BaseCharacter* pWho );
    virtual void     OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame );
    virtual void     RefreshEnmity(){}
    virtual void     OnDeath(){}
    
    void             SetMoveStep( float moveStep ){ m_fMoveStep = moveStep; } // �ƶ�����
    float            GetMoveStep()                { return m_fMoveStep; }

    BOOL             AddRelateQuestInfo( RelateQuestInfo* pInfo );
    int              GetRelateQuestInfoCount() { return (int)_relateQuestInfo.size(); }
    RelateQuestInfo* GetRelateQuestInfo( int n );
    RelateQuestInfo* GetRelateQuestInfoByQuestID( int nQuestID );
    void             SetNpcType( ENpcType type ) { m_enNpcType = type; }
    
    void             SetNpcID( int npcId )                      { m_nNpcId = npcId; } // nNpcId_for_storage ��Npcslk������ֶ�npcID ���������Ϊ�����òֿ�NPC ��Ψһ��ţ�Ϊ���㲻ͬ�ֿ�ȡ����������̵�
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
    float                    m_fMoveStep         ; // �ƶ�����
    RelateQuestInfoContainer _relateQuestInfo    ; // �󶨵�����
    NpcInfo::Npc*            _pNpcInfo           ; // Npc info _bUseNpcInfoConfig==true ����Config������ false ���Լ�ά����New������
    bool                     _bIsConfigAddress   ; // �Ƿ���ָ��NpcInfo.h��ĵ�ַ
    SRoute                   _Route              ; // Npc��·��
    ENpcType                 m_enNpcType         ; // Npc����
    int                      m_nCurStep          ; // ��ǰ·�㲽
    DWORD                    m_dwWaitingStartTime;
    EAction                  m_enMoveState       ; // ��ǰ״̬
    int                      m_nTalkCount        ; // ��֮�Ի����ۼ���
    DWORD                    m_dwTalkTimeOut     ;
    int                      m_nNpcId            ; // NpcId
    std::string              m_strLastAnimName   ;
    DWORD                    m_dwLastUpdateMoveStateToPlayerTime;                
    DWORD                    m_DisappearTime     ; // ��ʧ��ʱ��
    GameTimerEx              _disappearTime      ; // ��ʧ��ʱ�����
    uint16                   m_n9AreaPlayerCnt   ; // ������Ұ�Ľ�ɫ��
    bool                     m_bShow             ; // �Ƿ���ʾ
    GameTimerEx              m_xHideTimer        ; // ����ʱ��
    GameTimerEx              m_xShowTimer        ; // ��ʾ��ʱ��
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
