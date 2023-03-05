#ifndef __LUCKREWARDCONFIG_H__
#define __LUCKREWARDCONFIG_H__

/************************************************************************/
/*                      幸运15关奖励配置                                */
/************************************************************************/
#include <vector>
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include <algorithm>
#include <functional>

#define theLuckRewardConfig LuckRewardConfig< RewardData >::Instance()          // 幸运15关奖励物品配置
#define theLuckRewardRandConfig LuckRewardConfig< RandData >::Instance()        // 幸运15关奖励类型概率配置 ( 只服务器使用 )

enum ELuckRewardConstDefine
{
    ECD_Reward_Init     = 0,        // 初始值
    ECD_Reward_Money    = 1,        // 游戏币
    ECD_Reward_Exp      = 2,        // 经验
    ECD_Reward_Item     = 3,        // 物品
    ECD_Reward_Max,                 // 奖励类型最大值

    ECD_ErrorItemID = 0,            // 无效物品ID
    ECD_Reward_MinLevel = 1,        // 从第1关开始
    ECD_Reward_MaxLevel = 15,       // 总共15关
    ECD_Reward_Count    = 1,        // 每关默认奖1个

    ECD_RandType_Init   = 0,        // 初始值
    ECD_RandType_Leave  = 1,        // 离开
    ECD_RandType_Half   = 2,        // 奖励一半
    ECD_RandType_Double = 3,        // 奖励一倍
    ECD_RandType_Front  = 4,        // 倒退一关
    ECD_RandType_Stay   = 5,        // 留在本关
    ECD_RandType_Next   = 6,        // 下一关
    ECD_RandType_Jump   = 7,        // 跳一关
    ECD_RandType_Max,               // 类型最大值
};

class RewardData                // 幸运15关奖励的物品信息
{
public:
    RewardData()
    {
        m_uchRewardType = ECD_Reward_Init;
        m_nItemID       = ECD_ErrorItemID;
        m_nValue        = 0;
        m_bIsFixed      = false;
        m_bIsRealLife   = false;
        m_nProbability  = 0;
    }

    const unsigned char GetType() const        { return m_uchRewardType; }
    const unsigned int  GetItemID() const      { return m_nItemID; }
    const unsigned int  GetValue() const       { return m_nValue; }
    const bool          GetFixed() const       { return m_bIsFixed; }
    const bool          GetRealLife() const    { return m_bIsRealLife; }
    const unsigned int  GetProbability() const { return m_nProbability; }

    void SetType( unsigned char uchValue )     { m_uchRewardType = uchValue; }
    void SetItemID( unsigned int nValue )      { m_nItemID = nValue; }
    void SetValue( unsigned int nValue )       { m_nValue = nValue; }
    void SetFixed( bool bValue )               { m_bIsFixed = bValue; }
    void SetRealLife( bool bValue )            { m_bIsRealLife = bValue; }
    void SetProbability( unsigned int nValue ) { m_nProbability = nValue; }

    bool IsError() { return ( m_uchRewardType == ECD_Reward_Init || m_nValue == 0 || ( m_uchRewardType == ECD_Reward_Item && m_nItemID == ECD_ErrorItemID ) ); }

    bool IsRewardMoney() { return m_uchRewardType == ECD_Reward_Money; }
    bool IsRewardExp() { return m_uchRewardType == ECD_Reward_Exp; }
    bool IsRewardItem() { return m_uchRewardType == ECD_Reward_Item; }

    friend bool operator == ( const RewardData& xLeft, const RewardData& xRight )
    {
        return ( xLeft.GetType() == xRight.GetType() && xLeft.GetItemID() == xRight.GetItemID() && xLeft.GetValue() == xRight.GetValue() && xLeft.GetFixed() == xRight.GetFixed() );
    }

private:
    unsigned char m_uchRewardType;          // 奖励类型
    unsigned int m_nItemID;                 // 奖励物品ID
    unsigned int m_nValue;                  // 奖励数值
    bool m_bIsFixed;                        // 是否必出
    bool m_bIsRealLife;                     // 是否是实物奖励
    unsigned int m_nProbability;            // 概率 ( 不是必出的情况下 )
};

