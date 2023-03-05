#ifndef __ONLINEREWARDCONFIG_H__
#define __ONLINEREWARDCONFIG_H__

#include <vector>

class OnLineRewardConfig
{
public:
    enum EConstDefine 
    {
        EConstDefine_RewardType_LumpSum = 0 ,   // һ���Խ���
        EConstDefine_RewardType_Daily   = 1 ,   // ÿ�ս���
        EConstDefine_RewardItemMaxSize  = 10,   // �������һ������10������
    };

    struct OnLineReward
    {
        unsigned int   dwOnLineTime ;        // ������ʱ��
		unsigned int   dwCountDown  ;		 // ����ʱʱ��
        
        unsigned short nItemID[EConstDefine_RewardItemMaxSize]; // ��������ƷID
        unsigned short nCount [EConstDefine_RewardItemMaxSize]; // ��������Ʒ����
        bool           bIsBound     [EConstDefine_RewardItemMaxSize];		 // �Ƿ��
        bool           bIsStarRandom[EConstDefine_RewardItemMaxSize];		 // �Ƿ�����Ǽ�
        unsigned char  nStarLevel   [EConstDefine_RewardItemMaxSize];		 // ����Ǽ�
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
        { return false; }       // �Ѿ�����������

        m_vecOnLineReward[ nIndex ] = xReward;
        return true;
    }

private:
    OnLineRewardConfig( const OnLineRewardConfig& );
    OnLineRewardConfig& operator = ( const OnLineRewardConfig& );

private:
    unsigned char  m_nLevelLowLimit;        // �ȼ�����
    unsigned char  m_nLevelUpLimit;         // �ȼ�����
    unsigned char  m_nRewardType;           // ��ȡ����
    unsigned short m_nMaxRewardCount;       // ��ཱ���Ĵ���
    OnLineRewardVector m_vecOnLineReward;   // �����Ķ���
};

#define theOnLineRewardConfig OnLineRewardConfig::Instance()

#endif