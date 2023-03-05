#include "DropQuestItem.h"
#include <string>
#include "RapidXml/MeRapidXml.h"
#include "Log4cpp/log4cpp_logger.h"



#define TEAM_TASK_VAR_DIST 60.0f

DropTaskItem::DropTaskItem()
{
}

DropTaskItem::~DropTaskItem()
{
}

bool DropTaskItem::Init()
{
//     bool bResult = LoadData();
//     if ( !bResult)
//         return false;

    return true;
}


// bool DropTaskItem::LoadData(const char* szFileName)
// {
//     m_vtDropItem.clear();
//     m_vtDropCount.clear();
// 
//     CSlkReader reader;
//     int iRet = 0;
//     int iRow = 0;
// 
//     //char* szFileName = TASKDROPITEM_FILEPATH;
// 
//     std::string FilePath = szFileName;
//     if( !reader.ReadFromFile( FilePath.c_str() )
//         return false;
// 
//     STaskDrop stItem;
// 
//     iRow = 3;
//     while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
//     {
//         if( CSlkReader::ret_nothisline == iRet )
//             continue;
// 
//         int nMonsterId         = -1;
//         int nTaskId            = -1;
//         int nTaskState         = -1;
//         int nItemId            = -1;
//         int nProbability       = 0;
//         int nMaxItemCount      = 0;
//         int nTaskVarId         = -1;
//         int nTaskMaxVar        = 0;
//         std::string strVarName = "";
// 
//         bool bNewMonster = true;
//         if( !reader.GetIntFieldByName( "MonsterId", nMonsterId ) )
//         {
//             bNewMonster = false;
//         }
//         if( !reader.GetIntFieldByName( "TaskId", nTaskId ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskId]  read failed", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "ItemId", nItemId ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [ItemId]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "Probability", nProbability ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [Probability]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "MaxItemCount", nMaxItemCount ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [MaxItemCount]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskVarId", nTaskVarId ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskVarId]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskState", nTaskState ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskState]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskMaxVar", nTaskMaxVar ) )
//         {
//             //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskMaxVar]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
// 
//         if ( nTaskVarId != -1 )
//         {
//             if( !reader.GetStringFieldByName( "TaskVarName", strVarName ) )
//             {
//                 //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskVarName]  read failed \n", szFileName, iRow-1 );
//                 continue;
//             }
//         }
// 
//         if ( bNewMonster == true )
//         {
//             if ( stItem.vtTask.size() > 0 )
//             {
//                 m_vtDropItem.push_back( stItem );
//                 stItem.vtTask.clear();
//             }
//             stItem.nMonster = nMonsterId;
//             stItem.vtTask.clear();
//         }
// 
//         STask stTask;
//         stTask.nTaskId             = nTaskId;
//         stTask.stItem.nItemId      = nItemId;
//         stTask.stItem.nProbability = nProbability;
//         stTask.nMaxItemCount       = nMaxItemCount;
//         stTask.nVarId              = nTaskVarId;
//         stTask.nTaskState          = nTaskState;
//         stTask.nMaxVar             = nTaskMaxVar;
//         stTask.strVarName          = strVarName;
//         stItem.vtTask.push_back( stTask );
// 
//         if ( nItemId != -1 && nProbability != 0 )
//         {
//             SDropCount stDrop;
//             stDrop.nItemId       = nItemId;
//             stDrop.nMaxItemCount = nMaxItemCount;
//             AddDropCount( stDrop );
//         }
//     }
// 
//     if ( stItem.vtTask.size() > 0 )
//     {
//         m_vtDropItem.push_back( stItem );
//     }
//     return true;
//}

