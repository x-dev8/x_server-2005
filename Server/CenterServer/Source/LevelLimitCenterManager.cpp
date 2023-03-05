#include "LevelLimitCenterManager.h"
#include "Timestamp/Timestamp.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"

CLevelLimitCenterManager::CLevelLimitCenterManager()
{
	isInit = false;
}

CLevelLimitCenterManager::~CLevelLimitCenterManager()
{

}

void CLevelLimitCenterManager::StartSaveTimer( unsigned int nCurrentTime )
{
	m_saveLevelLimitTime.StartTimer( nCurrentTime, eLimitGlobal_savetime );
}

void CLevelLimitCenterManager::ProceeMySqlData(MsgAckMySQLData* pData)
{
	if (!pData)
	{
		return;
	}

	if (pData->ustCount > 0)
	{
		if (InitLevelLimit(&pData->sllinfo[0],pData->max_level))
		{
			isInit = true;
			StartSaveTimer(HQ_TimeGetTime());
		}
	}
	else
	{
		if (InitLevelLimit(NULL,pData->max_level))
		{
			isInit = true;
			StartSaveTimer(HQ_TimeGetTime());
		}
	}
}

bool CLevelLimitCenterManager::InitLevelLimit(SLevelLimitInfo* pLLInfo,int last_done_level)
{
	SLevelLimitConfig* pLLConfig = NULL;
	if (!pLLInfo)
	{
		if (last_done_level == 0)
		{
			pLLConfig = theLevelLimitConfig.GetFirstLimitConfig();
		}
		else
			pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(last_done_level);

		if (!pLLConfig)
		{
			return false;
		}

		limit_state = eLimitState_noActive;
		player_count = 0;
		trigger_lv = pLLConfig->level;
		trigger_count = pLLConfig->setup_min_count;
		active_time = 0;
		done_time =0;
		time_min = pLLConfig->time_min;
		time_max = pLLConfig->time_max;
		////////////////////////////////
		MsgAddLevelLimit msg;
		msg.sllinfo.active_time = active_time;
		msg.sllinfo.done_time = done_time;
		msg.sllinfo.level = trigger_lv;
		msg.sllinfo.next_level = pLLConfig->next_level;
		msg.sllinfo.player_count = player_count;
		msg.sllinfo.state = limit_state;
		theMysqlCommunication.PushReqMessage( &msg, 0 );
		/////////////////////////////////
		return true;
	}
	else
	{
		switch(pLLInfo->state)
		{
		case eLimitState_Done:
			{
				pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(pLLInfo->next_level);
				if (!pLLConfig)
				{
					return false;
				}

				limit_state = eLimitState_noActive;
				player_count = pLLInfo->player_count;
				trigger_lv = pLLConfig->level;
				trigger_count = pLLConfig->setup_min_count;
				active_time = 0;
				done_time = 0;
				time_min = pLLConfig->time_min;
				time_max = pLLConfig->time_max;
				memset(active_name,0,sizeof(active_name));
			}
			break;
		case eLimitState_noActive:
			{
				pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(pLLInfo->level);
				if (!pLLConfig)
				{
					return false;
				}

				limit_state = eLimitState_noActive;
				player_count = pLLInfo->player_count;
				trigger_lv = pLLConfig->level;
				trigger_count = pLLConfig->setup_min_count;
				active_time = 0;
				done_time = 0;
				time_min = pLLConfig->time_min;
				time_max = pLLConfig->time_max;
				memset(active_name,0,sizeof(active_name));
			}
			break;
		case eLimitState_Active:
			{
				pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(pLLInfo->level);
				if (!pLLConfig)
				{
					return false;
				}
				limit_state = eLimitState_Active;
				player_count = pLLInfo->player_count;
				trigger_lv = pLLConfig->level;
				trigger_count = pLLConfig->setup_min_count;
				active_time = pLLInfo->active_time;
				done_time = pLLInfo->done_time;
				per_count = pLLConfig->per_count;
				time_min = pLLConfig->time_min;
				time_max = pLLConfig->time_max;
				strncpy_s( active_name, sizeof( active_name ), pLLInfo->active_name, sizeof( active_name ) - 1 );
			}
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}

void CLevelLimitCenterManager::ProcessActiveLimit()
{
	if (limit_state != eLimitState_Active)
	{
		return;
	}

	unsigned long currtime = theTimestamp.GetTimestamp();
	if (currtime >= done_time)
	{//��ӡʱ�����
		limit_state = eLimitState_Done;
		///////////////////��֪ͨ���е�GAME SERVER��ӡ����,������������ʲô
		MsgUpdateLevelLimitSate update_state;
		update_state._state = eLimitState_Done;
		theGameServerManager.SendMessageToGameServers(&update_state);
		////////////////////////////////////////////////////////////////////////	
		/////////todo:֪ͨ�ı�MYSQLԭ״̬,֪ͨGAME SERVER������ӡ����///////////////
		UpdateToMySql();
		////////////////////////////////////////////////////////////////////////////
		SLevelLimitConfig* pLLConfig = NULL;
		pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
		if (!pLLConfig)
		{
			return;
		}
		pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(pLLConfig->next_level);
		if (!pLLConfig)
		{
			return;
		}
		//�Ȱ�״̬�Ĺ���
		limit_state = eLimitState_noActive;
		player_count = 0;
		trigger_lv = pLLConfig->level;
		trigger_count = pLLConfig->setup_min_count;
		active_time = 0;
		done_time = 0;
		time_min = pLLConfig->time_min;
		time_max = pLLConfig->time_max;
		memset(active_name,0,sizeof(active_name));
		/////////todo:�·������еķ������ı�״̬,��֪ͨ���е�CLIENT///////////////////
		SendLevelLimitInfoToAllGame();
		/////////todo:MYSQL������״̬/////////////////////////////////////////////////
		MsgAddLevelLimit msg;
		msg.sllinfo.active_time = 0;
		msg.sllinfo.done_time = 0;
		msg.sllinfo.level = trigger_lv;
		msg.sllinfo.next_level = pLLConfig->next_level;
		msg.sllinfo.player_count = player_count;
		msg.sllinfo.state = limit_state;
		memset(msg.sllinfo.active_name,0,sizeof(msg.sllinfo.active_name));
		theMysqlCommunication.PushReqMessage( &msg, 0 );
		//////////////////////////////////////////////////////////////////////////////
	}
}

void CLevelLimitCenterManager::AddPlayer(int add_count)
{
	if (add_count <= 0)
	{
		return;
	}
	player_count += add_count;

	int temp_count = player_count - trigger_count;
	if (per_count > 0&&temp_count%per_count == 0)
	{//��������ʱ��,ÿ�μ��٣�����ʱ��-����ʱ�䣩/5�ķ�ӡʱ��
	 //���1/5ʱ��С������-���޵�ʱ����ֱ�ӽ⿪��ӡ
		if (temp_count > 0)
		{
			SLevelLimitConfig* pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
			if (!pLLConfig)
			{
				return;
			}

			int sub_time = (pLLConfig->time_max - pLLConfig->time_min)/5;
			if (sub_time < 0)
			{
				return;
			}
			unsigned long temp_time = done_time - active_time;
			if (sub_time > temp_time)
			{
				sub_time = temp_time;
			}
			done_time = theTimestamp.GetTimestamp();

			SendLevelLimitInfoToAllGame();
		}
	}
	else
	{
		//ÿ�ζ�Ҫͬ��������GAME SERVER����
		UpdatePlayerCount2GS();
	}
}

void CLevelLimitCenterManager::ActiveLimit(const char* player_name)
{
	if (limit_state != eLimitState_noActive)
	{
		return;
	}

	SLevelLimitConfig* pLLConfig = NULL;
	pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
	if (!pLLConfig)
	{
		return;
	}

	limit_state = eLimitState_Active;
	active_time = theTimestamp.GetTimestamp();
	done_time = active_time + pLLConfig->time_max*3600;//��
	strncpy_s( active_name, sizeof( active_name ), player_name, sizeof( active_name ) - 1 );

	//todo:֪ͨ����GAME SERVER�����пͻ���////////////////////////////
	MsgActiveLimitAck ack;
	ack._state = eLimitState_Active;
	strncpy_s( ack.active_name, sizeof( ack.active_name ), player_name, sizeof( ack.active_name ) - 1 );
	theGameServerManager.SendMessageToGameServers(&ack);
	////////////////////////////////////////////////////////////////////
	//todo:�ı�MYSQL����״̬//////////////////////////////////////////
	UpdateToMySql();
	//////////////////////////////////////////////////////////////////
}

static bool have_req = false;
void CLevelLimitCenterManager::RunUpdate(unsigned int nCurrentTime)
{
	if (!isInit)
	{
		if (!have_req)
		{
			MsgReqMYSQLData msg;
			theMysqlCommunication.PushReqMessage( &msg, 0 );
			have_req = true;
		}
		return;
	}

	ProcessActiveLimit();

	if (m_saveLevelLimitTime.DoneTimer())
	{
		UpdateToMySql();
	}
}

void CLevelLimitCenterManager::UpdateToMySql()
{
	SLevelLimitConfig* pLLConfig = NULL;
	pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
	if (!pLLConfig)
	{
		return;
	}
	MsgUpdateLevelLimit msg;
	msg.sllinfo.active_time = active_time;
	msg.sllinfo.done_time = done_time;
	msg.sllinfo.level = trigger_lv;
	msg.sllinfo.next_level = pLLConfig->next_level;
	msg.sllinfo.player_count = player_count;
	msg.sllinfo.state = limit_state;
	strncpy_s( msg.sllinfo.active_name, sizeof( msg.sllinfo.active_name ), active_name, sizeof( msg.sllinfo.active_name ) - 1 );
	theMysqlCommunication.PushReqMessage( &msg, 0 );
}

void CLevelLimitCenterManager::SendLevelLimitInfoToAllGame()
{
	SLevelLimitConfig* pLLConfig = NULL;
	pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
	if (!pLLConfig)
	{
		return;
	}
	Msg2AllGameInfo allgame;
	allgame.sllinfo.active_time = active_time;
	allgame.sllinfo.done_time = done_time;
	allgame.sllinfo.level = trigger_lv;
	allgame.sllinfo.next_level = pLLConfig->next_level;
	allgame.sllinfo.player_count = player_count;
	allgame.sllinfo.state = limit_state;
	strncpy_s( allgame.sllinfo.active_name, sizeof( allgame.sllinfo.active_name ), active_name, sizeof( allgame.sllinfo.active_name ) - 1 );
	theGameServerManager.SendMessageToGameServers(&allgame);
}

void CLevelLimitCenterManager::UpdatePlayerCount2GS()
{
	MsgUpdatePlayerCount msg;
	msg._count = player_count;
	theGameServerManager.SendMessageToGameServers(&msg);
}

Msg2AllGameInfo* CLevelLimitCenterManager::GetLimitInfoToGame(Msg2AllGameInfo& allgame)
{
	SLevelLimitConfig* pLLConfig = NULL;
	pLLConfig = theLevelLimitConfig.GetLevelLimitConfig(trigger_lv);
	if (!pLLConfig)
	{
		return NULL;
	}
	allgame.sllinfo.active_time = active_time;
	allgame.sllinfo.done_time = done_time;
	allgame.sllinfo.level = trigger_lv;
	allgame.sllinfo.next_level = pLLConfig->next_level;
	allgame.sllinfo.player_count = player_count;
	allgame.sllinfo.state = limit_state;
	strncpy_s( allgame.sllinfo.active_name, sizeof( allgame.sllinfo.active_name ), active_name, sizeof( allgame.sllinfo.active_name ) - 1 );
	return &allgame;
}