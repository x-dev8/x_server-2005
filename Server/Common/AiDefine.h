#ifndef __MONSTERSERVERDEFINE_H__
#define __MONSTERSERVERDEFINE_H__

/************************************************************************
                怪物属性定义

************************************************************************/
#include <map>
#include <set>
#include <functional>
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
#include "MsgBase.h"
#include "MonsterDefine.h"

#define ENMITY_RATE           0.2f // 等级仇恨差比率

struct SPetItem;
namespace AiDefine
{
    enum EServerDefine
    {
        NoneEnmity = 0,                 // 无仇恨值
        EnmityReductionRate = 100,      // 怪物仇恨衰减比例
        EnmityBaseRate = 1000,          // 怪物仇恨衰减比例
        MinEnmityViewSight = 4,         // 最小仇恨视野

        MonsterMaxTaskCount  = 10,      // 怪物的任务队列长度
        MonsterMaxSkillCount = 3 ,      // 怪物技能的个数
        PetMonsterSkillIndex = 2 ,      // 宠物使用技能

        MonsterThinkTime = 1000,        // 怪物思考波动时间范围
        BaseThinkTime = 200,            // 宠物思考时间

        RefeshEnmitySpaceTime = 1000,   // 怪物仇恨刷新定时器
        MonsterIdleMoveRand =  10000,   // 怪物随即移动概率基数

        VerifyPointSpaceTime = 2000,    // 2秒同步怪物位置

        MonsterDeathScriptEnter = 1,    // 死亡脚本入口
        MonsterDefaultScriptEnter = 2,  // 状态改变默认脚本入口

        LostMasterKeepTime = 300000,    // 保护怪丢失主人后5分钟后消失

        AiTalkTimeOut = 2 * 60000,      // npc停下来对话超时时间

        MonsterMoveRadius = 2,
		MonsterUpdateBeLongTime=1000,	// 怪物归属的更新间隔

        ////////////////////////////////////////////////////////////////
        ProjectCharDistance = 10,       // 10 提示
        ProtectCharStopDistance = 20,   // 20 停止
        TellClientDisPerTime = 5000,    // 
        //////////////////////////////////////////////////////////
        // 怪物AI任务的优先级
        LowAiTaskPriority = 0,
        NormalAiTaskPriority,
        HighAiTaskPriority,

        /////////////////////////////////////////////////////////
        // 怪物创建方式
        NormalCreateType = 0,

        ////////////////////////////////////////////////////////////
        ThinkingDoNothing = 0   ,       // 啥也不干
        ThinkingMoveToBorn      ,       // 回到出生点
        ThinkingMoveAround      ,       // 周围随即移动
        ThinkingMoveToTarget    ,       // 移动到攻击目标
        ThinkingAttackTarget    ,       // 攻击目标
        ThinkingMoveToRoute     ,       // 移动到路点
        ThinkingMoveToLastIdle  ,       // 移动到最后没有被攻击的坐标
        ThinkingMoveToMaster    ,       // 移动到主人身边
        ThinkingFollowMaster    ,       // 跟随主人
        ThinkingWaitRelive      ,       // 死亡等待复活
        ThinkingStopToTalk      ,       // 停止移动与玩家对话
        ThinkingMoveToPoint     ,       // 移动到某一点
        ThinkingMoveEscape      ,       // 逃跑
        ThinkingIdle            ,       // 待机状态
        ThinkingRandRun         ,       // 随即乱跑( 中了乱跑状态 )

        /////////////////////////////////////////////////////////////
        LuaTimerCount = 3,              // Lua脚本定时器的数量
        LuaValueArrayCount = 10,  
    };

    enum EAiTimer
    {
        AiTimer_Thinking        = 0 ,   // AI思考
        AiTimer_IdleView            ,   // 怪物恢复非战斗视野
        AiTimer_Disappear           ,   // 怪物销毁
        AiTimer_Restore             ,   // 怪物回血, 回魔
        AiTimer_Move                ,   // 发送怪物位置消息
        AiTimer_Relive              ,   // 死亡复活
        AiTimer_Talk                ,   // 停下来对话
        AiTimer_StatusChange        ,   // 怪物状态改变
        AiTimer_KeepAttack          ,   // 怪物追击
        AiTimer_RouteMove           ,   // 路点移动停顿

