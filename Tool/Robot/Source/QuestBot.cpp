#include "stdafx.h"
#include "Bot.h"
#include "QuestBot.h"
#include "GameDefineBot.h"
#include "Tinyxml/tinyxml.h"
#include "ItemDetail.h"
#include "GameBot.h"



#define theQuestManager QuestManager::Instance()			//任务管理
#define theQuestInfo QuestInfo::Instance()				//任务数据
#define MountQuestId (3023)

#define Space_Time (1000)
#define ReqScriptSpaceTime  (10 * Space_Time)
////////////////////////////////////////////////////////////////////////////
bool CQuestBot::m_bLoad = false;
bool CQuestBot::m_bLoadSuccessed = true;
bool CQuestBot::IsLoadQust = false;
CQuestBot::MapForQustType CQuestBot::m_MapForQuset;
CQuestBot::DropItemContainer CQuestBot::DorpItemList;
CQuestBot::CQuestBot()
{

   m_BotType = Bot_Quest;


	m_dwNextRunTime = 0;
	m_bRunQuestStart = false;

	m_eQuestState = Quest_NotActive;

	m_nNpcId = -1;

	if (!m_bLoad)
	{
		CString strText = "";
		//载入任务信息
		if (!LoadQuest())
       {
           strText.Format("加载 %s 失败！", Quest_File);
           AfxMessageBox(strText);
           m_bLoadSuccessed = false;
       }
       ParseQuestForMap(theQuestInfo.m_pQuests);
		//载入NPC信息
		if (theNpcInfo.LoadConfig(NpcXml_File) != File_Success)
		{
			strText.Format("加载 %s 失败！", NpcXml_File);
			AfxMessageBox(strText);
			m_bLoadSuccessed = false;
		}

		//载入寻路表
		if (thePositionInfo.LoadConfig(Position_File) != File_Success)
		{
			strText.Format("加载 %s 失败！", Position_File);
			AfxMessageBox(strText);
			m_bLoadSuccessed = false;
		}
       
       if (!LoadMonsetDropItem(Quest_DropFile))
       {
           strText.Format("加载 %s 失败！", Quest_DropFile);
           AfxMessageBox(strText);
           m_bLoadSuccessed = false;
       }
		m_bLoad = true;
	}
   CurRunQuest.clear();
   NoQuestTime = 0;
   bFirst = true;
	//SetMoveNpcPoint();		//设置坐标

   TotalDoneQuestCondition = 0;
   CurDoneQuestCondition = 0;
   NeedItemId = ErrorUnsignedShortID;
   InitRunTime = 0;
   ReqItemTime = 0;
   bMoveToMonster = false;
   MaxKillNum = -1;
   KillIndex = -1;
   FrontQuestId = -1;
   CurQuestId = -1;
   IsSendRecvQuest = false;
   ReqNpcScriptTime = 0;
   MoveTime = 0;

   ZeroMemory(LocalVars,sizeof(LocalVars));
   NeedKillMonster = false;
}

// unsigned short ParseQuestForType( SQuest* quest ) // 分析任务的种类
// {
//     
// }


bool CQuestBot::LoadQuest()
{
   if (!IsLoadQust)
   {
       if (!theQuestInfo.LoadQuest(Quest_File, false))
       {
           return false;
       }
       IsLoadQust = true;
   }
   return true;
}

bool CQuestBot::ParseQuestForMap(QuestInfo::SQuests& m_pQuests)
{
   if (!m_MapForQuset.empty())
   {
       return true;
   }
   QuestInfo::SQuests::iterator BeginItr = m_pQuests.begin();
   QuestInfo::SQuests::iterator EndItr = m_pQuests.end();
   for (;BeginItr != EndItr;++BeginItr)
   {
       m_MapForQuset.insert(MapForQustType::value_type(BeginItr->second->MapId,&(*BeginItr->second)));
   }
   return true;
}

void CQuestBot::GetNpcByMap(int MapId)
{
//     m_NpcForMap.clear();
//     for (int i = 0;i<theNpcInfo.GetNpcCount();++i)
//     {
//         NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(i);
//         if (NULL != pNpc)
//         {
//             if (pNpc->mapId == MapId)
//                 m_NpcForMap.insert(MapForNpcType::value_type(MapId,pNpc));
//         }
//     }
}

void CQuestBot::GetUnActiveQustDone(int curmapid)
{
   if (!CurRunQuest.empty())
       return;

   typedef std::pair<MapForQustType::iterator,MapForQustType::iterator> Pairs;
   // 检查

   Pairs ValuePair = m_MapForQuset.equal_range(curmapid);
   for (MapForQustType::iterator itr = ValuePair.first; itr != ValuePair.second;++itr)
   {
       SQuest* quest = itr->second;
       if ( !theQuestManager.IsQuestDone( GetRoleVarValue( quest->Id ) ) )
       {
           PushToRunQuest(quest);
       }
   }
}

void CQuestBot::PushToRunQuest(SQuest* quest)
{
   if (NULL == quest)
       return;

   bool bFind = false;
   for(QuestList::iterator itr = CurRunQuest.begin();itr != CurRunQuest.end();++itr)
   {
       if ((*itr)->Id == quest->Id)
       {
           bFind = true;
           break;
       }
   }

   if (!bFind)
   {
       CurRunQuest.push_back(quest);
   }
}

CQuestBot::~CQuestBot()
{

}

void CQuestBot::InitPlayGame(UINT mapid)
{
   m_bFlyMap = true;
   //CBot::InitPlayGame(mapid);
}