bool DropTaskItem::LoadXmlData(const char* FileName)
{
    if (!FileName||strlen(FileName) == 0)
    {
        return false;
    }
    std::string filePath = FileName;

	m_vtDropItem.clear();

    MeXmlDocument doc;
    if(!doc.LoadFile(filePath.c_str()))
    {
        return false;
    }

    MeXmlElement* pProject = doc.FirstChildElement("Project");
    if (pProject == NULL)
    {
        return false;
    }
    MeXmlElement* pMonsters = pProject->FirstChildElement("Monsters");
    if (pMonsters == NULL)
    {
        return false;
    }
    MeXmlElement* pMonster = pMonsters->FirstChildElement("Monster");
    while (pMonster)
    {
        STask stTask;
        int MonsterId = 0;
        pMonster->Attribute("Id",&MonsterId);
        MeXmlElement* pDropItem = pMonster->FirstChildElement("DropItem");
        while (pDropItem)
        {
            pDropItem->Attribute( "Id" , &stTask.nVarId  );
            pDropItem->Attribute( "QuestId" , &stTask.nTaskId);
            pDropItem->Attribute( "ItemId" , &stTask.stItem.nItemId);
            pDropItem->Attribute( "DropRate" , &stTask.stItem.nProbability);
            pDropItem->Attribute( "DropItemCount" , &stTask.nMaxItemCount);
            pDropItem->Attribute( "MonsterKillCount" , &stTask.nMaxVar);
            stTask.nTaskState = 1;

            if ( MonsterId != 0 )
            {
                DropItemType::iterator finditr = m_vtDropItem.find(MonsterId);
                if (finditr != m_vtDropItem.end())
                {
                    finditr->second.push_back(stTask);
                    //m_vtDropItem.insert(DropItemType::value_type(MonsterId,stTask));
                }
                else
                {
                    STaskVector vec;
                    vec.push_back(stTask);
                    m_vtDropItem.insert(DropItemType::value_type(MonsterId,vec));
                }
            }

            if ( stTask.stItem.nItemId != -1 && stTask.stItem.nProbability != 0 )
            {
                SDropCount stDrop;
                stDrop.nItemId       = stTask.stItem.nItemId;
                stDrop.nMaxItemCount = stTask.nMaxItemCount;
                AddDropCount( stDrop );
            }
            pDropItem = pDropItem->NextSiblingElement();
        }
        pMonster = pMonster->NextSiblingElement();
    }
    return true;
}



bool DropTaskItem::AddDropCount( const SDropCount& stItem )
{
    bool bFind = false;
    for ( unsigned int n=0; n<m_vtDropCount.size(); ++n )
    {
        SDropCount* pDrop = &m_vtDropCount[n];
        if ( !pDrop)
            continue;

        if ( pDrop->nItemId == stItem.nItemId )
        {
            bFind = true;
            if ( pDrop->nMaxItemCount != stItem.nMaxItemCount )
            {
               // LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"MonsterDropItem.config中发现需求数不同但相同ID的任务物品[%d] \n", pDrop->nItemId );
                return false;
            }
            break;
        }
    }

    if ( bFind == false )
    {
        m_vtDropCount.insert( DropCountType::value_type(stItem.nItemId,stItem) );       
    }
    return bFind;
}

