#ifndef __LUCKREWARDCONFIG_H__
#define __LUCKREWARDCONFIG_H__

/************************************************************************/
/*                      ����15�ؽ�������                                */
/************************************************************************/
#include <vector>
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include <algorithm>
#include <functional>

#define theLuckRewardConfig LuckRewardConfig< RewardData >::Instance()          // ����15�ؽ�����Ʒ����
#define theLuckRewardRandConfig LuckRewardConfig< RandData >::Instance()        // ����15�ؽ������͸������� ( ֻ������ʹ�� )

enum ELuckRewardConstDefine
{
    ECD_Reward_Init     = 0,        // ��ʼֵ
    ECD_Reward_Money    = 1,        // ��Ϸ��
    ECD_Reward_Exp      = 2,        // ����
    ECD_Reward_Item     = 3,        // ��Ʒ
    ECD_Reward_Max,                 // �����������ֵ

    ECD_ErrorItemID = 0,            // ��Ч��ƷID
    ECD_Reward_MinLevel = 1,        // �ӵ�1�ؿ�ʼ
    ECD_Reward_MaxLevel = 15,       // �ܹ�15��
    ECD_Reward_Count    = 1,        // ÿ��Ĭ�Ͻ�1��

    ECD_RandType_Init   = 0,        // ��ʼֵ
    ECD_RandType_Leave  = 1,        // �뿪
    ECD_RandType_Half   = 2,        // ����һ��
    ECD_RandType_Double = 3,        // ����һ��
    ECD_RandType_Front  = 4,        // ����һ��
    ECD_RandType_Stay   = 5,        // ���ڱ���
    ECD_RandType_Next   = 6,        // ��һ��
    ECD_RandType_Jump   = 7,        // ��һ��
    ECD_RandType_Max,               // �������ֵ
};

class RewardData                // ����15�ؽ�������Ʒ��Ϣ
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
    unsigned char m_uchRewardType;          // ��������
    unsigned int m_nItemID;                 // ������ƷID
    unsigned int m_nValue;                  // ������ֵ
    bool m_bIsFixed;                        // �Ƿ�س�
    bool m_bIsRealLife;                     // �Ƿ���ʵ�ｱ��
    unsigned int m_nProbability;            // ���� ( ���Ǳس�������� )
};

class RandData                      // ����15�صĽ������͸�����Ϣ
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
    unsigned char m_uchRandType;            // �������ʵ�����
    unsigned int m_nProbability;            // ����ֵ
};


template< class T >
struct FindData : public std::unary_function< T, bool >
{
    FindData( unsigned int nProbability ) : m_nValue( 0 ), m_nProbability( nProbability ) {}

    bool operator()( const T& xRand )
    {
        m_nValue += xRand.GetProbability();           // ÿ�����Ͷ���һ������,�����������������Ҹ���
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

    // ����config�ļ�
    bool LoadLuckRewardConfig( const char* szFile );    
    bool LoadLuckRandConfig  ( const char* szFile );

    // ���������
    unsigned char GetMaxLevel() { return m_uchMaxLevel; }

    // ��Ϸ���8��,�ʹ��� 8 �ȼ�������
    // ���ĳ�ȼ������н���
    const VecData* GetReward( unsigned char uchRewardLevel ) const                           
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return NULL; }

        return &m_vecLuckReward[uchRewardLevel];
    }

    // ���ĳ�ȼ��ĵڼ�������
    const T* GetReward( unsigned char uchRewardLevel, unsigned char uchIndex ) const     
    {
        const VecData* pVecRewardData = GetReward( uchRewardLevel );
        if ( pVecRewardData == NULL )
        { return NULL; }

        if ( uchIndex < 0 || uchIndex >= static_cast< unsigned char >( pVecRewardData->size() ) )
        { return NULL; }

        return &( pVecRewardData->at( uchIndex ) );
    }

    // ���ĳ�ȼ��Ľ�������
    unsigned char GetRewardCountByRewardLevel( unsigned char uchRewardLevel ) const                
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return 0; }

        return m_vecLuckCount[uchRewardLevel];
    }

    // ��øõȼ����������ݸ���
    unsigned char GetDataSizeByLevel( unsigned char uchRewardLevel ) const                
    {
        if ( uchRewardLevel < ECD_Reward_MinLevel || uchRewardLevel > m_uchMaxLevel )
        { return 0; }

        return static_cast< unsigned char >( m_vecLuckReward[uchRewardLevel].size() );
    }

    // ����ȼ� �� һ���漴��,��ý������漴������Ϣ
    const T* GetLuckRand( unsigned char uchLevel, unsigned int nRandNumber ) const
    {
        const VecData* pVecRewardData = GetReward( uchLevel );
        if ( pVecRewardData == NULL )
        { return NULL; }

        if ( m_vecRandLuckNumber[uchLevel] == 0 )
        { return NULL; }

        int nRand = nRandNumber % m_vecRandLuckNumber[uchLevel];

        // �������
        VecConstDataIter iter = std::find_if( pVecRewardData->begin(), pVecRewardData->end(), FindData< T >( nRand ) );
        if ( iter == pVecRewardData->end() )
        { return NULL; }

        return &( *iter );
    }

    //  ��ñؽ��Ķ���
    void GetFixedLuckReward( unsigned char uchLevel, RewardIndex& vecReward ) const
    {
        vecReward.clear();

        if ( uchLevel < ECD_Reward_MinLevel || uchLevel > m_uchMaxLevel )
        { return; }

        const unsigned char uchRewardCount = GetRewardCountByRewardLevel( uchLevel );       // �ùؽ����ĸ���

        const RewardIndex& vecFixedLuckReward = m_vecFixedLuckRewardIndex[uchLevel];
        RewardIndexConstIter end = vecFixedLuckReward.end();
        if ( vecFixedLuckReward.size() > uchRewardCount )
        {
            end = vecFixedLuckReward.begin();
            advance( end, uchRewardCount );
        }

        vecReward.assign( vecFixedLuckReward.begin(), end );
    }

    // �����������Ķ���������
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
    VecLuckReward m_vecLuckReward;              // ���еĽ���
    VecCount m_vecLuckCount;                    // �õȼ�����������

    RewardIndexVec m_vecFixedLuckRewardIndex;   // ÿ�رؽ����Ķ�������
    RandNumberVec m_vecRandLuckNumber;          // ÿһ��������������ĸ����ܺ�
    VecLuckReward m_vecRandLuckReward;          // ÿ��������Ķ���
    RewardIndexVec m_vecRandLuckRewardIndex;    // ÿ��������Ķ���������
    
    unsigned char m_uchMaxLevel;                // �����ٹ�,�ɶ�̬����

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif