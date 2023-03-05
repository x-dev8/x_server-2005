/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\EspecialTask.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EspecialTask.h"
#include "QuestManager.h"
#include "actionUi.h"
#include "Property.h"
#include "GameMain.h"
#include "MessageBox.h"
#include "UIMgr.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
// #include "help.h"
#include "../color_config.h"
#include "../MotionBillBoard.h"
#include "ChatInfoBox.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "../MiniMap.h"
#include "GameMain.h"
#include "MeUi/ExpressionManager.h"
#include "QuestData.h"
#include "core/Name.h"
#include "QuestManager.h"
#include "GroupPanel.h"
#include "Compound.h"
#include "Gang.h"
// #include "Corps.h"
#include "NpcTaskDialogBox.h"
#include "NpcChatDialogBox.h"
#include "SelectBox.h"
#include "script_manager.h"
#include "NpcInfo.h"
#include "MeTerrain/stdafx.h"
#include "ShowScreenText.h"
#include "TitleConfig.h"
#include "AllNpcList.h"
#include "ActivityList.h"
#include "UserData.h"
#include "logmgr.h"
// #include "Tinyxml/tinyxml.h"
#include "Dxsdk/dinput.h"
#include "Common.h"
#include "ScreenInfoManager.h"
#include "Task.h"
#include "Player.h"

#define ERROR_INFO_LOG	"ErrorInfo.log"

extern short GetKeyboardInput( int iKey );

CUI_ID_FRAME_EspecialTask s_CUI_ID_FRAME_EspecialTask;
MAP_FRAME_RUN( s_CUI_ID_FRAME_EspecialTask, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_EspecialTask, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LIST_TaskOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_AwardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_AwardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_AwardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_AwardOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LIST_TaskStateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LIST_TaskInfoOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_BUTTON_AcceptOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_RewardListOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_RewardListOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_RewardListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_RewardListOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_ItemIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_ItemIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_ItemIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_LISTIMG_ItemIconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EspecialTask, ID_BUTTON_BrushOnButtonClick )
CUI_ID_FRAME_EspecialTask::CUI_ID_FRAME_EspecialTask()
{
	// Member
	m_pID_FRAME_EspecialTask = NULL;
	m_pID_PICTURE_TaskListWall = NULL;
	m_pID_LIST_Task = NULL;
	m_pID_PICTURE_TitleWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_TaskAwardWall = NULL;
	m_pID_LISTIMG_Award = NULL;
	m_pID_TEXT_ItemZ = NULL;
	//m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_TaskInfoWall = NULL;
	m_pID_TEXT_TaskListZ = NULL;
	m_pID_TEXT_ExpZ = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_AwardZ = NULL;
	m_pID_PICTURE_TaskStateWall = NULL;
	m_pID_LIST_TaskState = NULL;
	m_pID_LIST_TaskInfo = NULL;
	m_pID_TEXT_TaskAwardZ = NULL;
	m_pID_TEXT_TaskLvlZ = NULL;
	m_pID_TEXT_TaskLvl = NULL;
	m_pID_PICTURE_LeftMiddleWall = NULL;
	m_pID_PICTURE_RightMiddleWall = NULL;
	m_pID_PICTURE_LeftWall = NULL;
	m_pID_PICTURE_RightWall = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_TEXT_MingWangZ = NULL;
	m_pID_TEXT_MingWang = NULL;
	m_pID_LISTIMG_RewardList = NULL;
	m_pID_PICTURE_ReitemWall = NULL;
	m_pID_LISTIMG_ItemIcon = NULL;
	m_pID_BUTTON_Brush = NULL;
	m_pID_TEXT_ItemInfo = NULL;
	m_pID_TEXT_TakeNum = NULL;
	m_pID_TEXT_TaskExplain = NULL;
	m_pID_PICTURE_Title1 = NULL;
	m_pID_PICTURE_Title2 = NULL;
	m_pID_TEXT_TaskInfo = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_MoneyZ = NULL;
}

