/********************************************************************
Created by UIEditor.exe
FileName: E:\武将三国\Data\Ui\TimeLimitTask.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TimeLimitTask.h"
#include "PlayerRole.h"
#include "NpcCoord.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "color_config.h"

CUI_ID_FRAME_TimeLimitTask s_CUI_ID_FRAME_TimeLimitTask;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TimeLimitTask, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TimeLimitTask, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TimeLimitTask, ID_BUTTON_SubOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TimeLimitTask, ID_BUTTON_PlusOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TimeLimitTask, ID_LIST_TaskOnListSelectChange )
CUI_ID_FRAME_TimeLimitTask::CUI_ID_FRAME_TimeLimitTask()
{
	// Member
	m_pID_FRAME_TimeLimitTask = NULL;
	m_pID_BUTTON_Sub = NULL;
	m_pID_BUTTON_Plus = NULL;
	m_pID_PICTURE_TaskWall = NULL;
	m_pID_LIST_Task = NULL;
	m_bMinisize = false;
	m_bHasTask = false;
}
// Frame
bool CUI_ID_FRAME_TimeLimitTask::OnFrameRun()
{
	std::vector<CPlayerRole::QuestInfo*>& activeQuest = thePlayerRole.GetActiveQuestInfo();
	m_bHasTask = false;
	for (int i=0;i<activeQuest.size();++i)
	{
		bool bRequireTime = false;
		SQuest* pQuestInfo = theQuestManager.GetQuest(activeQuest[i]->nQuestId);
		if (pQuestInfo)
		{
			SQuest::RequirementType CommitRequirement = pQuestInfo->stCommitRequirement;
			CPlayerRole::QuestInfo* pQuestState = thePlayerRole.FindQuestInfoById(activeQuest[i]->nQuestId);
			for (SQuest::RequirementTypeItr iter = CommitRequirement.begin();iter!=CommitRequirement.end();++iter)
			{
				if (iter->byType == SQuest::eRequirement_Time)
					bRequireTime = true;
			}
		}
		m_bHasTask = m_bHasTask||((activeQuest[i]->chState==QuestManager::eQuestGaining && bRequireTime)?true:false);
	}
	_SetVisable(m_bHasTask);
	if (!_IsVisable() || m_bMinisize || !m_bHasTask)
	{
		return false;
	}
	RefreshTask();
	return true;
}
bool CUI_ID_FRAME_TimeLimitTask::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_TimeLimitTask::ID_BUTTON_SubOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_TimeLimitTask)
	{
		return false;
	}
	m_bMinisize = true;
	m_pID_LIST_Task->Clear();
	m_pID_BUTTON_Plus->SetVisable(true);
	m_pID_BUTTON_Sub->SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_TimeLimitTask::ID_BUTTON_PlusOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_TimeLimitTask)
	{
		return false;
	}
	m_bMinisize = false;
	RefreshTask();
	m_pID_BUTTON_Plus->SetVisable(false);
	m_pID_BUTTON_Sub->SetVisable(true);
	return true;
}
// List
void CUI_ID_FRAME_TimeLimitTask::ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_TimeLimitTask::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TimeLimitTask.MEUI",true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TimeLimitTask.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TimeLimitTask::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TimeLimitTask, s_CUI_ID_FRAME_TimeLimitTaskOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TimeLimitTask, s_CUI_ID_FRAME_TimeLimitTaskOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_TimeLimitTask, ID_BUTTON_Sub, s_CUI_ID_FRAME_TimeLimitTaskID_BUTTON_SubOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_TimeLimitTask, ID_BUTTON_Plus, s_CUI_ID_FRAME_TimeLimitTaskID_BUTTON_PlusOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_TimeLimitTask, ID_LIST_Task, s_CUI_ID_FRAME_TimeLimitTaskID_LIST_TaskOnListSelectChange );

	m_pID_FRAME_TimeLimitTask = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TimeLimitTask );
	m_pID_BUTTON_Sub = (ControlButton*)theUiManager.FindControl( ID_FRAME_TimeLimitTask, ID_BUTTON_Sub );
	m_pID_BUTTON_Plus = (ControlButton*)theUiManager.FindControl( ID_FRAME_TimeLimitTask, ID_BUTTON_Plus );
	m_pID_PICTURE_TaskWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TimeLimitTask, ID_PICTURE_TaskWall );
	m_pID_LIST_Task = (ControlList*)theUiManager.FindControl( ID_FRAME_TimeLimitTask, ID_LIST_Task );
	assert( m_pID_FRAME_TimeLimitTask );
	assert( m_pID_BUTTON_Sub );
	assert( m_pID_PICTURE_TaskWall );
	assert( m_pID_LIST_Task );
	assert( m_pID_BUTTON_Plus );

	if (m_pID_LIST_Task)
	{
		m_pID_LIST_Task->SetOnCollapseFun( Task_CollapseCallBackFun );
		m_pID_LIST_Task->RemoveSyntaxFlag(eKeyItem);
	}

	if (m_pID_BUTTON_Plus)
	{
		m_pID_BUTTON_Plus->SetVisable(false);
	}
	if (m_pID_BUTTON_Sub)
	{
		m_pID_BUTTON_Sub->SetVisable(true);
	}
	
	_SetVisable(true);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TimeLimitTask::_UnLoadUI()
{
	m_pID_FRAME_TimeLimitTask = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TimeLimitTask.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TimeLimitTask::_IsVisable()
{
	return m_pID_FRAME_TimeLimitTask->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TimeLimitTask::_SetVisable( const bool bVisable )
{
	if (m_pID_FRAME_TimeLimitTask)
	{
		m_pID_FRAME_TimeLimitTask->SetVisable( bVisable );
	}
	
	//if (bVisable)
	//{
	//	RefreshTask();
	//}
	//
}

void CUI_ID_FRAME_TimeLimitTask::RefreshTask()
{
	std::vector<CPlayerRole::QuestInfo*>& activeQuest = thePlayerRole.GetActiveQuestInfo();
	char localStr[128];
	m_pID_LIST_Task->Clear();
	for (int i=0; i<activeQuest.size(); ++i)
	{
		SQuest* pQuestInfo = theQuestManager.GetQuest(activeQuest[i]->nQuestId);
		if (pQuestInfo)
		{
			SQuest::RequirementType CommitRequirement = pQuestInfo->stCommitRequirement;
			CPlayerRole::QuestInfo* pQuestState = thePlayerRole.FindQuestInfoById(activeQuest[i]->nQuestId);
			for (SQuest::RequirementTypeItr iter = CommitRequirement.begin();iter!=CommitRequirement.end();++iter)
			{
				if (iter->byType == SQuest::eRequirement_Time && pQuestState->chState == QuestManager::eQuestGaining )
				{
					//std::vector<UiCallbackDataBase*> CallBackDataArr;
					//CallBackDataArr.clear();
					//NpcCoord::getInstance()->addNpcHyberForText(localStr,NpcCoord::eQuestId,activeQuest[i]->nQuestId,pQuestInfo->ReplyTargetId,&CallBackDataArr);
					
					ControlList::S_List	stItem;
					TimeEx xStartTime( activeQuest[i]->time );    // 
					TimeEx xCurrentTime = TimeEx::GetCurrentTime();
					TimeSpan xSpan = xCurrentTime - xStartTime;
					int leftTime = iter->Value - xSpan.GetTotalSeconds();
					if (leftTime<=0)
					{
						break;
					}
					MeSprintf_s(localStr, sizeof(localStr)/sizeof(char) - 1, "【%s】%s",theXmlString.GetString( eText_QuestType_1 + pQuestInfo->chQuestType ),pQuestInfo->GetQuestName());
					stItem.UseSelColor = false;
					stItem.m_nHiberarchy = 0;
					stItem.RemoveSyntaxFlag(eKeyHyper);
					stItem.SetData( localStr,activeQuest[i]->nQuestId,NULL,Color_Config.getColor( CC_TASK_NAME ) );
					m_pID_LIST_Task->AddItem(&stItem,NULL);

					MeSprintf_s(localStr, sizeof(localStr)/sizeof(char) - 1, "%s",theXmlString.GetString(pQuestInfo->TargetStringId));
					std::vector<UiCallbackDataBase*> CallBackDataArr;
					CallBackDataArr.clear();
					std::string Str = localStr;
					NpcCoord::getInstance()->addNpcHyberForText(Str,NpcCoord::eQuestId,activeQuest[i]->nQuestId,pQuestInfo->ReplyTargetId,&CallBackDataArr,true);
					stItem.m_nHiberarchy = 1;
					stItem.SetData( Str.c_str(),activeQuest[i]->nQuestId );
					m_pID_LIST_Task->AddItem(&stItem,NULL);

					MeSprintf_s(localStr, sizeof(localStr)/sizeof(char) - 1, "剩余时间:%02d:%02d:%02d",leftTime/3600,(leftTime/60)%60,leftTime%60);
					stItem.m_nHiberarchy = 1;
					stItem.SetData( localStr,activeQuest[i]->nQuestId );
					m_pID_LIST_Task->AddItem(&stItem,NULL);
					//stItem.SetHyberOtherColor(col );
					break;
				}
			}	
		}
	}
	if (m_bHasTask)
	{
		_SetVisable(true);
	}
	else
	{
		_SetVisable(false);
	}
}

void CUI_ID_FRAME_TimeLimitTask::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_TimeLimitTask )
		return;

	_SetVisable( false );
}

void CUI_ID_FRAME_TimeLimitTask::Task_CollapseCallBackFun( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_TimeLimitTask.RefreshListData();
}

void CUI_ID_FRAME_TimeLimitTask::RefreshListData()
{
	if( !m_pID_FRAME_TimeLimitTask )
		return;

	ControlList::S_List stItem;

	if (m_pID_LIST_Task->GetListItemCnt() - m_pID_LIST_Task->GetStartIndex() < m_pID_LIST_Task->GetItemShowCount())
	{
		m_pID_LIST_Task->SetShowStartHeight(0);
		m_pID_LIST_Task->SetShowStartHeight(0);
	}
}