//
#ifdef __QUEST_EDIT__
bool DropTaskItem::SaveXmlData(const char* FileName)
{
    if (!FileName||strlen(FileName) == 0)
    {
        return false;
    }
    std::string filePath = FileName;
    MeXmlDocument doc;

    doc.InsertEndChild( MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = doc.InsertEndChild("Project")->ToElement();
    pRoot->SetAttribute("Name","HeroOnline");
    MeXmlElement* Monsters = pRoot->InsertEndChild("Monsters")->ToElement();

    for(DropItemType::iterator itrDropitem = m_vtDropItem.begin();itrDropitem != m_vtDropItem.end();++itrDropitem)
    {
        MeXmlElement* pMonster = Monsters->InsertEndChild("Monster")->ToElement();
        pMonster->SetAttribute("Id",itrDropitem->first);

        for(STaskVector::iterator result = itrDropitem->second.begin();result != itrDropitem->second.end();++result)
        {
            if ( result->nTaskId == -1 )
            {
                continue;
            }

            MeXmlElement* pDropItem = pMonster->InsertEndChild("DropItem")->ToElement();
            pDropItem->SetAttribute( "QuestId",result->nTaskId );
            pDropItem->SetAttribute( "ItemId",result->stItem.nItemId  );
            pDropItem->SetAttribute( "Id",result->nVarId );
            pDropItem->SetAttribute( "DropRate",result->stItem.nProbability );
            pDropItem->SetAttribute( "DropItemCount",result->nMaxItemCount );
            pDropItem->SetAttribute( "MonsterKillCount",result->nMaxVar );

        }
    }

    return doc.SaveFile(filePath.c_str());
}

bool        DropTaskItem::AddQuest(int MonsterId ,STask &stask, bool bDropCount /* = true*/)
{
    //stask.nTaskState = 1;
    bool result = true;
    if ( stask.stItem.nItemId != -1 && stask.stItem.nProbability != 0  && bDropCount)
    {
        SDropCount stDrop;
        stDrop.nItemId       = stask.stItem.nItemId;
        stDrop.nMaxItemCount = stask.nMaxItemCount;
        result = AddDropCount( stDrop );
    }
    if (result)
    {
        if ( MonsterId != 0 )
        {
            DropItemType::iterator finditr = m_vtDropItem.find(MonsterId);
            if (finditr != m_vtDropItem.end())
            {
                bool canadd = true;
                for (STaskVector::iterator addit = finditr->second.begin();addit != finditr->second.end();++addit)
                {
                    if (stask.nTaskId == addit->nTaskId && stask.stItem.nItemId == addit->stItem.nItemId)
                    {
                        canadd = false;
                        addit->nMaxItemCount       = stask.nMaxItemCount;
                        addit->nMaxVar             = stask.nMaxVar;
                        addit->nTaskState          = stask.nTaskState;
                        addit->nVarId              = stask.nVarId;
                        addit->stItem.nItemId      = stask.stItem.nItemId;
                        addit->stItem.nProbability = stask.stItem.nProbability;

						break;
                    }
                }
                if (canadd)
                {
                    finditr->second.push_back(stask);
                }
            }
            else
            {
                STaskVector vec;
                vec.push_back(stask);
                m_vtDropItem.insert(DropItemType::value_type(MonsterId,vec));
            }
        }
    }

    return result;
}

bool DropTaskItem::SubQuest(int Monster,int QuestId,int itemid)
{
    DropItemType::iterator result = m_vtDropItem.end();
	if (Monster > 0)
	{
		result = m_vtDropItem.find(Monster);
	}
	else
		result = m_vtDropItem.begin(/*Monster*/);
	
	if (result == m_vtDropItem.end())
	{
		return false;
	}

    bool bFind = false;
	if (Monster > 0)
	{
		for (STaskVector::iterator itrResult = result->second.begin();itrResult != result->second.end();++itrResult)
		{
			if (itrResult->nTaskId == QuestId)
			{
				bFind = true;
				for(DropCountType::iterator itr = m_vtDropCount.begin();itr != m_vtDropCount.end();)
				{
					if (itr->second.nItemId == itrResult->stItem.nItemId)
					{
						itrResult->stItem.nItemId = -1;
					}
					++itr;
				}
				itrResult->Drop();

				break;
			}
		}
	}
	else
	{
		for (;result != m_vtDropItem.end() ;++result)
		{
			for (STaskVector::iterator itrResult = result->second.begin();itrResult != result->second.end();++itrResult)
			{
				if (itrResult->nTaskId == QuestId)
				{
					bFind = true;
					for(DropCountType::iterator itr = m_vtDropCount.begin();itr != m_vtDropCount.end();)
					{
						if (/*itr->second.nItemId*/itemid == itrResult->stItem.nItemId)
						{
							itrResult->stItem.nItemId = -1;
						}
						++itr;
					}
					itrResult->Drop();

					break;
				}
			}
		}
	}	
    return bFind;
}
bool        DropTaskItem::CoalitionTable(DropTaskItem* item)
{
    if (item == NULL)
    {
        return false;
    }
    bool CoalitionResult = true;
    for (DropItemType::iterator itr = item->m_vtDropItem.begin();itr!=item->m_vtDropItem.end();++itr)
    {
        for (STaskVector::iterator result = itr->second.begin();result!=itr->second.end();++result)
        {
            if (!AddQuest(itr->first,*result))
            {
                //LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"MonsterDropItem.config合并文件出错，QuestId = [%d] \n", result->nTaskId );
                CoalitionResult = false;
            }
        }
    }

    return CoalitionResult;
}

int         DropTaskItem::FindDropItemByVarId(int Varid,STask &sTask)
{
    if (Varid < 0 ||Varid > 2999)
    {
        return -1;
    }
    for (DropItemType::iterator itrDrop = m_vtDropItem.begin();itrDrop!=m_vtDropItem.end();++itrDrop)
    {
        for (STaskVector::iterator itr = itrDrop->second.begin();itr != itrDrop->second.end();++itr)
        {
            if (itr->nVarId == Varid )
            {
                sTask.nMaxItemCount = itr->nMaxItemCount;
                sTask.nMaxVar = itr->nMaxVar;
                sTask.nTaskId = itr->nTaskId;
                sTask.nTaskState = itr->nTaskState;
                sTask.nVarId = itr->nVarId;
                sTask.stItem.nItemId = itr->stItem.nItemId;
                sTask.stItem.nProbability = itr->stItem.nProbability;
                return itrDrop->first;
            }
        }
    }
    return -1;
}

int         DropTaskItem::FindDropItemByMonsterId(int MonsterId,int Questid,STask &sTask)
{
    if (Questid<3000||Questid>5999)
    {
        return -1;
    }
    DropItemType::iterator find = m_vtDropItem.find(MonsterId);
    if (find==m_vtDropItem.end())
    {
        return -1;
    }
    for(STaskVector::iterator result = find->second.begin();result!=find->second.end();++result)
    {
        if(result->nTaskId == Questid)
        {
            sTask.nMaxItemCount = result->nMaxItemCount;
            sTask.nMaxVar = result->nMaxVar;
            sTask.nTaskId = result->nTaskId;
            sTask.nTaskState = result->nTaskState;
            sTask.nVarId = result->nVarId;
            sTask.stItem.nItemId = result->stItem.nItemId;
            sTask.stItem.nProbability = result->stItem.nProbability;
            return find->first;
        }
    }
    return -1;
}

int DropTaskItem::FindDropItemByItemId(int ItemId, int QuestId, STask &task)
{
	if (QuestId<3000||QuestId>5999)
	{
		return -1;
	}

	for (DropItemType::iterator itrDrop = m_vtDropItem.begin();itrDrop!=m_vtDropItem.end();++itrDrop)
	{
		for (STaskVector::iterator itr = itrDrop->second.begin();itr != itrDrop->second.end();++itr)
		{
			if (itr->nTaskId == QuestId && itr->stItem.nItemId == ItemId)
			{
				task.nMaxItemCount = itr->nMaxItemCount;
				task.nMaxVar = itr->nMaxVar;
				task.nTaskId = itr->nTaskId;
				task.nTaskState = itr->nTaskState;
				task.nVarId = itr->nVarId;
				task.stItem.nItemId = itr->stItem.nItemId;
				task.stItem.nProbability = itr->stItem.nProbability;
				return itrDrop->first;
			}
		}
	}

	return -1;
}
    
int        DropTaskItem::CheckVarId(int VarId,STask &sTask)
{
    for (DropItemType::iterator itrDrop = m_vtDropItem.begin();itrDrop!=m_vtDropItem.end();++itrDrop)
    {
        for (STaskVector::iterator itr = itrDrop->second.begin();itr != itrDrop->second.end();++itr)
        {
            if (itr->nVarId == VarId)
            {
                sTask.nMaxItemCount = itr->nMaxItemCount;
                sTask.nMaxVar = itr->nMaxVar;
                sTask.nTaskId = itr->nTaskId;
                sTask.nTaskState = itr->nTaskState;
                sTask.nVarId = itr->nVarId;
                sTask.stItem.nItemId = itr->stItem.nItemId;
                sTask.stItem.nProbability = itr->stItem.nProbability;
                return itrDrop->first;
            }
        }
    }
    return -1;
}

#endif // __QUEST_EDIT__

// bool DropTaskItem::IsTaskItemFull( GamePlayer* pPlayer, int nItemId )
// {
//     if ( !pPlayer || !pPlayer->IsPlayer())
//         return false;
//     
//     for ( unsigned int n=0; n<m_vtDropCount.size(); ++n )
//     {
//         SDropCount* pDrop = &m_vtDropCount[n];
//         if ( !pDrop)
//             continue;
// 
//         if ( pDrop->nItemId == nItemId )
//         {
//             int nBagCount = pPlayer->m_bag.GetItemCount( nItemId );
//             if ( nBagCount < pDrop->nMaxItemCount )
//                 return false;
//             else
//                 return true;
//         }
//     }
//     return true;
// }

// bool DropTaskItem::MonsterDeath( AiBaseCharacter* pMonster, BaseCharacter* pKiller )
// {
//     if ( !pKiller || !pKiller->IsPlayer() )
//         return false;
// 
//     GamePlayer* pPlayer = (GamePlayer*)pKiller;
//     if ( !pPlayer)
//         return false;
// 
//     for ( unsigned int n=0; n<m_vtDropItem.size(); ++n )
//     {
//         STaskDrop* pTaskDrop = &m_vtDropItem[n];        
//         if ( !pTaskDrop )
//             continue;
// 
//         if ( pTaskDrop->nMonster == pMonster->GetMonsterId() )
//         { // 找出此怪物
//             for ( unsigned int i=0; i<pTaskDrop->vtTask.size(); ++i)
//             {
//                 STask* pTask = &pTaskDrop->vtTask[i];
//                 // 有任务物品
//                 if ( pTask->stItem.nItemId != -1 )
//                 {
//                     // 是否需要掉落此任务物品
//                     if ( !pPlayer->IsNeedDropTaskItem( pTask->nTaskId, pTask->nTaskState, pTask->stItem.nItemId ) )
//                         continue;
// 
//                     // 按掉落机率掉落
//                     int nRand = rand()%DROP_PROBABILITY;
//                     
//                     if ( nRand < pTask->stItem.nProbability )
//                     {
//                         // 掉落物品
//                         DropItem( pTask->stItem.nItemId, 1, pMonster->GetMapID(), 
//                             pMonster->GetFloatX(), pMonster->GetFloatY(), true, pPlayer );
//                     }
//                 }
//                 if ( UpdateTeamTaskVar( pTask, pMonster, pPlayer ) )
//                 {
//                 }
//             }
//             break;
//         }
//     }
//     return true;
// }

// bool DropTaskItem::UpdateTeamTaskVar( const STask* pTask, const AiBaseCharacter* pMonster, GamePlayer *pPlayer )
// {
//     // 是否有任务关联记数变量
//     if ( pTask->nVarId == -1 )
//         return false;
//     float fMonsterX = pMonster->GetFloatX();
//     float fMonsterY = pMonster->GetFloatY();
//     //
//     QuestManager* pMgr = GetQuestManager();
//     SQuest* pQuest = pMgr->GetQuest( pTask->nTaskId );
//     if( !pQuest )
//     {
//         GetErrorLog()->logString( "SQuest %ld load failed", pTask->nTaskId );
//         return false;
//     }
//     //
//     bool bResult = false;
//     Team * pTeam = NULL;
//     pTeam = GetTeamManager().GetTeam( pPlayer->GetTeamID() );
//     if( !pTeam )
//     {
//         int nTaskState = pPlayer->GetQuestState( pTask->nTaskId );
//         if ( nTaskState == pTask->nTaskState )
// //        if( pPlayer->IsQuestActive(pTask->nTaskId) )
//         {
//             int nVar = pPlayer->GetVar( pTask->nVarId );
//             if ( nVar < pTask->nMaxVar )
//             {
//                 pPlayer->SetVar( pTask->nVarId, ++nVar );
//                 pPlayer->ShowInfo( true , 1000, 0xff00ff00, theString.GetString(eClient_AddInfo_2slk_45), theString.GetString(pQuest->QuestNameId) );
//                 pPlayer->ShowInfo( false, 1000, 0xff00ff00, "%s(%d/%d)",
//                                 pTask->strVarName.c_str(), nVar, pTask->nMaxVar );
//                 //
//                 char szLog[256];
//                 sprintf_s( szLog, 255, theString.GetString(eLog_info_2slk_21),
//                             theString.GetString(pQuest->QuestNameId), pTask->nVarId, nVar );
//                 pPlayer->Log( szLog );
//                 bResult = true;
//             }
//         }
//     }
//     else
//     {
//         for ( int n=0; n<pTeam->GetTeamNumber(); n++ )
//         {
//             int nId = pTeam->GetTeamMemberID( n );
//             if ( nId == -1 )
//             {
//                 continue;
//             }
//             GamePlayer* pTeamPlayer = NULL;
//             pTeamPlayer = (GamePlayer*)RunTimeData::GetInstance().GetCharacterByID( nId );
//             assert( pTeamPlayer );
//             if( !pTeamPlayer || !pTeamPlayer->IsPlayer() ||
//                 pTeamPlayer->IsDead() )
//                 continue;
//             int nTaskState = pTeamPlayer->GetQuestState( pTask->nTaskId );
//             if ( nTaskState == pTask->nTaskState )
//             {
//                 // 不在同一张地图(副本)
//                 if ( pTeamPlayer->GetMapID() != pMonster->GetMapID() )
//                 {
//                     continue;
//                 }
//                 float fPlayerX = pTeamPlayer->GetFloatX();
//                 float fPlayerY = pTeamPlayer->GetFloatY();
//                 float x = fMonsterX - fPlayerX;
//                 float y = fMonsterY - fPlayerY;
//                 float dist = sqrtf( x*x + y*y );
//                 // 距离过远
//                 if( dist > TEAM_TASK_VAR_DIST )
//                 {
//                     continue;
//                 }
//                 int nVar = pTeamPlayer->GetVar( pTask->nVarId );
//                 // 变量记数已经相等或超过
//                 if ( nVar >= pTask->nMaxVar )
//                 {
//                     continue;
//                 }
//                 pTeamPlayer->SetVar( pTask->nVarId, ++nVar );
//                 pTeamPlayer->ShowInfo( true , 1000, 0xff00ff00, theString.GetString(eClient_AddInfo_2slk_45), theString.GetString(pQuest->QuestNameId) );
//                 pTeamPlayer->ShowInfo( false, 1000, 0xff00ff00, "%s(%d/%d)",
//                                     pTask->strVarName.c_str(), nVar, pTask->nMaxVar );
//                 //
//                 char szLog[256];
//                 sprintf_s( szLog, 255, theString.GetString(eLog_info_2slk_22),
//                     theString.GetString(pQuest->QuestNameId), pTask->nVarId, nVar );
//                 pTeamPlayer->Log( szLog );
//                 bResult = true;
//             }
//         }
//     }
//     return bResult;
// }