// Frame
bool CUI_ID_FRAME_EspecialTask::OnFrameRun()
{
	if (!IsVisable())
	{
		return false;
	}
	int nStartIndex = m_pID_LIST_Task->GetShowStartHeight();
	m_pID_LISTIMG_RewardList->SetShowStartHeight(nStartIndex);
	return true;
}
bool CUI_ID_FRAME_EspecialTask::OnFrameRender()
{
    ProcessVisualUI();
	return true;
}
// List
void CUI_ID_FRAME_EspecialTask::ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
    if(!m_pID_FRAME_EspecialTask)
    {
        assert(false&&"ui error");
        return ;
    }

	TaskListSelectChanged();
}
// Button
bool CUI_ID_FRAME_EspecialTask::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_AwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_AwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_AwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_AwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// List
void CUI_ID_FRAME_EspecialTask::ID_LIST_TaskStateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_EspecialTask::ID_LIST_TaskInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_EspecialTask::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_EspecialTask::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_EspecialTask::ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_EspecialTask)
    {
        assert(false&&"ui error");
        return false;
    }

	ControlList::S_List* pItem = m_pID_LIST_Task->GetCurSelItem();
	if (!pItem)
		return false;

	MsgReceiveQuestReq msg;
	msg.stQuestID = pItem->m_nID;
	msg.stNpcID = m_npcId;
	GettheNetworkInput().SendMsg( &msg );

	m_canRefresh = true;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_RewardListOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_RewardListOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_RewardListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_RewardListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_ItemIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_ItemIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_ItemIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EspecialTask::ID_LISTIMG_ItemIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
