#ifndef __ONLINEREWARDCONFIG_H__
#define __ONLINEREWARDCONFIG_H__

#include <vector>

class OnLineRewardConfig
{
public:
    enum EConstDefine 
    {
        EConstDefine_RewardType_LumpSum = 0 ,   // 一次性奖励
        EConstDefine_RewardType_Daily   = 1 ,   // 每日奖励
        EConstDefine_RewardItemMaxSize  = 10,   // 可以最多一次性送10件道具
    };

    struct OnLineReward
    {
        unsigned int   dwOnLineTime ;        // 在线总时间
		unsigned int   dwCountDown  ;		 // 倒计时时间
        
        unsigned short nItemID[EConstDefine_RewardItemMaxSize]; // 奖励的物品ID
        unsigned short nCount [EConstDefine_RewardItemMaxSize]; // 奖励的物品数量
        bool           bIsBound     [EConstDefine_RewardItemMaxSize];		 // 是否绑定
        bool           bIsStarRandom[EConstDefine_RewardItemMaxSize];		 // 是否随机星级
        unsigned char  nStarLevel   [EConstDefine_RewardItemMaxSize];		 // 最大星级
        bool IsError() const { return ( dwOnLineTime == 0 || nItemID[0] == 0 || nCount[0] == 0 ); }
    };

public:
    typedef std::vector< OnLineReward > OnLineRewardVector;
    typedef OnLineRewardVector::iterator OnLineRewardVectorIter;
    typedef OnLineRewardVector::const_iterator OnLineRewardVectorConstIter;

public:
    ~OnLineRewardConfig() { m_vecOnLineReward.clear(); }

    static OnLineRewardConfig& Instance()
    {
        static OnLineRewardConfig s_xConfig;
        return s_xConfig;
    }

    const OnLineReward* GetOnLineReward( unsigned short nIndex ) const
    {
        if ( nIndex >= m_nMaxRewardCount )
        { return NULL; }

        return &( m_vecOnLineReward.at( nIndex ) );
    }

    unsigned short GetMaxRewardCount() const { return m_nMaxRewardCount;    }
    unsigned char  GetLevelLowLimit()  const { return m_nLevelLowLimit;     }
    unsigned char  GetLevelUpLimit()   const { return m_nLevelUpLimit;      }
    unsigned char  GetRewardType()     const { return m_nRewardType;        }

    bool LoadOnLineRewardConfig( const char* szFile );

protected:
    OnLineRewardConfig() : m_nRewardType(0), m_nLevelUpLimit(0), m_nLevelLowLimit(0), m_nMaxRewardCount(0)
    { 
        m_vecOnLineReward.clear();
    }

    bool AddOnLineReward( unsigned short nIndex, const OnLineReward& xReward )
    {
        if ( nIndex >= m_nMaxRewardCount ||  xReward.IsError() )
        { return false; }

        if ( !m_vecOnLineReward[ nIndex ].IsError() )
        { return false; }       // 已经存在属性了

        m_vecOnLineReward[ nIndex ] = xReward;
        return true;
    }

private:
    OnLineRewardConfig( const OnLineRewardConfig& );
    OnLineRewardConfig& operator = ( const OnLineRewardConfig& );

private:
    unsigned char  m_nLevelLowLimit;        // 等级下限
    unsigned char  m_nLevelUpLimit;         // 等级上限
    unsigned char  m_nRewardType;           // 领取类型
    unsigned short m_nMaxRewardCount;       // 最多奖励的次数
    OnLineRewardVector m_vecOnLineReward;   // 奖励的东西
};

#define theOnLineRewardConfig OnLineRewardConfig::Instance()

#endif