void CQuestBot::CheckQuest()
{
   for (QuestList::iterator itr = CurRunQuest.begin();itr != CurRunQuest.end();)
   {
       if(QuestManager::Instance().IsQuestDone(GetRoleVarValue((*itr)->Id)))
       {
           itr = CurRunQuest.erase(itr);
           FrontQuestId = -1;
           continue;
       }
       else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue((*itr)->Id)))
       {
           if (m_eQuestState == Quest_NotActive )
           {
               m_eQuestState = Quest_Refer;
           }
           return;
       }
       ++itr;
   }
}

void CQuestBot::PlayGame()
{
	//Say("做任务真开心，有钱又有经验，大家一起来呀！");
	if (m_bLoadSuccessed)		//加载成功才可以执行
	{
		PlayQuest();
	}	
}

int CQuestBot::GetNpcById()
{
   if (NeedKillMonster)
   {
       PlayerInfo* Target = NULL;
       for (PlayerInfoContainer::iterator itr = m_listMonsterList.begin();itr != m_listMonsterList.end();++itr)
       {
           if (itr->dwCharacterID == m_xTargetNpcPoint.nNpcId)
           {
               Target = &(*itr);
               break;
           }
       }

       if (NULL != Target)
       {
           //MoveToPoint(Target->m_vPos);
           return Target->shPlayerID;
       }
       return -1;
   }
   NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_xTargetNpcPoint.nNpcId);
   if (pNpc != NULL)
   {
       PlayerInfo* pPlayerInfo = GetPlayerByName(pNpc->name);
       if (NULL != pPlayerInfo)
       {
           m_xTargetNpcPoint.nMapId = pNpc->mapId;
           m_xTargetNpcPoint.x = pNpc->x;
           m_xTargetNpcPoint.y = pNpc->y;
           return pPlayerInfo->shPlayerID;
       }
   }
   return -1;
}

void CQuestBot::PlayQuest()
{
//     {
//         // 针对某个特定任务进行测试
//         
//         DWORD dwNowTime = HQ_TimeGetTime();
//         if (dwNowTime < m_dwNextRunTime)
//         {
//             return;
//         }
//         m_dwNextRunTime = HQ_TimeGetTime() + 1 * Space_Time;
//         if(GetBotLevel()<6)
//         {
//             MsgChat ChatMsg(MsgChat::CHAT_TYPE_NORMAL);
//             char buf[255];
//             sprintf_s(buf,sizeof(buf),"/self changelevel 7");
//             ChatMsg.SetString(buf);
//             SendMsg(&ChatMsg);
//             return;
//         }
//         if (GetMapID() != 3)
//         {
//             MsgChat ChatMsg(MsgChat::CHAT_TYPE_NORMAL);
//             char buf[255];
//             sprintf_s(buf,sizeof(buf),"/flytomap 3 261 253");
//             ChatMsg.SetString(buf);
//             SendMsg(&ChatMsg);
//             return;
//         }
//         if (QuestManager::IsQuestActive(GetRoleVarValue(3049)))
//         {
//             MsgAbandonTask AbanMsg;
//             AbanMsg.stTaskId = 3049;
//             SendMsg(&AbanMsg);
//             return;
//         }
//         else
//         {
//             CurQuestId = 3049;
//         }
// 
//         NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(263);
//         if (pNpc != NULL)
//         {
//             D3DXVECTOR3 xPos;
//             xPos.x = pNpc->x;
//             xPos.y = pNpc->y;
//             xPos.z = 0;
//             if(MoveToPoint(xPos))
//             {
//                 PlayerInfo* pPlayerInfo = GetPlayerByName(pNpc->name);
//                 if (NULL != pPlayerInfo
//                     && HQ_TimeGetTime() - ReqItemTime >= 5 * Space_Time)
//                 {
//                     MsgReqScript MsgScript;
//                     MsgScript.header.stID = GetBotShortId();
//                     MsgScript.stNpcId = pPlayerInfo->shPlayerID;
//                     SendMsg(&MsgScript);
//                     ReqItemTime = HQ_TimeGetTime();
//                 }
//             }
//         }
// 
//         
//         return;
//     }
///////////////以上代码 专用 测试某个任务////////

   if (!AutoRunPosList.empty())
   {
       MoveToPoint(AutoRunPosList.front());
       return;
   }

   if (QuestManager::Instance().IsQuestDone( GetRoleVarValue(CurQuestId) ))
   {
       m_nNpcId = -1;
       CurQuestId = -1;
   }
   else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(CurQuestId)))
   {
       if(!NeedKillMonster)
       {
           m_xTargetNpcPoint.nNpcId = -1;
           m_xTargetNpcPoint.nMapId = -1;
       }
   }

   DWORD dwNowTime = HQ_TimeGetTime();
   if (dwNowTime < m_dwNextRunTime)
   {
       return;
   }

   if(!NeedKillMonster)
   {
	    if (!MoveToNpcPoint())		//先跑到npc
	    {
		    return;
	    }

	    //先获得动态ID
       int TempNpcId = GetNpcById();

       if (TempNpcId == -1 && m_xTargetNpcPoint.nNpcId != -1)
       {
           D3DXVECTOR3 xPos;
           xPos.x = m_xTargetNpcPoint.x;
           xPos.y = m_xTargetNpcPoint.y;
           xPos.z = 0;
           bool bIsOk = MoveToPoint(xPos);
           if (!bIsOk)
           {
               return;
           }
       }
       if (TempNpcId!= -1)
       {
           m_nNpcId = TempNpcId;
       }
   }
	if (m_nNpcId != -1 || NeedKillMonster)
	{
		switch (m_eQuestState)
		{
		case Quest_NotActive:
			{
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(CurQuestId))
                   /*||QuestManager::IsQuestCast(LocalVars[(*CurRunQuest.begin())->Id])*/)
               {
                   m_eQuestState = Quest_Refer;
                   break;
               }
               if (!IsSendRecvQuest || HQ_TimeGetTime() - ReqNpcScriptTime >= ReqScriptSpaceTime)
               {
				    MsgReqScript MsgScript;
                   MsgScript.header.stID = GetBotShortId();
				    MsgScript.stNpcId = m_nNpcId;
				    SendMsg(&MsgScript);

				    SetTipsInfo("接任务");
				    ReqNpcScriptTime = HQ_TimeGetTime();
                   IsSendRecvQuest = true;
               }
			}
			break;

		case Quest_Refer:
			{
               unsigned short questType = ParseQuestForType(QuestManager::Instance().GetQuest(CurQuestId));
               if (DoQuest(questType))
               {
                   m_eQuestState = Quest_CasterState;
                   //m_nNpcId = -1;
                   m_xTargetNpcPoint.nMapId = -1;
               }
               m_dwNextRunTime = dwNowTime + 200;
			}
			break;
		case Quest_CasterState:		//任务可以提交了
			{
               unsigned short questType = ParseQuestForType(QuestManager::Instance().GetQuest(CurQuestId));
               if (DoQuest(questType) && HQ_TimeGetTime() - ReqNpcScriptTime >= ReqScriptSpaceTime)
               {
                   MsgReqScript MsgScript;
                   MsgScript.stNpcId = m_nNpcId;
                   SendMsg(&MsgScript);

                   SetTipsInfo("提交任务");
                   ReqNpcScriptTime = HQ_TimeGetTime();
                   //m_nNpcId = -1;
                   m_xTargetNpcPoint.nMapId = -1;
               }                
			}
			break;
		case Quest_Done:
			{
				//任务已经完成,设置任务状态未激活
				//m_eQuestState = Quest_NotActive;
               CurDoneQuestCondition++;
               EreaseQuest(CurQuestId);
				SetTipsInfo("任务已完成");
				m_dwNextRunTime = dwNowTime + Space_Time;
			}
			break;
		default:
			break;
		}		
	}	
}