static bool EspecialTaskUseItem(char bPressYesButton, void *pData)
{
	if (bPressYesButton)
	{
		MsgResetPubQuestReq* pMsg = (MsgResetPubQuestReq*)pData;
		GettheNetworkInput().SendMsg( pMsg );

		s_CUI_ID_FRAME_EspecialTask.SetCanRefresh(false);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_EspecialTask::ID_BUTTON_BrushOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_EspecialTask)
    {
        assert(false&&"ui error");
        return false;
    }

	// 物品ID
	//ResetPubQuestItemID1 = 13409,   // 皇榜=>皇榜令
	//	ResetPubQuestItemID2 = 13410,   // 酒馆=>行酒令
	MsgResetPubQuestReq msg;
	msg.stNpcID = m_npcId;

	SCharItem item;
	ItemDefine::SItemCommon* pCommon = 0;
	switch (m_taskType)
	{
	case MsgScriptReqShowQuestDlg::ShowType_Pub:
		{
			if (!thePlayerRole.m_bag.GetItemByItemID(ResetPubQuestItemID2, &item))
			{
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_QuestState_Error, theXmlString.GetString(eText_GameTaskInfo) );
				return false;
			}

			msg.chType = SQuest::Type_Pub;
		}break;
	case MsgScriptReqShowQuestDlg::ShowType_Royal:
		{
			if (!thePlayerRole.m_bag.GetItemByItemID(ResetPubQuestItemID1, &item))
				return false;

			msg.chType = SQuest::Type_Royal;
		}break;
	}

	pCommon = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
	if (!pCommon)
		return false;

	DWORD dwColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );

	char text[MAX_PATH];
	char name[MAX_PATH];
	MeSprintf_s(name,sizeof(name)/sizeof(char) - 1, "{#%x=%s#}", dwColor, pCommon->GetItemName());
	MeSprintf_s(text,sizeof(text)/sizeof(char) - 1, theXmlString.GetString(eClient_IfUseItem), name);

	s_CUI_ID_FRAME_MessageBox.Show( text, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
		false, EspecialTaskUseItem, &msg, sizeof(MsgChat) );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_EspecialTask::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\EspecialTask.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\EspecialTask.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_EspecialTask::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_EspecialTask, s_CUI_ID_FRAME_EspecialTaskOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_EspecialTask, s_CUI_ID_FRAME_EspecialTaskOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_EspecialTask, ID_LIST_Task, s_CUI_ID_FRAME_EspecialTaskID_LIST_TaskOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_EspecialTask, ID_BUTTON_Cancel, s_CUI_ID_FRAME_EspecialTaskID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_EspecialTask, ID_LISTIMG_Award, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_AwardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EspecialTask, ID_LISTIMG_Award, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_AwardOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EspecialTask, ID_LISTIMG_Award, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_AwardOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EspecialTask, ID_LISTIMG_Award, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_AwardOnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_EspecialTask, ID_LIST_TaskState, s_CUI_ID_FRAME_EspecialTaskID_LIST_TaskStateOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_EspecialTask, ID_LIST_TaskInfo, s_CUI_ID_FRAME_EspecialTaskID_LIST_TaskInfoOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_EspecialTask, ID_BUTTON_help, s_CUI_ID_FRAME_EspecialTaskID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_EspecialTask, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EspecialTaskID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_EspecialTask, ID_BUTTON_Accept, s_CUI_ID_FRAME_EspecialTaskID_BUTTON_AcceptOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_EspecialTask, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_RewardListOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EspecialTask, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_RewardListOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EspecialTask, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_RewardListOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EspecialTask, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_RewardListOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EspecialTask, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_ItemIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EspecialTask, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_ItemIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EspecialTask, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_ItemIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EspecialTask, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_EspecialTaskID_LISTIMG_ItemIconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_EspecialTask, ID_BUTTON_Brush, s_CUI_ID_FRAME_EspecialTaskID_BUTTON_BrushOnButtonClick );

	m_pID_FRAME_EspecialTask = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_EspecialTask );
	m_pID_PICTURE_TaskListWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_TaskListWall );
	m_pID_LIST_Task = (ControlList*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LIST_Task );
	m_pID_PICTURE_TitleWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_TitleWall );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_BUTTON_Cancel );
	m_pID_PICTURE_TaskAwardWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_TaskAwardWall );
	m_pID_LISTIMG_Award = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LISTIMG_Award );
	m_pID_TEXT_ItemZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_ItemZ );
	//m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_Title );
	m_pID_PICTURE_TaskInfoWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_TaskInfoWall );
	m_pID_TEXT_TaskListZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskListZ );
	m_pID_TEXT_ExpZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_ExpZ );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_Exp );
	m_pID_TEXT_AwardZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_AwardZ );
	m_pID_PICTURE_TaskStateWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_TaskStateWall );
	m_pID_LIST_TaskState = (ControlList*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LIST_TaskState );
	m_pID_LIST_TaskInfo = (ControlList*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LIST_TaskInfo );
	m_pID_TEXT_TaskAwardZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskAwardZ );
	m_pID_TEXT_TaskLvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskLvlZ );
	m_pID_TEXT_TaskLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskLvl );
	m_pID_PICTURE_LeftMiddleWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_LeftMiddleWall );
	m_pID_PICTURE_RightMiddleWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_RightMiddleWall );
	m_pID_PICTURE_LeftWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_LeftWall );
	m_pID_PICTURE_RightWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_RightWall );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Accept = (ControlButton*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_BUTTON_Accept );
	m_pID_TEXT_MingWangZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_MingWangZ );
	m_pID_TEXT_MingWang = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_MingWang );
	m_pID_LISTIMG_RewardList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LISTIMG_RewardList );
	m_pID_PICTURE_ReitemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_ReitemWall );
	m_pID_LISTIMG_ItemIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_LISTIMG_ItemIcon );
	m_pID_BUTTON_Brush = (ControlButton*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_BUTTON_Brush );
	m_pID_TEXT_ItemInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_ItemInfo );
	m_pID_TEXT_TakeNum = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TakeNum );
	m_pID_TEXT_TaskExplain = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskExplain );
	m_pID_PICTURE_Title1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_Title1 );
	m_pID_PICTURE_Title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_PICTURE_Title2 );
	m_pID_TEXT_TaskInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_TaskInfo );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_Money );
	m_pID_TEXT_MoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EspecialTask, ID_TEXT_MoneyZ );

	assert( m_pID_FRAME_EspecialTask );
	assert( m_pID_PICTURE_TaskListWall );
	assert( m_pID_LIST_Task );
	assert( m_pID_PICTURE_TitleWall );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_PICTURE_TaskAwardWall );
	assert( m_pID_LISTIMG_Award );
	assert( m_pID_TEXT_ItemZ );
	//assert( m_pID_PICTURE_Title );
	assert( m_pID_PICTURE_TaskInfoWall );
	assert( m_pID_TEXT_TaskListZ );
	assert( m_pID_TEXT_ExpZ );
	assert( m_pID_TEXT_Exp );
	assert( m_pID_TEXT_AwardZ );
	assert( m_pID_PICTURE_TaskStateWall );
	assert( m_pID_LIST_TaskState );
	assert( m_pID_LIST_TaskInfo );
	assert( m_pID_TEXT_TaskAwardZ );
	assert( m_pID_TEXT_TaskLvlZ );
	assert( m_pID_TEXT_TaskLvl );
	assert( m_pID_PICTURE_LeftMiddleWall );
	assert( m_pID_PICTURE_RightMiddleWall );
	assert( m_pID_PICTURE_LeftWall );
	assert( m_pID_PICTURE_RightWall );
	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Accept );
	assert( m_pID_TEXT_MingWangZ );
	assert( m_pID_TEXT_MingWang );
	assert( m_pID_LISTIMG_RewardList );
	assert( m_pID_PICTURE_ReitemWall );
	assert( m_pID_LISTIMG_ItemIcon );
	assert( m_pID_BUTTON_Brush );
	assert( m_pID_TEXT_ItemInfo );
	assert( m_pID_TEXT_TakeNum );
	assert( m_pID_TEXT_TaskExplain );
	assert( m_pID_TEXT_TaskInfo );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_MoneyZ );

	m_pID_LIST_TaskInfo->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_TaskInfo->HaveSelBar( false );	//没有绿色cur选中地图
	//m_pID_LIST_TaskInfo->SetEnablePathFinding(false);//不换图标
// 	m_pID_LIST_TaskInfo->SetHyberOtherClick(Task_HyberOtherClick);

	m_pID_LIST_TaskState->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_TaskState->HaveSelBar( false );	//没有绿色cur选中地图
// 	m_pID_LIST_TaskState->SetHyberOtherClick(Task_HyberOtherClick);
	m_pID_LIST_TaskState->SetHyberRBtnDown( Task_HyberRBtnDown );
	m_pID_LIST_TaskState->setShowTip(true);

	m_pID_LISTIMG_RewardList->SetCanbePick(false);
	m_pID_LISTIMG_RewardList->ShowPressEffect(false);
	m_pID_LISTIMG_RewardList->SetMsgHoldup(false);	//不接受消息


	m_pID_FRAME_EspecialTask->SetOnVisibleChangedFun(OnVisibleChanged);

	SetVisable(false);

	m_canRefresh = true;
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_EspecialTask::_UnLoadUI()
{
	m_pID_FRAME_EspecialTask = NULL;
	m_pID_PICTURE_TaskListWall = NULL;
	m_pID_LIST_Task = NULL;
	m_pID_PICTURE_TitleWall = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_TaskAwardWall = NULL;
	m_pID_LISTIMG_Award = NULL;
	m_pID_TEXT_ItemZ = NULL;
	//m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_TaskInfoWall = NULL;
	m_pID_TEXT_TaskListZ = NULL;
	m_pID_TEXT_ExpZ = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_AwardZ = NULL;
	m_pID_PICTURE_TaskStateWall = NULL;
	m_pID_LIST_TaskState = NULL;
	m_pID_LIST_TaskInfo = NULL;
	m_pID_TEXT_TaskAwardZ = NULL;
	m_pID_TEXT_TaskLvlZ = NULL;
	m_pID_TEXT_TaskLvl = NULL;
	m_pID_PICTURE_LeftMiddleWall = NULL;
	m_pID_PICTURE_RightMiddleWall = NULL;
	m_pID_PICTURE_LeftWall = NULL;
	m_pID_PICTURE_RightWall = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_TEXT_MingWangZ = NULL;
	m_pID_TEXT_MingWang = NULL;
	m_pID_LISTIMG_RewardList = NULL;
	m_pID_PICTURE_ReitemWall = NULL;
	m_pID_LISTIMG_ItemIcon = NULL;
	m_pID_BUTTON_Brush = NULL;
	m_pID_TEXT_ItemInfo = NULL;
	m_pID_TEXT_TakeNum = NULL;
	m_pID_TEXT_TaskExplain = NULL;
	m_pID_PICTURE_Title1 = NULL;
	m_pID_PICTURE_Title2 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\EspecialTask.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_EspecialTask::_IsVisable()
{
	if(!m_pID_FRAME_EspecialTask)
		return false;
	return m_pID_FRAME_EspecialTask->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_EspecialTask::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_EspecialTask)
		return ;

	m_pID_FRAME_EspecialTask->SetVisable( bVisable );

	m_canRefresh = true;
}

static const char* NpcHyberLeft = "<";
static const char* NpcHyberRight = ">";

static void EspecialTask_FillMapPosTip(const NpcCoordInfo* pNpcInfo,ControlList::S_List* pList )
{
	char cTip[256];
	cTip[0] = '\0';
	if (pNpcInfo)
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

static void EspecialTask_AddInfoToList(const std::string& str, ControlList* pList,DWORD col)
{
	std::string localStr = str;
	std::wstring strWide = Common::_tstring::toWideString(localStr.c_str());
	int startCP = 0;
	int endCP = strWide.length();
	int width = ControlHelper::Get().GetTextWidth(strWide, pList->GetFontHDC(),
		startCP, endCP,pList, pList->GetFontIndex() );
	int listWidth = pList->GetWidth() - 5;
	while (width > listWidth)
	{
		--endCP;
		width = ControlHelper::Get().GetTextWidth(strWide,
			pList->GetFontHDC(),
			startCP, endCP,pList, pList->GetFontIndex() );
	}

	ControlList::S_List	stItem;
	stItem.UseSelColor = false;

	NpcCoordInfo* pNpcInfo = NULL;
	if ((int)strWide.size() > endCP)
	{
		localStr = _tstring::toNarrowString(strWide.substr(0, endCP).c_str());
		NpcCoord::getInstance()->addNpcHyber(localStr, NpcHyberLeft, NpcHyberRight,&pNpcInfo);
		EspecialTask_FillMapPosTip(pNpcInfo,&stItem);
		stItem.SetData( localStr.c_str() );
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem);

		EspecialTask_AddInfoToList(_tstring::toNarrowString(strWide.substr(endCP).c_str()), pList,col);
	}
	else
	{
		NpcCoord::getInstance()->addNpcHyber(localStr, NpcHyberLeft, NpcHyberRight,&pNpcInfo);
		EspecialTask_FillMapPosTip(pNpcInfo,&stItem);
		stItem.SetData( localStr.c_str() );
		stItem.SetHyberOtherColor(col );
		pList->AddItem(&stItem);
	}
}

void CUI_ID_FRAME_EspecialTask::Show(const ControlList::S_List *pTaskListItem, int count, int npcId, char taskType)
{
	SetVisable(true);
	if( !m_pID_FRAME_EspecialTask )
		return;

	m_npcId = npcId;
	m_taskType = taskType;

	m_pID_PICTURE_Title1->SetVisable(taskType == MsgScriptReqShowQuestDlg::ShowType_Royal);
	m_pID_PICTURE_Title2->SetVisable(taskType == MsgScriptReqShowQuestDlg::ShowType_Pub);

	m_pID_LIST_Task->Clear();
	m_pID_LIST_Task->AddArrayItem( pTaskListItem, count, false );
	m_pID_LIST_Task->SetCurSelIndex(0);

	m_pID_BUTTON_Accept->SetEnable(count > 0);

	ControlIconDrag::S_ListImg itemListImg;
	int itemCount = 0;
	if (taskType == MsgScriptReqShowQuestDlg::ShowType_Pub)
	{
		itemListImg.SetData(ResetPubQuestItemID2, 1, eIcon_Enable);
		m_pID_TEXT_ItemInfo->SetText(theXmlString.GetString(eClient_PubItemDesc));
		itemCount = thePlayerRole.m_bag.GetItemCount(ResetPubQuestItemID2);
	}
	else
	{
		itemListImg.SetData(ResetPubQuestItemID1, 1, eIcon_Enable);
		m_pID_TEXT_ItemInfo->SetText(theXmlString.GetString(eClient_RoyalItemDesc));
		itemCount = thePlayerRole.m_bag.GetItemCount(ResetPubQuestItemID1);
	}
	m_pID_LISTIMG_ItemIcon->SetItem(&itemListImg, 0);

	char buf[256];
	sprintf(buf, theXmlString.GetString(eText_PubQuestItemCount), itemCount);
	m_pID_TEXT_TakeNum->SetText(buf);

	m_pID_BUTTON_Brush->SetEnable(itemCount > 0);
	
	TaskListSelectChanged();
	RefreshListPictrue();

	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pPlayer)
		return;
	SetVisualPos( *(Vector*)&pPlayer->GetPos());
}

void CUI_ID_FRAME_EspecialTask::RefreshListPictrue()
{
	m_pID_LISTIMG_RewardList->Clear();
	int nItemImage = 0;
	const int nImageListWidth = m_pID_LISTIMG_RewardList->GetRowItemCnt();
	m_pID_LISTIMG_RewardList->SetHeightMaxCnt(m_pID_LIST_Task->GetListItemCnt());
	for (int i = 0; i < m_pID_LIST_Task->GetListItemCnt(); ++i)
	{
		int nQuestId = m_pID_LIST_Task->GetListItem(i)->m_nID;
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
		nItemImage = i* nImageListWidth; 

		if( pInfo )
		{
			SQuest *pQuest = theQuestManager.GetQuest( pInfo->nQuestId );
			if( !pQuest )
			{
				assert(0);
				continue;
			}
			SQuestReward *pReward = NULL;
			ControlIconDrag::S_ListImg stImgItem;
			for ( int n=0; n<pQuest->stReward.size(); n++ )
			{
				pReward = &pQuest->stReward[n];
				ItemDefine::SItemCommon *pItemDetail = NULL;
				if (pReward->byType == SQuest::eReward_Item)
				{
					pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
					if( !pItemDetail )
						continue;
					if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
						pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
						pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
					{
						unsigned char cPro = thePlayerRole.GetProfession();
						if (!(pReward->shProfession & (1 << cPro)))
							continue;

						if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
							continue;
					}
					stImgItem.SetData( pItemDetail->ustItemID, pReward->Number,eIcon_Enable, true );
				}
				else
				{
					if (SQuest::eReward_Money == pReward->byType)
					{
						int money = pReward->Value;
						if (money == 0)
						{
							// deleted, [2/6/2010 jiayi],新的lua文件过长原因，这段暂时去掉，因为没用
							// 								char filename[MAX_PATH];
							// 								sprintf(filename, "%s/Data/Quest/CalculateExp.string", GetRootPath());
							// 								LuaFunction<int> CalcMoney( ScriptManager::instance().getLuaStateOwner(filename), "CalcMoney" );
							// 								money = CalcMoney( pInfo->nQuestId, pQuest->RankId, thePlayerRole.GetLevel() );
							if (money <= 0)
							{
								continue;
							}
						}
					}
					else if (SQuest::eReward_Exp == pReward->byType)
					{
						int RewardValue = pReward->Value;
						if (RewardValue == 0)
						{
							try
							{
								char filename[MAX_PATH];
								MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/Quest/CalculateExp.string", GetRootPath());

								LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
								const char* pszRewardValue = CalcExp( pInfo->nQuestId, pQuest->RankId, thePlayerRole.GetLevel() );

								// modified, jiayi, [2009/11/15]
								// 空指针不能进行std::string的比较
								if ( pszRewardValue && ( std::string("0") == pszRewardValue ) )
								{
									continue;
								}
							}
							catch ( const LuaPlus::LuaException& e )
							{
								OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
							}
						}
					}
					int nRewardItemId = pReward->Icon;
					if (nRewardItemId == 0)
					{
						continue;
					}
					pItemDetail = GettheItemDetail().GetItemByID( nRewardItemId );
					stImgItem.SetData( pItemDetail->ustItemID,1);
				}
				m_pID_LISTIMG_RewardList->SetItem( &stImgItem,nItemImage++ );
			}
		}
	}

	m_pID_LISTIMG_RewardList->SetShowStartHeight(m_pID_LIST_Task->GetShowStartHeight());
}

