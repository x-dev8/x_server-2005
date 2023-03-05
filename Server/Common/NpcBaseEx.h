#ifndef __NPCBASEEX_H
#define __NPCBASEEX_H

/************************************************************************
                  npc����
                  Filename:     NpcBaseEx.h
                  MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "AiCharacter.h"
#include "NpcInfo.h"

class NpcBaseEx : public AiCharacter
{
public:
    NpcBaseEx();
    virtual ~NpcBaseEx();

    //////////////////////////////////////////////////////////////////////////////////////////

    // �����ҹ�����ߵĻ�������
    static uint8 GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem ); 

    // ����������NPC���߼۸�
    static int32 GetPlayerSellNpcItemCost( uint16 itemId, uint16 count );                  

    // ������װ�����ռ۸�
    static int32 GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count );           
    ///////////////////////////////////////////////////////////////////////////////////////////
    // �Ƿ���NPC
    virtual bool IsNpc() { return true; }

    // �ж��Ƿ��ܱ�����
    virtual bool CheckCanBeAttack() { return false; }   

    // ִ��update
    virtual void Run( uint32 dwCostTime );

    // ��һ��ӡ��
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    //////////////////////////////////////////////////////////////////////////////////////////////
    // ��ʼ��npc��Ϣ
    virtual void Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn = false );

    // ������ʧ
    void SetDisappear( uint32 nTime );

    // �����ʾ��������
    bool GetShow() { return m_bShow; }

    // ������ʾ��������  [bInit]��ֹ���̷߳���Ϣ
    void SetShow( bool bValue ,bool bInit = false);
    
    // ��ʼ��ʾ��ʱ��
    void StartShowTimer( unsigned int nStartTime, unsigned int nSpaceTime );
   
    // ��ʼ���ض�ʱ��
    void StartHideTimer( unsigned int nStartTime, unsigned int nSpaceTime );

    // ������ʾ������
    void ProcessShowAndHide();

    // ��ýű���Ϣ����
    int GetQuestScriptCount() { return static_cast< int >( m_vecQuestScript.size() ); }

    // ��ӽű���Ϣ
    void AddQuestScript( QuestScript& xInfo );

    // ��ýű���Ϣ
    QuestScript* GetQuestScriptByIndex( unsigned int nIndex );
    QuestScript* GetQuestScriptByQuestID( int nQuestID );

    void UpdateMoveRouteToPlayer( GamePlayer* pPlayer );

    void SetLastAnimName( const char* szName );
    const char* GetLastAnimName();

    void SetNewConfig( bool bValue ) { m_bNewConfig = bValue; }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // ���NPC����
    int GetNpcType()	{ return m_pNpcInfo->type; }

    // ���NPCid
    int GetNpcID()		{ return m_pNpcInfo->id; }

	int GetInitVMId()	{ return nInitVMId; }

    // ��ȡNPC������
    virtual unsigned char GetPhyle() const { return m_pNpcInfo->phyle; }

protected:
    //////////////////////////////////////////////////////////////////////////////////////////////
    // npc��ˢ���
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime ){}

    // npc���ҹ���Ŀ��
    virtual void ProcessFindAttackTarget(){}

    // �������ýű�
    virtual void ProcessDeathCallScript();

    // ����״̬�ı�
    virtual void ProcessDeathExitWorld();

    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    ////////////////////////////////////////////////////////////////////////////////////////////////
protected:
    
    typedef std::vector< QuestScript > QuestScriptVector;
    typedef QuestScriptVector::iterator QuestScriptVectorIter;

    // NPC�ϹҵĽű�
    QuestScriptVector m_vecQuestScript;

    // npc������Ϣ
    NpcInfo::Npc* m_pNpcInfo;

    // �Ƿ���new�������ڴ�
    bool m_bNewConfig;

    // ��һ�β��ŵĶ���
    std::string m_strLastAnimName;

    // �Ƿ���ʾ
    bool m_bShow; 

    // ����ʱ��
    GameTimerEx m_xHideTimer; 

    // ��ʾ��ʱ��
    GameTimerEx m_xShowTimer; 

	// ���������ʼ���ű���vmId
	int nInitVMId;
};


//////////////////////////////////////////////////////////////////////////////////////

inline void NpcBaseEx::AddQuestScript( QuestScript& xInfo )
{
    m_vecQuestScript.push_back( xInfo );
}


inline void NpcBaseEx::SetLastAnimName( const char* szName )
{
    if ( !szName )
    { return; }
    m_strLastAnimName = szName;
}

inline const char* NpcBaseEx::GetLastAnimName()
{
    return m_strLastAnimName.c_str();
}

#endif