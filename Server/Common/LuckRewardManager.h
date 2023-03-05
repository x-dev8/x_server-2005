#ifndef __LUCKREWARDMANAGER_H__
#define __LUCKREWARDMANAGER_H__
/************************************************************************
                        幸运15关相关逻辑
             Filename:     LuckReward.h
             MaintenanceMan Mail: lori227@live.cn
************************************************************************/


#include "Memory_pool.h"
#include "LuckRewardConfig.h"
#include "MessageDefine.h"
#include "DropItem.h"

enum ELuckRewardManagerConstDefine
{
    ECD_LuckReward_TimeOut = 60000 * 5,
};

class LuckReward : INHERIT_POOL_PARAM( LuckReward, 50 )
{
public:
    typedef std::vector< char > RewardVec;
    typedef RewardVec::iterator RewardVecIter;
public:
    static LuckReward* CreateLuckReward(){ return CNewWithDebug< LuckReward >::Alloc( 1, "LuckReward::CreateLuckReward中创建CreateLuckReward实例" ); }
    virtual void Release() { CNewWithDebug< LuckReward >::Free( this ); }

    LuckReward() : m_uchMaxLevel( ECD_Reward_MaxLevel ), m_ustSummonCount( 0 )
    {
        m_uchLevel      = ECD_Reward_MinLevel;              // 初始第一关
        m_dwTimeOut     = ECD_LuckReward_TimeOut;
        m_bCanLuck      = false;
        m_bHasPlay      = false;
        m_bIsLucking    = false;
        m_uchRewardType = ECD_RandType_Init;
        m_vecReward.clear();

        m_dwMapID       = 0;
    }

    void SetLevel( unsigned char uchValue ) 
    { 
        if ( uchValue < ECD_Reward_MinLevel )
            uchValue = ECD_Reward_MinLevel;
        if ( uchValue > m_uchMaxLevel )
            uchValue = m_uchMaxLevel;

        m_uchLevel = uchValue; 
    }

    void SetTimeOut( unsigned int dwTimeOut )
    {
        if ( dwTimeOut > ECD_LuckReward_TimeOut )
            dwTimeOut = ECD_LuckReward_TimeOut;

        m_dwTimeOut = dwTimeOut;
    }

    void SetID( unsigned int dwID )                { m_dwID = dwID; }
    void SetCanPlay( bool bValue )                 { m_bCanLuck = bValue; }
    void SetHasPlay( bool bValue )                 { m_bHasPlay = bValue; }
    void SetIsLucking( bool bValue )               { m_bIsLucking = bValue; }
    void SetRewardType( unsigned char chType )     { m_uchRewardType = chType; }
    void SetMaxLevel( unsigned char uchMaxLevel )  { m_uchMaxLevel = uchMaxLevel; }
    void SetMapID( unsigned int dwMapID )          { m_dwMapID = dwMapID; }
    void SetFloatX( float fX )                     { m_fX = fX; }
    void SetFloatY( float fY )                     { m_fY = fY; }
    void SetSummonCount( unsigned short ustCount ) { m_ustSummonCount = ustCount; }

    const unsigned int GetID() const            { return m_dwID; }
    const unsigned char GetLevel() const        { return m_uchLevel; }
    const unsigned int GetTimeOut() const       { return m_dwTimeOut; }
    const bool GetCanPlay() const               { return m_bCanLuck; }
    const bool GetHasPlay() const               { return m_bHasPlay; }   
    const bool GetIsLucking() const             { return m_bIsLucking; }
    const unsigned char GetRewardType() const   { return m_uchRewardType; }
    const unsigned char GetMaxLevel() const     { return m_uchMaxLevel; }
    const unsigned int GetMapID() const         { return m_dwMapID; }
    const float GetFloatX() const               { return m_fX; }
    const float GetFloatY() const               { return m_fY; }
    const unsigned short GetSummonCount() const { return m_ustSummonCount; }

    bool IsCanGetReward();                              // 只有这3中情况能领取奖品
    bool IsCanNextLuckLevel();                         // 判断能否前往下一关
    bool IsCanAcceptQuest( unsigned char uchLevel );    // 判断是否能接任务( 也就是刷怪物 )
    bool IsCanLuckReward();                             // 判断是否能摇奖
    void ClearReward() { m_vecReward.clear(); }
    void AddReward( char chIndex )      // 添加奖励物品
    {
        if ( chIndex < 0 )
        { return; }
        
        m_vecReward.push_back( chIndex );
    }
    void CopyReward( MsgTellLuckReward& xReward );              // 读取配置表时发送具体奖励内容

