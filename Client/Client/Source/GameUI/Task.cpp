/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Task.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Task.h"
#include "Task_Track.h"
#include "QuestManager.h"
#include "actionUi.h"
#include "Property.h"
#include "GameMain.h"
#include "MessageBox.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
#include "../MotionBillBoard.h"
#include "ChatInfoBox.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "../MiniMap.h"
#include "Epic.h"
#include "GameMain.h"
#include "MeUi/ExpressionManager.h"
#include "QuestData.h"
#include "core/Name.h"
#include "QuestManager.h"
#include "GroupPanel.h"
#include "Compound.h"
#include "Gang.h"
#include "NpcTaskDialogBox.h"
#include "NpcChatDialogBox.h"
#include "SelectBox.h"
#include "script_manager.h"
#include "NpcInfo.h"
#include "MeTerrain/stdafx.h"
#include "ScreenInfoManager.h"
#include "TitleConfig.h"
#include "AllNpcList.h"
#include "ActivityList.h"
#include "UserData.h"
#include "logmgr.h"
#include "RapidXml/MeRapidXml.h"
#include "Cfg.h"
#include "Player.h"
#include "MeFont\MeFontSystem.h"
#include "SoundConfig.h"
#include "ui\ActivityDay.h"
#include "ui\QuestEntrust.h"
#include "ui\AddQuestEntrust.h"
extern char* GetFullFileName(const char* filename);

#define ERROR_INFO_LOG	"ErrorInfo.log"

const char* NpcHyberLeft = "<";
const char* NpcHyberRight = ">";

extern short GetKeyboardInput( int iKey );



enum
{
	eCurr_Task = 0,
	eAcceptable_Task,
	TotalTabType
};
struct TreeStatusRecord {
	short m_nSubType;
	bool m_isCollapse;
	TreeStatusRecord(int nSubType,bool isCollapse)
		:m_nSubType(nSubType),m_isCollapse(isCollapse)
	{;}
};
typedef std::vector<TreeStatusRecord>  RecordArr;
RecordArr					m_RecordArr[TotalTabType]; 
void CUI_ID_FRAME_Task::RecordCollapseInfo()
{
	for(int i = 0; i < m_pID_LIST_Task->GetListItemCnt(); ++i)
	{
		ControlList::S_List* pList = m_pID_LIST_Task->GetListItem(i);
		if (pList->m_nHiberarchy == 0)
		{
			bool isExisted = false;
			for (int i = 0; i < m_RecordArr[m_CurrTabType].size(); ++i)
			{
				if (m_RecordArr[m_CurrTabType][i].m_nSubType == pList->m_nID)
				{
					m_RecordArr[m_CurrTabType][i].m_isCollapse = pList->m_bCollapse;
					isExisted = true;
				}
			}
			if (!isExisted)
			{
				m_RecordArr[m_CurrTabType].push_back(TreeStatusRecord(pList->m_nID,pList->m_bCollapse));
			}
		}
	}
}
static const char* TaskTreeFilename = "TaskTreeStatus.config";
static const char* TaskTreeFilenameOld = "TaskTreeStatus.xml";
bool CUI_ID_FRAME_Task::LoadCollapseInfo()
{
	for (int i = 0; i < TotalTabType; ++i)
	{
		m_RecordArr[i].clear();
	}
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTreeFilename;

	MeXmlDocument doc1;
// 	if( !doc1.LoadFile(filename.c_str()) )
// 	{
// 		filename = CUserData::Instance()->GetUserDataPath();
// 		filename += TaskTreeFilenameOld;
// 	}

	if( doc1.LoadFile(filename.c_str()) )
	{
// 		MeXmlHandle	 hDoc1(&doc1);

		MeXmlElement* pHeader = doc1.FirstChildElement("Project");
		if (pHeader)
		{
			MeXmlElement* pElem = pHeader->FirstChildElement("TreeStatuses")->FirstChildElement("TaskTabType");
			for( ; pElem; pElem = pElem->NextSiblingElement() )
			{
				int nType = 0;
				pElem->QueryIntAttribute("Type", &nType);

				if (nType < 0 || nType >= TotalTabType)
				{
					continue;
				}
				MeXmlElement* pStatus = pElem->FirstChildElement("TreeStatus");
				for( ; pStatus; pStatus = pStatus->NextSiblingElement() )
				{
					int nSubType = 0;
					pStatus->QueryIntAttribute("SubType", &nSubType);
					int nIsCollapse = 0;
					pStatus->QueryIntAttribute("IsCollapse", &nIsCollapse);
					m_RecordArr[nType].push_back(TreeStatusRecord(nSubType,nIsCollapse));
				}
			}
		}
	}

	return true;

}

bool CUI_ID_FRAME_Task::SaveCollapseInfo()
{
	if (m_pID_FRAME_Task == NULL)
	{
		return false;
	}
	RecordCollapseInfo();
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTreeFilename;

	SetFileAttributes( filename.c_str(), FILE_ATTRIBUTE_NORMAL );
	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "utf-8", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement *project = doc.InsertEndChild("Project");
	project->SetAttribute("Name", "HeroOnline");
	project->SetAttribute("Version", "");

	MeXmlElement *tracks = project->InsertEndChild("TreeStatuses");

	for (int i = 0; i < TotalTabType; ++i)
	{
		MeXmlElement *TaskTabType = tracks->InsertEndChild("TaskTabType");
		TaskTabType->SetAttribute("Type", i);
		for (int z = 0; z < m_RecordArr[i].size();++z)
		{
			MeXmlElement *track = TaskTabType->InsertEndChild("TreeStatus");
			track->SetAttribute("SubType", m_RecordArr[i][z].m_nSubType);
			track->SetAttribute("IsCollapse", m_RecordArr[i][z].m_isCollapse);
// 			TaskTabType.InsertEndChild(track);
		}
// 		tracks.InsertEndChild(TaskTabType);
	}
// 	project.InsertEndChild(tracks);

// 	doc.InsertEndChild(project);
	doc.SaveFile(filename.c_str());

	// 删除旧文件格式
	filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTreeFilenameOld;
	::DeleteFile(filename.c_str());

	return true;
}

CUI_ID_FRAME_Task s_CUI_ID_FRAME_Task;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Task, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Task, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Task, ID_LIST_TaskOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_AbandonTaskOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_RewardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_RewardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_RewardOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_ThirdItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_ThirdItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_ThirdItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_ThirdItemOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_FourItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_FourItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_FourItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_FourItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Task, ID_CHECKBOX_Task1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Task, ID_CHECKBOX_Task2OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_ZhuizongOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_QuxiaoOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Task, ID_LIST_TaskstateOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Task, ID_CHECKBOX_jienengOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_ActivityListOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Task, ID_LIST_FinishOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_SecondItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_SecondItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_SecondItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Task, ID_LISTIMG_SecondItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_EpicOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Task, ID_CHECKBOX_ActivityTrackOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Task, ID_CHECKBOX_JinOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_AddQuestEntrustOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Task, ID_BUTTON_OpenQuestEntrustOnButtonClick )
CUI_ID_FRAME_Task::CUI_ID_FRAME_Task()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_Task::ResetMembers()
{
	m_pID_FRAME_Task = NULL;
	m_pID_LIST_Task = NULL;
	m_pID_BUTTON_AbandonTask = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_LISTIMG_ThirdItem = NULL;
	m_pID_LISTIMG_FourItem = NULL;
	m_pID_PICTURE_174 = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_Task1 = NULL;
	m_pID_CHECKBOX_Task2 = NULL;
	m_pID_BUTTON_Zhuizong = NULL;
	m_pID_BUTTON_Quxiao = NULL;
	m_pID_TEXT_TaskDiff = NULL;
	m_pID_CHECKBOX_jieneng = NULL;
	m_pID_TEXT_TaskTrack = NULL;
	m_pID_BUTTON_ActivityList = NULL;
	m_pID_LIST_Finish = NULL;
	m_bUILoad = FALSE;
	m_pID_TEXT_TaskInfo = NULL;
	m_pID_TEXT_TaskDepict = NULL;
	m_bUpdateTrackTask = false;

	_nCurIndex = 0;
	m_nCurrSelectedQuest = -1;
	m_CurrTabType = eCurr_Task;
	m_pID_LISTIMG_SecondItem = NULL;
	m_pID_TEXT_FITEM = NULL;
	m_pID_TEXT_SECITEM = NULL;
	m_pID_BUTTON_Epic = NULL;
	m_pID_CHECKBOX_ActivityTrack = NULL;

	m_pID_TEXT_AwardExp = NULL;
	m_pID_TEXT_AwardMoney = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_TEXT_Award = NULL;
	m_pID_TEXT_Aim = NULL;

	m_pID_PICTURE_JQ1 = NULL;
	m_pID_CHECKBOX_Jin = NULL;
	m_pID_BUTTON_AddQuestEntrust = NULL;
	m_pID_BUTTON_OpenQuestEntrust = NULL;
}
// Frame
bool CUI_ID_FRAME_Task::OnFrameRun()
{
	if( IsVisable() )
	{
		int nStartIndex = m_pID_LIST_Task->GetShowStartHeight();
		m_pID_LIST_Finish->SetShowStartHeight(nStartIndex);
	}
	return true;
}
bool CUI_ID_FRAME_Task::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_Task::ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Task )
		return;
	_nCurIndex = m_pID_LIST_Task->GetCurSelIndex();

	if (_nCurIndex != -1 && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		int id = m_pID_LIST_Task->GetCurSelItem()->m_nID;
		std::vector<int>::iterator itr = std::find(m_vNotTrackList.begin(), m_vNotTrackList.end(), id);
		if (m_pID_CHECKBOX_Task1->IsChecked())
		{
			m_pID_BUTTON_Zhuizong->SetVisable(itr != m_vNotTrackList.end());
			m_pID_BUTTON_Quxiao->SetVisable(itr == m_vNotTrackList.end());
		}
		//UITask_ShowInfo(id);
		UpdateTaskPanel(id);	

		//屏蔽任务链接
		//if ( GetKeyState( VK_SHIFT ) & 0x8000 )
		//{
		//	SQuest *pQuest = theQuestManager.GetQuest( id );
		//	if ( pQuest )
		//	{
		//		CommonChatFrame::GetActiveChatFrame()->addHyberTextEx( pQuest->GetQuestName(), MsgChat::HYBERTYPE_TASK, id, 0 );	
		//	}
		//			
		//}
	}
}
// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_EpicOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_Epic.SetVisable( !s_CUI_ID_FRAME_Epic.IsVisable() );
	theUiManager.ToTop(s_CUI_ID_FRAME_Epic.GetFrame());
	return true;
}
// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_AbandonTaskOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Task )
		return false;
	ControlList::S_List *pList = NULL;
	pList = m_pID_LIST_Task->GetCurSelItem();
	if ( !pList || pList->m_nHiberarchy != 1)
		return false;
	int nTaskId = pList->m_nID;
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nTaskId );
	if ( !pInfo )
		return false;

	if(pInfo->chState ==  QuestManager::eQuestFrozen )
	{
		//提示玩家 冻结的任务无法放弃
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_CancelError));
		return false;
	}

    // 判断能否请求脚本
    if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->CanReqScript() )
        return false;

	if( theQuestManager.IsQuestActive( pInfo->chState ) )
	{
		SQuest *pQuest = theQuestManager.GetQuest( pInfo->nQuestId );
		if ( pQuest && !pQuest->IsCancel )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eClient_task_AbandonTask) );
			return false;
		}

		MsgAbandonTask msg;
		msg.stTaskId = nTaskId;
		//是否放弃此任务 确认
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Ask_Task),
			"",
			CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
			CUI_ID_FRAME_Task::Task_AbandonCallBackFun,
			&msg, sizeof(msg) );
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Task::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Task )
		return false;
	return false;
}

bool CUI_ID_FRAME_Task::ID_LISTIMG_ThirdItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_ThirdItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_ThirdItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_ThirdItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Task::ID_LISTIMG_FourItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_FourItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_FourItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}
bool CUI_ID_FRAME_Task::ID_LISTIMG_FourItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Task )
		return false;
	return false;
}

// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Task )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_Task::ID_CHECKBOX_Task1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Task )
		return;
	m_pID_CHECKBOX_Task1->SetCheck(true);
	m_pID_CHECKBOX_Task2->SetCheck(false);
	m_pID_BUTTON_AbandonTask->SetEnable(true);
	RecordCollapseInfo();
	m_CurrTabType = eCurr_Task;
	Refresh(true);
	m_pID_BUTTON_AddQuestEntrust->SetVisable(true);
}
// CheckBox
void CUI_ID_FRAME_Task::ID_CHECKBOX_Task2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Task )
		return;
	m_pID_CHECKBOX_Task1->SetCheck(false);
	m_pID_CHECKBOX_Task2->SetCheck(true);
	m_pID_BUTTON_AbandonTask->SetEnable(false);
	m_pID_BUTTON_Quxiao->SetVisable(false);
	m_pID_BUTTON_Zhuizong->SetVisable(false);
	RecordCollapseInfo();
	m_CurrTabType = eAcceptable_Task;
	Refresh(true);
	m_pID_BUTTON_AddQuestEntrust->SetVisable(false);
}
// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_ZhuizongOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Task )
		return false;
	if (m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		int id = m_pID_LIST_Task->GetCurSelItem()->m_nID;
		std::vector<int>::iterator itr = std::find(m_vNotTrackList.begin(), m_vNotTrackList.end(), id);
		if(itr != m_vNotTrackList.end())
			m_vNotTrackList.erase(itr);
		m_pID_BUTTON_Zhuizong->SetVisable(false);
		m_pID_BUTTON_Quxiao->SetVisable(true);
		UpdateTrackInfo();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_QuxiaoOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Task )
		return false;
	if (m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		int id = m_pID_LIST_Task->GetCurSelItem()->m_nID;
		m_vNotTrackList.push_back(id);
		m_pID_BUTTON_Zhuizong->SetVisable(true);
		m_pID_BUTTON_Quxiao->SetVisable(false);
		UpdateTrackInfo();
		SaveTrackInfo();
	}
	return true;
}
// List
void CUI_ID_FRAME_Task::ID_LIST_TaskstateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Task )
		return;
}
// List
// void CUI_ID_FRAME_Task::ID_LIST_TaskInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if( !m_pID_FRAME_Task )
// 		return;
// }
// CheckBox
void CUI_ID_FRAME_Task::ID_CHECKBOX_jienengOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Task )
		return;
}
// Button
// bool CUI_ID_FRAME_Task::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_Task )
// 		return false;
// 	return true;
// }
// Button
bool CUI_ID_FRAME_Task::ID_BUTTON_ActivityListOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Task )
		return false;
	s_CUI_ID_FRAME_ActivityList.SetVisable(!s_CUI_ID_FRAME_ActivityList.IsVisable());
	//s_CUI_ID_FRAME_ActivityDay.SetVisable(!s_CUI_ID_FRAME_ActivityDay.IsVisable());
	return true;
}

