#ifndef __NPCBASEEX_H
#define __NPCBASEEX_H

/************************************************************************
                  npc基类
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

    // 获得玩家购买道具的花费类型
    static uint8 GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem ); 

    // 获得玩家卖给NPC道具价格
    static int32 GetPlayerSellNpcItemCost( uint16 itemId, uint16 count );                  

    // 获得玩家装备回收价格
    static int32 GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count );           
    ///////////////////////////////////////////////////////////////////////////////////////////
    // 是否是NPC
    virtual bool IsNpc() { return true; }

    // 判断是否能被攻击
    virtual bool CheckCanBeAttack() { return false; }   

    // 执行update
    virtual void Run( uint32 dwCostTime );

    // 第一眼印象
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    //////////////////////////////////////////////////////////////////////////////////////////////
    // 初始化npc信息
    virtual void Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn = false );

    // 设置消失
    void SetDisappear( uint32 nTime );

    // 获得显示或者隐藏
    bool GetShow() { return m_bShow; }

    // 设置显示或者隐藏  [bInit]防止多线程发消息
    void SetShow( bool bValue ,bool bInit = false);
    
    // 开始显示定时器
    void StartShowTimer( unsigned int nStartTime, unsigned int nSpaceTime );
   
    // 开始隐藏定时器
    void StartHideTimer( unsigned int nStartTime, unsigned int nSpaceTime );

    // 处理显示和隐藏
    void ProcessShowAndHide();

    // 获得脚本信息数量
    int GetQuestScriptCount() { return static_cast< int >( m_vecQuestScript.size() ); }

    // 添加脚本信息
    void AddQuestScript( QuestScript& xInfo );

    // 获得脚本信息
    QuestScript* GetQuestScriptByIndex( unsigned int nIndex );
    QuestScript* GetQuestScriptByQuestID( int nQuestID );

    void UpdateMoveRouteToPlayer( GamePlayer* pPlayer );

    void SetLastAnimName( const char* szName );
    const char* GetLastAnimName();

    void SetNewConfig( bool bValue ) { m_bNewConfig = bValue; }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // 获得NPC类型
    int GetNpcType()	{ return m_pNpcInfo->type; }

    // 获得NPCid
    int GetNpcID()		{ return m_pNpcInfo->id; }

	int GetInitVMId()	{ return nInitVMId; }

    // 获取NPC的种族
    virtual unsigned char GetPhyle() const { return m_pNpcInfo->phyle; }

protected:
    //////////////////////////////////////////////////////////////////////////////////////////////
    // npc不刷仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime ){}

    // npc不找攻击目标
    virtual void ProcessFindAttackTarget(){}

    // 死亡调用脚本
    virtual void ProcessDeathCallScript();

    // 死亡状态改变
    virtual void ProcessDeathExitWorld();

    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    ////////////////////////////////////////////////////////////////////////////////////////////////
protected:
    
    typedef std::vector< QuestScript > QuestScriptVector;
    typedef QuestScriptVector::iterator QuestScriptVectorIter;

    // NPC上挂的脚本
    QuestScriptVector m_vecQuestScript;

    // npc配置信息
    NpcInfo::Npc* m_pNpcInfo;

    // 是否是new出来的内存
    bool m_bNewConfig;

    // 上一次播放的动作
    std::string m_strLastAnimName;

    // 是否显示
    bool m_bShow; 

    // 隐身定时器
    GameTimerEx m_xHideTimer; 

    // 显示定时器
    GameTimerEx m_xShowTimer; 

	// 用来保存初始化脚本的vmId
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