void CQuestBot::SwitchMsg(Msg* pMsg)
{
	if (pMsg == NULL)
	{
		return;
	}

	switch(pMsg->GetType())
	{
	case MSG_TELLMAP_NPCQUEST:
		OnMsg_TellMap_NpcQuest(pMsg);
		break;

	case MSG_ALLNPCONTHEMAP:
		OnMsg_AllNpcInTheMap(pMsg); //服务器回应的NPC 动态ID
		break;

	case MSG_ACK_SCRIPT:
		OnMsg_Ack_Script(pMsg);
		break;

	case MSG_TELL_CHAR_VAR:
		OnMsg_TellCharVar(pMsg);
		break;

	case MSG_SCRIPT_REQ_SHOW_QUEST_DLG: ///接受到消息
		OnMsg_ScriptReqShowQuestDlg(pMsg);
		break;

   case MSG_CHANGEMAP:
       OnMsgChangeMap(pMsg);
       break;
	default:
		BaseRobot::SwitchMsg(pMsg);
		break;
	}
}

bool CQuestBot::CheckBag(SCharItem *Addr,int ItemId,int &ItemCount)
{
   if (NULL == Addr)
       return false;

   for (int i = 0;i< 20;++i)
   {
       SCharItem *pSCharItem = Addr + i;
       if (NULL == pSCharItem)
       {
           continue;
       }
       if (pSCharItem->itembaseinfo.ustItemID == ItemId)
       {
           ItemCount = pSCharItem->itembaseinfo.ustItemCount;
           return true;
       }
   }
   return false;
}

bool CQuestBot::CheckBagItem(short BagType,int ItemId,int &ItemCount) // 检查道具是否存在背包中,ItemCount输出道具的数量
{
   if (ItemId <= 0 )
       return false;
   
   switch(BagType)
   {
   case BT_NormalItemBag:
       return CheckBag(m_pItemBag, ItemId,ItemCount);
   case BT_MaterialBag:
       return CheckBag(m_pMaterialBag,ItemId,ItemCount);
   case BT_TaskBag:
       return CheckBag(m_pTaskItemBag,ItemId,ItemCount);
   default:
       break;
   };

   return false;    
}

bool CQuestBot::LoadMonsetDropItem(const char* FilePath)
{
   if(NULL == FilePath||strlen(FilePath)==0)
       return false;

   TiXmlDocument doc;
   if(!doc.LoadFile(FilePath))
   {
       return false;
   }

   TiXmlElement* pProject = doc.FirstChildElement("Project");
   if (pProject == NULL)
   {
       return false;
   }
   TiXmlElement* pMonsters = pProject->FirstChildElement("Monsters");
   if (pMonsters == NULL)
   {
       return false;
   }
   TiXmlElement* pMonster = pMonsters->FirstChildElement("Monster");
   while (pMonster)
   {
       stDropItem stItem;
       stItem.Clear();

       int MonsterId = 0;
       pMonster->Attribute("Id",&MonsterId);
       stItem.MonsterId = MonsterId;
       TiXmlElement* pDropItem = pMonster->FirstChildElement("DropItem");
       while (pDropItem)
       {
           pDropItem->Attribute( "QuestId" , &stItem.QuestId);   
           pDropItem->Attribute( "ItemId" , &stItem.ItemId);

           DorpItemList.push_back(stItem);
           pDropItem = pDropItem->NextSiblingElement();
       }
       pMonster = pMonster->NextSiblingElement();
   }
   return true;
}

CQuestBot::stDropItem* CQuestBot::FindDropInfoByQuestId(int QuestId)
{
   if (QuestId <= dr_MinQuestId ||QuestId > dr_MaxQuestId)
   {
       return NULL;
   }
   for (DropItemContainer::iterator itr = DorpItemList.begin();itr!=DorpItemList.end();++itr)
   {
       if (itr->QuestId == QuestId)
       {
           return &(*itr);
       }
   }
   return NULL;
}