        AiTimer_MaxCount             
    };
}

// 怪物仇恨
class EnmityData
{
public:
    EnmityData() : m_nEnmity( 0 ), m_nReduction( 0 ), m_nDamage( 0 ){}

    unsigned int GetEnmity() const { return m_nEnmity; }
    unsigned int GetReduction() const { return m_nReduction; }
    unsigned int GetDamage() const { return m_nDamage; }

    void SetEnmity( unsigned int nValue ) { m_nEnmity = nValue; }
    void SetReduction( unsigned int nValue ) { m_nReduction = nValue; }
    void SetDamage( unsigned int nValue ) { m_nDamage = nValue; }

    void AddEnmity( unsigned int nValue ) { m_nEnmity += nValue; }
    void AddDamage( unsigned int nValue ) { m_nDamage += nValue; }

    void DecEnmity( unsigned int nValue )
    {
        if ( m_nEnmity <= nValue )
        { m_nEnmity = 0; }
        else
        { m_nEnmity -= nValue; }
    }

    void ClearEnmity() { m_nEnmity = 0; m_nReduction = 0; m_nDamage = 0; }
    void ClearDamage() { m_nDamage = 0; }

    bool HaveEnmity() const { return m_nEnmity != AiDefine::NoneEnmity; }

private:
    // 怪物当前仇恨
    unsigned int m_nEnmity;          

     // 仇恨衰减基数( 每次衰减的数值 )
    unsigned int m_nReduction;      

    // 记录玩家对怪物的伤害总值 不影响怪物的攻击目标
    unsigned int m_nDamage; 
};


class AiEnmity
{
public:
    // 获得仇恨数量
    int GetEnmityCount() const { return static_cast< int >( m_mapTargetEnmity.size() ); }

    // 添加仇恨
    unsigned int AddEnmity( GameObjectId nID, unsigned int nEnmity, unsigned int nDamage, int nReductionRate = AiDefine::EnmityReductionRate );

    // 设置仇恨
    unsigned int SetEnmity( GameObjectId nID, unsigned int nEnmity, int nReductionRate = AiDefine::EnmityReductionRate );

    // 减少仇恨( 返回当前仇恨值 )
    unsigned int DecEnmity( GameObjectId nID, unsigned int nEnmity );

    // 删除仇恨列表
    void RemoveEnmity( GameObjectId nID );

    // 清除仇恨
    void ClearEnmity( bool bClearList );

    // 是否有仇恨
    bool HaveEnmity();

    // 获得仇恨属性
    EnmityData* GetEnmity( GameObjectId nID );

    // 获得仇恨值最大的角色
    GameObjectId GetMaxEnmityID();
         
    // 获得伤害最大的角色
    GameObjectId GetMaxDamageID();

    // 删除自己对目标的仇恨列表
    void RemoveAttackTarget( GameObjectId nID ) { m_setAttackTarget.erase( nID ); }

    // 添加自己对目标的仇恨列表
    void AddAttackTarget( GameObjectId nID ) { m_setAttackTarget.insert( nID ); }

    // 是否是攻击目标
    bool IsAttackTarget( GameObjectId nID ) { return m_setAttackTarget.find( nID ) != m_setAttackTarget.end(); }

	// 新仇恨目标接口
	virtual void OnNewEnmityTarget( GameObjectId nID ) {}

protected:
    typedef std::map< GameObjectId, EnmityData > TargetEnmityMap;
    typedef TargetEnmityMap::iterator TargetEnmityMapIter;

    typedef std::set< GameObjectId > AttackTargetSet;
    typedef AttackTargetSet::iterator AttackTargetSetIter;

    // 自己对别人产生的仇恨列表
    TargetEnmityMap m_mapTargetEnmity;   

    // 自己攻击的目标
    AttackTargetSet m_setAttackTarget;
};


///////////////////////////////////////////////
// 怪物AI技能
class AiSkill
{
public:

