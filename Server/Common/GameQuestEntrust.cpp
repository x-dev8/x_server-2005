#include "QuestEntrust.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "QuestEntrustMessage.h"
template<>
void GameQuestEntrustManager::RunUpdate( unsigned int nCurrentTime )
{
	
}
template<>
void GameQuestEntrustManager::SendQuestEntrustData( unsigned int nServerID )
{
	//发送部分请求到客户端去 包括可以接去的委托 和自己接去的委托 和未完成的委托
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID(nServerID);
	if(pPlayer)
	{
		MsgLoadQuestEntrustDataAck msg;
		msg.ClearAllInfo();
		if(!QuestEntrustMap.empty())
		{
			std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
			int Index = 0;
			for(;Iter != QuestEntrustMap.end();++Iter,++Index)
			{
				//判断是否为一个国家的 任务
				/*if(Iter->second.SrcPlayerID != pPlayer->GetDBCharacterID() && Iter->second.DestPlayerID != pPlayer->GetDBCharacterID() && !pPlayer->IfCanJoinQuest(Iter->second.DestQuestID))
					continue;	*/
				if(msg.PushInfo(Iter->second,(Index == QuestEntrustMap.size()-1)))
				{
					pPlayer->SendMessageToClient(&msg);
					msg.ClearAllInfo();
				}
			}
		}
		else
		{
			msg.Sum = 0;
			msg.IsEnd = true;
			msg.SetLength();
			pPlayer->SendMessageToClient(&msg);
		}
	}
}
template<>
void GameQuestEntrustManager::AddQuestEntrust(QuestEntrustStates& info)
{
	//客户端发送来添加的请求
	//1.判断指定任务是否可以执行委托
	//2.设置好结构的一些基本参数
	//3.过滤一些基本情况 如玩家的金钱
	GS2CSAddQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::DelQuestEntrust(unsigned int ID)
{
	//1.判断是否是本玩家直接发布的
	if(!GetQuestEntrust(ID))
		return;
	GS2CSDelQuestEntrustReq msg;
	msg.ID = ID;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::JoinQuestEntrust(QuestEntrustStates& info)
{
	//1.判断是否已经接取了委托
	//2.是否有条件接取委托 如任务的接取条件
	//3.
	GS2CSUpdateJoinQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::CanelQuestEntrust(QuestEntrustStates& info)
{
	GS2CSUpdateCanelQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
//1.加载配置文件 OK
//2.加载Center发来的全部数据 OK
//3.接收客户端的添加委托的请求  OK 
//4.接收客户端的删除委托的请求 OK
//5.接收客户端的接取委托的请求 OK
//6.接收客户端的放弃委托的请求 OK
//Handle 里处理
//7.接收中央服务器的添加委托的请求
//8.接收中央服务器的删除委托的请求
//9.接收中央服务器的修改委托的请求
//10.接收客户端请求全部委托的请求 OK