void CUI_ID_FRAME_Task::InitializeAtEnterWorld()
{
    for (int i = SQuest::Type_Main; i < SQuest::Type_End; ++i)
    {
        m_QuestTypeString[i] = theXmlString.GetString(eQuestType_1 + i);
    
    }

    m_vTrackList.clear();
    m_bTaskInfoLoaded = false;

    m_arrHideTaskTypeInAccecptableTask.clear();
    char strFilename[MAX_PATH] = {0};
    sprintf(strFilename, "%s/Data/ClientConfig/GameSetting.config", GetRootPath());
    MeXmlDocument	doc;
    if( !doc.LoadFile(strFilename) )
    {
        assert(false && "GameSetting::config 文件读取失败");
        return;
    }

    // 	MeXmlHandle		hDoc(&doc);
    const char* szValue = NULL;
    int nId = -1;

    MeXmlElement* pElem = doc.FirstChildElement("Project")->FirstChildElement("SystemConfig")
        ->FirstChildElement("Game")->FirstChildElement("HideAcceptableQuest")->FirstChildElement("String");
    if (pElem)
    {
        for( ; pElem; pElem = pElem->NextSiblingElement() )
        {
            pElem->QueryIntAttribute("TypeId", &nId);
            m_arrHideTaskTypeInAccecptableTask.push_back(nId);
        }
    }

    Refresh();

	m_bFirst = true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Task::ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_ID_FRAME_Task::ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Task::ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Task::ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Task::ID_BUTTON_AddQuestEntrustOnButtonClick( ControlObject* pSender )
{
	_nCurIndex = m_pID_LIST_Task->GetCurSelIndex();
	if (_nCurIndex != -1 && m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		int id = m_pID_LIST_Task->GetCurSelItem()->m_nID;
		s_CUI_ID_FRAME_AddQuestEntrust.LoadInfoToUI(id);
	}
	return true;
}
bool CUI_ID_FRAME_Task::ID_BUTTON_OpenQuestEntrustOnButtonClick( ControlObject* pSender )
{
	//打开任务委托面板
	s_CUI_ID_FRAME_QuestEntrust.SetVisable(!s_CUI_ID_FRAME_QuestEntrust.IsVisable());
	return true;
}
// CheckBox
void CUI_ID_FRAME_Task::ID_CHECKBOX_ActivityTrackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	s_CUI_ID_FRAME_TRACK.SetVisable( *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_Task::ID_CHECKBOX_JinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (_IsVisable())
	{
		Refresh(true);
	}
}

bool CUI_ID_FRAME_Task::UITaskFrame_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
	

	return false;
}

// 装载UI
bool CUI_ID_FRAME_Task::_LoadUI()
{
	LoadCollapseInfo();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Task.MEUI",false,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Task.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Task::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Task, s_CUI_ID_FRAME_TaskOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Task, s_CUI_ID_FRAME_TaskOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Task, ID_LIST_Task, s_CUI_ID_FRAME_TaskID_LIST_TaskOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_AbandonTask, s_CUI_ID_FRAME_TaskID_BUTTON_AbandonTaskOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Task, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskID_LISTIMG_RewardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Task, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskID_LISTIMG_RewardOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Task, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskID_LISTIMG_RewardOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Task, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskID_LISTIMG_RewardOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Task, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_TaskID_LISTIMG_ThirdItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Task, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_TaskID_LISTIMG_ThirdItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Task, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_TaskID_LISTIMG_ThirdItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Task, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_TaskID_LISTIMG_ThirdItemOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Task, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_TaskID_LISTIMG_FourItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Task, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_TaskID_LISTIMG_FourItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Task, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_TaskID_LISTIMG_FourItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Task, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_TaskID_LISTIMG_FourItemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TaskID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Task, ID_CHECKBOX_Task1, s_CUI_ID_FRAME_TaskID_CHECKBOX_Task1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Task, ID_CHECKBOX_Task2, s_CUI_ID_FRAME_TaskID_CHECKBOX_Task2OnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_Zhuizong, s_CUI_ID_FRAME_TaskID_BUTTON_ZhuizongOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_Quxiao, s_CUI_ID_FRAME_TaskID_BUTTON_QuxiaoOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Task, ID_LIST_Taskstate, s_CUI_ID_FRAME_TaskID_LIST_TaskstateOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Task, ID_CHECKBOX_jieneng, s_CUI_ID_FRAME_TaskID_CHECKBOX_jienengOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_ActivityList, s_CUI_ID_FRAME_TaskID_BUTTON_ActivityListOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Task, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskID_LISTIMG_SecondItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Task, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskID_LISTIMG_SecondItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Task, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskID_LISTIMG_SecondItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Task, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskID_LISTIMG_SecondItemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_Epic, s_CUI_ID_FRAME_TaskID_BUTTON_EpicOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Task, ID_CHECKBOX_ActivityTrack, s_CUI_ID_FRAME_TaskID_CHECKBOX_ActivityTrackOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Task, ID_CHECKBOX_Jin, s_CUI_ID_FRAME_TaskID_CHECKBOX_JinOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_AddQuestEntrust, s_CUI_ID_FRAME_TaskID_BUTTON_AddQuestEntrustOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Task, ID_BUTTON_OpenQuestEntrust, s_CUI_ID_FRAME_TaskID_BUTTON_OpenQuestEntrustOnButtonClick );
		

	m_pID_FRAME_Task = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Task );
	m_pID_LIST_Task = (ControlList*)theUiManager.FindControl( ID_FRAME_Task, ID_LIST_Task );
	m_pID_BUTTON_AbandonTask = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_AbandonTask );
	m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Task, ID_LISTIMG_Reward );
	m_pID_LISTIMG_ThirdItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Task, ID_LISTIMG_ThirdItem );
	m_pID_LISTIMG_FourItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Task, ID_LISTIMG_FourItem );
	m_pID_PICTURE_174 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Task, ID_PICTURE_174 );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_Task1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Task, ID_CHECKBOX_Task1 );
	m_pID_CHECKBOX_Task2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Task, ID_CHECKBOX_Task2 );
	m_pID_BUTTON_Zhuizong = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_Zhuizong );
	m_pID_BUTTON_Quxiao = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_Quxiao );
	m_pID_TEXT_TaskDiff = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_TaskDiff );
	m_pID_CHECKBOX_jieneng = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Task, ID_CHECKBOX_jieneng );
	m_pID_TEXT_TaskTrack = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_TaskTrack );
	m_pID_BUTTON_ActivityList = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_ActivityList );
	m_pID_LIST_Finish = (ControlList*)theUiManager.FindControl( ID_FRAME_Task, ID_LIST_Finish );
    m_pID_TEXT_TaskInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_TaskInfo );
	m_pID_TEXT_TaskDepict = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_TaskDepict );
	m_pID_LISTIMG_SecondItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Task, ID_LISTIMG_SecondItem );
	m_pID_TEXT_FITEM = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_FITEM );
	m_pID_TEXT_SECITEM = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_SECITEM );
	m_pID_BUTTON_Epic = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_Epic );
	m_pID_CHECKBOX_ActivityTrack = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Task, ID_CHECKBOX_ActivityTrack );

	m_pID_TEXT_AwardExp = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_AwardExp );
	m_pID_TEXT_AwardMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_AwardMoney );
	m_pID_PICTURE_JQ1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Task, ID_PICTURE_JQ1 );
	m_pID_TEXT_Amount = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_Amount );
	m_pID_TEXT_Award = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_Award );
	m_pID_TEXT_Aim = (ControlText*)theUiManager.FindControl( ID_FRAME_Task, ID_TEXT_Aim );
	m_pID_CHECKBOX_Jin = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Task, ID_CHECKBOX_Jin );
	m_pID_BUTTON_AddQuestEntrust = (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_AddQuestEntrust );
	m_pID_BUTTON_OpenQuestEntrust= (ControlButton*)theUiManager.FindControl( ID_FRAME_Task, ID_BUTTON_OpenQuestEntrust );
	assert(m_pID_CHECKBOX_Jin);

	char szTemp[64] = {0};
	for(int i=1; i<18; ++i)
	{
		sprintf(szTemp, "ID_PICTURE_Finish%d", i);
		ControlPicture* pPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Task, szTemp );
		if( pPic )
			m_finishPics.AddControl(pPic);
	}
	m_finishPics.SetVisible(false);

	m_pID_FRAME_Task->SetOnVisibleChangedFun(FrameOnVisiableChanged);
	m_pID_LIST_Task->SetOnCollapseFun( Task_CollapseCallBackFun );
	m_pID_LIST_Task->SetOnVisibleChangedFun(Task_OnVisiableChanged);
	m_pID_LIST_Task->RemoveSyntaxFlag(eKeyItem);

	m_pID_CHECKBOX_jieneng->SetCheck(true);
	m_pID_CHECKBOX_Task1->SetCheck(true);
	m_pID_CHECKBOX_Task2->SetCheck(false);
	m_pID_CHECKBOX_Jin->SetCheck(false);

	m_pID_LIST_Finish->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_Finish->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_Finish->SetCurSelIndex(-1);

	m_pID_TEXT_TaskInfo->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_HighLightNpcName)));
	m_pID_TEXT_TaskInfo->setShowTip(true);

	m_pID_TEXT_TaskInfo->GetScrollBar()->SetUpdatePosFun(UpdateTaskInfo);
	m_pID_CHECKBOX_ActivityTrack->SetCheck( true );

	m_pID_FRAME_Task->SetMsgProcFun( UITaskFrame_MsgProc );

	m_pID_BUTTON_AddQuestEntrust->SetEnable(false);

	ClearShowInfo();
	ClearTaskPanel();
	Refresh();

    _SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Task::_UnLoadUI()
{
	SaveCollapseInfo();
	SaveTrackInfo();
	m_vTrackList.clear();
	m_finishPics.Clear();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Task.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Task::_IsVisable()
{
	if( !m_pID_FRAME_Task )
		return false;
	return m_pID_FRAME_Task->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Task::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Task )
		return;
	m_pID_FRAME_Task->SetVisable( bVisable );
	if (bVisable)
	{
		/*
		 *	Author 2012-12-4 zhuxincong
		 *	DESC: 先判断有多少任务，如果只有一个的话，默认就显示第一个
		 */
		 Refresh(true);
		
	}
	else
	{
		RecordCollapseInfo();
	}
}