short CQuestBot::GetRoleVarValue(int index)
{
   if (index < 0 || index >=More_iMaxVars)
   {
       return -1;
   }
   return LocalVars[index];
}

unsigned short CQuestBot::ParseQuestForType( SQuest* quest ) // 解析任务的类型
{
   if(NULL == quest)
       return EDCT_Error;

//     for (std::vector<SQuestRequirement>::iterator FrontItr = quest->stReceiveRequirement.begin();FrontItr!= quest->stReceiveRequirement.end();++FrontItr)
//     {
//         if (FrontItr->byType == SQuest::eRequirement_Quest)
//         {
//             if (!QuestManager::IsQuestDone(GetRoleVarValue(FrontItr->Value)))
//             {
//                 FrontQuestId = FrontItr->Value;
//                 //CurQuestId = FrontQuestId;
//                 return EDCT_NeedQuest;
//             }
//         }
//         else if(FrontItr->byType == SQuest::eRequirement_Var )
//         {
//             if (quest->Id == 3030 || quest->Id == 3098)
//             {
//                 //DoneQuestInface()
//                 //这2个任务需要分析字串，找到对应的NPC去做
//             }
//             if (!QuestManager::IsQuestDone(GetRoleVarValue(FrontItr->wVar)))
//             {
//                 FrontQuestId = FrontItr->wVar;
//                 //CurQuestId = FrontQuestId;
//                 return EDCT_NeedQuest;
//             }
//         }
//     }

   if (quest->Id == 3030 || (quest->Id >= 4001 && quest->Id <= 4010))
   {
       switch (GetSelfProfession())
       {
       case EArmType_Warrior:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(4001)))
               {
                   CurQuestId = 4001;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(4006))) 
               {
                   CurQuestId = 4006;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3030)))
               {
                   CurQuestId = 3030;
               }
           }
           break;
       case EArmType_Mage:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(4002)))
               {
                   CurQuestId = 4002;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(4007))) 
               {
                   CurQuestId = 4007;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3030)))
               {
                   CurQuestId = 3030;
               }
           }
           break;
       case EArmType_Taoist:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(4003)))
               {
                   CurQuestId = 4003;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(4008))) 
               {
                   CurQuestId = 4008;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3030)))
               {
                   CurQuestId = 3030;
               }
           }
           break;
       case EArmType_Assassin:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(4004)))
               {
                   CurQuestId = 4004;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(4009))) 
               {
                   CurQuestId = 4009;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3030)))
               {
                   CurQuestId = 3030;
               }
           }
           break;
       case EArmType_Hunter:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(4005)))
               {
                   CurQuestId = 4005;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(4010))) 
               {
                   CurQuestId = 4010;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3030)))
               {
                   CurQuestId = 3030;
               }
           }
           break;
       default:
           break;
       }
       return EDCT_NoNeed;
   }
   else if (quest->Id >= 3088 && quest->Id <= 3098)
   {
       switch (GetSelfProfession())
       {
       case EArmType_Warrior:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3088)))
               {
                   CurQuestId = 3088;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(3093))) 
               {
                   CurQuestId = 3093;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3098)))
               {
                   CurQuestId = 3098;
               }
           }
           break;
       case EArmType_Mage:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3089)))
               {
                   CurQuestId = 3089;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(3094))) 
               {
                   CurQuestId = 3094;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3098)))
               {
                   CurQuestId = 3098;
               }
           }
           break;
       case EArmType_Taoist:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3090)))
               {
                   CurQuestId = 3090;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(3095))) 
               {
                   CurQuestId = 3095;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3098)))
               {
                   CurQuestId = 3098;
               }
           }
           break;
       case EArmType_Assassin:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3091)))
               {
                   CurQuestId = 3091;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(3096))) 
               {
                   CurQuestId = 3096;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3098)))
               {
                   CurQuestId = 3098;
               }
           }
           break;
       case EArmType_Hunter:
           {
               if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3092)))
               {
                   CurQuestId = 3092;
               }
               else if(QuestManager::Instance().IsQuestActive(GetRoleVarValue(3097))) 
               {
                   CurQuestId = 3097;
               }
               else if (QuestManager::Instance().IsQuestActive(GetRoleVarValue(3098)))
               {
                   CurQuestId = 3098;
               }
           }
           break;
       default:
           break;
       }
       return EDCT_NoNeed;
   }


   if (quest->stCommitRequirement.empty())
   {
       TotalDoneQuestCondition = 0;
       NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(quest->ReplyTargetId);
       m_xTargetNpcPoint.nMapId = pNpc->mapId;
       m_xTargetNpcPoint.nNpcId = quest->ReplyTargetId;
       m_xTargetNpcPoint.nQuestId = quest->Id;
       m_xTargetNpcPoint.x = pNpc->x;
       m_xTargetNpcPoint.y = pNpc->y;
       return EDCT_NoNeed;
   }
   bMoveToMonster = false;
   TotalDoneQuestCondition = quest->stCommitRequirement.size();// 记录当前任务的总数
   m_xTargetNpcPoint.nQuestId = quest->Id;

   int i = 0;
   for (std::vector<SQuestRequirement>::iterator itr = quest->stCommitRequirement.begin();itr!= quest->stCommitRequirement.end();++itr,++i)
   {
       if (i != CurDoneQuestCondition)
       {
           continue;
       }

       switch (itr->byType)
       {
       case SQuest::eRequirement_Profession:
           ++CurDoneQuestCondition;
           break;
           //return EDCT_NoNeed;
       case SQuest::eRequirement_Action:
           {
               NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(quest->TargetStringId);
               
               m_xTargetNpcPoint.x = pNpc->x;
               m_xTargetNpcPoint.y = pNpc->y;
           }
           return EDCT_Action;
       case SQuest::eRequirement_Monster: // 需要杀怪
           {
               int MapId = -1;
               SMapMonsterInfo* pSMapMonsterInfo = theApp.GetMonsterInfo(itr->Value,MapId);
               if (NULL != pSMapMonsterInfo)
               {
                   m_xTargetNpcPoint.nMapId = MapId;
                   m_xTargetNpcPoint.x = TileToFloat(pSMapMonsterInfo->m_nX);
                   m_xTargetNpcPoint.y = TileToFloat(pSMapMonsterInfo->m_nY);
                   TargetSMapMonsterInfo = pSMapMonsterInfo;
               }
               m_xTargetNpcPoint.nNpcId = itr->Value;
               KillIndex = itr->wVar;
               MaxKillNum = itr->MaxNum;
           }
           NeedKillMonster = true;
           return EDCT_KillMonster;
       case SQuest::eRequirement_Item:    // 需要道具
           // 需要分析一下到底是只要道具还是要杀怪拿道具
           {
               stDropItem* pDrop = FindDropInfoByQuestId(quest->Id);
               if (itr->wVar == 65535 &&  pDrop == NULL) 
               {
                   // 需要找NPC拿
                   //++CurDoneQuestCondition;
                   int count = 0;
                   if (IsNormalBagFull())
                   {
                       ClearNormalBagItem();
                       return EDCT_NeedItem;
                   }
                   bool bFind = false;
                   bFind = CheckBagItem(BT_TaskBag,itr->Value,count);
                   if (!bFind)
                   {
                       bFind = CheckBagItem(BT_NormalItemBag,itr->Value,count);
                   }
                   if (bFind)
                   {
                       if (count < itr->MaxNum)
                       {
                           bFind = false;
                       }
                   }
                   NeedItemId = itr->Value;
                   MaxKillNum = itr->MaxNum;
                   if (HQ_TimeGetTime() - ReqItemTime >= 10 * Space_Time 
                       && !bFind)
                   {
                       char GetItemBuf[255];
                       sprintf_s(GetItemBuf,sizeof(GetItemBuf),"/CreateItem %d %d 0",itr->Value,itr->MaxNum);
                       MsgChat Chat(MsgChat::CHAT_TYPE_NORMAL);
                       Chat.SetString(GetItemBuf);
                       SendMsg(&Chat);
                       ReqItemTime = HQ_TimeGetTime();
                   }
                   return EDCT_NeedItem;
               }
               else
               {
                   int MapId = -1;
                   SMapMonsterInfo* pSMapMonsterInfo = theApp.GetMonsterInfo(pDrop->MonsterId, MapId );
                   if (NULL != pSMapMonsterInfo)
                   {
                       m_xTargetNpcPoint.nMapId = MapId;
                       m_xTargetNpcPoint.x = pSMapMonsterInfo->m_nX;
                       m_xTargetNpcPoint.y = pSMapMonsterInfo->m_nY;
                       TargetSMapMonsterInfo = pSMapMonsterInfo;
                   }
                   m_xTargetNpcPoint.nNpcId = pDrop->MonsterId;
                   NeedItemId = itr->Value;
                   MaxKillNum = itr->MaxNum;
                   // 杀怪拿道具
                   return EDCT_KillMonsterItem;
               }
           }
           break;
       case SQuest::eRequirement_Sex:
           ++CurDoneQuestCondition;
           break;
       case SQuest::eRequirement_Var:
           {
               DoneQuestInface(quest->Id);
           }
           return EDCT_NeedVar;
       default:
           return EDCT_Error;
       }
   }
   return EDCT_Error;
}

