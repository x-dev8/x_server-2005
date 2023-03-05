#include "CountryManager.h"
#include "CountryMessage.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"
#include "CountryConfig.h"
#include <functional>
#include <algorithm>
template<>
void CenterCountryManager::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // �����������
    ProcessLoadCountryData( nCurrentTime );

    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        m_xCountry[ i ].RunUpdate( nCurrentTime );
    }

    // �����������ս�߼�
    ProcessCountryWarFightUpdate( nCurrentTime );

	ProcessCalcCountryStrength(nCurrentTime);//ǿ��������
}

template<>
void CenterCountryManager::ProcessCalcCountryStrength( unsigned int nCurrentTime )
{
	static SYSTEMTIME xDate;
    ::GetLocalTime( &xDate );

    if ( xDate.wMinute == 0 && xDate.wHour == 0 && xDate.wDayOfWeek == 1 )
    { m_xStrengthTimer.StartTimer( nCurrentTime, 65000 ); }

    if ( m_xStrengthTimer.DoneTimer() )
    {
        //��ʱ����
		for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
		{
			m_xCountry[ i ].ProcessCalcCountryStrength(nCurrentTime);
		}
		//������Ϻ� ����ǿ��������
		CalcWeakCountry();
		CalcStrongCountry();
		//�������ݵ�GameServer
		HandleAllCountryStrength();//������ǰ���й��ҵĹ��� ���ҷ��͹����ı����Ϣ
		//����ǿ������Ϣ��Character
		SendWeakCountryMessage();
		SendStrongCountryMessage();
		//����ǿ������Ϣ��GameServer
		CS2GSCountryWeakStrongthChange msg;
		msg.uchStrongCountryID = GetStrongCountry();
		msg.uchWeakCountryID = GetWeakCountry();
		theGameServerManager.SendMessageToGameServers( &msg );
    }
}

template<>

void CenterCountryManager::ProcessLoadCountryData( unsigned int nCurrentTime )
{
    StartLoadTimer();
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return; }

    CS2DBRequestCountryDataReq xReq;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void CenterCountryManager::ProcessCountryWarFightUpdate( unsigned int nCurrentTime )
{
    static SYSTEMTIME xDate;
    ::GetLocalTime( &xDate );

    const CountryConfig::WarFightSetting& xSetting = theCountryConfig.GetWarFightSetting();

    switch ( m_uchWarStatus )
    {
    case CountryDefine::WarStatusInit:
        {
            if ( !xSetting.CheckPrepareTime( xDate.wMinute, xDate.wHour, xDate.wDayOfWeek ) )
            { return; }

            ProcessWarStatusChange( CountryDefine::WarStatusPrepare );
        }
        break;
    case CountryDefine::WarStatusPrepare:
        {
            if ( !xSetting.CheckStartTime( xDate.wMinute, xDate.wHour, xDate.wDayOfWeek ) )
            { return; }

            ProcessWarStatusChange( CountryDefine::WarStatusFight );
        }
        break;
    case CountryDefine::WarStatusFight:
        {
            if ( !xSetting.CheckEndTime( xDate.wMinute, xDate.wHour, xDate.wDayOfWeek ) )
            { return; }

            ProcessWarStatusChange( CountryDefine::WarStatusEnd );
            ProcessCountryWarFightSort();   // �����սɱ������
        }
        break;
    case CountryDefine::WarStatusEnd:
        {
            ProcessWarStatusChange( CountryDefine::WarStatusInit );
        }
    default:
        return;
        break;
    }
}
template<>
void CenterCountryManager::CalcStrongCountry()
{
	//����ǿ��ID
	m_uchStrongCountryID = CountryDefine::Country_Init;
    // �Ȼ����͵Ĺ���ʵ��
    unsigned int nStrength = 0;
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() > nStrength )
        {
            nStrength = m_xCountry[ i ].GetLastStrength();
        }
    }

    // �����ߵĹ���ʵ���ĸ���
    std::vector< unsigned char > vecCountry( 0 );
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() == nStrength )
        {
            vecCountry.push_back( m_xCountry[ i ].GetID() );
        }
    }

    // 4�����Ҷ���ͬ, û����ν������
    int nCount = vecCountry.size();
    if ( vecCountry.size() >= CountryDefine::Country_Max - 1 )
    { return; }

    int nIndex = rand() % nCount;

    m_uchStrongCountryID = vecCountry.at( nIndex );
}
template<>
void CenterCountryManager::CalcWeakCountry()
{
    m_uchWeakCountryID = CountryDefine::Country_Init;
    // �Ȼ����͵Ĺ���ʵ��
    unsigned int nStrength = 0xFFFFFFFF;
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() < nStrength )
        {
            nStrength = m_xCountry[ i ].GetLastStrength();
        }
    }

    // �����͵Ĺ���ʵ���ĸ���
    std::vector< unsigned char > vecCountry( 0 );
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() == nStrength )
        {
            vecCountry.push_back( m_xCountry[ i ].GetID() );
        }
    }

    // 4�����Ҷ���ͬ, û����ν������
    int nCount = vecCountry.size();
    if ( vecCountry.size() >= CountryDefine::Country_Max - 1 )
    { return; }

    int nIndex = rand() % nCount;

    m_uchWeakCountryID = vecCountry.at( nIndex );
}

