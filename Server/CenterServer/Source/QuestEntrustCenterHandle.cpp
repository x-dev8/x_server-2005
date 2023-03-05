#include "NetEvent.h"
#include "GameServerManager.h"
#include "QuestEntrust.h"
#include "QuestEntrustMessage.h"
#include "..\CenterServer\Source\MySqlCommunication.h"
long NetEvent::OnProcessQuestEntrustMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( GS2CS_ADDQUESTENTRUSTREQ, GS2CSAddQuestEntrustReq, _OnGS2CSAddQuestEntrustReq );
		MESSAGE_HANDLE( GS2CS_DELQUESTENTRUSTREQ, GS2CSDelQuestEntrustReq, _OnGS2CSDelQuestEntrustReq );
		MESSAGE_HANDLE( GS2CS_UPDATEJOINQUESTENTRUSTREQ, GS2CSUpdateJoinQuestEntrustReq, _OnGS2CSUpdateJoinQuestEntrustReq );
		MESSAGE_HANDLE( GS2CS_UPDATECANELQUESTENTRUSTREQ, GS2CSUpdateCanelQuestEntrustReq, _OnGS2CSUpdateCanelQuestEntrustReq );
		MESSAGE_HANDLE( GS2CS_QUESTENTRUSTSECCREQ, GS2CSQuestEntrustSeccReq, _OnGS2CSQuestEntrustSeccReq );
		MESSAGE_HANDLE( GS2CS_QUESTENTRUSTENDREQ, GS2CSQuestEntrustEndReq, _OnGS2CSQuestEntrustEndReq );
    MESSAGE_MAPPING_END
    return ER_Success;
}
void NetEvent::_OnGS2CSAddQuestEntrustReq( NetClient* pNetClient, GS2CSAddQuestEntrustReq* pMessage )
{
	//玩家申请添加一个任务委托
	if(theCenterQuestEntrustManager.GetConfig().GetChangeQuestID(pMessage->info.SrcQuestID) == 0)
		return;
	theCenterQuestEntrustManager.AddQuestEntrust(pMessage->info);
}
void NetEvent::_OnGS2CSDelQuestEntrustReq( NetClient* pNetClient, GS2CSDelQuestEntrustReq* pMessage )
{
	unsigned int ID = pMessage->ID;
	QuestEntrustStates* pInfo = theCenterQuestEntrustManager.GetQuestEntrust(ID);
	if(!pInfo)
		return;
	theCenterQuestEntrustManager.DelQuestEntrust(ID);
}
void NetEvent::_OnGS2CSUpdateJoinQuestEntrustReq( NetClient* pNetClient, GS2CSUpdateJoinQuestEntrustReq* pMessage )
{
	theCenterQuestEntrustManager.JoinQuestEntrust(pMessage->info);
}
void NetEvent::_OnGS2CSUpdateCanelQuestEntrustReq( NetClient* pNetClient, GS2CSUpdateCanelQuestEntrustReq* pMessage )
{
	theCenterQuestEntrustManager.CanelQuestEntrust(pMessage->info);
}
void NetEvent::_OnGS2CSQuestEntrustSeccReq( NetClient* pNetClient, GS2CSQuestEntrustSeccReq* pMessage )
{
	//玩家成功完成了奖励
	QuestEntrustStates* pInfo = theCenterQuestEntrustManager.GetQuestEntrust(pMessage->ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID == 0)
		return;
	pInfo->IsSecc = true;
	//发送命令道全部的GameServer去
	CS2GSQuestEntrustSeccAck msg;
	msg.ID = pInfo->ID;
	theGameServerManager.SendMessageToGameServers( &msg );
	//发送到数据库去存储起来
	/*CS2DBQuestEntrustDataSaveReq msgDB;
	msgDB.info = *pInfo;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/

	theCenterQuestEntrustManager.UpdateIDInList(pMessage->ID);
	if(!theCenterQuestEntrustManager.IsSaveTimerStart())
		theCenterQuestEntrustManager.StartSaveTimer(HQ_TimeGetTime());
}
void NetEvent::_OnGS2CSQuestEntrustEndReq( NetClient* pNetClient, GS2CSQuestEntrustEndReq* pMessage )
{
	QuestEntrustStates* pInfo = theCenterQuestEntrustManager.GetQuestEntrust(pMessage->ID);
	if(!pInfo)
		return;
	if(!pInfo->IsSecc)
		return;
	theCenterQuestEntrustManager.EraseQuestEntrust(pMessage->ID);
	//发送到数据库去
	//CS2DBQuestEntrustDeleteReq msgDB;
	//msgDB.ID = pMessage->ID;
	//theMysqlCommunication.PushReqMessage( &msgDB, 0 );

	theCenterQuestEntrustManager.DelIDInList(pMessage->ID);
	if(!theCenterQuestEntrustManager.IsSaveTimerStart())
		theCenterQuestEntrustManager.StartSaveTimer(HQ_TimeGetTime());

	CS2GSQuestEntrustEndAck msg;
	msg.ID = pMessage->ID;
	theGameServerManager.SendMessageToGameServers( &msg );
}