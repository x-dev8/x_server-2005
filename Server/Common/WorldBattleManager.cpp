#include "WorldBattleManager.h"
#include "Configure.h"
#include "MapConfig.h"
#include "CampBattleMessage.h"
#include "GameServer.h"
#include "ScriptMgr.h"
#include "MonsterCreater.h"
#include "GlobalDBManager.h"

void WorldBattleManager::Init()
{
	unsigned int MapID = m_config.GetMapID();
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( MapID );
	if(g_Cfg.IsMapRun(MapID) && pMapData)
	{
		m_Init = true;
		m_MapPkType = pMapData->CanPk;
	}
	else
		m_Init = false;
}
bool WorldBattleManager::LoadFilePath(const char* FilePaht)
{
	return m_config.LoadFilePath(FilePaht);
}
void WorldBattleManager::Update(unsigned int nCurrentTime)
{
	if(!m_Init) return;//不需要更新
	//1分钟执行次 设置定时器

	static SYSTEMTIME xSystemTime;
    GetLocalTime( &xSystemTime );//获取系统时间

	switch(m_States)
	{
	case WBS_StatusInit:
		{
			//判断时间是否到里准备阶段
			ProcessBattleInitStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusPrepare:
		{
			//判断时间是否到了战斗阶段
			ProcessBattlePrepareStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusFight:
		{
			//判断战斗是否到了结束阶段
			ProcessBattleEndStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusEnd:
		{
			//判断战场是否需要转换到初始化状态
			m_States = WBS_StatusInit;
		}
		break;
	default:
		break;
	}
}
void WorldBattleManager::ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if ( !m_config.CheckPrepareTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )//检查是否到了报名时间
    { return; }
	//开始准备阶段
	if(m_States !=  WBS_StatusInit)
		return;
	m_States = WBS_StatusPrepare;
	//在进入准备阶段需要做的一些事情
	//1.发送通知给服务器所有玩家
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_Prepare;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
}
void WorldBattleManager::ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if ( !m_config.CheckFightTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }
	if(m_States !=  WBS_StatusPrepare)
		return;
	m_States = WBS_StatusFight;
	//战斗正式开始
	//1.广播整个服务器
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_Fight;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.修改地图的PK模式 为特定的模式 EPKM_WorldBattle_PK
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_config.GetMapID() );
	if(pMapData)
	{
		pMapData->CanPk = MapConfig::MapData::EPKM_WorldBattle_PK;
	}
	std::vector<MonsterCreateData>& vecData = m_config.GetMonstData(theGameGlobalDBManager.GetMapCountryID());
	if(vecData.empty())
		return;
	std::vector<MonsterCreateData>::iterator Iter = vecData.begin();
	for(;Iter != vecData.end();++Iter)
	{
		//刷怪
		MonsterCreater::ProcessCreateNormalMonster(*Iter);
	}
}
void WorldBattleManager::ProcessBattleEndStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if ( !m_config.CheckEndTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }
	if(m_States !=  WBS_StatusFight)
		return;
	m_States = WBS_StatusEnd;
	//战场结束 我们处理下
	//1.广播服务器 所有玩家
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_End;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.修改地图的PK类型
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_config.GetMapID() );
	if(pMapData)
	{
		pMapData->CanPk = m_MapPkType;
	}
	//3野外战场恢复的时候 是否需要移除刷出来的怪物

}
void WorldBattleManager::SetWorldBattleIsResult()
{
	//设置战场已经结束了  
	if(m_States !=  WBS_StatusFight)
		return;
	m_States = WBS_StatusEnd;
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_End;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.修改地图的PK类型
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_config.GetMapID() );
	if(pMapData)
	{
		pMapData->CanPk = m_MapPkType;
	}
	//3野外战场恢复的时候 是否需要移除刷出来的怪物
	
}