#ifndef __GAMECOUNTRYMANAGER_H__
#define __GAMECOUNTRYMANAGER_H__

/************************************************************************
            国家管理
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "Country.h"
#include "RunStatus.h"
#include "GameTimer.h"
#include "Singleton.h"

template< class T >
class CountryManager : public ISingletion< CountryManager< T > >
{
public:
    CountryManager();
    ~CountryManager();

    // 添加一个国家
    bool AddCountry( T& xData );                    

    // 查找国家属性
    T* GetCountry( unsigned char uchID );           

    // 初始化国家列表
    void InitCountry( CountryData* pData );

    // 初始化国家名字
    void InitCountryName( unsigned char uchID, const char* szName );    

    // 国家管理RunUpdate
    void RunUpdate( unsigned int nCurrentTime );    
    
    // 开启加载定时器
    void StartLoadTimer();

    // 停止加载定时器
    void StopLoadTimer();

    // 获得是否加载数据库成功
    bool GetLoadSuccess() const;

    // 设置加载数据库状态
    void SetLoadSuccess( bool bValue );

    // 发送国家数据到GameServer
    void SendCountryDataToGameServer( unsigned int nServerID );

    // 发送弱国消息
    void SendWeakCountryMessage();

	// 发生强国消息
	void SendStrongCountryMessage();
    
    // 保存国家信息
    void SaveCountryData();

    // 获得弱国ID
    unsigned char GetWeakCountry() const;

	//获得强国
	unsigned char GetStrongCountry() const;

    // 设置弱国ID
    void SetWeakCountry( unsigned char uchValue );

	//设置强国
	void SetStrongCountry( unsigned char uchValue );

    // 计算弱国
    void CalcWeakCountry();

	// 计算强国
	void CalcStrongCountry();

    // 设置屠城战状态
    void SetWarStatus( unsigned char uchValue );

    // 判断是否在屠城战阶段
    bool CheckInCountryWarFight() const;

    // 处理屠城战状态改变
    void ProcessWarStatusChange( unsigned char uchValue );

    // 发送国战杀人信息给CenterServer
    void SendWarFightKillPlayerMessage( unsigned char uchKillCountryID, unsigned char uchDeathCountryID );

    // 处理国战杀人信息
    void ProcessWarKillPlayer( unsigned char uchKillCountryID, unsigned int nKillCount, unsigned char uchDeathCountryID, unsigned int nDeathCount );

    // 处理国战杀人排行
    void ProcessCountryWarFightSort();

	void HandleAllCountryStrength(bool IsSendMsg = true);

	// 让center马上计算国家实力
	void CalcCountryStrengthAtOnce();
protected:
    // 发送请求加载国家信息
    void ProcessLoadCountryData( unsigned int nCurrentTime );                         

    // 处理国家屠城战更新
    void ProcessCountryWarFightUpdate( unsigned int nCurrentTime );

    // 发送屠城战状态改变消息
    void SendWarStatusChangeMessage();

	void ProcessCalcCountryStrength( unsigned int nCurrentTime );
private:

    T m_xCountry[ CountryDefine::Country_Max ];     // 国家数组
    unsigned char m_uchWeakCountryID;               // 弱国ID
	unsigned char m_uchStrongCountryID;				// 强国ID

    GameTimerEx m_xUpdateTimer;     // 更新定时器
    bool m_bLoadSuccess;            // 是否加载成功
    bool m_bLoadTimerStart;         // 是否启动加载定时器
    GameTimerEx m_xLoadTimer;       // 加载定时器
    unsigned char m_uchWarStatus;   // 国家屠城战状态 

    ///////////////////////////////////////////////////////////////
    GameTimerEx m_xWarFightTimer;
	GameTimerEx m_xStrengthTimer;        // 国家实力清算定时器
};

///////////////////////////////////////////////////////////////////////////
typedef CountryManager< CenterCountry > CenterCountryManager;
#define theCenterCountryManager CenterCountryManager::Instance()

typedef CountryManager< GameCountry > GameCountryManager;
#define theGameCountryManager GameCountryManager::Instance()
///////////////////////////////////////////////////////////////////////////
template< class T >
CountryManager< T >::CountryManager() : m_bLoadTimerStart( false ), m_bLoadSuccess( false ), m_uchWeakCountryID( CountryDefine::Country_Init ),m_uchStrongCountryID( CountryDefine::Country_Init )
{
    for ( int i = CountryDefine::Country_Init; i < CountryDefine::Country_Max; ++i )
    {
        m_xCountry[ i ].SetID( i );
    }

    m_xUpdateTimer.StartTimer( 1, CountryDefine::UpdateSpaceTime );
    m_uchWarStatus = CountryDefine::WarStatusInit;
}

template< class T >
CountryManager< T >::~CountryManager()
{

}

template< class T >
inline bool CountryManager< T >::AddCountry( T& xData )
{
    if ( xData.GetID() >= CountryDefine::Country_Max || xData.GetID() == CountryDefine::Country_Init )
    { return false; }

    m_xCountry[ xData.GetID() ] == xData;
    return true;
}

template< class T >
inline T* CountryManager< T >::GetCountry( unsigned char uchID )
{
    if ( uchID >= CountryDefine::Country_Max )
    { uchID = CountryDefine::Country_Init; }

    return &( m_xCountry[ uchID ] );
}

template< class T >
void CountryManager< T >::InitCountry( CountryData* pData )
{
    if ( pData == NULL || GetLoadSuccess() )
    { return; }

    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( pData[ i ].GetID() == CountryDefine::Country_Init || pData[ i ].GetID() >= CountryDefine::Country_Max )
        { continue; }

        m_xCountry[ i ].SetCountryData( pData[ i ] );
    }

    SetLoadSuccess( true );
    StopLoadTimer();
    CalcWeakCountry();
	CalcStrongCountry();
    //SendCountryDataToGameServer( CountryDefine::ErrorID );      // 发送到服务器上
}

template< class T >
inline void CountryManager< T >::InitCountryName( unsigned char uchID, const char* szName )
{
    T* pCountry = GetCountry( uchID );
    if ( pCountry == NULL )
    { return; }

    pCountry->SetName( szName );
}

template< class T >
inline void CountryManager< T >::StartLoadTimer()
{
    if ( m_bLoadTimerStart )
    { return; }     // 已经开启

    m_bLoadTimerStart = true;
    m_xLoadTimer.StartTimer( 1, CountryDefine::LoadSpaceTime );
}

template< class T >
inline void CountryManager< T >::StopLoadTimer()
{
    m_xLoadTimer.StopTimer();
}

template< class T >
inline bool CountryManager< T >::GetLoadSuccess() const
{
    return m_bLoadSuccess;
}

template< class T >
inline void CountryManager< T >::SetLoadSuccess( bool bValue )
{
    m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadContrySuccess);
	}
}

template< class T >
void CountryManager< T >::SaveCountryData()
{
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].IsSaveTimerStart() )
        {
            m_xCountry[ i ].SaveToDatabase();
        }
    }
}

template< class T >
inline unsigned char CountryManager< T >::GetWeakCountry() const
{
    return m_uchWeakCountryID; 
}
template< class T >
inline unsigned char CountryManager< T >::GetStrongCountry() const
{
	return m_uchStrongCountryID;
}
template< class T >
inline void CountryManager< T >::SetWeakCountry( unsigned char uchValue )
{
    m_uchWeakCountryID = uchValue;
}
template< class T >
inline void CountryManager< T >::SetStrongCountry( unsigned char uchValue )
{
	m_uchStrongCountryID = uchValue;
}

template< class T >
inline void CountryManager< T >::SetWarStatus( unsigned char uchValue )
{
    m_uchWarStatus = uchValue;
}

template< class T >
inline bool CountryManager< T >::CheckInCountryWarFight() const
{
    return m_uchWarStatus == CountryDefine::WarStatusFight;
}

template< class T >
void CountryManager< T >::ProcessWarStatusChange( unsigned char uchValue )
{
     m_uchWarStatus = uchValue;
    SendWarStatusChangeMessage();

    switch( uchValue )
    {
    case CountryDefine::WarStatusPrepare:
        {
            // 清除国战新人信息
            for ( int i = 0; i < CountryDefine::Country_Max; ++i )
            {
                m_xCountry[ i ].SetSortIndex( 0 );
                m_xCountry[ i ].SetKillCount( 0 );
                m_xCountry[ i ].SetDeathCount( 0 ); 
            }
        }
        break;
    }
}

#endif