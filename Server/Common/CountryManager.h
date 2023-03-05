#ifndef __GAMECOUNTRYMANAGER_H__
#define __GAMECOUNTRYMANAGER_H__

/************************************************************************
            ���ҹ���
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

    // ���һ������
    bool AddCountry( T& xData );                    

    // ���ҹ�������
    T* GetCountry( unsigned char uchID );           

    // ��ʼ�������б�
    void InitCountry( CountryData* pData );

    // ��ʼ����������
    void InitCountryName( unsigned char uchID, const char* szName );    

    // ���ҹ���RunUpdate
    void RunUpdate( unsigned int nCurrentTime );    
    
    // �������ض�ʱ��
    void StartLoadTimer();

    // ֹͣ���ض�ʱ��
    void StopLoadTimer();

    // ����Ƿ�������ݿ�ɹ�
    bool GetLoadSuccess() const;

    // ���ü������ݿ�״̬
    void SetLoadSuccess( bool bValue );

    // ���͹������ݵ�GameServer
    void SendCountryDataToGameServer( unsigned int nServerID );

    // ����������Ϣ
    void SendWeakCountryMessage();

	// ����ǿ����Ϣ
	void SendStrongCountryMessage();
    
    // ���������Ϣ
    void SaveCountryData();

    // �������ID
    unsigned char GetWeakCountry() const;

	//���ǿ��
	unsigned char GetStrongCountry() const;

    // ��������ID
    void SetWeakCountry( unsigned char uchValue );

	//����ǿ��
	void SetStrongCountry( unsigned char uchValue );

    // ��������
    void CalcWeakCountry();

	// ����ǿ��
	void CalcStrongCountry();

    // ��������ս״̬
    void SetWarStatus( unsigned char uchValue );

    // �ж��Ƿ�������ս�׶�
    bool CheckInCountryWarFight() const;

    // ��������ս״̬�ı�
    void ProcessWarStatusChange( unsigned char uchValue );

    // ���͹�սɱ����Ϣ��CenterServer
    void SendWarFightKillPlayerMessage( unsigned char uchKillCountryID, unsigned char uchDeathCountryID );

    // �����սɱ����Ϣ
    void ProcessWarKillPlayer( unsigned char uchKillCountryID, unsigned int nKillCount, unsigned char uchDeathCountryID, unsigned int nDeathCount );

    // �����սɱ������
    void ProcessCountryWarFightSort();

	void HandleAllCountryStrength(bool IsSendMsg = true);

	// ��center���ϼ������ʵ��
	void CalcCountryStrengthAtOnce();
protected:
    // ����������ع�����Ϣ
    void ProcessLoadCountryData( unsigned int nCurrentTime );                         

    // �����������ս����
    void ProcessCountryWarFightUpdate( unsigned int nCurrentTime );

    // ��������ս״̬�ı���Ϣ
    void SendWarStatusChangeMessage();

	void ProcessCalcCountryStrength( unsigned int nCurrentTime );
private:

    T m_xCountry[ CountryDefine::Country_Max ];     // ��������
    unsigned char m_uchWeakCountryID;               // ����ID
	unsigned char m_uchStrongCountryID;				// ǿ��ID

    GameTimerEx m_xUpdateTimer;     // ���¶�ʱ��
    bool m_bLoadSuccess;            // �Ƿ���سɹ�
    bool m_bLoadTimerStart;         // �Ƿ��������ض�ʱ��
    GameTimerEx m_xLoadTimer;       // ���ض�ʱ��
    unsigned char m_uchWarStatus;   // ��������ս״̬ 

    ///////////////////////////////////////////////////////////////
    GameTimerEx m_xWarFightTimer;
	GameTimerEx m_xStrengthTimer;        // ����ʵ�����㶨ʱ��
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
    //SendCountryDataToGameServer( CountryDefine::ErrorID );      // ���͵���������
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
    { return; }     // �Ѿ�����

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
            // �����ս������Ϣ
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