void CQuestBot::DoneQuestInface(int QuestId)
{
	return ;
   MsgChat ChatMsg( MsgChat::CHAT_TYPE_NORMAL );
   strncpy( ChatMsg.chatHeader.szToName, GetBotRoleName() , MAX_NAME_STRING - 1 );

   char szMsg[dr_MaxChatString] = {0};
   std::string command = ROBOT_REQUEST_COMMAND;
   command += "SetQuestState %d %d";
   //std::string command = "/SetQuestState %d %d";
//   _snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), QuestId, QuestManager::Instance().eQuestCasterState);
   ChatMsg.SetString(szMsg);
   SendMsg(&ChatMsg);
}

//做任务，TRUE表示昨完了
bool CQuestBot::DoQuest(unsigned short usQuestType)
{
   if (usQuestType <= EDCT_Error|| usQuestType > EDCT_NeedQuest)
   {
       return true;
   }

   switch (usQuestType)
   {
   case EDCT_Error:
       // 这个任务不能做，通过接口调用任务完成
       DoneQuestInface(CurQuestId);
       return true;
   case EDCT_Action:
       //护送任务 直接去 交任务的NPC哪里
       {
           D3DXVECTOR3 Pos;
           Pos.x = m_xTargetNpcPoint.x;
           Pos.y = m_xTargetNpcPoint.y;
           if (!MoveToPoint(Pos))
               return false;

           return true;
       }
   case EDCT_NeedItem:
       {
           int Count = 0 ;
           bool bFind = CheckBagItem(BT_NormalItemBag,NeedItemId,Count);
           if (!bFind)
           {
               bFind = CheckBagItem(BT_MaterialBag,NeedItemId,Count);
           }

           if (!bFind)
           {
               bFind = CheckBagItem(BT_TaskBag,NeedItemId,Count);
           }
           if (bFind && Count < MaxKillNum)
           {
               bFind = false;
           }

           if (bFind)
           {
               return true;
           }
           return false;
       }
   case EDCT_NeedVar:
       {
           return true;
       }
   case EDCT_NoNeed:          // 移动到完成任务的Npc哪里
       {
           if (GetMapID() != m_xTargetNpcPoint.nMapId)
           {
               FlyToMap(m_xTargetNpcPoint.nMapId,m_xTargetNpcPoint.x,m_xTargetNpcPoint.y);
               return false;
           }

           return true;
       }
   case EDCT_KillMonster:     // 杀一定数量的怪物
       {
           NeedKillMonster = true;
           if (CheckKillVar())
           {
               NeedKillMonster = false;
               m_xTargetNpcPoint.nNpcId = GetRunQuest()->ReplyTargetId;
               return true;
           }
           PlayerInfo* Target = NULL;
           for (PlayerInfoContainer::iterator itr = m_listMonsterList.begin();itr != m_listMonsterList.end();++itr)
           {
               if (itr->dwCharacterID == m_xTargetNpcPoint.nNpcId)
               {
                   Target = &(*itr);
                   break;
               }
           }

           if (NULL != Target && MoveToPoint(Target->m_vPos))
           {
               m_shTargetID = Target->shPlayerID;
               MsgLockTarget msg;
               msg.stWho = m_shTargetID;
               SendMsg(&msg);

               m_dwLockTargetTime = HQ_TimeGetTime();
               PlayAttack();
           }
           else
           {
               if (GetMapID() != m_xTargetNpcPoint.nMapId && m_xTargetNpcPoint.nMapId != -1)
               {
                   FlyToMap(m_xTargetNpcPoint.nMapId,m_xTargetNpcPoint.x,m_xTargetNpcPoint.y);
                   SetSleep(2000);
                   return false;
               }
               D3DXVECTOR3 xPos;
               xPos.x = m_xTargetNpcPoint.x;
               xPos.y = m_xTargetNpcPoint.y;
               xPos.z = 0;
               MoveToPoint(xPos);
           }

           return false;
       }
   case EDCT_KillMonsterItem:
       {
           NeedKillMonster = true;
           int Count = 0;
           bool bFind = false;
           bFind = CheckBagItem(BT_NormalItemBag,NeedItemId,Count);
           if (!bFind)
           {
               bFind = CheckBagItem(BT_TaskBag,NeedItemId,Count);
           }
           if (!bFind)
           {
               bFind = CheckBagItem(BT_MaterialBag,NeedItemId,Count);
           }

           if (bFind && Count == MaxKillNum)
           {
               NeedKillMonster = false;
               return true;
           }
           
           PlayerInfo* Target = NULL;
           for (PlayerInfoContainer::iterator itr = m_listMonsterList.begin();itr != m_listMonsterList.end();++itr)
           {
               if (itr->dwCharacterID == m_xTargetNpcPoint.nNpcId)
               {
                   Target = &(*itr);
                   break;
               }
           }
           // 不足够
           if (Target == NULL)
           {
               D3DXVECTOR3 xPos;
               xPos.x = m_xTargetNpcPoint.x;
               xPos.y = m_xTargetNpcPoint.y;
               xPos.z = 0;
               MoveToPoint(xPos);
               return false;
           }

           if (NULL != Target && MoveToPoint(Target->m_vPos))
           {
               m_shTargetID = Target->shPlayerID;
               MsgLockTarget msg;
               msg.stWho = m_shTargetID;
               SendMsg(&msg);
               m_dwLockTargetTime = HQ_TimeGetTime();
               PlayAttack();
           }
           return false;
       }
   case EDCT_NeedQuest:
       m_xTargetNpcPoint.nMapId = -1;
       return false;
   default:
       DoneQuestInface(CurQuestId);
       return true;
   }
   return true;
}