template<>
void CenterCountryManager::SendCountryDataToGameServer( unsigned int nServerID )
{
    if ( !GetLoadSuccess() )
    { return; }

    CS2GSCountryDataList xList;
    xList.uchWeakCountryID = m_uchWeakCountryID;
	xList.uchStrongCountryID = m_uchStrongCountryID;
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        xList.xData[ i ] = m_xCountry[ i ];
    }

	//��������Ϣ���͵�GameServer ���鷢��
	CS2GSRequestCountryInfoAck msg;
	int Sum = 0;
	for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
	{
		for(int j =0;j<CountryDefine::MaxCountryInfoSum;++j)
		{
			strcpy_s(msg.Info[Sum%CountryDefine::MaxMsgCountryInfoSum],CountryDefine::MaxCountryInfoLength-1,m_xCountry[ i ].GetCountryInfo(j));
			msg.CountryID[Sum%CountryDefine::MaxMsgCountryInfoSum] = i;
			msg.Time[Sum%CountryDefine::MaxMsgCountryInfoSum] =  m_xCountry[ i ].GetCountryInfoTime(j);
			msg.values[Sum%CountryDefine::MaxMsgCountryInfoSum] =  m_xCountry[ i ].GetCountryInfoValue(j);
			++msg.Sum;
			if(msg.Sum == CountryDefine::MaxMsgCountryInfoSum)
			{
				msg.IsEnd = (i == CountryDefine::Country_Max -1 && j == CountryDefine::MaxCountryInfoSum-1);
				if ( nServerID == CountryDefine::ErrorID )
				{
					theGameServerManager.SendMessageToGameServers( &msg );
				}
				else
				{
					GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );
					if ( pGameServer != NULL )
					{
						pGameServer->Send( &msg );
					}
				}
				memset( msg.Info, 0, sizeof( msg.Info ) );
				memset( msg.Time, 0, sizeof( msg.Time ) );
				memset( msg.CountryID, 0, sizeof( msg.CountryID ) );
				memset( msg.values, 0, sizeof( msg.values ) );
				msg.Sum = 0;
				msg.IsEnd = false;
			}

			++Sum;
		}
	}
	if(msg.Sum != 0)
	{
		msg.IsEnd = true;
		if ( nServerID == CountryDefine::ErrorID )
		{
			theGameServerManager.SendMessageToGameServers( &msg );
		}
		else
		{
			GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );
			if ( pGameServer != NULL )
			{
				pGameServer->Send( &msg );
			}
		}
	}
    if ( nServerID == CountryDefine::ErrorID )
    {
        theGameServerManager.SendMessageToGameServers( &xList );
        SendWeakCountryMessage();
		SendStrongCountryMessage();
    }
    else
    {
        GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );
        if ( pGameServer != NULL )
        {
            pGameServer->Send( &xList );
        }
    }
}

template<>
void CenterCountryManager::SendWeakCountryMessage()
{
    if ( m_uchWeakCountryID == CountryDefine::Country_Init )
    { return; }

    CS2GSTellWeakCountry xTell;
    xTell.uchCountryID = m_uchWeakCountryID;

    theGameServerManager.SendMessageToCharacterServer( &xTell );
}
template<>
void CenterCountryManager::SendStrongCountryMessage()
{
	if ( m_uchStrongCountryID == CountryDefine::Country_Init )
    { return; }
	CS2GSTellStrongCountry xTell;
	xTell.uchCountryID = m_uchStrongCountryID;
    theGameServerManager.SendMessageToCharacterServer( &xTell );
}

template<>
void CenterCountryManager::SendWarStatusChangeMessage()
{
    CS2GSCountryWarStatus xStatus;
    xStatus.uchStatus = m_uchWarStatus;
    theGameServerManager.SendMessageToGameServers( &xStatus );
}


