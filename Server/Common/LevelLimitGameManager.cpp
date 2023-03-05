#include "LevelLimitGameManager.h"
#include "GameServer.h"
#include "Configure.h"

CLevelLimitGameManager::CLevelLimitGameManager()
{
	isInit = false;
	StartSaveTimer(HQ_TimeGetTime());
}

CLevelLimitGameManager::~CLevelLimitGameManager()
{

}

void CLevelLimitGameManager::StartSaveTimer( unsigned int nCurrentTime )
{
	m_AckTimer.StartTimer( nCurrentTime, eLimitGlobal_DelayAck );
}


void CLevelLimitGameManager::OnMsgLevelLimitInfo(Msg2AllGameInfo* pMsg)
{
	if (!pMsg)
	{
		return;
	}

	memcpy(&sllinfo,&pMsg->sllinfo,sizeof(SLevelLimitInfo));
	isInit = true;
	m_AckTimer.StopTimer();
}

void CLevelLimitGameManager::UpdatePlayerCount(int count)
{
	if (count < 0||!isInit)
	{
		return;
	}
	sllinfo.player_count = count;
}

void CLevelLimitGameManager::AddPlayerCount(int count)
{
	if (count <= 0||!isInit||sllinfo.state == eLimitState_Done)
	{
		return;
	}
	MsgAddPlayerCountLimit addplayer;
	addplayer.add_count = count;
	GettheServer().SendMsgToCenterServer( &addplayer );
}

void CLevelLimitGameManager::ReqActiveLimit(const char* player_name)
{
	if (!player_name||!isInit||sllinfo.state != eLimitState_noActive)
	{
		return;
	}
	sllinfo.state = eLimitState_Active;
	strncpy_s( sllinfo.active_name, sizeof( sllinfo.active_name), player_name, sizeof( sllinfo.active_name) - 1 );

	//通知所有的客户端
	MsgFIRSTLIMITINFO flinfo;
	//memcpy(&flinfo.sllinfo,&sllinfo,sizeof(flinfo.sllinfo));
	flinfo.max_lv = g_Cfg.m_nLevelLimt;
	GettheServer().SendMsgToWorld(&flinfo);
}

void CLevelLimitGameManager::ActiveLimitToCS(const char* player_name)
{
	if (!player_name||!isInit||sllinfo.state != eLimitState_noActive)
	{
		return;
	}
	//todo:center server
	MsgActiveLimit msg;
	strncpy_s( msg.active_name, sizeof( msg.active_name), player_name, sizeof( msg.active_name) - 1 );
	GettheServer().SendMsgToCenterServer( &msg );
}

void CLevelLimitGameManager::RunOnStep(unsigned long cur_time)
{
	if (!isInit)
	{
		if (m_AckTimer.DoneTimer())
		{
			MsgGS2CSReqLimitInfo msg;
			GettheServer().SendMsgToCenterServer( &msg );
		}
	}
}

short CLevelLimitGameManager::GetLimitExpAward(short stLevel)
{
	if (!isInit||sllinfo.state != eLimitState_Active)
	{
		return eLimitAward_no;
	}
	short temp_lv = sllinfo.level - stLevel;
	if (temp_lv <= 0)
	{
		return eLimitAward_no;
	}

	if (stLevel < special_level)
	{
		return eLimitAward_no;
	}
	else
	{
		if (temp_lv > eLimitLevel_diff_lv3)
		{
			return eLimitAward_lv3;
		}
		else if (temp_lv > eLimitLevel_diff_lv2&& temp_lv <= eLimitLevel_diff_lv3)
		{
			return eLimitAward_lv2;
		}
		else if (temp_lv > eLimitLevel_diff_lv1 && temp_lv <= eLimitLevel_diff_lv2)
		{
			return eLimitAward_lv1;
		}
		else if(temp_lv <= 0)
		{
			return eLimitAward_maxlv;
		}
		else
			return eLimitAward_no;

	}
}

void CLevelLimitGameManager::CheckActiveLimit(const char* player_name)
{
	if (!player_name||!isInit||sllinfo.state != eLimitState_noActive)
	{
		return;
	}

	MsgActiveLimit al_msg;
	strncpy_s( al_msg.active_name, sizeof( al_msg.active_name ), player_name, sizeof( al_msg.active_name ) - 1 );
	GettheServer().SendMsgToCenterServer( &al_msg );
}

void CLevelLimitGameManager::UpdateLimitState(short _state)
{
	if (!isInit||sllinfo.state != eLimitState_Active||_state != eLimitState_Done)
	{
		return;
	}

	sllinfo.state = _state;
	MsgGS2CLimitDone msg;
	GettheServer().SendMsgToWorld(&msg);
}