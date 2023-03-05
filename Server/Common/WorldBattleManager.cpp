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
	if(!m_Init) return;//����Ҫ����
	//1����ִ�д� ���ö�ʱ��

	static SYSTEMTIME xSystemTime;
    GetLocalTime( &xSystemTime );//��ȡϵͳʱ��

	switch(m_States)
	{
	case WBS_StatusInit:
		{
			//�ж�ʱ���Ƿ���׼���׶�
			ProcessBattleInitStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusPrepare:
		{
			//�ж�ʱ���Ƿ���ս���׶�
			ProcessBattlePrepareStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusFight:
		{
			//�ж�ս���Ƿ��˽����׶�
			ProcessBattleEndStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
		}
		break;
	case WBS_StatusEnd:
		{
			//�ж�ս���Ƿ���Ҫת������ʼ��״̬
			m_States = WBS_StatusInit;
		}
		break;
	default:
		break;
	}
}
void WorldBattleManager::ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if ( !m_config.CheckPrepareTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )//����Ƿ��˱���ʱ��
    { return; }
	//��ʼ׼���׶�
	if(m_States !=  WBS_StatusInit)
		return;
	m_States = WBS_StatusPrepare;
	//�ڽ���׼���׶���Ҫ����һЩ����
	//1.����֪ͨ���������������
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
	//ս����ʽ��ʼ
	//1.�㲥����������
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_Fight;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.�޸ĵ�ͼ��PKģʽ Ϊ�ض���ģʽ EPKM_WorldBattle_PK
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
		//ˢ��
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
	//ս������ ���Ǵ�����
	//1.�㲥������ �������
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_End;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.�޸ĵ�ͼ��PK����
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_config.GetMapID() );
	if(pMapData)
	{
		pMapData->CanPk = m_MapPkType;
	}
	//3Ұ��ս���ָ���ʱ�� �Ƿ���Ҫ�Ƴ�ˢ�����Ĺ���

}
void WorldBattleManager::SetWorldBattleIsResult()
{
	//����ս���Ѿ�������  
	if(m_States !=  WBS_StatusFight)
		return;
	m_States = WBS_StatusEnd;
	MsgCampWorldBattleAck msg;
	msg.uchResult = MsgCampWorldBattleAck::WBD_End;
	msg.GlobalDBCOuntryID = theGameGlobalDBManager.GetMapCountryID();
	GettheServer().SendMsgToWorld(&msg);
	//2.�޸ĵ�ͼ��PK����
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_config.GetMapID() );
	if(pMapData)
	{
		pMapData->CanPk = m_MapPkType;
	}
	//3Ұ��ս���ָ���ʱ�� �Ƿ���Ҫ�Ƴ�ˢ�����Ĺ���
	
}