void CUI_ID_FRAME_Task::Refresh(bool bClear )
{
    if( !m_pID_FRAME_Task && s_CUI_ID_FRAME_TRACK.IsUILoad() )
        UpdateTrackInfo();

	if (!m_pID_FRAME_Task || !m_pID_LIST_Task)
		return;

	m_dwLastRefreshTime = HQ_TimeGetTime();

    m_pID_LIST_Task->BeginUpdate();
	m_pID_LIST_Task->Clear();

	bool isLastSelectionExisted = false;
	std::vector<CPlayerRole::QuestInfo*>& vtQuest = thePlayerRole.GetActiveQuestInfo();
	bool isCurrenting = m_pID_CHECKBOX_Task1->IsChecked();
	SQuest *pQuest = NULL;
	ControlList::S_List stList;

	std::vector<int> mapIdSet;
	std::multimap<int,int> mapSet;
	mapSet.clear();
	mapIdSet.clear();
	int nTaskCount = 0;

	int Array[] = {0,2,10,1};	
	for(int j =0;j<sizeof(Array)/sizeof(int);++j)
	{
		int i = Array[j];
		if (!isCurrenting)
		{
			bool bHide = false;
			for (int z = 0; z < m_arrHideTaskTypeInAccecptableTask.size();++z)
			{
				if (m_arrHideTaskTypeInAccecptableTask[z] == i)
				{
					bHide = true;
					break;
				}
			}
			if (bHide)
			{
				continue;
			}
		}
		bool hasFirst = false;
		for ( int n=0; n<vtQuest.size(); n++ )
		{
			pQuest = theQuestManager.GetQuest( vtQuest[n]->nQuestId );
			if ( !pQuest )
			{
				continue;
			}
			if (pQuest->chQuestType != i )
			{
				continue;
			}
			//不是自己国家的任务不显示
			if (pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry())
			{
				continue;
			}
			//本场景任务
			if (m_pID_CHECKBOX_Jin->IsChecked())
			{
				CWorldTile* pCurrTile = CURRENTTILE;
				if(!pCurrTile || pQuest->MapId!=pCurrTile->GetMapId())
				{
					continue;
				}
				
			}

			CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( vtQuest[n]->nQuestId );
			if( !pInfo )
			{
				continue;
			}
			if (theQuestManager.IsQuestActive(pInfo->chState))
			{
			}

			if (isCurrenting)
			{
				if (!theQuestManager.IsQuestActive(pInfo->chState))
				{
					continue;
				}
			}
			else
			{
				if ((!pQuest->CanDisplay )||
					pInfo->nQuestId < dr_MinQuestId || (!pQuest->bDisplayInCanAccept))
				{//高于5000不提示可接任务
					continue;
				}
				if(!theQuestManager.IsQuestNotGain(pInfo->chState))
				{
					continue;
				}
			}

			if(m_CurrTabType != eCurr_Task)
			{
				std::string content;
				content.clear();
				const NpcCoordInfo *pNpcInfo = NULL;
				//if(pInfo->bDone)
				//	pNpcInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId);
				//else

				pNpcInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);
				if(pNpcInfo)
					content = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str());

				int nMapIdInMyCountry = NpcCoord::RetriveMapIdFromQuest(pQuest->Id, content);
				mapSet.insert(make_pair(nMapIdInMyCountry,pQuest->Id));
				std::vector<int>::iterator it = find(mapIdSet.begin(),mapIdSet.end(),nMapIdInMyCountry);
				if(it == mapIdSet.end())
					mapIdSet.push_back(nMapIdInMyCountry);
			}
			else
			{
				if (!hasFirst)
				{
					stList.m_nHiberarchy = 0;
					bool bCollapse = false;
					for(int z = 0; z < m_RecordArr[m_CurrTabType].size(); ++z )
					{
						if (m_RecordArr[m_CurrTabType][z].m_nSubType == i)
						{
							bCollapse = m_RecordArr[m_CurrTabType][z].m_isCollapse;
						}
					}
					stList.m_bCollapse = bCollapse;
					stList.SetData(m_QuestTypeString[i],i);
					m_pID_LIST_Task->AddItem(&stList);
					hasFirst = true;
				}
				AddTaskItem(pQuest);
				++nTaskCount;
			}

			if (m_nCurrSelectedQuest == pQuest->Id)
			{
				isLastSelectionExisted = true;
			}
			//zhuxincong 12.5 在接到新任务之后，几个text还是会显示之前任务的内容是因为没有把任务ID赋值过去
			else
			{
				m_nCurrSelectedQuest = pQuest->Id;
				isLastSelectionExisted = true;
			}

// 			col = theHeroGame.GetPlayerMgr()->GetQuestRankColor(pQuest);
// 
//             // 任务显示等级     added by ZhuoMeng.Hu		[11/24/2010]
//             char szTaskLevel[MAX_PATH] = {0};
//             char szTaskName[MAX_PATH] = {0};
//             int nNeedlevel = pQuest->HintLevelMin;
//             MeSprintf_s( szTaskLevel, sizeof( szTaskLevel ) - 1, theXmlString.GetString( eText_Quest_NeedLevel ), nNeedlevel );
// 
// 			CPlayerRole::QuestInfo* pQuestInfo = thePlayerRole.FindQuestInfoById( pQuest->Id);
// 			if( !pQuestInfo )
// 				continue;
// 
//             int nTaskType = pQuest->chQuestType;
// 			if (pQuestInfo->bDone )
// 				MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s%s%s%s",theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Done));
// 			else
// 				MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s%s%s",theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName() );
// 
// 			stList.SetData( szTaskName, pQuest->Id, NULL, col );
// 
// 			stList.UseSelColor = false;
// 			stList.m_nHiberarchy = 1;
// 			m_pID_LIST_Task->AddItem( &stList,NULL, false);
		}
	}

	for (int i = SQuest::Type_Main; i < SQuest::Type_End; ++i)//按特殊顺序来处理
	{
		if((i == SQuest::Type_Main || i == SQuest::Type_Campaign || i == SQuest::Type_Gut || i == SQuest::Type_Lateral))
			continue;

		if (!isCurrenting)
		{
			bool bHide = false;
			for (int z = 0; z < m_arrHideTaskTypeInAccecptableTask.size();++z)
			{
				if (m_arrHideTaskTypeInAccecptableTask[z] == i)
				{
					bHide = true;
					break;
				}
			}
			if (bHide)
			{
				continue;
			}
		}
		bool hasFirst = false;
		for ( int n=0; n<vtQuest.size(); n++ )
		{
			pQuest = theQuestManager.GetQuest( vtQuest[n]->nQuestId );
			if ( !pQuest )
			{
				continue;
			}
			if (pQuest->chQuestType != i )
			{
				continue;
			}
			//不是自己国家的任务不显示
			if (pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry())
			{
				continue;
			}
			//本场景任务
			if (m_pID_CHECKBOX_Jin->IsChecked())
			{
				CWorldTile* pCurrTile = CURRENTTILE;
				if(!pCurrTile || pQuest->MapId!=pCurrTile->GetMapId())
				{
					continue;
				}
				
			}

			CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( vtQuest[n]->nQuestId );
			if( !pInfo )
			{
				continue;
			}
			if (theQuestManager.IsQuestActive(pInfo->chState))
			{
			}

			if (isCurrenting)
			{
				if (!theQuestManager.IsQuestActive(pInfo->chState))
				{
					continue;
				}
			}
			else
			{
				if ((!pQuest->CanDisplay )||
					pInfo->nQuestId < dr_MinQuestId || (!pQuest->bDisplayInCanAccept))
				{//高于5000不提示可接任务
					continue;
				}
				if(!theQuestManager.IsQuestNotGain(pInfo->chState))
				{
					continue;
				}
			}

			if(m_CurrTabType != eCurr_Task)
			{
				std::string content;
				content.clear();
				const NpcCoordInfo *pNpcInfo = NULL;
				//if(pInfo->bDone)
				//	pNpcInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId);
				//else

				pNpcInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);
				if(pNpcInfo)
					content = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str());

				int nMapIdInMyCountry = NpcCoord::RetriveMapIdFromQuest(pQuest->Id, content);
				mapSet.insert(make_pair(nMapIdInMyCountry,pQuest->Id));
				std::vector<int>::iterator it = find(mapIdSet.begin(),mapIdSet.end(),nMapIdInMyCountry);
				if(it == mapIdSet.end())
					mapIdSet.push_back(nMapIdInMyCountry);
			}
			else
			{
				if (!hasFirst)
				{
					stList.m_nHiberarchy = 0;
					bool bCollapse = false;
					for(int z = 0; z < m_RecordArr[m_CurrTabType].size(); ++z )
					{
						if (m_RecordArr[m_CurrTabType][z].m_nSubType == i)
						{
							bCollapse = m_RecordArr[m_CurrTabType][z].m_isCollapse;
						}
					}
					stList.m_bCollapse = bCollapse;
					stList.SetData(m_QuestTypeString[i],i);
					m_pID_LIST_Task->AddItem(&stList);
					hasFirst = true;
				}
				AddTaskItem(pQuest);
				++nTaskCount;
			}

			if (m_nCurrSelectedQuest == pQuest->Id)
			{
				isLastSelectionExisted = true;
			}
			//zhuxincong 12.5 在接到新任务之后，几个text还是会显示之前任务的内容是因为没有把任务ID赋值过去
			else
			{
				m_nCurrSelectedQuest = pQuest->Id;
				isLastSelectionExisted = true;
			}

// 			col = theHeroGame.GetPlayerMgr()->GetQuestRankColor(pQuest);
// 
//             // 任务显示等级     added by ZhuoMeng.Hu		[11/24/2010]
//             char szTaskLevel[MAX_PATH] = {0};
//             char szTaskName[MAX_PATH] = {0};
//             int nNeedlevel = pQuest->HintLevelMin;
//             MeSprintf_s( szTaskLevel, sizeof( szTaskLevel ) - 1, theXmlString.GetString( eText_Quest_NeedLevel ), nNeedlevel );
// 
// 			CPlayerRole::QuestInfo* pQuestInfo = thePlayerRole.FindQuestInfoById( pQuest->Id);
// 			if( !pQuestInfo )
// 				continue;
// 
//             int nTaskType = pQuest->chQuestType;
// 			if (pQuestInfo->bDone )
// 				MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s%s%s%s",theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Done));
// 			else
// 				MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s%s%s",theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName() );
// 
// 			stList.SetData( szTaskName, pQuest->Id, NULL, col );
// 
// 			stList.UseSelColor = false;
// 			stList.m_nHiberarchy = 1;
// 			m_pID_LIST_Task->AddItem( &stList,NULL, false);
		}
	}

	SetTaskNum(nTaskCount);  //设置任务数量

	if(mapIdSet.size() > 0)
	{
		for (int i = 0;i < mapIdSet.size(); ++i)
		{
			CWorldTile* pWorldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(mapIdSet[i]);
			if(!pWorldTile)
				continue;

			char szWord[256] = {0};
			MeSprintf_s(szWord,sizeof(szWord)," %s",pWorldTile->GetTileName());

			ControlList::S_List stItem;
			stItem.UseSelColor = false;

			stItem.clear();
			stItem.m_nHiberarchy = 0;
			stItem.SetData(szWord,mapIdSet[i]);
			bool bCollapse = false;
			for(int z = 0; z < m_RecordArr[m_CurrTabType].size(); ++z )
			{
				if (m_RecordArr[m_CurrTabType][z].m_nSubType == mapIdSet[i])
				{
					bCollapse = m_RecordArr[m_CurrTabType][z].m_isCollapse;
				}
			}
			stItem.m_bCollapse = bCollapse;

			m_pID_LIST_Task->AddItem(&stItem,NULL,true);

			std::multimap<int,int>::size_type nSize = mapSet.count(mapIdSet[i]);
			if(nSize == 0)
				continue;

			typedef std::multimap<int,int>::iterator IterMap;

			std::pair<IterMap,IterMap> pairResult = mapSet.equal_range(mapIdSet[i]);
			for(IterMap iter = pairResult.first;iter != pairResult.second;++iter)
			{
				int nQuestId = iter->second;

				SQuest *pQuest = theQuestManager.GetQuest( nQuestId );
				CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
				if( !pQuest || !pInfo )
					continue;

				AddTaskItem(pQuest);
			}
		}
	}


    if( m_pID_LIST_Task->GetListItemCnt() > m_pID_LIST_Task->GetItemShowCount() )
    {
        ControlScrollBar* pScrollBar = m_pID_LIST_Task->GetScrollBar();
        if( pScrollBar )
        {
           // pScrollBar->SetMaxValue(m_pID_LIST_Task->GetTotalHeight() - m_pID_LIST_Task->GetHeight()/*m_pID_LIST_Task->GetListItemCnt() - m_pID_LIST_Task->GetItemShowCount()*/ );
           // pScrollBar->SetStepValue( 1 );
		   pScrollBar->SetValue(0);
        }
    }

    m_pID_LIST_Task->EndUpdate();
	RefreshFinishPic();

	if (!m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetListItemCnt() > 2)
	{
		m_pID_LIST_Task->SetCurSelIndex(2);
	}
	if (m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		if ( m_pID_CHECKBOX_Task1->IsChecked())
		{
			int id = m_pID_LIST_Task->GetCurSelItem()->m_nID;
			std::vector<int>::iterator itr = std::find(m_vNotTrackList.begin(), m_vNotTrackList.end(), id);
			m_pID_BUTTON_Zhuizong->SetVisable(itr != m_vNotTrackList.end());
			m_pID_BUTTON_Quxiao->SetVisable(itr == m_vNotTrackList.end());
		}
		m_nCurrSelectedQuest = (m_pID_LIST_Task->GetCurSelItem()->m_nID);
		if (-1 == m_nCurrSelectedQuest)
		{
#ifdef _CLIENT_
			char temp[2048];
			sprintf_s(temp,2048,"任务序列号获取失败");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
#endif
		}
	}
	else
	{
		if (!isLastSelectionExisted)
		{
			m_nCurrSelectedQuest = -1;
		}
	}

	//UITask_ShowInfo(m_nCurrSelectedQuest);
	UpdateTaskPanel( m_nCurrSelectedQuest );
	UpdateTrackInfo();
}

void CUI_ID_FRAME_Task::SetTaskNum(int nTaskNum)
{
	if(m_CurrTabType == eCurr_Task)
		m_pID_TEXT_Amount->SetText(nTaskNum);
}


void CUI_ID_FRAME_Task::AddTaskItem(SQuest *pQuest)
{
	if(!pQuest)
		return;

	ControlList::S_List stList;
	stList.clear();

	col = theHeroGame.GetPlayerMgr()->GetQuestRankColor(pQuest);

	// 任务显示等级     added by ZhuoMeng.Hu		[11/24/2010]
	char szTaskLevel[MAX_PATH] = {0};
	char szTaskName[MAX_PATH] = {0};
	std::string strTaskName;
	strTaskName.clear();
	int nNeedlevel = pQuest->HintLevelMin;
	MeSprintf_s( szTaskLevel, sizeof( szTaskLevel ) - 1, theXmlString.GetString( eText_Quest_NeedLevel ), nNeedlevel );

	CPlayerRole::QuestInfo* pQuestInfo = thePlayerRole.FindQuestInfoById( pQuest->Id);
	if( !pQuestInfo )
		return;

	int nTaskType = pQuest->chQuestType;
	if(m_CurrTabType == eCurr_Task)
	{
		if (pQuestInfo->bDone)
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s %s%s", szTaskLevel, pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Done));
		else if(pQuestInfo->chState == QuestManager::eQuestFrozen)
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s %s%s", szTaskLevel, pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Frozen));
		else
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s %s", szTaskLevel, pQuest->GetQuestName() );
	}
	else
	{
		if (pQuestInfo->bDone)
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, theXmlString.GetString(eText_Quest_TaskNone)/*"【%s】%s%s"*/,theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName());
		else if(pQuestInfo->chState == QuestManager::eQuestFrozen)
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, "%s %s%s", szTaskLevel, pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Frozen));
		else
			MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, theXmlString.GetString(eText_Quest_TaskNone)/*"【%s】%s%s"*/,theXmlString.GetString( eText_QuestType_1 + nTaskType ), szTaskLevel, pQuest->GetQuestName());
	}

	strTaskName = szTaskName;
	SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_VarLimit);
	if (pRequire)
	{
		char szWord[256] = {0};
		MeSprintf_s(szWord,sizeof(szWord),"(%d/%d)",thePlayerRole.GetVariableValue( pRequire->wVar ),pRequire->MaxNum);
		strTaskName += szWord;
	}

	stList.SetData( strTaskName.c_str()/*szTaskName*/, pQuest->Id, NULL, col );

	stList.UseSelColor = false;
	stList.m_nHiberarchy = 1;
	m_pID_LIST_Task->AddItem( &stList,NULL, true);
}