    unsigned int GetRewardCount() { return static_cast< unsigned int > ( m_vecReward.size() ); }
    bool IsHasReward() { return !m_vecReward.empty(); }
    RewardVec& GetReward() { return m_vecReward; }

private:
    // 禁止拷贝 复制
    LuckReward( const LuckReward& );            
    LuckReward& operator = ( const LuckReward& );

private:        
    unsigned int m_dwID;              // 队伍模式是队伍ID 个人模式是DBID
    unsigned char m_uchLevel;         // 当前第几关
    unsigned int m_dwTimeOut;         // 超时时间
    bool m_bCanLuck;                  // ( 完成任务才能玩摇奖游戏 )
    bool m_bHasPlay;                  // 是否已经玩过了 
    bool m_bIsLucking;                // 客户端是否正在转盘
    unsigned char m_uchRewardType;    // 当前随即到得奖励类型
    unsigned char m_uchMaxLevel;      // 最大多少关
    RewardVec m_vecReward;            // 此关的奖励东西

    unsigned short m_ustSummonCount;  // 召唤怪物次数

    // 接任务时候的地图坐标
    unsigned int m_dwMapID;
    float m_fX;
    float m_fY;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >             
class LuckRewardManager
{
public:
    ~LuckRewardManager();

    static LuckRewardManager& Instance()
    {
        static LuckRewardManager s_xLuckRewardManager;
        return s_xLuckRewardManager;
    }

    void LuckRewardUpdate();                                           // 更新
    LuckReward* GetLuckReward( unsigned int dwID );                    // 查找
    bool AddLuckReward( unsigned int dwID, LuckReward* pLuckReward );  // 添加
    bool RemoveLuckReward( unsigned int dwID );                        // 删除一个
    bool IsInLuckReward( unsigned int dwID );                          // 是否在玩幸运15关
    void RunLuckReward( LuckReward* pLuckReward );                     // 执行摇奖结果
    bool ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bReceive = true );          // 处理领取奖品逻辑
    void ReceiveLuckReward( LuckReward* pLuckReward );                 // 领取奖励
    void StartLuckReward( LuckReward* pLuckReward );                   // 客户端开始转盘
    void ShowLuckReward( LuckReward* pLuckReward, unsigned char uchShowType );
    void RandLuckReward( LuckReward* pLuckReward );

protected:
    LuckRewardManager();
    bool CheckValid( LuckReward* pLuckReward );                         // 检查是否有效
    const RandData* RandLuckRewardType( LuckReward* pLuckReward );      // 随机奖励类型
    void SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage );         // 发消息

    T* GetLuckUnit( unsigned int dwID );

    void LogLuckReward( LuckReward* pLuckReward );
    void LogLuckReward( LuckReward* pLuckReward, T* pLuckUnit );

    const char* FormatLogString( LuckReward* pLuckReward );
private:
    LuckRewardManager( const LuckRewardManager& );
    LuckRewardManager& operator = ( const LuckRewardManager& );
private:
    typedef std::map< unsigned int, LuckReward* > LuckRewardMap;        // 队伍形式用队伍SessionID做key 个人用DBID做key
    typedef LuckRewardMap::iterator LuckRewardMapIter;

    LuckRewardMap m_mapLuckReward;                                      // 队伍形式
    unsigned int m_dwNextUpdateTime;                                    // 下次更新时间
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class GameTeamMember;
template< class T, class U > class Team;      
typedef LuckRewardManager < Team< GameTeamMember, GamePlayer > > TeamLuckRewardManager;
#define theTeamLuckRewardManager TeamLuckRewardManager::Instance()             // 队伍形式

typedef LuckRewardManager< GamePlayer > CharLuckRewardManager;
#define theCharLuckRewardManager CharLuckRewardManager::Instance()            // 个人形式

/////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
LuckRewardManager< T >::LuckRewardManager() : m_dwNextUpdateTime( 0 )
{   
    m_mapLuckReward.clear();
}

template< class T >
LuckRewardManager< T >::~LuckRewardManager()
{
    for ( LuckRewardMapIter iter = m_mapLuckReward.begin(); iter != m_mapLuckReward.end(); ++iter )
    {
        if ( iter->second != NULL )
        {
            iter->second->Release();
        }
    }
}

