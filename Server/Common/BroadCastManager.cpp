#include "BroadCastManager.h"
#include "TimeEx.h"
#include "..\CenterServer\Source\GameServerManager.h"

#define ONE_MINUTE ( 60 * 1000 )
#define ONE_DAY ( 24 * 60 * 60 )

BroadCastManager::BroadCastManager()
{
	m_xUpdateTimer.StartTimer(1, ONE_MINUTE);
}

BroadCastManager::~BroadCastManager()
{
	m_vecType0.clear();
	m_vecType1.clear();
	m_vecType2.clear();
	m_vecType3.clear();
	m_vecType4.clear();
}

void BroadCastManager::UpdataData()
{
	Updata0( theBroadCastConfig.GetType0() );
	Updata1( theBroadCastConfig.GetType1() );
	Updata2( theBroadCastConfig.GetType2() );
	Updata3( theBroadCastConfig.GetType3() );
	Updata4( theBroadCastConfig.GetType4() );
}

void BroadCastManager::Updata0( BroadCastConfig::VecType0& data )
{
	m_vecType0.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);

	for ( BroadCastConfig::type0iter iter = data.begin(); iter != data.end(); iter++ )
	{

		if ( nowtime > iter->mSETime.nEnd )
			continue;
		if ( iter->mSETime.nStart > nowtime && ( iter->mSETime.nStart - nowtime > ONE_DAY ) )
			continue;

		iter->mLastTime = nowtime;

		m_vecType0.push_back( *iter );
	}
}

void BroadCastManager::Updata1( BroadCastConfig::VecType1& data )
{
	m_vecType1.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);

	for ( BroadCastConfig::type1iter iter = data.begin(); iter != data.end(); iter++ )
	{
		if ( nowtime > iter->mSETime.nEnd )
			continue;
		if ( iter->mSETime.nStart > nowtime && ( iter->mSETime.nStart - nowtime > ONE_DAY ) )
			continue;

		m_vecType1.push_back( *iter );
	}
}

void BroadCastManager::Updata2( BroadCastConfig::VecType2& data )
{
	m_vecType2.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( BroadCastConfig::type2iter iter = data.begin(); iter != data.end(); iter++ )
	{
		if ( nowtime > iter->mSETime.nEnd )
			continue;
		if ( iter->mSETime.nStart > nowtime && ( iter->mSETime.nStart - nowtime > ONE_DAY ) )
			continue;
		if ( nowTime.GetDayOfWeek() != iter->nWeek )
			continue;

		iter->mLastTime = nowtime;

		m_vecType2.push_back( *iter );
	}
}

void BroadCastManager::Updata3( BroadCastConfig::VecType3& data )
{
	m_vecType3.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( BroadCastConfig::type3iter iter = data.begin(); iter != data.end(); iter++ )
	{
		if ( nowtime > iter->mSETime.nEnd )
			continue;
		if ( iter->mSETime.nStart > nowtime && ( iter->mSETime.nStart - nowtime > ONE_DAY ) )
			continue;
		if ( nowTime.GetDayOfWeek() != iter->nWeek )
			continue;

		m_vecType3.push_back( *iter );
	}
}

void BroadCastManager::Updata4( BroadCastConfig::VecType4& data )
{
	m_vecType4.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);

	for ( BroadCastConfig::type4iter iter = data.begin(); iter != data.end(); iter++ )
	{
		iter->mLastTime = nowtime;
		m_vecType4.push_back( *iter );
	}
}

void BroadCastManager::RunUpdate( unsigned int nCurrentTime )
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
		return;

	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	if ( nowTime.GetHour() == 0 && nowTime.GetMinute() == 1 ) //每天0点1分更新数据
		UpdataData();

	runUpdateType0( nCurrentTime );
	runUpdateType1( nCurrentTime );
	runUpdateType2( nCurrentTime );
	runUpdateType3( nCurrentTime );
	runUpdateType4( nCurrentTime );
}

