#ifndef __LUCKREWARDMANAGER_H__
#define __LUCKREWARDMANAGER_H__
/************************************************************************
                        ����15������߼�
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
    static LuckReward* CreateLuckReward(){ return CNewWithDebug< LuckReward >::Alloc( 1, "LuckReward::CreateLuckReward�д���CreateLuckRewardʵ��" ); }
    virtual void Release() { CNewWithDebug< LuckReward >::Free( this ); }

    LuckReward() : m_uchMaxLevel( ECD_Reward_MaxLevel ), m_ustSummonCount( 0 )
    {
        m_uchLevel      = ECD_Reward_MinLevel;              // ��ʼ��һ��
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

    bool IsCanGetReward();                              // ֻ����3���������ȡ��Ʒ
    bool IsCanNextLuckLevel();                         // �ж��ܷ�ǰ����һ��
    bool IsCanAcceptQuest( unsigned char uchLevel );    // �ж��Ƿ��ܽ�����( Ҳ����ˢ���� )
    bool IsCanLuckReward();                             // �ж��Ƿ���ҡ��
    void ClearReward() { m_vecReward.clear(); }
    void AddReward( char chIndex )      // ��ӽ�����Ʒ
    {
        if ( chIndex < 0 )
        { return; }
        
        m_vecReward.push_back( chIndex );
    }
    void CopyReward( MsgTellLuckReward& xReward );              // ��ȡ���ñ�ʱ���;��影������

    unsigned int GetRewardCount() { return static_cast< unsigned int > ( m_vecReward.size() ); }
    bool IsHasReward() { return !m_vecReward.empty(); }
    RewardVec& GetReward() { return m_vecReward; }

private:
    // ��ֹ���� ����
    LuckReward( const LuckReward& );            
    LuckReward& operator = ( const LuckReward& );

private:        
    unsigned int m_dwID;              // ����ģʽ�Ƕ���ID ����ģʽ��DBID
    unsigned char m_uchLevel;         // ��ǰ�ڼ���
    unsigned int m_dwTimeOut;         // ��ʱʱ��
    bool m_bCanLuck;                  // ( ������������ҡ����Ϸ )
    bool m_bHasPlay;                  // �Ƿ��Ѿ������ 
    bool m_bIsLucking;                // �ͻ����Ƿ�����ת��
    unsigned char m_uchRewardType;    // ��ǰ�漴���ý�������
    unsigned char m_uchMaxLevel;      // �����ٹ�
    RewardVec m_vecReward;            // �˹صĽ�������

    unsigned short m_ustSummonCount;  // �ٻ��������

    // ������ʱ��ĵ�ͼ����
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

    void LuckRewardUpdate();                                           // ����
    LuckReward* GetLuckReward( unsigned int dwID );                    // ����
    bool AddLuckReward( unsigned int dwID, LuckReward* pLuckReward );  // ���
    bool RemoveLuckReward( unsigned int dwID );                        // ɾ��һ��
    bool IsInLuckReward( unsigned int dwID );                          // �Ƿ���������15��
    void RunLuckReward( LuckReward* pLuckReward );                     // ִ��ҡ�����
    bool ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bReceive = true );          // ������ȡ��Ʒ�߼�
    void ReceiveLuckReward( LuckReward* pLuckReward );                 // ��ȡ����
    void StartLuckReward( LuckReward* pLuckReward );                   // �ͻ��˿�ʼת��
    void ShowLuckReward( LuckReward* pLuckReward, unsigned char uchShowType );
    void RandLuckReward( LuckReward* pLuckReward );

protected:
    LuckRewardManager();
    bool CheckValid( LuckReward* pLuckReward );                         // ����Ƿ���Ч
    const RandData* RandLuckRewardType( LuckReward* pLuckReward );      // �����������
    void SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage );         // ����Ϣ

    T* GetLuckUnit( unsigned int dwID );

    void LogLuckReward( LuckReward* pLuckReward );
    void LogLuckReward( LuckReward* pLuckReward, T* pLuckUnit );

    const char* FormatLogString( LuckReward* pLuckReward );
private:
    LuckRewardManager( const LuckRewardManager& );
    LuckRewardManager& operator = ( const LuckRewardManager& );
private:
    typedef std::map< unsigned int, LuckReward* > LuckRewardMap;        // ������ʽ�ö���SessionID��key ������DBID��key
    typedef LuckRewardMap::iterator LuckRewardMapIter;

    LuckRewardMap m_mapLuckReward;                                      // ������ʽ
    unsigned int m_dwNextUpdateTime;                                    // �´θ���ʱ��
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class GameTeamMember;
template< class T, class U > class Team;      
typedef LuckRewardManager < Team< GameTeamMember, GamePlayer > > TeamLuckRewardManager;
#define theTeamLuckRewardManager TeamLuckRewardManager::Instance()             // ������ʽ

typedef LuckRewardManager< GamePlayer > CharLuckRewardManager;
#define theCharLuckRewardManager CharLuckRewardManager::Instance()            // ������ʽ

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

        if ( iter->second->GetCanPlay() || iter->second->GetHasPlay() )           // �Ѿ��������� �����Ѿ������
        {
            if ( iter->second->GetTimeOut() > dwCostTime )
            {
                iter->second->SetTimeOut( iter->second->GetTimeOut() - dwCostTime );
            }
            else
            {
                if ( iter->second->GetIsLucking() )                         // �ͻ�������ת
                {
                    RunLuckReward( iter->second );
                }
                else
                {
                    // ��ʱֱ����ȡ��Ʒ
                    if ( ProcessReceiveLuckReward( iter->second ) )         // ��Ϊ������ɾ������������,��������ֱ�ӷ���
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
    pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut / 5 );          // ת30�볬ʱ

    MsgLuckRewardAck xAck;
    xAck.uchResult = MsgLuckRewardAck::ECD_Start;
    SendRewardMessage( pLuckReward, &xAck );
}


template< class T >
void LuckRewardManager< T >::RandLuckReward( LuckReward* pLuckReward )
{
    // �õ��˹صĽ�������
    unsigned int nRewardCount = theLuckRewardConfig.GetRewardCountByRewardLevel( pLuckReward->GetLevel() );
    if ( nRewardCount == 0 )
    { return; }

    // ��ñس��Ľ���
    theLuckRewardConfig.GetFixedLuckReward( pLuckReward->GetLevel(), pLuckReward->GetReward() );
    while ( pLuckReward->GetRewardCount() < nRewardCount )      // ����������
    {
        // �����������Ķ����������ѡ
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

    if ( !pLuckReward->IsHasReward() )      // ��û�м��㽱Ʒ
    {
        RandLuckReward( pLuckReward );
    }

    // ֪ͨ�ͻ��˻�õĽ���
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
    if ( pLuckReward == NULL || !pLuckReward->IsCanLuckReward() )          // �Ѿ������
    { return; }

    if ( pLuckReward->GetLevel() >= theLuckRewardConfig.GetMaxLevel() )
    { return; }                     // ������

    const RandData* pRandData = RandLuckRewardType( pLuckReward );
    if ( pRandData == NULL )        // ʲô��û�� �´ο��Լ�����
    { return; }

    pLuckReward->SetRewardType( pRandData->GetType() );          // ��������
    pLuckReward->SetIsLucking( false );                          // ����ֹͣת��  
    pLuckReward->SetCanPlay( false );                            // �����Ѿ������������
    pLuckReward->SetHasPlay( true );                             // �����Ѿ������
    pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut );           // �������ó�ʱʱ��

    switch ( pLuckReward->GetRewardType() )
    {
    case ECD_RandType_Front:        // ��һ��
        {
            pLuckReward->SetLevel( pLuckReward->GetLevel() - 1 );
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Next:         // ��һ��
        {
            pLuckReward->SetLevel( pLuckReward->GetLevel() + 1 );
            pLuckReward->ClearReward();
        }
        break;
    case ECD_RandType_Jump:         // ��һ��
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
            // ��¼��־
            LogLuckReward( pLuckReward );
        }
        break;
    default:
        break;
    }

    // ֪ͨ���
    MsgLuckRewardResult xResult;
    xResult.uchLevel      = pLuckReward->GetLevel();
    xResult.uchRewardType = pLuckReward->GetRewardType();
    SendRewardMessage( pLuckReward, &xResult );
}

template< class T >             // ����true ��ʶ����ȡ��Ʒ,��Ҫ�뿪
bool LuckRewardManager< T >::ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bReceive )
{
    if ( pLuckReward == NULL )
    { return true; }

    // ��֪ͨ�رմ���
    MsgLuckRewardAck xAck;
    xAck.uchResult = MsgLuckRewardAck::ECD_Close;
    SendRewardMessage( pLuckReward, &xAck );

    if ( bReceive )         // �뿪������ȡ��Ʒ
    {
        if ( pLuckReward->GetRewardType() == ECD_RandType_Leave || pLuckReward->IsCanGetReward() )
        {
            ReceiveLuckReward( pLuckReward );           // ��ȡ����
            RemoveLuckReward( pLuckReward->GetID() );   // ɾ��
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
        "�����ԭʼ����", "�뿪��", "�����һ�㽱��", "�����˫������",
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