    AiSkill() : m_nID( 0 ), m_nLevel( 0 ), m_nUseRate( 0 ), m_nCostHP( 0 ), m_nCostMP( 0 ),
        m_nStartColdDownTime( 0 ), m_nColdDownTime( 0 ), m_nAttackDistance( 10 ){}

    unsigned short GetID() const { return m_nID; }
    unsigned char GetLevel() const { return m_nLevel; }
    unsigned short GetCostHP() const { return m_nCostHP; }
    unsigned short GetCostMP() const { return m_nCostMP; }
    unsigned int GetAttackDistance() const { return m_nAttackDistance; }
    unsigned char GetUseRate() const { return m_nUseRate; }
    unsigned int GetStartColdDownTime() const { return m_nStartColdDownTime; }
    unsigned int GetColdDownTime() const { return m_nColdDownTime; }

    void SetID( unsigned short nValue ) { m_nID = nValue; }
    void SetLevel( unsigned char nValue ) { m_nLevel = nValue; }
    void SetCostHP( unsigned short nValue ) { m_nCostHP = nValue; }
    void SetCostMP( unsigned short nValue ) { m_nCostMP = nValue; }
    void SetAttackDistance( unsigned int nValue ) { m_nAttackDistance = nValue; }
    void SetUseRate( unsigned char nValue ) { m_nUseRate = nValue; }
    void SetStartColdDownTime( unsigned int nValue ) { m_nStartColdDownTime = nValue; }
    void SetColdDownTime( unsigned int nValue ) { m_nColdDownTime = nValue; }

    bool CanUseAiSkill( uint32 nHP, uint32 nMP ) const;

private:
    // 技能ID
    unsigned short m_nID;

    // 技能等级
    unsigned char m_nLevel;    

    // 最低消耗HP
    unsigned short m_nCostHP;

    // 最低消耗MP
    unsigned short m_nCostMP;

    // 攻击距离
    unsigned int m_nAttackDistance;

    // 技能触发的概率
    unsigned char m_nUseRate;

    // 技能CD开始时间
    unsigned int m_nStartColdDownTime;

    // 技能的CD时间
    unsigned int m_nColdDownTime;
};

// 怪物AI任务队列
class AiTask : INHERIT_POOL_PARAM( AiTask, 100 )
{
public:
    DECLARE_POOL_FUNC( AiTask )

    AiTask() : m_nPriority( AiDefine::NormalAiTaskPriority ), m_nAttackID( -1 ), m_nSkillID( 0 ), m_nSkillLevel( 0 ){}
    virtual ~AiTask(){};

    unsigned char GetPriority() const { return m_nPriority; }
    GameObjectId GetAttackID() const { return m_nAttackID; }
    unsigned short GetSkillID() const { return m_nSkillID; }
    unsigned char GetSkillLevel() const { return m_nSkillLevel; }

    void SetPriority( unsigned char nValue ) { m_nPriority = nValue; }
    void SetAttackID( GameObjectId nValue ) { m_nAttackID = nValue; }
    void SetSkillID( unsigned short nValue ) { m_nSkillID = nValue; }
    void SetSkillLevel( unsigned char nValue ) { m_nSkillLevel = nValue; }

private:
    // 任务优先级
    unsigned char m_nPriority;

    // 要攻击的目标
    GameObjectId m_nAttackID;

    // 技能ID
    unsigned short m_nSkillID;

    // 技能等级
    unsigned char m_nSkillLevel;
};

// 按AITask优先级排序
inline bool SortAITaskPriority( const AiTask* pLeft, const AiTask* pRight )
{
    if ( pLeft == NULL || pRight == NULL )
    { return false; }

    return (pLeft -> GetPriority() >= pRight -> GetPriority());
}

////////////////////////////////////////////////////////////////////////
class MonsterCreateData
{
public:
    MonsterCreateData() 
    {
        memset( this, 0, sizeof( MonsterCreateData ) ); 
        m_nRouteID = -1;
        m_nMonsterIndex = -1;
        m_nCount = 1;
        m_pPetData = NULL;
    }

    unsigned int GetMapID() const { return m_nMapID; }
    float GetPostionX() const { return m_fX; }
    float GetPostionY() const { return m_fY; }
    float GetDirX() const { return m_fDirX; }
    float GetDirY() const { return m_fDirY; }
    int GetDirection() const { return m_nDirection; }
    float GetRadius() const { return m_fRadius; }
    float GetBodySize() const { return m_fBodySize; }
    int GetMonsterIndex() const { return m_nMonsterIndex; }
    int GetMonsterID() const { return m_nMonsterID; }
    short GetCount() const { return m_nCount; }
    short GetCreateType() const { return m_nCreateType; }
    short GetFightCamp() const { return m_nFightCamp; }
    short GetCountry() const { return m_nCountry; }
    short GetForce() const { return m_nForce; }
    short GetSpecialType() const { return m_nSpecialType; }
    unsigned int GetSpecialValue() const { return m_nSpecialValue; }
    int GetRouteID() const { return m_nRouteID; }
    const RECT& GetCanMoveZone() const { return m_xCanMoveZone; }
    int GetThinkingTime() const { return m_nThinkingTime; }
    int GetReliveTime() const { return m_nReliveTime; }
    SPetItem* GetPetItem() const { return m_pPetData; }
	bool IsCanRide() const { return m_bIsCanRide; }

    void SetMapID( unsigned int nValue ) { m_nMapID = nValue; }
    void SetPostionX( float fValue ) { m_fX = fValue; }
    void SetPostionY( float fValue ) { m_fY = fValue; }
    void SetDirection( int nValue ) { m_nDirection = nValue; }
    void SetDirX( float fValue ) { m_fDirX = fValue; }
    void SetDirY( float fValue ) { m_fDirY = fValue; }
    void SetRadius( float fValue ) { m_fRadius = fValue; }
    void SetBodySize( float fValue ){ m_fBodySize = fValue; }
    void SetMonsterIndex( int nValue ) { m_nMonsterIndex = nValue; }
    void SetMonsterID( int nValue ) { m_nMonsterID = nValue; }
    void SetCount( short nValue ) { m_nCount = nValue; }
    void SetCreateType( short nValue ) { m_nCreateType = nValue; }
    void SetFightCamp( short nValue ) { m_nFightCamp = nValue; }
    void SetCountry( short nValue ) { m_nCountry = nValue; }
    void SetForce( short nValue ) { m_nForce = nValue; }
    void SetSpecialType( short nValue ) { m_nSpecialType = nValue; }
    void SetSpecialValue( unsigned int nValue ) { m_nSpecialValue = nValue; }
    void SetRouteID( int nValue ) { m_nRouteID = nValue; }
    void SetCanMoveZone( RECT& xValue ) { m_xCanMoveZone = xValue; }
    void SetThinkingTime( int nValue ) { m_nThinkingTime = nValue; }
    void SetReliveTime( int nValue ) { m_nReliveTime = nValue; }
    void SetPetItem( SPetItem* pPetData ) { m_pPetData = pPetData; }
	void SetCanRide( bool b ) { m_bIsCanRide = b; }

private:
    unsigned int m_nMapID;
    float m_fX;
    float m_fY;
    float m_fDirX;
    float m_fDirY;
    int m_nDirection;       // 朝向角度
    float m_fRadius;        // 范围
    float m_fBodySize;      // 体型
    int m_nMonsterIndex;    // 生产序列号
    int m_nMonsterID;       // 怪物ID
    short m_nCount;         // 数量
    short m_nCreateType;    // 创建类型
    short m_nFightCamp;     // 阵营
    short m_nCountry;       // 国家
    short m_nForce;         // 势力
    short m_nSpecialType;   // 专属类型
    unsigned int m_nSpecialValue;  // 专属ID
    int m_nRouteID;                // 路点ID
    RECT m_xCanMoveZone;           // 可以移动的返回
    int m_nThinkingTime;           // 思考时间
    int m_nReliveTime;             // 死亡后多久复活
    SPetItem* m_pPetData;     // 宠物数据
	bool m_bIsCanRide;		// 能否被骑
};

#endif