class RandData                      // 幸运15关的奖励类型概率信息
{
public:
    RandData()
    {
        m_uchRandType  = ECD_RandType_Init;
        m_nProbability = 0;
    }

    const unsigned char GetType() const  { return m_uchRandType; }
    const unsigned int  GetProbability() const { return m_nProbability; }

    void SetType( unsigned char uchValue ) { m_uchRandType = uchValue; }
    void SetProbability( unsigned int nValue )   { m_nProbability = nValue; }

    bool IsError() { return ( m_uchRandType == ECD_RandType_Init ); }

    friend bool operator == ( const RandData& xLeft, const RandData& xRight )
    {
        return ( xLeft.GetType() == xRight.GetType() );
    }
    bool operator < ( const RandData& xRand )
    {
        return GetProbability() < xRand.GetProbability();
    }
private:
    unsigned char m_uchRandType;            // 奖励概率的类型
    unsigned int m_nProbability;            // 概率值
};


template< class T >
struct FindData : public std::unary_function< T, bool >
{
    FindData( unsigned int nProbability ) : m_nValue( 0 ), m_nProbability( nProbability ) {}

    bool operator()( const T& xRand )
    {
        m_nValue += xRand.GetProbability();           // 每种类型都有一个概率,所以这里用区间来找概率
        return ( m_nProbability < m_nValue );
    }
private:
    unsigned int m_nValue;
    unsigned int m_nProbability;
};


template< class T >
class LuckRewardConfig
{
public:
    typedef std::vector < T > VecData;
    typedef typename VecData::iterator VecDataIter;
    typedef typename VecData::const_iterator VecConstDataIter;
    typedef typename VecData::const_reverse_iterator VecConstReDataIter;
    typedef std::vector< VecData > VecLuckReward;

    typedef std::vector< unsigned char > VecCount;
    typedef std::vector< char > RewardIndex;
    typedef RewardIndex::iterator RewardIndexIter;
    typedef RewardIndex::const_iterator RewardIndexConstIter;
    typedef std::vector < RewardIndex > RewardIndexVec;


    typedef std::vector< unsigned int > RandNumberVec;
    typedef RandNumberVec::iterator RandNumberVecIter;
    typedef RandNumberVec::const_iterator RandNumberVecConstIter;

public:
    static LuckRewardConfig< T >& Instance()
    {
        static LuckRewardConfig< T > s_xLuckRewardConfig;
        return s_xLuckRewardConfig;
    }

    void Initialize()
    {
        m_vecLuckReward.clear();
        m_vecLuckReward.resize( m_uchMaxLevel + 1 );
        m_vecLuckCount.clear();
        m_vecLuckCount.resize( m_uchMaxLevel + 1 );

        m_vecFixedLuckRewardIndex.clear();
        m_vecFixedLuckRewardIndex.resize( m_uchMaxLevel + 1 );
        m_vecRandLuckReward.clear();
        m_vecRandLuckReward.resize( m_uchMaxLevel + 1 );
        m_vecRandLuckNumber.clear();
        m_vecRandLuckNumber.resize( m_uchMaxLevel + 1 );
        m_vecRandLuckRewardIndex.clear();
        m_vecRandLuckRewardIndex.resize( m_uchMaxLevel + 1 );
    }

    // 加载config文件
    bool LoadLuckRewardConfig( const char* szFile );    
    bool LoadLuckRandConfig  ( const char* szFile );

    // 获得最大关数
    unsigned char GetMaxLevel() { return m_uchMaxLevel; }