bool CQuestBot::CheckKillVar()
{
   if (KillIndex<-1||KillIndex > More_iMaxVars)
   {
       return false;
   }
   if(GetRoleVarValue(KillIndex) == MaxKillNum)
   {
       NeedKillMonster = false;
       m_xTargetNpcPoint.nMapId = -1;
       m_xTargetNpcPoint.nNpcId = -1;
       return true;
   }
   return false;
}


void CQuestBot::OnMsg_UnPlayerEnterSight(Msg* pMsg)
{
   BaseRobot::OnMsg_UnPlayerEnterSight(pMsg);
   MsgNPCEnterMySight *pSightNpc = (MsgNPCEnterMySight*)pMsg;
   if (pSightNpc->stCharType != Object_MonsterBuilding || pSightNpc->stCharType == Object_Dump)
   {
       //请求NpcInfo
       BaseRobot::OnMsg_PlayerEnterSight(pMsg);
   }
}

void CQuestBot::OnMsgChangeMap(Msg* pMsg)
{
   BaseRobot::OnMsgChangeMap(pMsg);
   CurRunQuest.clear();
   MsgChangeMap *pChangeMsg = (MsgChangeMap*)pMsg;
   GetNpcByMap(pChangeMsg->dwMapId);
}

SQuest* CQuestBot::GetRunQuest(int id )
{
   if ((id < 0 && id > More_iMaxVars) || QuestManager::Instance().IsQuestDone(GetRoleVarValue(id)))
   {
       id = -1;
   }
   // 选择当前地图里面的可以做的任务
   if (id != -1)
   {
       for (QuestList::iterator itr = CurRunQuest.begin();itr != CurRunQuest.end();++itr)
       {
           if ((*itr)->Id == id)
           {
               return *itr;
           }
       }
   }

   GetUnActiveQustDone(GetMapID());
   if (CurRunQuest.empty())
   {
       if ( NoQuestTime == 0 )
       {
           NoQuestTime = HQ_TimeGetTime();
       }
       return NULL;
   }
   
   for (QuestList::iterator itr = CurRunQuest.begin();itr != CurRunQuest.end();)
   {
       SQuest* quest = *itr;
       if ( theQuestManager.IsQuestDone( GetRoleVarValue(quest->Id) ) )
       {
           itr = CurRunQuest.erase(itr);
           m_nNpcId = -1;
           continue;
       }
       else if (theQuestManager.IsQuestActive(GetRoleVarValue(quest->Id)))
       {
           //m_eQuestState = Quest_Refer;
           return *itr;
       }
//        else if (QuestManager::Instance().IsQuestCast( GetRoleVarValue(quest->Id) ))
//        {
//            return *itr;
//        }
       ++itr;
   }
   return NULL;
}