bool CUI_ID_FRAME_Task::UITask_ShowInfo(int questId)
{
	ClearShowInfo();
	ClearTaskPanel();
	if (-1 == questId)
	{
		return true;
	}
	//
	SQuest *pQuest = theQuestManager.GetQuest( questId );
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( questId );
	if ( !pQuest || !pInfo )
	{
#ifdef _CLIENT_
		char temp[2048];
		sprintf_s(temp,2048,"%d任务获取失败！",questId);
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
#endif
		return false;
	}
	std::string strNeedItemInfo;

	// 任务品质
// 	switch (pQuest->RankId)
// 	{
// 	case SQuest::eQuestRank_Nor:
// 		m_pID_PICTURE_RankId0->SetVisable(true);
// 		break;
// 	case SQuest::eQuestRank_Nic:
// 		m_pID_PICTURE_RankId1->SetVisable(true);
// 		break;
// 	case SQuest::eQuestRank_Exc:
// 		m_pID_PICTURE_RankId2->SetVisable(true);
// 		break;
// 	case SQuest::eQuestRank_Gold:
// 		m_pID_PICTURE_RankId3->SetVisable(true);
// 		break;
// 	case SQuest::eQuestRank_Legend:
// 		m_pID_PICTURE_RankId4->SetVisable(true);
// 		break;
// 	}

	ControlList::S_List	stItem;
	stItem.UseSelColor = false;

	std::string strTaskTarget;
	strTaskTarget.clear();

	if (m_pID_CHECKBOX_Task1->IsChecked())
	{
		if (pQuest->stCommitRequirement.empty() || !pInfo->bDone)
		{
 			std::string strInfo = pQuest->GetQuestStateInfo();
			if(!strInfo.empty())
			{
				NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
				// 			AddInfoToList(strInfo, m_pID_LIST_Taskstate,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
				strTaskTarget += "\n    ";
				strTaskTarget += strInfo;
			}
		}
		else
		{
			std::string format = theXmlString.GetString(eText_AckNpc);
			int npcId = pQuest->ReplyTargetId;
			const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoord(npcId);
			std::string pNpcName ;
			if (pNpcInfo)
			{
				pNpcName = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str()).c_str();
			}
			char szInfo[dr_MaxQuestDesc] = {0};
			sprintf( szInfo, format.c_str(), pNpcName.c_str() );
			std::string strInfo = szInfo;
			NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
			
			strTaskTarget += "\n    ";
			strTaskTarget += strInfo;
			//AddInfoToList(strInfo, m_pID_LIST_Taskstate,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
		}

		std::string strNeedItem;
		strNeedItem.clear();

		GetNeedItemInfo(pQuest,strNeedItem);
		strTaskTarget += strNeedItem;

		SQuestRequirement *pRequirement = NULL;

		for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
		{
			stItem.clear();
			pRequirement = &pQuest->stCommitRequirement[i];
			char szInfo[256] = "";
			switch( pRequirement->byType )
			{
			case SQuest::eRequirement_Item:
				{
					ItemDefine::SItemCommon* pItemDetail = NULL;
					pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
					if( pItemDetail )
					{
						int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
						{
							nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
							if (nItemCount < 1)
								nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
						}

						//需要任务物品
						sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedItem),pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );

						// 增加Item寻路tips
// 						const NpcCoordInfo *pNpcInfo =  NpcCoord::getInstance()->getNpcCoord(pItemDetail->GetItemName());
// 						FillMapPosTip(pNpcInfo,&stItem);
					}
				}
				break;
			case SQuest::eRequirement_Monster:
				{
					int nVar = 0;
					CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
					if( pVariableInfo )
						nVar = pVariableInfo->chState;
					ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
					if (pMonstor)
					{
						sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedMonster),pMonstor->GetName(), nVar, pRequirement->MaxNum );
// 						const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(pMonstor->GetName());
// 						FillMapPosTip(pNpcInfo,&stItem);
					}
				}
				break;
			case SQuest::eRequirement_Action:
				{
					int nVar = 0;
					CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
					if( pVariableInfo )
						nVar = pVariableInfo->chState;
					sprintf( szInfo, "%s (%ld/%ld)", theXmlString.GetString(pRequirement->Value), nVar, pRequirement->MaxNum );
				}break;
			case SQuest::eRequirement_Var:
				{
					int nVar = 0;
					CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
					if( pVariableInfo )
						nVar = pVariableInfo->chState;

					if(nVar == pRequirement->MaxNum)
						continue;

					sprintf(szInfo, "%s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
				}
				break;
			default:
				break;
			}
			/*if (pQuest->IsSingleRequirement)
			{
				break;
			}*/
			/*std::string strInfo = szInfo;
			NpcCoord::getInstance()->addNpcHyber(strInfo, NpcHyberLeft, NpcHyberRight);
			stItem.SetData( strInfo.c_str() );
			stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );*/
		}
	}
	else
	{
		char temp[1024];
		NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(pQuest->AcceptTargetId);
		if (NpcName)
		{
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(NpcName->mapId);
			if (pTile)
			{
				sprintf(temp,theXmlString.GetString(eClient_AcceptNPC),pTile->GetTileName(),NpcName->name.c_str());
				//AddInfoToList(temp, m_pID_LIST_Taskstate,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));

				strTaskTarget += "\n    ";
				strTaskTarget += temp;
			}
		}
	}

	std::string strTaskInfo;
	strTaskInfo.clear();

	//strTaskInfo += theXmlString.GetString(eText_Quest_Task);
	//strTaskInfo += pQuest->GetQuestName();
	strTaskInfo += "\n";
	strTaskInfo += "\n";

	//任务目标
	strTaskInfo += theXmlString.GetString(eText_Quest_TaskTarget);
	strTaskInfo += "    ";
	strTaskInfo += strTaskTarget;
	strTaskInfo += "\n";

	strTaskInfo += "\n";
	//任务描述
	strTaskInfo += theXmlString.GetString(eText_Quest_TaskDes);
	strTaskInfo += "\n";
	strTaskInfo += "    ";
	strTaskInfo += pQuest->GetQuestInfo();
	strTaskInfo += "\n";

	//任务奖励
	std::string strRewardItem;
	strRewardItem.clear();
	GetRewardItemInfo(pQuest,strRewardItem);
	if(m_pID_LISTIMG_Reward->GetNullItem() != 0)
	{
		strTaskInfo += "\n";
		strTaskInfo += theXmlString.GetString(eText_Quest_TaskReward);
		strTaskInfo += "\n";

		m_pID_TEXT_TaskInfo->SetText(strTaskInfo);
		int nTotalLines = m_pID_TEXT_TaskInfo->GetMaxLines();

		RECT rc;
		m_pID_TEXT_TaskInfo->GetRectSize(&rc);

		//计算高度
		int nHeight = (nTotalLines + 1) * (FontSystem::GetFontHeight(m_pID_TEXT_TaskInfo->GetFontIndex()) + m_pID_TEXT_TaskInfo->GetOffsetHeight());

		ModifyRewardItem(rc.top + nHeight,rc.left);
		strTaskInfo += "\n\n\n";
	}


	strTaskInfo += strRewardItem;

	//NpcCoord::getInstance()->addNpcHyber(strTaskInfo, NpcHyberLeft, NpcHyberRight);

// 	std::string strIntro = pQuest->GetQuestInfo();
// 
// 	AddInfoToTaskInfo(strIntro);

	//std::string strRewardItem;
	//GetRewardItemInfo(pQuest,strRewardItem);

	std::vector<UiCallbackDataBase*> CallBackDataArr;
	NpcCoord::getInstance()->addNpcHyberForText(strTaskInfo,NpcCoord::eQuestId,questId,pQuest->ReplyTargetId,&CallBackDataArr);
	std::string strInfo;
	strInfo.clear();
	strInfo += theXmlString.GetString(eText_Quest_Task);
	strInfo += pQuest->GetQuestName();

	strTaskInfo.insert(0,strInfo.c_str());
	m_pID_TEXT_TaskInfo->SetText(strTaskInfo.c_str(),0,&CallBackDataArr);

	//AddInfoToTaskInfo(strTaskInfo,pQuest->Id);
	//m_pID_TEXT_TaskInfo->SetText(strTaskInfo);
	m_pID_TEXT_TaskInfo->SetVisable(true);
	return true;
}

void CUI_ID_FRAME_Task::RefreshTaskTrack()
{
	if (!s_CUI_ID_FRAME_TRACK.IsUILoad())
		return;

	if (!m_bTaskInfoLoaded)
		return;

	if( !IsDirty() )
		return;

	SetDirty( false );

	std::vector<CPlayerRole::QuestInfo*>& vtQuest = thePlayerRole.GetActiveQuestInfo();

	SQuest *pQuest = NULL;
	for ( int n=vtQuest.size() - 1; n>=0; n-- )
	{
		CPlayerRole::QuestInfo* pInfo = vtQuest[n];
		if( !pInfo )
		{
			continue;
		}
		pQuest = theQuestManager.GetQuest( pInfo->nQuestId );
		if ( !pQuest )
		{
			std::list<int>::iterator itr = std::find(m_vTrackList.begin(), m_vTrackList.end(), pQuest->Id);
			if (itr != m_vTrackList.end())
				m_vTrackList.erase(itr);
			continue;
		}

		std::list<int>::iterator itr = std::find(m_vTrackList.begin(), m_vTrackList.end(), pQuest->Id);
		bool bFind = itr != m_vTrackList.end();

		if ( pInfo->chState == 1 && !bFind)
			m_vTrackList.push_front(pQuest->Id);
		else if (pInfo->chState != 1 && bFind)
			m_vTrackList.erase(itr);
	}

	for (std::list<int>::iterator itr = m_vTrackList.begin(); itr != m_vTrackList.end(); )
	{
		bool bFind = false;
		for (int n=0; n<vtQuest.size(); ++n)
		{
			CPlayerRole::QuestInfo* pInfo = vtQuest[n];
			if( pInfo && pInfo->nQuestId == *itr)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
			itr = m_vTrackList.erase(itr);
		else
			++itr;
	}

	UpdateTrackInfo();
}

void CUI_ID_FRAME_Task::UpdateTrackInfo()
{
    if( s_CUI_ID_FRAME_TRACK.IsMinisized() )
        return;

	std::map<int, int> collapseStatus;
	if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
	{
		for (int i = 0; i < s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->GetListItemCnt(); ++i)
		{
			ControlList::S_List* pItem = s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->GetListItem(i);
			if (pItem && pItem->m_nHiberarchy == 0)
				collapseStatus[pItem->m_nID] = pItem->m_bCollapse;
		}
		s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->Clear(false);
	}

	if( s_CUI_ID_FRAME_TRACK.GetLIST_Finish() )
		s_CUI_ID_FRAME_TRACK.GetLIST_Finish()->Clear();
	s_CUI_ID_FRAME_TRACK.GetfinishPicGroup().SetVisible(false);

	ControlList::S_List	stItem;
	stItem.UseSelColor = false;

	for (std::vector<int>::iterator itr=m_vNotTrackList.begin(); itr!=m_vNotTrackList.end(); )
	{
		SQuest *pQuest = theQuestManager.GetQuest( *itr );
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( *itr );
		if( !pQuest || !pInfo )
		{
			itr = m_vNotTrackList.erase(itr++);
			continue;
		}

		if( pInfo->chState == 0 )
		{
			itr = m_vNotTrackList.erase(itr++);
			continue;
		}

		if (pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry())
		{
			itr = m_vNotTrackList.erase(itr++);
			continue;
		}

		++itr;
	}

	bool bMain = false;
	DWORD dwColor = 0;
	//对任务进行排序
	std::stable_sort(m_vTrackList.begin(),m_vTrackList.end(),SortByQuestID);

	for(std::list<int>::iterator itr=m_vTrackList.begin(); itr!=m_vTrackList.end(); itr++)
	{
		SQuest *pQuest = theQuestManager.GetQuest( *itr );
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( *itr );
		if( !pQuest || !pInfo ||(pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry()))
		{
			m_vTrackList.erase(itr++);
			UpdateTrackInfo();
			break;
		}

		if( pInfo->chState == 0 )
		{
			m_vTrackList.erase(itr++);
			UpdateTrackInfo();
			break;
		}

		std::vector<int>::iterator itrNot;
		itrNot = std::find(m_vNotTrackList.begin(), m_vNotTrackList.end(), pQuest->Id);
		if (itrNot != m_vNotTrackList.end())
			continue;

		UpdateTrackInfoItem(pQuest,pInfo->bDone,collapseStatus);
		if(pQuest->chQuestType == SQuest::Type_Main)
			bMain = true;
	}

	//显示所有可接主线任务
	if(!bMain)
	{
		if(!theHeroGame.GetPlayerMgr()->GetMe())
			return;

		std::vector<CPlayerRole::QuestInfo*>& vtQuest = thePlayerRole.GetActiveQuestInfo();
		SQuest *pQuest = NULL;
		for ( int n=vtQuest.size() - 1; n>=0; n-- )
		{
			CPlayerRole::QuestInfo* pInfo = vtQuest[n];
			if( !pInfo )
				continue;

			pQuest = theQuestManager.GetQuest( pInfo->nQuestId );
			if(!pQuest || (pQuest->Country!=0 && pQuest->Country!=thePlayerRole.GetCountry()) )
				continue;

			if(pQuest->chQuestType == SQuest::Type_Main)
			{
				char szTaskInfo[256] = {0};
				MeSprintf_s(szTaskInfo,sizeof(szTaskInfo),"[%s]%s",theXmlString.GetString(eText_QuestType_1),pQuest->GetQuestName());
				
				static short shNone = 0;

				ControlList::S_List stItem;
				stItem.m_nHiberarchy = 0;
				stItem.SetData(szTaskInfo,pQuest->Id,(void*)shNone,Color_Config.getColor( CC_TASK_NAME ));
				if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
					s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem(&stItem,NULL,false);

				szTaskInfo[0] = '\0';
				//获得地图名
				std::string content;
				content.clear();
				const NpcCoordInfo *pNpcInfo = NULL;
				pNpcInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);
				
				if(pNpcInfo)
					content = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str());

				int nMapIdInMyCountry = NpcCoord::RetriveMapIdFromQuest(pQuest->Id, content);
				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapIdInMyCountry);
				if (pTile)
				{
					MeSprintf_s(szTaskInfo,sizeof(szTaskInfo),theXmlString.GetString(eClient_AcceptNPC),pTile->GetTileName(),content.c_str());
					
					ControlList *pList = s_CUI_ID_FRAME_TRACK.GetLIST_TRACK();
					if(!pList)
						return;

					std::string strInfo = szTaskInfo;
					AddInfoToList(strInfo, pList,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)),pInfo->nQuestId,pQuest->AcceptTargetId,false);

					//stItem.SetData(szTaskInfo,pQuest->Id);
					//if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
					//	s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem(&stItem,NULL,false);
				}
			}
		}

	}
	if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
		s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->SetScrollValue(0);

	s_CUI_ID_FRAME_TRACK.RefreshTask();
}