    // 游戏里第8关,就传入 8 等级做参数
    // 获得某等级的所有奖励
    const VecData* GetReward( unsigned char uchRewardLevel ) const                           
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return NULL; }

        return &m_vecLuckReward[uchRewardLevel];
    }

    // 获得某等级的第几个奖励
    const T* GetReward( unsigned char uchRewardLevel, unsigned char uchIndex ) const     
    {
        const VecData* pVecRewardData = GetReward( uchRewardLevel );
        if ( pVecRewardData == NULL )
        { return NULL; }

        if ( uchIndex < 0 || uchIndex >= static_cast< unsigned char >( pVecRewardData->size() ) )
        { return NULL; }

        return &( pVecRewardData->at( uchIndex ) );
    }

    // 获得某等级的奖励个数
    unsigned char GetRewardCountByRewardLevel( unsigned char uchRewardLevel ) const                
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return 0; }

        return m_vecLuckCount[uchRewardLevel];
    }

    // 获得该等级容器类数据个数
    unsigned char GetDataSizeByLevel( unsigned char uchRewardLevel ) const                
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return 0; }

        return static_cast< unsigned char >( m_vecLuckReward[uchRewardLevel].size() );
    }

    // 传入等级 和 一个随即数,获得奖励的随即类型信息
    const T* GetLuckRand( unsigned char uchLevel, unsigned int nRandNumber ) const
    {
        const VecData* pVecRewardData = GetReward( uchLevel );
        if ( pVecRewardData == NULL )
        { return NULL; }

        if ( m_vecRandLuckNumber[uchLevel] == 0 )
        { return NULL; }

        int nRand = nRandNumber % m_vecRandLuckNumber[uchLevel];

        // 正序查找
        VecConstDataIter iter = std::find_if( pVecRewardData->begin(), pVecRewardData->end(), FindData< T >( nRand ) );
        if ( iter == pVecRewardData->end() )
        { return NULL; }

        return &( *iter );
    }

    //  获得必奖的东西
    void GetFixedLuckReward( unsigned char uchLevel, RewardIndex& vecReward ) const
    {
        vecReward.clear();

        if ( uchLevel < ECD_Reward_MinLevel || uchLevel > m_uchMaxLevel )
        { return; }

        const unsigned char uchRewardCount = GetRewardCountByRewardLevel( uchLevel );       // 该关奖励的个数

        const RewardIndex& vecFixedLuckReward = m_vecFixedLuckRewardIndex[uchLevel];
        RewardIndexConstIter end = vecFixedLuckReward.end();
        if ( vecFixedLuckReward.size() > uchRewardCount )
        {
            end = vecFixedLuckReward.begin();
            advance( end, uchRewardCount );
        }

        vecReward.assign( vecFixedLuckReward.begin(), end );
    }

    // 获得随机奖励的东西的索引
    char GetRandLuckReward( unsigned char uchLevel, unsigned int nRandNumber ) const
    {
        if ( uchLevel < ECD_Reward_MinLevel || uchLevel > m_uchMaxLevel )
        { return -1; }

        if ( m_vecRandLuckNumber[uchLevel] == 0 )
        { return -1; }

        unsigned int nRand = nRandNumber % m_vecRandLuckNumber[uchLevel];
        const VecData& vecReward = m_vecRandLuckReward[uchLevel];
        VecConstDataIter iter = std::find_if( vecReward.begin(), vecReward.end(), FindData< T >( nRand ) );
        if ( iter == vecReward.end() )
        { return -1; }

        int nIndex = static_cast< int >( distance( vecReward.begin(), iter ) );
        return m_vecRandLuckRewardIndex[uchLevel].at( nIndex );
    }

protected:
    LuckRewardConfig() : m_uchMaxLevel( ECD_Reward_MaxLevel ) { }
    bool AddReward( unsigned char uchRewardLevel, T& xData )
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel || xData.IsError() )
        { return false; }

        VecData &vecRewardData = m_vecLuckReward[uchRewardLevel];
        VecDataIter iter = std::find( vecRewardData.begin(), vecRewardData.end(), xData );
        if ( iter != vecRewardData.end() )
        { return false; }

        vecRewardData.push_back( xData );
        return true;
    }

private:
    LuckRewardConfig( const LuckRewardConfig& );
    LuckRewardConfig& operator = ( const LuckRewardConfig& );

private:
    VecLuckReward m_vecLuckReward;              // 所有的奖励
    VecCount m_vecLuckCount;                    // 该等级奖励的数量

    RewardIndexVec m_vecFixedLuckRewardIndex;   // 每关必奖励的东西索引
    RandNumberVec m_vecRandLuckNumber;          // 每一关所有随机奖励的概率总和
    VecLuckReward m_vecRandLuckReward;          // 每关随机出的东西
    RewardIndexVec m_vecRandLuckRewardIndex;    // 每关随机出的东西的索引
    
    unsigned char m_uchMaxLevel;                // 最大多少关,可动态配置

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif