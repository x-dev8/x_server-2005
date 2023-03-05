/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (2)\TaskTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"

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


#include "TaskTip.h"

CUI_ID_FRAME_TaskTip s_CUI_ID_FRAME_TaskTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TaskTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TaskTip, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LIST_TaskOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LIST_TaskstateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LIST_TaskInfoOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_CHECKBOX_jienengOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_ZhuizongOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LIST_FinishOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyRewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyRewardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyRewardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyRewardOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardListOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardListOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardListOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardListOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_CHECKBOX_autotraceOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_RewardOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_CHECKBOX_Task1OnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_QuxiaoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_ActivityListOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_AbandonTaskOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_CHECKBOX_Task2OnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_SecondItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_SecondItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_SecondItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_LISTIMG_SecondItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_EpicOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_Task0OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_BUTTON_Task1OnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TaskTip, ID_CHECKBOX_ActivityTrackOnCheckBoxCheck )
CUI_ID_FRAME_TaskTip::CUI_ID_FRAME_TaskTip()
{
	// Member
	m_pID_FRAME_TaskTip = NULL;
	m_pID_PICTURE_DI2 = NULL;
	m_pBg2 = NULL;
	m_pID_LIST_Task = NULL;
	m_pID_PICTURE_2574 = NULL;
	m_pID_PICTURE_12238 = NULL;
	m_pID_PICTURE_174 = NULL;
	m_pID_PICTURE_Bg1 = NULL;
	m_pID_TEXT_27806 = NULL;
	m_pID_TEXT_246 = NULL;
	m_pID_PICTURE_122366 = NULL;
	m_pID_PICTURE_Finish1 = NULL;
	m_pID_PICTURE_Finish2 = NULL;
	m_pID_PICTURE_Finish3 = NULL;
	m_pID_PICTURE_Finish4 = NULL;
	m_pID_PICTURE_Finish5 = NULL;
	m_pID_PICTURE_Finish6 = NULL;
	m_pID_PICTURE_Finish7 = NULL;
	m_pID_PICTURE_Finish8 = NULL;
	m_pID_PICTURE_Finish9 = NULL;
	m_pID_PICTURE_Finish10 = NULL;
	m_pID_PICTURE_Finish11 = NULL;
	m_pID_PICTURE_Finish12 = NULL;
	m_pID_PICTURE_Finish13 = NULL;
	m_pID_PICTURE_Finish14 = NULL;
	m_pID_PICTURE_Finish15 = NULL;
	m_pID_PICTURE_Finish16 = NULL;
	m_pID_PICTURE_Finish17 = NULL;
	m_pID_LIST_Taskstate = NULL;
	m_pID_LIST_TaskInfo = NULL;
	m_pID_TEXT_TaskDiff = NULL;
	m_pID_TEXT_TaskLvlZ = NULL;
	m_pID_CHECKBOX_jieneng = NULL;
	m_pID_TEXT_TaskTrack = NULL;
	m_pID_PICTURE_RankId4 = NULL;
	m_pID_PICTURE_RankId3 = NULL;
	m_pID_PICTURE_RankId2 = NULL;
	m_pID_PICTURE_RankId1 = NULL;
	m_pID_PICTURE_RankId0 = NULL;
	m_pID_TEXT_TaskLvl = NULL;
	m_pID_PICTURE_29797 = NULL;
	m_pID_PICTURE_11751 = NULL;
	m_pID_PICTURE_29700 = NULL;
	m_pID_PICTURE_14908 = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Zhuizong = NULL;
	m_pID_LIST_Finish = NULL;
	m_pID_TEXT_FinallyItem = NULL;
	m_pID_LISTIMG_FinallyReward = NULL;
	m_pID_LISTIMG_FinallyReward2 = NULL;
	m_pID_LISTIMG_RewardList = NULL;
	m_pID_TEXT_TaskInfoZ = NULL;
	m_pID_TEXT_SkillExpZ = NULL;
	m_pID_TEXT_SkillExp = NULL;
	m_pID_CHECKBOX_autotrace = NULL;
	m_pID_TEXT_TaskDesc = NULL;
	m_pID_TEXT_TaskTarget = NULL;
	m_pID_TEXT_wp = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_CHECKBOX_Task1 = NULL;
	m_pID_BUTTON_Quxiao = NULL;
	m_pID_BUTTON_ActivityList = NULL;
	m_pID_BUTTON_AbandonTask = NULL;
	m_pID_CHECKBOX_Task2 = NULL;
	m_pID_TEXT_TaskLvlText = NULL;
	m_pID_LISTIMG_SecondItem = NULL;
	m_pID_TEXT_FITEM = NULL;
	m_pID_TEXT_SECITEM = NULL;
	m_pID_BUTTON_Epic = NULL;
	m_pID_BUTTON_Task0 = NULL;
	m_pID_BUTTON_Task1 = NULL;
	m_pID_CHECKBOX_ActivityTrack = NULL;
	m_pID_TEXT_Activity = NULL;
	m_pID_TEXT_TaskInfo = NULL;

}
	// Frame
	bool CUI_ID_FRAME_TaskTip::OnFrameRun()
	{
		return true;
	}
	bool CUI_ID_FRAME_TaskTip::OnFrameRender()
	{
		return true;
	}
	// List
	void CUI_ID_FRAME_TaskTip::ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_TaskTip::ID_LIST_TaskstateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_TaskTip::ID_LIST_TaskInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// CheckBox
	void CUI_ID_FRAME_TaskTip::ID_CHECKBOX_jienengOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_ZhuizongOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// List
	void CUI_ID_FRAME_TaskTip::ID_LIST_FinishOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyRewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyRewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyRewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyRewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyReward2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyReward2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyReward2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_FinallyReward2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardListOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardListOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// CheckBox
	void CUI_ID_FRAME_TaskTip::ID_CHECKBOX_autotraceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// CheckBox
	void CUI_ID_FRAME_TaskTip::ID_CHECKBOX_Task1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_QuxiaoOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_ActivityListOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_AbandonTaskOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// CheckBox
	void CUI_ID_FRAME_TaskTip::ID_CHECKBOX_Task2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_TaskTip::ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_EpicOnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_Task0OnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// Button
	bool CUI_ID_FRAME_TaskTip::ID_BUTTON_Task1OnButtonClick( ControlObject* pSender )
	{
		return true;
	}
	// CheckBox
	void CUI_ID_FRAME_TaskTip::ID_CHECKBOX_ActivityTrackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}

	// 装载UI