void CUI_ID_FRAME_Task::UpdateTrackInfoItem(SQuest *pQuest,bool bDone,std::map<int, int> &collapseStatus)
{
	if(!pQuest)
		return;

	static short none = 0;
	DWORD dwColor = 0;

	ControlList::S_List	stItem;	
	stItem.UseSelColor = false;
	
	stItem.clear();
	stItem.m_nHiberarchy = 0;
	if (collapseStatus.find(pQuest->Id) != collapseStatus.end())
		stItem.m_bCollapse = collapseStatus[pQuest->Id];

	// 任务追踪显示任务类型     added by ZhuoMeng.Hu		[11/24/2010]
	//设置任务标题
	char szTaskName[MAX_PATH] = {0};
	std::string strTaskName;
	strTaskName.clear();
	int nTaskType = pQuest->chQuestType;
	if(bDone)
		MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, theXmlString.GetString(eText_Quest_TaskTrackDone)/*"【%s】%s%s"*/, theXmlString.GetString( eText_QuestType_1 + nTaskType ), pQuest->GetQuestName(),theXmlString.GetString(eText_Quest_Done) );
	else
		MeSprintf_s( szTaskName, sizeof( szTaskName ) - 1, theXmlString.GetString(eText_Quest_TaskTrackNone)/*"【%s】%s"*/, theXmlString.GetString( eText_QuestType_1 + nTaskType ), pQuest->GetQuestName() );

	strTaskName = szTaskName;
	SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_VarLimit);
	if (pRequire)
	{
		char szWord[256] = {0};
		MeSprintf_s(szWord,sizeof(szWord),"(%d/%d)",thePlayerRole.GetVariableValue( pRequire->wVar ),pRequire->MaxNum);
		strTaskName += szWord;
	}
	stItem.SetData( strTaskName.c_str(), pQuest->Id, (void*)bDone, Color_Config.getColor( CC_TASK_NAME ) );

	stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
	if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
		s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem( &stItem, NULL,false );


	char szInfo[dr_MaxQuestDesc] = {0};
	if (bDone)
	{
		if (pQuest->stCommitRequirement.empty())
		{
			std::string format = pQuest->GetQuestStateInfo();
			if(!format.empty())
			{
				/*
				int npcId = pQuest->ReplyTargetId;
				std::vector<UiCallbackDataBase*> CallBackDataArr;
				NpcCoord::getInstance()->addNpcHyberForText(format, NpcCoord::eQuestId,pQuest->Id,&CallBackDataArr,true);
				stItem.clear();
				stItem.m_nHiberarchy = 1;
// 				const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(npcId);
// 				AddMapName(pNpcInfo,format);
				stItem.SetData( format.c_str(), pQuest->Id, (void*)none,  Color_Config.getColor(CC_TASK_DONE) );
				stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
// 				FillMapPosTip(pNpcInfo,&stItem);
				if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
					s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem( &stItem,&CallBackDataArr, false );
				*/

				if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
				     AddInfoToList(format,s_CUI_ID_FRAME_TRACK.GetLIST_TRACK(),Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)),pQuest->Id,pQuest->ReplyTargetId,true);
			}
		}
		else
		{
			std::string format = "";
			int npcId = pQuest->ReplyTargetId;
			const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoord(npcId);
			//现在镜像地图不是完整的使用，暂时把task track 中的寻路超链接改为直接从自身地图读取  by vvx 2012.9.28
			//const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(npcId);
			format += theXmlString.GetString(eText_AckNpc);
			std::string pNpcName ;
			if (pNpcInfo)
			{
				pNpcName = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str()).c_str();
			}
			sprintf( szInfo, format.c_str(), pNpcName.c_str() );
			format = szInfo;
			/*
			std::vector<UiCallbackDataBase*> CallBackDataArr;
			NpcCoord::getInstance()->addNpcHyberForText(format,NpcCoord::eQuestId,pQuest->Id,&CallBackDataArr,true);
// 			NpcCoord::getInstance()->addNpcHyber(format, NpcHyberLeft, NpcHyberRight);
// 			AddMapName(pNpcInfo,format);
			stItem.clear();
			stItem.m_nHiberarchy = 1;
			stItem.SetData( format.c_str(), pQuest->Id, (void*)none,  Color_Config.getColor(CC_TASK_DONE) );
			stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
// 			FillMapPosTip(pNpcInfo,&stItem);
			if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
				s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem( &stItem,&CallBackDataArr, false );
			*/

			if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
				AddInfoToList(format,s_CUI_ID_FRAME_TRACK.GetLIST_TRACK(),Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)),pQuest->Id,pQuest->ReplyTargetId,true);
		}
		return;
	}

	std::string strTarget = pQuest->GetQuestStateInfo();
	if(!strTarget.empty())
	{
		stItem.clear();
		std::string format = "";
		format += strTarget;
/*
		std::vector<UiCallbackDataBase*> CallBackDataArr;
		NpcCoord::getInstance()->addNpcHyberForText(format,NpcCoord::eQuestId,pQuest->Id,&CallBackDataArr,true);
// 		NpcCoordInfo* pNpcInfo = NULL;
// 		NpcCoord::getInstance()->addNpcHyber(format, NpcHyberLeft, NpcHyberRight,&pNpcInfo);
// 		AddMapName(pNpcInfo,format);
// 		FillMapPosTip(pNpcInfo,&stItem);
		stItem.m_nHiberarchy = 1;
		stItem.SetData( format.c_str(), pQuest->Id, (void*)none,  Color_Config.getColor(CC_TASK_NONE) );
		stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
		if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
			s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem( &stItem,&CallBackDataArr, false );
*/
		if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
			AddInfoToListName(format,s_CUI_ID_FRAME_TRACK.GetLIST_TRACK(),Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)),pQuest->Id,true);
	}

	//增加需要的物品
	SQuestRequirement *pRequirement = NULL;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		bool bShowMapName = false;

		stItem.clear();
		pRequirement = &pQuest->stCommitRequirement[i];
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
					}
					if(nItemCount == pRequirement->MaxNum)
						continue;

					//需要任务物品
					sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedItem),pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );
					// 增加Item寻路tips
// 					const NpcCoordInfo *pNpcInfo =  NpcCoord::getInstance()->getNpcCoord(pItemDetail->GetItemName());
// 					FillMapPosTip(pNpcInfo,&stItem);
				}
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (pMonstor)
				{
					if(nVar == pRequirement->MaxNum)
						continue;

					//需要
					sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedMonster),pMonstor->GetName(), nVar, pRequirement->MaxNum );
// 					const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(pMonstor->GetName());
// 					FillMapPosTip(pNpcInfo,&stItem);
					//
					bShowMapName = true;
				}	

			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				if(nVar == pRequirement->MaxNum)
					continue;

				sprintf( szInfo, "%s (%ld/%ld)", theXmlString.GetString(pRequirement->Value),
					nVar, pRequirement->MaxNum );
			}break;
		case SQuest::eRequirement_Var:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				if(nVar == pRequirement->MaxNum)
					continue;
				
				sprintf(szInfo, "%s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
				bShowMapName = true;
			}
			break;
		default:
			break;
		}
		if(bDone)
		{
			dwColor = Color_Config.getColor(CC_TASK_DONE);
		}
		else
		{
			dwColor = Color_Config.getColor(CC_TASK_NONE); 
		}
		NpcCoordInfo *pNpcInfo = NULL;
		std::string str = szInfo;
		/*
		std::vector<UiCallbackDataBase*> CallBackDataArr;
		NpcCoord::getInstance()->addNpcHyberForText(str, NpcCoord::eQuestId,pQuest->Id,&CallBackDataArr,false);
// 		NpcCoord::getInstance()->addNpcHyber(str, NpcHyberLeft, NpcHyberRight,&pNpcInfo);
		//AddMapName(pNpcInfo,str);
		stItem.m_nHiberarchy = 1;
		stItem.SetData( str.c_str(), pQuest->Id, (void*)none, dwColor );
		stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
		if( s_CUI_ID_FRAME_TRACK.GetLIST_TRACK() )
			s_CUI_ID_FRAME_TRACK.GetLIST_TRACK()->AddItem( &stItem,&CallBackDataArr, false );
		*/
		if (str.size())
		{
			if(s_CUI_ID_FRAME_TRACK.GetLIST_TRACK())
				AddInfoToListName(str,s_CUI_ID_FRAME_TRACK.GetLIST_TRACK(),Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)),pQuest->Id,bShowMapName);

		}

		/*if (pQuest->IsSingleRequirement)
		{
			break;
		}*/
	}
}



void CUI_ID_FRAME_Task::AddInfoToTaskInfo(std::string& str,short questId,short npcId)
{
	std::vector<UiCallbackDataBase*> CallBackDataArr;
	NpcCoord::getInstance()->addNpcHyberForText(str,NpcCoord::eQuestId,questId,npcId,&CallBackDataArr);
	m_pID_TEXT_TaskInfo->SetText(str.c_str(),0,&CallBackDataArr);
}


void CUI_ID_FRAME_Task::AddInfoToListName(const std::string& str, ControlList* pList,DWORD col,short questId,bool bShowMapName,int nHiberarchy /* = 0 */,std::vector<UiCallbackDataBase*> *pData /* = NULL */)
{
	std::string localStr = str;

	//增加超链接
	std::vector<UiCallbackDataBase*> CallBackDataArr;
	CallBackDataArr.clear();
	if(nHiberarchy == 0)
		NpcCoord::getInstance()->addNpcHyberForTextName(localStr,NpcCoord::eQuestId,questId,&CallBackDataArr,bShowMapName);
	else
	{
		if(NULL != pData)
		{
			for(int i = 0;i < pData->size();++i)
			{
				CallBackDataArr.push_back((*pData)[i]);
			}
		}
	}

	//计算显示在List上的宽度
	std::string tStr = str;
	//zhuxincong 12.4 注释掉 会影响到任务面板显示
	NpcCoord::getInstance()->addNpcHyberForTextName(tStr,NpcCoord::eQuestId,questId,NULL,bShowMapName,false);  //只插入地图名称
	std::wstring wStr = Common::_tstring::toWideString(tStr.c_str());
	//获得实际宽度
	int width = ControlHelper::Get().GetTextWidth(wStr,pList->GetFontHDC(),0,wStr.length(),pList,pList->GetFontIndex());
	int nNum = 0;
	int nPos = 0;
	while(nPos < wStr.length())
	{
		if(wStr.at(nPos) == L'$')
			++nNum;
		++nPos;
	}

	width -= nNum * 6;

	//计算宽度
	std::wstring strWide = Common::_tstring::toWideString(localStr.c_str());
	int startCP = 0;
	int endCP = strWide.length();
	// 	int width = ControlHelper::Get().GetTextWidth(strWide, pList->GetFontHDC(),
	// 		startCP, endCP,pList, pList->GetFontIndex() );
	int listWidth = pList->GetWidth() - 18;
	while (width > listWidth)
	{
		--endCP;
		width = ControlHelper::Get().GetTextWidth(strWide,
			pList->GetFontHDC(),
			startCP, endCP,pList, pList->GetFontIndex() );

		std::wstring w = strWide.substr(0,endCP);
		int n = 0;
		int nn = 0;
		while ( n < w.length())
		{
			if(strWide.at(n) == L'<' || strWide.at(n) == L'>' || strWide.at(n) == L'$')
				++nn;
			++n;
		}
		width -= nn * 6;
	}

	//	bool bOK = false;
	//	FontSystem::GetEndIndexByWidth( pList->GetFontIndex(), strWide, startCP, listWidth, endCP, bOK);


	//检测超链接是否需要换行,只检测<> 和[]两种符号
	std::string line = _tstring::toNarrowString(strWide.substr(0, endCP).c_str());
	int nPreFix = line.rfind("<");
	int nPostFix = line.rfind(">");
	if (nPreFix > nPostFix)//地址发生了错行
	{
		std::wstring nextline = &strWide[endCP];
		nPostFix = nextline.find(L">");
		if (nPostFix != -1&& nPreFix != 0)
		{
			line = line.substr(0,nPreFix);
			endCP = _tstring::toWideString(line.c_str()).length();
		}
	}

	line = _tstring::toNarrowString(strWide.substr(0,endCP).c_str());
	nPreFix = line.rfind("$[");
	nPostFix = line.rfind("]$");
	if(nPreFix > nPostFix)
	{
		std::wstring strNextLine = &strWide[endCP];
		nPostFix = strNextLine.find(L"]");
		if(nPostFix == -1)
		{
			int nIndex = strNextLine.find(L"$");
			if(nIndex != -1)
			{
				line = line.substr(0,nPreFix - 1);
				endCP = _tstring::toWideString(line.c_str()).length();
			}
		}
		else if(nPostFix != -1&&nPreFix != 0)
		{
			line = line.substr(0,nPreFix - 1);
			endCP = _tstring::toWideString(line.c_str()).length();
		}
	}

	ControlList::S_List	stItem;
	stItem.UseSelColor = false;
	stItem.m_nHiberarchy = 1;
	stItem.RemoveSyntaxFlag(eKeyHyper);

	NpcCoordInfo* pNpcInfo = NULL;
	if ((int)strWide.size() > endCP)
	{
		localStr = _tstring::toNarrowString(strWide.substr(0, endCP).c_str());

		std::vector<UiCallbackDataBase*> DataSet;
		DataSet.clear();

		int nIndex = localStr.find("<");
		int nCount = 0;
		for (; nIndex != -1;)
		{
			if(nCount >= CallBackDataArr.size())
				break;

			DataSet.push_back(CallBackDataArr[nCount]);
			nIndex = localStr.find("<",nIndex + 1);
			++nCount;
		}

		stItem.SetData( localStr.c_str(), questId);
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem,&DataSet);

		//如果还有超链接数据
		if(nCount < CallBackDataArr.size())
		{
			if(nCount != 0)
			{
				std::vector<UiCallbackDataBase*>::iterator it = CallBackDataArr.begin();
				std::advance(it,nCount);
				CallBackDataArr.erase(CallBackDataArr.begin(),it);
			}
			AddInfoToListName(_tstring::toNarrowString(strWide.substr(endCP).c_str()), pList,col,questId,false,++nHiberarchy,&CallBackDataArr);
		}
		else
			AddInfoToListName(_tstring::toNarrowString(strWide.substr(endCP).c_str()), pList,col,questId,false,++nHiberarchy);
	}
	else
	{

		stItem.SetData( localStr.c_str(),questId );
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem,&CallBackDataArr);
	}
}