void CQuestBot::SetMoveNpcPoint()
{
//    CheckQuest();
//    SQuest *pQuest = NULL;
//    if (FrontQuestId != -1)
//    {
//        pQuest = GetRunQuest(FrontQuestId);
//    }
//    else
//    {
// 	    pQuest = GetRunQuest(CurQuestId);
//    }
// 	if (pQuest == NULL)
// 	{
//        if ( HQ_TimeGetTime() - NoQuestTime >= 60*1000)//60秒没有任务就随机飞到别的地图
//        {
//            if (vecMap.empty())
//            {
//                vecMap.push_back(1);
//                vecMap.push_back(2);
//                vecMap.push_back(3);
//                vecMap.push_back(10);
//                vecMap.push_back(11);
//            }
// 
//            //LoadRandFlyMap();
//            if (bFirst)
//            {
//                bFirst = false;
//                NoQuestTime = HQ_TimeGetTime();
//                return;
//            }
//            RandFly();
//            NoQuestTime = 0;
//        }
//        m_nNpcId = -1;
// 		return;
// 	}
// 
// 
// #define EMPTYNPCID (0)
//    NpcInfo::Npc *pPosition = NULL;
//    if (CurQuestId == -1)
//    {
//        CurQuestId = pQuest->Id;
//    }
//    //CurQuestId = pQuest->Id;
//    if (theQuestManager.IsQuestCast(GetRoleVarValue(CurQuestId)))
//    {
//        if (pQuest->AcceptTargetId == EMPTYNPCID)
//        {
//            EreaseQuest(pQuest->Id);
//            return;
//        }
//        pPosition = theNpcInfo.GetNpcByStaticId(pQuest->AcceptTargetId);
//        /*m_eQuestState = Quest_Refer;*/
//        m_xTargetNpcPoint.nNpcId = pQuest->AcceptTargetId;
//    }
//    else
//    {//获得交任务的具体地点
//        if (pQuest->ReplyTargetId == EMPTYNPCID)
//        {
//            EreaseQuest(pQuest->Id);
//            return;
//        }
//        pPosition = theNpcInfo.GetNpcByStaticId(pQuest->ReplyTargetId);
//        //m_eQuestState = Quest_NotActive;
//        m_xTargetNpcPoint.nNpcId = pQuest->ReplyTargetId;
//    }
// 
// //     if (m_xTargetNpcPoint.nQuestId == pQuest->Id)
// //         return;
// 	if (pPosition == NULL)
// 	{
// 		return;
// 	}
// 
// 	//m_xTargetNpcPoint.nNpcId = pPosition->id;
// 	m_xTargetNpcPoint.nQuestId = CurQuestId;
// 	m_xTargetNpcPoint.nMapId = pPosition->mapId;
// 	m_xTargetNpcPoint.x = pPosition->x;
// 	m_xTargetNpcPoint.y = pPosition->y;
}

bool CQuestBot::EreaseQuest(int QuestId)
{
   if (QuestId<=0)
       return true;
   for (QuestList::iterator itr = CurRunQuest.begin();itr != CurRunQuest.end();++itr )
   {
       if ((*itr)->Id == QuestId)
       {
           CurRunQuest.erase(itr);
           return true;
       }
   }
   return false;
}

bool CQuestBot::MoveToNpcPoint()
{
	if (m_xTargetNpcPoint.Empty() || m_bRunQuestStart)
	{
       SetMoveNpcPoint();
		//return true;
	}

	if (HQ_TimeGetTime() - MoveTime <= Space_Time)
	{
		return false;
	}
   MoveTime = HQ_TimeGetTime();

	if (GetMapID() != m_xTargetNpcPoint.nMapId)
	{
		m_dwNextRunTime = HQ_TimeGetTime() + 1 * Space_Time;
		return false;
	}

	D3DXVECTOR3 xPos;
	xPos.x = m_xTargetNpcPoint.x;
	xPos.y = m_xTargetNpcPoint.y;
	xPos.z = 0;
   
	//return (m_bRunQuestStart = MoveToPoint(xPos));
   return MoveToPoint(xPos);
}

void CQuestBot::OnMsg_AllNpcInTheMap(Msg* pMsg)
{
	MsgAllNpcOnTheMap* NpcMapInfo = (MsgAllNpcOnTheMap*)pMsg;
	for (int i = 0;i < NpcMapInfo->wNpcCount;++i)
	{
		if (NpcMapInfo->wNpcCount > MsgAllNpcOnTheMap::eMaxNpc)
		{
			break;
		}
		NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByName(NpcMapInfo->infos[i].szName);

		if (pNpc != NULL)
		{
			pNpc->dynamicId = NpcMapInfo->infos[i].stNpcId;
		}		
	}
}