void BroadCastManager::runUpdateType0( unsigned int nCurrentTime )
{
	__time64_t nowtime = 0;
	_time64(&nowtime);

	for ( BroadCastConfig::type0iter iter = m_vecType0.begin(); iter != m_vecType0.end(); iter++ )
	{
		if ( nowtime < iter->mSETime.nStart || nowtime > iter->mSETime.nEnd )
			continue;

		if ( nowtime - iter->mLastTime >= ( iter->nSpaceTime * 60 ) )
		{
			MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
			xChat.SetString( iter->mCommon.strTip.c_str() );
			theGameServerManager.SendMsgToWorldUser( &xChat );

			iter->mLastTime = nowtime;
		}
	}
}

void BroadCastManager::runUpdateType1( unsigned int nCurrentTime )
{
	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( BroadCastConfig::type1iter iter = m_vecType1.begin(); iter != m_vecType1.end(); iter++ )
	{
		if ( nowtime < iter->mSETime.nStart || nowtime > iter->mSETime.nEnd )
			continue;

		if ( nowTime.GetHour() == iter->mTime.nHour && nowTime.GetMinute() == iter->mTime.nMinute )
		{
			MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
			xChat.SetString( iter->mCommon.strTip.c_str() );
			theGameServerManager.SendMsgToWorldUser( &xChat );
		}
	}
}

void BroadCastManager::runUpdateType2( unsigned int nCurrentTime )
{
	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( BroadCastConfig::type2iter iter = m_vecType2.begin(); iter != m_vecType2.end(); iter++ )
	{
		if ( nowtime < iter->mSETime.nStart || nowtime > iter->mSETime.nEnd )
			continue;
		if ( nowTime.GetDayOfWeek() != iter->nWeek )
			continue;

		if ( nowtime - iter->mLastTime >= ( iter->nSpaceTime * 60 ) )
		{
			MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
			xChat.SetString( iter->mCommon.strTip.c_str() );
			theGameServerManager.SendMsgToWorldUser( &xChat );

			iter->mLastTime = nowtime;
		}
	}
}

void BroadCastManager::runUpdateType3( unsigned int nCurrentTime )
{
	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( BroadCastConfig::type3iter iter = m_vecType3.begin(); iter != m_vecType3.end(); iter++ )
	{
		if ( nowtime < iter->mSETime.nStart || nowtime > iter->mSETime.nEnd )
			continue;
		if ( nowTime.GetDayOfWeek() != iter->nWeek )
			continue;

		if ( nowTime.GetHour() == iter->mTime.nHour && nowTime.GetMinute() == iter->mTime.nMinute )
		{
			MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
			xChat.SetString( iter->mCommon.strTip.c_str() );
			theGameServerManager.SendMsgToWorldUser( &xChat );
		}
	}
}

void BroadCastManager::runUpdateType4( unsigned int nCurrentTime )
{
	__time64_t nowtime = 0;
	_time64(&nowtime);

	for ( BroadCastConfig::type4iter iter = m_vecType4.begin(); iter != m_vecType4.end(); iter++ )
	{
		if ( nowtime - iter->mLastTime >= ( iter->nSpaceTime * 60 ) )
		{
			MsgCS2GSBroadCast msg;

			msg.type = MsgCS2GSBroadCast::Type_Monster;
			msg.nMonsterID = iter->nMonsterID;
			msg.nMapID = iter->nMapID;

			theGameServerManager.SendMessageToGameServers(&msg);

			iter->mLastTime = nowtime;
		}
	}
}

void BroadCastManager::OnMsgAck( MsgGS2CSBroadCastAck* pMessage )
{
	if ( !pMessage )
		return;

	if ( pMessage->type == MsgCS2GSBroadCast::Type_Monster )
	{
		for ( BroadCastConfig::type4iter iter = m_vecType4.begin(); iter != m_vecType4.end(); iter++ )
		{
			if ( iter->nMonsterID == pMessage->nResult )
			{
				MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
				xChat.SetString( iter->mCommon.strTip.c_str() );
				theGameServerManager.SendMsgToWorldUser( &xChat );

				break;
			}
		}
	}
}