void CUI_ID_FRAME_EspecialTask::TaskListSelectChanged()
{
	m_pID_LIST_TaskInfo->Clear();
	m_pID_LIST_TaskState->Clear();
	m_pID_TEXT_TaskLvl->SetText("");
	m_pID_TEXT_TaskInfo->SetText("");

	m_pID_TEXT_ExpZ->SetVisable(false);
	m_pID_TEXT_Exp->SetVisable(false);
	m_pID_TEXT_Exp->SetText("");


	m_pID_TEXT_MoneyZ->SetVisable(false);
	m_pID_TEXT_Money->SetVisable(false);

	m_pID_LISTIMG_Award->Clear();
	m_pID_TEXT_ItemZ->SetVisable(false);
	m_pID_LISTIMG_Award->SetVisable(false);

	m_pID_TEXT_MingWangZ->SetVisable(false);
	m_pID_TEXT_MingWang->SetVisable(false);
	m_pID_TEXT_MingWang->SetText("");

	ControlList::S_List* pItem = m_pID_LIST_Task->GetCurSelItem();
	if (!pItem)
		return;

	int nQuestId = pItem->m_nID;

	SQuest *pQuest = theQuestManager.GetQuest( nQuestId );
	if (!pQuest)
		return;

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	if( !pInfo )
		return;

	// Task Level
	std::stringstream sstr;
	sstr << pQuest->GetPlayerReceiveQuestLevel();
	m_pID_TEXT_TaskLvl->SetText(sstr.str());

	// Task Info
	EspecialTask_AddInfoToList(pQuest->GetQuestInfo(),
		m_pID_LIST_TaskInfo,
		Color_Config.getColor((ColorConfigure)(CC_PathFindLinker/*CC_HighLightNpcName*/)));

	std::string strTaskTarget;
	strTaskTarget.clear();

	// Task State
	ControlList::S_List	stItem;
	stItem.UseSelColor = false;

	if (pQuest->stCommitRequirement.empty() || !pInfo->bDone)
	{
		std::string strInfo = pQuest->GetQuestStateInfo();
		if(!strInfo.empty())
		{
			NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
			strTaskTarget += "\n    ";
			strTaskTarget += strInfo;
		}
		//EspecialTask_AddInfoToList(strInfo, m_pID_LIST_TaskState,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	}
	else
	{
		std::string format = theXmlString.GetString(eText_AckNpc);
		int npcId = pQuest->ReplyTargetId;
		const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoord(npcId);
		std::string pNpcName;
		if (pNpcInfo)
		{
			pNpcName = Common::_tstring::toNarrowString(pNpcInfo->_szName.c_str()).c_str();
		}
		char szInfo[dr_MaxQuestDesc] = {0};
		sprintf( szInfo, format.c_str(), pNpcName.c_str() );
		std::string strInfo = szInfo;
		NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);

		strTaskTarget += "\n    ";
		strTaskTarget += szInfo;
		//EspecialTask_AddInfoToList(strInfo, m_pID_LIST_TaskState,Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	}

	std::string strNeedItem;
	strNeedItem.clear();
	s_CUI_NpcTaskDialogBox.GetNeedItemInfo(pQuest,strNeedItem);
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
					sprintf( szInfo, "%s %s (%ld/%ld)", theXmlString.GetString( eText_NeedItem ),
						pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );
					//
					// 						if( nItemCount < pRequirement->MaxNum )
					// 						{
					// 							pInfo->bDone = false;
					// 						}
					// 增加Item寻路tips
					const NpcCoordInfo *pNpcInfo =  NpcCoord::getInstance()->getNpcCoord(pItemDetail->GetItemName());
					EspecialTask_FillMapPosTip(pNpcInfo,&stItem);
				}
				// 					else
				// 					{
				// 						pInfo->bDone = false;
				// 					}
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
					sprintf( szInfo, "%s %s (%ld/%ld)", theXmlString.GetString(eUI_NeedText),
						pMonstor->GetName(), nVar, pRequirement->MaxNum );
					//
					// 						if( nVar < pRequirement->MaxNum )
					// 							pInfo->bDone = false;
					const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoordInPrimaryMap(pMonstor->GetName());
					EspecialTask_FillMapPosTip(pNpcInfo,&stItem);
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
		default:
			// 			assert(false);
			break;
		}
		//strNeedItemInfo += szInfo;

		std::string strInfo = szInfo;

		NpcCoord::getInstance()->addNpcHyber(strInfo, NpcHyberLeft, NpcHyberRight);
		stItem.SetData( strInfo.c_str() );
		stItem.SetHyberOtherColor(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)) );
		m_pID_LIST_TaskState->AddItem(&stItem);
	}

	std::string strTaskInfo;
	strTaskInfo.clear();
	
	strTaskInfo += theXmlString.GetString(eText_Quest_Task);
	strTaskInfo += pQuest->GetQuestName();
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

	std::vector<UiCallbackDataBase*> CallBackDataArr;
	NpcCoord::getInstance()->addNpcHyberForText(strTaskInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,&CallBackDataArr);
	m_pID_TEXT_TaskInfo->SetText(strTaskInfo.c_str(),0,&CallBackDataArr);

	ShowTaskReward(pQuest);
}

