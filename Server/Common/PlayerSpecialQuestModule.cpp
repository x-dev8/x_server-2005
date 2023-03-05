#include "GamePlayer.h"
#include "QuestManager.h"
#include "SpecialTask.h"
#include "GlobalDef.h"
#include <map>

bool GamePlayer::TriggerSpecialQuest(ESpecialTaskType eQuestType)
{
	CSpecialTaskMgr::PairIter	pTaskRange = TheSpecialTaskMgr.GetTaskRangeByType(eQuestType);
	if (pTaskRange.first == pTaskRange.second)
	{
		return false;
	}
	
	switch (eQuestType)
	{
	
	case ESTT_Intensify:					//ǿ��
	case ESTT_GemUp:						//��ʯ����
	case ESTT_Hole:							//���
	case ESTT_EquipGem:						//��Ƕ��ʯ
	case ESTT_EquipStar:					//װ������
	case ESTT_KillPlayer:
	case ESTT_KillWei:
	case ESTT_KillShu:
	case ESTT_KillWu:
	default:
		while(pTaskRange.first!=pTaskRange.second)
		{
			CSpecialTaskMgr::SSpecialTask* pTast = pTaskRange.first->second;
			pTaskRange.first++;
			if (GetQuestState(pTast->nTaskID)!=QuestManager::eQuestGaining)
			{
				continue;
			}
			map<int,int> mapVar = pTast->mapTaskVarReq;
			bool bDone = true;
			
			for (map<int,int>::iterator iter=mapVar.begin();iter!=mapVar.end();iter++)
			{
				int var = GetVar(iter->first);
				if ( var < iter->second )
				{
					SetVar(iter->first, var+1);
					if ((var+1) < iter->second)
					{
						bDone = false;
					}
				}
			}
			//if (bDone)
			//{
			//	SetQuestState(pTast->nTaskID,QuestManager::eQuestDone);
			//	//SetVar( pTast->nTaskID, theQuestManager.SetQuestState( GetVar( pTast->nTaskID ), QuestManager::eQuestDone ) );
			//}			
		}
		break;
	}
	return true;
}

bool GamePlayer::TriggerKillPlayerQuest()
{
	return true;
}