template< class T >
void LuckRewardManager< T >::LuckRewardUpdate()
{
    unsigned int dwCurrentTime = HQ_TimeGetTime();
    if ( !GameTime::IsPassCurrentTime( dwCurrentTime, m_dwNextUpdateTime, 2000 ) )
    { return; }

    unsigned int dwCostTime = ( dwCurrentTime - m_dwNextUpdateTime );
    for ( LuckRewardMapIter iter = m_mapLuckReward.begin(); iter != m_mapLuckReward.end(); )
    {
        if ( !CheckValid( iter->second ) )
        {
            if ( iter->second != NULL )
            {
                iter->second->Release();
            }
            iter = m_mapLuckReward.erase( iter );
            continue;
        }

        if ( iter->second->GetCanPlay() || iter->second->GetHasPlay() )           // 已经交了任务 或者已经玩过了
        {
            if ( iter->second->GetTimeOut() > dwCostTime )
            {
                iter->second->SetTimeOut( iter->second->GetTimeOut() - dwCostTime );
            }
            else
            {
                if ( iter->second->GetIsLucking() )                         // 客户端正在转
                {
                    RunLuckReward( iter->second );
                }
                else
                {
                    // 超时直接领取奖品
                    if ( ProcessReceiveLuckReward( iter->second ) )         // 因为函数有删除迭代器操作,所以这里直接返回
                    { return;  }
                }
            }
        }

        ++iter;
    }

    m_dwNextUpdateTime = dwCurrentTime;
}

template< class T >
LuckReward* LuckRewardManager< T >::GetLuckReward( unsigned int dwID )
{
    LuckRewardMapIter iter = m_mapLuckReward.find( dwID );
    if ( iter == m_mapLuckReward.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
bool LuckRewardManager< T >::AddLuckReward( unsigned int dwID, LuckReward* pLuckReward )
{
    if ( dwID == InvalidLogicNumber || pLuckReward == NULL )
    { return false; }

    LuckRewardMapIter iter = m_mapLuckReward.find( dwID );
    if ( iter != m_mapLuckReward.end() )
    {
        if ( iter->second != NULL )
        {
            iter->second->Release();
        }
        iter->second = pLuckReward;
    }
    else
    {
        m_mapLuckReward.insert( make_pair( dwID, pLuckReward ) );
    }

    return true;
}

template< class T >
bool LuckRewardManager< T >::RemoveLuckReward( unsigned int dwID )
{
    if ( dwID == InvalidLogicNumber )
    { return false; }

    LuckRewardMapIter iter = m_mapLuckReward.find( dwID );
    if ( iter == m_mapLuckReward.end() )
    { return false; }

    iter->second->Release();
    m_mapLuckReward.erase( iter );
    return true;
}

template< class T >
bool LuckRewardManager< T >::IsInLuckReward( unsigned int dwID )
{
    LuckReward* pLuckReward = GetLuckReward( dwID );
    return pLuckReward != NULL;
}

template< class T >
const RandData* LuckRewardManager< T >::RandLuckRewardType( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return NULL; }

    return theLuckRewardRandConfig.GetLuckRand( pLuckReward->GetLevel(), theRand.rand32() );
}

template< class T >
void LuckRewardManager< T >::StartLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL || !pLuckReward->GetCanPlay() || pLuckReward->GetIsLucking() )
    { return; }

    pLuckReward->SetIsLucking( true );
    pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut / 5 );          // 转30秒超时

    MsgLuckRewardAck xAck;
    xAck.uchResult = MsgLuckRewardAck::ECD_Start;
    SendRewardMessage( pLuckReward, &xAck );
}


template< class T >
void LuckRewardManager< T >::RandLuckReward( LuckReward* pLuckReward )
{
    // 得到此关的奖励个数
    unsigned int nRewardCount = theLuckRewardConfig.GetRewardCountByRewardLevel( pLuckReward->GetLevel() );
    if ( nRewardCount == 0 )
    { return; }

    // 获得必出的奖励
    theLuckRewardConfig.GetFixedLuckReward( pLuckReward->GetLevel(), pLuckReward->GetReward() );
    while ( pLuckReward->GetRewardCount() < nRewardCount )      // 数量还不够
    {
        // 在随机里面出的东西里面随机选
        char chIndex = theLuckRewardConfig.GetRandLuckReward( pLuckReward->GetLevel(), theRand.rand32() );
        if ( chIndex == -1 )
        { break; }

        pLuckReward->AddReward( chIndex );
    }
}

