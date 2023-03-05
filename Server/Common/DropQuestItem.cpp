#include "DropQuestItem.h"
#include "GamePlayer.h"
#include "ErrorLog.h"
#include "MonsterBaseEx.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "QuestManager.h"
//#include "LogFileObjectName.h"
#include "Tinyxml/tinyxml.h"
#include "TeamManager.h"

DropQuestItem::DropQuestItem()
{
}

DropQuestItem::~DropQuestItem()
{
}

bool DropQuestItem::Init()
{
    bool bResult = LoadData();
    if ( !bResult)
        return false;

    return true;
}

bool DropQuestItem::LoadData(const char* FileName)
{
    if (!FileName||strlen(FileName) == 0)
    {
        return false;
    }
    std::string filePath = FileName;
    m_vtDropItem.clear();
    m_vtDropCount.clear();
    TiXmlDocument doc;
    if(!doc.LoadFile(filePath.c_str()))
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
        STask stTask;
        int MonsterId = 0;
        pMonster->Attribute("Id",&MonsterId);
        TiXmlElement* pDropItem = pMonster->FirstChildElement("DropItem");
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
    //old
//     m_vtDropItem.clear();
//     m_vtDropCount.clear();
// 
//     CSlkReader reader;
//     int iRet = 0;
//     int iRow = 0;
// 
//     char* szFileName = TASKDROPITEM_FILEPATH;
// 
//     if( !reader.ReadFromFile( szFileName ) )
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
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskId]  read failed", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "ItemId", nItemId ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [ItemId]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "Probability", nProbability ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [Probability]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "MaxItemCount", nMaxItemCount ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [MaxItemCount]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskVarId", nTaskVarId ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskVarId]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskState", nTaskState ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskState]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
//         if( !reader.GetIntFieldByName( "TaskMaxVar", nTaskMaxVar ) )
//         {
//             LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskMaxVar]  read failed \n", szFileName, iRow-1 );
//             continue;
//         }
// 
//         if ( nTaskVarId != -1 )
//         {
//             if( !reader.GetStringFieldByName( "TaskVarName", strVarName ) )
//             {
//                 LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s %d  [TaskVarName]  read failed \n", szFileName, iRow-1 );
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
}

bool DropQuestItem::AddDropCount( const SDropCount& stItem )
{
    bool bFind = false;
    
    DropCountType::iterator itr = m_vtDropCount.find(stItem.nItemId);
    if (itr != m_vtDropCount.end())
    {
        bFind = true;
        if ( itr->second.nMaxItemCount != stItem.nMaxItemCount )
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"QuestMonsterDropItem.config 中发现需求数不同但相同ID的任务物品[%d] \n", itr->second.nItemId );
            return false;
        }
    }

    if ( bFind == false )
    {
        m_vtDropCount.insert( DropCountType::value_type(stItem.nItemId,stItem) );
        return true;
    }
    return false;
    /*
    //old code
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
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"MonsterDropItem.config中发现需求数不同但相同ID的任务物品[%d] \n", pDrop->nItemId );
            }
            break;
        }
    }

    if ( bFind == false )
    {
        m_vtDropCount.push_back( stItem );
        return true;
    }
    return false;
    */
}

bool DropQuestItem::IsTaskItemFull( GamePlayer* pPlayer, int nItemId )
{
    if ( !pPlayer || !pPlayer->IsPlayer())
        return false;

    DropCountType::iterator find = m_vtDropCount.find(nItemId);
    if( find != m_vtDropCount.end() )
    {
        int nBagCount = pPlayer->_TaskItemBag.GetItemCount( nItemId );
        if ( nBagCount < find->second.nMaxItemCount )
            return false;
    }

    return true;
}

bool DropQuestItem::MonsterDeath( MonsterBaseEx* pMonster, BaseCharacter* pKiller )
{
    if ( !pKiller || !pKiller->IsPlayer() )
        return false;

    GamePlayer* pPlayer = (GamePlayer*)pKiller;
    if ( !pPlayer)
        return false;

    //更新杀怪记数
    pPlayer->UpdatePlayerCounterByCount(TitleConfig::Condition_KillEnemy, pMonster->GetMonsterID());

    DropItemType::iterator find =  m_vtDropItem.find(pMonster->GetMonsterID());
    if ( find == m_vtDropItem.end() )
    {
        if ( pMonster->GetMonsterID() <= ECTYPEMONSTERSTARTID )
        { return false; }       // 不是副本怪,退出

        //如果是副本怪, 如是111108, 则格式化成111100这个ID,来查找一遍
        unsigned short ustLevel = 0;
        int nEctypeMonsterID = GetEctypeMonsterID( pMonster->GetMonsterID(), ustLevel );

        nEctypeMonsterID = FormatEctypeMonsterID( nEctypeMonsterID, 0);
        find = m_vtDropItem.find( nEctypeMonsterID );
        if ( find == m_vtDropItem.end() )
        { return false; }
    }

    int nTask = 0x1;      // 任务掉落
    if ( pMonster->CheckSpecialTarget( MonsterDefine::SpecialPlayerVar, pPlayer ) )
    { nTask = nTask | 0x2; }

    for (STaskVector::iterator itr = find->second.begin();itr != find->second.end();++itr)
    {
        if ( itr->stItem.nItemId != -1 )
        {
            // 是否需要掉落此任务物品
            if ( !pPlayer->IsNeedDropTaskItem( itr->nTaskId, itr->nTaskState, itr->stItem.nItemId ) )
                continue;

            // 按掉落机率掉落
            int nRand = theRand.rand32() % DROP_PROBABILITY;

            if ( nRand < itr->stItem.nProbability )
            {
                DropItem(itr->stItem.nItemId, 1, pPlayer, nTask, itr->nTaskId, itr->nTaskState);
            }
        }
        UpdateTeamTaskVar( &(*itr), pMonster, pPlayer );
    }

    return true;
}