bool CUI_ID_FRAME_TaskTip::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TaskTip.MEUI",false,UI_Render_LayerThree );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\TaskTip.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_TaskTip::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_TaskTip, s_CUI_ID_FRAME_TaskTipOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_TaskTip, s_CUI_ID_FRAME_TaskTipOnFrameRender );
		theUiManager.OnListSelectChange( ID_FRAME_TaskTip, ID_LIST_Task, s_CUI_ID_FRAME_TaskTipID_LIST_TaskOnListSelectChange );
		theUiManager.OnListSelectChange( ID_FRAME_TaskTip, ID_LIST_Taskstate, s_CUI_ID_FRAME_TaskTipID_LIST_TaskstateOnListSelectChange );
		theUiManager.OnListSelectChange( ID_FRAME_TaskTip, ID_LIST_TaskInfo, s_CUI_ID_FRAME_TaskTipID_LIST_TaskInfoOnListSelectChange );
		theUiManager.OnCheckBoxCheck( ID_FRAME_TaskTip, ID_CHECKBOX_jieneng, s_CUI_ID_FRAME_TaskTipID_CHECKBOX_jienengOnCheckBoxCheck );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_HELP, s_CUI_ID_FRAME_TaskTipID_BUTTON_HELPOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TaskTipID_BUTTON_CLOSEOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_Zhuizong, s_CUI_ID_FRAME_TaskTipID_BUTTON_ZhuizongOnButtonClick );
		theUiManager.OnListSelectChange( ID_FRAME_TaskTip, ID_LIST_Finish, s_CUI_ID_FRAME_TaskTipID_LIST_FinishOnListSelectChange );
		theUiManager.OnIconDragOn( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyRewardOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyRewardOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyRewardOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyRewardOnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyReward2OnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyReward2OnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyReward2OnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2, s_CUI_ID_FRAME_TaskTipID_LISTIMG_FinallyReward2OnIconRButtonUp );
		theUiManager.OnIconDragOn( ID_FRAME_TaskTip, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardListOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_TaskTip, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardListOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_TaskTip, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardListOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_TaskTip, ID_LISTIMG_RewardList, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardListOnIconRButtonUp );
		theUiManager.OnCheckBoxCheck( ID_FRAME_TaskTip, ID_CHECKBOX_autotrace, s_CUI_ID_FRAME_TaskTipID_CHECKBOX_autotraceOnCheckBoxCheck );
		theUiManager.OnIconDragOn( ID_FRAME_TaskTip, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_TaskTip, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_TaskTip, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_TaskTip, ID_LISTIMG_Reward, s_CUI_ID_FRAME_TaskTipID_LISTIMG_RewardOnIconRButtonUp );
		theUiManager.OnCheckBoxCheck( ID_FRAME_TaskTip, ID_CHECKBOX_Task1, s_CUI_ID_FRAME_TaskTipID_CHECKBOX_Task1OnCheckBoxCheck );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_Quxiao, s_CUI_ID_FRAME_TaskTipID_BUTTON_QuxiaoOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_ActivityList, s_CUI_ID_FRAME_TaskTipID_BUTTON_ActivityListOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_AbandonTask, s_CUI_ID_FRAME_TaskTipID_BUTTON_AbandonTaskOnButtonClick );
		theUiManager.OnCheckBoxCheck( ID_FRAME_TaskTip, ID_CHECKBOX_Task2, s_CUI_ID_FRAME_TaskTipID_CHECKBOX_Task2OnCheckBoxCheck );
		theUiManager.OnIconDragOn( ID_FRAME_TaskTip, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskTipID_LISTIMG_SecondItemOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_TaskTip, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskTipID_LISTIMG_SecondItemOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_TaskTip, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskTipID_LISTIMG_SecondItemOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_TaskTip, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_TaskTipID_LISTIMG_SecondItemOnIconRButtonUp );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_Epic, s_CUI_ID_FRAME_TaskTipID_BUTTON_EpicOnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_Task0, s_CUI_ID_FRAME_TaskTipID_BUTTON_Task0OnButtonClick );
		theUiManager.OnButtonClick( ID_FRAME_TaskTip, ID_BUTTON_Task1, s_CUI_ID_FRAME_TaskTipID_BUTTON_Task1OnButtonClick );
		theUiManager.OnCheckBoxCheck( ID_FRAME_TaskTip, ID_CHECKBOX_ActivityTrack, s_CUI_ID_FRAME_TaskTipID_CHECKBOX_ActivityTrackOnCheckBoxCheck );

		m_pID_FRAME_TaskTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TaskTip );
		m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_DI2 );
		m_pBg2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, Bg2 );
		m_pID_LIST_Task = (ControlList*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LIST_Task );
		m_pID_PICTURE_2574 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_2574 );
		m_pID_PICTURE_12238 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_12238 );
		m_pID_PICTURE_174 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_174 );
		m_pID_PICTURE_Bg1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Bg1 );
		m_pID_TEXT_27806 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_27806 );
		m_pID_TEXT_246 = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_246 );
		m_pID_PICTURE_122366 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_122366 );
		m_pID_PICTURE_Finish1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish1 );
		m_pID_PICTURE_Finish2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish2 );
		m_pID_PICTURE_Finish3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish3 );
		m_pID_PICTURE_Finish4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish4 );
		m_pID_PICTURE_Finish5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish5 );
		m_pID_PICTURE_Finish6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish6 );
		m_pID_PICTURE_Finish7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish7 );
		m_pID_PICTURE_Finish8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish8 );
		m_pID_PICTURE_Finish9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish9 );
		m_pID_PICTURE_Finish10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish10 );
		m_pID_PICTURE_Finish11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish11 );
		m_pID_PICTURE_Finish12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish12 );
		m_pID_PICTURE_Finish13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish13 );
		m_pID_PICTURE_Finish14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish14 );
		m_pID_PICTURE_Finish15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish15 );
		m_pID_PICTURE_Finish16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish16 );
		m_pID_PICTURE_Finish17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_Finish17 );
		m_pID_LIST_Taskstate = (ControlList*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LIST_Taskstate );
		m_pID_LIST_TaskInfo = (ControlList*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LIST_TaskInfo );
		m_pID_TEXT_TaskDiff = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskDiff );
		m_pID_TEXT_TaskLvlZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskLvlZ );
		m_pID_CHECKBOX_jieneng = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_CHECKBOX_jieneng );
		m_pID_TEXT_TaskTrack = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskTrack );
		m_pID_PICTURE_RankId4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_RankId4 );
		m_pID_PICTURE_RankId3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_RankId3 );
		m_pID_PICTURE_RankId2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_RankId2 );
		m_pID_PICTURE_RankId1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_RankId1 );
		m_pID_PICTURE_RankId0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_RankId0 );
		m_pID_TEXT_TaskLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskLvl );
		m_pID_PICTURE_29797 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_29797 );
		m_pID_PICTURE_11751 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_11751 );
		m_pID_PICTURE_29700 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_29700 );
		m_pID_PICTURE_14908 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_PICTURE_14908 );
		m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_HELP );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_CLOSE );
		m_pID_BUTTON_Zhuizong = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_Zhuizong );
		m_pID_LIST_Finish = (ControlList*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LIST_Finish );
		m_pID_TEXT_FinallyItem = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_FinallyItem );
		m_pID_LISTIMG_FinallyReward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward );
		m_pID_LISTIMG_FinallyReward2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LISTIMG_FinallyReward2 );
		m_pID_LISTIMG_RewardList = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LISTIMG_RewardList );
		m_pID_TEXT_TaskInfoZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskInfoZ );
		m_pID_TEXT_SkillExpZ = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_SkillExpZ );
		m_pID_TEXT_SkillExp = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_SkillExp );
		m_pID_CHECKBOX_autotrace = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_CHECKBOX_autotrace );
		m_pID_TEXT_TaskDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskDesc );
		m_pID_TEXT_TaskTarget = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskTarget );
		m_pID_TEXT_wp = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_wp );
		m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LISTIMG_Reward );
		m_pID_CHECKBOX_Task1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_CHECKBOX_Task1 );
		m_pID_BUTTON_Quxiao = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_Quxiao );
		m_pID_BUTTON_ActivityList = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_ActivityList );
		m_pID_BUTTON_AbandonTask = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_AbandonTask );
		m_pID_CHECKBOX_Task2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_CHECKBOX_Task2 );
		m_pID_TEXT_TaskLvlText = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskLvlText );
		m_pID_LISTIMG_SecondItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_LISTIMG_SecondItem );
		m_pID_TEXT_FITEM = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_FITEM );
		m_pID_TEXT_SECITEM = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_SECITEM );
		m_pID_BUTTON_Epic = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_Epic );
		m_pID_BUTTON_Task0 = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_Task0 );
		m_pID_BUTTON_Task1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_BUTTON_Task1 );
		m_pID_CHECKBOX_ActivityTrack = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_CHECKBOX_ActivityTrack );
		m_pID_TEXT_Activity = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_Activity );
		m_pID_TEXT_TaskInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskTip, ID_TEXT_TaskInfo );
		assert( m_pID_FRAME_TaskTip );
		assert( m_pID_PICTURE_DI2 );
		assert( m_pBg2 );
		assert( m_pID_LIST_Task );
		assert( m_pID_PICTURE_2574 );
		assert( m_pID_PICTURE_12238 );
		assert( m_pID_PICTURE_174 );
		assert( m_pID_PICTURE_Bg1 );
		assert( m_pID_TEXT_27806 );
		assert( m_pID_TEXT_246 );
		assert( m_pID_PICTURE_122366 );
		assert( m_pID_PICTURE_Finish1 );
		assert( m_pID_PICTURE_Finish2 );
		assert( m_pID_PICTURE_Finish3 );
		assert( m_pID_PICTURE_Finish4 );
		assert( m_pID_PICTURE_Finish5 );
		assert( m_pID_PICTURE_Finish6 );
		assert( m_pID_PICTURE_Finish7 );
		assert( m_pID_PICTURE_Finish8 );
		assert( m_pID_PICTURE_Finish9 );
		assert( m_pID_PICTURE_Finish10 );
		assert( m_pID_PICTURE_Finish11 );
		assert( m_pID_PICTURE_Finish12 );
		assert( m_pID_PICTURE_Finish13 );
		assert( m_pID_PICTURE_Finish14 );
		assert( m_pID_PICTURE_Finish15 );
		assert( m_pID_PICTURE_Finish16 );
		assert( m_pID_PICTURE_Finish17 );
		assert( m_pID_LIST_Taskstate );
		assert( m_pID_LIST_TaskInfo );
		assert( m_pID_TEXT_TaskDiff );
		assert( m_pID_TEXT_TaskLvlZ );
		assert( m_pID_CHECKBOX_jieneng );
		assert( m_pID_TEXT_TaskTrack );
		assert( m_pID_PICTURE_RankId4 );
		assert( m_pID_PICTURE_RankId3 );
		assert( m_pID_PICTURE_RankId2 );
		assert( m_pID_PICTURE_RankId1 );
		assert( m_pID_PICTURE_RankId0 );
		assert( m_pID_TEXT_TaskLvl );
		assert( m_pID_PICTURE_29797 );
		assert( m_pID_PICTURE_11751 );
		assert( m_pID_PICTURE_29700 );
		assert( m_pID_PICTURE_14908 );
		assert( m_pID_BUTTON_HELP );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_BUTTON_Zhuizong );
		assert( m_pID_LIST_Finish );
		assert( m_pID_TEXT_FinallyItem );
		assert( m_pID_LISTIMG_FinallyReward );
		assert( m_pID_LISTIMG_FinallyReward2 );
		assert( m_pID_LISTIMG_RewardList );
		assert( m_pID_TEXT_TaskInfoZ );
		assert( m_pID_TEXT_SkillExpZ );
		assert( m_pID_TEXT_SkillExp );
		assert( m_pID_CHECKBOX_autotrace );
		assert( m_pID_TEXT_TaskDesc );
		assert( m_pID_TEXT_TaskTarget );
		assert( m_pID_TEXT_wp );
		assert( m_pID_LISTIMG_Reward );
		assert( m_pID_CHECKBOX_Task1 );
		assert( m_pID_BUTTON_Quxiao );
		assert( m_pID_BUTTON_ActivityList );
		assert( m_pID_BUTTON_AbandonTask );
		assert( m_pID_CHECKBOX_Task2 );
		assert( m_pID_TEXT_TaskLvlText );
		assert( m_pID_LISTIMG_SecondItem );
		assert( m_pID_TEXT_FITEM );
		assert( m_pID_TEXT_SECITEM );
		assert( m_pID_BUTTON_Epic );
		assert( m_pID_BUTTON_Task0 );
		assert( m_pID_BUTTON_Task1 );
		assert( m_pID_CHECKBOX_ActivityTrack );
		assert( m_pID_TEXT_Activity );
		assert( m_pID_TEXT_TaskInfo );
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_TaskTip::_UnLoadUI()
	{
		m_pID_FRAME_TaskTip = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\TaskTip.MEUI" );
	}
	// 是否可视
	bool CUI_ID_FRAME_TaskTip::_IsVisable()
	{
		return m_pID_FRAME_TaskTip->IsVisable();
	}
	// 设置是否可视
	void CUI_ID_FRAME_TaskTip::_SetVisable( const bool bVisable )
	{
		if ( m_pID_FRAME_TaskTip == NULL )
		{
			return;
		}
		
		m_pID_FRAME_TaskTip->SetVisable( bVisable );
	}

	void CUI_ID_FRAME_TaskTip::ClearShowInfo()
	{
		*m_pID_TEXT_TaskInfo = "";

		m_pID_LISTIMG_Reward->Clear();
		m_pID_LISTIMG_Reward->SetVisable(false);
		m_pID_LISTIMG_SecondItem->Clear();
		m_pID_LISTIMG_SecondItem->SetVisable(false);
		m_pID_TEXT_FITEM->SetText("");
		m_pID_TEXT_FITEM->SetVisable(false);
		m_pID_TEXT_SECITEM->SetText("");
		m_pID_TEXT_SECITEM->SetVisable(false);
	}

void CUI_ID_FRAME_TaskTip::GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem)
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
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),pReward->Value);
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
		case SQuest::eReward_SkillExp:
			{
				int  nRewardValue = pReward->Value;
				if(0 != nRewardValue)
				{
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
}

void CUI_ID_FRAME_TaskTip::GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem)
{
	if(!pQuest)
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

void CUI_ID_FRAME_TaskTip::ModifyRewardItem(int nTop,int nLeft)
{
	if(!m_pID_FRAME_TaskTip)
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
	m_pID_LISTIMG_Reward->SetRealRect(&listRect);

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
	m_pID_LISTIMG_SecondItem->SetRealRect(&listRect);

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


bool CUI_ID_FRAME_TaskTip::UITask_ShowInfo(int questId)
{
	ClearShowInfo();
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

		//ModifyRewardItem(rc.top + nHeight,rc.left);
		m_pID_LISTIMG_Reward->SetVisable(true);
		m_pID_LISTIMG_SecondItem->SetVisable(true);
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
