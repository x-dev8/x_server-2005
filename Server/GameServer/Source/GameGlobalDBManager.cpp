#include "GlobalDBManager.h"
#include "GlobalDBMessage.h"
#include "GameServer.h"
template<>
void GameGlobalDBManager::InitGlobalDB()
{
}
template<>
void GameGlobalDBManager::LoadGlobalDB(GlobalDB& info)
{
	m_GlobalDB.SetData(info);
}
template<>
void GameGlobalDBManager::SetBattleSum(unsigned int Value)
{
	//修改指定数据
	if(m_GlobalDB.GetBattleSum() == Value) return;
	m_GlobalDB.SetBattleSum(Value);
	//发送命令道CenterServer
	GS2CSUpdateGlobalDBReq msg;
	msg.uchUpdateType = UpdateBattleSum;
	msg.n64Value = Value;
	msg.Index = 0;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameGlobalDBManager::SetMapCountryID(unsigned int Value)
{
	if(m_GlobalDB.GetMapCountryID() == Value) return;
	m_GlobalDB.SetMapCountryID(Value);
	//发送命令道CenterServer
	GS2CSUpdateGlobalDBReq msg;
	msg.uchUpdateType = UpdateMapCountryID;
	msg.n64Value = Value;
	msg.Index = 0;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameGlobalDBManager::SetTimeHandleLog(unsigned int Index,__int64 Value)
{
	if(m_GlobalDB.GetTimeHandleLog(Index) == Value) return;
	m_GlobalDB.SetTimeHandleLog(Index,Value);
	GS2CSUpdateGlobalDBReq msg;
	msg.uchUpdateType = UpdateTimeHandleLog;
	msg.n64Value = Value;
	msg.Index = Index;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameGlobalDBManager::SetTimeHandleState(unsigned int Index,int Value)
{
	if(m_GlobalDB.GetTimeHandleState(Index) == Value) return;
	m_GlobalDB.SetTimeHandleState(Index,Value);
	GS2CSUpdateGlobalDBReq msg;
	msg.uchUpdateType = UpdateTimeHandleState;
	msg.n64Value = Value;
	msg.Index = Index;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameGlobalDBManager::SendUpdateGlobalDBDataMessage( unsigned char uchType,unsigned int Index, __int64 n64Value )
{
	
}