void CQuestBot::OnMsg_TellMap_NpcQuest(Msg* pMsg)
{
// 	MsgTellMapNpcQuest* pQuestMsg = (MsgTellMapNpcQuest*)pMsg;
// 
// 	// 只要找到自己要接的任务状态就可以了
// 	for(int i = 0; i < pQuestMsg->byQuestCount; ++i)
// 	{
// 		NpcInfo::Npc* pNpc = theNpcInfo.FindNpcByDynamicId(pQuestMsg->infos[i].stNpcId);
// 		if (pNpc != NULL)
// 		{
// 			if (pNpc->id == m_xTargetNpcPoint.nNpcId && pQuestMsg->infos[i].stQuestId == m_xTargetNpcPoint.nQuestId)
// 			{				
// 				if (theQuestManager.IsQuestCast(pQuestMsg->infos[i].chState))
// 				{
// 					m_eQuestState = Quest_NotActive;
// 				}
// 				else if (theQuestManager.IsQuestActive(pQuestMsg->infos[i].chState))
// 				{
// 					m_eQuestState = Quest_CasterState;
// 				}
// 				else if (theQuestManager.IsQuestDone(pQuestMsg->infos[i].chState))
// 				{
// 					m_eQuestState = Quest_Done;
// 				}
// 									
// 				break;
// 			}				
// 		}
// 	}
}

void CQuestBot::LoadAllRoleVars(MsgTellCharVar * pVar)
{
   if (NULL == pVar )
       return;

   for(int i = 0; i < pVar->varCount; ++i)
   {
  //     if (pVar->charVars[i].byAction == MsgTellCharVar::eStateChange)
       {
           LocalVars[pVar->charVars[i].varId] = pVar->charVars[i].varValue;
           //if (LocalVars[pVar->states[i].stQuestId] == QuestManager::)
       }
   }
}
//收到状态改变
void CQuestBot::OnMsg_TellCharVar(Msg* pMsg)
{
	MsgTellCharVar* pCharVar = (MsgTellCharVar*)pMsg;

   LoadAllRoleVars(pCharVar);
}

//收到显示任务对话框的消息， 就直接选择任务
void CQuestBot::OnMsg_ScriptReqShowQuestDlg(Msg* pMsg)
{
   MsgScriptReqShowQuestDlg* pReqMsg = (MsgScriptReqShowQuestDlg*)pMsg;
//     if (IsSendRecvQuest)
//     {
       MsgScriptAckShowQuestDlg xMsg;
       xMsg.stQuestId = CurQuestId;//(*CurRunQuest.begin())->Id;
       SendMsg(&xMsg);
       IsSendRecvQuest = false;
//     }
//     else
//     {
       //收到新的任务，应该优先处理
       //MsgScriptReqShowQuestDlg* pReqMsg = (MsgScriptReqShowQuestDlg*)pMsg;
       OutputDebugStringA(pReqMsg->szInfo);
//    }	
}

void CQuestBot::OnMsg_Ack_Script(Msg* pMsg)
{
	MsgAckScript* pAck = (MsgAckScript*)pMsg;

	if (pAck->byType == MsgAckScript::eNpcDialog)
	{
		switch(pAck->dlgType)
		{
		case MsgAckScript::eNDT_AcceptTask:		
			m_eQuestState = Quest_Refer;
           CurQuestId = pAck->iValue;
			//继续执行
		case MsgAckScript::eNDT_FinishTask:
			{
				MsgReqScript MsgScript;
				MsgScript.stNpcId = m_nNpcId;
				SendMsg(&MsgScript);
			}
			break;

		case MsgAckScript::eNDT_Close:
			{
// 				MsgScriptEnd xMsgEnd;
// 
// 				xMsgEnd.type = ST_NPC;
// 
// 				SendMsg(&xMsgEnd);
			}
			break;
       case MsgAckScript::eNDT_Description:
           {
               MsgScriptAckShowQuestDlg ShowQuestDlg;
               ShowQuestDlg.stQuestId = CurQuestId;//(*CurRunQuest.begin())->Id;
               SendMsg(&ShowQuestDlg);
           }
           break;
		default:
			break;
		}
	}
   else if(pAck->byType == MsgAckScript::eAskQuestion)
   {
       switch(pAck->dlgType)
       {
       case MsgAckScript::eNDT_AcceptTask:		
           m_eQuestState = Quest_Refer;
           //继续执行
           CurQuestId = pAck->iValue;
           //break;
       case MsgAckScript::eNDT_FinishTask:
           {
               MsgReqScript MsgScript;
               MsgScript.stNpcId = m_nNpcId;
               SendMsg(&MsgScript);
           }
           break;

       case MsgAckScript::eNDT_Close:
           {
//                 MsgScriptEnd xMsgEnd;
// 
//                 xMsgEnd.type = ST_NPC;
// 
//                 SendMsg(&xMsgEnd);
           }
           break;
       case MsgAckScript::eNDT_Description:
           {
               MsgReqScript MsgScript;
               MsgScript.stNpcId = GetNpcById();
               if (CurQuestId == MountQuestId)
               {
                   //DoneQuestInface(MountQuestId);//这个任务直接完成,不知道马匹怎么移动的
                   MsgScriptAckShowQuestDlg ShowQuestDlg;
                   ShowQuestDlg.stQuestId = MountQuestId;
                   SendMsg(&ShowQuestDlg);
                   //bAutoRun = true;
                   //AutoRunTime = HQ_TimeGetTime();
                   break;
               }
               else
               {
                   int Select = TokenString(pAck->szString);
                   MsgScript.chSelItem = rand()%Select;
               }
               SendMsg(&MsgScript);
           }
           break;
       }
   }
}

int CQuestBot::TokenString(const std::string SplitString)
{
   int result = 0;
   for (int i = 0;i < SplitString.size();++i)
   {
       if (SplitString[i] == ' ')
       {
           ++result;
       }
   }
   return result;
}