void CUI_ID_FRAME_Task::AddInfoToList(const std::string& str, ControlList* pList,DWORD col,short questId,short npcId,bool bShowMapName,int nHiberarchy /*= 0*/,std::vector<UiCallbackDataBase*> *pData /*= NULL*/)
{

	std::string localStr = str;

	//增加超链接
	std::vector<UiCallbackDataBase*> CallBackDataArr;
	CallBackDataArr.clear();
	if(nHiberarchy == 0)
	    NpcCoord::getInstance()->addNpcHyberForText(localStr,NpcCoord::eQuestId,questId,npcId,&CallBackDataArr,bShowMapName);//zhuxincong 8.14 函数中多增加了参数npcId，需求是在npc.config中有相同名字的NPC，可以寻路过去
	else
	{
		if(NULL != pData)
		{
			for(int i = 0;i < pData->size();++i)
			{
				CallBackDataArr.push_back((*pData)[i]);
			}
		}
	}

	//计算显示在List上的宽度
	std::string tStr = str;
	NpcCoord::getInstance()->addNpcHyberForText(tStr,NpcCoord::eQuestId,questId,npcId,NULL,bShowMapName,false);  //只插入地图名称
	std::wstring wStr = Common::_tstring::toWideString(tStr.c_str());
	//获得实际宽度
	int width = ControlHelper::Get().GetTextWidth(wStr,pList->GetFontHDC(),0,wStr.length(),pList,pList->GetFontIndex());
	int nNum = 0;
	int nPos = 0;
	while(nPos < wStr.length())
	{
		if(wStr.at(nPos) == L'$')
			++nNum;
		++nPos;
	}

	width -= nNum * 6;

	//计算宽度
	std::wstring strWide = Common::_tstring::toWideString(localStr.c_str());
	int startCP = 0;
	int endCP = strWide.length();
// 	int width = ControlHelper::Get().GetTextWidth(strWide, pList->GetFontHDC(),
// 		startCP, endCP,pList, pList->GetFontIndex() );
	int listWidth = pList->GetWidth() - 18;
	while (width > listWidth)
	{
		--endCP;
		width = ControlHelper::Get().GetTextWidth(strWide,
			pList->GetFontHDC(),
			startCP, endCP,pList, pList->GetFontIndex() );

		std::wstring w = strWide.substr(0,endCP);
		int n = 0;
		int nn = 0;
		while ( n < w.length())
		{
			if(strWide.at(n) == L'<' || strWide.at(n) == L'>' || strWide.at(n) == L'$')
				++nn;
			++n;
		}
		width -= nn * 6;
	}

//	bool bOK = false;
//	FontSystem::GetEndIndexByWidth( pList->GetFontIndex(), strWide, startCP, listWidth, endCP, bOK);


	//检测超链接是否需要换行,只检测<> 和[]两种符号
	std::string line = _tstring::toNarrowString(strWide.substr(0, endCP).c_str());
	int nPreFix = line.rfind("<");
	int nPostFix = line.rfind(">");
	if (nPreFix > nPostFix)//地址发生了错行
	{
		std::wstring nextline = &strWide[endCP];
		nPostFix = nextline.find(L">");
		if (nPostFix != -1&& nPreFix != 0)
		{
			line = line.substr(0,nPreFix);
			endCP = _tstring::toWideString(line.c_str()).length();
		}
	}

	line = _tstring::toNarrowString(strWide.substr(0,endCP).c_str());
	nPreFix = line.rfind("$[");
	nPostFix = line.rfind("]$");
	if(nPreFix > nPostFix)
	{
		std::wstring strNextLine = &strWide[endCP];
		nPostFix = strNextLine.find(L"]");
		if(nPostFix == -1)
		{
			int nIndex = strNextLine.find(L"$");

			if(nIndex != -1)
			{
				line = line.substr(0,nPreFix - 1);
				endCP = _tstring::toWideString(line.c_str()).length();
			}
		}
		else if(nPostFix != -1&&nPreFix != 0)
		{
			line = line.substr(0,nPreFix - 1);
			endCP = _tstring::toWideString(line.c_str()).length();
		}
	}

	ControlList::S_List	stItem;
	stItem.UseSelColor = false;
	stItem.m_nHiberarchy = 1;
	stItem.RemoveSyntaxFlag(eKeyHyper);

	NpcCoordInfo* pNpcInfo = NULL;
	if ((int)strWide.size() > endCP)
	{
		localStr = _tstring::toNarrowString(strWide.substr(0, endCP).c_str());

		std::vector<UiCallbackDataBase*> DataSet;
		DataSet.clear();

		int nIndex = localStr.find("<");
		int nCount = 0;
		for (; nIndex != -1;)
		{
			if(nCount >= CallBackDataArr.size())
				break;

			DataSet.push_back(CallBackDataArr[nCount]);
			nIndex = localStr.find("<",nIndex + 1);
			++nCount;
		}

		stItem.SetData( localStr.c_str(), questId);
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem,&DataSet);

		//如果还有超链接数据
		if(nCount < CallBackDataArr.size())
		{
			if(nCount != 0)
			{
				std::vector<UiCallbackDataBase*>::iterator it = CallBackDataArr.begin();
				std::advance(it,nCount);
				CallBackDataArr.erase(CallBackDataArr.begin(),it);
			}
			AddInfoToList(_tstring::toNarrowString(strWide.substr(endCP).c_str()), pList,col,questId,npcId,false,++nHiberarchy,&CallBackDataArr);
		}
		else
			AddInfoToList(_tstring::toNarrowString(strWide.substr(endCP).c_str()), pList,col,questId,npcId,false,++nHiberarchy);
	}
	else
	{

		stItem.SetData( localStr.c_str(),questId );
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem,&CallBackDataArr);
	}
}

void CUI_ID_FRAME_Task::ShowUnderLine( bool bShow /* = true */ )
{
	if( !m_pID_FRAME_Task )
		return;
}

extern short GetKeyboardInput( int iKey );
#include "Dxsdk/dinput.h"

void CUI_ID_FRAME_Task::Task_HyberRBtnDown( ControlObject* pSender,  const char* szName ,int eHyberType)
{
	if( !s_CUI_ID_FRAME_Task.GetFrame() )
		return;

	if((eHyberType & (eKeyAddress|eKeyNpc)) &&
		(GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) ))
	{
		ControlList* pList = (ControlList*)pSender;
        if(!pList)
            return;

		int nQuestId = pList->GetCurSelItem()->m_nID;

		SQuest* pQuest = theQuestManager.GetQuest(nQuestId);
        if(!pQuest)  //下一句导致了Dump,所以加上指针的判断
            return;

		int nMapId = -1;
		const NpcCoordInfo* pInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(pQuest->AcceptTargetId);

		if (pInfo && Common::_tstring::toNarrowString(pInfo->_szName.c_str()) == szName)
		{
			nMapId = pInfo->_mapId;
		}
		else
		{
			pInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(pQuest->ReplyTargetId);
			if (pInfo && Common::_tstring::toNarrowString(pInfo->_szName.c_str()) == szName)
			{
				nMapId = pInfo->_mapId;
			}
			else
			{
				pInfo = NpcCoord::getInstance()->/*getNpcCoordInPrimaryMap*/getNpcCoord(szName);
			}
		}
		if (pInfo)
		{
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pInfo->_mapId);
			if (NULL == pTile)
			{
				return ;
			}
			s_CUI_ID_FRAME_AllNpcList.ShowTile(pTile,pInfo->_mapX,pInfo->_mapY);

		}

	}

}
// void CUI_ID_FRAME_Task::Task_HyberOtherClick( ControlObject* pSender, const std::string& content  ,int nId)
// {
// 	if( !pSender )
// 		return;
// 
// 	ControlList* pList = (ControlList*)pSender;
// 	int nQuestId = pList->GetCurSelItem()->m_nID;
// 	int nMapIdInMyCountry = NpcCoord::RetriveMapIdFromQuest(nQuestId, content);
// 
// 	if (false == NpcCoord::getInstance()->clickHyberToMiniMap(content.c_str(),nMapIdInMyCountry))
// 	{
// 		CWorldTile* pCurrTile = CURRENTTILE;
// 		if (pCurrTile->GetMapId() != nMapIdInMyCountry)
// 		{
// 			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFind) );
// 		}
// 	}
// 
// }

bool CUI_ID_FRAME_Task::Task_AbandonCallBackFun( const char bPressYesButton, void *pData )
{
	if( !s_CUI_ID_FRAME_Task.GetFrame() )
		return false;

	if( !pData )
		return false;
	MsgAbandonTask* pMsg = (MsgAbandonTask*)pData;
	if ( bPressYesButton != 0 )
	{
		GettheNetworkInput().SendMsg( pMsg );

		std::vector<int>::iterator itr = std::find(s_CUI_ID_FRAME_Task.m_vNotTrackList.begin(),
			s_CUI_ID_FRAME_Task.m_vNotTrackList.end(), pMsg->stTaskId);
		if(itr != s_CUI_ID_FRAME_Task.m_vNotTrackList.end())
			s_CUI_ID_FRAME_Task.m_vNotTrackList.erase(itr);
	}
	PlaySoundConfig( SoundConfig::EST_AbandonTask );
	return true;
}

void CUI_ID_FRAME_Task::FillMapPosTip(const NpcCoordInfo* pNpcInfo,ControlList::S_List* pList )
{
	return;
	if( !pList )
		return;
	if (!pNpcInfo || !pNpcInfo->_bPFPossible)
	{
		return;
	}
	char cTip[256];
	cTip[0] = '\0';
	{
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
		if (pTile)
		{
			sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
		}
	}
	if (cTip[0] != '\0')
	{
		pList->setTip( cTip );
		pList->_bOnline = true;
	}


}

void CUI_ID_FRAME_Task::ClearShowInfo()
{
	*m_pID_TEXT_TaskInfo = "";

	m_pID_LISTIMG_Reward->Clear();
	m_pID_LISTIMG_Reward->SetVisable(true);
	m_pID_LISTIMG_SecondItem->Clear();
	m_pID_LISTIMG_SecondItem->SetVisable(true);
	m_pID_TEXT_FITEM->SetText("");
	m_pID_TEXT_FITEM->SetVisable(false);
	m_pID_TEXT_SECITEM->SetText("");
	m_pID_TEXT_SECITEM->SetVisable(false);

	m_bFirst = true;
}