template< class T >
void LuckRewardManager< T >::ShowLuckReward( LuckReward* pLuckReward, unsigned char uchShowType )
{
    if ( pLuckReward == NULL )
    { return; }

    if ( !pLuckReward->IsHasReward() )      // 还没有计算奖品
    {
        RandLuckReward( pLuckReward );
    }

    // 通知客户端获得的奖励
    MsgTellLuckReward xReward;
    xReward.uchLevel      = pLuckReward->GetLevel();
    xReward.uchOperator   = uchShowType;
    xReward.uchRewardType = pLuckReward->GetRewardType();
    pLuckReward->CopyReward( xReward );
    SendRewardMessage( pLuckReward, &xReward );
}

template< class T >
void LuckRewardManager< T >::RunLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL || !pLuckReward->IsCanLuckReward() )          // 已经玩过了
    { return; }

    if ( pLuckReward->GetLevel() >= theLuckRewardConfig.GetMaxLevel() )
    { return; }                     // 最大关了

    const RandData* pRandData = RandLuckRewardType( pLuckReward );
    if ( pRandData == NULL )        // 什么都没有 下次可以继续玩
    { return; }

    pLuckReward->SetRewardType( pRandData->GetType() );          // 设置类型
    pLuckReward->SetIsLucking( false );                          // 设置停止转了  
    pLuckReward->SetCanPlay( false );                            // 设置已经玩过不能玩了
    pLuckReward->SetHasPlay( true );                             // 设置已经玩过了
    pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut );           // 重新设置超时时间

    switch ( pLuckReward->GetRewardType() )
    {
    case ECD_RandType_Front:        // 退一关
        {
            pLuckReward->SetLevel( pLuckReward->GetLevel() - 1 );
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Next:         // 下一关
        {
            pLuckReward->SetLevel( pLuckReward->GetLevel() + 1 );
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Jump:         // 跳一关
        {
            pLuckReward->SetLevel( pLuckReward->GetLevel() + 2 );
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Stay:
        {
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Leave:
        {
            // 记录日志
            LogLuckReward( pLuckReward );
        }
        break;
    default:
        break;
    }

    // 通知结果
    MsgLuckRewardResult xResult;
    xResult.uchLevel      = pLuckReward->GetLevel();
    xResult.uchRewardType = pLuckReward->GetRewardType();
    SendRewardMessage( pLuckReward, &xResult );
}

template< class T >             // 返回true 标识已领取奖品,将要离开
bool LuckRewardManager< T >::ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bReceive )
{
    if ( pLuckReward == NULL )
    { return true; }

    // 先通知关闭窗口
    MsgLuckRewardAck xAck;
    xAck.uchResult = MsgLuckRewardAck::ECD_Close;
    SendRewardMessage( pLuckReward, &xAck );

    if ( bReceive )         // 离开或者领取奖品
    {
        if ( pLuckReward->GetRewardType() == ECD_RandType_Leave || pLuckReward->IsCanGetReward() )
        {
            ReceiveLuckReward( pLuckReward );           // 领取奖励
            RemoveLuckReward( pLuckReward->GetID() );   // 删除
            return true;
        }
    }

    return false; 
}

template< class T >
void LuckRewardManager< T >::LogLuckReward( LuckReward* pLuckReward )
{
    T* pLuckUnit = GetLuckUnit( pLuckReward->GetID() );
    if ( pLuckUnit == NULL )
    { return; }

    LogLuckReward( pLuckReward, pLuckUnit );
}

template< class T >
const char* LuckRewardManager< T >::FormatLogString( LuckReward* pLuckReward )
{
    static const char* s_szLogString[] = 
    {
        "获得了原始奖励", "离开了", "获得了一般奖励", "获得了双倍奖励",
    };

    if ( pLuckReward == NULL )
    { return ""; }

    static const int s_nLogStringSize = sizeof( s_szLogString ) / sizeof( char* );

    if ( pLuckReward->GetRewardType() < 0 || pLuckReward->GetRewardType() >= s_nLogStringSize )
    {
        return "";
    }

    return s_szLogString[pLuckReward->GetRewardType()];
}

#endif