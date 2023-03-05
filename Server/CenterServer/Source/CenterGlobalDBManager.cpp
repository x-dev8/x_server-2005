#include "GlobalDBManager.h"
#include "GlobalDBMessage.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"
#include "CenterTimeHandleManager.h"
template<>
void CenterGlobalDBManager::InitGlobalDB()
{
	//发送命令到数据库去读取数据 并且将数据发送到GameServer
	//1.发送命令道数据库 去读取数据库存储的数据
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
	//当数据从数据库加载成功的时候 centerserver表示可以使用了
	theCenterTimeHandleManager.SetInit();
}
template<>
void CenterGlobalDBManager::SaveGlobalDB()
{
	//将现有数据保存到数据库 发送命令到数据
	GS2CSSaveGlobalDBReq msg;
	msg.info.SetData(m_GlobalDB);
	theMysqlCommunication.PushReqMessage( &msg,0);
}
template<>
void CenterGlobalDBManager::SendUpdateGlobalDBDataMessage( unsigned char uchType,unsigned int Index ,__int64 n64Value )
{
	//发送命令到所有的GameServer去 修改全局变量
	//1.发送命令
	CS2GSUpdateGlobalDBAck msg;
	msg.uchUpdateType = uchType;
	msg.n64Value = n64Value;
	msg.Index = Index;
	theGameServerManager.SendMessageToGameServers(&msg);
	//2.保存到数据库
	SaveGlobalDB();
}
template<>
void CenterGlobalDBManager::SetBattleSum(unsigned int Value)
{
	if(m_GlobalDB.GetBattleSum() == Value) return;
	//发送命令道GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateBattleSum,0,Value);
}
template<>
void CenterGlobalDBManager::SetMapCountryID(unsigned int Value)
{
	if(m_GlobalDB.GetMapCountryID() == Value) return;
	//发送命令道GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateMapCountryID,0,Value);
}
template<>
void CenterGlobalDBManager::SetTimeHandleLog(unsigned int Index,__int64 Value)
{
	if(m_GlobalDB.GetTimeHandleLog(Index) == Value) return;
	//发送命令道GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateTimeHandleLog,Index,Value);
}
template<>
void CenterGlobalDBManager::SetTimeHandleState(unsigned int Index,int Value)
{
	if(m_GlobalDB.GetTimeHandleState(Index) == Value) return;
	//发送命令道GameServer
	theCenterGlobalDBManager.UpdateGlobalDBData(UpdateTimeHandleState,Index,Value);
}