void DropQuestItem::QuestInfoToClient( SQuest* pQuest, const STask* pTask, MonsterBaseEx* pMonster, GamePlayer *pPlayer, int nVar )
{
    pPlayer->SetVar( pTask->nVarId, ++nVar );

    MsgUpdateQuestVar updateMsg;
    updateMsg.ustQuestId = pQuest->Id;  // 任务ID
    updateMsg.ustMonsterId = pMonster->GetMonsterID();  // 怪物ID
    updateMsg.nVar = nVar;  // 当前杀怪数量
    updateMsg.nMaxVar = pTask->nMaxVar; // 最大杀怪数量
    GettheServer().SendMsgToSingle( &updateMsg, pPlayer );
}

bool DropQuestItem::UpdateTeamTaskVar( const STask* pTask,  MonsterBaseEx* pMonster, GamePlayer *pPlayer )
{
    // 是否有任务关联记数变量
    if ( pTask->nVarId == -1 )
    { return false; }

    SQuest* pQuest = theQuestManager.GetQuest( pTask->nTaskId );
    if( pQuest == NULL )
    { return false; }

    bool bResult = false;
	GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if( pTeam == NULL || pMonster->CheckSpecialTarget( MonsterDefine::SpecialPlayerVar, pPlayer ) )    // 专属怪也只能他获得记数
    {
        int nTaskState = pPlayer->GetQuestState( pTask->nTaskId );
        if ( nTaskState == pTask->nTaskState )
        {
            int nVar = pPlayer->GetVar( pTask->nVarId );
            if ( nVar < pTask->nMaxVar )
            {
                QuestInfoToClient(pQuest, pTask, pMonster, pPlayer, nVar);
                bResult = true;
            }
        }
    }
    else
    {
		int nCount = pTeam->TeamMemberCount();
        for ( int i = 0; i < nCount; ++i)
        {
            DWORD dwPlayerID = pTeam->GetMemberIDByIndex( i );
			GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID(dwPlayerID);
            if( pTeamPlayer == NULL )
            { continue; }
         
            int nTaskState = pTeamPlayer->GetQuestState( pTask->nTaskId );
            if ( nTaskState == pTask->nTaskState )
            {
                if ( !pTeamPlayer->IsInMapArea( pMonster->GetMapID(), pMonster->GetFloatX(), pMonster->GetFloatY(), TEAM_EXP_DIS ) )
                { continue; }
               
                int nVar = pTeamPlayer->GetVar( pTask->nVarId );
                // 变量记数已经相等或超过
                if ( nVar >= pTask->nMaxVar )
                { continue; }

                QuestInfoToClient(pQuest, pTask, pMonster, pTeamPlayer, nVar);
                bResult = true;
            }
        }
    }
    return bResult;
}

#ifdef __QUEST_EDIT__

bool DropQuestItem::SaveXmlData(const char* FileName)
{
    if (!FileName||strlen(FileName) == 0)
    {
        return false;
    }
    std::string filePath = FileName;
    TiXmlDocument doc;

    doc.InsertEndChild( TiXmlDeclaration("1.0","utf-8","yes"));

    TiXmlElement* pRoot = doc.InsertEndChild(TiXmlElement("Project"))->ToElement();
    pRoot->SetAttribute("Name","HeroOnline");
    TiXmlElement* Monsters = pRoot->InsertEndChild(TiXmlElement("Monsters"))->ToElement();

    for(DropItemType::iterator itrDropitem = m_vtDropItem.begin();itrDropitem != m_vtDropItem.end();++itrDropitem)
    {
        TiXmlElement* pMonster = Monsters->InsertEndChild(TiXmlElement("Monster"))->ToElement();
        pMonster->SetAttribute("Id",itrDropitem->first);
        for(STaskVector::iterator result = itrDropitem->second.begin();result != itrDropitem->second.end();++result)
        {
            if ( result->nTaskId == -1 )
            {
                continue;
            }
            TiXmlElement* pDropItem = pMonster->InsertEndChild(TiXmlElement("DropItem"))->ToElement();
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

bool        DropQuestItem::AddQuest(int MonsterId ,STask &stask, bool bDropCount /* = true*/)
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
                        addit->nMaxItemCount = stask.nMaxItemCount;
                        addit->nMaxVar = stask.nMaxVar;
                        addit->nTaskState = stask.nTaskState;
                        addit->nVarId = stask.nVarId;
                        addit->stItem.nItemId = stask.stItem.nItemId;
                        addit->stItem.nProbability = stask.stItem.nProbability;
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

bool        DropQuestItem::SubQuest(int Monster,int QuestId)
{
    DropItemType::iterator result = m_vtDropItem.find(Monster);
    if (result == m_vtDropItem.end())
    {
        return false;
    }
    bool bFind = false;
    for (STaskVector::iterator itrResult = result->second.begin();itrResult != result->second.end();++itrResult)
    {
        if (itrResult->nTaskId == QuestId)
        {
            bFind = !bFind;
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

    return bFind;
}

bool        DropQuestItem::CoalitionTable(DropQuestItem* item)
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
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"MonsterDropItem.config合并文件出错，QuestId = [%d] \n", result->nTaskId );
                CoalitionResult = false;
            }
        }
    }
    return CoalitionResult;
}

int         DropQuestItem::FindDropItemByVarId(int Varid,STask &sTask)
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

int         DropQuestItem::FindDropItemByMonsterId(int MonsterId,int Questid,STask &sTask)
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

int DropQuestItem::FindDropItemByItemId(int ItemId, int QuestId, STask &task)
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
    
int        DropQuestItem::CheckVarId(int VarId,STask &sTask)
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