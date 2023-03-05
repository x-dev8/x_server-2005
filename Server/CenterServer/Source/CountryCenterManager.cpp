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

    // 处理加载数据
    ProcessLoadCountryData( nCurrentTime );

    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        m_xCountry[ i ].RunUpdate( nCurrentTime );
    }

    // 处理国家屠城战逻辑
    ProcessCountryWarFightUpdate( nCurrentTime );

	ProcessCalcCountryStrength(nCurrentTime);//强弱国更新
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
        //定时处理
		for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
		{
			m_xCountry[ i ].ProcessCalcCountryStrength(nCurrentTime);
		}
		//处理完毕后 更新强弱国数据
		CalcWeakCountry();
		CalcStrongCountry();
		//发生数据到GameServer
		HandleAllCountryStrength();//基本当前所有国家的国力 并且发送国力改变的消息
		//发送强弱国消息到Character
		SendWeakCountryMessage();
		SendStrongCountryMessage();
		//发送强弱国消息到GameServer
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
            ProcessCountryWarFightSort();   // 处理国战杀人排行
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
	//计算强国ID
	m_uchStrongCountryID = CountryDefine::Country_Init;
    // 先获得最低的国家实力
    unsigned int nStrength = 0;
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() > nStrength )
        {
            nStrength = m_xCountry[ i ].GetLastStrength();
        }
    }

    // 获得最高的国家实力的个数
    std::vector< unsigned char > vecCountry( 0 );
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() == nStrength )
        {
            vecCountry.push_back( m_xCountry[ i ].GetID() );
        }
    }

    // 4个国家都相同, 没有所谓的弱国
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
    // 先获得最低的国家实力
    unsigned int nStrength = 0xFFFFFFFF;
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() < nStrength )
        {
            nStrength = m_xCountry[ i ].GetLastStrength();
        }
    }

    // 获得最低的国家实力的个数
    std::vector< unsigned char > vecCountry( 0 );
    for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_xCountry[ i ].GetLastStrength() == nStrength )
        {
            vecCountry.push_back( m_xCountry[ i ].GetID() );
        }
    }

    // 4个国家都相同, 没有所谓的弱国
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

	//将国家信息发送到GameServer 分组发送
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

    // 同步给所有服务器

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
        // 判断杀人数
        if ( xLeft.GetKillCount() > xRight.GetKillCount() )
        { return true; }

        if ( xLeft.GetKillCount() < xRight.GetKillCount() )
        { return false; }

        // 判断死亡数
        if ( xLeft.GetDeathCount() < xRight.GetDeathCount() )
        { return true; }

        if ( xLeft.GetDeathCount() > xRight.GetDeathCount() )
        { return false; }

        // 判断国家实力小的国家
        return xLeft.GetLastStrength() < xRight.GetLastStrength();
    }
};

template<>      // 国战排行
void CenterCountryManager::ProcessCountryWarFightSort()
{
    // 计算排行
    CenterCountry xCountry[ CountryDefine::Country_Max ];
    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        // 不能使用memcpy_s
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
	//因国家发布任务 或者 国家金钱变化 国家
	unsigned int AllQuestSum = 0;
	unsigned int AllPlayerSum = 0;
	unsigned int AllCountryMoney= 0;
	for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        CenterCountry* pCountry = GetCountry( m_xCountry[i].GetID() );
        if ( pCountry == NULL ) 
        { continue; }
		//1.所有国家发布的任务数
		AllQuestSum += pCountry->GetAllQuestSum();
		//2.所有国家人数
		AllPlayerSum += pCountry->GetCountryPlayerSum();
		//3.所有国家资金
		AllCountryMoney += pCountry->GetMoney();
    }
	for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
		//计算各个国家的国力
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
			//通知GameServer 国家实力发生变化
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