bool CUI_ID_FRAME_Task::UpdateTaskPanel( int questId )
{
	if ( questId == -1 )
	{
		return false;
	}

	SQuest *pQuest = theQuestManager.GetQuest( questId );
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( questId );
	if ( !pQuest || !pInfo )
	{
#ifdef _CLIENT_
		char temp[2048];
		sprintf_s(temp,2048,"%d任务获取失败！",questId);
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
#endif
		return false;
	}

	ClearTaskPanel();

	//任务图片
	m_pID_PICTURE_JQ1->SetVisable(true);

	//任务目标
	std::string targetStr = GetQuestTargetInfo( pQuest, pInfo,false);/*pQuest->GetQuestStateInfo();*/
	std::vector<UiCallbackDataBase*> CallBackDataArr;
	//试下用这个
	NpcCoord::getInstance()->addNpcHyberForTextName(targetStr,NpcCoord::eQuestId,questId,&CallBackDataArr,true);
	//if(pQuest->AcceptTargetId != pQuest->ReplyTargetId)
	//	NpcCoord::getInstance()->addNpcHyberForText( targetStr, NpcCoord::eQuestId, questId,pQuest->AcceptTargetId/*ReplyTargetId*/, &CallBackDataArr );
	m_pID_TEXT_TaskInfo->SetText( targetStr, 0, &CallBackDataArr );

	//任务描述
	std::string infoStr = pQuest->GetQuestInfo();
	CallBackDataArr.clear();
	//NpcCoord::getInstance()->addNpcHyberForText( infoStr, NpcCoord::eQuestId, questId,pQuest->AcceptTargetId/*ReplyTargetId*/, &CallBackDataArr,true);
	NpcCoord::getInstance()->addNpcHyberForTextName(infoStr,NpcCoord::eQuestId,questId,&CallBackDataArr,true);
	/*if(pQuest->AcceptTargetId != pQuest->ReplyTargetId)
	{
		NpcCoord::getInstance()->addNpcHyberForText(infoStr,NpcCoord::eQuestId,questId,pQuest->ReplyTargetId, &CallBackDataArr,true);
	}*/
	m_pID_TEXT_TaskDepict->SetText( infoStr, 0, &CallBackDataArr );

	//任务奖励
	std::string strReward;
	strReward.clear();
	GetRewardItemInfo(pQuest,strReward);
	CallBackDataArr.clear();
	NpcCoord::getInstance()->addNpcHyberForText( strReward, NpcCoord::eQuestId, questId,pQuest->ReplyTargetId, &CallBackDataArr );
	m_pID_TEXT_Award->SetText(strReward.c_str());

	//任务需求
	std::string strRequire;
	strRequire.clear();
	GetNeedItemInfo(pQuest,strRequire);
	CallBackDataArr.clear();
	NpcCoord::getInstance()->addNpcHyberForText( strRequire, NpcCoord::eQuestId, questId,pQuest->ReplyTargetId, &CallBackDataArr );
	m_pID_TEXT_Aim->SetText(strRequire.c_str());

	if(m_pID_BUTTON_AddQuestEntrust->IsVisable())
		m_pID_BUTTON_AddQuestEntrust->SetEnable((s_CUI_ID_FRAME_QuestEntrust.GetConfig().GetChangeQuestID(questId) == 0?false:true));

	return true;
}

void CUI_ID_FRAME_Task::ClearTaskPanel()
{
	m_pID_TEXT_AwardExp->SetText("");
	m_pID_TEXT_AwardMoney->SetText("");
	m_pID_LISTIMG_Reward->Clear();
	m_pID_LISTIMG_SecondItem->Clear();
	m_pID_LISTIMG_ThirdItem->Clear();
	m_pID_LISTIMG_FourItem->Clear();

	m_pID_TEXT_TaskInfo->SetText("");
	m_pID_TEXT_TaskDepict->SetText("");
	m_pID_PICTURE_JQ1->SetVisable(false);
}

std::string CUI_ID_FRAME_Task::GetQuestTargetInfo( SQuest *pQuest, CPlayerRole::QuestInfo* pInfo ,bool IsAddStrMapName)
{
	ControlList::S_List	stItem;
	stItem.UseSelColor = false;
	std::string strTaskTarget;
	
	if (pQuest->stCommitRequirement.empty() || !pInfo->bDone)
	{
		std::string strInfo = pQuest->GetQuestStateInfo();
		if(!strInfo.empty())
		{
			if(IsAddStrMapName)
			{
				NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
				if(pQuest->ReplyTargetId != pQuest->AcceptTargetId)
					NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->AcceptTargetId,NULL,true,false);
			}
			// 			AddInfoToList(strInfo, m_pID_LIST_Taskstate,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
			strTaskTarget += "\n    ";
			strTaskTarget += strInfo;
		}
	}
	else
	{
		std::string format = theXmlString.GetString(eText_AckNpc);
		int npcId = pQuest->ReplyTargetId;
		const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoord(npcId);
		std::string pNpcName ;
		if (pNpcInfo)
		{
			pNpcName = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str()).c_str();
		}
		char szInfo[dr_MaxQuestDesc] = {0};
		sprintf( szInfo, format.c_str(), pNpcName.c_str() );
		std::string strInfo = szInfo;
		if(IsAddStrMapName)
		{
			NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
			if(pQuest->ReplyTargetId != pQuest->AcceptTargetId)
				NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->AcceptTargetId,NULL,true,false);
		}
	
		strTaskTarget += "\n    ";
		strTaskTarget += strInfo;
		//AddInfoToList(strInfo, m_pID_LIST_Taskstate,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	}
	if(pInfo->chState == QuestManager::eQuestEntrustDone)	
		return strTaskTarget;
	std::string strNeedItem;
	strNeedItem.clear();

	GetNeedItemInfo(pQuest,strNeedItem);
	strTaskTarget += strNeedItem;

	SQuestRequirement *pRequirement = NULL;

	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		stItem.clear();
		pRequirement = &pQuest->stCommitRequirement[i];
		char szInfo[256] = "";
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
					}

					//需要任务物品
					sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedItem),pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );

					// 增加Item寻路tips
// 						const NpcCoordInfo *pNpcInfo =  NpcCoord::getInstance()->getNpcCoord(pItemDetail->GetItemName());
// 						FillMapPosTip(pNpcInfo,&stItem);
				}
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (pMonstor)
				{
					sprintf( szInfo, theXmlString.GetString(eText_Quest_TaskNeedMonster),pMonstor->GetName(), nVar, pRequirement->MaxNum );
// 						const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(pMonstor->GetName());
// 						FillMapPosTip(pNpcInfo,&stItem);
				}
			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				sprintf( szInfo, "%s (%ld/%ld)", theXmlString.GetString(pRequirement->Value), nVar, pRequirement->MaxNum );
			}break;
		case SQuest::eRequirement_Var:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				if(nVar == pRequirement->MaxNum)
					continue;

				sprintf(szInfo, "%s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
			}
			break;
		default:
			break;
		}
		/*if (pQuest->IsSingleRequirement)
		{
			break;
		}*/
		/*std::string strInfo = szInfo;
		NpcCoord::getInstance()->addNpcHyber(strInfo, NpcHyberLeft, NpcHyberRight);
		stItem.SetData( strInfo.c_str() );
		stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );*/
	}

	return strTaskTarget;
}



void CUI_ID_FRAME_Task::RefreshFinishPic()
{
	//{
	//	m_pID_LISTIMG_RewardList->Clear();
	//	int nItemImage = 0;
	//	const int nImageListWidth = m_pID_LISTIMG_RewardList->GetRowItemCnt();
	//	m_pID_LISTIMG_RewardList->SetHeightMaxCnt(m_pID_LIST_Task->GetListItemCnt());
	//	for (int i = 0; i < m_pID_LIST_Task->GetListItemCnt(); ++i)
	//	{
	//		if (m_pID_LIST_Task->GetListItem(i)->m_nHiberarchy != 1)
	//		{
	//			continue;
	//		}
	//		int nQuestId = m_pID_LIST_Task->GetListItem(i)->m_nID;
	//		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	//		nItemImage = i* nImageListWidth; 

	//		if( pInfo )
	//		{
	//			SQuest *pQuest = theQuestManager.GetQuest( pInfo->nQuestId );
	//			if( !pQuest )
	//				continue;
	//			SQuestReward *pReward = NULL;
	//			ControlIconDrag::S_ListImg stImgItem;
	//			for ( int n=0; n<pQuest->stReward.size(); n++ )
	//			{
	//				pReward = &pQuest->stReward[n];
	//				ItemDefine::SItemCommon *pItemDetail = NULL;
	//				if (pReward->byType == SQuest::eReward_Item)
	//				{
	//					pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
	//					if( !pItemDetail )
	//						continue;
	//					if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
	//						pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
	//						pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	//					{
	//						unsigned char cPro = thePlayerRole.GetProfession();
	//						if (!(pReward->shProfession & (1 << cPro)))
	//							continue;

	//						if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
	//							continue;
	//					}
	//					stImgItem.SetData( pItemDetail->ustItemID, pReward->Number,eIcon_Enable, true );
	//				}
	//				else
	//				{
	//					if (SQuest::eReward_Money == pReward->byType)
	//					{
	//						int money = pReward->Value;
	//						if (money == 0)
	//						{
	//							if (money <= 0)
	//							{
	//								continue;
	//							}
	//						}
	//					}
	//					else if (SQuest::eReward_Exp == pReward->byType)
	//					{
	//						int RewardValue = pReward->Value;
	//						if (RewardValue == 0)
	//						{
	//							try
	//							{
	//								char filename[MAX_PATH] = {0};
	//								sprintf(filename, "%s/Data/Quest/CalculateExp.string", GetRootPath());

	//								LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
	//								const char* pszRewardValue = CalcExp( pInfo->nQuestId, pQuest->RankId, thePlayerRole.GetLevel() );

	//								// 空指针不能进行std::string的比较
	//								if ( pszRewardValue && ( std::string("0") == pszRewardValue ) )
	//								{
	//									continue;
	//								}
	//							}
	//							catch (LuaPlus::LuaException &e)
	//							{
	//								assert( 0 && "calculateexp.string" );
 //                                   ::OutputDebugString(e.GetErrorMessage());
	//							}
	//							
	//						}
	//					}
	//					int nRewardItemId = pReward->Icon;
	//					if (nRewardItemId == 0)
	//					{
	//						continue;
	//					}
	//					pItemDetail = GettheItemDetail().GetItemByID( nRewardItemId );
	//					stImgItem.SetData( pItemDetail->ustItemID,1);
	//				}
	//				m_pID_LISTIMG_RewardList->SetItem( &stImgItem,nItemImage++ );
	//			}
	//		}
	//	}

	//	m_pID_LISTIMG_RewardList->SetStartIndex(m_pID_LIST_Task->GetStartIndex());
	//}

	m_pID_LIST_Finish->BeginUpdate();
	m_pID_LIST_Finish->Clear();

	bool isCurrenting = m_pID_CHECKBOX_Task1->IsChecked();
	if (!isCurrenting)
	{
		return;
	}
	for (int i = 0; i < m_pID_LIST_Task->GetListItemCnt(); ++i)
	{
		ControlList::S_List stItem;
		if (m_pID_LIST_Task->GetListItem(i)->m_nHiberarchy != 1)
		{
			stItem.SetData("");
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
			continue;
		}
		int nQuestId = m_pID_LIST_Task->GetListItem(i)->m_nID;
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );

		if( !pInfo )
		{
			stItem.SetData("");
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
			continue;
		}
		if (!theQuestManager.IsQuestActive(pInfo->chState))
		{
			stItem.SetData("");
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
			continue;
		}
		if (pInfo->bDone )
		{
			stItem.SetData("{#1030}");
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}
		else
		{
			stItem.SetData("");
			m_pID_LIST_Finish->AddItem(&stItem,NULL, false);
		}
	}
	m_pID_LIST_Finish->EndUpdate();
}

void CUI_ID_FRAME_Task::Task_CollapseCallBackFun( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !s_CUI_ID_FRAME_Task.GetFrame() )
		return;

	s_CUI_ID_FRAME_Task.RefreshFinishPic();
}

// bool CUI_ID_FRAME_Task::ID_LISTIMG_FinallyRewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_Task )
// 		return false;
// 	return true;
// }
// 
// bool CUI_ID_FRAME_Task::ID_LISTIMG_FinallyRewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_Task )
// 		return false;
// 	return true;
// }
// 
// bool CUI_ID_FRAME_Task::ID_LISTIMG_FinallyRewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_Task )
// 		return false;
// 	return true;
// }
// 
// bool CUI_ID_FRAME_Task::ID_LISTIMG_FinallyRewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_Task )
// 		return false;
// 	return true;
// }

void CUI_ID_FRAME_Task::ID_LIST_FinishOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Task )
		return;
}

static const char* TaskTrackFilename = "TaskTrack.config";
static const char* TaskTrackFilenameOld = "TaskTrack.xml";

bool CUI_ID_FRAME_Task::LoadTrackInfo()
{
	if (m_bTaskInfoLoaded)
		return false;

	m_bTaskInfoLoaded = true;
	m_vNotTrackList.clear();
	m_vTrackList.clear();

	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTrackFilename;

	MeXmlDocument doc1;
	//if( !doc1.LoadFile(filename.c_str()) )
	//{
	//	// 读旧的文件格式
	//	filename = CUserData::Instance()->GetUserDataPath();
	//	filename += TaskTrackFilenameOld;
	//}
	if( doc1.LoadFile(filename.c_str()) )
	{
// 		MeXmlHandle	 hDoc1(&doc1);

		MeXmlElement* pHeader = doc1.FirstChildElement("Project");
		if (pHeader)
		{
			MeXmlElement* pElem = pHeader->FirstChildElement("Tracks")->FirstChildElement("Track");
			for( ; pElem; pElem = pElem->NextSiblingElement() )
			{
				int nId = 0;
				pElem->QueryIntAttribute("Id", &nId);
				m_vTrackList.push_back(nId);

				int nIsTrack = 0;
				pElem->QueryIntAttribute("IsTrack", &nIsTrack);
				if (!nIsTrack)
					m_vNotTrackList.push_back(nId);
			}
		}
	}

	return !m_vNotTrackList.empty();
}

void CUI_ID_FRAME_Task::SaveTrackInfo()
{
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTrackFilename;

	SetFileAttributes( filename.c_str(), FILE_ATTRIBUTE_NORMAL );

	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "utf-8", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement *project= doc.InsertEndChild("Project");
	project->SetAttribute("Name", "HeroOnline");
	project->SetAttribute("Version", "");

	MeXmlElement *tracks = project->InsertEndChild("Tracks");

	for(std::list<int>::iterator itr=m_vTrackList.begin(); itr!=m_vTrackList.end(); itr++)
	{
		MeXmlElement *track = tracks->InsertEndChild("Track");
		track->SetAttribute("Id", *itr);
		int nIsTrack = std::find(m_vNotTrackList.begin(), m_vNotTrackList.end(), *itr) == m_vNotTrackList.end();
		track->SetAttribute("IsTrack", nIsTrack);

// 		tracks.InsertEndChild(track);
	}
// 	project.InsertEndChild(tracks);

// 	doc.InsertEndChild(project);
	doc.SaveFile(filename.c_str());

	// 删除旧文件格式
	filename = CUserData::Instance()->GetUserDataPath();
	filename += TaskTrackFilenameOld;
	::DeleteFile(filename.c_str());
}