void CUI_ID_FRAME_EspecialTask::ShowTaskReward(SQuest* pQuest)
{
	m_pID_TEXT_ExpZ->SetVisable(false);
	m_pID_TEXT_Exp->SetVisable(false);
	m_pID_TEXT_Exp->SetText("");


	m_pID_TEXT_MoneyZ->SetVisable(false);
	m_pID_TEXT_Money->SetVisable(false);

	m_pID_LISTIMG_Award->Clear();
	m_pID_TEXT_ItemZ->SetVisable(false);
	m_pID_LISTIMG_Award->SetVisable(false);

	m_pID_TEXT_MingWangZ->SetVisable(false);
	m_pID_TEXT_MingWang->SetVisable(false);
	m_pID_TEXT_MingWang->SetText("");

	if(!pQuest)
		return;

	// 任务奖励
	ControlListImage* pSpiecialItemImage = m_pID_LISTIMG_Award;
	ControlText* pSpiecialItemText =m_pID_TEXT_ItemZ;
	if ((pQuest->GetReward(SQuest::eReward_Item) == NULL) && pQuest->GetReward(SQuest::eReward_SpecialItem))
	{
		//m_pID_TEXT_ItemZ->SetText(theXmlString.GetString(eText_TheFinalAward));
	}
	else
	{
		//m_pID_TEXT_ItemZ->SetText(theXmlString.GetString(eText_TheAward));
	}

	//	std::string strReward;
	SQuestReward *pReward = NULL;
	for ( int n=0; n<pQuest->stReward.size(); n++ )
	{
		pReward = &pQuest->stReward[n];
		// 		char szInfo[256] = "";
		switch( pReward->byType )
		{
		case SQuest::eReward_JiaoZi:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromJiaoZi(money, text);
					*m_pID_TEXT_Money = text;
					m_pID_TEXT_MoneyZ->SetVisable(true);
					m_pID_TEXT_Money->SetVisable(true);
				}
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

					*m_pID_TEXT_Exp = RewardValue;
					m_pID_TEXT_ExpZ->SetVisable(true);
					m_pID_TEXT_Exp->SetVisable(true);
				}
				else
				{
					try
					{
						char filename[MAX_PATH];
						MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/Quest/CalculateExp.string", GetRootPath());

						//
						// 经验计算
						//
						LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
						const char* pszRewardValue = CalcExp( pQuest->Id, pQuest->RankId, thePlayerRole.GetLevel() );

						// modified, jiayi, [2009/11/15]
						// 空指针不能进行std::string的比较
						if ( pszRewardValue && ( std::string("0") != pszRewardValue ) )
						{
							*m_pID_TEXT_Exp = pszRewardValue;
							m_pID_TEXT_ExpZ->SetVisable(true);
							m_pID_TEXT_Exp->SetVisable(true);
						}
					}
					catch ( const LuaPlus::LuaException& e )
					{
						OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
					}
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
				stItem.SetData( pItemDetail->ustItemID, pReward->Number );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					//ItemDefine::SItemCanEquip* pEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}
				m_pID_LISTIMG_Award->SetItem( &stItem );
				m_pID_LISTIMG_Award->SetVisable(true);
				m_pID_TEXT_ItemZ->SetVisable(true);
			}
			break;
		case SQuest::eReward_Reputation:
			{
				m_pID_TEXT_MingWangZ->SetVisable( true );
				m_pID_TEXT_MingWang->SetVisable( true );

				*m_pID_TEXT_MingWang = pReward->Value;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}


void CUI_ID_FRAME_EspecialTask::Task_HyberRBtnDown( ControlObject* pSender,  const char* szName ,int eHyberType)
{

	if((eHyberType & (eKeyAddress|eKeyNpc)) &&
		(GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) ))
	{
		ControlList* pList = (ControlList*)pSender;
		int nQuestId = pList->GetCurSelItem()->m_nID;

		SQuest* pQuest = theQuestManager.GetQuest(nQuestId);
		int nMapId = -1;
		if( !pQuest )
		{
			assert(0);
			return;
		}
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

void CUI_ID_FRAME_EspecialTask::OnVisibleChanged(ControlObject *pObject)
{
	if(!pObject->IsVisable())
		s_CUI_NpcTaskDialogBox.CloseDialog();
}

// void CUI_ID_FRAME_EspecialTask::Task_HyberOtherClick( ControlObject* pSender, const std::string& content  ,int nId)
// {
// 	ControlList* pList = (ControlList*)pSender;
// 	if (pList == s_CUI_ID_FRAME_EspecialTask.m_pID_LIST_TaskState || pList == s_CUI_ID_FRAME_EspecialTask.m_pID_LIST_TaskInfo)
// 	{
// 		pList = s_CUI_ID_FRAME_EspecialTask.m_pID_LIST_Task;
// 	}
// 	if (!pList->GetCurSelItem())
// 	{
// 		return;
// 	}
// 	int nQuestId = pList->GetCurSelItem()->m_nID;
// 
// 	SQuest* pQuest = theQuestManager.GetQuest(nQuestId);
// 	int nMapId = -1;
// 	if( !pQuest )
// 		return;
// 	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);
// 
// 	if (pInfo && content == Common::_tstring::toNarrowString(pInfo->_szName.c_str()))
// 	{
// 		nMapId = pInfo->_mapId;
// 	}
// 	else
// 	{
// 		pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId);
// 		if (pInfo && content == Common::_tstring::toNarrowString(pInfo->_szName.c_str()))
// 		{
// 			nMapId = pInfo->_mapId;
// 		}
// 	}
// 
// 	// 	std::string npc = NpcCoord::getInstance()->FindFirstNpcName(content);
// 	if (false == NpcCoord::getInstance()->clickHyberToMiniMap(content.c_str(),nMapId))
// 	{
// 		CWorldTile* pCurrTile = CURRENTTILE;
// 		if (pCurrTile->GetMapId() != nMapId)
// 		{
// 			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFind) );
// 		}
// 	}
// 
// }

void CUI_ID_FRAME_EspecialTask::ProcessVisualUI()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if (!pMe )
		return;

	Vector vCurPos;
	pMe->GetPos( &vCurPos.x, &vCurPos.y, &vCurPos.z );

	float xoff = vCurPos.x - m_VisualPos.x;
	float yoff = vCurPos.y - m_VisualPos.y;
	float fDist = sqrtf( xoff*xoff + yoff*yoff );
	if(fDist > 8.0f)
	{
		SetVisable(false);
	}
}

void CUI_ID_FRAME_EspecialTask::RefeshBrushButton()
{
	if(!m_pID_FRAME_EspecialTask)
		return;

	int itemCount = 0;
	if (m_taskType == MsgScriptReqShowQuestDlg::ShowType_Pub)
		itemCount = thePlayerRole.m_bag.GetItemCount(ResetPubQuestItemID2);
	else
		itemCount = thePlayerRole.m_bag.GetItemCount(ResetPubQuestItemID1);

	m_pID_BUTTON_Brush->SetEnable(itemCount > 0);
}