template<>
void CenterCountryManager::ProcessWarKillPlayer( unsigned char uchKillCountryID, unsigned int nKillCount, unsigned char uchDeathCountryID, unsigned int nDeathCount )
{
    CenterCountry* pKillCountry = GetCountry( uchKillCountryID );
    CenterCountry* pDeathCountry = GetCountry( uchDeathCountryID );
    if ( pKillCountry == NULL || pDeathCountry == NULL )
    { return; }

    pKillCountry->AddKillCount( nKillCount );
    pDeathCountry->AddDeathCount( nDeathCount );

    // ͬ�������з�����

    CS2GSCountryWarKillPlayer xWarKillPlayer;
    xWarKillPlayer.uchKillCountryID  = uchKillCountryID;
    xWarKillPlayer.nKillCount        = pKillCountry->GetKillCount();
    xWarKillPlayer.uchDeathCountryID = uchDeathCountryID;
    xWarKillPlayer.nDeathCount       = pDeathCountry->GetDeathCount();
    theGameServerManager.SendMessageToGameServers( &xWarKillPlayer );
}

struct SortByGreaterWarFightKill : public std::unary_function< CenterCountry, bool >
{
    bool operator() ( const CenterCountry& xLeft, const CenterCountry& xRight )
    {
        // �ж�ɱ����
        if ( xLeft.GetKillCount() > xRight.GetKillCount() )
        { return true; }

        if ( xLeft.GetKillCount() < xRight.GetKillCount() )
        { return false; }

        // �ж�������
        if ( xLeft.GetDeathCount() < xRight.GetDeathCount() )
        { return true; }

        if ( xLeft.GetDeathCount() > xRight.GetDeathCount() )
        { return false; }

        // �жϹ���ʵ��С�Ĺ���
        return xLeft.GetLastStrength() < xRight.GetLastStrength();
    }
};

template<>      // ��ս����
void CenterCountryManager::ProcessCountryWarFightSort()
{
    // ��������
    CenterCountry xCountry[ CountryDefine::Country_Max ];
    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        // ����ʹ��memcpy_s
        xCountry[ i ] = m_xCountry[ i ]; 
    }

    std::sort( xCountry + 1, xCountry + CountryDefine::Country_Max, SortByGreaterWarFightKill() );

    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        CenterCountry* pCountry = GetCountry( xCountry[i].GetID() );
        if ( pCountry == NULL ) 
        { continue; }

        pCountry->UpdateCountryData( CountryDefine::UpdateSortIndex, i );
    }
}
template<>
void CenterCountryManager::HandleAllCountryStrength(bool IsSendMsg)
{
	//����ҷ������� ���� ���ҽ�Ǯ�仯 ����
	unsigned int AllQuestSum = 0;
	unsigned int AllPlayerSum = 0;
	unsigned int AllCountryMoney= 0;
	for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        CenterCountry* pCountry = GetCountry( m_xCountry[i].GetID() );
        if ( pCountry == NULL ) 
        { continue; }
		//1.���й��ҷ�����������
		AllQuestSum += pCountry->GetAllQuestSum();
		//2.���й�������
		AllPlayerSum += pCountry->GetCountryPlayerSum();
		//3.���й����ʽ�
		AllCountryMoney += pCountry->GetMoney();
    }
	for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
		//����������ҵĹ���
		CenterCountry* pCountry = GetCountry( m_xCountry[i].GetID() );
        if ( pCountry == NULL ) 
        { continue; }		
		double Strength=(AllQuestSum ==0?0:((pCountry->GetAllQuestSum() * 1000.0) / AllQuestSum))+
			(AllPlayerSum ==0?0:((pCountry->GetCountryPlayerSum() * 6000.0)/AllPlayerSum))+
			(AllCountryMoney ==0?0:((pCountry->GetMoney() * 2000.0)/AllCountryMoney))+
			pCountry->GetTribute() * 1.0 + pCountry->GetDoneQuestAddStrength() * 1.0;
		unsigned int GeneralQuestSum = pCountry->GetQuestSumByType(CountryDefine::QuestType_General);
		if(GeneralQuestSum >0)
		{
			const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
			Strength += xSetting.GetReleaseModulus() * GeneralQuestSum;
		}
		unsigned int NowStrength = (int)Strength;
		if(pCountry->GetNowStrength() != NowStrength)
		{
			//֪ͨGameServer ����ʵ�������仯
			if(IsSendMsg)
				pCountry->UpdateCountryData(CountryDefine::UpdateNowStrength,NowStrength);
			else
				pCountry->SetNowStrength( NowStrength );
		}
	}
}
template<>
void CenterCountryManager::CalcCountryStrengthAtOnce()
{
	m_xStrengthTimer.StartTimer( 1, 65000 );
}