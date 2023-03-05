#include "CreateMonsterManager.h"
#include "TimeEx.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "AiDefine.h"
#include "MonsterCreater.h"
#include "GameServer.h"
#include "MapConfig.h"
#include "Configure.h"

#define ONE_MINUTE ( 60 * 1000 )

CreateMonsterManager::CreateMonsterManager()
{
	m_vecMonster.clear();
	m_xUpdateTimer.StartTimer(1, ONE_MINUTE);
}

CreateMonsterManager::~CreateMonsterManager()
{
	m_vecMonster.clear();
}

void CreateMonsterManager::UpdataData( CreateMonsterConfig::VecMonster& data )
{
	m_vecMonster.clear();

	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	for ( CreateMonsterConfig::vecIter iter = data.begin(); iter != data.end(); iter++ )
	{
		if ( iter->nYear != -1 && nowTime.GetYear() != iter->nYear )
			continue;
		if ( iter->nMonth != -1 && nowTime.GetMonth() != iter->nMonth )
			continue;
		if ( iter->nDay != -1 && nowTime.GetDay() != iter->nDay )
			continue;
		if ( iter->nWeek != -1 && nowTime.GetDayOfWeek() != iter->nWeek )
			continue;

		m_vecMonster.push_back( *iter );
	}
}

void CreateMonsterManager::RunUpdate( unsigned int nCurrentTime )
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
		return;

	__time64_t nowtime = 0;
	_time64(&nowtime);
	TimeEx nowTime( nowtime );

	if ( nowTime.GetHour() == 0 && nowTime.GetMinute() == 0 ) //每天0点0分更新数据
		UpdataData( theCreateMonsterConfig.GetMonsterVec() );

	for ( CreateMonsterConfig::vecIter iter = m_vecMonster.begin(); iter != m_vecMonster.end(); iter++ )
	{
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( iter->nMapId );
		if ( pMapData == NULL || !g_Cfg.IsMapRun( iter->nMapId ) )
			continue; 

		if ( nowTime.GetHour() == iter->nHour && nowTime.GetMinute() == iter->nMinute )
		{
			if ( iter->bIsOnly )
			{
				BaseCharacter* pChar = theRunTimeData.GetCharacterByMonsterID( iter->nMonsterId, iter->nMapId );
				if ( pChar && !pChar->IsDead() )
					continue;
			}

			 MonsterCreateData xCreateData;
			 xCreateData.SetMonsterID( iter->nMonsterId );
			 xCreateData.SetMapID( iter->nMapId );
			 xCreateData.SetCount( iter->nCount );
			 xCreateData.SetPostionX( iter->nX );
			 xCreateData.SetPostionY( iter->nY );

			 MonsterCreater::ProcessCreateNormalMonster( xCreateData );

			 if ( iter->strSay.length() > 0 )
			 {
				 MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
				 xChat.SetString( iter->strSay.c_str() );
				 GettheServer().SendMsgToWorld   ( &xChat, true  );
			 }
		}
	}
}