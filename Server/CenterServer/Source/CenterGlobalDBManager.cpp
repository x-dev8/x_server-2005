#include "GlobalDBManager.h"
#include "GlobalDBMessage.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"
#include "CenterTimeHandleManager.h"
template<>
void CenterGlobalDBManager::InitGlobalDB()
{
	//����������ݿ�ȥ��ȡ���� ���ҽ����ݷ��͵�GameServer
	//1.������������ݿ� ȥ��ȡ���ݿ�洢������
	static bool IsInit = true;
	if(IsInit)
	{
		GS2CSLoadGlobalDBReq msg;
		theMysqlCommunication.PushReqMessage( &msg,0);
		IsInit = false;
	}
}
template<>
void CenterGlobalDBManager::LoadGlobalDB(GlobalDB& info)
{
	m_GlobalDB.SetData(info);
	//�����ݴ����ݿ���سɹ���ʱ�� centerserver��ʾ����ʹ����
	theCenterTimeHandleManager.SetInit();
}
template<>
void CenterGlobalDBManager::SaveGlobalDB()
{
	//���������ݱ��浽���ݿ� �����������
	GS2CSSaveGlobalDBReq msg;
	msg.info.SetData(m_GlobalDB);
	theMysqlCommunication.PushReqMessage( &msg,0);
}
template<>
void CenterGlobalDBManager::SendUpdateGlobalDBDataMessage( unsigned char uchType,unsigned int Index ,__int64 n64Value )
{
	//����������е�GameServerȥ �޸�ȫ�ֱ���
	//1.��������
	CS2GSUpdateGlobalDBAck msg;
	msg.uchUpdateType = uchType;
	msg.n64Value = n64Value;
	msg.Index = Index;
	theGameServerManager.SendMessageToGameServers(&msg);
	//2.���浽���ݿ�
	SaveGlobalDB();
}
template<>
void CenterGlobalDBManager::SetBattleSum(unsigned int Value)
{
	if(m_GlobalDB.GetBattleSum() == Value) return;
	//���������GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateBattleSum,0,Value);
}
template<>
void CenterGlobalDBManager::SetMapCountryID(unsigned int Value)
{
	if(m_GlobalDB.GetMapCountryID() == Value) return;
	//���������GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateMapCountryID,0,Value);
}
template<>
void CenterGlobalDBManager::SetTimeHandleLog(unsigned int Index,__int64 Value)
{
	if(m_GlobalDB.GetTimeHandleLog(Index) == Value) return;
	//���������GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateTimeHandleLog,Index,Value);
}
template<>
void CenterGlobalDBManager::SetTimeHandleState(unsigned int Index,int Value)
{
	if(m_GlobalDB.GetTimeHandleState(Index) == Value) return;
	//���������GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateTimeHandleState,Index,Value);
}