bool CUI_ID_FRAME_Task::RefreshCurrSelect()
{
	if( !m_pID_FRAME_Task )
		return false;

	if (m_pID_LIST_Task&& m_pID_FRAME_Task->IsVisable()&&m_pID_LIST_Task->GetCurSelItem() && m_pID_LIST_Task->GetCurSelItem()->m_nHiberarchy == 1)
	{
		UpdateTaskPanel(m_pID_LIST_Task->GetCurSelItem()->m_nID);
		//UITask_ShowInfo(m_pID_LIST_Task->GetCurSelItem()->m_nID);
	}
	return true;
}

void CUI_ID_FRAME_Task::Task_OnVisiableChanged( ControlObject* pSender )
{
	if( !s_CUI_ID_FRAME_Task.GetFrame() )
		return;

	if (!pSender->IsVisable())
	{
		s_CUI_ID_FRAME_Task.RecordCollapseInfo();
	}
}

void CUI_ID_FRAME_Task::CHECKBOX_jieneng_SetCheck( bool bCheck )
{
	if( !m_pID_FRAME_Task )
		return;
	m_pID_CHECKBOX_jieneng->SetCheck(bCheck);
}

void CUI_ID_FRAME_Task::Text_TaskInfo_HyberClick( ControlObject* pSender, const char* szData )
{
	if( szData )
		NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}

void CUI_ID_FRAME_Task::GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem)
{
	if(!pQuest)
		return;

	// 任务奖励
	SQuestReward *pReward = NULL;
	for ( int n=0; n<pQuest->stReward.size(); n++ )
	{
		pReward = &pQuest->stReward[n];
		switch( pReward->byType )
		{
		case SQuest::eReward_Money:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(money, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskGold);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_ScriptExp://脚本经验
			{
				// 各个值不同 
				char szWord[256] = {0};
				switch(pReward->Value)
				{
				case 1:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp1));
					break;
				case 2:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp2));
					break;
				}
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Exp:
			{
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					//计算经验值加成
					/*if(thePlayerRole.IsInWeakCountry())
						RewardValue = RewardValue*1.05;
					else if(thePlayerRole.IsInStrongCountry())
						RewardValue = RewardValue;
					else if(thePlayerRole.GetCountry() != CountryDefine::Country_Init)
						RewardValue = RewardValue * 1.1;*/

					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),RewardValue);
					strRewardItem += "\n";
					strRewardItem += szWord;
				}
				else
				{
					try
					{
						char filename[MAX_PATH] = {0};
						sprintf(filename, "%s/Data/Quest/CalculateExp.string", GetRootPath());

						try
						{
							//
							// 经验计算
							//
							LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
							const char* pszRewardValue = CalcExp( pQuest->Id, pQuest->RankId, thePlayerRole.GetLevel() );

							// 空指针不能进行std::string的比较
							if ( pszRewardValue && ( std::string("0") != pszRewardValue ) )
							{
								if(pszRewardValue != NULL)
								{
									int nValue = 0;
									//if(sscanf_s(RewardValue,"%d",&nValue) == 1)
									{
										nValue = atoi(pszRewardValue);
										char szWord[256] = {0};
										MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),nValue);
										strRewardItem += "\n";
										strRewardItem += szWord;
									}
								}
								//*m_pID_TEXT_Exp = pszRewardValue;
							}
						}
						catch (LuaPlus::LuaException &e)
						{
							assert( 0 && "calculateexp.string" );
							::OutputDebugString(e.GetErrorMessage());
						}
					}
					catch (LuaPlus::LuaException &e)
					{
						assert( 0 && "calculateexp.string" );
						::OutputDebugString(e.GetErrorMessage());
					}

				}

			}
			break;
		case SQuest::eReward_CountryMoney:
			{
				//奖励国家资金
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(RewardValue, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_CountryMoney);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_SkillExp:
			{
				int  nRewardValue = pReward->Value;
				if(0 != nRewardValue)
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),"{#fff4db30=历练名望: %d#}",nRewardValue);
					strRewardItem += "\n";
					strRewardItem += szWord;
					// *m_pID_TEXT_SkillExp = nRewardValue;
					// m_pID_TEXT_SkillExpZ->SetVisable(true);
					//                    m_pID_TEXT_SkillExp->SetVisable(true);
				}
			}
			break;
		case SQuest::eReward_Item:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number, eIcon_Enable, false, eTipFlag_Normal, false, true );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}

 				if(m_pID_LISTIMG_Reward->GetNullItem() == 0)
 					m_pID_LISTIMG_Reward->SetItem( &stItem );
 				else if(m_pID_LISTIMG_SecondItem->GetNullItem() == 0)
 					m_pID_LISTIMG_SecondItem->SetItem( &stItem );
				else if(m_pID_LISTIMG_ThirdItem->GetNullItem() == 0)
					m_pID_LISTIMG_ThirdItem->SetItem( &stItem );
				else if(m_pID_LISTIMG_FourItem->GetNullItem() == 0)
					m_pID_LISTIMG_FourItem->SetItem( &stItem );

// 				m_pID_LISTIMG_Reward->SetItem( &stItem );
// 				m_pID_LISTIMG_SecondItem->SetItem(&stItem);
// 				m_pID_LISTIMG_Reward->SetVisable(true);
			}
			break;
		case SQuest::eReward_Reputation:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskMingWang),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;

			}
			break;
		case SQuest::eReward_Exploit:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGongXun),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Title:
			{
				TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pReward->Value );
				if( pTitle )
				{
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskTitle);
					strRewardItem += pTitle->GetName();
				}
			}
			break;
		case SQuest::eReward_GuildContribute:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGuildContribute),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_SpecialItem:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}
				// 				pSpiecialItemImage->SetItem( &stItem );
				// 				pSpiecialItemImage->SetVisable(true);
				// 				pSpiecialItemText->SetVisable(true);
			}
			break;
		case SQuest::eReward_JiaoZi:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromJiaoZi(money, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskJiaozi);
					strRewardItem += text;
				}
			}
			break;
		case SQuest::eReward_Honor:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskRongYu),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	if (strRewardItem.find_first_of("\n")==0)
	{
		strRewardItem.erase(strRewardItem.find_first_of("\n"),1);
	}
}

void CUI_ID_FRAME_Task::GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem)
{
	if(!pQuest)
		return;
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pQuest->Id );
	if(pInfo && pInfo->chState == QuestManager::eQuestEntrustDone)	
		return;

	strNeedItem.clear();
	if(pQuest->IsSingleRequirement)
		strNeedItem += theXmlString.GetString(eText_Quest_IsSingleRequirement);

	SQuestRequirement *pRequirement = NULL;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		bool bShowMapName = false;
		pRequirement = &pQuest->stCommitRequirement[i];
		char szInfo[256] = "";
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
					}

					//需要任务物品
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString( eText_NeedItem ),
						pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );
				}
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (pMonstor)
				{
					//需要
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString(eUI_NeedText),
						pMonstor->GetName(), nVar, pRequirement->MaxNum );

					bShowMapName = true;
				}
			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				sprintf( szInfo, "    %s (%ld/%ld)", theXmlString.GetString(pRequirement->Value),
					nVar, pRequirement->MaxNum );
			}
			break;
		case SQuest::eRequirement_Var:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				if(nVar == pRequirement->MaxNum)
					continue;

				sprintf(szInfo, "\n    %s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
				bShowMapName = true;			
			}
			break;
		default:
			break;
		}
		std::string strInfo = szInfo;
		NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,bShowMapName,false);

		strNeedItem += strInfo;
		/*if (pQuest->IsSingleRequirement)
		{
			break;
		}*/
	}
}

void CUI_ID_FRAME_Task::ModifyRewardItem(int nTop,int nLeft)
{
	if(!m_pID_FRAME_Task)
		return;

	if(m_pID_LISTIMG_Reward->GetNullItem() == 0)
		return;

	//获得实际控件坐标
	RECT rcList,rcText;
	m_pID_LISTIMG_Reward->GetRectSize(&rcList);
	m_pID_TEXT_FITEM->GetRectSize(&rcText);

	//调整ListImage控件
	int nListHeight = 0,nListWidth = 0;
	nListWidth  = m_pID_LISTIMG_Reward->GetWidth();
	nListHeight = m_pID_LISTIMG_Reward->GetHeight();

	RECT listRect;
	listRect.left = rcList.left;
	listRect.top  = nTop;
	listRect.bottom = listRect.top + nListHeight;
	listRect.right  = listRect.left + nListWidth;
	//m_pID_LISTIMG_Reward->SetRealRect(&listRect);

	//设置描述文件
	int nTextWidth = 0,nTextHeight = 0;
	nTextWidth = m_pID_TEXT_FITEM->GetWidth();
	nTextHeight = m_pID_TEXT_FITEM->GetHeight();

	RECT desRc;
	desRc.left = rcText.left;
	desRc.top  =  nTop + (nListHeight - nTextHeight)/2;
	desRc.right = desRc.left + nTextWidth;
	desRc.bottom = desRc.top + nTextHeight;
	m_pID_TEXT_FITEM->SetRealRect(&desRc);

	ControlListImage::S_ListImg *pListImg = m_pID_LISTIMG_Reward->GetItemByIndex(0);
	if(!pListImg)
		return;

	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(pListImg->m_pkIconInfo->Id());
	if(!pCommon)
		return;

	m_pID_TEXT_FITEM->SetText(pCommon->GetItemName());

	m_pID_LISTIMG_Reward->SetVisable(true);
	m_pID_TEXT_FITEM->SetVisable(true);

	//第二个

	if(m_pID_LISTIMG_SecondItem->GetNullItem() == 0)
		return;

	m_pID_LISTIMG_SecondItem->GetRectSize(&rcList);
	m_pID_TEXT_SECITEM->GetRectSize(&rcText);

	//调整ListImage控件
	nListWidth = m_pID_LISTIMG_SecondItem->GetWidth();
	nListHeight = m_pID_LISTIMG_SecondItem->GetHeight();

	listRect.left = rcList.left;
	listRect.top  = nTop;
	listRect.bottom = listRect.top + nListHeight;
	listRect.right  = listRect.left + nListWidth;
	//m_pID_LISTIMG_SecondItem->SetRealRect(&listRect);

	//描述文件
	nTextWidth = m_pID_TEXT_SECITEM->GetWidth();
	nTextHeight = m_pID_TEXT_SECITEM->GetHeight();

	RECT rcTextName;
	rcTextName.left = rcText.left;
	rcTextName.top = nTop + (nListHeight - nTextHeight)/2;
	rcTextName.right = rcTextName.left + nTextWidth;
	rcTextName.bottom = rcTextName.top + nTextHeight;
	m_pID_TEXT_SECITEM->SetRealRect(&rcTextName);

	pListImg = m_pID_LISTIMG_SecondItem->GetItemByIndex(0);
	if(!pListImg)
		return;

	//设置名称
	pCommon = GettheItemDetail().GetItemByID(pListImg->m_pkIconInfo->Id());
	if(!pCommon)
		return;

	m_pID_TEXT_SECITEM->SetText(pCommon->GetItemName());


	m_pID_LISTIMG_SecondItem->SetVisable(true);
	m_pID_TEXT_SECITEM->SetVisable(true);
}

void CUI_ID_FRAME_Task::UpdateTaskInfo( OUT ControlObject* pSender, int n )
{
	s_CUI_ID_FRAME_Task.UpdateRewardItem(n);
}

void CUI_ID_FRAME_Task::UpdateRewardItem(int n)
{
	if(m_bFirst)
	{
		m_pID_LISTIMG_Reward->GetRectSize(&m_rc);
		m_bFirst = false;
	}

	int nTop = m_rc.top - n;

	ModifyRewardItem(nTop,m_rc.left);
}

void CUI_ID_FRAME_Task::AddMapName(const NpcCoordInfo* pNpcInfo,std::string &format)
{
	if(!pNpcInfo)
		return;

	if(!pNpcInfo->_bNpc)
		return;

	std::string::size_type nPos = format.find(NpcHyberLeft);
	if(nPos != std::string::npos)
	{
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
		if (pTile)
		{
			char szMapName[256]={0};
			MeSprintf_s(szMapName,sizeof(szMapName),theXmlString.GetString(eText_Quest_MapName),pTile->GetTileName());
			format.insert(nPos,szMapName);
		}
	}
}

void CUI_ID_FRAME_Task::FrameOnVisiableChanged( ControlObject* pSender )
{
	s_CUI_ID_FRAME_Task.GetTextControl()->SetVisable(pSender->IsVisable());
}
uint8 CUI_ID_FRAME_Task::GetQusetSortValue(uint8 Type)
{
	switch(Type)
	{
	case SQuest::Type_Main:
		return 1;
		break;
	case SQuest::Type_Campaign:
		return 2;
		break;
	case SQuest::Type_Gut:
		return 3;
		break;
	case SQuest::Type_Lateral:
		return 4;
		break;
	default:
		return 5;
		break;
	}
}
bool CUI_ID_FRAME_Task::SortByQuestID(int lhs, int rhs)
{
	SQuest *pQuestL = theQuestManager.GetQuest( lhs );
	if(!pQuestL) return true;
	uint8 TypeL =  GetQusetSortValue(pQuestL->chQuestType);

	SQuest *pQuestR = theQuestManager.GetQuest( rhs );
	if(!pQuestR) return true;
	uint8 TypeR =  GetQusetSortValue(pQuestR->chQuestType);

	if(TypeL < TypeR)
		return true;
	else if(TypeL > TypeR)
		return false;
	else
	{
		return pQuestL->chQuestType < pQuestR->chQuestType;
	}
}